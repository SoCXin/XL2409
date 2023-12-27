/*************************************************************************/
#include "bsp_expand.h"
#include <stdio.h>
#include <string.h>
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_tim3.h"
#include "bsp_uart.h"
#include "bsp_rf.h"
#include "bsp_encode.h"
#include "bsp_pins.h"
#include "bsp_flash.h"
#include "bsp_keyslisten.h"
#include "bsp_state_machine.h"

r_infor_flag_block infor_flag = {0, 0, 0};
uint8_t tap_first[4] = {1, 1, 1, 1}; //点动起始/结束
uint8_t selfdelay[4] = {0, 0, 0, 0}; //自锁传递引脚信息
uint8_t interdelay[4] = {0, 0, 0, 0}; //互锁传递引脚信息
uint8_t rf_flag = 0;  //发送标记
uint8_t t_tap_first[4] = {1, 1, 1, 1}; //点动模式判断第一次按下 发送一次反馈信号

void Ignore(void)
{
    //空函数，不进行操作
}

//打印日志 调试用
void PrintLog(void)
{
    Encode_Form();
    SendEncode();
}

//按下次数无功能 闪烁两次
void LedBlinkTwice(void)
{
    LedCount(LED1_PORT, LED1_PIN, 2);
}

//清状态
void Clear_ModeFlag(void)
{
    memset(tap_first, 1, 4);
    memset(selfdelay, 0, 4);
    memset(interdelay, 0, 4);
    memset(encode_flag.keys_flag, 0, 4);
    memset(t_tap_first, 1, 4);
    rf_flag = 0;

}

//点动模式接收端熄灯
void LED_MODE1_OFF(void)
{
    uint8_t i = 0;
    for(i = 0; i < 4; i++)
    {
        if(tap_first[i] == 0)
        {
            if(tim_rfsend >= 320)
            {
                LedOff(LED2_PORT, LED2_PIN);
                tap_first[i] = 1;
            }
        }
    }
}


//判断地址是否相同
uint8_t Judge_Adr(void)
{
    uint8_t i = 0;
    uint8_t t = 0;
    FLASH_Read_8(FLASH_INFOR_ADR, FlashReadBuf, FLASH_INFOR_LENGTH);
    for(i = 0; i < 4; i++) //地址相同
    {
        if(mRfRxBuf[2 + i] == FlashReadBuf[i])
        {
            t++;
        }
    }
    if(t == 4)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//判断flash中是否有对应地址 以及读出模式信息
uint8_t Judge_Flash_Mate(uint16_t nums)
{
    uint16_t i = 0;
    uint16_t length = 8 * nums;
    uint8_t flash_matebuf[length];
    if(length > 0)
    {
        FLASH_Read_8(FLASH_MATE_ADR, flash_matebuf, length);
        for(i = 0; i < nums; i++)
        {
            if(mRfRxBuf[2] == flash_matebuf[0 + 8 * i] && mRfRxBuf[3] == flash_matebuf[1 + 8 * i] && mRfRxBuf[4] == flash_matebuf[2 + 8 * i] && mRfRxBuf[5] == flash_matebuf[3 + 8 * i])
            {
                infor_flag.t_or_r_mode_flag = flash_matebuf[4 + 8 * i];
                return 1;
            }
        }
    }
    return 0;
}

uint8_t Rssi_Busy(void)
{
    uint8_t rssi_val;
    __disable_irq();
    rssi_val = RfReadRssi();
    __enable_irq();

    if(rssi_val > 67)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}
/***************************************************************/
//接收端 点动模式 进入待配对状态 学习按键K 1次
void R_Tap(void)
{
    infor_flag.r_reqmate_flag = 1;  //点动模式待配对
    encode_flag.state_flag = 10;  //状态位为0A
    Encode_Form();
    SendEncode();
    LedOn(LED2_PORT, LED2_PIN);
}

//接收端 自锁模式 进入待配对状态 学习按键K 2次
void R_Selflock(void)
{
    infor_flag.r_reqmate_flag = 2;  //自锁模式待配对
    encode_flag.state_flag = 11;  //状态位为0B
    Encode_Form();
    SendEncode();
    LedOn(LED2_PORT, LED2_PIN);

}

//接收端 互锁模式 进入待配对状态 学习按键K 3次
void R_Interlock(void)
{
    infor_flag.r_reqmate_flag = 3;  //自锁模式待配对
    encode_flag.state_flag = 12;  //状态位为0C
    Encode_Form();
    SendEncode();
    LedOn(LED2_PORT, LED2_PIN);
}

//接收端 切换为发射端  学习按键K按下5次
void R_Toggle(void)
{
    infor_flag.r_reqmate_flag = 0; //待配对状态清空
    KEYS_Init();  //配置四个IO为按键
    Clear_ModeFlag();  //清空三种模式标志位
    encode_flag.t_or_r_mode_flag = 1;  //转为发射态
    encode_flag.adr_change = 2;  //地址修正为新随机地址
    //Encode_Form();
    //SendEncode();
    pCurrentState = &T_State; //切换状态机
    Flash_Infor();
    LedCount(LED2_PORT, LED2_PIN, 2); //闪烁两次
}

//接收端 清除状态  学习按键K按下8次
void R_Clear(void)
{
    infor_flag.r_reqmate_flag = 0; //待配对状态清空
    infor_flag.tr_mate_nums = 0;
    Clear_ModeFlag(); //清空三种模式标志位
    Encode_Form();
    //SendEncode();
    //********************************/存入Flash
    Flash_Erase(FLASH_MATE_ADR); //擦除Flash
    Flash_Infor();
    LedCount(LED2_PORT, LED2_PIN, 8);
}
/***************************************************************/

//接收端配对过程
void R_Mate_Receive(void)
{
    infor_flag.t_or_r_mode_flag = infor_flag.r_reqmate_flag;
    infor_flag.r_reqmate_flag = 0;
    encode_flag.adr_change = 3;	//以发射端的地址反馈
    encode_flag.state_flag = 1; //配对完成标志位，传回发射端
    LedCount(LED2_PORT, LED2_PIN, 5);
    Encode_Form();
    SendEncode();
    //********************************/存入Flash
    Flash_Mate_Form();
    infor_flag.tr_mate_nums ++;
    Flash_Infor();
}

//接收端 点动模式 对信号响应
void R_Tap_Receive(void)
{
    uint8_t i = 0;
    for(i = 0; i < 4; i++)
    {
        if(mRfRxBuf[i + 6] == 0x01)
        {
            tim_rfsend = 0; //每收到一次按键按下信号，红灯熄灭计时重置
        }
        if(mRfRxBuf[i + 6] == 0x01 && tap_first[i] == 1) //对应按键第一次按下 tap_first用来辅助判断是否按键结束
        {
            //printf("111 \n");
            tap_first[i] = 0;
            encode_flag.keys_flag[i] = 1;
            encode_flag.state_flag = 2;  //状态位 反馈信号
            encode_flag.adr_change = 3;	//以发射端的地址反馈
            LedOn(LED2_PORT, LED2_PIN);
            Encode_Form();
            SendEncode();
        }
        if(mRfRxBuf[i + 6] == 0x00 && tap_first[i] == 0)
        {
            // printf("222 \n");
            tap_first[i] = 1;
            encode_flag.keys_flag[i] = 0;
            //SendEncode();

        }
    }
    if(tap_first[0] + tap_first[1] + tap_first[2] + tap_first[3] == 4)  ///*
    {
        // printf("333 \n");
        LedOff(LED2_PORT, LED2_PIN);   //四按键均未按下灯熄灭
    }
    Pins_Ctrl();  //置位引脚高低

}


//接收端 自锁模式 对信号响应
void R_Selflock_Receive(void)
{
    uint8_t i = 0;
    for(i = 0; i < 4; i++)
    {
        if(mRfRxBuf[i + 6] == 0x01)
        {
            selfdelay[i] = 1;
        }
        if(mRfRxBuf[i + 6] == 0x00 && selfdelay[i] == 1)
        {
            selfdelay[i] = 0;
            if(encode_flag.keys_flag[i] == 0)
            {
                encode_flag.keys_flag[i] = 1;
            }
            else
            {
                encode_flag.keys_flag[i] = 0;
            }
            encode_flag.state_flag = 2;  //状态位 反馈信号
            encode_flag.adr_change = 3;	//以发射端的地址反馈
            Encode_Form();
            SendEncode();
            LedCount(LED2_PORT, LED2_PIN, 1);
        }
    }
    Pins_Ctrl();  //置位引脚高低
}


//接收态 互锁模式 对信号响应
void R_Interlock_Receive(void)
{
    uint8_t i = 0;
    memset(encode_flag.keys_flag, 0, 4);
    for(i = 0; i < 4; i++)
    {
        if(mRfRxBuf[i + 6] == 0x01)
        {
            interdelay[i] = 1;
        }

        if(mRfRxBuf[i + 6] == 0x00 && interdelay[i] == 1)
        {
            interdelay[i] = 0;
            encode_flag.keys_flag[i] = 1;
            encode_flag.state_flag = 2;  //状态位 反馈信号
            encode_flag.adr_change = 3;	//以发射端的地址反馈
            Encode_Form();
            SendEncode();
            LedCount(LED2_PORT, LED2_PIN, 1);
        }
    }
    Pins_Ctrl();  //置位引脚高低
}


//接收端 对信号响应
void R_Receive(void)
{
    //对方为发射态 且 自身等待配对
    if(mRfRxBuf[1] == t_encode && infor_flag.r_reqmate_flag > 0 && Judge_Flash_Mate(infor_flag.tr_mate_nums) == 0) //配对过程
    {
        if(mRfRxBuf[6] + mRfRxBuf[7] + mRfRxBuf[8] + mRfRxBuf[9] == 0)
        {
            R_Mate_Receive();
        }
        //存入Flash
    }
    else if(mRfRxBuf[1] == t_encode && Judge_Flash_Mate(infor_flag.tr_mate_nums) == 1) //能匹配上
    {
        switch(infor_flag.t_or_r_mode_flag)
        {
        case 1: //为点动
            R_Tap_Receive();
            break;
        case 2: //为自锁
            R_Selflock_Receive();
            break;
        case 3: //为互锁
            R_Interlock_Receive();
            break;
        }
    }
}


/***************************************************************/
//发射端 切换为接收端  学习按键K按下5次
void T_Toggle(void)
{
    Pins_Init();  //配置四个IO为引脚
    Clear_ModeFlag(); //清空三种模式标志位
    encode_flag.t_or_r_mode_flag = 0;  //转为接收态
    encode_flag.adr_change = 1;  //地址修正为空地址
    Encode_Form();
    //SendEncode();
    pCurrentState = &R_State; //切换状态机
    //********************************/存入Flash
    Flash_Infor();
    LedCount(LED2_PORT, LED2_PIN, 5);	 //闪烁五次
}

//发射端按键反馈
void T_Keys_State(void)
{
    uint8_t i = 0;
    for(i = 0; i < 4; i++)
    {
        if(studykey_lock == 0 && keys[i] == 1 && t_tap_first[i] == 1)
        {
            RandNum();
            encode_flag.keys_flag[i] = 1, rf_flag = 1, t_tap_first[i] = 0, tim_rfsend = 300;
            LedOn(LED2_PORT, LED2_PIN);
        }
        if(keys[i] == 0 && t_tap_first[i] == 0)
        {
            t_tap_first[i] = 1;
            encode_flag.keys_flag[i] = 0;
            if(keys[0] + keys[1] + keys[2] + keys[3] == 0)
            {
                LedOff(LED2_PORT, LED2_PIN);    //所有按键均弹起才熄灯与停止发送
                rf_flag = 0;
            }
            Encode_Form();
            SendEncode();
        }
    }

    if(rf_flag == 1)
    {
        //		rf_flag = 0;
        if(tim_rfsend >= 300)  //发送一次
        {
            tim_rfsend = 0;
            Encode_Form();
            SendEncode();
        }
    }
}


//发射端 对信号响应
void T_Receive(void)
{
    //对方为接收态且地址相同
    if(mRfRxBuf[1] == r_encode && Judge_Adr() == 1)
    {
        //  LedCount(LED1_PORT, LED1_PIN, 7); //*********蓝灯***********//
        if(mRfRxBuf[10] == 0x01)  //接收到配对完成信号
        {
            LedCount(LED1_PORT, LED1_PIN, 5); //*********蓝灯***********//
        }
        if(mRfRxBuf[10] == 0x02)  //接收到反馈信号
        {
            LedCount(LED1_PORT, LED1_PIN, 3); //*********蓝灯***********//
        }

    }
}


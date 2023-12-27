/*************************************************************************/
//编码生成、发送、读取
/*************************************************************************/
#include "bsp_encode.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "bsp_rf.h"
#include "bsp_expand.h"
#include "bsp_flash.h"
#include "bsp_keyslisten.h"
#include "bsp_state_machine.h"
#include "bsp_led.h"

unsigned char gSendBuf1[TEST_BER_DATA_LEN] = "\xAB\xBB\xFF\xFF\xFF\xFF\x00\x00\x00\x00\x00"; //0 起始  1 发射/接收  2-5 地址  6-9 按键K  10状态位
//状态位： 01 完成配对（接收）  02反馈信号（接收） 11点动模式待配对 12自锁模式待配对 13互锁模式待配对（后三种调试用）
encode_flag_block encode_flag = {0, 0, 0, {0, 0, 0, 0}};

uint8_t FlashReadBuf[FLASH_MATE_LENGTH]; //Flash读取数据缓冲区

//更新Flash中自身状态信息
void Flash_Infor(void)
{
    uint8_t FlashSendBuf1[FLASH_INFOR_LENGTH / 2];
    if(encode_flag.t_or_r_mode_flag == 0)
    {
        FlashSendBuf1[0] = r_encode;   //接收态
    }
    if(encode_flag.t_or_r_mode_flag == 1)
    {
        FlashSendBuf1[0] = t_encode;   //发射态
    }
    FlashSendBuf1[1] = infor_flag.tr_mate_nums;
    FlashSendBuf1[2] = first;
    FlashSendBuf1[3] = 0;
    Flash_ChangeInfor(FLASH_INFOR_ADR, FlashSendBuf1);

}

//将地址信息存入Flash
void Flash_Adr(void)
{
    uint8_t Flash_Adr_Infor_Buf[FLASH_INFOR_LENGTH];
    uint8_t i;
    for(i = 0; i < 4; i++)
    {
        Flash_Adr_Infor_Buf[i] = rand_num[i];
    }

    if(encode_flag.t_or_r_mode_flag == 0)
    {
        Flash_Adr_Infor_Buf[4] = r_encode;   //接收态
    }
    if(encode_flag.t_or_r_mode_flag == 1)
    {
        Flash_Adr_Infor_Buf[4] = t_encode;   //发射态
    }
    Flash_Adr_Infor_Buf[5] = infor_flag.tr_mate_nums;
    Flash_Adr_Infor_Buf[6] = first;
    Flash_Adr_Infor_Buf[7] = 0;

    Flash_Write_8(FLASH_INFOR_ADR, Flash_Adr_Infor_Buf, FLASH_INFOR_LENGTH);
}


//将新配对的发射端信息存入Flash
void Flash_Mate_Form(void)
{
    uint8_t FlashSendBuf2[FLASH_MATE_LENGTH];
    uint8_t i = 0;
    for(i = 0; i < 4; i++)
    {
        FlashSendBuf2[i] = mRfRxBuf[2 + i];
    }
    FlashSendBuf2[4] = infor_flag.t_or_r_mode_flag;
    FlashSendBuf2[5] = 0;
    FlashSendBuf2[6] = 0;
    FlashSendBuf2[7] = 0;
    FLASH_AddMate(FLASH_MATE_ADR, FlashSendBuf2, infor_flag.tr_mate_nums); //新配对信息存入flash
}

//退避产生随机延时重新发送
uint8_t SendDelay_Create(void)
{
    uint8_t Delaytime;
    FLASH_Read_8(FLASH_INFOR_ADR, FlashReadBuf, FLASH_INFOR_LENGTH);
    srand(FlashReadBuf[0]);  //随机地址的第一位作为随机延时的种子
    Delaytime = rand() % 20 + 30;
    return Delaytime;
}

//编码形成
void Encode_Form(void)
{
    uint16_t i = 0;
    gSendBuf1[0] = head_encode;
    //gSendBuf1[0] = RfReadRssi();
    if(encode_flag.t_or_r_mode_flag == 0)
    {
        gSendBuf1[1] = r_encode;   //接收态
    }
    if(encode_flag.t_or_r_mode_flag == 1)
    {
        gSendBuf1[1] = t_encode;   //发射态
    }

    //地址
    switch(encode_flag.adr_change)
    {
    case 1://接收态空地址
        for(i = 0; i < 4; i++)
        {
            gSendBuf1[2 + i] = adrnull_encode;
        }
        encode_flag.adr_change = 0;
        break;

    case 2://发射态产生随机地址
        FLASH_Read_8(FLASH_INFOR_ADR, FlashReadBuf, FLASH_INFOR_LENGTH);
        for(i = 0; i < 4; i++)
        {
            gSendBuf1[2 + i] = FlashReadBuf[i];
            encode_flag.adr_change = 0;
        }
        break;

    case 3://接收态学习发射态的地址

        for(i = 0; i < 4; i++)
        {
            gSendBuf1[2 + i] = mRfRxBuf[2 + i];
        }
        encode_flag.adr_change = 1;
        break;
    }


    //四按键/引脚
    for(i = 0; i < 4; i++)
    {
        gSendBuf1[i + 6] = encode_flag.keys_flag[i];
    }

    //状态位
    gSendBuf1[10] = encode_flag.state_flag;
    encode_flag.state_flag = 0;
}

uint8_t busy_count = 0;
//发送包
void SendEncode(void)
{
    if(Rssi_Busy() == 1)
    {
        RfDataPackageSend(gSendBuf1, TEST_BER_DATA_LEN);
        busy_count = 0;
    }
    else
    {
        if(busy_count > 5)
        {
            busy_count = 0;
            printf("Send False\n");
        }
        else
        {
            busy_count ++;
            printf("busy_count = %d \n", busy_count);
            HAL_Delay(SendDelay_Create());
            SendEncode();
        }
    }

}


//接收监测
void ReceiveEncode(void)
{
    LED_MODE1_OFF();
    if(mRfRxBuf[0] == head_encode)  //第一位为指定值
    {
        pCurrentState -> pt_or_r_response();
        memset(mRfRxBuf, 0, TEST_BER_DATA_LEN);
    }
}


//重启读取flash中的状态
void Flash_Readstate(void)
{
    FLASH_Read_8(FLASH_INFOR_ADR, FlashReadBuf, FLASH_INFOR_LENGTH);
    uint8_t i = 0;
    for(i = 0; i < 4; i++)
    {
        gSendBuf1[2 + i] = FlashReadBuf[i];
    }
    if(FlashReadBuf[5] == 0xff)
    {
        infor_flag.tr_mate_nums = 0;

    }
    else
    {
        infor_flag.tr_mate_nums = FlashReadBuf[5];
    }
    first = FlashReadBuf[6];
    if(FlashReadBuf[4] == r_encode)
    {
        encode_flag.t_or_r_mode_flag = 0;
        encode_flag.adr_change = 1;
        pCurrentState = &R_State;
    }
    if(FlashReadBuf[4] == t_encode)
    {
        encode_flag.t_or_r_mode_flag = 1;
        pCurrentState = &T_State;
    }
    memset(FlashReadBuf, 0, FLASH_INFOR_LENGTH);
    Encode_Form();
    // SendEncode();
}

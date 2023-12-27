#include "XL2400P.h"

unsigned char    gRFChnl;//跳频变量

const unsigned char CHANNELTABLE[] = {05, 76, 19};//频点

unsigned char RF_Test_Adrress[5]={0xcc,0xcc,0xcc,0xcc,0xcc};//RF地址


/*********************************************************************************************/
/***********************************  延时函数  ***********************************************/
/*********************************************************************************************/

//微秒延时函数
void DelayUs(unsigned char Time)
{
	unsigned char a;
	for(a=0;a<Time;a++)
	{
	}
	Time>>=1;
	for(a=0;a<Time;a++)
	{
	}
	Time>>=2;
	for(a=0;a<Time;a++)
	{
	}
} 

//毫秒延时函数
void DelayMs(unsigned char Time)
{
	unsigned char a,b;
	for(a=0;a<Time;a++)
	{	
		for(b=0;b<5;b++)
		{
		 	DelayUs(195); 	
		}
	}
}

/*********************************************************************************************/
/******************************  XL2400P_SPI通讯  ********************************************/
/*********************************************************************************************/

//射频GPIO引脚初始化
void RF_GPIO_Init(void)
{
	/*使能模块时钟*/
	__HAL_RCC_GPIOF_CLK_ENABLE();//PF
	__HAL_RCC_GPIOA_CLK_ENABLE();//PA

	GPIO_InitTypeDef   GPIO_InitStruct;

    GPIO_InitStruct.Pin   = GPIO_PIN_1;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_InitStruct.Pin   = GPIO_PIN_3;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	
    GPIO_InitStruct.Pin   = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


//SPI通讯初始化
void RF_SPI_Init(void)
{
	CS_High;
	SCK_Low;
}

//SPI写数据（1字节）
//参数 需要写入的数据
void SPI_Write_Byte(unsigned char buff)
{
	unsigned char i;
    for(i = 0; i < 8; i++)
	{
        SCK_Low;

        if(buff & 0x80)
		{
            SPI_MOSI_High;
		}
        else
		{
            SPI_MOSI_Low;
		}

        buff = buff << 1;

        SCK_High;
    }
    SPI_MOSI_High;
    SCK_Low;
}


//SPI读数据（1字节）
//返回 读取到的数据
unsigned char SPI_Read_Byte(void)
{
	unsigned char i;  
    unsigned char  buff = 0;

    for(i = 0; i < 8; i++)
    {
        SCK_Low;
        buff = buff << 1;
        SCK_High;
        if(Read_MOSI)
		{
			buff |= 0x01;
		}         
    }
    SCK_Low;

    return buff;
}

//SPI写数据到寄存器
//参数1 寄存器地址+写指令
//参数2 需要写入的数据
void SPI_Write_Reg(unsigned char RfAdress,unsigned char RfData)
{
	CS_Low;//拉低片选
	SPI_Write_Byte(RfAdress);//1写入地址
	SPI_Write_Byte(RfData);//2写入数据
	CS_High;//写入完成拉高片选
}

//SPI从寄存器读取数据
//参数 寄存器地址+读指令
//返回 读取到的数据
unsigned char SPI_Read_Reg(unsigned char RfAdress)
{
	unsigned char rTemp;
	CS_Low;
	SPI_Write_Byte(RfAdress);//写入地址+读取指令
	rTemp = SPI_Read_Byte();//读取数据
	CS_High;
	return rTemp;
}

//写入多个数据到寄存器
//参数1 寄存器地址+指令
//参数2 需要写入的数据地址
//参数3 写入次数
void Write_RF_Buff(unsigned char RFAdress , unsigned char *pBuff , unsigned char Len)
{
	unsigned char i;
	unsigned char rTemp;
	CS_Low;
	SPI_Write_Byte(RFAdress);
	for(i = 0 ; i < Len ; i++)
	{
		rTemp = pBuff[i];
        SPI_Write_Byte(rTemp);
	}
	CS_High;
}

//从寄存器读取多个数据
//参数1 寄存器地址+指令
//参数2 读取到的数据存放地址
//参数3 读取的次数
void Read_RF_Buff(unsigned char RFAdress , unsigned char *pBuff , unsigned char Len)
{
	unsigned char i;
	CS_Low;
	SPI_Write_Byte(RFAdress);
	for(i = 0 ; i < Len ; i++)
	{
		pBuff[i] = SPI_Read_Byte();
	}
	CS_High;
}

/*********************************************************************************************/
/***********************************  XL2400P  ***********************************************/
/*********************************************************************************************/

//射频初始化
void RF_Init(void)
{
	unsigned char RF_Init_Buff[16]={0};

	SPI_Write_Reg(W_REG+CFG_TOP,0x02);
	DelayMs(2);

    SPI_Write_Reg(W_REG+CFG_TOP,0x3E);
	DelayMs(2);
	
    /* 配置模拟寄存器 */
    Read_RF_Buff(ANALOG_CFG3 , RF_Init_Buff , 6);
	RF_Init_Buff[5] =((RF_Init_Buff[5]&0xff) | 0x6d);
	Write_RF_Buff(W_REG+ANALOG_CFG3 , RF_Init_Buff , 6);
	 
    /* 配置使能地址 */
	SPI_Write_Reg(W_REGISTER + EN_RXADDR, 0x3f);

    /* 配置地址长度 */
	SPI_Write_Reg(W_REGISTER + SETUP_AW,  0xaf);//5字节

    /* 配置重传次数和时间间隔 */
	SPI_Write_Reg(W_REGISTER + SETUP_RETR,0x33);		

    /* 配置通讯速率 */
	SPI_Write_Reg(W_REGISTER + RF_SETUP, C_DR_250K);//250Kpbs

	ACK_OFF();//不使用应答
	//ACK_ON();//使用应答

	PLOAD_X_Len();//使用动态数据长度
	//PLOAD_Fixed_Len();//使用固定长度数据

	RF_Set_Power(C_RF6dBm);//设置发射功率

	RF_Set_Address(RF_Test_Adrress);//设置RF地址

	RF_Clear_Buf();//清除状态
}


/******************** XL2400P配置函数 *****************************/

//关闭自动应答
void ACK_OFF(void)
{
	SPI_Write_Reg(W_REGISTER + EN_AA,     0x00);//不使用应答
}
//打开自动应答
void ACK_ON(void)
{
	SPI_Write_Reg(W_REGISTER + EN_AA,     0x3f);//使用应答
}

//使用动态数据长度
void PLOAD_X_Len(void)
{
	/* 配置PIPE动态长度使能位 */
	SPI_Write_Reg(W_REGISTER+DYNPD, 0x3f);//使用动态长度

//配置其他RF特性:
//bit7&6=00 发送寄存器地址时返回State
//bit5=0 非长数据包
//bit4=1 禁止FEC功能
//bit3=1 FEATURE 配置有效
//bit2=0 动态长度功能打开
//bit1=0 ACK不用带PL
//bit0=0 未开启W_TX_PAYLOAD_NOACK模式
	SPI_Write_Reg(W_REGISTER+FEATURE, 0x1c);//打开动态长度功能

}

//使用固定数据长度
void PLOAD_Fixed_Len(void)
{
	unsigned char RF_Init_Buff[3];
	/* 配置PIPE0&PIPE1接收包长度 */
	RF_Init_Buff[0] = RF_PACKET_SIZE;
	RF_Init_Buff[1] = RF_PACKET_SIZE;
	Write_RF_Buff(W_REGISTER+RX_PW_PX, RF_Init_Buff ,2);

	/* 配置PIPE动态长度使能位 */
	SPI_Write_Reg(W_REGISTER+DYNPD, 0x00);//使用固定长度

//配置其他RF特性:
//bit7&6=00 发送寄存器地址时返回State
//bit5=0 非长数据包
//bit4=1 禁止FEC功能
//bit3=1 FEATURE 配置有效
//bit2=0 动态长度功能打开
//bit1=0 ACK不用带PL
//bit0=0 未开启W_TX_PAYLOAD_NOACK模式
	SPI_Write_Reg(W_REGISTER+FEATURE, 0x18);
}

//设置频点
void RF_Set_Chn(unsigned char Chn)
{
	SPI_Write_Reg(W_REGISTER + EN_AA, 0x00);
	SPI_Write_Reg(W_REGISTER + RF_CH, Chn + 0x60);
	SPI_Write_Reg(W_REGISTER + EN_AA, 0x40);							
}

//设置地址
void RF_Set_Address(unsigned char *AddrBuff)
{
	Write_RF_Buff(W_REGISTER+TX_ADDR,AddrBuff , 5);
	Write_RF_Buff(W_REGISTER+RX_ADDR_P0, AddrBuff ,5);
}

//设置发射功率
void RF_Set_Power(unsigned char Power)
{
	unsigned char Power_Buff[3]={0};
	Read_RF_Buff(R_REGISTER+RF_SETUP , Power_Buff, 2);
	Power_Buff[1] = Power;
	Write_RF_Buff(W_REGISTER+RF_SETUP , Power_Buff ,2);
}

//设置为发射模式
void RF_Tx_Mode(void)
{
   unsigned char Mode_Buff[3]={0};
   Mode_Buff[0] = 0xee;
   Mode_Buff[1] = 0x80; 
   Write_RF_Buff(W_REG+CFG_TOP, Mode_Buff ,2);
   RF_Clear_Buf();
   DelayMs(1);
}

//设置为接收模式
void RF_Rx_Mode(void)
{
   unsigned char Mode_Buff[3]={0};
   Mode_Buff[0] = 0xee;
   Mode_Buff[1] = 0xc0; 
   Write_RF_Buff(W_REG+CFG_TOP , Mode_Buff ,2);
   RF_Clear_Buf();
   RF_CE_High();
   DelayMs(1);
}

/************************* XL2400P操作相关函数 *********************************/

//拉高RF_CE
void RF_CE_High(void)
{
	SPI_Write_Reg(W_REGISTER+CFG_TOP, 0xEF);
}

//拉低RF_CE
void RF_CE_Low(void)
{
	SPI_Write_Reg(W_REGISTER+CFG_TOP, 0xEE);
}

//清除状态
void RF_Clear_Buf(void)
{
	SPI_Write_Reg(W_REGISTER+RF_STATUS, (SPI_Read_Reg(RF_STATUS)|RX_DR | TX_DS | MAX_RT));
	SPI_Write_Reg(FLUSH_TX, CMD_NOP);
	SPI_Write_Reg(FLUSH_RX, CMD_NOP);
}

//复位RF
void RF_Reset(void)
{
   SPI_Write_Reg(W_REG+CFG_TOP,0xEA);
   DelayUs(200);
   SPI_Write_Reg(W_REG+CFG_TOP,0xEE);
   DelayMs(1);
}

//RF休眠
void RF_Sleep(void)
{
	SPI_Write_Reg(W_REGISTER+CFG_TOP, 0x00);
}


/***********************************************************************************************/
/*************************************** 跳频 **************************************************/
/***********************************************************************************************/

void RFAPIChannelNext(void)
{
	static unsigned char gChannelIndex;
	
	if(gChannelIndex < 2)
	{
	  gChannelIndex++ ;
	}
	else
	{
	  gChannelIndex = 0;
	}
	gRFChnl = CHANNELTABLE[gChannelIndex];
	RF_Set_Chn(gRFChnl);
}


void RFAPIChannelNext_RX(void)
{
	static unsigned char gChannelIndex;
	
	if(gChannelIndex < 2)
	{
	  gChannelIndex++ ;
	}
	else
	{
	  gChannelIndex = 0;
	}
	gRFChnl = CHANNELTABLE[gChannelIndex];
	gRFChnl -= 1;
	RF_Set_Chn(gRFChnl);
}

/***********************************************************************************************/
/************************************* 通讯测试 *************************************************/
/***********************************************************************************************/

//发送动态长度数据
//参数1 发送数据的地址
//参数2 发送数据的长度
unsigned char RF_Send_Data_X(unsigned char *Data_Buff , unsigned char Len)
{
	unsigned char y=200;//发送等待时间
	unsigned char RetVaule=0;//状态寄存器的值
	
    SPI_Write_Reg(FLUSH_TX, CMD_NOP);//清空TX FIFO

	Write_RF_Buff(W_TX_PLOAD,Data_Buff,Len);//填写发送内容 发送

	RF_CE_High();//拉高CE
	DelayUs(100);//延时100微妙
	RF_CE_Low();//拉低CE
	while(y--)//等待																	
	{
		DelayUs(100);//延时
		RetVaule = SPI_Read_Reg(R_REGISTER+RF_STATUS);//读取状态寄存器
		if((RetVaule&(MAX_RT|TX_DS)) != 0)	//	如果达到最大发送次数 或者 触发发送完成中断 代表发送完成								
		{
			printf("Send OK!\r\n");//打印发送完成
			break;//跳出程序
		}
	}
	return RetVaule;
}



unsigned char Rec_Buff[16]={0};//接收到的数据的缓冲区
unsigned char Data_Len=0;//接收到的数据的长度

//接收数据
unsigned char Rec_Data(void)
{
  unsigned char status;
  unsigned char RfPlwid;
	if(SPI_Read_Reg(RF_STATUS) & RX_DR)  //如果触发接收中断
	{   
		RF_CE_Low();//拉高CE
		status = SPI_Read_Reg(RF_SETUP);
		if((status & 0x0e) != 0x0e)
		{
			RfPlwid = SPI_Read_Reg(R_RX_PL_WID);
			Data_Len = RfPlwid;
			Read_RF_Buff(R_RX_PLOAD,Rec_Buff,RfPlwid); //读取有效数据
		}
		SPI_Write_Reg(FLUSH_RX, CMD_NOP);//清空RX FIFO
		SPI_Write_Reg(W_REG+RF_STATUS,(SPI_Read_Reg(RF_STATUS)|RX_DR));
		RF_CE_High();//拉高CE
		return 1;
	}
	else
	{
		return 0;
	}
}


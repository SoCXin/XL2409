#include "RF.h"
#include "RF_SPI.h"
#include "RF_Delay.h"

unsigned char    gRFChnl;

const unsigned char CHANNELTABLE[] = {05, 76, 19};//频点

unsigned char RF_Test_Adrress[5]={0xcc,0xcc,0xcc,0xcc,0xcc};//RF地址

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
	 
    /* 配置应答PIPE */
	SPI_Write_Reg(W_REGISTER + EN_AA,     0x00);//不使用应答

    /* 配置使能地址 */
	SPI_Write_Reg(W_REGISTER + EN_RXADDR, 0x3f);

    /* 配置地址长度 */
	SPI_Write_Reg(W_REGISTER + SETUP_AW,  0xaf);

    /* 配置重传次数和时间间隔 */
	SPI_Write_Reg(W_REGISTER + SETUP_RETR,0x33);		

    /* 配置通讯速率 */
	SPI_Write_Reg(W_REGISTER + RF_SETUP, C_DR_250K);//250Kpbs

    /* 配置PIPE0&PIPE1接收包长度 */
	// RF_Init_Buff[0] = RF_PACKET_SIZE;
	// RF_Init_Buff[1] = RF_PACKET_SIZE;
	// Write_RF_Buff(W_REGISTER+RX_PW_PX, RF_Init_Buff ,2);

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

	RF_Set_Power(C_RF6dBm);//设置发射功率

	RF_Set_Address(RF_Test_Adrress);//设置RF地址

	RF_Clear_Buf();//清除状态
}


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

//RF休眠
void RF_Sleep(void)
{
	SPI_Write_Reg(W_REGISTER+CFG_TOP, 0x00);
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


/******************************** 跳频 ***************************************/
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

/********************************************* 通讯测试 ***********************************************************/

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

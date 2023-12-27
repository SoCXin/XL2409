
#include "XL2400.h"
#include "USERAPP.h"	

void RF_IO_Init(void)
{
	GPIO_InitTypeDef   GPIO_InitStruct;

	__HAL_RCC_GPIOF_CLK_ENABLE();

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	
		__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
/*****************************************************************************
* 函数名称：void DelayUs(unsigned char Time)
* 功能：   us级延时
* 输入参数：Time 要延时的us
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
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

/*****************************************************************************
* 函数名称：void DelayMs(unsigned char Time)
* 功能：   Ms级延时
* 输入参数：Time 要延时的Ms
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
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

/*****************************************************************************
* 函数名称：void DelayS(unsigned char Time)
* 功能：   S级延时
* 输入参数：Time 要延时的S
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
void DelayS(unsigned char Time)
{
	unsigned char a,b;
	for(a=0;a<Time;a++)
	{
		for(b=0;b<10;b++)
		{	
		 	DelayMs(100); 
		}
	}
}

volatile uint8_t  rw_val;
uint8_t  rf_buffer[64];

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////  SPI 通信 /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

void rf_spi_reg_init(void)
{
	CS_High;
	SCK_Low;
}
/*****************************************************************************
* 函数名称：void SPI_WR(u8 buff)
* 功能：    寄存器写函数
* 输入参数：写入的字节
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
void SPI_WR(uint8_t buff)
{
	  unsigned char i;
    for(i = 0; i < 8; i++){
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
/*****************************************************************************
* 函数名称：unsigned char rf_spi_reg_init(void)
* 功能：    寄存器读函数
* 输入参数：无
* 输出参数：无
* 返回参数：读到的字节 
******************************************************************************/	
unsigned char SPI_RD(void)
{  
    unsigned char  buff = 0;
	  unsigned char  i;
    for(i = 0; i < 8; i++)
    {
        SCK_Low;
        buff = buff << 1;
        SCK_High;
        if(HAL_GPIO_ReadPin(GPIOF, SPI_MISO_GPIO_PIN))       
          buff |= 0x01;    
    }
    SCK_Low;
    return buff;
}
/*****************************************************************************
* 函数名称：uint8_t XC_Read_Buf
* 功能：    寄存器读多个字节函数
* 输入参数：无
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
uint8_t RF_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t length)
{
	  unsigned char  byte_ctr;
  	CS_Low;                    		                                    
  	SPI_WR(reg);       		                                          
  	for(byte_ctr=0;byte_ctr<length;byte_ctr++)                                
    	pBuf[byte_ctr] = SPI_RD();                                          
  	CS_High;
	return *pBuf; 
}
/*****************************************************************************
* 函数名称：void RF_Write_Buf(uint8_t reg, uint8_t   *pBuf, uint8_t len)
* 功能：    寄存器写多个字节
* 输入参数：无
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
void RF_Write_Buf(uint8_t reg, uint8_t   *pBuf, uint8_t len)
{
	  unsigned char  j;
    CS_Low;
    SPI_WR(reg);
    for(j = 0;j < len; j++)
        SPI_WR(pBuf[j]);
    CS_High;
}
/*****************************************************************************
* 函数名称：void sleep_reset(void)
* 功能：    rf休眠函数
* 输入参数：无
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
void sleep_reset(void)
{
    RF_Write_Reg(W_REG |CFG_TOP,0x00);//sleep and reset (sleep current 2.1ua,performing sleep reset rf)
}
/*****************************************************************************
* 函数名称：void RF_SetChannel(uint16_t channel)
* 功能：    工作频点设定函数
* 输入参数：无
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
void RF_SetChannel(uint16_t channel)
{
	uint8_t xc_buffer[2]={0};
  RF_Write_Reg(W_REG | EN_AA,0x3f);
	xc_buffer[0]=channel;xc_buffer[1]=channel>>8;
	RF_Write_Buf(W_REG|RF_CH,xc_buffer,2);
  RF_Write_Reg(W_REG | EN_AA,0x7f);
}
/*****************************************************************************
* 函数名称：void RF_TxPacket(uint8_t *txbuf, uint8_t len)
* 功能：    数据发射函数
* 输入参数：无
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
void RF_TxPacket(uint8_t *txbuf, uint8_t len)//r
{ 
	if(!((RF_Read_Reg(STATUS_FIFO))& TX_FULL))
	{	
		RF_Write_Buf(W_TX_PLOAD, txbuf, len);
		CE_High;
    DelayMs(1);
		CE_Low;		
	}	
}
/*****************************************************************************
* 函数名称：uint8_t RF_RxPacket(uint8_t *rxbuf)
* 功能：    数据接收函数
* 输入参数：无
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
uint8_t RF_RxPacket(uint8_t *rxbuf)//r
{
	uint8_t status, len ;
 	status=RF_Read_Reg(STATUS );  
	if((status & 0x0e) != 0x0e) {
		len=RF_Read_Reg(R_RX_PL_WID );//pipe = (status & 0xe) >> 1;
		RF_Read_Buf(R_RX_PLOAD, rxbuf, len); 
	} 
	RF_Write_Buf(W_REG | STATUS, &status,1);
	return len;
}
/*****************************************************************************
* 函数名称：void RF_Init(void)
* 功能：    RF初始化
* 输入参数：无
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
uint8_t val[6]={0xE6,0xE7,0xE7,0xE7,0xE7};
void RF_Init(void)
{ 
   //uint8_t xc_buffer[8];
	 RF_Write_Reg(W_REG |CFG_TOP,0x1a);//reset and open en_pm power_up
	 DelayMs(2);

   RF_Write_Reg(W_REG |CFG_TOP,0x3E);//release reset and open en_pm power_up
	 DelayMs(2);
	 while(1)
	 {
		 RF_Read_Reg(CFG_TOP);
		 if(rw_val == 0x3E)
			 break;
	 }
 	 RF_Write_Buf(W_REG | TX_ADDR, val, 5);
	 RF_Write_Buf(W_REG | RX_ADDR_P0,  val, 5);
	
	 RF_Read_Buf(ANALOG_CFG3,val,6);
	 val[5] =((val[5]&0xff) | 0x6d);
	 RF_Write_Buf(W_REG |ANALOG_CFG3,val,6);
	
   RF_Write_Reg(W_REG |RX_PW_PX,BUFF_LENGTH); 
	 rf_buffer[0]= TRANS_RATE;rf_buffer[1]= POWER_LEVEL;
   RF_Write_Buf(W_REG |SETUP_RF,  rf_buffer, 2);
#ifdef RF_TX_MODE    
	 val[0] = 0xee; val[1]=0x80; 
   RF_Write_Buf(W_REG | CFG_TOP,  val,2); 
#else
	 val[0] = 0xee; val[1]=0xc0; 
   RF_Write_Buf(W_REG | CFG_TOP,  val,2); 	
#endif
  RF_Write_Reg(W_REG | STATUS,(RF_Read_Reg(STATUS)|XC_RX_DR | XC_TX_DS | XC_MAX_RT));
	RF_Write_Reg(FLUSH_TX, CMD_NOP);
	RF_Write_Reg(FLUSH_RX, CMD_NOP);
}

/*****************************************************************************
* 函数名称：void rf_tx_test(void)
* 功能：    发射测试接口
* 输入参数：无
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
void rf_tx_test(void)
{
	uint8_t count=0; 
	uint8_t idx;
	RF_SetChannel(CHANNEL_XL2400);//设置为xxx信道
	for (idx=0; idx<32; idx++)  rf_buffer[idx] = idx;//填写发包内容，  
    CE_High;
	while(1)
	{             
		rf_buffer[0]=count++;
		RF_Write_Reg(FLUSH_TX, CMD_NOP);  //清除发送FIFO	
 		RF_TxPacket(rf_buffer, BUFF_LENGTH);//发包
		if((RF_Read_Reg(STATUS)&0x20))
		{			
			RF_Write_Reg(W_REG | STATUS,(RF_Read_Reg(STATUS)|XC_TX_DS));    
		}
		DelayMs(5);		
   }   
}
/*****************************************************************************
* 函数名称：void rf_rx_test(void)
* 功能：    接收测试接口
* 输入参数：无
* 输出参数：无
* 返回参数：无 
******************************************************************************/	
void rf_rx_test(void)
{
	uint8_t packet_len=0;	 
	RF_SetChannel(CHANNEL_XL2400-1);//设置为xxx信道
  CE_High;
	
	while(1)
	{ 
		if(RF_Read_Reg(STATUS) & XC_RX_DR)  
		{   
			CE_Low;
			packet_len = RF_RxPacket(rf_buffer);//接收无线数据
			RF_Write_Reg(FLUSH_RX, CMD_NOP);
			RF_Write_Reg(W_REG | STATUS,(RF_Read_Reg(STATUS)|XC_RX_DR));
			if(packet_len)
			{				
				packet_len = 0;
			}
			CE_High;
		} 
	}  
}

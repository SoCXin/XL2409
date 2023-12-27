#include "RF_SPI.h"

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
    for(unsigned char i = 0; i < 8; i++)
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
    unsigned char  buff = 0;

    for(unsigned char i = 0; i < 8; i++)
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
	unsigned char rTemp;
	CS_Low;
	SPI_Write_Byte(RFAdress);
	for(unsigned char i = 0 ; i < Len ; i++)
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
	CS_Low;
	SPI_Write_Byte(RFAdress);
	for(unsigned char i = 0 ; i < Len ; i++)
	{
		pBuff[i] = SPI_Read_Byte();
	}
	CS_High;
}







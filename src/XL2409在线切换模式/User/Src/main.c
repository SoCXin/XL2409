#include "main.h"
#include "User_System_Clock.h"
#include "XL2400P.h"


#include "User_UART1.h"
#include "User_Timer14.h"

void User_UAER_Rec_RF_Send(void);
void NoSignalHandler(void);
void User_RF_Rec(void);

uint8_t RF_STAT=0;//RF切换标志

int main(void)
{
	HAL_Init();           //HAL库初始化
	System_Clock_Init();  //系统时钟配置 HSI 24MHZ
	User_USART1_Init(115200);   //串口初始化 波特率115200
	printf("hello\r\n");  //打印测试
	User_TIM14_Init();    //定时器14初始化
	/***************** XL2400P **********************/
	RF_GPIO_Init();       //引脚初始化
	RF_SPI_Init();        //SPI通讯初始化
	RF_Init();            //RF初始化
	/************************************************/
	RF_Tx_Mode();//设置为发射模式

	while(1) 
	{
		User_UAER_Rec_RF_Send();
		User_RF_Rec();
	}
}



void User_UAER_Rec_RF_Send(void)
{
	if(UART1RecFlag == 1)//如果串口接收完成数据 发生空闲中断
	{
		uint16_t len =  strlen( (char *)UART1RecBuffer);//获取接收缓冲区的长度
		uint8_t sendcount = 4;//重传次数
		while( sendcount --)
		{
			RF_Reset();
			RFAPIChannelNext();
			RF_Send_Data_X(UART1RecBuffer,len);
		}
		UART1_Count=0;
		memset(UART1RecBuffer , 0 ,len);//清空接收缓冲区
		UART1RecFlag =0;

		RF_Rx_Mode();//切换为接收模式
		RF_STAT=1;
	}
}

void User_RF_Rec(void)
{
	if( RF_STAT ==1)
	{
		if(Rec_Data() == 1)
		{
			printf("Receive Data is:\r\n");
			for(uint8_t i=0;i<Data_Len;i++)
			{
				printf("%c",Rec_Buff[i]);
			}
			printf("\r\n");
		}
		else
		{
			NoSignalHandler();
		}
	}
}


void NoSignalHandler(void)
{
	if(gTmrCnt > 40)
	{
		gTmrCnt = 0;
		RF_Reset();
		RF_CE_High();
		RFAPIChannelNext_RX();
	}
}


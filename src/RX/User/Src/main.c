#include "main.h"
#include "LED.h"
#include "System_Clock_Config.h"
#include "Usart1.h"

#include "User_Timer.h"
#include "RF_SPI.h"
#include "RF.h"

void NoSignalHandler(void);

int main(void)
{
	HAL_Init();//HAL库初始化
	System_Clock_Config();//配置MUC时钟到24Mhz
	
	USART1_Config();//串口初始化
	printf("hello\r\n");//打印测试

    //User_LED();
	User_TIM14_Config();
	/*RF*/
	RF_GPIO_Init();//射频引脚初始化
    RF_SPI_Init();//射频SPI通讯初始化
	RF_Init(); //射频初始化
	HAL_Delay(200);


	RF_Rx_Mode();//设置为接收模式
	while(1) 
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

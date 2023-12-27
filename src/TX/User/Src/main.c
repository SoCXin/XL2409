#include "main.h"
#include "LED.h"
#include "System_Clock_Config.h"
#include "Usart1.h"
#include "RF_SPI.h"
#include "RF.h"

int main(void)
{
	HAL_Init();//HAL库初始化
	System_Clock_Config();//配置MUC时钟到24Mhz
	
	USART1_Config();//串口初始化
	printf("hello\r\n");//打印测试

    User_LED();
	/*RF*/
	RF_GPIO_Init();//射频引脚初始化
    RF_SPI_Init();//射频SPI通讯初始化
	RF_Init(); //射频初始化
	HAL_Delay(200);

	RF_Tx_Mode();//设置为发射模式

	uint8_t Len=0;//串口接收到的数据的长度
	while(1) 
	{	
		if(USART_RX_STA & 0x8000 )//如果接收数据完成
		{
			
			Len = USART_RX_STA & 0x3fff;//计算出接收到的数据长度

			uint8_t aa =4;//循环发送次数
			while (aa--)
			{
				RF_Reset();//复位RF
				RFAPIChannelNext();//跳频
				RF_Send_Data_X(USART_RX_BUF,Len);//发送数据
			}
			/*打印接收到的数据*/
			printf("Input Data:\r\n");
			for(uint8_t i = 0 ; i < Len ; i++)
			{
				printf("%c",USART_RX_BUF[i]);
			} 
			printf("\r\n");
			USART_RX_STA = 0;//清零准备下一次接收数据
		}

	}

}





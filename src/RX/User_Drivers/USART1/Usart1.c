/***************************************
 * 串口引脚定义：
 * USART1_TX---->PA2
 * USART1_RX---->PA3
****************************************/
#include "Usart1.h"

UART_HandleTypeDef USART1_Handle;//USART1句柄

uint8_t aRxBuffer[1];//串口接收的数据临时缓冲区
uint16_t USART_RX_STA=0;//接收状态标记 一共16位
uint8_t USART_RX_BUF[USART_REC_LEN];//存放接收的数据 最大200字节


//USART1参数配置
void USART1_Config(void)
{
  /*使能时钟*/
  __HAL_RCC_GPIOA_CLK_ENABLE();  //开启GPIOA模块时钟
  __HAL_RCC_USART1_CLK_ENABLE(); //开启USART1模块时钟

  /*配置GPIO参数*/
  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Pin       = GPIO_PIN_2|GPIO_PIN_3;     //PA2|PA3
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;           //推免复用
  GPIO_InitStruct.Pull      = GPIO_PULLUP;               //上拉模式
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH; //超高速模式
  GPIO_InitStruct.Alternate = GPIO_AF1_USART1;           //连接到USART1

  HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);//根据GPIO结构体初始化引脚
  /*配置USART1参数*/
  USART1_Handle.Instance        = USART1;              //串口基地址为USART1
  USART1_Handle.Init.BaudRate   = 115200;              //波特率设置为115200
  USART1_Handle.Init.WordLength = UART_WORDLENGTH_8B;  //数据位
  USART1_Handle.Init.StopBits   = UART_STOPBITS_1;     //停止位
  USART1_Handle.Init.Parity     = UART_PARITY_NONE;    //无校验
  USART1_Handle.Init.Mode       = UART_MODE_TX_RX;     //工作模式选择发送与接收
  USART1_Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE; //无硬件控制流
  
  HAL_UART_Init(&USART1_Handle);//根据结构体配置初始化USART1

  /* 使能NVIC */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  /*通过中断接收数据 接收的数据存放到aRXBuffer 每次接收1字节*/  
  HAL_UART_Receive_IT(&USART1_Handle, (uint8_t *)aRxBuffer, 1);
}

//重定向printf
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&USART1_Handle, (uint8_t *)&ch, 1, 0xffff);//通过USART1发送数据
  return ch;
}

//串口1中断服务函数
void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&USART1_Handle);//调用HAL库中断处理公共函数

  /*HAL_UART_IRQHandler()会清除中断 需要重新开启*/

  /*重新开启中断接收*/
  HAL_UART_Receive_IT(&USART1_Handle, (uint8_t *)aRxBuffer, 1);
} 

//接收完成回调函数
//0x0A 换行 Bit15
//0x0D 回车 Bit14
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART1)
  {

    if((USART_RX_STA & 0x8000) == 0)//接收未完成
    {

        if(USART_RX_STA & 0x4000)//接收到了回车
        {

            if(aRxBuffer[0] != 0x0a)//接收到的不是换行
            {
              USART_RX_STA=0;//接收错误,重新开始
            }
            else//接收到的是回车
            {
              USART_RX_STA |= 0x8000;	//接收完成
            } 
    
        }
        else //还没收到回车
        {

            if(aRxBuffer[0]==0x0d)//接收到了回车
            {
                USART_RX_STA |= 0x4000;//Bit14置1
            }
            else//还没接收到回车
            {
                USART_RX_BUF[USART_RX_STA & 0X3FFF]=aRxBuffer[0] ;
                USART_RX_STA++;
                if(USART_RX_STA>(USART_REC_LEN-1))
                {
                  USART_RX_STA=0;//接收数据错误,重新开始接收
                }	  
            }		 
        }

    }
  }
  
}








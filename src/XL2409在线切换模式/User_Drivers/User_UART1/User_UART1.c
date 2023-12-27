/***************************************
 * 串口引脚定义：
 * USART1_TX---->PA2
 * USART1_RX---->PA3
****************************************/
#include "User_UART1.h"

UART_HandleTypeDef USART1_Handle;//串口句柄

uint8_t UART1RecBuffer[16];//接收数据缓冲区
uint8_t UART1_Count=0;//串口接收数据计数
uint8_t UART1RecFlag=0;//空闲中断标志 也可以理解为接收完成标志

//串口1中断函数
void USART1_IRQHandler(void)
{
    if( (USART1->SR & (1<<5)) != 0)//产生接收中断 //这里不能使用==1 不知道为什么 有知道的告诉我一下！！！！！！！！
    {
        UART1RecBuffer[UART1_Count]= (uint8_t)USART1->DR;//将数据寄存器的值转移
        UART1_Count++;
		USART1->SR &= ~(1<<5);//清除中断标志位
    }
    if( (USART1->SR & (1<<4)) !=0)//产生空闲中断  //这里不能使用==1 不知道为什么 有知道的告诉我一下！！！！！！！！
    {
        UART1RecFlag=1;//接收完成标志置1
        /*清除中断标志位*/
        USART1->SR;
        USART1->DR;
    }
}


//串口接收一个字节
//如果使能中断 此函数有阻塞功能 
uint8_t UART1_Rec_Byte(void)
{
    uint8_t str;
	  while( (USART1->SR&(1<<5)) ==0);//等待接收数据 如果没接收到数据会一直卡在这里
    str = (uint8_t)USART1->DR;//读取数据寄存器
    return str;
}


//串口发送一个字节
void UART1_Send_Byte(uint8_t dat)
{
    USART1->DR = dat;//将内容写入DR寄存器
	  while((USART1->SR &(1<<6))==0);//等待上一个字节发送完成
    /*关于发送数据的写法待验证 目前发现只有PY的芯片while要写在后面*/
}

//重定向fputc
int fputc(int ch , FILE *f)
{
    UART1_Send_Byte(ch);
    return ch;
}

//USART1参数配置
void User_USART1_Init(uint32_t baud)
{

  /*配置USART1参数*/
  USART1_Handle.Instance        = USART1;              //串口基地址为USART1
  USART1_Handle.Init.BaudRate   = baud;              //波特率设置为115200
  USART1_Handle.Init.WordLength = UART_WORDLENGTH_8B;  //数据位
  USART1_Handle.Init.StopBits   = UART_STOPBITS_1;     //停止位
  USART1_Handle.Init.Parity     = UART_PARITY_NONE;    //无校验
  USART1_Handle.Init.Mode       = UART_MODE_TX_RX;     //工作模式选择发送与接收
  USART1_Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE; //无硬件控制流
  
  HAL_UART_Init(&USART1_Handle);//根据结构体配置初始化USART1

  USART1->CR1 |= (1<<2);//接收使能
  USART1->CR1 |= (1<<3);//发送使能

  USART1->CR1 |= (1<<5);//接收中断使能
  USART1->CR1 |= (1<<4);//空闲中断使能

  //USART1->CR1 |= (1<<6);//发送中断使能

  USART1->CR1 |= (1<<13);//串口使能

  /* 使能NVIC */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(USART1_IRQn);

}


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART1)
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

  }
}








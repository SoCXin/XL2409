#include "bsp_uart.h"
#include "bsp_tim3.h"
#include <string.h>

UART_HandleTypeDef UartHandle;   //定义串口结构体
UART_PARAM_STRUCT Uart1Data = {0};

void UART_Init(void)										 //串口初始化设置
{
    GPIO_InitTypeDef  GPIO_InitStruct;     //定义串口所用GPIO

    __HAL_RCC_USART2_CLK_ENABLE();         //开启串口时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();					 //开启GPIO时钟

    /*串口参数设置*/
    UartHandle.Instance          = USART2;
    UartHandle.Init.BaudRate     = 115200;
    UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits     = UART_STOPBITS_1;
    UartHandle.Init.Parity       = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode         = UART_MODE_TX_RX;

    HAL_UART_Init(&UartHandle);


    /*GPIO参数设置*/
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(USART2_IRQn, 0, 1);  //配置中断优先级
    HAL_NVIC_EnableIRQ(USART2_IRQn);          //配置NVIC串口中断

    //__HAL_UART_ENABLE_IT(&UartHandle, UART_IT_RXNE);  //使能串口接收中断
}


int fputc(int ch, FILE *f) 	 						//重定向，为了用printf
{
    /* Send a byte to USART */
    HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 1000);

    return (ch);
}


/********************************************************************************************************
**函数信息 ：void USART1_IRQHandler(void)
**功能描述 ：USART1 串口中断处理函数
**输入参数 ：
**输出参数 ：
**    备注 ：
********************************************************************************************************/
void USART1_IRQHandler(void)						//串口接收中断响应函数，接收不定长数据
{
    if(__HAL_UART_GET_FLAG(&UartHandle, USART_CR1_RXNEIE))// 如果接收到一个字节  USART_CR1_RXNEIE
    {
        __HAL_UART_CLEAR_FLAG(&UartHandle, USART_CR1_RXNEIE);
    }

    int ch;
    uint32_t isrflags   = READ_REG(UartHandle.Instance->SR);
    uint32_t cr1its     = READ_REG(UartHandle.Instance->CR1);

    /* UART in mode Receiver -------------------------------------------------*/
    if (((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
    {
        __HAL_UART_CLEAR_FLAG(&UartHandle, USART_SR_RXNE);

        ch = USART1->DR;
        if( Uart1Data.RxLen > 0 && 0 == Uart1Data.RxTimer )
        {
            return;
        }
        if( Uart1Data.RxLen < UART_BUF_SIZE )
        {
            Uart1Data.RxBuf[Uart1Data.RxLen ++ ] = ch;
            Uart1Data.RxTimer = UART_RX_OVERTIME;
        }
    }

    if (((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
    {
        __HAL_UART_CLEAR_FLAG(&UartHandle, USART_SR_TXE);
    }
}


/********************************************************************************************************
**函数信息 ：void USART2_IRQHandler(void)
**功能描述 ：USART2 串口中断处理函数
**输入参数 ：
**输出参数 ：
**    备注 ：
********************************************************************************************************/
void USART2_IRQHandler(void)						//串口接收中断响应函数，接收不定长数据
{
    if(__HAL_UART_GET_FLAG(&UartHandle, USART_CR1_RXNEIE))// 如果接收到一个字节  USART_CR1_RXNEIE
    {
        __HAL_UART_CLEAR_FLAG(&UartHandle, USART_CR1_RXNEIE);
    }

    int ch;
    uint32_t isrflags   = READ_REG(UartHandle.Instance->SR);
    uint32_t cr1its     = READ_REG(UartHandle.Instance->CR1);

    /* UART in mode Receiver -------------------------------------------------*/
    if (((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
    {
        __HAL_UART_CLEAR_FLAG(&UartHandle, USART_SR_RXNE);

        ch = USART1->DR;
        if( Uart1Data.RxLen > 0 && 0 == Uart1Data.RxTimer )
        {
            return;
        }
        if( Uart1Data.RxLen < UART_BUF_SIZE )
        {
            Uart1Data.RxBuf[Uart1Data.RxLen ++ ] = ch;
            Uart1Data.RxTimer = UART_RX_OVERTIME;
        }
    }

    if (((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
    {
        __HAL_UART_CLEAR_FLAG(&UartHandle, USART_SR_TXE);
    }
}

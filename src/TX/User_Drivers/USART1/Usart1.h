#ifndef _USART1_H
#define _USART1_H

#include "main.h"

#define RXBUFFERSIZE   1    //缓存大小
#define USART_REC_LEN  32 //定义最大接收字节数 32

extern UART_HandleTypeDef USART1_Handle;//USART1句柄
extern uint8_t aRxBuffer[1];
extern uint16_t USART_RX_STA;//接收状态标记 一共16位
extern uint8_t USART_RX_BUF[USART_REC_LEN];//存放接收的数据 最大32字节


void USART1_Config(void);


#endif



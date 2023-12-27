#ifndef USER_UART1_H
#define USER_UART1_H

#include "main.h"

extern uint8_t UART1RecBuffer[16];//接收数据缓冲区
extern uint8_t UART1_Count;
extern uint8_t UART1RecFlag;//空闲中断标志 也可以理解为接收完成标志

void User_USART1_Init(uint32_t baud);



#endif



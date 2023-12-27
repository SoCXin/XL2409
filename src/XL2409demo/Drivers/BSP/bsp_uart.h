#ifndef __BSP_UART_H
#define __BSP_UART_H

#include "main.h"
#include "sip_mcu_hal.h"


#define UART_BUF_SIZE				256
#define UART_RX_OVERTIME	  15
void UART_Init(void);

typedef struct
{
    uint16_t TxCount;
    uint16_t RxTimer;
    uint16_t TxLen;
    uint16_t RxLen;
    uint8_t  TxBuf[UART_BUF_SIZE];
    uint8_t  RxBuf[UART_BUF_SIZE];
} UART_PARAM_STRUCT;

#endif

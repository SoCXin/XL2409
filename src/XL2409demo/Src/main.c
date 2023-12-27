#include "main.h"
#include "bsp_system.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_tim3.h"
#include "bsp_rf.h"
#include "bsp_expand.h"
#include "bsp_encode.h"
#include "bsp_keyslisten.h"
#include <math.h>
#include "bsp_pins.h"
#include "bsp_flash.h"
#include "bsp_iwdg.h"
#include "bsp_uart.h"
#include "bsp_state_machine.h"
#include "XL2400.h"
#include "USERAPP.h"	

uint8_t aRxBuffer[128] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
extern UART_HandleTypeDef UartHandle;
//extern void usart1DataProcess();

int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    SystemClock_Config();
		RF_IO_Init();
		rf_spi_reg_init(); 
		RF_Init(); 
	
#ifdef RF_TX_MODE
		printf("/******send device***********/\r\n");
		rf_tx_test();
#else 
		printf("/******recv device***********/\r\n");
		rf_rx_test();
#endif     
}




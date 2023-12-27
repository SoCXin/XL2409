#ifndef __BSP_KEY_H
#define __BSP_KEY_H


#include "sip_mcu_hal.h"


#define KEY_ON     1
#define KEY_OFF 	 0

#define SEND_KEY3_GPIO_PORT     GPIOA
#define SEND_KEY3_GPIO_PIN      GPIO_PIN_12

#define FUN_KEY2_GPIO_PORT     GPIOB
#define FUN_KEY2_GPIO_PIN      GPIO_PIN_3

#define KEY1_GPIO_PORT     GPIOB
#define KEY1_GPIO_PIN      GPIO_PIN_5

#define KEY2_GPIO_PORT     GPIOB
#define KEY2_GPIO_PIN      GPIO_PIN_6

#define KEY3_GPIO_PORT     GPIOB
#define KEY3_GPIO_PIN      GPIO_PIN_7

#define KEY4_GPIO_PORT     GPIOA
#define KEY4_GPIO_PIN      GPIO_PIN_0

void KEY_Init(void);
void KEYS_Init(void);
uint8_t KEY_SCAN(GPIO_TypeDef *GPIOx, uint16_t Pin);


#endif

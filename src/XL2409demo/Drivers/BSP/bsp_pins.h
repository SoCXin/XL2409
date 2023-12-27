#ifndef __BSP_PINS_H
#define __BSP_PINS_H

#include "sip_mcu_hal.h"



#define PINS1_PORT     GPIOB
#define PINS1_PIN      GPIO_PIN_5

#define PINS2_PORT     GPIOB
#define PINS2_PIN      GPIO_PIN_6

#define PINS3_PORT     GPIOB
#define PINS3_PIN      GPIO_PIN_7

#define PINS4_PORT     GPIOA
#define PINS4_PIN      GPIO_PIN_0

void Pins_Init(void);  //���ų�ʼ��
void Pins_Ctrl(void); //����ģʽ��������


#endif

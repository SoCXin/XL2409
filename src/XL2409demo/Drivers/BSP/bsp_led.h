#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "sip_mcu_hal.h"


#define LED1_PORT   GPIOB
#define LED1_PIN	GPIO_PIN_7  //white

#define LED2_PORT   GPIOB
#define LED2_PIN	GPIO_PIN_6  //red

#define LED3_PORT   GPIOB
#define LED3_PIN	GPIO_PIN_5  //green

void LED_Init(void);
void GREEN_LED_Init(void);
void LedOn(GPIO_TypeDef *GPIOx, uint16_t Pin);  //����
void LedOff(GPIO_TypeDef *GPIOx, uint16_t Pin);  //�ص�
void LedToggle(GPIO_TypeDef *GPIOx, uint16_t Pin);  //��ת
void LedCount(GPIO_TypeDef *GPIOx, uint16_t Pin, uint16_t Count);	 //���ƴ���
void LedBlinkCase(void);  //Led��˸����ʱ�����ƣ�

#endif

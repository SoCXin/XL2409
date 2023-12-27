#ifndef __BSP_TIM3_H
#define __BSP_TIM3_H

#include "sip_mcu_hal.h"


void TIM3_Init(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void Clear_Tim(void);
void Tim_On(void);

extern uint16_t tim_rfsend;
extern uint16_t tim_led1;
extern uint16_t tim_led2;
extern uint16_t tim_count1;

#endif

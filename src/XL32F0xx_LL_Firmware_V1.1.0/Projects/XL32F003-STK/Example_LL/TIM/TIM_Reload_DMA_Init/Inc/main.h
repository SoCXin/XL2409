/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "xl32f0xx_ll_rcc.h"
#include "xl32f0xx_ll_bus.h"
#include "xl32f0xx_ll_system.h"
#include "xl32f0xx_ll_exti.h"
#include "xl32f0xx_ll_cortex.h"
#include "xl32f0xx_ll_utils.h"
#include "xl32f0xx_ll_pwr.h"
#include "xl32f0xx_ll_dma.h"
#include "xl32f0xx_ll_gpio.h"
#include "xl32f0xx_ll_tim.h"
	
#if defined(USE_FULL_ASSERT)
#include "xl32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void APP_UpdateCallback(void);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT Xinling *****END OF FILE****/

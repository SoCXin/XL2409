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
#include "xl32f0xx_ll_i2c.h"

#if defined(USE_FULL_ASSERT)
#include "xl32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define SLAVE_OWN_ADDRESS                       0x5A /* 从机地址 */
#define I2C_REQUEST_WRITE                       0x00 /* 方向位：写 */
#define I2C_REQUEST_READ                        0x01  /* 方向位：读 */

/* 取消注释此行以将板用作从板，否则将其用作主板 */
#define SLAVE_BOARD

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT Xinling *****END OF FILE****/

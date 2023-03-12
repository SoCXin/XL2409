/**
  ******************************************************************************
  * @file    xl32f0xx_hal_led.h
  * @author  MCU Application Team
  * @brief   Header file of LED HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Xinling Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software is owned and published by:
  * Xinling Semiconductor Co., Ltd.
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are met:
  *
  *  1. Redistributions of source code must retain the above copyright notice,
  *     this list of conditions and the following disclaimer.
  *  2. Redistributions in binary form must reproduce the above copyright notice,
  *     this list of conditions and the following disclaimer in the documentation
  *     and/or other materials provided with the distribution.
  *  3. Neither the name of the copyright holder nor the names of its contributors
  *     may be used to endorse or promote products derived from this software
  *     without specific prior written permission.
  *
  *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  *  POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#ifndef __XL32F0xx_HAL_LED_H
#define __XL32F0xx_HAL_LED_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "xl32f0xx_hal_def.h"



/**
  * @brief LED Init Structure definition
  */
typedef struct
{
  uint32_t ComDrive;          /*!< Specifies the LED COM drive capability.
                                     This parameter can be a value of @ref LED_COMDrive */

  uint32_t Prescaler;         /*!< Specifies the prescaler value used to divide the LED clock.
                                     This parameter can be a number between Min_Data = 0x00(div1) and Max_Data = 0xFF(div256) */

  uint32_t ComNum;            /*!< Specifies the number of COM open.
                                     This parameter can be a number between Min_Data = 0(1COM) and Max_Data = 3(4COM) */

  uint32_t LightTime;         /*!< Specifies LED Lighting time.
                                     This parameter can be a number between Min_Data = 1 and Max_Data = 0xFF */

  uint32_t DeadTime;          /*!< Specifies LED Dead time.
                                     This parameter can be a number between Min_Data = 1 and Max_Data = 0xFF */

} LED_InitTypeDef;

/** 
  * @brief HAL LED State structures definition
  */ 
typedef enum
{
  HAL_LED_STATE_RESET             = 0x00U,    /*!< Peripheral is not yet Initialized */
  HAL_LED_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use */
  HAL_LED_STATE_BUSY              = 0x02U,    /*!< an internal process is ongoing */
  HAL_LED_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state */
  HAL_LED_STATE_ERROR             = 0x04U     /*!< Error */
}HAL_LED_StateTypeDef;

#if (USE_HAL_LED_REGISTER_CALLBACKS == 1)
typedef struct __LED_HandleTypeDef
#else
typedef struct
#endif
{
  LED_TypeDef                   *Instance;

  LED_InitTypeDef               Init;

  HAL_LockTypeDef               Lock;        /* Locking object */

  __IO HAL_LED_StateTypeDef     State;       /* LED communication state */

#if (USE_HAL_LED_REGISTER_CALLBACKS == 1)
  void (* MspInitCallback)(struct __LED_HandleTypeDef *hled);

  void (* LightComplateCallback)(struct __LED_HandleTypeDef *hled);
#endif
} LED_HandleTypeDef;

#define __HAL_LED_ENABLE(__HANDLE__)                  SET_BIT((__HANDLE__)->Instance->CR, LED_CR_LEDON)

/** @brief  Disable the specified LED peripheral.
  * @param  __HANDLE__ specifies the LED Handle.
  * @retval None
  */
#define __HAL_LED_DISABLE(__HANDLE__)                 CLEAR_BIT((__HANDLE__)->Instance->CR, LED_CR_LEDON)

#define __HAL_LED_CLEAR_FLAG(__HANDLE__, __FLAG__)    ((__HANDLE__)->Instance->IR = (__FLAG__))

#define __HAL_LED_ENABLE_IT(__HANDLE__, __INTERRUPT__)       SET_BIT((__HANDLE__)->Instance->CR, (__INTERRUPT__))

/** @defgroup LED_Display_Value  LED display value
  * @{
  */
#define LED_DISP_NONE     0x00
#define LED_DISP_FULL     0xFF

#define LED_DISP_0        0x3F
#define LED_DISP_1        0x06
#define LED_DISP_2        0x5B
#define LED_DISP_3        0x4F
#define LED_DISP_4        0x66
#define LED_DISP_5        0x6D
#define LED_DISP_6        0x7D
#define LED_DISP_7        0x07
#define LED_DISP_8        0x7F
#define LED_DISP_9        0x6F
#define LED_DISP_A        0x77
#define LED_DISP_B        0x7C
#define LED_DISP_C        0x39
#define LED_DISP_D        0x5E
#define LED_DISP_E        0x79
#define LED_DISP_F        0x71
#define LED_DISP_H        0x76
#define LED_DISP_P        0x73
#define LED_DISP_U        0x3E
#define LED_DISP_DOT      0x80
/**
  * @}
  */

/** @defgroup LED_COM_Select  LED COM Select
  * @{
  */
#define LED_COM0          (0x01<<0)
#define LED_COM1          (0x01<<1)
#define LED_COM2          (0x01<<2)
#define LED_COM3          (0x01<<3)
#define LED_COM_ALL       (LED_COM0 | LED_COM1 | LED_COM2 | LED_COM3)
/**
  * @}
  */

/** @defgroup LED_COMDrive  LED COM Drive
  * @{
  */
#define LED_COMDRIVE_LOW          0
#define LED_COMDRIVE_HIGH         LED_CR_EHS
/**
  * @}
  */


/** @defgroup LED_Exported_Functions_Group LED operation functions
 *  @brief    LED operation functions
 * @{
 */

/* LED operation functions *****************************************************/
HAL_StatusTypeDef HAL_LED_Init(LED_HandleTypeDef *hled);
void HAL_LED_MspInit(LED_HandleTypeDef *hled);
HAL_StatusTypeDef HAL_LED_SetComDisplay(LED_HandleTypeDef *hled, uint8_t comCh, uint8_t data);
void HAL_LED_LightCpltCallback(LED_HandleTypeDef *hled);
void HAL_LED_IRQHandler(LED_HandleTypeDef *hled);

/**
  * @}
  */

#endif

/**
  ******************************************************************************
  * @file    xl32f0xx_ll_system.h
  * @author  MCU Application Team
  * @brief   Header file of SYSTEM LL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef XL32F0XX_LL_SYSTEM_H
#define XL32F0XX_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "xl32f0xx.h"

/** @addtogroup XL32F0XX_LL_Driver
  * @{
  */

#if defined (FLASH) || defined (SYSCFG) || defined (DBGMCU)

/** @defgroup SYSTEM_LL SYSTEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Private_Constants SYSTEM Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup SYSTEM_LL_EC_REMAP SYSCFG REMAP
  * @{
  */
#define LL_SYSCFG_REMAP_FLASH               0x00000000U                                           /*!< Main Flash memory mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_SYSTEMFLASH         SYSCFG_CFGR1_MEM_MODE_0                               /*!< System Flash memory mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_SRAM                (SYSCFG_CFGR1_MEM_MODE_1 | SYSCFG_CFGR1_MEM_MODE_0)   /*!< Embedded SRAM mapped at 0x00000000 */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_I2C_ANF I2C ANALOG FILTER ENABLE CONTORL
  * @{
  */
#define LL_SYSCFG_I2C_ANF_PA2                SYSCFG_CFGR1_I2C_PA2_ANF
#define LL_SYSCFG_I2C_ANF_PA3                SYSCFG_CFGR1_I2C_PA3_ANF
#define LL_SYSCFG_I2C_ANF_PA7                SYSCFG_CFGR1_I2C_PA7_ANF
#define LL_SYSCFG_I2C_ANF_PA8                SYSCFG_CFGR1_I2C_PA8_ANF
#define LL_SYSCFG_I2C_ANF_PA9                SYSCFG_CFGR1_I2C_PA9_ANF
#define LL_SYSCFG_I2C_ANF_PA10               SYSCFG_CFGR1_I2C_PA10_ANF
#define LL_SYSCFG_I2C_ANF_PA11               SYSCFG_CFGR1_I2C_PA11_ANF
#define LL_SYSCFG_I2C_ANF_PA12               SYSCFG_CFGR1_I2C_PA12_ANF
#define LL_SYSCFG_I2C_ANF_PB6                SYSCFG_CFGR1_I2C_PB6_ANF
#define LL_SYSCFG_I2C_ANF_PB7                SYSCFG_CFGR1_I2C_PB7_ANF
#define LL_SYSCFG_I2C_ANF_PB8                SYSCFG_CFGR1_I2C_PB8_ANF
#define LL_SYSCFG_I2C_ANF_PF0                SYSCFG_CFGR1_I2C_PF0_ANF
#define LL_SYSCFG_I2C_ANF_PF1                SYSCFG_CFGR1_I2C_PF1_ANF
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TIMBREAK TIMER BREAK INPUT
  * @{
  */
#define LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL      SYSCFG_CFGR2_LOCKUP_LOCK
#define LL_SYSCFG_TIMBREAK_PVD_TO_ALL         SYSCFG_CFGR2_PVD_LOCK
#define LL_SYSCFG_TIMBREAK_COMP1_TO_TIM1      SYSCFG_CFGR2_COMP1_BRK_TIM1
#define LL_SYSCFG_TIMBREAK_COMP2_TO_TIM1      SYSCFG_CFGR2_COMP2_BRK_TIM1
#define LL_SYSCFG_TIMBREAK_COMP1_TO_TIM16     SYSCFG_CFGR2_COMP1_BRK_TIM16
#define LL_SYSCFG_TIMBREAK_COMP2_TO_TIM16     SYSCFG_CFGR2_COMP2_BRK_TIM16
#define LL_SYSCFG_TIMBREAK_COMP1_TO_TIM17     SYSCFG_CFGR2_COMP1_BRK_TIM17
#define LL_SYSCFG_TIMBREAK_COMP2_TO_TIM17     SYSCFG_CFGR2_COMP2_BRK_TIM17
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_ETR_SRC ETR SOURCE
  */
#define LL_SYSCFG_ETR_SRC_TIM1_GPIO          0x00000000U
#define LL_SYSCFG_ETR_SRC_TIM1_COMP1         SYSCFG_CFGR2_ETR_SRC_TIM1_0
#define LL_SYSCFG_ETR_SRC_TIM1_COMP2         SYSCFG_CFGR2_ETR_SRC_TIM1_1
#define LL_SYSCFG_ETR_SRC_TIM1_ADC           (SYSCFG_CFGR2_ETR_SRC_TIM1_1 | SYSCFG_CFGR2_ETR_SRC_TIM1_0)
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DMA_MAP DMA MAP
  */
#define LL_SYSCFG_DMA_MAP_ADC               0x00000000U
#define LL_SYSCFG_DMA_MAP_SPI1_TX           SYSCFG_CFGR3_DMA1_MAP_0
#define LL_SYSCFG_DMA_MAP_SPI1_RX           SYSCFG_CFGR3_DMA1_MAP_1
#define LL_SYSCFG_DMA_MAP_SPI2_TX           (SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_SPI2_RX           SYSCFG_CFGR3_DMA1_MAP_2
#define LL_SYSCFG_DMA_MAP_USART1_TX         (SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_USART1_RX         (SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1)
#define LL_SYSCFG_DMA_MAP_USART2_TX         (SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_USART2_RX         SYSCFG_CFGR3_DMA1_MAP_3
#define LL_SYSCFG_DMA_MAP_I2C_TX            (SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_I2C_RX            (SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_1)
#define LL_SYSCFG_DMA_MAP_TIM1_CH1          (SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM1_CH2          (SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2)
#define LL_SYSCFG_DMA_MAP_TIM1_CH3          (SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM1_CH4          (SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1)
#define LL_SYSCFG_DMA_MAP_TIM1_COM          (SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM1_UP           SYSCFG_CFGR3_DMA1_MAP_4
#define LL_SYSCFG_DMA_MAP_TIM1_TRIG         (SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM3_CH1          (SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_1)
#define LL_SYSCFG_DMA_MAP_TIM3_CH3          (SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM3_CH4          (SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_2)
#define LL_SYSCFG_DMA_MAP_TIM3_TRG          (SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM3_UP           (SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_2 | SYSCFG_CFGR3_DMA1_MAP_1)
#define LL_SYSCFG_DMA_MAP_TIM16_CH1         (SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3)
#define LL_SYSCFG_DMA_MAP_TIM16_UP          (SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_0)
#define LL_SYSCFG_DMA_MAP_TIM17_CH1         (SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_1)
#define LL_SYSCFG_DMA_MAP_TIM17_UP          (SYSCFG_CFGR3_DMA1_MAP_4 | SYSCFG_CFGR3_DMA1_MAP_3 | SYSCFG_CFGR3_DMA1_MAP_1 | SYSCFG_CFGR3_DMA1_MAP_0)
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DMA_ACKLVL DMA SPEED ENABLE
  */
#define LL_SYSCFG_DMA_ACKLVL_NORM          0x00000000U
#define LL_SYSCFG_DMA_ACKLVL_FAST          SYSCFG_CFGR3_DMA1_ACKLVL
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DMA_CHNNEL_SHIFT DMA CHNNEL SHIFT ADDRESS
  */
#define LL_SYSCFG_DMA_CH2_SHIFT            (8U)
#define LL_SYSCFG_DMA_CH3_SHIFT            (16U)
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_LATENCY FLASH LATENCY
  * @{
  */
#define LL_FLASH_LATENCY_0                 0x00000000U             /*!< FLASH Zero Latency cycle */
#define LL_FLASH_LATENCY_1                 FLASH_ACR_LATENCY       /*!< FLASH One Latency cycle */
/**
  * @}
  */


/** @defgroup SYSTEM_LL_EC_APB1_GRP1_STOP_IP  DBGMCU APB1 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB1_GRP1_TIM3_STOP      DBGMCU_APB_FZ1_DBG_TIM3_STOP        /*!< TIM3 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_RTC_STOP       DBGMCU_APB_FZ1_DBG_RTC_STOP         /*!< RTC Calendar frozen when core is halted */
#define LL_DBGMCU_APB1_GRP1_WWDG_STOP      DBGMCU_APB_FZ1_DBG_WWDG_STOP        /*!< Debug Window Watchdog stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_IWDG_STOP      DBGMCU_APB_FZ1_DBG_IWDG_STOP        /*!< Debug Independent Watchdog stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_LPTIM1_STOP    DBGMCU_APB_FZ1_DBG_LPTIM_STOP      /*!< LPTIM1 counter stopped when Core is halted */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB2_GRP1_STOP_IP DBGMCU APB2 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB1_GRP2_TIM1_STOP      DBGMCU_APB_FZ2_DBG_TIM1_STOP        /*!< TIM1 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP2_TIM14_STOP     DBGMCU_APB_FZ2_DBG_TIM14_STOP       /*!< TIM14 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP2_TIM16_STOP     DBGMCU_APB_FZ2_DBG_TIM16_STOP       /*!< TIM16 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP2_TIM17_STOP     DBGMCU_APB_FZ2_DBG_TIM17_STOP       /*!< TIM17 counter stopped when core is halted */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Functions SYSTEM Exported Functions
  * @{
  */

/** @defgroup SYSTEM_LL_EF_SYSCFG SYSCFG
  * @{
  */

/**
  * @brief  Set memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      LL_SYSCFG_SetRemapMemory
  * @param  Memory This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetRemapMemory(uint32_t Memory)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE, Memory);
}

/**
  * @brief  Get memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      LL_SYSCFG_GetRemapMemory
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetRemapMemory(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE));
}

/**
  * @brief  Enable analog filtering of I2C related IO
  * @param  I2CAnalogFilter This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA2
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA3
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA7
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA8
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA9
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA10
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA11
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA12
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB6
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB7
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB8
  *         @arg @ref LL_SYSCFG_I2C_ANF_PF0
  *         @arg @ref LL_SYSCFG_I2C_ANF_PF1
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableI2CAnalogFilter(uint32_t I2CAnalogFilter)
{
  SET_BIT(SYSCFG->CFGR1, I2CAnalogFilter);
}

/**
  * @brief  Disable analog filtering of I2C related IO
  * @param  I2CAnalogFilter This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA2
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA3
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA7
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA8
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA9
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA10
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA11
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA12
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB6
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB7
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB8
  *         @arg @ref LL_SYSCFG_I2C_ANF_PF0
  *         @arg @ref LL_SYSCFG_I2C_ANF_PF1
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableI2CAnalogFilter(uint32_t I2CAnalogFilter)
{
  CLEAR_BIT(SYSCFG->CFGR1, I2CAnalogFilter);
}

/**
  * @brief  Indicate if enable analog filtering of I2C related IO
  * @param  I2CAnalogFilter This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA2
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA3
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA7
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA8
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA9
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA10
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA11
  *         @arg @ref LL_SYSCFG_I2C_ANF_PA12
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB6
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB7
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB8
  *         @arg @ref LL_SYSCFG_I2C_ANF_PF0
  *         @arg @ref LL_SYSCFG_I2C_ANF_PF1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledI2CAnalogFilter(uint32_t I2CAnalogFilter)
{
  return ((READ_BIT(SYSCFG->CFGR1, I2CAnalogFilter) == (I2CAnalogFilter)) ? 1UL : 0UL);
}

/**
  * @brief  Enables COMPx as TIMx break input
  * @param  TIMBreakInputs This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM17
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableTIMBreakInputs(uint32_t TIMBreakInputs)
{
  SET_BIT(SYSCFG->CFGR2, TIMBreakInputs);
}

/**
  * @brief  Disables COMPx as TIMx break input
  * @param  TIMBreakInputs This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM17
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableTIMBreakInputs(uint32_t TIMBreakInputs)
{
  CLEAR_BIT(SYSCFG->CFGR2, TIMBreakInputs);
}

/**
  * @brief  Indicate if COMPx as TIMx break input
  * @param  TIMBreakInputs This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM1
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM16
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP1_TO_TIM17
  *         @arg @ref LL_SYSCFG_TIMBREAK_COMP2_TO_TIM17
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledTIMBreakInputs(uint32_t TIMBreakInputs)
{
  return ((READ_BIT(SYSCFG->CFGR2, TIMBreakInputs) == (TIMBreakInputs)) ? 1UL : 0UL);
}

/**
  * @brief  Set the TIMER1 ETR input source
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_GPIO
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_COMP1
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_COMP2
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_ADC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetTIM1ETRSource(uint32_t source)
{
  MODIFY_REG(SYSCFG->CFGR2, SYSCFG_CFGR2_ETR_SRC_TIM1, source);
}

/**
  * @brief  Get the TIMER1 ETR input source
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_GPIO
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_COMP1
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_COMP2
  *         @arg @ref LL_SYSCFG_ETR_SRC_TIM1_ADC
  * @retval None
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIM1ETRSource(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_ETR_SRC_TIM1));
}

/**
  * @brief  Set the request image for DMA channel 1
  * @param  Requset This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_MAP_ADC
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH2
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_COM
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_TRIG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_TRG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_UP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetDMARemap_CH1(uint32_t Requset)
{
  MODIFY_REG(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA1_MAP_Msk, Requset);
}

/**
  * @brief  Gett the request image for DMA channel 1
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_MAP_ADC
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH2
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_COM
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_TRIG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_TRG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_UP
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDMARemap_CH1(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA1_MAP_Msk));
}

/**
  * @brief  Set the response speed of DMA channel 1
  * @param  Requset This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_NORM
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_FAST
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetDMAResponseSpeed_CH1(uint32_t ResponseSpeed)
{
  MODIFY_REG(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA1_ACKLVL, ResponseSpeed);
}

/**
  * @brief  Get the response speed of DMA channel 1
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_NORM
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_FAST
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDMAResponseSpeed_CH1(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA1_ACKLVL));
}


/**
  * @brief  Set the request image for DMA channel 2
  * @param  Requset This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_MAP_ADC
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH2
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_COM
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_TRIG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_TRG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_UP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetDMARemap_CH2(uint32_t Requset)
{
  MODIFY_REG(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA2_MAP_Msk, (Requset << LL_SYSCFG_DMA_CH2_SHIFT));
}

/**
  * @brief  Gett the request image for DMA channel 2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_MAP_ADC
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH2
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_COM
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_TRIG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_TRG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_UP
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDMARemap_CH2(void)
{
  return (uint32_t)((READ_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA2_MAP_Msk)) >> LL_SYSCFG_DMA_CH2_SHIFT);
}

/**
  * @brief  Set the response speed of DMA channel 2
  * @param  Requset This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_NORM
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_FAST
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetDMAResponseSpeed_CH2(uint32_t ResponseSpeed)
{
  MODIFY_REG(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA2_ACKLVL, (ResponseSpeed << LL_SYSCFG_DMA_CH2_SHIFT));
}

/**
  * @brief  Get the response speed of DMA channel 2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_NORM
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_FAST
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDMAResponseSpeed_CH2(void)
{
  return (uint32_t)((READ_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA2_ACKLVL)) >> LL_SYSCFG_DMA_CH2_SHIFT);
}

/**
  * @brief  Set the request image for DMA channel 3
  * @param  Requset This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_MAP_ADC
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH2
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_COM
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_TRIG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_TRG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_UP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetDMARemap_CH3(uint32_t Requset)
{
  MODIFY_REG(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA3_MAP_Msk, (Requset << LL_SYSCFG_DMA_CH3_SHIFT));
}

/**
  * @brief  Gett the request image for DMA channel 3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_MAP_ADC
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART2_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH2
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_COM
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_TRIG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH3
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH4
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_TRG
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_UP
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_CH1
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_UP
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDMARemap_CH3(void)
{
  return (uint32_t)((READ_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA3_MAP_Msk)) >> LL_SYSCFG_DMA_CH3_SHIFT);
}

/**
  * @brief  Set the response speed of DMA channel 3
  * @param  Requset This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_NORM
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_FAST
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetDMAResponseSpeed_CH3(uint32_t ResponseSpeed)
{
  MODIFY_REG(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA3_ACKLVL, (ResponseSpeed << LL_SYSCFG_DMA_CH3_SHIFT));
}

/**
  * @brief  Get the response speed of DMA channel 3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_NORM
  *         @arg @ref LL_SYSCFG_DMA_ACKLVL_FAST
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDMAResponseSpeed_CH3(void)
{
  return (uint32_t)((READ_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_DMA3_ACKLVL)) >> LL_SYSCFG_DMA_CH3_SHIFT);
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_FLASH FLASH
  * @{
  */

/**
  * @brief  Set FLASH Latency
  * @rmtoll FLASH_ACR    FLASH_ACR_LATENCY       LL_FLASH_SetLatency
  * @param  Latency This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetLatency(uint32_t Latency)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, Latency);
}

/**
  * @brief  Get FLASH Latency
  * @rmtoll FLASH_ACR    FLASH_ACR_LATENCY       LL_FLASH_GetLatency
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(void)
{
  return (uint32_t)(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY));
}

/**
  * @}
  */

/**
  * @}
  */


/**
  * @brief  Return the device identifier
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetDeviceID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_DEV_ID));
}

/**
  * @brief  Return the device revision identifier
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetRevisionID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_REV_ID) >> DBGMCU_IDCODE_REV_ID_Pos);
}


/**
  * @brief  Enable the Debug Module during STOP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Indicate if enable the Debug Module during STOP mode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGStopMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP) == (DBGMCU_CR_DBG_STOP)) ? 1UL : 0UL);
}
/**
  * @brief  Freeze APB1 peripherals (group1 peripherals)
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APBFZ1, Periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals (group1 peripherals)
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APBFZ1, Periphs);
}

/**
  * @brief  Indicate if Freeze APB1 peripherals (group1 peripherals)
  * @param  Periphs This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_APB1_GRP1_IsFreezePeriph(uint32_t Periphs)
{
  return ((READ_BIT(DBGMCU->APBFZ1, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Freeze APB1 peripherals(group2 peripherals)
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APBFZ2, Periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals(group2 peripherals)
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APBFZ2, Periphs);
}

/**
  * @brief  Indicate if Freeze APB1 peripherals (group2 peripherals)
  * @param  Periphs This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM17_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_APB1_GRP2_IsFreezePeriph(uint32_t Periphs)
{
  return ((READ_BIT(DBGMCU->APBFZ2, Periphs) == (Periphs)) ? 1UL : 0UL);
}
/**
  * @}
  */

#endif /* defined (FLASH) || defined (SYSCFG) || defined (DBGMCU) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* XL32F0XX_LL_SYSTEM_H */

/************************ (C) COPYRIGHT Xinling *****END OF FILE****/

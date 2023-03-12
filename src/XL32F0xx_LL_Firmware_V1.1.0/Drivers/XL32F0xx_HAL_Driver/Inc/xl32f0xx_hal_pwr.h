/**
  ******************************************************************************
  * @file    xl32f0xx_hal_pwr.h
  * @author  MCU Application Team
  * @brief   Header file of PWR HAL module.
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
#ifndef __XL32F0xx_HAL_PWR_H
#define __XL32F0xx_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "xl32f0xx_hal_def.h"

/** @addtogroup XL32F0xx_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief PWR HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PWR_Exported_Types PWR Exported Types
  * @{
  */

#if defined(PWR_PVD_SUPPORT)
/**
  * @brief  PWR PVD configuration structure definition
  */
typedef struct
{
  uint32_t PVDSource;   /*!< PVDSource: Specifies the PVD detection source.
                              This parameter can be a value of @ref PWR_PVD_Source. */
    
  uint32_t PVDFilter;   /*!< PVDFilter: Specifies the PVD input filter.    
                              This parameter can be a value of @ref PWR_PVD_Filter. */
    
  uint32_t PVDLevel;    /*!< PVDLevel: Specifies the PVD detection level.
                              This parameter can be a value or a combination of
                              @ref PWR_PVD_detection_level. */

  uint32_t Mode;        /*!< Mode: Specifies the operating mode for the selected pins.
                              This parameter can be a value of @ref PWR_PVD_Mode. */
} PWR_PVDTypeDef;
#endif
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

#if defined(PWR_PVD_SUPPORT)
/** @defgroup PWR_PVD_Source  PWR PVD Source
  * @{
  */
#define PWR_PVD_SOURCE_VCC                  (0x00000000u)  /*!< PVD detection source is Vcc */
#define PWR_PVD_SOURCE_PB07                 (PWR_CR2_SRCSEL)  /*!< PVD detection source is PB07 */
/**
  * @}
  */

/** @defgroup PWR_PVD_Filter  PWR PVD Filter
  * @{
  */
#define PWR_PVD_FILTER_NONE                  (0x00000000u)                                              /*!< PVD filter disable */
#define PWR_PVD_FILTER_1CLOCK                (PWR_CR2_FLTEN | 0x00000000u)                              /*!< PVD filter 1    clock */
#define PWR_PVD_FILTER_2CLOCK                (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_0)                       /*!< PVD filter 2    clock */
#define PWR_PVD_FILTER_4CLOCK                (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_1)                       /*!< PVD filter 4    clock */
#define PWR_PVD_FILTER_16CLOCK               (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_0 | PWR_CR2_FLT_TIME_1)  /*!< PVD filter 16   clock */
#define PWR_PVD_FILTER_64CLOCK               (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_2)                       /*!< PVD filter 64   clock */
#define PWR_PVD_FILTER_128CLOCK              (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_2 | PWR_CR2_FLT_TIME_0)  /*!< PVD filter 128  clock */
#define PWR_PVD_FILTER_1024CLOCK             (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_2 | PWR_CR2_FLT_TIME_1)  /*!< PVD filter 1024 clock */
/**
  * @}
  */

/** @defgroup PWR_PVD_detection_level  Programmable Voltage Detection levels
  * @note   see datasheet for selection voltage value
  * @{
  */
#define PWR_PVDLEVEL_0                      (0x00000000u)                                        /*!< same PVD threshold level 0 on rising & falling */
#define PWR_PVDLEVEL_1                      (PWR_CR2_PVDT_0)                                     /*!< same PVD threshold level 1 on rising & falling */
#define PWR_PVDLEVEL_2                      (PWR_CR2_PVDT_1)                                     /*!< same PVD threshold level 2 on rising & falling */
#define PWR_PVDLEVEL_3                      (PWR_CR2_PVDT_0 | PWR_CR2_PVDT_1)                    /*!< same PVD threshold level 3 on rising & falling */
#define PWR_PVDLEVEL_4                      (PWR_CR2_PVDT_2)                                     /*!< same PVD threshold level 4 on rising & falling */
#define PWR_PVDLEVEL_5                      (PWR_CR2_PVDT_2 | PWR_CR2_PVDT_0)                    /*!< same PVD threshold level 5 on rising & falling */
#define PWR_PVDLEVEL_6                      (PWR_CR2_PVDT_2 | PWR_CR2_PVDT_1)                    /*!< same PVD threshold level 6 on rising & falling */
#define PWR_PVDLEVEL_7                      (PWR_CR2_PVDT_2 | PWR_CR2_PVDT_1 | PWR_CR2_PVDT_0)   /*!< same PVD threshold level 7 on rising & falling */
/**
  * @}
  */

/** @defgroup PWR_PVD_Mode  PWR PVD interrupt and event mode
  * @{
  */
#define PWR_PVD_MODE_NORMAL                 (0x00000000u)  /*!< basic mode is used */
#define PWR_PVD_MODE_IT_RISING              (0x00010001u)  /*!< External Interrupt Mode with Rising edge trigger detection */
#define PWR_PVD_MODE_IT_FALLING             (0x00010002u)  /*!< External Interrupt Mode with Falling edge trigger detection */
#define PWR_PVD_MODE_IT_RISING_FALLING      (0x00010003u)  /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING           (0x00020001u)  /*!< Event Mode with Rising edge trigger detection */
#define PWR_PVD_MODE_EVENT_FALLING          (0x00020002u)  /*!< Event Mode with Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING_FALLING   (0x00020003u)  /*!< Event Mode with Rising/Falling edge trigger detection */
/**
  * @}
  */

/** @defgroup PWR_PVD_EXTI_LINE  PWR PVD external interrupt line
  * @{
  */
#define PWR_EXTI_LINE_PVD                   (EXTI_IMR_IM16)  /*!< External interrupt line 16 connected to PVD */
/**
  * @}
  */

/** @defgroup PWR_PVD_EVENT_LINE  PWR PVD event line
  * @{
  */
#define PWR_EVENT_LINE_PVD                  (EXTI_EMR_EM16)  /*!< Event line 16 connected to PVD */
/**
  * @}
  */
#endif


/** @defgroup PWR_Regulator_state_in_SLEEP_STOP_mode  PWR regulator mode
  * @{
  */
#define PWR_MAINREGULATOR_ON                (0x00000000u)  /*!< Regulator in main mode      */
#define PWR_LOWPOWERREGULATOR_ON            PWR_CR1_LPR    /*!< Regulator in low-power mode */
/**
  * @}
  */

/** @defgroup PWR_SLEEP_mode_entry  PWR SLEEP mode entry
  * @{
  */
#define PWR_SLEEPENTRY_WFI                  ((uint8_t)0x01u)        /*!< Wait For Interruption instruction to enter Sleep mode */
#define PWR_SLEEPENTRY_WFE                  ((uint8_t)0x02u)        /*!< Wait For Event instruction to enter Sleep mode        */
/**
  * @}
  */

/** @defgroup PWR_STOP_mode_entry  PWR STOP mode entry
  * @{
  */
#define PWR_STOPENTRY_WFI                   ((uint8_t)0x01u)        /*!< Wait For Interruption instruction to enter Stop mode */
#define PWR_STOPENTRY_WFE                   ((uint8_t)0x02u)        /*!< Wait For Event instruction to enter Stop mode        */
/**
  * @}
  */


/** @defgroup PWR_Flag  PWR Status Flags
  * @{
  */
#if defined(PWR_PVD_SUPPORT)
#define PWR_FLAG_PVDO                       (PWR_SR_PVDO)      /*!< Power Voltage Detector output */
#endif
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup PWR_Exported_Macros  PWR Exported Macros
  * @{
  */

#if defined(PWR_PVD_SUPPORT)
/** @defgroup PWR_Exported_Macros  PWR Exported Macros
  * @{
  */
/** @brief  Check whether or not a specific PWR flag is set.
  * @param  __FLAG__  specifies the flag to check.
  *         This parameter can be one a combination of following values:
  *            @arg PWR_FLAG_PVDO: Power Voltage Detector Output. Indicates whether
  *                 VDD voltage is below or above the selected PVD threshold.
  * @endif
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_PWR_GET_FLAG(__FLAG__)        ((PWR->SR & (__FLAG__)) == (__FLAG__))

/**
  * @brief Enable the PVD Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_IT()            SET_BIT(EXTI->IMR, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_IT()           CLEAR_BIT(EXTI->IMR, PWR_EXTI_LINE_PVD)

/**
  * @brief Enable the PVD Event Line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_EVENT()         SET_BIT(EXTI->EMR, PWR_EVENT_LINE_PVD)

/**
  * @brief Disable the PVD Event Line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_EVENT()        CLEAR_BIT(EXTI->EMR, PWR_EVENT_LINE_PVD)

/**
  * @brief Enable the PVD Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR, PWR_EXTI_LINE_PVD)

/**
  * @brief Enable the PVD Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE()  SET_BIT(EXTI->FTSR, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE() CLEAR_BIT(EXTI->FTSR, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                   \
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0U)

/**
  * @brief Disable the PVD Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0U)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_GENERATE_SWIT()        SET_BIT(EXTI->SWIER, PWR_EXTI_LINE_PVD)

/**
  * @brief Check whether or not the PVD EXTI interrupt flag is set.
  * @retval EXTI PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTI_GET_FLAG()             (EXTI->PR & PWR_EXTI_LINE_PVD)

/**
  * @brief Clear the PVD EXTI interrupt flag.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_FLAG()           WRITE_REG(EXTI->PR, PWR_EXTI_LINE_PVD)
#endif /* PWR_PVD_SUPPORT */

/**
  * @}
  */

/* Private constants-------------------------------------------------------*/
/** @defgroup PWREx_WUP_Polarity Shift to apply to retrieve polarity information from PWR_WAKEUP_PINy_xxx constants
  * @{
  */
#define PWR_WUP_POLARITY_SHIFT              0x08u   /*!< Internal constant used to retrieve wakeup pin polariry */
/**
  * @}
  */

/* Private macros --------------------------------------------------------*/
/** @defgroup PWR_Private_Macros  PWR Private Macros
  * @{
  */
#if defined(PWR_PVD_SUPPORT)
#define IS_PWR_PVD_LEVEL(LEVEL)                   (((LEVEL) & ~(PWR_CR2_PVDT)) == 0x00000000u)

#define IS_PWR_PVD_MODE(MODE)                     (((MODE) == PWR_PVD_MODE_NORMAL)              || \
                                                   ((MODE) == PWR_PVD_MODE_IT_RISING)           || \
                                                   ((MODE) == PWR_PVD_MODE_IT_FALLING)          || \
                                                   ((MODE) == PWR_PVD_MODE_IT_RISING_FALLING)   || \
                                                   ((MODE) == PWR_PVD_MODE_EVENT_RISING)        || \
                                                   ((MODE) == PWR_PVD_MODE_EVENT_FALLING)       || \
                                                   ((MODE) == PWR_PVD_MODE_EVENT_RISING_FALLING))
#endif

#define IS_PWR_REGULATOR(REGULATOR)               (((REGULATOR) == PWR_MAINREGULATOR_ON) || \
                                                   ((REGULATOR) == PWR_LOWPOWERREGULATOR_ON))

#define IS_PWR_SLEEP_ENTRY(ENTRY)                 (((ENTRY) == PWR_SLEEPENTRY_WFI) || \
                                                   ((ENTRY) == PWR_SLEEPENTRY_WFE))

#define IS_PWR_STOP_ENTRY(ENTRY)                  (((ENTRY) == PWR_STOPENTRY_WFI) || \
                                                   ((ENTRY) == PWR_STOPENTRY_WFE))
/**
  * @}
  */

/* Include PWR HAL Extended module */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_Exported_Functions  PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1  Initialization and de-initialization functions
  * @{
  */

/* Initialization and de-initialization functions *******************************/
void              HAL_PWR_DeInit(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group2  Peripheral Control functions
  * @{
  */
/* Peripheral Control functions  ************************************************/
void              HAL_PWR_EnableBkUpAccess(void);
void              HAL_PWR_DisableBkUpAccess(void);
#if defined(PWR_PVD_SUPPORT)
HAL_StatusTypeDef HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD);
void              HAL_PWR_EnablePVD(void);
void              HAL_PWR_DisablePVD(void);
#endif

/* Low Power modes configuration functions ************************************/
void              HAL_PWR_EnterSLEEPMode(uint8_t SLEEPEntry);
void              HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void              HAL_PWR_EnableSleepOnExit(void);
void              HAL_PWR_DisableSleepOnExit(void);
void              HAL_PWR_EnableSEVOnPend(void);
void              HAL_PWR_DisableSEVOnPend(void);
#if defined(PWR_PVD_SUPPORT)
void              HAL_PWR_PVD_IRQHandler(void);
void              HAL_PWR_PVD_Callback(void);
#endif
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* __XL32F0xx_HAL_PWR_H */

/************************ (C) COPYRIGHT Xinling *****END OF FILE****/

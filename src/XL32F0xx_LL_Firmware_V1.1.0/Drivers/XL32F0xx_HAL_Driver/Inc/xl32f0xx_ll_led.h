/**
  ******************************************************************************
  * @file    xl32f0xx_ll_led.h
  * @author  MCU Application Team
  * @brief   Header file of LED LL module.
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
#ifndef XL32F0XX_LL_LED_H
#define XL32F0XX_LL_LED_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "xl32f0xx.h"

/** @addtogroup XL32F0XX_LL_Driver
  * @{
  */

#if defined (LED)
/** @defgroup LED_LL LED
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
  * @brief LED Init Structure definition
  */
typedef struct
{
  uint32_t ComDrive;          /*!< Specifies the LED COM drive capability.
                                     This parameter can be a value of @ref LED_LL_EC_ComDrive */

  uint32_t Prescaler;         /*!< Specifies the prescaler value used to divide the LED clock.
                                     This parameter can be a number between Min_Data = 0x00(div1) and Max_Data = 0xFF(div256) */

  uint32_t ComSelect;            /*!< Specifies the number of COM open.
                                     This parameter can be a value of @ref LED_LL_EC_ComSelct */

  uint32_t LightTime;         /*!< Specifies LED Lighting time.
                                     This parameter can be a number between Min_Data = 1 and Max_Data = 0xFF */

  uint32_t DeadTime;          /*!< Specifies LED Dead time.
                                     This parameter can be a number between Min_Data = 1 and Max_Data = 0xFF */

} LL_LED_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup LED_LL_EC_ComDrive ComDrive
  * @{
  */
#define LL_LED_COMDRIVE_LOW          0x00000000U
#define LL_LED_COMDRIVE_HIGH         LED_CR_EHS
/**
  * @}
  */


/** @defgroup LED_LL_EC_ComSelct the number of COM open
  * @{
  */
#define LL_LED_COMSELECT_1COM             0x00000000U
#define LL_LED_COMSELECT_2COM             LED_CR_LED_COM_SEL_0
#define LL_LED_COMSELECT_3COM             LED_CR_LED_COM_SEL_1
#define LL_LED_COMSELECT_4COM             (LED_CR_LED_COM_SEL_1 | LED_CR_LED_COM_SEL_0)
/**
  * @}
  */

/** @defgroup LED_LL_EC_DisplayValue LED display value
  * @{
  */
#define LL_LED_DISP_NONE            0x00U
#define LL_LED_DISP_FULL            0xFFU

#define LL_LED_DISP_0               0x3FU
#define LL_LED_DISP_1               0x06U
#define LL_LED_DISP_2               0x5BU
#define LL_LED_DISP_3               0x4FU
#define LL_LED_DISP_4               0x66U
#define LL_LED_DISP_5               0x6DU
#define LL_LED_DISP_6               0x7DU
#define LL_LED_DISP_7               0x07U
#define LL_LED_DISP_8               0x7FU
#define LL_LED_DISP_9               0x6FU
#define LL_LED_DISP_A               0x77U
#define LL_LED_DISP_B               0x7CU
#define LL_LED_DISP_C               0x39U
#define LL_LED_DISP_D               0x5EU
#define LL_LED_DISP_E               0x79U
#define LL_LED_DISP_F               0x71U
#define LL_LED_DISP_H               0x76U
#define LL_LED_DISP_P               0x73U
#define LL_LED_DISP_U               0x3EU
#define LL_LED_DISP_DOT             0x80U
/**
  * @}
  */

/** @defgroup LED_LL_EC_ComDisplay LED COM Select
  * @{
  */
#define LL_LED_COM0                0x00000000U
#define LL_LED_COM1                0x00000004U
#define LL_LED_COM2                0x00000008U
#define LL_LED_COM3                0x0000000CU
/**
  * @}
  */

/** @defgroup LED_LL_EC_DataReg Data Register Mask and position
  * @{
  */
#define LL_LED_DR_DATA               LED_DR0_DATA0
#define LL_LED_DR_DATA_Pos           LED_DR0_DATA0_Pos
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Set the LED COM drive capability.
  * @param  LEDx LED Instance
  * @param  ComDrive This parameter can be one of the following values:
  *         @arg @ref LL_LED_COMDRIVE_LOW
  *         @arg @ref LL_LED_COMDRIVE_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_LED_SetComDrive(LED_TypeDef *LEDx, uint32_t ComDrive)
{
  MODIFY_REG(LEDx->CR, LED_CR_EHS, ComDrive);
}

/**
  * @brief  Get the LED COM drive capability.
  * @param  LEDx LED Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LED_COMDRIVE_LOW
  *         @arg @ref LL_LED_COMDRIVE_HIGH
  */
__STATIC_INLINE uint32_t LL_LED_GetComDrive(LED_TypeDef *LEDx)
{
  return (READ_BIT(LEDx->CR, LED_CR_EHS));
}

/**
  * @brief  Enable LED Interrupt.
  * @param  LEDx LED Instance
  * @retval None
  */
__STATIC_INLINE void LL_LED_EnableIT(LED_TypeDef *LEDx)
{
  SET_BIT(LEDx->CR, LED_CR_IE);
}

/**
  * @brief  Disable LED Interrupt.
  * @param  LEDx LED Instance
  * @retval None
  */
__STATIC_INLINE void LL_LED_DisableIT(LED_TypeDef *LEDx)
{
  CLEAR_BIT(LEDx->CR, LED_CR_IE);
}
/**
  * @brief  Check if LED Interrupt is enabled
  * @param  LEDx LED Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LED_IsEnabledIT(LED_TypeDef *LEDx)
{
  return ((READ_BIT(LEDx->CR, LED_CR_IE) == (LED_CR_IE)) ? 1UL : 0UL);
}

/**
  * @brief  Set he number of COM open.
  * @param  LEDx LED Instance
  * @param  ComNum This parameter can be one of the following values:
  *         @arg @ref LL_LED_COMSELECT_1COM
  *         @arg @ref LL_LED_COMSELECT_2COM
  *         @arg @ref LL_LED_COMSELECT_3COM
  *         @arg @ref LL_LED_COMSELECT_4COM
  * @retval None
  */
__STATIC_INLINE void LL_LED_SetComNum(LED_TypeDef *LEDx, uint32_t ComNum)
{
  MODIFY_REG(LEDx->CR, LED_CR_LED_COM_SEL, ComNum);
}

/**
  * @brief  Get the number of COM open.
  * @param  LEDx LED Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LED_COMSELECT_1COM
  *         @arg @ref LL_LED_COMSELECT_2COM
  *         @arg @ref LL_LED_COMSELECT_3COM
  *         @arg @ref LL_LED_COMSELECT_4COM
  */
__STATIC_INLINE uint32_t LL_LED_GetComNum(LED_TypeDef *LEDx)
{
  return (READ_BIT(LEDx->CR, LED_CR_LED_COM_SEL));
}


/**
  * @brief  Enable LED. 
  * @param  LEDx LED Instance
  * @retval None
  */
__STATIC_INLINE void LL_LED_Enable(LED_TypeDef *LEDx)
{
  SET_BIT(LEDx->CR, LED_CR_LEDON);
}

/**
  * @brief  Disable LED. 
  * @param  LEDx LED Instance
  * @retval None
  */
__STATIC_INLINE void LL_LED_Disable(LED_TypeDef *LEDx)
{
  CLEAR_BIT(LEDx->CR, LED_CR_LEDON);
}

/**
  * @brief  Checks if LED is enabled
  * @param  LEDx LED Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LED_IsEnabled(LED_TypeDef *LEDx)
{
  return ((READ_BIT(LEDx->CR, LED_CR_LEDON) == (LED_CR_LEDON)) ? 1UL : 0UL);
}

/**
  * @brief  Set the LED prescale Value.
  * @param  LEDx LED Instance
  * @param  Prescaler This parameter can be a number between Min_Data = 0x00(div1)
  *         and Max_Data = 0xFF(div256)
  * @retval None
  */
__STATIC_INLINE void LL_LED_SetPrescaler(LED_TypeDef *LEDx, uint32_t Prescaler)
{
  MODIFY_REG(LEDx->PR, LED_PR_PR, (Prescaler << LED_PR_PR_Pos));
}

/**
  * @brief  Return LED Prescaler Value.
  * @param  LEDx LED Instance
  * @retval Returned value can be a number between Min_Data = 0x00(div1)
  *         and Max_Data = 0xFF(div256)
  */
__STATIC_INLINE uint32_t LL_LED_GetPrescaler(LED_TypeDef *LEDx)
{
  return (READ_BIT(LEDx->PR, LED_PR_PR) >> LED_PR_PR_Pos);
}

/**
  * @brief  Set the LED Lighting and Dead time.
  * @param  LEDx LED Instance
  * @param  LightTime This parameter can be a number between Min_Data = 1 and
  *         Max_Data = 0xFF
  * @param  DeadTime This parameter can be a number between Min_Data = 1 and
  *         Max_Data = 0xFF
  * @retval None
  */
__STATIC_INLINE void LL_LED_SetLightAndDeadTime(LED_TypeDef *LEDx,\
  uint32_t LightTime, uint32_t DeadTime)
{
  MODIFY_REG(LEDx->TR, (LED_TR_T1 | LED_TR_T2), ((LightTime << LED_TR_T1_Pos) |\
      (DeadTime << LED_TR_T2_Pos)));
}

/**
  * @brief  Set the LED Lighting time.
  * @param  LEDx LED Instance
  * @param  LightTime This parameter can be a number between Min_Data = 1 and
  *         Max_Data = 0xFF
  * @retval None
  */
__STATIC_INLINE void LL_LED_SetLightTime(LED_TypeDef *LEDx, uint32_t LightTime)
{
  MODIFY_REG(LEDx->TR, LED_TR_T1, (LightTime << LED_TR_T1_Pos));
}

/**
  * @brief  Set the LED Dead time.
  * @param  LEDx LED Instance
  * @param  DeadTime This parameter can be a number between Min_Data = 1 and
  *         Max_Data = 0xFF
  * @retval None
  */
__STATIC_INLINE void LL_LED_SetDeadTime(LED_TypeDef *LEDx, uint32_t DeadTime)
{
  MODIFY_REG(LEDx->TR, LED_TR_T2, (DeadTime << LED_TR_T2_Pos));
}

/**
  * @brief  Get the LED Lighting time.
  * @param  LEDx LED Instance
  * @retval Returned value can be a number between Min_Data = 1 and
  *         Max_Data = 0xFF
  */
__STATIC_INLINE uint32_t LL_LED_GetLightTime(LED_TypeDef *LEDx)
{
  return (READ_BIT(LEDx->TR, LED_TR_T1) >> LED_TR_T1_Pos);
}

/**
  * @brief  Get the LED Dead time.
  * @param  LEDx LED Instance
  * @retval Returned value can be a number between Min_Data = 1 and
  *         Max_Data = 0xFF
  */
__STATIC_INLINE uint32_t LL_LED_GetDeadTime(LED_TypeDef *LEDx)
{
  return (READ_BIT(LEDx->TR, LED_TR_T2) >> LED_TR_T2_Pos);
}

/**
  * @brief  Set the LED display value.
  * @param  LEDx LED Instance
  * @param  comCh Specify COM channels.This parameter can be one of the following values:
  *         @arg @ref LL_LED_COM0
  *         @arg @ref LL_LED_COM1
  *         @arg @ref LL_LED_COM2
  *         @arg @ref LL_LED_COM3
  * @param  data Specify display values.This parameter can be one of the following values:
  *         @arg @ref LL_LED_DISP_NONE
  *         @arg @ref LL_LED_DISP_FULL
  *         @arg @ref LL_LED_DISP_0
  *         @arg @ref LL_LED_DISP_1
  *         @arg @ref LL_LED_DISP_2
  *         @arg @ref LL_LED_DISP_3
  *         @arg @ref LL_LED_DISP_4
  *         @arg @ref LL_LED_DISP_5
  *         @arg @ref LL_LED_DISP_6
  *         @arg @ref LL_LED_DISP_7
  *         @arg @ref LL_LED_DISP_8
  *         @arg @ref LL_LED_DISP_9
  *         @arg @ref LL_LED_DISP_A
  *         @arg @ref LL_LED_DISP_B
  *         @arg @ref LL_LED_DISP_C 
  *         @arg @ref LL_LED_DISP_D
  *         @arg @ref LL_LED_DISP_E
  *         @arg @ref LL_LED_DISP_F
  *         @arg @ref LL_LED_DISP_H
  *         @arg @ref LL_LED_DISP_P
  *         @arg @ref LL_LED_DISP_U
  *         @arg @ref LL_LED_DISP_DOT
  * @retval None
  */
__STATIC_INLINE void LL_LED_SetDisplayValue(LED_TypeDef *LEDx,uint32_t comCh,\
  uint32_t data)
{
  MODIFY_REG((*((uint32_t *)((uint32_t)&(LEDx->DR0) + comCh))), LL_LED_DR_DATA,\
     (data << LL_LED_DR_DATA_Pos));
}

/**
  * @brief  Get the LED display value.
  * @param  LEDx LED Instance
  * @param  comCh Specify COM channels.This parameter can be one of the following values:
  *         @arg @ref LL_LED_COM0
  *         @arg @ref LL_LED_COM1
  *         @arg @ref LL_LED_COM2
  *         @arg @ref LL_LED_COM3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LED_DISP_NONE
  *         @arg @ref LL_LED_DISP_FULL
  *         @arg @ref LL_LED_DISP_0
  *         @arg @ref LL_LED_DISP_1
  *         @arg @ref LL_LED_DISP_2
  *         @arg @ref LL_LED_DISP_3
  *         @arg @ref LL_LED_DISP_4
  *         @arg @ref LL_LED_DISP_5
  *         @arg @ref LL_LED_DISP_6
  *         @arg @ref LL_LED_DISP_7
  *         @arg @ref LL_LED_DISP_8
  *         @arg @ref LL_LED_DISP_9
  *         @arg @ref LL_LED_DISP_A
  *         @arg @ref LL_LED_DISP_B
  *         @arg @ref LL_LED_DISP_C 
  *         @arg @ref LL_LED_DISP_D
  *         @arg @ref LL_LED_DISP_E
  *         @arg @ref LL_LED_DISP_F
  *         @arg @ref LL_LED_DISP_H
  *         @arg @ref LL_LED_DISP_P
  *         @arg @ref LL_LED_DISP_U
  *         @arg @ref LL_LED_DISP_DOT
  */
__STATIC_INLINE uint32_t LL_LED_GetDisplayValue(LED_TypeDef *LEDx, uint32_t comCh)
{
  return ((READ_BIT((*((uint32_t *)((uint32_t)&(LEDx->DR0) + comCh))), LL_LED_DR_DATA))\
      >> LL_LED_DR_DATA_Pos);
}


/**
  * @brief  Get the LED interrupt flag.
  * @param  LEDx LED Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LED_IsActiveFlag_IT(LED_TypeDef *LEDx)
{
  return ((READ_BIT(LEDx->IR, LED_IR_FLAG) == (LED_IR_FLAG)) ? 1UL : 0UL);
}

/**
  * @brief  the LED interrupt flag.
  * @param  LEDx LED Instance
  * @retval None
  */
__STATIC_INLINE void LL_LED_ClearFlag_IT(LED_TypeDef *LEDx)
{
  SET_BIT(LEDx->IR, LED_IR_FLAG);
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup LED_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_LED_DeInit(LED_TypeDef *LEDx);
ErrorStatus LL_LED_Init(LED_TypeDef *LEDx, LL_LED_InitTypeDef *LED_InitStruct);
void LL_LED_StructInit(LL_LED_InitTypeDef *LED_InitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

#endif /* LED */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* XL32F0xx_LL_LED_H */

/************************ (C) COPYRIGHT Xinling *****END OF FILE****/

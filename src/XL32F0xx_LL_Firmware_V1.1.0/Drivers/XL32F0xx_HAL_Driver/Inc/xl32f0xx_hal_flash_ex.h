/**
  ******************************************************************************
  * @file    xl32f0xx_hal_flash_ex.h
  * @author  MCU Application Team
  * @brief   Header file of FLASH HAL Extended module.
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
#ifndef __XL32F0xx_HAL_FLASH_EX_H
#define __XL32F0xx_HAL_FLASH_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "xl32f0xx_hal_def.h"

/** @addtogroup XL32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Constants FLASH Exported Constants
  * @{
  */
/** @defgroup FLASHEx_Empty_Check FLASHEx Empty Check
  * @{
  */
#define FLASH_PROG_NOT_EMPTY                0x00000000u          /*!< 1st location in Flash is programmed */
#define FLASH_PROG_EMPTY                    FLASH_ACR_PROGEMPTY  /*!< 1st location in Flash is empty */
/**
  * @}
  */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASHEx_Exported_Functions
  * @{
  */

/* Extended Program operation functions  *************************************/
/** @addtogroup FLASHEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);
void              HAL_FLASHEx_EnableDebugger(void);
void              HAL_FLASHEx_DisableDebugger(void);
uint32_t          HAL_FLASHEx_FlashEmptyCheck(void);
void              HAL_FLASHEx_ForceFlashEmpty(uint32_t FlashEmpty);
#if defined(FLASH_SECURABLE_MEMORY_SUPPORT)
void              HAL_FLASHEx_EnableSecMemProtection(uint32_t Bank);
#endif
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Constants FLASHEx Private Constants
  * @{
  */
#define FLASH_PCROP_GRANULARITY_OFFSET             9u                                        /*!< FLASH Code Readout Protection granularity offset */
#define FLASH_PCROP_GRANULARITY                    (1UL << FLASH_PCROP_GRANULARITY_OFFSET)   /*!< FLASH Code Readout Protection granularity, 512 Bytes */
/**
  * @}
  */


/** @defgroup FLASHEx_Private_Macros FLASHEx Private Macros
  *  @{
  */
#define IS_FLASH_EMPTY_CHECK(__VALUE__)     (((__VALUE__) == FLASH_PROG_EMPTY) || ((__VALUE__) == FLASH_PROG_NOT_EMPTY))
void              FLASH_PageErase(uint32_t Page);
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

#endif /* __XL32F0xx_HAL_FLASH_EX_H */

/************************ (C) COPYRIGHT Xinling *****END OF FILE****/

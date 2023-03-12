/**
  ******************************************************************************
  * @file    xl32f0xx.h
  * @brief   CMSIS XL32F0xx Device Peripheral Access Layer Header File.
  * @version v1.0.0
  *
  ******************************************************************************
  * @attention
  *
  *     COPYRIGHT(c) 2021, Xinling Semiconductor Inc.
  *
  *     All rights reserved.
  *
  *     Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of the copyright holder nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  *     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup xl32f0xx
  * @{
  */

#ifndef __XL32F0XX_H
#define __XL32F0XX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief XL32 Family
  */
#if !defined  (XL32F0)
#define XL32F0
#endif /* XL32F0 */

#if (defined(XL32F030x3) || defined(XL32F030x4) || defined(XL32F030x6) || defined(XL32F030x7) || defined(XL32F030x8))
#define XL32F030PRE
#elif (defined(XL32F003x4) || defined(XL32F003x6) || defined(XL32F003x8))
#define XL32F003PRE
#elif (defined(XL32F072xB))
#define XL32F072PRE
#endif

/* Uncomment the line below according to the target XL32 device used in your
   application
  */

#if !defined (XL32F030x3) && !defined (XL32F030x4) && !defined (XL32F030x6) && !defined (XL32F030x7) && !defined (XL32F030x8) && !defined (XL32F030xx) && \
    !defined (XL32F003x4) && !defined (XL32F003x6) && !defined (XL32F003x8) && \
    !defined (XL32F072xB)
/* #define XL32F030x3 */  /*!< XL32F030x3 Devices (XL32F030xx microcontrollers where the Flash memory is 8 Kbytes)               */
/* #define XL32F030x4 */  /*!< XL32F030x4 Devices (XL32F030xx microcontrollers where the Flash memory is 16 Kbytes)              */
/* #define XL32F030x6 */  /*!< XL32F030x6 Devices (XL32F030xx microcontrollers where the Flash memory is 32 Kbytes)              */
/* #define XL32F030x7 */  /*!< XL32F030x7 Devices (XL32F030xx microcontrollers where the Flash memory is 48 Kbytes)              */
/* #define XL32F030x8 */  /*!< XL32F030x8 Devices (XL32F030xx microcontrollers where the Flash memory is 64 Kbytes)              */
/* #define XL32F003x4 */  /*!< XL32F003x4 Devices (XL32F003xx microcontrollers where the Flash memory is 16 Kbytes)              */
/* #define XL32F003x6 */  /*!< XL32F003x6 Devices (XL32F003xx microcontrollers where the Flash memory is 32 Kbytes)              */
/* #define XL32F003x8 */  /*!< XL32F003x8 Devices (XL32F003xx microcontrollers where the Flash memory is 64 Kbytes)              */
/* #define XL32F072xB */  /*!< XL32F072xB Devices (XL32F072xx microcontrollers where the Flash memory is 128 Kbytes)             */
#endif

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
#if !defined  (USE_HAL_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
/*#define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */

/**
  * @brief CMSIS Device version number V1.0.0
  */
#define __XL32F0_DEVICE_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __XL32F0_DEVICE_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __XL32F0_DEVICE_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __XL32F0_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __XL32F0_DEVICE_VERSION        ((__XL32F0_DEVICE_VERSION_MAIN << 24)\
                                        |(__XL32F0_DEVICE_VERSION_SUB1 << 16)\
                                        |(__XL32F0_DEVICE_VERSION_SUB2 << 8 )\
                                        |(__XL32F0_DEVICE_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(XL32F030x3)
#include "xl32f030x3.h"
#elif defined(XL32F030x4)
#include "xl32f030x4.h"
#elif defined(XL32F030x6)
#include "xl32f030x6.h"
#elif defined(XL32F030x7)
#include "xl32f030x7.h"
#elif defined(XL32F030x8)
#include "xl32f030x8.h"
#elif defined(XL32F003x4)
#include "xl32f003x4.h"
#elif defined(XL32F003x6)
#include "xl32f003x6.h"
#elif defined(XL32F003x8)
#include "xl32f003x8.h"
#elif defined(XL32F072xB)
#include "xl32f072xB.h"
#else
#error "Please select first the target XL32F0xx device used in your application (in xl32f0xx.h file)"
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */
typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  ERROR = 0,
  SUCCESS = !ERROR
} ErrorStatus;

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define HW32_REG(ADDRESS)     ( * ((volatile unsigned           int * )(ADDRESS)))

#define HW16_REG(ADDRESS)     ( * ((volatile unsigned short     int * )(ADDRESS)))

#define HW8_REG(ADDRESS)      ( * ((volatile unsigned          char * )(ADDRESS)))

/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "xl32f0xx_hal.h"
#endif /* USE_HAL_DRIVER */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __XL32F0xx_H */
/**
  * @}
  */

/**
  * @}
  */


/************************ (C) COPYRIGHT Xinling *****END OF FILE******************/


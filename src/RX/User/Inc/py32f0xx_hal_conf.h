/*定义以防止递归包含*/
#ifndef __PY32F0xx_HAL_CONF_H
#define __PY32F0xx_HAL_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif


/* ########################## 模块选择 ############################## */
/* HAL驱动程序中使用的模块列表 */
#define HAL_UART_MODULE_ENABLED//使能串口
#define HAL_MODULE_ENABLED  
#define HAL_RCC_MODULE_ENABLED//使能时钟
/* #define HAL_ADC_MODULE_ENABLED */
/* #define HAL_CRC_MODULE_ENABLED */
/* #define HAL_COMP_MODULE_ENABLED */
#define HAL_FLASH_MODULE_ENABLED   //使能FLASH
#define HAL_GPIO_MODULE_ENABLED    //使能GPIO
/* #define HAL_IWDG_MODULE_ENABLED */
/* #define HAL_WWDG_MODULE_ENABLED */
#define HAL_TIM_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED       //使能DMA
/* #define HAL_LPTIM_MODULE_ENABLED */
#define HAL_PWR_MODULE_ENABLED       //使能电源
/* #define HAL_I2C_MODULE_ENABLED */
/* #define HAL_UART_MODULE_ENABLED */
/* #define HAL_SPI_MODULE_ENABLED */
/* #define HAL_RTC_MODULE_ENABLED */
/* #define HAL_LED_MODULE_ENABLED */
/* #define HAL_EXTI_MODULE_ENABLED */
#define HAL_CORTEX_MODULE_ENABLED       //使能内核

/* ########################## 振荡器值自适应 ####################*/

/*内部高速时钟*/
#if !defined  (HSI_VALUE) 
  #define HSI_VALUE              ((uint32_t)8000000)     //内部高速时钟 值定义 单位Hz
#endif

/*外部高速时钟*/
#if !defined  (HSE_VALUE) 
  #define HSE_VALUE              ((uint32_t)24000000) //外部高速时钟 值定义 单位Hz
#endif

/*外部高速时钟启动时间*/
#if !defined  (HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    ((uint32_t)200)   /*外部高速时钟启动时间 值定义 单位ms*/
#endif

/*内部低速时钟*/
#if !defined  (LSI_VALUE) 
 #define LSI_VALUE               ((uint32_t)32768)    //内部低速时钟 值定义 单位Hz
#endif

/*外部低速时钟*/
#if !defined  (LSE_VALUE)
  #define LSE_VALUE              ((uint32_t)32768) //外部低速时钟 值定义 单位Hz
#endif /* LSE_VALUE */

/*外部低速时钟启动时间*/
#if !defined  (LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT    ((uint32_t)5000)   //外部低速时钟启动时间 值定义 单位ms
#endif /* LSE_STARTUP_TIMEOUT */


/* ########################### 系统配置 ######################### */
   
#define  VDD_VALUE               ((uint32_t)3300) //VDD值定义 单位mv           
#define  PRIORITY_HIGHEST        0
#define  PRIORITY_HIGH           1
#define  PRIORITY_LOW            2
#define  PRIORITY_LOWEST         3
#define  TICK_INT_PRIORITY       ((uint32_t)PRIORITY_LOWEST)    //时钟中断优先级(默认最低)        
#define  USE_RTOS                0
#define  PREFETCH_ENABLE         0

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT       1U */


/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include module's header file 
  */
#ifdef HAL_MODULE_ENABLED
 #include "py32f0xx_hal.h"
#endif /* HAL_MODULE_ENABLED */

#ifdef HAL_RCC_MODULE_ENABLED
 #include "py32f0xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_EXTI_MODULE_ENABLED
 #include "py32f0xx_hal_exti.h"
#endif /* HAL_EXTI_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
 #include "py32f0xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_CORTEX_MODULE_ENABLED
 #include "py32f0xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
  #include "py32f0xx_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
 #include "py32f0xx_hal_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_CRC_MODULE_ENABLED
 #include "py32f0xx_hal_crc.h"
#endif /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_COMP_MODULE_ENABLED
#include "py32f0xx_hal_comp.h"
#endif /* HAL_COMP_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
 #include "py32f0xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
 #include "py32f0xx_hal_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_IWDG_MODULE_ENABLED
 #include "py32f0xx_hal_iwdg.h"
#endif /* HAL_IWDG_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
 #include "py32f0xx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
 #include "py32f0xx_hal_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */    

#ifdef HAL_SPI_MODULE_ENABLED
 #include "py32f0xx_hal_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
 #include "py32f0xx_hal_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_LPTIM_MODULE_ENABLED
 #include "py32f0xx_hal_lptim.h" 
#endif /* HAL_LPTIM_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
 #include "py32f0xx_hal_uart.h"
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_WWDG_MODULE_ENABLED
 #include "py32f0xx_hal_wwdg.h"
#endif /* HAL_WWDG_MODULE_ENABLED */

#ifdef HAL_LED_MODULE_ENABLED
 #include "py32f0xx_hal_led.h"
#endif /* HAL_LED_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
 #include "py32f0xx_hal_usart.h"
#endif /* HAL_USART_MODULE_ENABLED */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed. 
  *         If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __PY32F0xx_HAL_CONF_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/

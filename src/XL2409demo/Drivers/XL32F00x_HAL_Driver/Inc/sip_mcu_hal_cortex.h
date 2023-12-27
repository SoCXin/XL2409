#ifndef __SIP_MCU_HAL_CORTEX_H
#define __SIP_MCU_HAL_CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "sip_mcu_hal_def.h"


/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup CORTEX_Exported_Constants CORTEX Exported Constants
  * @{
  */

/** @defgroup CORTEX_SysTick_clock_source CORTEX SysTick clock source
  * @{
  */
#define SYSTICK_CLKSOURCE_HCLK_DIV8       0x00000000U
#define SYSTICK_CLKSOURCE_HCLK            0x00000004U











/* Exported macros -----------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Macros CORTEX Exported Macros
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Functions CORTEX Exported Functions
  * @{
  */

/** @defgroup CORTEX_Exported_Functions_Group1 Initialization and Configuration functions
 *  @brief    Initialization and Configuration functions
 * @{
 */
/* Initialization and Configuration functions *****************************/
void HAL_NVIC_SetPriority(IRQn_Type IRQn,uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);
/**
  * @}
  */

/** @defgroup CORTEX_Exported_Functions_Group2 Peripheral Control functions
 *  @brief   Cortex control functions
 * @{
 */
/* Peripheral Control functions *************************************************/
uint32_t HAL_NVIC_GetPriority(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);



/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup CORTEX_Private_Macros CORTEX Private Macros
  * @{
  */
#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)     ((PRIORITY) < 0x4U)

#define IS_NVIC_DEVICE_IRQ(IRQ)                   ((IRQ) > SysTick_IRQn)

#define IS_SYSTICK_CLK_SOURCE(SOURCE)             (((SOURCE) == SYSTICK_CLKSOURCE_HCLK) || \
                                                   ((SOURCE) == SYSTICK_CLKSOURCE_HCLK_DIV8))



/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SIP_MCU_HAL_CORTEX_H */





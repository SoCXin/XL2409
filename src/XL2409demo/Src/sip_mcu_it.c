/**
  ******************************************************************************
  * @file    sip_mcu_it.c
  * @author  MCU SYSTEM Team
  * @Version V1.0.0
  * @Date    2020-10-19
  * @brief   Interrupt Service Routines.
  ******************************************************************************

  */

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "sip_mcu_it.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
extern   TIM_HandleTypeDef  TimHandle;
extern   UART_HandleTypeDef UartHandle;

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {

  }
}


/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}


/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  //HAL_TIM_IRQHandler(&TimHandle);
}

void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle);
}


/******************************************************************************/
/* sip_mcu Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_xl110x.s).                    */
/******************************************************************************/



/**
  ******************************************************************************
  * @file    xl32f0xx_it.c
  * @author  MCU Application Team
  * @Version V1.0.0
  * @Date    2020-10-19
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "xl32f0xx_it.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers         */
/******************************************************************************/
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
}

/******************************************************************************/
/* XL32F0xx Peripheral Interrupt Handlers                                     */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_xl32f003xx.s).                   */
/******************************************************************************/

/**
  * @brief This function handles DMA channel 1 interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  APP_DmaChannel1IRQCallback();
}

/**
  * @brief This function handles DMA channel 1, channel 2 interrupt.
  */
void DMA1_Channel2_3_IRQHandler(void)
{
  APP_DmaChannel2_3_IRQCallback();
}

/**
  * @brief This function handles USART1 interrupt.
  */
void USART1_IRQHandler(void)
{   
  APP_UsartIRQCallback(USART1);
}

/**
  * @brief This function handles USART2 interrupt.
  */
void USART2_IRQHandler(void)
{
  APP_UsartIRQCallback(USART2);
}

/************************ (C) COPYRIGHT Xinling *****END OF FILE****/

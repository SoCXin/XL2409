#include "User_System_Clock.h"

void System_Clock_Init(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* 配置时钟源HSI */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                                       /* 开启HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                                       /* 不分频 */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_24MHz;                              /* 配置HSI输出时钟为24MHz */

  HAL_RCC_OscConfig(&RCC_OscInitStruct);                                           /* 初始化RCC振荡器 */

  /* 初始化CPU,AHB,APB总线时钟 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;  /* RCC系统时钟类型 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                                          /* SYSCLK的源选择为HSI */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                              /* APH时钟不分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                                               /* APB时钟不分频 */

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);                         /* 初始化RCC系统时钟(FLASH_LATENCY_0=24M以下;FLASH_LATENCY_1=48M) */
}





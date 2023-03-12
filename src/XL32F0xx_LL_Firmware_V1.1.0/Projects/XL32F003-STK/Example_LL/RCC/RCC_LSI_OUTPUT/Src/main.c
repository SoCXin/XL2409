/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @Version V1.0.0
  * @Date    2022-8-19
  * @brief   main function
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void GPIO_Config(void);

/*******************************************************************************
**功能描述 ：执行函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
int main(void)
{
  /*时钟初始化,配置系统时钟为LSI*/
  SystemClock_Config();
  
  /*引脚输出初始化*/
  GPIO_Config();
  
  /*MCO输出时钟及分频初始化*/
  LL_RCC_ConfigMCO(LL_RCC_MCO1SOURCE_SYSCLK,LL_RCC_MCO1_DIV_1);
  
  while (1)
  {
  }
}

/*******************************************************************************
**功能描述 ：系统时钟配置函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void SystemClock_Config(void)
{
  
  /* LSI使能及初始化 */
  LL_RCC_LSI_Enable();
  while(LL_RCC_LSI_IsReady() != 1)
  {
  }
  
  /* 设置AHB分频*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  
  /* 配置LSI为系统时钟及初始化 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_LSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_LSI)
  {
  }
  
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  
  /*设置APB1分频及初始化*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(24000000);
}

/*******************************************************************************
**功能描述 ：配置PA01为MCO复用功能
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void GPIO_Config(void)
{
  /* GPIOA时钟使能*/
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  
  /* 配置PA01为复用模式，并复用为MCO输出引脚*/
  LL_GPIO_InitTypeDef GPIO_InitStruct;  
  /* 选择1号引脚*/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_1; 
  /* 配置为复用模式*/	
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE; 
  /* 选择复用为AF15功能*/	
  GPIO_InitStruct.Alternate = LL_GPIO_AF15_MCO;     
  /* 输出速度选择*/	
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;   
  /* 输出模式选择*/
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  /* 无上下拉*/	
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;                
  
  /* 初始化GPIOA*/
  LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
}

/*******************************************************************************
**功能描述 ：错误执行函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void Error_Handler(void)
{
}

#ifdef  USE_FULL_ASSERT
/*******************************************************************************
**功能描述 ：输出产生断言错误的源文件名及行号
**输入参数 ：file：源文件名指针
**输入参数 ：line：发生断言错误的行号
**输出参数 ：
*******************************************************************************/
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Xinling *****END OF FILE****/

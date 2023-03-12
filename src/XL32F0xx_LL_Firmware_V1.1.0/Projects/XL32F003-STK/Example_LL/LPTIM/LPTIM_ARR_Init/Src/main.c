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
#include "xl32f003xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void APP_ConfigLPTIM_OneShot(void);
void APP_LPTIMCallback(void);

/*******************************************************************************
**功能描述 ：执行函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
int main(void)
{
  /*使能LPTIM时钟*/
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPTIM1);
  
  /*配置系统时钟*/
  SystemClock_Config();
  
  /*初始化LED*/  
  BSP_LED_Init(LED3);
  
  /*配置并开启LPTIM*/
  APP_ConfigLPTIM_OneShot();
  
  while (1)
  {
  }
}

/*******************************************************************************
**功能描述 ：配置LPTIM单次模式
**输入参数 ：
**输出参数 ：
**    备注 ：默认使用APB时钟作为LPTIM时钟源
*******************************************************************************/
void APP_ConfigLPTIM_OneShot(void)
{
  /*配置LPTIM*/
  /*LPTIM预分频器64分频*/
  LL_LPTIM_SetPrescaler(LPTIM1,LL_LPTIM_PRESCALER_DIV64);
  
  /*LPTIM计数周期结束更新ARR*/
  LL_LPTIM_SetUpdateMode(LPTIM1,LL_LPTIM_UPDATE_MODE_ENDOFPERIOD);
  
  /*使能ARR中断*/
  LL_LPTIM_EnableIT_ARRM(LPTIM1);
  
  /*使能LPTIM*/
  LL_LPTIM_Enable(LPTIM1);
  
  /*配置重装载值：62500*/
  /*8000000/64/62500 = 2Hz*/
  LL_LPTIM_SetAutoReload(LPTIM1,62500);
  
  /*开启单次模式*/
  LL_LPTIM_StartCounter(LPTIM1,LL_LPTIM_OPERATING_MODE_ONESHOT);
  
  /*使能NVIC请求*/
  NVIC_EnableIRQ(LPTIM1_IRQn);
  NVIC_SetPriority(LPTIM1_IRQn,0);
}

/*******************************************************************************
**功能描述 ：LPTIM ARR中断回调函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void APP_LPTIMCallback(void)
{
  /*翻转LED*/
  BSP_LED_Toggle(LED3);
  
  /*开启单次模式*/
  LL_LPTIM_StartCounter(LPTIM1,LL_LPTIM_OPERATING_MODE_ONESHOT);
}

/*******************************************************************************
**功能描述 ：系统时钟配置函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void SystemClock_Config(void)
{
  /* 使能HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* 设置 AHB 分频*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* 配置HSISYS作为系统时钟源 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* 设置 APB1 分频*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);
  
  /* 更新系统时钟全局变量SystemCoreClock(也可以通过调用SystemCoreClockUpdate函数更新) */
  LL_SetSystemCoreClock(8000000);
}

/*******************************************************************************
**功能描述 ：错误执行函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void Error_Handler(void)
{
  while(1)
  {
  }
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

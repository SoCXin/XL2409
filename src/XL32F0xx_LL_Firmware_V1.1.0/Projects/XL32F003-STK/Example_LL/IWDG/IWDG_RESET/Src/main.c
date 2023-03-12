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
void SystemClock_Config(void);
void IWDG_Config(void);
/* Private user code ---------------------------------------------------------*/

/*******************************************************************************
**功能描述 ：执行函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
int main(void)
{
  /*时钟初始化,配置系统时钟为HSI*/
  SystemClock_Config();

  /*LED初始化*/
  BSP_LED_Init(LED3);

  /*IWDG配置*/
  IWDG_Config();

  while (1)
  {
    /*延时时间*/
		LL_mDelay(900);
		//LL_mDelay(1100);

    /*LED翻转*/
    BSP_LED_Toggle(LED3);

    /*喂狗*/
    LL_IWDG_ReloadCounter(IWDG);
  }
}

/*******************************************************************************
**功能描述 ：系统时钟初始化
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void SystemClock_Config(void)
{
  /* HSI使能及初始化 */
  LL_RCC_HSI_Enable();
  while (LL_RCC_HSI_IsReady() != 1)
  {
  }


  /* 设置AHB分频*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* 配置HSISYS为系统时钟及初始化 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  /*设置APB1分频及初始化*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(8000000);
}

/*******************************************************************************
**功能描述 ：iwdg配置
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void IWDG_Config(void)
{
  /* 使能LSI */
  LL_RCC_LSI_Enable();
  while (LL_RCC_LSI_IsReady() == 0U) {;}

  /* 使能IWDG */
  LL_IWDG_Enable(IWDG);
  /* 开启写权限 */
  LL_IWDG_EnableWriteAccess(IWDG);
  /* 设置IWDG分频 */
  LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_32); // T=1MS
  /* 设置喂狗事件*/
  LL_IWDG_SetReloadCounter(IWDG, 1000); // 1ms*1000=1s
  /* IWDG初始化*/
  while (LL_IWDG_IsReady(IWDG) == 0U) {;}
  /*喂狗*/
  LL_IWDG_ReloadCounter(IWDG);
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

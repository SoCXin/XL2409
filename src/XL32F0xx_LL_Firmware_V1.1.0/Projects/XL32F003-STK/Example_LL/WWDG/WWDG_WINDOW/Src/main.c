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
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void LED_Init(void);
void LED_Toggle(void);
void WWDG_Config(void);
static uint32_t TimeoutCalculation(uint32_t timevalue);

/*******************************************************************************
**功能描述 ：执行函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
int main(void)
{
  /*PWR时钟使能*/
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  /*时钟初始化,配置系统时钟为HSI*/
  SystemClock_Config();

  /*KED初始化*/
  LED_Init();
  
  /*IWDG配置*/
  WWDG_Config();
  
  /*延时时间计算*/
  uint32_t delay = TimeoutCalculation(((0x7F-0x50) + 1) + 1);
  
  while (1)
  {
    /*LED翻转*/
    LED_Toggle();
    /*延时时间*/
    LL_mDelay(delay);
    /*喂狗*/
    LL_WWDG_SetCounter(WWDG, 0x7F);

  }
}

/*******************************************************************************
**功能描述 ：系统时钟配置函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void SystemClock_Config(void)
{
  /* HSI使能及初始化 */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }
  
  /* 设置AHB分频*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  
  /* 配置HSISYS为系统时钟及初始化 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
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
**功能描述 ：配置LED初始化
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void LED_Init(void)
{
  /* 使能GPIOB时钟 */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  /* 配置PA11做输出引脚 */
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
  
}

/*******************************************************************************
**功能描述 ：配置LED翻转
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void LED_Toggle(void)
{
  LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_5); 
}

/*******************************************************************************
**功能描述 ：WWDG配置
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void WWDG_Config(void)
{
  /* 使能WWDG时钟 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_WWDG);
  
  /*设置计数器*/
  LL_WWDG_SetCounter(WWDG, 0x7F);
  /*设置分频*/
  LL_WWDG_SetPrescaler(WWDG, LL_WWDG_PRESCALER_8);
  /*设置窗口值*/
  LL_WWDG_SetWindow(WWDG, 0x50);
  /* 使能WWDG */
  LL_WWDG_Enable(WWDG);
}

/*******************************************************************************
**功能描述 ：超时函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static uint32_t TimeoutCalculation(uint32_t timevalue)
{
  uint32_t timeoutvalue = 0;
  LL_RCC_ClocksTypeDef RCC_Clocks;
  uint32_t pclk1 = 0;
  uint32_t wdgtb = 0;

  /*获取HCLK频率*/
  LL_RCC_GetSystemClocksFreq(&RCC_Clocks);
  pclk1 = RCC_Clocks.PCLK1_Frequency;

  /* 获得分频*/
  wdgtb = (1 << ((LL_WWDG_PRESCALER_8) >> 7)); /* 2^WDGTB[1:0] */

  /* 计算时间 */
  timeoutvalue = ((4096 * wdgtb * timevalue) / (pclk1 / 1000));

  return timeoutvalue;
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

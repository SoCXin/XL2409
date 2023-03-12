/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Configure_EXTI(void);
void Enter_Sleep(void);
void GPIO_Config(void);
static void APP_LED_run(void);

/*******************************************************************************
**功能描述 ：执行函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
int main(void)
{

  /*时钟初始化,配置系统时钟为HSI*/
  SystemClock_Config();

  /*配置PB05输出*/
  GPIO_Config();
  
  /*外部中断初始化*/
  Configure_EXTI();
  
  /*LED亮*/
  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
  /*延时200ms*/
  LL_mDelay(200);
  /*LED灭*/
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
  
  /*进入SLEEP模式*/
  Enter_Sleep();
  
  while (1)
  {
      APP_LED_run();
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
  LL_RCC_HSI_SetCalibFreq(LL_RCC_HSICALIBRATION_24MHz);
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
  LL_Init1msTick(24000000);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(24000000);
}

/*******************************************************************************
**功能描述 ：配置外部中断
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void Configure_EXTI(void)
{
   /*GPIOA时钟使能*/
   LL_IOP_GRP1_EnableClock (LL_IOP_GRP1_PERIPH_GPIOA);
  
   LL_GPIO_InitTypeDef GPIO_InitStruct;
   /*选择PA06引脚*/
   GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
   /*选择输入模式*/
   GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
   /*选择下拉*/
   GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
   /*GPIOA初始化*/
   LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	 /*选择EXTI6做外部中断输入*/
   LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA,LL_EXTI_CONFIG_LINE6);

   LL_EXTI_InitTypeDef EXTI_InitStruct;
   /*选择EXTI6*/
   EXTI_InitStruct.Line = LL_EXTI_LINE_6;
   /*使能*/
   EXTI_InitStruct.LineCommand = ENABLE;
   /*选择中断模式*/
   EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
   /*选择上升沿触发*/
   EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
   /*外部中断初始化*/
   LL_EXTI_Init(&EXTI_InitStruct);
   
   /*设置中断优先级*/
   NVIC_SetPriority(EXTI4_15_IRQn,1);
   /*使能中断*/
   NVIC_EnableIRQ(EXTI4_15_IRQn);
 	
}

/*******************************************************************************
**功能描述 ：进入SLEEP模式
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void Enter_Sleep(void)
{
  /*使能PWR时钟*/
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  
  /*进入Sleep模式*/
  LL_LPM_EnableSleep();
  
  /*等待中断指令*/
  __WFI();
}

/*******************************************************************************
**功能描述 ：LED运行配置
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_LED_run(void)
{
  /*翻转LED灯*/
  LL_GPIO_TogglePin(GPIOB ,LL_GPIO_PIN_5);
  /*延时200ms*/
  LL_mDelay(200);
  /*翻转LED灯*/
  LL_GPIO_TogglePin(GPIOB ,LL_GPIO_PIN_5);
  /*延时200ms*/
  LL_mDelay(200);
}

/*******************************************************************************
**功能描述 ：GPIO配置
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void GPIO_Config(void)
{
  /* GPIOB时钟使能*/
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  
  /* 配置PB05为输出模式*/
  LL_GPIO_InitTypeDef GPIO_InitStruct;  
  /* 选择5号引脚*/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_5; 
  /* 配置为输出模式*/	
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;    
  /* 输出速度选择*/	
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;   
  /* 输出模式选择*/
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  /* 无上下拉*/	
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;                
  
  /* 初始化GPIOB*/
  LL_GPIO_Init(GPIOB,&GPIO_InitStruct);
  
  /*LED灭*/
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
    
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

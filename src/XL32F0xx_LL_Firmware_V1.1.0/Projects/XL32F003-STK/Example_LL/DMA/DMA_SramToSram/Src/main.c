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
#define BUFFER_SIZE              32
/* Private variables ---------------------------------------------------------*/
uint32_t aSRC_Const_Buffer[BUFFER_SIZE];       /* 数据传输源buffer */
uint32_t aDST_Buffer[BUFFER_SIZE];             /* 数据传输目标buffer */
__IO uint32_t transferErrorDetected=0;    /* 当发生传输错误时，该位置1 */
__IO uint32_t transferCompleteDetected=0; /* 当传输完成时，该位置1 */
/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);
static void APP_DMA_Config(void);
void SystemClock_Config(void);
/*******************************************************************************
**功能描述 ：执行函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
int main(void)
{
  /* 配置系统时钟 */
  SystemClock_Config();
  /* 初始化LED(PA11)*/
  BSP_LED_Init(LED_GREEN);
  // 给DMA 源buffer初始化数据
  for(uint8_t i=0; i<BUFFER_SIZE; i++)
  {
    aSRC_Const_Buffer[i]=i;
  }

  /* DMA模块配置*/
  APP_DMA_Config();

  /* LED灯初始状态为常亮*/
  BSP_LED_On(LED_GREEN);



  while (1)
  {
    /*如果产生传输错误，LED灯熄灭*/
    if (transferErrorDetected == 1)
    {
      /*LED熄灭*/
      BSP_LED_Off(LED_GREEN);
      /*清除错误标志位*/
      transferErrorDetected = 0;
    }
    /*如果传输完成，则LED灯闪烁*/
    else if (transferCompleteDetected == 1)
    {
      /*LED翻转*/
      BSP_LED_Toggle(LED_GREEN);
      LL_mDelay(200);
    }
  }
}


/*******************************************************************************
**功能描述 ：DMA配置函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_DMA_Config(void)
{
  LL_DMA_InitTypeDef dma_initstruct;

  /* 使能DMA时钟 */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  /* 配置 DMA 功能参数*/
  dma_initstruct.PeriphOrM2MSrcAddress  = (uint32_t)&aSRC_Const_Buffer;
  dma_initstruct.MemoryOrM2MDstAddress  = (uint32_t)&aDST_Buffer;
  dma_initstruct.Direction              = LL_DMA_DIRECTION_MEMORY_TO_MEMORY;
  dma_initstruct.Mode                   = LL_DMA_MODE_NORMAL;
  dma_initstruct.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_INCREMENT;
  dma_initstruct.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;
  dma_initstruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_WORD;
  dma_initstruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_WORD;
  dma_initstruct.NbData                 = BUFFER_SIZE;
  dma_initstruct.Priority               = LL_DMA_PRIORITY_HIGH;
  if (LL_DMA_Init(DMA1, LL_DMA_CHANNEL_1, &dma_initstruct) != SUCCESS)
  {
    Error_Handler();
  }

  /* 使能中断 */
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
  LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_1);
  NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);

  /* 使能DMA */
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
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

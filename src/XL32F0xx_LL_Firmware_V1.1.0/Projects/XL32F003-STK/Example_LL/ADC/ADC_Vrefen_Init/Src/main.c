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
#define ADC_DELAY_CALIB_ENABLE_CPU_CYCLES  (LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES * 32)
#define VAR_CONVERTED_DATA_INIT_VALUE    (__LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B) + 1)

/* Private variables ---------------------------------------------------------*/
__IO uint32_t ubUserButtonPressed = 0;
__IO uint16_t uhADCxConvertedData = VAR_CONVERTED_DATA_INIT_VALUE;
__IO uint16_t uhADCxConvertedData_Voltage_mVolt = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void APP_Configure_ADC(void);
static void APP_Activate_ADC(void);

/*******************************************************************************
**功能描述 ：执行函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
int main(void)
{
  /* 配置系统时钟 */
  SystemClock_Config();
  /* 初始化调试串口(printf使用) */
  BSP_USART_Config();
  /*配置ADC相关参数*/
  APP_Configure_ADC();
  /* 激活ADC */
  APP_Activate_ADC();
  /*开始ADC转换(如果是软件触发则直接开始转换*/
  LL_ADC_REG_StartConversion(ADC1);
  while (1)
  {
    if(LL_ADC_IsActiveFlag_EOS(ADC1))
    {
      LL_ADC_ClearFlag_EOS(ADC1);
       /* 获取ADC转换数据 */
      uhADCxConvertedData = LL_ADC_REG_ReadConversionData12(ADC1);

      /* 将ADC原始数据转换为物理值 */
      uhADCxConvertedData_Voltage_mVolt=__LL_ADC_CALC_VREFANALOG_VOLTAGE(uhADCxConvertedData, LL_ADC_RESOLUTION_12B);
    
      /* 打印当前VCC值 */
      printf("%d mv\r\n",uhADCxConvertedData_Voltage_mVolt);
      LL_mDelay(200);
    }
  }
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
**功能描述 ：ADC配置函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_Configure_ADC(void)
{
  LL_ADC_InitTypeDef ADC_Init;
  LL_ADC_REG_InitTypeDef LL_ADC_REG_InitType;
  ADC_Common_TypeDef ADC_Common_Type;
  /*ADC复位*/
  LL_ADC_Reset(ADC1);
  /*ADC模块时钟使能*/
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);
  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /*ADC部分功能初始化*/
    ADC_Init.Clock=LL_ADC_CLOCK_SYNC_PCLK_DIV64;
    ADC_Init.DataAlignment=LL_ADC_DATA_ALIGN_RIGHT;
    ADC_Init.LowPowerMode=LL_ADC_LP_MODE_NONE;
    ADC_Init.Resolution=LL_ADC_RESOLUTION_12B;
    LL_ADC_Init(ADC1,&ADC_Init);
    /* 设置通道转换时间 */
    LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_239CYCLES_5);
  }
  if ((LL_ADC_IsEnabled(ADC1) == 0)               ||
      (LL_ADC_REG_IsConversionOngoing(ADC1) == 0)   )
  {
    /*ADC结构功能初始化*/
    LL_ADC_REG_InitType.ContinuousMode=LL_ADC_REG_CONV_CONTINUOUS;
    LL_ADC_REG_InitType.DMATransfer=LL_ADC_REG_DMA_TRANSFER_NONE;
    LL_ADC_REG_InitType.Overrun=LL_ADC_REG_OVR_DATA_OVERWRITTEN;
    LL_ADC_REG_InitType.SequencerDiscont=LL_ADC_REG_SEQ_DISCONT_DISABLE;
    LL_ADC_REG_InitType.TriggerSource=LL_ADC_REG_TRIG_SOFTWARE;
    LL_ADC_REG_Init(ADC1,&LL_ADC_REG_InitType);
    /*ADC共用参数设置*/
    LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1),LL_ADC_PATH_INTERNAL_VREFINT);
    /* 设置通道12为转换通道      */
    LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_VREFINT);
  }
}

/*******************************************************************************
**功能描述 ：ADC激活函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_Activate_ADC(void)
{
  __IO uint32_t wait_loop_index = 0;
#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 0; /* Variable used for timeout management */
#endif /* USE_TIMEOUT */

  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* 使能校准 */
    LL_ADC_StartCalibration(ADC1);

#if (USE_TIMEOUT == 1)
    Timeout = ADC_CALIBRATION_TIMEOUT_MS;
#endif /* USE_TIMEOUT */

    while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0)
    {
#if (USE_TIMEOUT == 1)
      /* 检测校准是否超时 */
      if (LL_SYSTICK_IsActiveCounterFlag())
      {
        if(Timeout-- == 0)
        {

        }
      }
#endif /* USE_TIMEOUT */
    }

    /* ADC校准结束和使能ADC之间的延时                   */
    wait_loop_index = (ADC_DELAY_CALIB_ENABLE_CPU_CYCLES >> 1);
    while(wait_loop_index != 0)
    {
      wait_loop_index--;
    }

    /* 使能ADC */
    LL_ADC_Enable(ADC1);
  }
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

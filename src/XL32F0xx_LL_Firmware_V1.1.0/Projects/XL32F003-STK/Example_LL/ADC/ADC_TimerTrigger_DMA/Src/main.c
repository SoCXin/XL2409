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
#define ADC_CALIBRATION_TIMEOUT_MS ((uint32_t) 1)
#define VDDA_APPLI                       ((uint32_t)3300)
#define VAR_CONVERTED_DATA_INIT_VALUE    (__LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B) + 1)
#define ADC_DELAY_CALIB_ENABLE_CPU_CYCLES  (LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES * 32)
/*DMA传输的目标源*/
static uint32_t ADCxConvertedDatas;

/* Private variables ---------------------------------------------------------*/
__IO uint32_t ubUserButtonPressed = 0;
__IO uint16_t uhADCxConvertedData = VAR_CONVERTED_DATA_INIT_VALUE;
__IO uint16_t uhADCxConvertedData_Voltage_mVolt = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void APP_Activate_ADC(void);
static void APP_ConfigureADC(void);
static void APP_Timer1Init(void);
static void APP_DMAConfig(void);

/*******************************************************************************
**功能描述 ：执行函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
int main(void)
{
  /* 配置系统时钟 */
  SystemClock_Config();

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  /* 初始化按键BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* 初始化调试串口(printf使用) */
  BSP_USART_Config();

  /* 配置DMA */
  APP_DMAConfig();

  /* 使能DMA */
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);

  /* 复位ADC*/
  LL_ADC_Reset(ADC1);

  /* 配置ADC参数 */
  APP_ConfigureADC();
 
  /* 激活ADC */
  APP_Activate_ADC();
 
  /* 开始ADC转换(如果是软件触发则直接开始转换) */
  LL_ADC_REG_StartConversion(ADC1);

  /* TIM1初始化*/
  APP_Timer1Init();
  while (1)
  {
    /* LED灯闪烁 */
    BSP_LED_Toggle(LED_GREEN);
    LL_mDelay(1000);
    /* 使能ADC */
    LL_ADC_Enable(ADC1);
    /* 开始ADC转换 */
    LL_ADC_REG_StartConversion(ADC1);
  }
}

/*******************************************************************************
**功能描述 ：ADC配置函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_ConfigureADC(void)
{
  /*## 配置ADC通道和管脚 ############################*/

  /* 注意: 在XL32系列中，ADC 通道4对应 GPIOA4 */

  /* 使能GPIOA时钟 */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* 配置管脚4为模拟输入 */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG);

  /* 使能ADC1时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);

  if(__LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE() == 0)
  {
    /* 配置内部转换通道 */
    LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_NONE);
  }
  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* 设置ADC时钟 */
    LL_ADC_SetClock(ADC1, LL_ADC_CLOCK_SYNC_PCLK_DIV2);

    /* 设置12位分辨率 */
    LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);

    /* 设置数据右对齐 */
    LL_ADC_SetResolution(ADC1, LL_ADC_DATA_ALIGN_RIGHT);

    /* 设置低功率模式无 */
    LL_ADC_SetLowPowerMode(ADC1, LL_ADC_LP_MODE_NONE);

    /* 设置通道转换时间 */
    LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_41CYCLES_5);

  }
  if ((LL_ADC_IsEnabled(ADC1) == 0)               ||
      (LL_ADC_REG_IsConversionOngoing(ADC1) == 0)   )
  {
    /* 设置触发源为TIM1 TRGO */
    LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_EXT_TIM1_TRGO);

    /* 设置上升沿触发转换 */
    LL_ADC_REG_SetTriggerEdge(ADC1, LL_ADC_REG_TRIG_EXT_RISING);

    /* 设置转换模式为单次转换 */
    LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);

    /* 设置DMA模式为循环模式，并开启 */
    LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);

    /* 设置过载管理模式为覆盖上一个值 */
    LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

    /* 设置不连续模式为不使能 */
    LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);

    /* 设置通道4为转换通道      */
    LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_4);
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
  uint32_t Timeout = 0;
#endif

  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* 使能校准 */
    LL_ADC_StartCalibration(ADC1);

#if (USE_TIMEOUT == 1)
    Timeout = ADC_CALIBRATION_TIMEOUT_MS;
#endif

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
#endif
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
**功能描述 ：TIM1配置函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_Timer1Init(void)
{
  /* 使能TIM1时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);

  /* 设置TIM1预分频器 */
  LL_TIM_SetPrescaler(TIM1,2000);

  /* 设置TIM1自动重装载值 */
  LL_TIM_SetAutoReload(TIM1, 4000);

  /* 设置TIM1更新触发 */
  LL_TIM_SetTriggerOutput(TIM1,LL_TIM_TRGO_UPDATE);

  /* 使能TIM1 */
  LL_TIM_EnableCounter(TIM1);
}

/*******************************************************************************
**功能描述 ：DMA配置函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_DMAConfig(void)
{
  /* 使能DMA1 时钟 */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  
  /* 使能syscfg 时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
 
  /* ADC对应通道LL_DMA_CHANNEL_1 */
  SET_BIT(SYSCFG->CFGR3, 0x0);

  /* 配置DMA传输方向为外设到存储器 */
  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  /* 配置DMA优先级为高 */
  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);

  /* 配置DMA循环模式 */
  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);

  /* 配置DMA外设地址不变模式 */
  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);

  /* 配置DMA存储地址不变模式 */
  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_NOINCREMENT);

  /* 配置DMA外设传输方式为字 */
  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_WORD);

  /* 配置DMA存储器传输方式为字 */
  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_WORD);

  /* 配置DMA传输长度为1 */
  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 1);

  /* 配置DMA外设和存储器的地址 */
  LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&ADC1->DR, (uint32_t)&ADCxConvertedDatas, LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1));

  /* 使能DMA传输完成中断 */
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);

  NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

/*******************************************************************************
**功能描述 ：DMA传输完成函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void APP_TransferCompleteCallback(void)
{
  /*将ADC的采样值转换为电压值*/
  uhADCxConvertedData_Voltage_mVolt = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, ADCxConvertedDatas, LL_ADC_RESOLUTION_12B);
  printf("%s%s%d mV\r\n","Channel4","Voltage:",uhADCxConvertedData_Voltage_mVolt);
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

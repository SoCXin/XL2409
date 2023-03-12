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
/* 发送缓冲区*/
uint8_t aTxBuffer[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
uint8_t ubNbDataToTransmit = sizeof(aTxBuffer);
uint8_t ubTransmitIndex = 0;

/* 接收缓冲区 */
uint8_t aRxBuffer[sizeof(aTxBuffer)] = {0};
uint8_t ubNbDataToReceive = sizeof(aTxBuffer);
uint8_t ubReceiveIndex = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void APP_ConfigSpi(void);
static void APP_WaitAndCheckEndOfTransfer(void);
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);
static void APP_LedBlinking(void);

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
  
  /* 配置SPI */
  APP_ConfigSpi();

  /* 使能 SPI1 */
  LL_SPI_Enable(SPI1);
  
  /* 等待传输结束并检查接收到的数据 */
  /* LED 在等待期间快速闪烁 */
  APP_WaitAndCheckEndOfTransfer();

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

/*******************************************************************************
**功能描述 ：SPI配置函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_ConfigSpi(void)
{
  LL_SPI_InitTypeDef SPI_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* 使能时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SPI1);

  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  /**SPI1 引脚配置
  PA1   ------> SPI1_SCK
  PA2   ------> SPI1_MOSI
  PA6   ------> SPI1_MISO
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* SPI1 中断配置 */
  NVIC_SetPriority(SPI1_IRQn, 1);
  NVIC_EnableIRQ(SPI1_IRQn);

  /* SPI1 参数配置*/
  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_SLAVE;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV128;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  LL_SPI_Init(SPI1, &SPI_InitStruct);

  /* 配置 SPI1 FIFO 阈值 */
  LL_SPI_SetRxFIFOThreshold(SPI1, LL_SPI_RX_FIFO_TH_QUARTER);
  
  /* 配置 SPI1 传输中断 */
  LL_SPI_EnableIT_TXE(SPI1);
  LL_SPI_EnableIT_RXNE(SPI1);
  LL_SPI_EnableIT_ERR(SPI1);
}

/*******************************************************************************
**功能描述 ：SPI1接收回调函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void  APP_SpiRxCallback(void)
{
  /* 读取数据寄存器中的字符。
     通过读取 DR 寄存器中的数据清除 RXNE 标志 */
  aRxBuffer[ubReceiveIndex++] = LL_SPI_ReceiveData8(SPI1);
}

/*******************************************************************************
**功能描述 ：SPI1发送回调函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void  APP_SpiTxCallback(void)
{
  /* 在数据寄存器中写入字符。
     通过读取 DR 寄存器中的数据清除 TXE 标志 */
  LL_SPI_TransmitData8(SPI1, aTxBuffer[ubTransmitIndex++]);
}

/*******************************************************************************
**功能描述 ：SPI1传输错误回调函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void APP_SpiTransferErrorCallback(void)
{
  /* 关 RXNE  中断             */
  LL_SPI_DisableIT_RXNE(SPI1);

  /* 关 TXE   中断             */
  LL_SPI_DisableIT_TXE(SPI1);

  /* 将 LED 设置为闪烁模式以指示发生错误 */
  APP_LedBlinking();
}

/*******************************************************************************
**功能描述 ：SPI1等待传输完成，并校验数据
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_WaitAndCheckEndOfTransfer(void)
{
  /* 1 - 等待传输结束 */
  while (ubTransmitIndex != ubNbDataToTransmit)
  {
  }
  /* 关 TXE 中断 */
  LL_SPI_DisableIT_TXE(SPI1);

  /* 2 - 等待接收结束 */
  while (ubNbDataToReceive > ubReceiveIndex)
  {
  }
  /* 关 RXNE 中断 */
  LL_SPI_DisableIT_RXNE(SPI1);

  /* 3 - 比较发送数据和接收数据 */
  if(APP_Buffercmp8((uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, ubNbDataToTransmit))
  {
    /* 错误处理 */
    APP_LedBlinking();
  }
  else
  {
    /* 如果数据接收到，则打开 LED */
    BSP_LED_On(LED_GREEN);
  }
}

/*******************************************************************************
**功能描述 ：字符比较函数
**输入参数 ：pBuffer1：待比较缓冲区1
**           pBuffer2：待比较缓冲区2
**           BufferLength：待比较字符的个数
**输出参数 ：
*******************************************************************************/
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }
    pBuffer1++;
    pBuffer2++;
  }
  return 0;
}

/*******************************************************************************
**功能描述 ：LED灯闪烁
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_LedBlinking(void)
{
  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);; 
    LL_mDelay(200);
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

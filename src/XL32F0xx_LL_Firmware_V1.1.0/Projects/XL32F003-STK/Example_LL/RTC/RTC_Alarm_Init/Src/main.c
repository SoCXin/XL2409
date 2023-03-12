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
/* 定义与时钟配置相关的 */
#define RTC_ASYNCH_PREDIV          ((uint32_t)0x7FFF)

/* Private variables ---------------------------------------------------------*/
/* 时间结构体及其变量 */
struct time_t
{
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
};
struct time_t RTC_TimeStruct;
struct time_t RTC_AlarmStruct;
/* 日期结构体及其变量 */
struct date_t
{
  uint8_t month;
  uint8_t day;
  uint8_t year;
};
struct date_t RTC_DateStruct;
uint8_t EndOfMonth[12]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/* 用于显示时间和日期的缓冲区 */
uint32_t TimeCounter = 0;
uint8_t aShowTime[50] = {0};
uint8_t aShowDate[50] = {0};

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void APP_ConfigRtc(void);
static void APP_ConfigRtcAlarm(void);
static void APP_ConfigRtcDate(uint8_t ,uint8_t , uint8_t);
static void APP_ShowRtcCalendar(void);
static void APP_UpadateRtcTimeStruct(void);
static void APP_UpadateRtcDateStruct(void);

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
  
  /* 关闭小灯 */
  BSP_LED_Off(LED_GREEN);

  /* 配置RTC外设 */
  APP_ConfigRtc();

  /* 配置RTC闹钟 */
  APP_ConfigRtcAlarm();

  while (1)
  {
    /* 更新并显示时间和日期 */
    APP_ShowRtcCalendar();
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
**功能描述 ：配置RTC时钟
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_ConfigRtc(void)
{
  LL_RTC_InitTypeDef rtc_initstruct;
  
  /*##-1- 启用 PWR 时钟并启用对备份域的访问 #######*/
  /* 要更改 RTC 功能（LSE、LSI）的源时钟，必须：
      - 启用PWR时钟
      - 启用写访问以配置 RTC 时钟源（在复位后完成一次）。
      - 复位备份域
      - 配置需要的RTC时钟源 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  LL_PWR_EnableBkUpAccess();

  /*##-2- 将LSI配置为RTC时钟源##############################*/
  /* 使能 LSI */
  LL_RCC_LSI_Enable();
  while (LL_RCC_LSI_IsReady() != 1)
  {
  }
  /* 仅当 LSI 尚未被选为 RTC 时钟源时才复位备份域 */
  if (LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSI)
  {
    LL_RCC_ForceBackupDomainReset();
    LL_RCC_ReleaseBackupDomainReset();
    LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
  }
  
  /* 使能 RTC 时钟和 RTC APB 时钟*/
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_RTC);
  LL_RCC_EnableRTC();
  
  /*##-4 配置RTC ######################################### ############*/
  /* 配置 RTC 预分频器和 RTC 数据寄存器 */
  if (LL_RTC_DeInit(RTC) != SUCCESS) 
  {
    /* 错误提示 */
    BSP_LED_Toggle(LED_GREEN);
  }
  
  /* 配置分频因子和输出源 */
  rtc_initstruct.AsynchPrescaler = RTC_ASYNCH_PREDIV;
  rtc_initstruct.OutPutSource    = LL_RTC_CALIB_OUTPUT_NONE;
  if (LL_RTC_Init(RTC, &rtc_initstruct) != SUCCESS)
  {
    /* 错误提示 */
    BSP_LED_Toggle(LED_GREEN);
  }
}

/*******************************************************************************
**功能描述 ：配置RTC闹钟
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_ConfigRtcAlarm(void)
{
  LL_RTC_TimeTypeDef  rtc_time_initstruct;
  LL_RTC_AlarmTypeDef rtc_alarm_initstruct;
  
  /*## 配置日期 ##################################################*/
  /* 设定日期: 2022.08.16 */
  APP_ConfigRtcDate(16, 8, 22);
  
  /*##-4- 配置时间 ################################################*/
  /* Set Time: 11:59:55 */
  rtc_time_initstruct.Hours      =11;
  rtc_time_initstruct.Minutes    =59 ;
  rtc_time_initstruct.Seconds    =55;
  /* 根据初始化结构中定义的参数初始化 RTC 时间 */  
  if (LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BIN, &rtc_time_initstruct) != SUCCESS)   
  {
    /* 错误提示 */
    BSP_LED_Toggle(LED_GREEN);
  }
  /*##-5-配置闹钟 #################################*/
  /* 配置闹钟时间为 12:00:25 */
  rtc_alarm_initstruct.AlarmTime.Hours      = 12;
  rtc_alarm_initstruct.AlarmTime.Minutes    = 00;
  rtc_alarm_initstruct.AlarmTime.Seconds    = 25;
  if (LL_RTC_ALARM_Init(RTC, LL_RTC_FORMAT_BIN, &rtc_alarm_initstruct) != SUCCESS)   
  {
    /* 错误提示 */
    BSP_LED_Toggle(LED_GREEN);
  }
  
  /* 禁用 RTC 寄存器的写保护 */
  LL_RTC_DisableWriteProtection(RTC);
  
  /* 清除闹钟中断挂起位 */
  LL_RTC_ClearFlag_ALR(RTC);
  
  /* 使能闹钟中断 */
  LL_RTC_EnableIT_ALR(RTC);

  /* 使能 RTC 寄存器的写保护 */
  LL_RTC_EnableWriteProtection(RTC);
  
  /*##-6- 配置RTC的NVIC ###############################*/
  NVIC_SetPriority(RTC_IRQn, 0x00);
  NVIC_EnableIRQ(RTC_IRQn);

  /*##-7- 退出初始化模式 #######################################*/
  if (LL_RTC_ExitInitMode(RTC) != SUCCESS)   
  {
    /* 错误提示 */
    BSP_LED_Toggle(LED_GREEN);
  }
}

/*******************************************************************************
**功能描述 ：配置日期
**输入参数 ：fYear：年份
**           fMonth：月份
**           fDate：天
**输出参数 ：
*******************************************************************************/
static void APP_ConfigRtcDate(uint8_t fDate , uint8_t fMonth , uint8_t fYear)
{
  RTC_DateStruct.day   = fDate;
  RTC_DateStruct.month = fMonth;
  RTC_DateStruct.year  = fYear;
}

/*******************************************************************************
**功能描述 ：显示日期和时间
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_ShowRtcCalendar(void)
{
  APP_UpadateRtcTimeStruct();
  APP_UpadateRtcDateStruct();
  /* 显示时间格式 : hh:mm:ss */
  sprintf((char*)aShowTime,"%.2d:%.2d:%.2d", RTC_TimeStruct.hour, 
          RTC_TimeStruct.min, 
          RTC_TimeStruct.sec);
  /* 显示日期格式 : mm-dd-yy */
  sprintf((char*)aShowDate,"%.2d-%.2d-%.2d", RTC_DateStruct.day,
          RTC_DateStruct.month,
          (2000 + RTC_DateStruct.year));
}

/*******************************************************************************
**功能描述 ：更新时间
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_UpadateRtcTimeStruct(void)
{  
  TimeCounter = LL_RTC_TIME_Get(RTC);
  RTC_TimeStruct.hour = (TimeCounter/3600);
  RTC_TimeStruct.min  = (TimeCounter % 3600) / 60;
  RTC_TimeStruct.sec  = (TimeCounter % 3600) % 60; 
}

/*******************************************************************************
**功能描述 ：更新日期
**输入参数 ：
**输出参数 ：
*******************************************************************************/
static void APP_UpadateRtcDateStruct(void)
{
  /* 当时间为 23:59:59 时，更新日期 */
  if (TimeCounter == 0x0001517FU)
  {
    if(RTC_DateStruct.day == EndOfMonth[RTC_DateStruct.month -1])
    {
      RTC_DateStruct.day = 1U;
      RTC_DateStruct.month += 1U;
    }
    else
    {
      RTC_DateStruct.day = RTC_DateStruct.day + 0x1U;
    }
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

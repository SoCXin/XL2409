#include "User_Timer14.h"

TIM_HandleTypeDef TIM_Handle;//定时器句柄

uint8_t gTmrCnt;
uint8_t gTmrBase;
uint8_t F_TMR_BASE;

void User_TIM14_Init(void)
{
    /*使能时钟*/
    __HAL_RCC_TIM14_CLK_ENABLE();

    /*参数配置*/
    TIM_Handle.Instance =TIM14;
    TIM_Handle.Init.Period = 2400-1;//自动重装载值
    TIM_Handle.Init.Prescaler = 10-1;//预分频值
    TIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//不分频
    TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;//向上计数模式
    TIM_Handle.Init.RepetitionCounter = 1-1;//不重复计数
    TIM_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;//自动重装载寄存器没有缓冲

    HAL_TIM_Base_Init(&TIM_Handle);

    HAL_TIM_Base_Start_IT(&TIM_Handle);

    /*配置中断优先级*/
    HAL_NVIC_SetPriority(TIM14_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(TIM14_IRQn); 

}

//中断服务函数
void TIM14_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TIM_Handle);
}

//定时器中断公共处理函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM14 )//如果是定时器14
    {
        gTmrCnt++;
    }
}


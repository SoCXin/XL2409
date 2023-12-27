#include "bsp_tim3.h"

TIM_HandleTypeDef  TimHandle;

void TIM3_Init(void)
{
    __HAL_RCC_TIM3_CLK_ENABLE() ;
    TimHandle.Instance = TIM3;                                           //选择TIM3
    TimHandle.Init.Period            = 1000 - 1;                         //自动重装载值
    TimHandle.Init.Prescaler         = 1000 - 1;                         //预分频为1000-1
    TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           //时钟不分频
    TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               //向上计数
    TimHandle.Init.RepetitionCounter = 1 - 1;                            //不重复计数
    TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;//TIM_AUTORELOAD_PRELOAD_DISABLE;   //自动重装载寄存器没有缓冲

    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 2);                //设置中断优先级
    HAL_NVIC_EnableIRQ(TIM3_IRQn);                        //使能中断
    __HAL_TIM_CLEAR_IT(&TimHandle, TIM_IT_UPDATE);        //清除中断标志
    //Tim_On();   //启动定时器
    Clear_Tim();
}

uint16_t tim_rfsend = 0; //用于点动发送与接收信号
uint16_t tim_led1 = 0; //用于led1闪烁
uint16_t tim_led2 = 0;  //用于led2闪烁
uint16_t tim_count1 = 0;  //按键按下/弹起间隔时间
//计时器中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    tim_rfsend ++;
    tim_led1 ++;
    tim_led2 ++;
    tim_count1 ++;  //按键按下/弹起间隔时间
    if(tim_rfsend > 2000) tim_rfsend = 0;
    if(tim_led1 > 2000) tim_led1 = 0;
    if(tim_led2 > 2000) tim_led2 = 0;
    if(tim_led2 > 2000) tim_led2 = 0;
    if(tim_count1 > 2000) tim_count1 = 0;
    //HAL_GPIO_TogglePin(LED3_GPIO_PORT, LED3_PIN);
}

void Tim_On(void)
{
    HAL_TIM_Base_Start_IT(&TimHandle);
}

void Clear_Tim(void)
{
    HAL_TIM_Base_Stop_IT(&TimHandle);                 //关闭计数
    __HAL_TIM_SET_COUNTER(&TimHandle, 0);							//清零计数
}






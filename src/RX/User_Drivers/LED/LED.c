#include "LED.h"

void User_LED(void)
{
    /*使能时钟*/
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*配置参数*/
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin       = GPIO_PIN_4;     //PA2|PA3
    GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;           //推免复用
    GPIO_InitStruct.Pull      = GPIO_PULLUP;               //上拉模式
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH; //超高速模式

    HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);//根据GPIO结构体初始化引脚

    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
}


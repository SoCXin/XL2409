#include "bsp_pins.h"
#include "bsp_encode.h"

//PB5 PB6 PB7 PA0初始化为输出
void Pins_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_Initstructure;

    //D0 PB5
    GPIO_Initstructure.Pin = PINS1_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initstructure.Pull = GPIO_PULLDOWN;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(PINS1_PORT, &GPIO_Initstructure);

    //D1 PB6
    GPIO_Initstructure.Pin = PINS2_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initstructure.Pull = GPIO_PULLDOWN;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(PINS2_PORT, &GPIO_Initstructure);

    //D2 PB7
    GPIO_Initstructure.Pin = PINS3_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initstructure.Pull = GPIO_PULLDOWN;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(PINS3_PORT, &GPIO_Initstructure);

    //D3 PA0
    GPIO_Initstructure.Pin = PINS4_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initstructure.Pull = GPIO_PULLDOWN;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(PINS4_PORT, &GPIO_Initstructure);

}

//拉高引脚
void Pins_High(GPIO_TypeDef *GPIOx, uint16_t Pin)
{
    HAL_GPIO_WritePin(GPIOx, Pin, GPIO_PIN_SET);
}

//拉低引脚
void Pins_Low(GPIO_TypeDef *GPIOx, uint16_t Pin)
{
    HAL_GPIO_WritePin(GPIOx, Pin, GPIO_PIN_RESET);
}

//三种模式控制引脚
void Pins_Ctrl(void)
{
    //D0
    if(encode_flag.keys_flag[0] == 1)
    {
        Pins_High(PINS1_PORT, PINS1_PIN);
    }
    else
    {
        Pins_Low(PINS1_PORT, PINS1_PIN);
    }

    //D1
    if(encode_flag.keys_flag[1] == 1)
    {
        Pins_High(PINS2_PORT, PINS2_PIN);
    }
    else
    {
        Pins_Low(PINS2_PORT, PINS2_PIN);
    }

    //D2
    if(encode_flag.keys_flag[2] == 1)
    {
        Pins_High(PINS3_PORT, PINS3_PIN);
    }
    else
    {
        Pins_Low(PINS3_PORT, PINS3_PIN);
    }

    //D3
    if(encode_flag.keys_flag[3] == 1)
    {
        Pins_High(PINS4_PORT, PINS4_PIN);
    }
    else
    {
        Pins_Low(PINS4_PORT, PINS4_PIN);
    }

}


#include "bsp_key.h"
#include "bsp_led.h"

//??????PA12
void KEY_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef   GPIO_Initstructure;

    GPIO_Initstructure.Pin = SEND_KEY3_GPIO_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_INPUT;
    GPIO_Initstructure.Pull = GPIO_PULLUP;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(SEND_KEY3_GPIO_PORT, &GPIO_Initstructure);

    GPIO_Initstructure.Pin = FUN_KEY2_GPIO_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_INPUT;
    GPIO_Initstructure.Pull = GPIO_PULLUP;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(FUN_KEY2_GPIO_PORT, &GPIO_Initstructure);
}

//????PB5 PB6 PB7 PA0?????
void KEYS_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef   GPIO_Initstructure;

    GPIO_Initstructure.Pin = KEY1_GPIO_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_INPUT;
    GPIO_Initstructure.Pull = GPIO_PULLUP;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_Initstructure);

    GPIO_Initstructure.Pin = KEY2_GPIO_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_INPUT;
    GPIO_Initstructure.Pull = GPIO_PULLUP;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(KEY2_GPIO_PORT, &GPIO_Initstructure);

    GPIO_Initstructure.Pin = KEY3_GPIO_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_INPUT;
    GPIO_Initstructure.Pull = GPIO_PULLUP;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(KEY3_GPIO_PORT, &GPIO_Initstructure);

    GPIO_Initstructure.Pin = KEY4_GPIO_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_INPUT;
    GPIO_Initstructure.Pull = GPIO_PULLUP;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(KEY4_GPIO_PORT, &GPIO_Initstructure);

}

//???????
uint8_t KEY_SCAN(GPIO_TypeDef *GPIOx, uint16_t Pin)
{
    if(HAL_GPIO_ReadPin(GPIOx, Pin) == GPIO_PIN_RESET)
    {
        return KEY_ON;
    }
    else
    {
        return KEY_OFF;
    }
}




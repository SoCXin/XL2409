#include "bsp_led.h"
#include "bsp_tim3.h"

uint16_t Led_gflag = 0;  //À¶µÆ±ê¼Ç
uint16_t Led_rflag = 0;  //ºìµÆ±ê¼Ç

//LEDµÆ³õÊ¼»¯
void LED_Init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_Initstructure;

    GPIO_Initstructure.Pin = LED1_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initstructure.Pull = GPIO_PULLUP;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(LED1_PORT, &GPIO_Initstructure);

    GPIO_Initstructure.Pin = LED2_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initstructure.Pull = GPIO_PULLUP;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(LED2_PORT, &GPIO_Initstructure);

    GPIO_Initstructure.Pin = LED3_PIN;
    GPIO_Initstructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initstructure.Pull = GPIO_PULLUP;
    GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(LED3_PORT, &GPIO_Initstructure);
}

/**
  * @brief  Configures LED GPIO.
  * @param  Led Specifies the Led to be configured.
  *         This parameter can be one of following parameters:
  *         @arg  LED3
  * @retval None
  */
void GREEN_LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /* Enable the GPIO_LED Clock */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
}

//ÁÁµÆ
void LedOn(GPIO_TypeDef *GPIOx, uint16_t Pin)
{
    if(GPIOx == LED1_PORT && Pin == LED1_PIN)  Led_gflag = 0;
    if(GPIOx == LED2_PORT && Pin == LED2_PIN)  Led_rflag = 0;
    HAL_GPIO_WritePin(GPIOx, Pin, GPIO_PIN_RESET);
}

//¹ØµÆ
void LedOff(GPIO_TypeDef *GPIOx, uint16_t Pin)
{
    if(GPIOx == LED1_PORT && Pin == LED1_PIN)  Led_gflag = 0;
    if(GPIOx == LED2_PORT && Pin == LED2_PIN)  Led_rflag = 0;
    HAL_GPIO_WritePin(GPIOx, Pin, GPIO_PIN_SET);
}

//ÇÐ»»
void LedToggle(GPIO_TypeDef *GPIOx, uint16_t Pin)
{
    HAL_GPIO_TogglePin(GPIOx, Pin);
}

//ÉÁµÆ´ÎÊý
void LedCount(GPIO_TypeDef *GPIOx, uint16_t Pin, uint16_t Count)
{
    if(GPIOx == LED1_PORT && Pin == LED1_PIN)  //LED1
    {
        LedOff(LED1_PORT, LED1_PIN);
        Led_gflag = 2 * Count, tim_led1 = 0; //ÁÁÃðÎªÁ½´ÎÇÐ»»×´Ì¬ count*2
    }
    if(GPIOx == LED2_PORT && Pin == LED2_PIN)  //LED2
    {
        LedOff(LED2_PORT, LED2_PIN);
        Led_rflag = 2 * Count, tim_led2 = 0;
    }
}

//LEDÉÁË¸ ¶¨Ê±Æ÷¿ØÖÆ
void LedBlinkCase(void)
{
    if(Led_gflag > 0)
    {
        if(tim_led1 >= 70)
        {
            Led_gflag --;
            tim_led1 = 0;
            HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
        }
    }

    if(Led_rflag > 0)
    {
        if(tim_led2 >= 70)
        {
            Led_rflag --;
            tim_led2 = 0;
            HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN);
        }
    }

}


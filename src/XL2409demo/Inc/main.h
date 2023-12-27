/**
  ******************************************************************************
  * @file    main.h
  * @author  Application Team
  * @Version V1.0.0
  * @Date
  * @brief   Header for main.c file.
  *          This file contains the common defines of the application.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H



/* Includes ------------------------------------------------------------------*/
#include "sip_mcu_hal.h"
//#include "xl32f00x_Start_Kit.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }

}
#endif /* USE_FULL_ASSERT */





#endif /* __MAIN_H */


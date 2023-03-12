/**
  ******************************************************************************
  * @file    xl32f0xx_ll_crc.c
  * @author  MCU Application Team
  * @brief   CRC LL module driver.
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "xl32f0xx_ll_crc.h"
#include "xl32f0xx_ll_bus.h"

#ifdef  USE_FULL_ASSERT
  #include "xl32_assert.h"
#else
  #define assert_param(expr) ((void)0U)
#endif

/** @addtogroup XL32F0xx_LL_Driver
  * @{
  */

#if defined (CRC)

/** @addtogroup CRC_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CRC_LL_Exported_Functions
  * @{
  */

/** @addtogroup CRC_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize CRC registers (Registers restored to their default values).
  * @param  CRCx CRC Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: CRC registers are de-initialized
  *          - ERROR: CRC registers are not de-initialized
  */
ErrorStatus LL_CRC_DeInit(CRC_TypeDef *CRCx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_CRC_ALL_INSTANCE(CRCx));

  if (CRCx == CRC)
  {

    /* Reset the CRC calculation unit */
    LL_CRC_ResetCRCCalculationUnit(CRCx);

    /* Reset IDR register */
    LL_CRC_Write_IDR(CRCx, 0x00U);
  }
  else
  {
    status = ERROR;
  }

  return (status);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (CRC) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT Xinling *****END OF FILE****/


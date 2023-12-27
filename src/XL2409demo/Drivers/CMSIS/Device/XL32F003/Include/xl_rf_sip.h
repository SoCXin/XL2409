#ifndef __XL_RF_SIP_H
#define __XL_RF_SIP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/**
  * @brief CMSIS Device version number V1.0.0
  */
#define __SIP_MCU_DEVICE_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __SIP_MCU_DEVICE_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __SIP_MCU_DEVICE_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __SIP_MCU_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __SIP_MCU_DEVICE_VERSION        ((__SIP_MCU_DEVICE_VERSION_MAIN << 24)\
                                        |(__SIP_MCU_DEVICE_VERSION_SUB1 << 16)\
                                        |(__SIP_MCU_DEVICE_VERSION_SUB2 << 8 )\
                                        |(__SIP_MCU_DEVICE_VERSION_RC))

#include "sip_mcu.h"



typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  ERROR = 0,
  SUCCESS = !ERROR
} ErrorStatus;


#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define HW32_REG(ADDRESS)     ( * ((volatile unsigned           int * )(ADDRESS)))

#define HW16_REG(ADDRESS)     ( * ((volatile unsigned short     int * )(ADDRESS)))

#define HW8_REG(ADDRESS)      ( * ((volatile unsigned          char * )(ADDRESS)))


 #include "sip_mcu_hal.h"



#ifdef __cplusplus
}
#endif 

#endif 



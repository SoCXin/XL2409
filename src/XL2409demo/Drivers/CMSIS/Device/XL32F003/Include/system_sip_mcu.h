#ifndef SYSTEM__SIP_MCU_H
#define SYSTEM__SIP_MCU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */

extern const uint32_t AHBPrescTable[16];  /*!<  AHB prescalers table values */
extern const uint32_t APBPrescTable[8];   /*!< APB prescalers table values */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit(void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM__SIP_MCU_H */

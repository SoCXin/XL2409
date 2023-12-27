#ifndef _RF_TEST_H_
#define _RF_TEST_H_
//#include "n32g031.h"
#include "sip_mcu_hal.h"

#define RF_SEND_LEN  128    //max is 128
typedef enum
{
    TestSensitivity = 0,
    TestOutputPower,
    TestDistance,
    TestDebugMode,
    TestRfModule,
    TestRfPower,
    TestNothing
} TEST_MODE_ENUM;

typedef enum
{
    M0,
    M1,
    M2,
    M3,
    M4,
    M5,
    STA_Recv,
    CCO_Recv
} Signal;

typedef struct 
{
  uint8_t value : 7;
  uint8_t symbol :1;
}TYPE_t;
extern volatile uint8_t g_Channel;
extern volatile uint8_t Signal_Type;
extern volatile uint32_t TestRfPower_time;
extern volatile uint32_t TestRfCheck_time;//dl 20200402
extern uint16_t Default_Freq[];	
extern TEST_MODE_ENUM TestMode;

uint8_t App_TestRfPower(uint8_t *Buf, uint16_t Len);
void rf_do_TestRfPower_proc(int Signal_Type);

#endif // _RF_TEST_H_


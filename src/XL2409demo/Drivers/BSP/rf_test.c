//------------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
//  All rights reserved
//
//  File    : rf_test.c
//  Purpose : rf test entry
//  History : Created by LZZX on 20200316.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#include "rf_test.h"
#include "bsp_rf.h"
#include <stdint.h>
#include <math.h>
#include <string.h>
//#include "systick.h"
//#include "common.h"
//#include "usart.h"
#include "sip_mcu_hal.h"


volatile uint8_t Signal_Type;
volatile uint8_t g_Channel = 0;
volatile double freq_offset;

volatile uint32_t TestRfPower_time = 0;
volatile uint32_t TestRfCheck_time = 0;

uint16_t Default_Freq[] =
{
    4763, 4847,         // Channel 0
    4715, 4793,         // Channel 1
    4717, 4795,         // Channel 2
    4719, 4797,         // Channel 3
    4721, 4799,         // Channel 4
    4723, 4801,         // Channel 5
    4725, 4803,         // Channel 6
    4727, 4805,         // Channel 7
    4729, 4807,         // Channel 8
    4731, 4809,         // Channel 9
    4733, 4811,         // Channel 10
    4735, 4813,         // Channel 11
    4737, 4815,         // Channel 12
    4739, 4817,         // Channel 13
    4741, 4819,         // Channel 14
    4743, 4821,         // Channel 15
    4745, 4823,         // Channel 16
    4747, 4825,         // Channel 17
    4749, 4827,         // Channel 18
    4751, 4829,         // Channel 19
    4753, 4831,         // Channel 20
    4755, 4833,         // Channel 21
    4757, 4835,         // Channel 22
    4759, 4837,         // Channel 23
    4761, 4839,         // Channel 24
    4765, 4841,         // Channel 25
    4767, 4843,         // Channel 26
    4769, 4845,         // Channel 27
    4771, 4849,         // Channel 28
    4773, 4851,         // Channel 29
    4775, 4853,         // Channel 30
    4777, 4855,         // Channel 31
    4779, 4857,         // Channel 32
};

TYPE_t Test_freq_offset;

TEST_MODE_ENUM TestMode = TestNothing;
uint8_t M0_Signal[2] = { 0x00,0x00 };
uint8_t M1_Signal[2] = { 0xFF,0xFF };
uint8_t M2_Signal[128] = { 0x00,0x78,0x47,0xA6,0x48,0x5E,0x33,0xDB,0xA8,0xA1,
                           0xB4,0x63,0xF1,0x16,0x15,0xAF,0xD5,0x41,0x4B,0xE4,
                           0x49,0x4F,0xA2,0x0E,0x19,0x65,0x1C,0xBA,0x02,0xD3,
                           0xAC,0xE7,0xF3,0x35,0x36,0x04,0xB6,0xC8,0x1A,0x57,
                           0xAE,0xC4,0xD0,0x9E,0x55,0x8D,0xE7,0x7B,0xFD,0xDC,
                           0xDC,0x54,0x9C,0x76,0xAE,0x4C,0x18,0x74,0x8D,0x6F,
                           0xB3,0x17,0x04,0x3E,
                           0x00,0x78,0x47,0xA6,0x48,0x5E,0x33,0xDB,0xA8,0xA1,
                           0xB4,0x63,0xF1,0x16,0x15,0xAF,0xD5,0x41,0x4B,0xE4,
                           0x49,0x4F,0xA2,0x0E,0x19,0x65,0x1C,0xBA,0x02,0xD3,
                           0xAC,0xE7,0xF3,0x35,0x36,0x04,0xB6,0xC8,0x1A,0x57,
                           0xAE,0xC4,0xD0,0x9E,0x55,0x8D,0xE7,0x7B,0xFD,0xDC,
                           0xDC,0x54,0x9C,0x76,0xAE,0x4C,0x18,0x74,0x8D,0x6F,
                           0xB3,0x17,0x04,0x3E};


uint8_t M4_Signal[2] = { 0x55,0x55 };

uint8_t STA_Recv_Signal[53] = { 0x02,0x01,0x36,0x41,0xcd,0x88,0x00,0x00,0x88,0x88,
                            0x88,0x88,0x88,0x88,0x00,0x00,0x00,0x00,0x00,0x00,
                            0x3c,0x88,0x88,0x88,0x88,0x88,0x88,0x00,0x00,0x00,
                            0x00,0x00,0x00,0xe1,0x12,0xdf,0x00,0x68,0x88,0x88,
                            0x88,0x88,0x88,0x88,0x68,0x11,0x04,0x33,0x33,0x34,
                            0x33,0xe2,0x16};

uint8_t CCO_Recv_Signal[36] = { 0x00,0x01,0x25,0x43,0xCD,0x00,0xFF,0xFF,0x00,0x00,
                            0x00,0x00,0x00,0x00,0x88,0x88,0x88,0x88,0x88,0x88,
                            0x50,0x68,0x0F,0x00,0xCA,0x00,0x00,0x00,0x00,0x00,
                            0x00,0x04,0x10,0x00,0x00,0x16};

extern double g_freq;
//static void PackageSendMode(uint8_t *send_buf,uint8_t send_len)
//{
////    TestRfCheck_time = 200;
//    
//    RfFreqSet(g_freq, 0, 0.0f);
//    RfRecEn();
//    send_buf[1] = send_len;
//    RfTestPackageSend(send_buf, send_len + 2);
//}

static void StreamSendMode(uint8_t *send_buf, uint8_t send_len)
{
    uint8_t Buf[RF_SEND_LEN + 1] = {0};
		uint8_t i;
		
    if (send_len > RF_SEND_LEN)
    {
        printf("StreamSendMode send len err, send_len = %d", send_len);
        return;
    }

    switch (Signal_Type)
    {
        case M0:
        case M1:
        case M4:
            for (i = 0; i < send_len + 1; i++)
            {
                Buf[i] = send_buf[0];
            }
            break;
        case M2:
            strncpy(( char*)Buf, (char*)send_buf, send_len);
            break;
        default:
            //SEGGER_RTT_printf(0,"StreamSendMode Signal_Type err, Signal_Type = %d", Signal_Type);
            return;
    }

    TestRfCheck_time = 0xFFFFFFFF;
    RfRegisterWrite(0x06, 0x20);
    RfFreqSet(g_freq, 0, 0.0f);
    RfRecEn();
    RfTestPackageSend(Buf, send_len + 1);
    //SEGGER_RTT_printf(0, "StreamSendMode send data len = %d", send_len + 1);
}

void Test_RfPowerStop( void )
{
    printf( "App_TestRfPower Stop");
    TestMode = TestNothing;
    RfRecEn();
    RfRegisterWrite(0x06, 0x3a); // zhengdeguan 2020.03.31 close scrambles
}

void Test_RfPowerStart( void )
{
    printf("App_TestRfPower Start");
    TestMode = TestRfPower;
}

void rf_do_TestRfPower_proc(int Signal_Type)
{ 
    uint8_t send_Buf[128]={0};

    if(Signal_Type  > 4) 
    {
      Signal_Type = 0;
    }
    switch (Signal_Type)
    {
        case M0:
            StreamSendMode(M0_Signal,RF_SEND_LEN);
            break;
        case M1:
            StreamSendMode(M1_Signal,RF_SEND_LEN);
            break;
        case M2:
            StreamSendMode(M2_Signal,RF_SEND_LEN);
            break;
        case M3:
            break;
        case M4:
            StreamSendMode(M4_Signal,RF_SEND_LEN);
            break;
        case M5:
            break;
        case STA_Recv:
            strncpy((char*)&send_Buf[2],(char*)STA_Recv_Signal,53);
            break;
        case CCO_Recv:
            strncpy((char*)&send_Buf[2],(char*)CCO_Recv_Signal,36);
            break;
        default:
            break;
    }
}

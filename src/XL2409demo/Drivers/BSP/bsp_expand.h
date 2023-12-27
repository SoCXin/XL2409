#ifndef __BSP_EXPAND_H
#define __BSP_EXPAND_H

#include "sip_mcu_hal.h"


void Ignore(void);
void PrintLog(void);
void LedBlinkTwice(void);
void LED_MODE1_OFF(void);
void Judge_Ask(void);
uint8_t Rssi_Busy(void);
/*******************************************/
void R_Tap(void);
void R_Selflock(void);
void R_Interlock(void);
void R_Toggle(void);
void R_Clear(void);
void R_Receive(void);
void T_Toggle(void);
void T_Keys_State(void);
void T_Receive(void);

typedef struct
{
    uint8_t tr_mate_nums;  //����Եķ��������
    uint8_t t_or_r_mode_flag;  //����Եķ����ģʽ
    uint8_t r_reqmate_flag;  //������Ա�־
} r_infor_flag_block;


extern r_infor_flag_block infor_flag;

#endif

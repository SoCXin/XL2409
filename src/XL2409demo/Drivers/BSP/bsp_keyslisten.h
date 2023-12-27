#ifndef __BSP_KEYSLISTEN_H
#define __BSP_KEYSLISTEN_H

#include "sip_mcu_hal.h"


void RandNum(void);
void Study_Key_Count(void);
void Study_Key_Response(uint16_t count);
void Keys_State(void);
void Key_Get(void);


extern uint8_t rand_num[4];
extern uint8_t first;  //���������ַ
extern uint8_t studykey_lock; //ѧϰ�������ȼ����
extern uint8_t keys[4]; //�ĸ�����

#endif

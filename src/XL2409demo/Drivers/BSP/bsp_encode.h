#ifndef __BSP_ENCODE_H
#define __BSP_ENCODE_H

#include "sip_mcu_hal.h"



//"\xAB\xBB\xFF\xFF\xFF\xFF\x00\x00\x00\x00\x00"; //0 ��ʼ  1 ����/����  2-5 ��ַ  6-9 ����K  10״̬λ
#define head_encode 0xAB  //ͷ���� 00
#define r_encode 0xBB //���� 01
#define t_encode 0xAA  //���� 01
#define adrnull_encode 0xFF //����̬�յ�ַ 2-5

typedef struct
{
    uint8_t t_or_r_mode_flag;  //����/���ձ�־λ 1����̬ 0����̬
    uint8_t state_flag;  //״̬λ
    uint8_t adr_change;  //��ַ����
    uint8_t keys_flag[4];  //�����Ƿ��±�־λ
} encode_flag_block;

extern encode_flag_block encode_flag; //���еı�־λӰ����������


void Encode_Form(void);
void SendEncode(void);
void ReceiveEncode(void);
void Flash_Readstate(void);
void Flash_Infor(void);
void Flash_Mate_Form(void);
void Flash_Adr(void);
uint8_t SendDelay_Create(void);


#define TEST_BER_DATA_LEN  11 //���볤��
#define FLASH_MATE_LENGTH 8  //������?����
#define FLASH_INFOR_LENGTH 8  //������Ϣ����
extern unsigned char gSendBuf1[TEST_BER_DATA_LEN];
extern uint8_t FlashSendBuf1[FLASH_INFOR_LENGTH / 2];
extern uint8_t FlashSendBuf2[FLASH_MATE_LENGTH];
extern uint8_t FlashReadBuf[FLASH_MATE_LENGTH];



#endif

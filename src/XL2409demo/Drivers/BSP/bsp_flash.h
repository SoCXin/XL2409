#ifndef __BSP_FLASH_H
#define __BSP_FLASH_H

#include "sip_mcu_hal.h"


#define FLASH_INFOR_ADR   0x08006000  //������Ϣ��ַ
#define FLASH_MATE_ADR     0x08006100  //�����Ϣ��ַ


void Flash_Write(uint32_t WriteAddr, uint32_t *Dataflash);
void FLASH_Read(uint32_t ReadAddr, uint32_t *pBuffer, uint16_t NumToRead);
void FLASH_Read_8(uint32_t ReadAddr, uint8_t *pBuffer1, uint16_t length);
void Flash_Write_8(uint32_t WriteAddr, uint8_t *pBuffer1, uint16_t length);
void FLASH_AddMate(uint32_t WriteAddr, uint8_t *pBuffer, uint16_t nums);
void Flash_ChangeInfor(uint32_t WriteAddr, uint8_t *pBuffer);
void Flash_Erase(uint32_t UserAddr);



#endif

#ifndef	RF_SPI_H
#define	RF_SPI_H

#include "main.h"

#define SPI_MISO_GPIO_PIN         GPIO_PIN_1
#define SPI_MOSI_GPIO_PIN         GPIO_PIN_3
#define SPI_SCK_GPIO_PIN          GPIO_PIN_0
#define SPI_CS_GPIO_PIN           GPIO_PIN_1

#define SCK_High                  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
#define SCK_Low                   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);

#define SPI_MOSI_High             HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);
#define SPI_MOSI_Low              HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);

#define CS_Low		                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
#define CS_High		                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
#define Read_MOSI                   HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_1)

void RF_GPIO_Init(void);
void RF_SPI_Init(void);
void SPI_Write_Byte(unsigned char buff);
unsigned char SPI_Read_Byte(void);
void SPI_Write_Reg(unsigned char RfAdress,unsigned char RfData);
unsigned char SPI_Read_Reg(unsigned char RfAdress);
void Write_RF_Buff(unsigned char RFAdress , unsigned char *pBuff , unsigned char Len);
void Read_RF_Buff(unsigned char RFAdress , unsigned char *pBuff , unsigned char Len);




#endif


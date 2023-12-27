#ifndef __BSP_RF_H
#define __BSP_RF_H

#include "sip_mcu_hal.h"


#define RF_SPI                       			SPI1

//#define RF_SPI_CLK                   			RCC_APB2_PERIPH_SPI2
#define RF_SPI_SCK_PIN               			GPIO_PIN_2                  /* PA.05 */
#define RF_SPI_SCK_GPIO_PORT         			GPIOA                       /* GPIOA */
//#define RF_SPI_SCK_GPIO_CLK          			RCC_APB2_PERIPH_GPIOA
#define RF_SPI_MISO_PIN              			GPIO_PIN_6                 /* PA.06 */
#define RF_SPI_MISO_GPIO_PORT        			GPIOA                       /* GPIOA */
//#define RF_SPI_MISO_GPIO_CLK         			RCC_APB2_PERIPH_GPIOA
#define RF_SPI_MOSI_PIN              			GPIO_PIN_3                 /* PA.07 */
#define RF_SPI_MOSI_GPIO_PORT        			GPIOA                       /* GPIOA */
//#define RF_SPI_MOSI_GPIO_CLK         			RCC_APB2_PERIPH_GPIOA
#define RF_CS_PIN                    			GPIO_PIN_7                  /* PB.04 */
#define RF_CS_GPIO_PORT              			GPIOA                       /* GPIOA */
//#define RF_CS_GPIO_CLK               			RCC_APB2_PERIPH_GPIOA

//#define RF_SDN_PIN                    		GPIO_PIN_4                  /* PB.04 */
//#define RF_SDN_GPIO_PORT              		GPIOB                       /* GPIOB */
//#define RF_SDN_GPIO_CLK               		RCC_APB2_PERIPH_GPIOB
#define RF_RSTN_PIN                   		GPIO_PIN_1                 /* PB.02 */
#define RF_RSTN_GPIO_PORT             		GPIOA                       /* GPIOA */
//#define RF_RSTN_GPIO_CLK              		RCC_APB2_PERIPH_GPIOA
#define RF_PTK_PIN                    		GPIO_PIN_1                  /* PB.03 */
#define RF_PTK_GPIO_PORT              		GPIOB                       /* GPIOA */
//#define RF_PTK_GPIO_CLK               		RCC_APB2_PERIPH_GPIOB


typedef enum
{
    DBM20,
    DBM19,
    DBM18,
    DBM17,
    DBM16,
    DBM15,
    DBM14,
    DBM13,
    DBM12,
    DBM11,
    DBM10,
    DBM9,
    DBM8,
    DBM7,
    DBM6,
    DBM5,
    DBM4,
    DBM3,
    DBM2,
    DBM1,
    DBM_0,
    DBM_1,
    DBM_2,
    DBM_3,
    DBM_4,
    DBM_5,
    DBM_6,
} PA_LEVEL;

extern unsigned char mRfRxBuf[264];
void rf_event_init(void);

extern double g_freq;
extern unsigned char g_paValue;
extern volatile char g_rece_fal;
extern unsigned char gRfWorkModeFlag;
extern unsigned char gRfTxSendFlag;
extern unsigned char gRfUserTxSendFlag;
extern volatile unsigned int g_preamble_timeout;
extern unsigned char   gTestBerIndex;
extern unsigned char   gTestBerTatol;
extern unsigned char   gTestBerSendIndex;
//extern unsigned char   gSendBuf[TEST_BER_DATA_LEN];

extern void RfConfigure(void);
extern void RfTestPackageSend(const unsigned char *buffer, const unsigned char size);
extern void RfDataPackageSend(const unsigned char *buffer, const unsigned char size);
extern int RfPackageRecv(char *buf);
extern void RfFreqSet(const double f0, const unsigned char N, const double step);
extern void RfRegisterWrite(const unsigned char addr, const unsigned char val);
extern unsigned char RfRegisterRead(const unsigned char addr);
extern void RfReadFIFO(unsigned char *StoreBuf, unsigned char Len);
extern unsigned char RfReadRssi(void);
extern void RfRecEn(void);
extern void RF_TxCW(void);
extern void RfIdleEn(void);
extern int  RfSystemStatus(void);
extern void RfSleepEn(void);
extern void RfStandByEn(void);
extern void RfTranEn(void);
extern void RfSetPA(PA_LEVEL x_dBm);
extern void RfDataProcess(void);
extern void auto_send_mode(void);
//RF ��ʼ��
extern void RfEnterLowPower(void);
extern void RfExitLowPower(void);

#endif

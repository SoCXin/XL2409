#ifndef	__XL2400_H
#define	__XL2400_H

#include "sip_mcu_hal.h"

#define TRIPLE             1
#define DUAL                0

#define setbit(x,y) ((x) |= (1<<(y)))
#define clrbit(x,y) ((x) &= ~(1<<(y)))
#define setbit_array(x,y) (setbit((x)[(y)/8],(y)%8))
#define clrbit_array(x,y) (clrbit((x)[(y)/8],(y)%8))
 
#define CFG_TOP				(0X00)
#define	EN_AA				(0X01)
#define	EN_RXADDR			(0X02)
#define	SETUP_AW			(0X03)
#define	SETUP_RETR			(0X04)
#define	RF_CH				(0X05)
#define	SETUP_RF			(0X06)
#define	STATUS				(0X07)
#define	OBSERVE_TX			(0X08)
#define	RSSI				(0X09)
#define	RX_ADDR_P0			(0X0A)
#define	RX_ADDR_P1			(0X0B)
#define	RX_ADDR_P2			(0X2)
#define	RX_ADDR_P3			(0X3)
#define	RX_ADDR_P4			(0X4)
#define	RX_ADDR_P5			(0X5)
#define	RX_ADDR_P2TOP5		(0X0C)
#define	BER_RESULT			(0X0D)
#define	AGC_SETTING			(0X0E)
#define	PGA_SETTING			(0X0F)
#define	TX_ADDR				(0X10)
#define	RX_PW_PX			(0X11)
#define	ANALOG_CFG0			(0X12)
#define	ANALOG_CFG1			(0X13)
#define	ANALOG_CFG2			(0X14)
#define	ANALOG_CFG3			(0X15)
#define	STATUS_FIFO			(0X17)
#define	RSSIREC				(0X18)
#define	TXPROC_CFG			(0X19)
#define	RXPROC_CFG			(0X1A)	
#define	DYNPD				(0X1C)
#define	FEATURE				(0X1D)
#define	RAMP_CFG			(0X1E)

#define R_REG				0x00//@
#define W_REG 				0x20//@
#define R_RX_PLOAD 			0x61//@
#define W_TX_PLOAD			0xA0//@
#define FLUSH_TX			0xE1//@
#define FLUSH_RX			0xE2//@
#define REUSE_TX_PL			0xE3//@
#define R_RX_PL_WID			0x60//@
#define W_ACK_PLOAD			0xA8//@
#define W_TX_PLOAD_NOACK	0xB0//@
#define CMD_NOP				0xFF//@

#define TX_ADDR_3BYTE			 (0x1 << 2)//@
#define TX_ADDR_4BYTE			 (0x2 << 2)//@
#define TX_ADDR_5BYTE			 (0x3 << 2)//@

#define RX_ADDR_3BYTE			 (0x1)//@
#define RX_ADDR_4BYTE			 (0x2)//@
#define RX_ADDR_5BYTE			 (0x3)//@

/* STATUS Interrupt status */
#define XC_RX_DR    		(0x1 << 6)//@
#define XC_TX_DS    		(0x1 << 5)//@
#define XC_MAX_RT   		(0x1 << 4)//@

/* FIFO Status */
#define TX_REUSE        		(0x1 << 6)//@
#define TX_FULL            		(0x1 << 5)//@
#define TX_EMPTY        		(0x1 << 4)//@
#define RX_FULL            		(0x2)//@
#define RX_EMPTY        		(0x1)//@



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

#define CE_Low		      RF_Write_Reg(W_REG |CFG_TOP,0xee)
#define CE_High         RF_Write_Reg(W_REG |CFG_TOP,0xef)


void RF_IO_Init(void);
void rf_spi_reg_init(void);
void RF_Init(void);
extern  uint8_t  xc_buffer[];
extern volatile uint8_t  rw_val;
void RF_SetChannel(uint16_t channel);
void RF_RegDump(void);
void RF_TxPacket(uint8_t *txbuf, uint8_t len);//r
uint8_t RF_RxPacket(uint8_t *rxbuf);//r
void rf_tx_test(void);
void rf_rx_test(void);

uint8_t RF_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t length);
void RF_Write_Buf(uint8_t reg, uint8_t   *pBuf, uint8_t len);


#define RF_Write_Reg(REG_ADDRESS,VAL)     rw_val=VAL;RF_Write_Buf(REG_ADDRESS,(uint8_t *)&rw_val,1) 
#define RF_Read_Reg(REG_ADDRESS)          RF_Read_Buf(REG_ADDRESS,(uint8_t *)&rw_val,1)
#define WAIT_TRANSFER()  while(!((TX_EMPTY & RF_Read_Reg(STATUS_FIFO))))
#endif

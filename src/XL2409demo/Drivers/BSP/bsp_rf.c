#include "bsp_rf.h"
#include <math.h>
#include <string.h>
#include "bsp_uart.h"
#include "stdio.h"
#include "bsp_led.h"
#include "rf_test.h"

SPI_HandleTypeDef Spi1Handle;
unsigned char gRfWorkModeFlag = 0;
uint8_t  gRfTxSendFlag = 0;
uint8_t  gRfUserTxSendFlag = 0;
unsigned char g_paValue = 10;

volatile char	g_rece_falg = 0;
volatile uint32_t g_preamble_timeout = 0;
unsigned char mRfRxBuf[264];

static void RfCsHigh(void)
{
    HAL_GPIO_WritePin(RF_CS_GPIO_PORT, RF_CS_PIN, GPIO_PIN_SET);
}
static void RfCsLow(void)
{
    HAL_GPIO_WritePin(RF_CS_GPIO_PORT, RF_CS_PIN, GPIO_PIN_RESET);
}


void rf_event_init(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;


    /* Enable GPIOA clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStructure.Pin   = RF_PTK_PIN;
    GPIO_InitStructure.Mode  = GPIO_MODE_IT_FALLING;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RF_PTK_GPIO_PORT, &GPIO_InitStructure);

    HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
    HAL_NVIC_SetPriority(EXTI0_1_IRQn, 1, 0);
}

static void RfGpioConfigure(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< RF_SPI_CS_GPIO, RF_SPI_MOSI_GPIO, RF_SPI_MISO_GPIO
    and RF_SPI_SCK_GPIO, RF_RSTN_PIN Periph clock enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /*!< RF_SPI Periph clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();


    /*!< Configure RF_RSTN_PIN */
    GPIO_InitStructure.Pin       = 		RF_RSTN_PIN;
    GPIO_InitStructure.Speed     = 		GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Mode      = 		GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(RF_RSTN_GPIO_PORT, &GPIO_InitStructure);
    HAL_GPIO_WritePin(RF_RSTN_GPIO_PORT, RF_RSTN_PIN, GPIO_PIN_SET);

    /*!< Configure RF_SPI pins: SCK */
    GPIO_InitStructure.Pin 	     =  	RF_SPI_SCK_PIN;
    GPIO_InitStructure.Speed     = 		GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Mode      = 		GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull      = 		GPIO_NOPULL;
    GPIO_InitStructure.Alternate =		GPIO_AF10_SPI1;
    HAL_GPIO_Init(RF_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure RF_SPI pins: MOSI */
    GPIO_InitStructure.Pin 	     =  	RF_SPI_MOSI_PIN;
    GPIO_InitStructure.Mode      = 		GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull      = 		GPIO_NOPULL;
    GPIO_InitStructure.Alternate =		GPIO_AF10_SPI1;
    HAL_GPIO_Init(RF_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure RF_SPI pins: MISO */
    GPIO_InitStructure.Pin 	     =  	RF_SPI_MISO_PIN;
    GPIO_InitStructure.Mode      = 		GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull      = 		GPIO_NOPULL;
    GPIO_InitStructure.Alternate =		GPIO_AF0_SPI1;
    HAL_GPIO_Init(RF_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure RF_CS_PIN pin: RF Card CS pin */
    GPIO_InitStructure.Pin 	     =  	RF_CS_PIN;
    GPIO_InitStructure.Mode      = 		GPIO_MODE_OUTPUT_PP;
    //GPIO_InitStructure.Alternate =		GPIO_AF10_SPI1;
    HAL_GPIO_Init(RF_CS_GPIO_PORT, &GPIO_InitStructure);

    rf_event_init();

}


static void RfSpiConfigure(void)
{
    //HAL_Init();                                                     //初始化systick
    //SystemClock_Config();                                           //时钟配置
    /*初始化SPI配置*/

    Spi1Handle.Instance               = RF_SPI;                       //SPI1
    Spi1Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;    //16/4=4MHz
    Spi1Handle.Init.Direction         = SPI_DIRECTION_2LINES;       //全双工
    Spi1Handle.Init.CLKPolarity       = SPI_POLARITY_LOW;           //时钟极性低
    Spi1Handle.Init.CLKPhase          = SPI_PHASE_2EDGE ;           //数据采样从第2个时钟边沿开始
    Spi1Handle.Init.DataSize          = SPI_DATASIZE_8BIT;          //SPI数据长度为8bit
    Spi1Handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;           //先发送MSB
    Spi1Handle.Init.NSS               = SPI_NSS_SOFT;        //NSS软件模式(硬件模式)
    Spi1Handle.Init.Mode 							= SPI_MODE_MASTER;            //配置为主机
    /*SPI初始化*/
    HAL_SPI_Init(&Spi1Handle);
}


static void rf_delay(unsigned int ms)
{
    unsigned int i;
    unsigned int loopCount;
    //delay
    for(i = ms * 10; i > 0; i--)
    {
        for (loopCount = 0xffff; loopCount != 0; loopCount--);
    }
}


static void RfReset(void)
{
    //GPIO_ResetBits( RF_RSTN_GPIO_PORT, RF_RSTN_PIN);
    HAL_GPIO_WritePin(RF_RSTN_GPIO_PORT, RF_RSTN_PIN, GPIO_PIN_RESET);
    rf_delay(1);
    rf_delay(1);
    //GPIO_SetBits( RF_RSTN_GPIO_PORT, RF_RSTN_PIN);
    HAL_GPIO_WritePin(RF_RSTN_GPIO_PORT, RF_RSTN_PIN, GPIO_PIN_SET);
    //delay
    rf_delay(1);
    rf_delay(1);
}


static unsigned char RfSendByte(unsigned char byte)
{
    unsigned char pData = 0;

    if(HAL_SPI_TransmitReceive(&Spi1Handle, &byte, &pData, 1, 1000) != HAL_OK)
    {
        //printf("HAL_SPI_Transmit timerout\n");
        return  pData;
    }
    return pData;
}


void RfRegisterWrite(const unsigned char addr, const unsigned char val)
{
    RfCsLow();
    RfSendByte(addr & 0x7f);
    RfSendByte(val);
    RfCsHigh();
}


unsigned char RfRegisterRead(const unsigned char addr)
{
    unsigned char readdat;

    RfCsLow();
    RfSendByte(addr | 0x80);
    readdat = RfSendByte(0x01);
    RfCsHigh();
    return readdat;
}

static void RfRegisterInit(void)
{
    unsigned int i=0;
    unsigned int loopCount = 0;

    RfRegisterWrite(0x09,0x08);/*Debug*/
    RfRegisterWrite(0x0c,0x03);
    RfRegisterWrite(0x0e,0xA1);//
    RfRegisterWrite(0x0F,0x0A);
    RfRegisterWrite(0x10,0x54);
    RfRegisterWrite(0x1b,0x25);

   
    RfRegisterWrite(0x20,0xa4);            
    RfRegisterWrite(0x21,0x37);         
    RfRegisterWrite(0x22,0x3a);         /*VCO Config  3a*/  //3a -> 0azhangjun 20200612    
    RfRegisterWrite(0x23,0x36);         /*SYN Config   bit[7]enable wideband */ 
    //RfRegisterWrite(0x23, ((RfRegisterRead(0x23)&0x8F)|0x50));  //bit[6-4] Vco ldo output voltage 
    RfRegisterWrite(0x2F,0xe0);         //rx rssi threshold
    RfRegisterWrite(0x2E,0x00);      

    RfRegisterWrite(0x30,0x00);         //ber optimize 0x40->0x00 by 20211126 juner
    RfRegisterWrite(0x31,0x00);         
    RfRegisterWrite(0x32,0x00); 
    RfRegisterWrite(0x33,0x00); 
    RfRegisterWrite(0x34,0x00); 
    RfRegisterWrite(0x35,0x00); 
    RfRegisterWrite(0x36,0x00); 


    RfRegisterWrite(0x39,0x74); //enable demode reset 
    RfRegisterWrite(0x3A,0x61); 
    RfRegisterWrite(0x4a,0x60);
    RfRegisterWrite(0x4d,0x0b);
    RfRegisterWrite(0x4e,0x7c);//ber optimize 0x6c->0x7c by 20211126 juner
    RfRegisterWrite(0x4f,0xc5);
    ////10kps
    RfRegisterWrite(0x74,0x9d);//bit[7-6] ADC clock select
#if 0                                          
    RfRegisterWrite(0x08,0x01);   //方法1设置频偏25k    
    
    RfRegisterWrite(0x24,0x19);   //中频设置[1-0] 19  bit[3]guass enable 
    RfRegisterWrite(0x3D,0x53);   //中频设置[7-0] 53

    RfRegisterWrite(0x38,0x56);   //解调相关
    RfRegisterWrite(0x3C,0xD1);   //原91 改为D1 ADC IQ 两路互换  解决接受灵敏度问题
    RfRegisterWrite(0x3E,0x83);
    RfRegisterWrite(0x3F,0x08);

    RfRegisterWrite(0x58,0x00);
    RfRegisterWrite(0x59,0x07);
    RfRegisterWrite(0x5A,0x08);
    RfRegisterWrite(0x5B,0x09);
    RfRegisterWrite(0x5C,0x03);
    RfRegisterWrite(0x5D,0x71);
    RfRegisterWrite(0x5e,0x00);
    RfRegisterWrite(0x5f,0xDF);

    RfRegisterWrite(0x78,0xC0);  //方法2设置频偏10k --未使用 25->20K
    RfRegisterWrite(0x79,0x51);  //25->20K
    RfRegisterWrite(0x7a,0xEC);  //25->20K                   
    RfRegisterWrite(0x7b,0x5A);  //5A   1101
    
    RfRegisterWrite(0x7c,0x7C);  //7C
    RfRegisterWrite(0x7d,0x01);
    
    RfRegisterWrite(0x7e,0x00);
    RfRegisterWrite(0x7f,0x70);
#else
 /*
                        RfRegisterWrite(0x08,0x11);
                        RfRegisterWrite(0x24,0x1A);       
                        RfRegisterWrite(0x3D,0xa6); 
                        
                        RfRegisterWrite(0x38,0xc6);       
                        RfRegisterWrite(0x3C,0xC1);       
                        RfRegisterWrite(0x3E,0x03);       
                        RfRegisterWrite(0x3F,0x08);  
                        
                        RfRegisterWrite(0x58,0x01);       
                        RfRegisterWrite(0x59,0x1F);       
                        RfRegisterWrite(0x5A,0x08);       
                        RfRegisterWrite(0x5B,0x03);       
                        RfRegisterWrite(0x5C,0x0F);       
                        RfRegisterWrite(0x5D,0x71);       
                        RfRegisterWrite(0x5e,0x00);       
                        RfRegisterWrite(0x5f,0xD3); 
                        
                        RfRegisterWrite(0x78,0xC0);       
                        RfRegisterWrite(0x79,0x28);       
                        RfRegisterWrite(0x7a,0xf6);       
                        RfRegisterWrite(0x7b,0x5B);       
                        RfRegisterWrite(0x7c,0x68);       
                        RfRegisterWrite(0x7d,0x05);       
                        RfRegisterWrite(0x7e,0x00);       
                        RfRegisterWrite(0x7f,0x6C);     
                      //  RfRegisterWrite(0x23,0x7f); 
   */                     
//  9.6数据率  --频偏最低22k  
                        /*
                       RfRegisterWrite(0x08,0x01);
                       RfRegisterWrite(0x24,0x19);
                       RfRegisterWrite(0x3D,0x53);
                       
                       RfRegisterWrite(0x38,0xA8);
                       RfRegisterWrite(0x3C,0xD1);
                       RfRegisterWrite(0x3E,0x03);
                       RfRegisterWrite(0x3F,0x2C);
                       
                       RfRegisterWrite(0x58,0x00);
                       RfRegisterWrite(0x59,0x11);
                       RfRegisterWrite(0x5A,0x00);
                       RfRegisterWrite(0x5B,0x0B);
                       RfRegisterWrite(0x5C,0x01);
                       RfRegisterWrite(0x5D,0x60);
                       RfRegisterWrite(0x5E,0x00);
                       RfRegisterWrite(0x5F,0x4F);
                       
                       RfRegisterWrite(0x78,0xC0);
                       RfRegisterWrite(0x79,0x28);
                       RfRegisterWrite(0x7A,0xf6);
                       RfRegisterWrite(0x7B,0x5A);
                       RfRegisterWrite(0x7C,0xF8);
                       RfRegisterWrite(0x7D,0x06);
                       RfRegisterWrite(0x7E,0x02);
                       RfRegisterWrite(0x7F,0x2F);
                      // RfRegisterWrite(0x74,0x9D);
                    */
                        
//  4.8k数据率    
#if 0                    
                    RfRegisterWrite(0x08,0x71);
                    RfRegisterWrite(0x24,0x19);
                    RfRegisterWrite(0x3D,0x53);
                    
                    RfRegisterWrite(0x38,0xA8);
                    RfRegisterWrite(0x3C,0xD1);
                    RfRegisterWrite(0x3E,0x03);
                    RfRegisterWrite(0x3F,0x2C);
                    
                    RfRegisterWrite(0x58,0x00);
                    RfRegisterWrite(0x59,0x3F);
                    RfRegisterWrite(0x5A,0x00);
                    RfRegisterWrite(0x5B,0x14);
                    RfRegisterWrite(0x5C,0x01);
                    RfRegisterWrite(0x5D,0x32);
                    RfRegisterWrite(0x5E,0x00);
                    RfRegisterWrite(0x5F,0x4F);
                    
                    RfRegisterWrite(0x78,0xC0);
                    RfRegisterWrite(0x79,0x66);
                    RfRegisterWrite(0x7A,0x66);
                    
                    RfRegisterWrite(0x7B,0x5D);
                    RfRegisterWrite(0x7C,0x68);
                    RfRegisterWrite(0x7D,0x01);
                    RfRegisterWrite(0x7E,0x00);
                    RfRegisterWrite(0x7F,0xE1);
                    RfRegisterWrite(0x74,0x9D);
                    

#endif
//  2.4k数据率//868, 2.4k
#if 1
                    RfRegisterWrite(0x08,0x81);
                    RfRegisterWrite(0x24,0x18);
                    RfRegisterWrite(0x3D,0xAA);
                    
                    RfRegisterWrite(0x38,0xb6);
                    RfRegisterWrite(0x3C,0xD1);
                    RfRegisterWrite(0x3E,0x13);
                    RfRegisterWrite(0x3F,0x20);
                    
                    RfRegisterWrite(0x58,0x00);
                    RfRegisterWrite(0x59,0x11);
                    RfRegisterWrite(0x5A,0x00);
                    RfRegisterWrite(0x5B,0x0B);
                    RfRegisterWrite(0x5C,0x01);
                    RfRegisterWrite(0x5D,0x60);
                    RfRegisterWrite(0x5e,0x00);
                    RfRegisterWrite(0x5f,0x9F);
                    
                    RfRegisterWrite(0x78,0xC0);
                    RfRegisterWrite(0x79,0x28);
                    RfRegisterWrite(0x7a,0xF5);
                    
                    RfRegisterWrite(0x7b,0x5D);
                    RfRegisterWrite(0x7c,0xF8);
                    RfRegisterWrite(0x7d,0x03);
                    RfRegisterWrite(0x7e,0x04);
                    RfRegisterWrite(0x7f,0x67);
                    RfRegisterWrite(0x74,0x9D);
#endif

#endif
    
    RfRegisterWrite(0x15,0x21);
    RfRegisterWrite(0x07,0x5d);
    RfRegisterWrite(0x18,0x20);
    RfRegisterWrite(0x2a, 0x18);
    RfRegisterWrite(0x37,0x99);

    RfRegisterWrite(0x06,0x3a);//0x3a /*syncwordlen = 2bytes,length = 1byte,CRC,SCramble_on*/   bit[3] share fifo
    RfRegisterWrite(0x04,0x50);/*preamble length 80 bytes*/

    for(i = 10;i >0;i--)
    {
        for (loopCount = 0xffff; loopCount != 0; loopCount--);
    }
}


/*static void  RFSetRefFreq(const double freq)
{
    unsigned int Fre = 0;
    unsigned char reg73 = 0,reg72 = 0,reg71 = 0,reg70 = 0;
    Fre = (unsigned int)(freq * pow(2.0,24.0));

    reg73 =(unsigned char)(Fre & 0xFF);
    reg72 =(unsigned char)((Fre >> 8) & 0xFF);
    reg71 =(unsigned char)((Fre >> 16) & 0xFF);
    reg70 =(unsigned char)((Fre >> 24) & 0xFF);

    RfRegisterWrite(0x73,reg73);
    RfRegisterWrite(0x72,reg72);
    RfRegisterWrite(0x71,reg71);
    RfRegisterWrite(0x70,reg70);
}*/


void RfSetPA(PA_LEVEL x_dBm)
{
    unsigned char r_reg;
#if 0
    unsigned char vReg25Tbl[] =      {0x3a, 0x2b, 0x25, 0x1a, 0x0d, 0x0b, 0x09, 0x07, 0x06, 0x04, 0x03, 0x01, 0x4c,
                                      0x4a, 0x46, 0x04, 0x04, 0x05, 0x04, 0x01, 0X01, 0X01, 0X00, 0X00, 0X02, 0X01, 0X00
                                     };
    unsigned char vReg26Tbl[] =      {0xdd, 0xdd, 0xbf, 0xdd, 0xdd, 0xdd, 0xdd, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x3a,
                                      0x3a, 0x30, 0x35, 0x25, 0x11, 0X0e, 0X17, 0X11, 0X0c, 0X11, 0X0a, 0X02, 0x03, 0x03
                                     };
    unsigned char vReg25Tbl_h3[] = { 0x3f, 0xff, 0xa6, 0x95, 0x94, 0xce, 0x91, 0x09, 0x08, 0x03, \
                                     0x7f, 0x3f, 0x2f, 0x1f, 0x1c, 0x15, 0x13, 0x11, 0x10, 0x10, \
                                     0x07, 0x05, 0x05, 0x03, 0x03, 0x03, 0x03
                                   };

    unsigned char vReg26Tbl_h3[] = { 0x81, 0x81, 0x83, 0x9a, 0x82, 0x82, 0x80, 0x83, 0x9f, 0x98, \
                                     0x7f, 0x64, 0x67, 0x7d, 0x7d, 0x7c, 0x77, 0x74, 0x75, 0x65, \
                                     0x6c, 0x77, 0x67, 0x7d, 0x6b, 0x5e, 0x56
                                   };
#else
    unsigned char vReg25Tbl_h4[] = {0x3f, 0x38, 0x25, 0x1a, 0x0f, 0x0d, 0x0b, 0x0a, 0x09, 0x08, 0x04, 0x03, 0x86,
                                    0x82, 0x01, 0x01, 0x02, 0x02, 0x00, 0x00, 0x24, 0x20, 0x16, 0x14, 0x11, 0x0d, 0x0d
                                   };

    unsigned char vReg26Tbl_h4[] = {0xb0, 0xb0, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x9f, 0x9f, 0xbf, 0x8f, 0x80,
                                    0xbf, 0x9f, 0x84, 0x81, 0x80, 0xad, 0x88, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x72, 0x62
                                   };



    unsigned char vReg25Tbl_h31[] = { 0xbf, 0xff, 0x1d, 0x1c, 0x0f, 0x0e, 0x07, 0x06, 0x05, 0x04, \
                                      0x03, 0x3f, 0x2f, 0x2f, 0x1d, 0x17, 0x13, 0x11, 0x10, 0x10, \
                                      0x07, 0x05, 0x05, 0x03, 0x03, 0x03, 0x03
                                    };

    unsigned char vReg26Tbl_h31[] = { 0x83, 0x81, 0xaf, 0x82, 0x8f, 0x85, 0x95, 0xbf, 0x81, 0xab, \
                                      0x81, 0x68, 0x6b, 0x5c, 0x75, 0x72, 0x7b, 0x79, 0x7a, 0x68, \
                                      0x6f, 0x7c, 0x6a, 0x7f, 0x6e, 0x62, 0x58
                                    };
#endif
    g_paValue = x_dBm;
    r_reg = RfRegisterRead(0x47);
    if( (r_reg & 0x07) == 0x04 )
    {
        RfRegisterWrite(0x25, vReg25Tbl_h4[x_dBm]);
        RfRegisterWrite(0x26, vReg26Tbl_h4[x_dBm]);
    }
    else
    {
        RfRegisterWrite(0x25, vReg25Tbl_h31[x_dBm]);
        RfRegisterWrite(0x26, vReg26Tbl_h31[x_dBm]);
    }
}

static void RfSetSyncLockRssi(void)
{
    RfRegisterWrite(0x3e, RfRegisterRead(0x3e) | 0x40);
}

static void RfSetVcoFreq(const double freq)
{
    unsigned int Fre = 0;
    unsigned char reg77 = 0, reg76 = 0, reg75 = 0, reg74 = 0, temp = 0;
    Fre = (unsigned int)(freq * pow(2.0, 20.0));

    reg77 = (unsigned char)(Fre & 0xFF);
    reg76 = (unsigned char)((Fre >> 8) & 0xFF);
    reg75 = (unsigned char)((Fre >> 16) & 0xFF);
    reg74 = (unsigned char)(((Fre >> 24) & 0xFF) | (RfRegisterRead(0x74) & 0xc0));

    temp = RfRegisterRead(0x00);
    RfRegisterWrite(0x00, (0x80 | temp));

    RfRegisterWrite(0x77, reg77);
    RfRegisterWrite(0x76, reg76);
    RfRegisterWrite(0x75, reg75);
    RfRegisterWrite(0x74, reg74);
}


static void  RfSetFreq_N(const unsigned char N)
{
    if(N > 0x7F)
        return;
    RfRegisterWrite(0x00, (0x80 | N));
}


static void RfSetFreqStep(double step)
{
    unsigned int fre = 0;
    unsigned char reg1 = 0, reg2 = 0, reg3 = 0;
    fre = (unsigned int)(step * pow(2.0, 20.0));
    reg3 = (unsigned char)(fre & 0xFF);
    reg2 = (unsigned char)((fre >> 8)  & 0xFF);
    reg1 = (unsigned char)((fre >> 16) & 0x7F);
    RfRegisterWrite(0x03, reg3);
    RfRegisterWrite(0x02, reg2);
    RfRegisterWrite(0x01, reg1);
}


double g_freq = 476.3;
void RfFreqSet(const double f0, const unsigned char N, const double step)
{

    g_freq = f0;
    RfSetVcoFreq(f0);
    RfSetFreq_N(N);
    RfSetFreqStep(step);
}


//清空发送区域
static void RfClrTxFifoWrPtr(void)
{
    RfRegisterWrite(0x53, 0x80);     /*Reset FIFO write Pointer*/
}

//获取包状态
unsigned char RfGetPktStatus(void)
{
    return HAL_GPIO_ReadPin(RF_PTK_GPIO_PORT, RF_PTK_PIN);
}

//读场强值
unsigned char RfReadRssi(void)
{
    unsigned char r_reg;

    r_reg = RfRegisterRead(0x43);
    return r_reg / 2;
}

//发送数据
static void RfWriteFIFO(const    unsigned char *SrcBuf, unsigned char len)
{
    unsigned char i = 0;

    RfCsLow();
    RfSendByte(0x55 & 0x7F);
    for(i = 0; i < len; i++)
    {
        RfSendByte(*(SrcBuf++));
    }
    RfCsHigh();
}

//读RF 数据
void RfReadFIFO(unsigned char *StoreBuf, unsigned char Len)
{
    unsigned char i = 0;
    RfCsLow();
    RfSendByte(0x52 | 0x80);
    for(i = 0; i < Len; i++)
    {
        *(StoreBuf + i) =  RfSendByte(0xFF);
    }
    RfCsHigh();
}

static int systemStatus = 0;
int RfSystemStatus(void)
{
    return systemStatus;
    /*
      switch(RfRegisterRead(0x46))
      {
        case 0x80:
           return systemStatus;
        break;
        case 0x20:
          return 2;
        break;
        case 0x40:
          return 1;
        break;
        case 0x10:
          return 6;
        break;
        case 0x08:
          return 7;
        case 0x04:
          return 8;
        case 0x02:
          return 9;
        case 0x01:
          return 10;
        break;
        default:
          break;
      }*/
}



void RfIdleEn(void)
{
    RfRegisterWrite(0x60, 0xff);
    while(RfRegisterRead(0x46) != 0x80);
    systemStatus = 0;
}

void RfRecEn(void)  //接收状态
{
    RfRegisterWrite(0x51, 0x80);
    RfIdleEn();
    RfRegisterWrite(0x66, 0xff);
    while(RfRegisterRead(0x46) != 0x20);
    systemStatus = 2;
}

void RfTranEn(void)
{
    RfIdleEn();
    RfRegisterWrite(0x65, 0xff);
    while(RfRegisterRead(0x46) != 0x40);
    systemStatus = 1;
}

void RfSleepEn(void)
{
    RfIdleEn();
    RfRegisterWrite(0x67, 0xff);
    systemStatus = 3;
}

void RfStandByEn(void)
{
    RfIdleEn();
    RfRegisterWrite(0x68, 0xff);
    systemStatus = 4;
}


//发送单音载波
void RF_TxCW(void)
{
    LedOff(LED1_PORT, LED1_PIN);// send led on
    RfIdleEn();
    RfRegisterWrite(0x24, (RfRegisterRead(0x24) | 0x80));
    RfRegisterWrite(0x06, (RfRegisterRead(0x06) & 0xFC));
    RfTranEn();
}

void RfTestPackageSend(const unsigned char *buffer, const unsigned char size)
{
    //volatile uint32_t send_count = 0;
    //RfTxLedOn();
    LedOff(LED1_PORT, LED1_PIN);// send led on
    //SEGGER_RTT_printf(0, "<%d>send %d byte...\r\n",send_count++,  size);
    /*Fix SPI concurrency conflicts, disable irq */
    __disable_irq();
    RfIdleEn();
    RfClrTxFifoWrPtr();
    RfWriteFIFO(&buffer[1], size);
    RfTranEn();
    __enable_irq();
}

uint8_t Rf_Busy = 0;
//发送数包
void RfDataPackageSend(const unsigned char *buffer, const unsigned char size)
{
    //volatile uint32_t send_count = 0;
    //SEGGER_RTT_printf(0, "<%d>send %d byte...\r\n",send_count++,  size);
    /*Fix SPI concurrency conflicts, disable irq */
    if(size > 0)
    {
        if(Rf_Busy == 0)
        {
            unsigned char buf[264] = {0};

            LedOff(LED1_PORT, LED1_PIN);// led on
            buf[0] = size;
            memcpy(buf + 1, buffer, size);
            //__disable_irq();
            RfIdleEn();
            RfClrTxFifoWrPtr();
            RfWriteFIFO(&buf[0], size + 1);
            RfTranEn();
            //__enable_irq();
        }
    }


}

//接收数据包
int RfPackageRecv(char *buf)
{
    int len;
    unsigned char rx_rssi = 0;
    Rf_Busy = 1;
    RfRegisterWrite(0x51, 0x80);
    len = RfRegisterRead(0x52 | 0x80);
    if (len == 0)
    {
        RfRecEn();
        Rf_Busy = 0;
        return -3;
    }
    else
    {
        rx_rssi = RfReadRssi();
        RfReadFIFO((uint8_t *)buf, len);
        RfRecEn();
        printf("rece data len = %d  rssi = -%d dB\r\n", len, rx_rssi);
        Rf_Busy = 0;
        return len;
    }

}

//RF 初始化
void RfConfigure(void)
{
    unsigned int i = 0;
	UART_Init();
    //初始化gpio
    RfGpioConfigure();
    //GPIO_SetBits(LED_RF_RX_PORT, LED_RF_RX_PIN);
    //GPIO_SetBits(LED_RF_TX_PORT, LED_RF_TX_PIN);
    RfCsHigh();
    //初始化rf spi
    RfSpiConfigure();
    //重启芯片
    rf_delay(1);
    HAL_Delay(200);    //delay_ms(200);
    RfReset();

	//RfRegisterWrite(0x70, 0x12);
	//i = RfRegisterRead(0x70);

    //初始化rf 参数
    RfRegisterInit();
    //设置参考频率
    RfRegisterWrite(0x70, 0x12);
    RfRegisterWrite(0x71, 0x14);
    RfRegisterWrite(0x72, 0x7A); // 6D 48    A1  7A 18.08
    RfRegisterWrite(0x73, 0xE1); // 32 00    84  E1
    //设置锁频
    RfSetSyncLockRssi();
    //设置中心频点
    RfFreqSet(434, 0, 0); //RfFreqSet(496.3,0,0); //RfFreqSet(434, 0, 0);// 434
    //设置发射功率
    RfSetPA(DBM20);
    //设置为接收态
    RfRecEn();
    //打印初始化参数
    for(i = 0; i <= 0x7f; i++)
    {
        printf("read  reg0x%02x = %02x \n", i, RfRegisterRead(i));
    }
    RfRecEn();

}


void EXTI0_1_IRQHandler(void)
{

    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != 0x00u)
        //if (RESET != EXTI_GetITStatus(EXTI_LINE3))
    {
        unsigned char ret = 0;
        __disable_irq();

        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
        //	EXTI_ClrITPendBit(EXTI_LINE3);
        ret = RfRegisterRead(0x40);
        if(ret & (1 << 6))
        {
            if(!(ret & (1 << 7)))
            {
                g_preamble_timeout = 200;
                printf("int type: pre\n");
            }
            else if (!(ret & (1 << 5))) // add CRC check
            {
                printf("int type: recv\n");
                g_preamble_timeout = 0;
                g_rece_falg = 0x01;
                LedOff(LED2_PORT, LED2_PIN);
            }
            else
            {
                g_rece_falg = 0x02;
                //RfRecEn();
                printf("event");
                g_preamble_timeout = 0;
            }
        }
        else
        {
            //printf("done \n\r");
            g_preamble_timeout = 0;
            RfRecEn();
            LedOn(LED1_PORT, LED1_PIN);
            //printf(0, "int type: transmit\n");
        }
        __enable_irq();
    }

}

unsigned char   gTestBerIndex = 0;
unsigned char   gTestBerSendIndex = 0;
unsigned char   gTestBerTatol = 0;
extern uint16_t tim_rfsend;

#define RF_RSSI_THRESHOLD  65
#define         TEST_BER_DATA_LEN  18
unsigned char   gSendBuf[TEST_BER_DATA_LEN]="\x0A\x01\x68\x88\x88\x88\x88\x30\x48\x68\x9E\x04\x33\x33\x93\x3D\x40\x16";

extern unsigned char mRfRxBuf[264];
void RfDataProcess(void)
{
    //Clear_Wdt();
    if(0x02 == g_rece_falg )
    {
        g_rece_falg = 0;
        memset(mRfRxBuf, 0, 255);
        RfPackageRecv((char *)mRfRxBuf);
    }
    if(0x01 == g_rece_falg )
    {
        uint16_t len = 0;
        g_rece_falg = 0;

        memset(mRfRxBuf, 0, 255);
        len = RfPackageRecv((char *)mRfRxBuf);
        if(len  > 0)
        {
            uint8_t i;
            if(len  > 0 )
            {
                //RfRxLedOn();
                //LedOff(LED2_PORT, LED2_PIN);
                //Soft_Timer_ActiveEvent(50, RfRxLedOff, Timer_ActiveResetMode);
                for( i = 0; i < len; i++)
                {
                    printf("%02x ", mRfRxBuf[i]);
                }
                printf("\n");
                if(mRfRxBuf[0] == 0x0A && 0x68 == mRfRxBuf[2])
                {
                    gTestBerTatol = mRfRxBuf[0];
                    gTestBerIndex = mRfRxBuf[1];
                    printf("tatol package:%d,sended: %d\n", gTestBerTatol, gTestBerIndex);
                }
								LedOn(LED2_PORT, LED2_PIN);
            }
        }
				else
				{
					LedOn(LED2_PORT, LED2_PIN);
				}
    }
		
		if(tim_rfsend >= 220)
		{
			tim_rfsend = 0;
			//if(RfReadRssi() > RF_RSSI_THRESHOLD)
			{
					gSendBuf[1] = ++gTestBerSendIndex;
					RfDataPackageSend(gSendBuf,TEST_BER_DATA_LEN);
					printf("\r\n send success  len = %d \r\n", TEST_BER_DATA_LEN);
			}
		}
}

extern UART_HandleTypeDef UartHandle;
extern uint8_t aRxBuffer[128];
void usart1DataProcess( void )
{
  uint8_t  regValue;
  uint8_t buf[256]={0};

	/*UART POLLING*/
	if (HAL_UART_Receive(&UartHandle, (uint8_t *)aRxBuffer, 12, 2000) != HAL_OK)
	{
		//printf("\n HAL_UART_Receive err! \n");
		return;
	}
//	else
//	{
//		 for(int i = 0; i < 12; i++)
//		{
//				printf("i 0x%02x = %02x \n", i, aRxBuffer[i]);
//		}
//	}

  //处理接收到的数据帧
  //if( Uart1Data.RxLen > 0 && 0 == Uart1Data.RxTimer )
  {
    memset(buf,0,256);
    memcpy(buf,"\xFA\xFB",2);
    //if(((Uart1Data.RxLen >= 4) && (Uart1Data.RxLen <= 8)&&(aRxBuffer[0] == 0xFA) && (aRxBuffer[1] == 0xFB) ))
		if(((aRxBuffer[0] == 0xFA) && (aRxBuffer[1] == 0xFB) ))
    {	
      switch( aRxBuffer[2])
      {
          case 0x00:  //直接读寄存器值
          regValue = RfRegisterRead(aRxBuffer[3]);
          buf[2] = 0x00;
          buf[3] = aRxBuffer[3];
          buf[4] = regValue;
          //usart1_send((char*)buf,5);
					HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 5, 5000);
          break;
          case 0x01: //直接写寄存器值
          //if( >= 5)
          {
            RfRegisterWrite(aRxBuffer[3],aRxBuffer[4]);
            regValue = RfRegisterRead(aRxBuffer[3]);
            buf[2] = 0x01;
            buf[3] = aRxBuffer[3];
            buf[4] = regValue;
            //usart1_send((char*)buf,5);
						HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 5, 5000);
          }
          break;
          case 0x02://发送M0 M1 M2 M4
            RfIdleEn();
            RfRegisterWrite(0x24,(RfRegisterRead(0x24)&0x7F));		//Bit[7] 设置载波模式寄存器
            RfRegisterWrite(0x06,((RfRegisterRead(0x06)&0xFC)|0x20));		//bit[1-0] 控制连续发生载波
            switch(aRxBuffer[3])
            {
              case 0:
                 RF_TxCW();
                //rf_do_TestRfPower_proc(M4);
                break;
              case 1:
                 rf_do_TestRfPower_proc(M0);
                break;
              case 2:
                 rf_do_TestRfPower_proc(M1);
                break;
              case 3:
                 rf_do_TestRfPower_proc(M4);
                break;
            }
            buf[2] = 0x02;
            buf[3] = aRxBuffer[3];
            //usart1_send((char*)buf,4);
						HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 4, 5000);
          break;
          case 0x03: //设置工作模式
            //RfIdleEn();
            switch(aRxBuffer[3])
            {
              case 0://空闲
                RfIdleEn();
                break;
              case 1://发送
                RfTranEn();
                break;
              case 2://接收
                RfRecEn();
                break;
              case 3://睡眠
                RfSleepEn();
                break;
              case 4://准备
                RfStandByEn();
                break;
              case 5://读取
                 
                break;
            }
            buf[2] = 0x03;
            buf[3] =  RfSystemStatus();
            //usart1_send((char*)buf,4);
						HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 4, 5000);
            break;
          case 0x04: //读中心频点
            {
              buf[2] = 0x04;
              buf[3] = 0x01;
              buf[4] = (RfRegisterRead(0x74)&0x3F);
              buf[5] = RfRegisterRead(0x75);
              buf[6]= RfRegisterRead(0x76);
              buf[7] = RfRegisterRead(0x77);
              //usart1_send((char*)buf,8);
							HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 8, 5000);
            }
          break;
          case 0x05: //设置中心频点
            RfIdleEn();
            //if(Uart1Data.RxLen >= 6)
            {
              if(aRxBuffer[3])
              {
								  unsigned int freq = 0;
                  double f0  = 0.0;
                  //if(Uart1Data.RxLen < 8)
                  //{
                    //return;
                  //}

                  //RfRegisterWrite(0x74,(aRxBuffer[4]| RfRegisterRead(0x74)&0xC0));
                  //RfRegisterWrite(0x75,aRxBuffer[5]);
                  //RfRegisterWrite(0x76,aRxBuffer[6]);
                  //RfRegisterWrite(0x77,aRxBuffer[7]);

                  freq = aRxBuffer[4]<<24;
                  freq += aRxBuffer[5]<<16;
                  freq +=aRxBuffer[6]<<8;
                  freq += aRxBuffer[7];
                 
                  f0 = (double)freq/1048576+0.0000005;
                  RfFreqSet(f0, 0, 0);
              }else
              {
                if(aRxBuffer[4] > 2 || aRxBuffer[5] >32)
                {
                  return;
                }
                if(aRxBuffer[4])
                {
                  g_Channel  = 2*aRxBuffer[5] + 1;
                }else
                {
                  g_Channel  = 2*aRxBuffer[5] ;
                }
                RfFreqSet(((double)Default_Freq[g_Channel]) / 10, 0, 0);
              }
              buf[2] = 0x05;
              buf[3] = 0x01;
              buf[4] = (RfRegisterRead(0x74)&0x3F);
              buf[5] = RfRegisterRead(0x75);
              buf[6] = RfRegisterRead(0x76);
              buf[7] = RfRegisterRead(0x77);
              //usart1_send((char*)buf,8);
							HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 8, 5000);
              RfRecEn();
            }
          break;
          
          case 0x06: //读中心频偏
            {
              buf[2] = 0x06;
              buf[3] = (RfRegisterRead(0x78)&0x0F);
              buf[4] = RfRegisterRead(0x79);
              buf[5] = RfRegisterRead(0x7a);
              //usart1_send((char*)buf,6);
							HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 6, 5000);
            }
          break;
          case 0x07: //写中心频偏
            {
                  RfIdleEn();
                  RfRegisterWrite(0x78,(aRxBuffer[4]| (RfRegisterRead(0x78)&0x70)|0x80) );
                  RfRegisterWrite(0x79,aRxBuffer[5]);
                  RfRegisterWrite(0x7a,aRxBuffer[6]);
                  
                  buf[2] = 0x06;
                  buf[3] = (RfRegisterRead(0x78)&0x0F);
                  buf[4] = RfRegisterRead(0x79);
                  buf[5] = RfRegisterRead(0x7a);
                  //usart1_send((char*)buf,6);
                  HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 6, 5000);
                  RfRecEn();
            }
          break;
          
          case 0x08: //w读参考频率
            {
              buf[2] = 0x08;
              buf[3] = (RfRegisterRead(0x70)&0x7F);
              buf[4] = RfRegisterRead(0x71);
              buf[5] = RfRegisterRead(0x72);
              buf[6] = RfRegisterRead(0x73);
              //usart1_send((char*)buf,7);
							HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 7, 5000);
            }
          break;
          case 0x09: //写参考频率
            {
                  RfIdleEn();
                  RfRegisterWrite(0x70,(aRxBuffer[4]| (RfRegisterRead(0x70)&0x80)));
                  RfRegisterWrite(0x71,aRxBuffer[5]);
                  RfRegisterWrite(0x72,aRxBuffer[6]);
                  RfRegisterWrite(0x73,aRxBuffer[7]);
                  
                  buf[2] = 0x09;
                  buf[3] = (RfRegisterRead(0x70)&0x7F);
                  buf[4] = RfRegisterRead(0x71);
                  buf[5] = RfRegisterRead(0x72);
                  buf[6] = RfRegisterRead(0x73);
                  //usart1_send((char*)buf,7);
                  HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 7, 5000);
                  RfRecEn();
            }
          break;
          case 0x0a: //计算参考频率并校准写入
            {
                   double setFreq = 0.0,refFreq = 0.0,watchFreq = 0.0,setRefFreq = 0.0;
                   unsigned int f0 =0;
                   
                  //都观察频点
                  f0 = aRxBuffer[4]<<24;
                  f0+= aRxBuffer[5]<<16;
                  f0+= aRxBuffer[6]<<8;
                  f0+= aRxBuffer[7];
                  watchFreq = (double)f0/1048576;
                  //读中心频点
              
                  f0=(RfRegisterRead(0x74)&0x3F)<<24;
                  f0+= RfRegisterRead(0x75)<<16;
                  f0+= RfRegisterRead(0x76)<<8;
                  f0+= RfRegisterRead(0x77);
                  setFreq = (double)f0/1048576;
                  //都参考频点
                  f0=(RfRegisterRead(0x70)&0x7F)<<24;
                  f0+= RfRegisterRead(0x71)<<16;
                  f0+= RfRegisterRead(0x72)<<8;
                  f0+= RfRegisterRead(0x73);
                  setRefFreq = (double)f0/16777216;
                  
              
                  //计算参考频率
                  refFreq= setRefFreq*watchFreq/setFreq;
                  /*
                  printf("\n watchFreq = %f \n",watchFreq);
                  printf("\n setFreq = %f \n",setFreq);
                  printf("\n setRefFreq = %f \n",setRefFreq);
                  printf("\n refFreq = %f \n",refFreq);
                  */
                  f0 = (unsigned int)refFreq*16777216;
                  
                  if(aRxBuffer[3])
                  {
                    RfIdleEn();
                    RfRegisterWrite(0x70,((f0>>24)| (RfRegisterRead(0x70)&0x80)));
                    RfRegisterWrite(0x71,((f0>>16)&0xFF));
                    RfRegisterWrite(0x72,((f0>>8)&0xFF));
                    RfRegisterWrite(0x73,(f0&0xFF));
                    RfRecEn();
                  }
                  buf[2] = 0x0A;
                  buf[3] = ((f0>>24)&0xFF);
                  buf[4] = ((f0>>16)&0xFF);
                  buf[5] = ((f0>>8)&0xFF);
                  buf[6] = (f0&0xFF);
                  //usart1_send((char*)buf,7);
									HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 7, 5000);
            }
          break;
          case 0x0b: //设置流模式
              RfRegisterWrite(0x06,(RfRegisterRead(0x06)&0xFD));
              buf[2] = 0x0b;
              buf[3] = 00;
              //usart1_send((char*)buf,4);
              HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 4, 5000);
          break;
          case 0x0c: //设置包模式
              RfRegisterWrite(0x06,(0x02|(RfRegisterRead(0x06)&0xFD)));
              buf[2] = 0x0c;
              buf[3] = 00;
              //usart1_send((char*)buf,4);
              HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 4, 5000);
              RfRecEn();
          break;
          case 0x0d://读去当前信号强度
              buf[2] = 0x0d;
              buf[3] = RfRegisterRead(0x43);
              //usart1_send((char*)buf,4);
              HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 4, 5000);
          break;
          case 0x20: //功率读 Reg
              buf[2] = 0x21;
              buf[3] = g_paValue;
              //usart1_send((char*)buf,4);
              HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 4, 5000);
              RfRecEn();
          break;
          case 0x21: //功率写 Reg
           if( aRxBuffer[3] <= 26)
           {
              RfSetPA((PA_LEVEL)aRxBuffer[3]);
              buf[2] = 0x21;
              buf[3] = g_paValue;
              //usart1_send((char*)buf,4);
              HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, 4, 5000);
              RfRecEn();
           }
          break;		
       }
    }
//    else
//    {
//        if(Uart1Data.RxLen > 0)
//        {
//					  gRfUserTxSendFlag = 1;
//            Uart1Data.TxLen = Uart1Data.RxLen;
//            gRfTxSendFlag = 1;
//            memset(Uart1Data.TxBuf,0,UART_BUF_SIZE);
//            memcpy(Uart1Data.TxBuf,aRxBuffer,Uart1Data.TxLen);
//        }
//    }
//    Uart1Data.RxLen = 0;
  }
}

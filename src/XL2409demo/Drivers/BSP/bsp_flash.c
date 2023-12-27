#include "bsp_flash.h"
#include <math.h>

//写入FLASH (4位)
void Flash_Write(uint32_t WriteAddr, uint32_t *pBuffer)
{

    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PAGEError = 0;
    uint32_t flash_program_start = WriteAddr;                              //flash写起始地址
    uint32_t flash_program_end = (WriteAddr + sizeof(pBuffer));           //flash写结束地址
    uint32_t *src = pBuffer;                                                          //数组指针

    HAL_FLASH_Unlock();                                                                 //解锁FLASH
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGEERASE;                            //擦写类型FLASH_TYPEERASE_PAGEERASE=Page擦, FLASH_TYPEERASE_SECTORERASE=Sector擦
    EraseInitStruct.PageAddress = WriteAddr;                                //擦写起始地址
    EraseInitStruct.NbPages  = 2;                                                       //需要擦写的页数量
    HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);                                    //执行page擦除,PAGEError返回擦写错误的page,返回0xFFFFFFFF,表示擦写成功

    do
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src) == HAL_OK) //执行Program; FLASH_TYPEPROGRAM_PAGE形参无效,需要修改库
        {
            flash_program_start += 128;                                                     //flash起始指针指向第一个page
            src += 32;                                                                      //更新数据指针
        }
    }
    while (flash_program_start < flash_program_end);
    HAL_FLASH_Lock();                                                                   //锁定FLASH
}

//写入FLASH (1位)
void Flash_Write_8(uint32_t WriteAddr, uint8_t *pBuffer1, uint16_t length)
{
    uint8_t mid_pBuffer[length + 3];
    uint16_t flash_length = ceil((float)length / 4.0);
    uint32_t pBuffer2[flash_length];
    uint16_t i;
    for(i = 0; i < length + 3; i++)
    {
        if(i < length)
        {
            mid_pBuffer[i] = pBuffer1[i];
        }
        else
        {
            mid_pBuffer[i] = 0xff;
        }

    }
    for(i = 0; i < flash_length ; i++)
    {
        pBuffer2[i] = (mid_pBuffer[0 + i * 4] << 24) | (mid_pBuffer[1 + i * 4] << 16) | (mid_pBuffer[2 + i * 4] << 8) | mid_pBuffer[3 + i * 4];
    }
    Flash_Write(WriteAddr, pBuffer2);
}


//对输入地址开始读取数据，返回读到的该地址的数据
uint32_t FLASH_ReadWord(uint32_t faddr)
{
    return *(uint32_t *)faddr;
}


//数据读取4位 length为想要的长度
void FLASH_Read(uint32_t ReadAddr, uint32_t *pBuffer, uint16_t length)
{
    uint16_t i;
    for(i = 0; i < length; i++)
    {
        pBuffer[i] = FLASH_ReadWord(ReadAddr);//对字节读取
        ReadAddr += 4; //地址向后偏移
    }
}

//数据读取1位 length为想要的pBuffer1的长度
void FLASH_Read_8(uint32_t ReadAddr, uint8_t *pBuffer1, uint16_t length)
{
    uint16_t flash_length = ceil((float)length / 4.0);
    uint32_t pBuffer2[flash_length];
    FLASH_Read(ReadAddr, pBuffer2, flash_length);
    uint16_t i;
    for(i = 0; i < flash_length ; i++)
    {
        if((0 + 4 * i) < length)
        {
            pBuffer1[0 + 4 * i] = (pBuffer2[i] >> 24) & 0xff;
        }
        if((1 + 4 * i) < length)
        {
            pBuffer1[1 + 4 * i] = (pBuffer2[i] >> 16) & 0xff;
        }
        if((2 + 4 * i) < length)
        {
            pBuffer1[2 + 4 * i] = (pBuffer2[i] >> 8) & 0xff;
        }
        if((3 + 4 * i) < length)
        {
            pBuffer1[3 + 4 * i] = pBuffer2[i] & 0xff;
        }
    }

}

//添加配对信息 nums为总计多少个配对的发射端
void FLASH_AddMate(uint32_t WriteAddr, uint8_t *pBuffer, uint16_t nums)
{
    uint32_t flash_mid[32];
    FLASH_Read(WriteAddr, flash_mid, 32);
    flash_mid[nums * 2] =  (pBuffer[0] << 24) | (pBuffer[1] << 16) | (pBuffer[2] << 8) | pBuffer[3];
    flash_mid[nums * 2 + 1] =  (pBuffer[4] << 24) | (pBuffer[5] << 16) | (pBuffer[6] << 8) | pBuffer[7];
    Flash_Write(WriteAddr, flash_mid);
}

//修改自身信息
void Flash_ChangeInfor(uint32_t WriteAddr, uint8_t *pBuffer)
{
    uint32_t flash_mid[32];
    FLASH_Read(WriteAddr, flash_mid, 32);
    flash_mid[1] = (pBuffer[0] << 24) | (pBuffer[1] << 16) | (pBuffer[2] << 8) | pBuffer[3];
    Flash_Write(WriteAddr, flash_mid);
}

//擦除
void Flash_Erase(uint32_t UserAddr)
{
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PAGEError = 0;
    HAL_FLASH_Unlock();                                                                 //解锁FLASH
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGEERASE;                            //擦写类型FLASH_TYPEERASE_PAGEERASE=Page擦, FLASH_TYPEERASE_SECTORERASE=Sector擦
    EraseInitStruct.PageAddress = UserAddr;                                             //擦写起始地址
    EraseInitStruct.NbPages  = 2;                                                       //需要擦写的页数量
    HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);                                    //执行page擦除,PAGEError返回擦写错误的page,返回0xFFFFFFFF,表示擦写成功
    HAL_FLASH_Lock();
}


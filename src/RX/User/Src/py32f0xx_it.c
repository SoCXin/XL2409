/*****************************************
 * 此文件一般不用
 * 中断服务函数都是直接写在对于的驱动文件里面
******************************************/
#include "main.h"
#include "py32f0xx_it.h"

/*不可屏蔽的中断处理*/
void NMI_Handler(void)
{
}

/*硬件故障中断处理*/
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/*通过SWI指令处理系统服务调用*/
void SVC_Handler(void)
{
}

/*处理对系统服务的可挂起请求*/
void PendSV_Handler(void)
{
}

/*处理系统时钟定时器*/
void SysTick_Handler(void)
{
  HAL_IncTick();
}



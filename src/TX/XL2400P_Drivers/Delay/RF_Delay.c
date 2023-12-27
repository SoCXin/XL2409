#include "RF_Delay.h"


//微秒延时函数
void DelayUs(unsigned char Time)
{
	unsigned char a;
	for(a=0;a<Time;a++)
	{
	}
	Time>>=1;
	for(a=0;a<Time;a++)
	{
	}
	Time>>=2;
	for(a=0;a<Time;a++)
	{
	}
} 

//毫秒延时函数
void DelayMs(unsigned char Time)
{
	unsigned char a,b;
	for(a=0;a<Time;a++)
	{	
		for(b=0;b<5;b++)
		{
		 	DelayUs(195); 	
		}
	}
}



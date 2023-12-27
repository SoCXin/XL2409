#include "bsp_state_machine.h"
#include <stdio.h>
#include "bsp_expand.h"
#include "bsp_encode.h"

State *pCurrentState;

//定义状态
/**************************/
//接收端
State R_State =
{
    R_Tap,
    R_Selflock,
    R_Interlock,//
    R_Toggle,
    R_Clear,//
    Ignore,
    R_Receive,
};

/**************************/
//发射端
State T_State =
{
    LedBlinkTwice,
    LedBlinkTwice,
    LedBlinkTwice,//
    T_Toggle,
    LedBlinkTwice,//
    T_Keys_State,
    T_Receive
};


/***********************************************
初始化系统当前状态指针，指定系统的起始状态
************************************************/
void Init_State_Machine(void)
{
	//初始为接收
    pCurrentState = &R_State;
	
  //初始为发射
    // pCurrentState = &T_State;
    // encode_flag.t_or_r_mode_flag = 1;
}



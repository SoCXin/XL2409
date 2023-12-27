#ifndef __BSP_STATE_MACHINE_H
#define __BSP_STATE_MACHINE_H

typedef struct
{
    void (* pt_or_r_studykeynum_1)(); //学习按键按下1次反馈
    void (* pt_or_r_studykeynum_2)(); //学习按键按下2次反馈
    void (* pt_or_r_studykeynum_3)(); //学习按键按下3次反馈
    void (* pt_or_r_studykeynum_5)(); //学习按键按下5次反馈
    void (* pt_or_r_studykeynum_8)(); //学习按键按下8次反馈
    void (* pt_or_r_keystate)();  //四个按键按下反馈（发射端）
    void (* pt_or_r_response)();  //收到信号处理
} State;

void Init_State_Machine(void);
extern State *pCurrentState;

extern State R_State;
extern State T_State;

#endif

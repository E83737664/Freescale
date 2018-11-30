#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "headfile.h"
#include "Fuzzy.h"


void Cascade_Control_Inside(void);
void Cascade_Control_Outside(void);
double Yijielvbo(double angle_m, double gyro_m);  //角度和角速度
void velocity(void);
void DirectionControl(void);
void DirectionControl_Inside(void);
void IncPIDCalc_Outside(void);  //直立控制函数PID算法
void IncPIDCalc_Inside(void);  //直立控制函数PID算法
void Speed_Get(void);
void Motor_Current(void);
void Pwm_Control_Out(void);
void CurrentControl(int Motor_Left_Current_Set, int Motor_Right_Current_Set);
void Inductance_GetConversionValue(void);
void Stop(void);

#endif

#ifndef _PATH_PROCESSING_INDUCTANCE_H_
#define _PATH_PROCESSING_INDUCTANCE_H_

#include "headfile.h"
#include "math.h"

/*½Ó¿Úº¯Êý*/
void Get_iErrordirect(void);
float Math_Sqrt(float Value,int cnt);
void Track_Check(void);
void Ramp_Judge(void);
void Bump_Judge(void);
void Ring_Judge(void);
void Special_Judge(void);
void Circle_Judge(void);
void Deviate_Revise(void);
void Island_Revise(void);
void Bump_Revise(void);
void Ramp_Revise(void);
void Regular_Track(void);
void FM_Control(void);

#endif


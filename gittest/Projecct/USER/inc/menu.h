#ifndef _MENU_H_
#define _MENU_H_

#include "headfile.h"

extern const uint8_t LargeChars[];

extern uint8_t mode;
extern uint8_t Protect;
extern int Finish_Symbol;
extern int SetBalance;
extern double angleP;
extern double angleD;
extern double balanceP;  
extern double balanceD;  
extern int SetSpeed;
extern double speedP;
extern double speedI;
extern int Range_I;
extern double directP;
extern double directD, directDD;
extern double directP_Inside, directD_Inside;
 
extern uint8_t Ring_Direction[20];
extern uint8_t Ring_Size[20];
extern uint8_t Ring_Num;

extern uint8_t Ramp_Num;
extern int Ramp_Time[7];
extern int Ramp_Angle[7];

extern uint8_t Circle_Num;

extern int xjb,Ring_Delay_50;

extern uint8 Special_Start[10],Special_Angel[10],Special_Num;
extern uint16 Special_Delay[10],Special_Menue_InTime;
#define menu_num 38
#define sector_num 240

struct Menu
{
	char name[10];
	uint16_t num;
	double multiple;
	uint8_t multiple_display;
};



#if(menu_num >= 1)
#define name0    	        "mode"
#define variable0          mode 
#define multiple0           1
#define multiple_display0   1
#endif 

#if(menu_num >= 2)
#define name1    	        "Protect"
#define variable1          Protect 
#define multiple1           1
#define multiple_display1   1
#endif 

#if(menu_num >= 3)
#define name2    	        "Finish S"
#define variable2          Finish_Symbol 
#define multiple2           1
#define multiple_display2   1
#endif 

#if(menu_num >= 4)
#define name3    	        "Balance"
#define variable3          SetBalance  
#define multiple3           10
#define multiple_display3   10
#endif 

#if(menu_num >= 5)
#define name4    	        "angleP"
#define variable4          angleP 
#define multiple4           1
#define multiple_display4   1
#endif 

#if(menu_num >= 6)
#define name5    	        "angleD/"
#define variable5          angleD 
#define multiple5           0.1
#define multiple_display5   1
#endif 

#if(menu_num >= 7)
#define name6    	        "balanceP"
#define variable6          balanceP  
#define multiple6          1  
#define multiple_display6  1  
#endif 

#if(menu_num >= 8)
#define name7   	        "balanceD/"
#define variable7          balanceD  
#define multiple7          0.1  
#define multiple_display7  1  
#endif 

#if(menu_num >= 9)
#define name8    	        "SetSpeed"
#define variable8          SetSpeed
#define multiple8           5
#define multiple_display8   5
#endif 

#if(menu_num >= 10)
#define name9    	        "speedP/"
#define variable9          speedP
#define multiple9           0.1
#define multiple_display9   1
#endif 

#if(menu_num >= 11)
#define name10    	        "RinDeF"
#define variable10          Ring_Delay_50
#define multiple10           20
#define multiple_display10   20
#endif 

#if(menu_num >= 12)
#define name11    	        "RI"
#define variable11          Range_I
#define multiple11           50
#define multiple_display11   50
#endif 

#if(menu_num >= 13)
#define name12    	        "directP"
#define variable12           directP
#define multiple12           1
#define multiple_display12   1
#endif 

#if(menu_num >= 14)
#define name13    	        "directD//"
#define variable13           directD
#define multiple13           0.01
#define multiple_display13   1
#endif 

#if(menu_num >= 15)
#define name14    	        "directDD"
#define variable14           directDD 
#define multiple14           1
#define multiple_display14   1
#endif 

#if(menu_num >= 16)
#define name15    	        "directPI/"
#define variable15           directP_Inside
#define multiple15           0.1
#define multiple_display15   1
#endif 

#if(menu_num >= 17)
#define name16    	        "directDI/"
#define variable16           directD_Inside
#define multiple16           0.1
#define multiple_display16   1
#endif

#if(menu_num >= 18)
#define name17    	        "CircleNum"
#define variable17           Circle_Num
#define multiple17           1
#define multiple_display17   1
#endif 

#if(menu_num >= 19)
#define name18    	        "Ring Num"
#define variable18           Ring_Num
#define multiple18           1
#define multiple_display18   1
#endif 

#if(menu_num >= 20)
#define name19    	        "RD A"
#define variable19           Ring_Direction[0]
#define multiple19           1
#define multiple_display19   1
#endif 

#if(menu_num >= 21)
#define name20    	        "RD B"
#define variable20           Ring_Direction[1]
#define multiple20           1
#define multiple_display20   1
#endif 

#if(menu_num >= 22)
#define name21    	        "RD C"
#define variable21           Ring_Direction[2]
#define multiple21           1
#define multiple_display21   1
#endif 

#if(menu_num >= 23)
#define name22    	        "RD D"
#define variable22           Ring_Direction[3]
#define multiple22           1
#define multiple_display22   1
#endif 

#if(menu_num >= 24)
#define name23    	        "RS A"
#define variable23           Ring_Size[0]
#define multiple23           1
#define multiple_display23   1
#endif 

#if(menu_num >= 25)
#define name24    	        "RS B"
#define variable24           Ring_Size[1]
#define multiple24           1
#define multiple_display24   1
#endif 

#if(menu_num >= 26)
#define name25    	        "RS C"
#define variable25           Ring_Size[2]
#define multiple25           1
#define multiple_display25   1
#endif 

#if(menu_num >= 27)
#define name26    	        "RS D"
#define variable26           Ring_Size[3]
#define multiple26           1
#define multiple_display26   1
#endif 

#if(menu_num >= 28)
#define name27    	        "Ramp Num"
#define variable27           Ramp_Num
#define multiple27           1
#define multiple_display27   1
#endif 

#if(menu_num >= 29)
#define name28    	        "R Angle A"
#define variable28           Ramp_Angle[0]
#define multiple28           10
#define multiple_display28   10
#endif 

#if(menu_num >= 30)
#define name29    	        "R Angle B"
#define variable29           Ramp_Angle[1]
#define multiple29           10
#define multiple_display29   10
#endif 

#if(menu_num >= 31)
#define name30    	        "R Time A"
#define variable30           Ramp_Time[0]
#define multiple30           10
#define multiple_display30   10
#endif 

#if(menu_num >= 32)
#define name31    	        "R Time B"
#define variable31           Ramp_Time[1]
#define multiple31           10
#define multiple_display31   10
#endif 

#if(menu_num >= 33)
#define name32    	        "Sp Num"
#define variable32           Special_Num
#define multiple32           1
#define multiple_display32   1
#endif 

#if(menu_num >= 34)
#define name33    	        "Sp CntA"
#define variable33           Special_Start[0]
#define multiple33           1
#define multiple_display33   1
#endif 

#if(menu_num >= 35)
#define name34    	        "Sp DelayA"
#define variable34           Special_Delay[0]
#define multiple34           1
#define multiple_display34   1
#endif 

#if(menu_num >= 36)
#define name35    	        "Sp Intime"
#define variable35           Special_Menue_InTime
#define multiple35           1
#define multiple_display35   1
#endif 

#if(menu_num >= 37)
#define name36    	        "Sp CntB"
#define variable36           Special_Start[1]
#define multiple36           1
#define multiple_display36   1
#endif 

#if(menu_num >= 38)
#define name37    	        "Sp DelayB"
#define variable37           Special_Delay[1]
#define multiple37           1
#define multiple_display37   1
#endif 

#if(menu_num >= 39)
#define name38    	        "Sp Delay"
#define variable38           Special_Delay[0]
#define multiple38           1
#define multiple_display38   1
#endif 

#if(menu_num >= 40)
#define name39    	        "Sp Intime"
#define variable39           Special_Menue_InTime
#define multiple39           1
#define multiple_display39   1
#endif 



void menu_Init(void);
void menu(void);
void menu_display(void);
void menu_key(void);

#endif

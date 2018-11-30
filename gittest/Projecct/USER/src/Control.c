#include "Control.h"
#define ACTUAL_SPEED 210

/////////////////////////////////////////////////////////////////////
///////    轮子周长20cm 轮胎齿数68 编码器齿数30 电机齿数16     ////////
///////         真实速度=瞬时脉冲(双轮5ms叠加)/58          ////////
/////////////////////////////////////////////////////////////////////

extern uint8_t Track_Symbol; 
extern uint8_t Stop_Symbol;
extern uint8_t run_start_symbol;

/********************************************************
融合输出
********************************************************/
extern int16_t Gyro_X, Gyro_Y, Gyro_Z,Delay_Limit_Cnt;
extern int16_t ACC_X, ACC_Y, ACC_Z, MAG_X, MAG_Y, MAG_Z; 

int16_t Gyro_X_REVISE, Gyro_Y_REVISE, Gyro_Z_REVISE;
int16_t ACC_X_REVISE, ACC_Y_REVISE, ACC_Z_REVISE, MAG_X_REVISE, MAG_Y_REVISE, MAG_Z_REVISE; 
int16_t Gyro_X_Last_REVISE=0,Gyro_Y_Last_REVISE=0,ACC_Z_Last_REVISE=0;

int Angle=0;
int Angle_REVISE=0, Angle_REVISE_Last=0;
uint8_t timeCount=0;
int startCount=0;
uint8_t pit_symbol=0;

int pwmLeft=0, pwmRight=0;
int pwmLeft_Last=0, pwmRight_Last=0;
int pwmBalance=0, pwmBalance_Last=0, pwmDirect=0, pwmDirect_Last=0, pwmGo=0, pwmGoOld=0, pwmGoNew=0,pwmDirectOld=0, pwmDirectNew=0;
int pwmOutput=0;
int Range_Min=0, Range_Max=0;
int Encoder_Left=0, Encoder_Right=0, Encoder_Left_Last=0, Encoder_Right_Last=0;
int Encoder_Sum=0,Encoder_Sum_Last=0, Encoder_Sum_True=0, Encoder_Sum_True_Last=0;
int Motor_Left_Current=0, Motor_Right_Current=0;
/********************************************************
直立环
********************************************************/
extern int Ramp_Time_Wait;
double K1 =0.01;   //对加速度计取值的权重
double dt=0.045;    //采样时间  注意程序运行时间
double angle1;     //一阶互补滤波后的角度

int SetBalance = 0; //设定值 Desired Value    
double angleP_REVISE=0;
double angleP=0;
double angleD=0;
double balanceP = 0;  
double balanceD = 0;  
int balance_Integral=0;
int balance_Target_rate=0;

int Pitch_Angle_Error=0 ,Pitch_Target_rate=0, Pitch_Target_rate_Last=0, Pitch_Rate_Error=0, Pitch_Rate_Error_Last=0;
int Angle_Target=0, Angle_Error=0, Angle_Error_Last=0;

double Encoder_Integral=0;

int Ramp_Max=0;
int Ramp_Min=0;

extern int Ramp_Time[7];
extern int Ramp_Angle[7];
extern uint8_t Ramp_Cnt;                               //坡道计数
extern int Ramp_Time_Count;
/********************************************************
速度环
********************************************************/
int SetSpeed = 0; //设定值 Desired Value 
double speedP=0, speedI=0;
int Range_I=0;
double IncPIDCalc_Inside_Integral=0;
double fDelta, fDelta_old;
double fP, fI;

/********************************************************
方向环
********************************************************/
float EV_VALUE1_Revise=1, EV_VALUE2_Revise=1, EV_VALUE3_Revise=1, EV_VALUE4_Revise=1;
int EV_VALUE1=0, EV_VALUE2=0, EV_VALUE3=0, EV_VALUE4=0,EV_VALUE2_Last=0, EV_VALUE1_Last=0, EV_VALUE4_Last=0;
int EV_VALUE2_REVISE=0;
extern int EV_VALUE1_MAX, EV_VALUE2_MAX, EV_VALUE3_MAX, EV_VALUE4_MAX;
extern int EV_VALUE1_MIN, EV_VALUE2_MIN, EV_VALUE3_MIN, EV_VALUE4_MIN;


double directP=0, directD=0, directDD=0;
double directP_Inside=0, directD_Inside=0;   
double directP_Revise=0, directD_Revise=0, directDD_Revise=0; 
double directP_Revise_Last=0;
int16_t DEVIATE=0; //当前偏差 
int16_t DEVIATE_Last=0;

extern int Ring_Wait_In;
extern int Ring_Wait_Out;

extern uint8_t Ring_Size[20];
extern uint8_t Ring_Cnt,TurnTooBig_Flag;

int Direct_Error=0, Direct_Error_Last=0;

int Direct_P_Revise[220]=
{
26,
26,
26,
27,
27,
28,
28,
28,
29,
29,
30,
30,
30,
31,
31,
32,
32,
32,
33,
33,
34,
34,
34,
35,
35,
36,
36,
36,
37,
37,
38,
38,
38,
39,
39,
40,
40,
40,
41,
41,
42,
42,
42,
43,
43,
44,
44,
44,
45,
45,
46,
46,
46,
47,
47,
48,
48,
48,
49,
49,
50,
50,
50,
51,
51,
52,
52,
52,
53,
53,
54,
54,
54,
55,
55,
56,
56,
56,
57,
57,
58,
58,
58,
59,
59,
60,
60,
60,
61,
61,
62,
62,
62,
63,
63,
64,
64,
64,
65,
65,
66,
76,
76,
77,
77,
78,
78,
78,
79,
79,
80,
80,
80,
81,
81,
82,
82,
82,
83,
83,
84,
94,
94,
95,
95,
96,
96,
96,
97,
97,
98,
98,
98,
99,
99,
100,
100,
100,
101,
101,
102,
102,
102,
103,
103,
103,
103,
103,
104,
104,
104,
105,
105,
105,
105,
106,
106,
106,
107,
108,
109,
110,
110,
111,
111,
112,
112,
112,
113,
113,
114,
114,
114,
115,
115,
116,
117,
117,
120,
120,
120,
120,
120,
120,
120,
120,
121,
121,
121,
121,
121,
122,
122,
122,
122,
122,
122,
122,
123,
123,
123,
123,
124,
124,
124,
124,
125,
125,
125,
125,
125,
125,
125,
125,
126,
126,
126,
126,
126,
126,


};

/********************************************************
电流环
********************************************************/
double currentP=0, currentI=0;
int Current_Error_Left=0, Current_Error_Left_Last=0;
int Current_Error_Right=0, Current_Error_Right_Last=0;
int Current_Left_Base_Value=0, Current_Right_Base_Value=0;

/********************************************************
紧急制动
********************************************************/
double StopP=30;
int Stop_Pwm_Out=0;
/************************************************************/
extern uint8 Special_Start[10],Special_Angel[10];
extern uint16 Special_Delay[10];
extern uint8 Track_Symbol_Cnt,Special_State,Un_Track_Symbol,Special_Cnt;
extern uint16 Special_Delay_Cnt;
uint16 Special_Time_Count=0;
uint8 Ring_Oled_P=0;

/************************************************************************************************************************************************
************************************************************************************************************************************************/

void PIT_CH0_IRQHandler(void)
{		
	Cascade_Control_Inside();                 //中断总内环
	
	if(timeCount%2==0)                        //中断总外环
		Cascade_Control_Outside();

	if(run_start_symbol==1)
		Pwm_Control_Out();                        //占空比输出                 
	
	timeCount++;
	pit_symbol=1;
	PIT_FLAG_CLR(pit0);
}
 
void Cascade_Control_Inside()                                                                     //2.5ms  周期控制
{
	FXAS21002C_XYZ();
	Gyro_Y_Last_REVISE = Gyro_Y_REVISE;
	Gyro_X_Last_REVISE = Gyro_X_REVISE;
	#if(SmartCar_Number == 1)
	Gyro_X_REVISE =Kaman_Gyroscope(Gyro_X); 					//陀螺仪X轴卡尔曼
	Gyro_Y_REVISE = (-Gyro_Y);
	#endif 
	
	#if(SmartCar_Number == 2)
	Gyro_X_REVISE =Kaman_Gyroscope(Gyro_Y); 					//陀螺仪X轴卡尔曼
	Gyro_Y_REVISE = (Gyro_X);
	#endif 
	
	IncPIDCalc_Inside();                   					 //直立环内环
	DirectionControl_Inside();	           					 //方向环内环
}

void Cascade_Control_Outside()     																																 //5ms 周期控制
{
	FXOS8700CQR1_XYZ();
	ACC_Z_Last_REVISE = ACC_Z_REVISE;
		#if(SmartCar_Number == 1)
	ACC_Z_REVISE = ACC_Z;                           //加速度计Z轴无修正
	MAG_Z_REVISE = MAG_Z;	
	#endif 
	
	#if(SmartCar_Number == 2)
	ACC_Z_REVISE = -ACC_Z;                           //加速度计Z轴无修正
	MAG_Z_REVISE = MAG_Z;	
	#endif 
	
	Angle =  Yijielvbo(ACC_Z_REVISE, Gyro_Y_REVISE);
	Angle_REVISE_Last = Angle_REVISE;
									//角度往前变大
	#if(SmartCar_Number == 1)
	Angle_REVISE = -Angle;  	
	#endif 

	#if(SmartCar_Number == 2)
		Angle_REVISE = -Angle-240;  	
	#endif 
	
	Inductance_GetConversionValue();							 //电感采集
	Speed_Get();  

//  Motor_Current();		                         //电流环暂时没用
	
	IncPIDCalc_Outside();                         //直立外环       
	
	DirectionControl();  					                //方向外环

	if(timeCount>=20*2)                           //速度环（20倍外环周期）            
	{		
		velocity();
		timeCount=0;
		if(startCount<=400 && Encoder_Sum>10)  //  
			startCount++;
	}
	//pwmGo += (pwmGoNew-pwmGoOld)/12;
	
}

void Pwm_Control_Out(void)                                      																	//占空比输出     
{
	
	pwmLeft_Last = pwmLeft;
	pwmRight_Last = pwmRight;
	if(Stop_Symbol == 0)   //
	{	
		pwmOutput = pwmBalance;// -  pwmGo
	}	

  else if(Stop_Symbol == 1)
	{
		 Stop();
	}
	
	
	if(Stop_Symbol == 1)
	{
		pwmLeft =Stop_Pwm_Out; // 
	  pwmRight =Stop_Pwm_Out;// 
	}	
	else if(Protect==2)
	{
		pwmLeft =pwmBalance; // 
	  pwmRight =pwmBalance;// 
	}
	else if(Protect==3)
	{
		pwmLeft = - pwmDirect; //
		pwmRight = pwmDirect;/// 
	}
	else
	{
		pwmLeft = pwmOutput - pwmDirect ; //pwmOutput - pwmDirect
		pwmRight = pwmOutput + pwmDirect;//pwmOutput + pwmDirect
	}
	
	if(Track_Symbol==7 && Encoder_Left>100)
		pwmLeft*=0.25;
	if(Track_Symbol==7 && Encoder_Right>100)
		pwmRight*=0.25;
	
		if(Special_State==2 || Track_Symbol==7)
		{
			if(pwmLeft-pwmLeft_Last>5000)
				pwmLeft = pwmLeft_Last+5000;
			if(pwmLeft-pwmLeft_Last<-5000)
				pwmLeft = pwmLeft_Last-5000;
			
			if(pwmRight-pwmRight_Last>5000)
				pwmRight = pwmRight_Last+5000;
			if(pwmRight-pwmRight_Last<-5000)
				pwmRight = pwmRight_Last-5000;
		}

	if(pwmLeft>0)
	{
		if(pwmLeft>9999)
			pwmLeft=9999;
		ftm_pwm_duty(motor_port,leftmotor1,pwmLeft);
		ftm_pwm_duty(motor_port,leftmotor2,0);
	}
	if(pwmRight>0)
	{
		if(pwmRight>9999)
			pwmRight=9999;
		ftm_pwm_duty(motor_port,rightmotor1,pwmRight);
		ftm_pwm_duty(motor_port,rightmotor2,0);
	}
	if(pwmLeft<0)
	{
		if(pwmLeft<-9999)
			pwmLeft=-9999;
		ftm_pwm_duty(motor_port,leftmotor1,0);
		ftm_pwm_duty(motor_port,leftmotor2,-pwmLeft);
	}
	if(pwmRight<0)
	{
		if(pwmRight<-9999)
			pwmRight=-9999;
		ftm_pwm_duty(motor_port,rightmotor1,0);
		ftm_pwm_duty(motor_port,rightmotor2,-pwmRight);
	}
}
	

void Speed_Get(void)                                            																	//编码器测速
{
	Encoder_Left_Last = Encoder_Left;
	Encoder_Right_Last = Encoder_Right;	
	Encoder_Sum_Last = Encoder_Sum;
	Encoder_Sum_True_Last = Encoder_Sum_True;
	
	if(gpio_get(EncoderLEFT_DIRECT_PIN))
		Encoder_Left=ftm_count_get(ftm0);
	else
		Encoder_Left=-ftm_count_get(ftm0);
	if(!gpio_get(EncoderRIGHT_DIRECT_PIN))
		Encoder_Right=ftm_count_get(ftm1);
	else
		Encoder_Right=-ftm_count_get(ftm1);
	
	Encoder_Sum = Encoder_Left+Encoder_Right;
	Encoder_Sum_True = Encoder_Left+Encoder_Right;
	
	if(Encoder_Sum>Encoder_Sum_Last+1)
		Encoder_Sum = Encoder_Sum_Last+1;
	if(Encoder_Sum<Encoder_Sum_Last-1)
		Encoder_Sum = Encoder_Sum_Last-1;
	ftm_count_clean(ftm0);
	ftm_count_clean(ftm1);
}

void Motor_Current(void)                                        																	//电流采集
{
	Motor_Left_Current=Mean_Value_Filtering(leftmotor_current,ADC_8bit);//-Current_Left_Base_Value
	Motor_Right_Current=Mean_Value_Filtering(rightmotor_current,ADC_8bit);//-Current_Right_Base_Value
}

void Inductance_GetConversionValue(void)                        																	//电感采集    
{		
		EV_VALUE2_Last = EV_VALUE2;
	  EV_VALUE1_Last = EV_VALUE1;
	  EV_VALUE4_Last = EV_VALUE4;
		
		EV_VALUE1 = 1.00*Mean_Value_Filtering(Left_Left_Inductance,ADC_10bit)*EV_VALUE1_Revise;
		EV_VALUE2 = 1.00*Mean_Value_Filtering(Left_Right_Inductance,ADC_10bit)*EV_VALUE2_Revise;
		//EV_VALUE3 = 1.00*Mean_Value_Filtering(Right_Left_Inductance,ADC_10bit)*EV_VALUE3_Revise;
		EV_VALUE4 = 1.00*Mean_Value_Filtering(Right_Right_Inductance,ADC_10bit)*EV_VALUE4_Revise;	
}

double Yijielvbo(double angle_m, double gyro_m)                 																	//角度和角速度(一阶互补滤波)
{
  angle1 = K1 * angle_m+ (1-K1) * (angle1 + gyro_m * dt);
	return angle1;
}

void IncPIDCalc_Outside(void)                                   																	//直立环控制（外环）   Cascade Control
{
	Pitch_Target_rate_Last = Pitch_Target_rate;
	Angle_Error_Last = Angle_Error;
	angleP_REVISE = angleP;	
/************************直立环特殊元素角度修正*************************************/
	if(Track_Symbol==8)
	{
		if(Encoder_Sum>120)
			Angle_Target = SetBalance + pwmGo + (Ramp_Angle[Ramp_Cnt]-600) - 1.00*(Ramp_Angle[Ramp_Cnt]-600)*Ramp_Time_Count/Ramp_Time[Ramp_Cnt];
		else
			Angle_Target = SetBalance + pwmGo + (Ramp_Angle[Ramp_Cnt]-700) - 1.00*(Ramp_Angle[Ramp_Cnt]-600)*Ramp_Time_Count/Ramp_Time[Ramp_Cnt];
		Angle_Error = Angle_REVISE - Angle_Target;
		Pitch_Target_rate = Angle_Error * angleP_REVISE *1.2+  (Angle_Error-Angle_Error_Last) * angleD*1.0; //期望值-此刻姿态值    角速度控制器期望值
	}
	else if(Track_Symbol==7)
	{	
		Angle_Target = SetBalance + pwmGo;
		Angle_Error = Angle_REVISE - Angle_Target;
		Pitch_Target_rate = Angle_Error * angleP_REVISE *1.2+  (Angle_Error-Angle_Error_Last) * angleD*1.2; //期望值-此刻姿态值    角速度控制器期望值
	} 
	else if(Track_Symbol==0)
	{	
		if(Special_State==2)
		{
			Angle_Target =350;	
			Angle_Error = Angle_REVISE - Angle_Target;
			Pitch_Target_rate = Angle_Error * angleP_REVISE +  (Angle_Error-Angle_Error_Last) * angleD*1.0; //期望值-此刻姿态值    角速度控制器期望值
		}
		else
		{
			if(startCount<balanceP)
				Angle_Target =900;	
			else
				Angle_Target =SetBalance+pwmGo;	

			Angle_Error = Angle_REVISE - Angle_Target;
			Pitch_Target_rate = Angle_Error * angleP_REVISE *1.0+  (Angle_Error-Angle_Error_Last) * angleD*1.0; //期望值-此刻姿态值    角速度控制器期望值
		}
	} 
	else
	{	
		Angle_Target =SetBalance+pwmGo;		
		Angle_Error = Angle_REVISE - Angle_Target;
		Pitch_Target_rate = Angle_Error * angleP_REVISE *1.0+  (Angle_Error-Angle_Error_Last) * angleD*1.0; //期望值-此刻姿态值    角速度控制器期望值
	}
//	pwmBalance = Pitch_Target_rate;   //无内环时启用
}

void IncPIDCalc_Inside(void)                                    																	//直立环控制（内环）   Cascade Control
{
	pwmBalance_Last = pwmBalance;

//		if(Special_State==2 || Track_Symbol==7)
//		{
//			pwmBalance = Pitch_Target_rate + balanceD * (-Gyro_Y_REVISE);//+ balance_Integral 
//			if(pwmBalance-pwmBalance_Last>3000)
//				pwmBalance = pwmBalance_Last+3000;
//			if(pwmBalance-pwmBalance_Last<-3000)
//				pwmBalance = pwmBalance_Last-3000;
//		}
//		else
			pwmBalance = Pitch_Target_rate + balanceD * (-Gyro_Y_REVISE);//+ balance_Integral 
}

void velocity(void)                                             																	//速度环              Cascade Control
{	
	fDelta = SetSpeed - Encoder_Sum;
 
	pwmGoOld=pwmGo;
	if(Track_Symbol!=8)
		pwmGo=fDelta*speedP;
//	if(pwmGo-pwmGoOld>20)
//		pwmGo=pwmGoOld+20;
//	if(pwmGo-pwmGoOld<-20)
//		pwmGo=pwmGoOld-20;
//	
	if(pwmGo+SetBalance<550)
		pwmGo = 550 - SetBalance;
	else if(pwmGo+SetBalance>650)
		pwmGo = 650 - SetBalance;
}


void DirectionControl(void)                                     																	//方向环控制（外环）   Cascade Control
{
	DEVIATE_Last = DEVIATE;
	directP_Revise_Last=directP_Revise;
	pwmDirectOld = pwmDirectNew;
		
	Get_iErrordirect();
	
//		if(TurnTooBig_Flag==1&&Ring_Size[Ring_Cnt]==1)
//		{
//			if(Ring_Direction[Ring_Cnt]==1)
//			{
//				if(DEVIATE<140)
//					DEVIATE=140;
//				if(DEVIATE>400)
//					DEVIATE=400;
//			}
//				
//			if(Ring_Direction[Ring_Cnt]==2)
//			{
//				if(DEVIATE>-140)
//					DEVIATE=-140;
//				if(DEVIATE<-400)
//					DEVIATE=-400;
//			}
//			 
//		
//		}
//	  else if(TurnTooBig_Flag==1&&Ring_Size[Ring_Cnt]==2)
//		{
//			if(Ring_Direction[Ring_Cnt]==1)
//			{
//				if(DEVIATE<180)
//					DEVIATE=180;
//				if(DEVIATE>400)
//					DEVIATE=400;
//			}
//				
//			if(Ring_Direction[Ring_Cnt]==2)
//			{
//				if(DEVIATE>-180)
//					DEVIATE=-180;
//				if(DEVIATE<-400)
//					DEVIATE=-400;
//			}
//			 
//		
//		}
//	if( ((Track_Symbol==1 && Ring_Wait_In>10)|| (Track_Symbol==2 && Ring_Wait_Out<150) || (Track_Symbol==4 && Ring_Wait_In>10)|| (Track_Symbol==5 && Ring_Wait_Out<150))&&Ring_Size[Ring_Cnt]<=2 )
//	{
//		if(DEVIATE-DEVIATE_Last>15)
//			DEVIATE = DEVIATE_Last+15;
//		if(DEVIATE-DEVIATE_Last<-15)
//			DEVIATE = DEVIATE_Last-15;	
//	
//		
//	}
//	
	if(Track_Symbol == 0)
	{
		if(DEVIATE-DEVIATE_Last>30)
			DEVIATE = DEVIATE_Last+30;
		if(DEVIATE-DEVIATE_Last<-30)
			DEVIATE = DEVIATE_Last-30;	
		
		if(DEVIATE>300)
			DEVIATE=300;
		if(DEVIATE<-300)
			DEVIATE=-300;
	}
		
	if(Track_Symbol==1)
	{
		if(Ring_Size[Ring_Cnt]==1 && Ring_Wait_In==2)
		{
			if(Encoder_Sum<100){directP_Revise=75; Ring_Oled_P=75;}
			else if(Encoder_Sum>=100 && Encoder_Sum<105){directP_Revise=80;Ring_Oled_P=80; }//
			else if(Encoder_Sum>=105 && Encoder_Sum<110){directP_Revise=85;Ring_Oled_P=85; }
			else if(Encoder_Sum>=110 && Encoder_Sum<115){directP_Revise=90;Ring_Oled_P=90; }//
			else if(Encoder_Sum>=115 && Encoder_Sum<120){directP_Revise=95;Ring_Oled_P=95; }
			else if(Encoder_Sum>=120 && Encoder_Sum<125){directP_Revise=100;Ring_Oled_P=100; }//
			else if(Encoder_Sum>=125 && Encoder_Sum<130){directP_Revise=105;Ring_Oled_P=105; }//
			else if(Encoder_Sum>=130 && Encoder_Sum<135){directP_Revise=110;Ring_Oled_P=110; }//
			else if(Encoder_Sum>=135 && Encoder_Sum<140){directP_Revise=120;Ring_Oled_P=120; }//
			else if(Encoder_Sum>=140 && Encoder_Sum<145){directP_Revise=125;Ring_Oled_P=125; }//
			else if(Encoder_Sum>=145 && Encoder_Sum<150){directP_Revise=130;Ring_Oled_P=130; }	
			else if(Encoder_Sum>=150 && Encoder_Sum<155){directP_Revise=135;Ring_Oled_P=135; }
			else if(Encoder_Sum>=155 && Encoder_Sum<160){directP_Revise=140;Ring_Oled_P=140; }
			else if(Encoder_Sum>=160 && Encoder_Sum<165){directP_Revise=145;Ring_Oled_P=145; }
			else if(Encoder_Sum>=165 && Encoder_Sum<170){directP_Revise=148;Ring_Oled_P=148; }
		  else if(Encoder_Sum>=170 && Encoder_Sum<175){directP_Revise=155;Ring_Oled_P=155; }
			else if(Encoder_Sum>=175 && Encoder_Sum<180){directP_Revise=160;Ring_Oled_P=160; }
			else if(Encoder_Sum>=180 && Encoder_Sum<185){directP_Revise=165;Ring_Oled_P=165; }

			else {directP_Revise=170; Ring_Oled_P=170;}

			
		}
		else if(Ring_Size[Ring_Cnt]==2 && Ring_Wait_In==2)
		{
			if(Encoder_Sum<100){directP_Revise=75; Ring_Oled_P=75;}
			else if(Encoder_Sum>=100 && Encoder_Sum<105){directP_Revise=80;Ring_Oled_P=80; }//
			else if(Encoder_Sum>=105 && Encoder_Sum<110){directP_Revise=85;Ring_Oled_P=85; }
			else if(Encoder_Sum>=110 && Encoder_Sum<115){directP_Revise=90;Ring_Oled_P=90; }//
			else if(Encoder_Sum>=115 && Encoder_Sum<120){directP_Revise=95;Ring_Oled_P=95; }
			else if(Encoder_Sum>=120 && Encoder_Sum<125){directP_Revise=100;Ring_Oled_P=100; }//
			else if(Encoder_Sum>=125 && Encoder_Sum<130){directP_Revise=105;Ring_Oled_P=105; }//
			else if(Encoder_Sum>=130 && Encoder_Sum<135){directP_Revise=110;Ring_Oled_P=110; }//
			else if(Encoder_Sum>=135 && Encoder_Sum<140){directP_Revise=120;Ring_Oled_P=120; }//
			else if(Encoder_Sum>=140 && Encoder_Sum<145){directP_Revise=125;Ring_Oled_P=125; }//
			else if(Encoder_Sum>=145 && Encoder_Sum<150){directP_Revise=130;Ring_Oled_P=130; }	
			else if(Encoder_Sum>=150 && Encoder_Sum<155){directP_Revise=135;Ring_Oled_P=135; }
			else if(Encoder_Sum>=155 && Encoder_Sum<160){directP_Revise=140;Ring_Oled_P=140; }
			else if(Encoder_Sum>=160 && Encoder_Sum<165){directP_Revise=145;Ring_Oled_P=145; }
			else if(Encoder_Sum>=165 && Encoder_Sum<170){directP_Revise=150;Ring_Oled_P=150; }
		  else if(Encoder_Sum>=170 && Encoder_Sum<175){directP_Revise=155;Ring_Oled_P=155; }
			else if(Encoder_Sum>=175 && Encoder_Sum<180){directP_Revise=160;Ring_Oled_P=160; }
			else if(Encoder_Sum>=180 && Encoder_Sum<185){directP_Revise=165;Ring_Oled_P=165; }

			else {directP_Revise=170; Ring_Oled_P=170;}
			
		}
		else if(Ring_Size[Ring_Cnt]>2 && Ring_Wait_In==2)
			directP_Revise=140;
		
	

	}
	else if(Track_Symbol==4)
	{
		
			if(Ring_Size[Ring_Cnt]==1 && Ring_Wait_In==2)
		{
			if(Encoder_Sum<100){directP_Revise=75; Ring_Oled_P=75;}
			else if(Encoder_Sum>=100 && Encoder_Sum<105){directP_Revise=80;Ring_Oled_P=80; }//
			else if(Encoder_Sum>=105 && Encoder_Sum<110){directP_Revise=85;Ring_Oled_P=85; }
			else if(Encoder_Sum>=110 && Encoder_Sum<115){directP_Revise=90;Ring_Oled_P=90; }//
			else if(Encoder_Sum>=115 && Encoder_Sum<120){directP_Revise=95;Ring_Oled_P=95; }
			else if(Encoder_Sum>=120 && Encoder_Sum<125){directP_Revise=100;Ring_Oled_P=100; }//
			else if(Encoder_Sum>=125 && Encoder_Sum<130){directP_Revise=105;Ring_Oled_P=105; }//
			else if(Encoder_Sum>=130 && Encoder_Sum<135){directP_Revise=110;Ring_Oled_P=110; }//
			else if(Encoder_Sum>=135 && Encoder_Sum<140){directP_Revise=120;Ring_Oled_P=120; }//
			else if(Encoder_Sum>=140 && Encoder_Sum<145){directP_Revise=125;Ring_Oled_P=125; }//
			else if(Encoder_Sum>=145 && Encoder_Sum<150){directP_Revise=130;Ring_Oled_P=130; }	
			else if(Encoder_Sum>=150 && Encoder_Sum<155){directP_Revise=135;Ring_Oled_P=135; }
			else if(Encoder_Sum>=155 && Encoder_Sum<160){directP_Revise=140;Ring_Oled_P=140; }
			else if(Encoder_Sum>=160 && Encoder_Sum<165){directP_Revise=145;Ring_Oled_P=145; }
			else if(Encoder_Sum>=165 && Encoder_Sum<170){directP_Revise=148;Ring_Oled_P=148; }
		  else if(Encoder_Sum>=170 && Encoder_Sum<175){directP_Revise=155;Ring_Oled_P=155; }
			else if(Encoder_Sum>=175 && Encoder_Sum<180){directP_Revise=160;Ring_Oled_P=160; }
			else if(Encoder_Sum>=180 && Encoder_Sum<185){directP_Revise=165;Ring_Oled_P=165; }

			else {directP_Revise=170; Ring_Oled_P=170;}
			
		}

		else if(Ring_Size[Ring_Cnt]==2 && Ring_Wait_In==2)
		{
			if(Encoder_Sum<100){directP_Revise=75; Ring_Oled_P=75;}
			else if(Encoder_Sum>=100 && Encoder_Sum<105){directP_Revise=80;Ring_Oled_P=80; }//
			else if(Encoder_Sum>=105 && Encoder_Sum<110){directP_Revise=85;Ring_Oled_P=85; }
			else if(Encoder_Sum>=110 && Encoder_Sum<115){directP_Revise=90;Ring_Oled_P=90; }//
			else if(Encoder_Sum>=115 && Encoder_Sum<120){directP_Revise=95;Ring_Oled_P=95; }
			else if(Encoder_Sum>=120 && Encoder_Sum<125){directP_Revise=100;Ring_Oled_P=100; }//
			else if(Encoder_Sum>=125 && Encoder_Sum<130){directP_Revise=105;Ring_Oled_P=105; }//
			else if(Encoder_Sum>=130 && Encoder_Sum<135){directP_Revise=110;Ring_Oled_P=110; }//
			else if(Encoder_Sum>=135 && Encoder_Sum<140){directP_Revise=120;Ring_Oled_P=120; }//
			else if(Encoder_Sum>=140 && Encoder_Sum<145){directP_Revise=125;Ring_Oled_P=125; }//
			else if(Encoder_Sum>=145 && Encoder_Sum<150){directP_Revise=130;Ring_Oled_P=130; }	
			else if(Encoder_Sum>=150 && Encoder_Sum<155){directP_Revise=135;Ring_Oled_P=135; }
			else if(Encoder_Sum>=155 && Encoder_Sum<160){directP_Revise=140;Ring_Oled_P=140; }
			else if(Encoder_Sum>=160 && Encoder_Sum<165){directP_Revise=145;Ring_Oled_P=145; }
			else if(Encoder_Sum>=165 && Encoder_Sum<170){directP_Revise=150;Ring_Oled_P=150; }
		  else if(Encoder_Sum>=170 && Encoder_Sum<175){directP_Revise=155;Ring_Oled_P=155; }
			else if(Encoder_Sum>=175 && Encoder_Sum<180){directP_Revise=160;Ring_Oled_P=160; }
			else if(Encoder_Sum>=180 && Encoder_Sum<185){directP_Revise=165;Ring_Oled_P=165; }

			else {directP_Revise=170; Ring_Oled_P=170;}
				
		}
		else if(Ring_Size[Ring_Cnt]>2 && Ring_Wait_In==2 && Encoder_Sum<150)
			directP_Revise=140;
		else if(Ring_Size[Ring_Cnt]>2 && Ring_Wait_In==2 && Encoder_Sum>=150)
			directP_Revise=150;
		

	}
	 
	else
	{
		if(Encoder_Sum<0)
			directP_Revise = directP_Revise_Last;
		else if(Encoder_Sum>=220)
		{
			directP_Revise = Direct_P_Revise[219] + directP - 10;
		} 	
		else
			directP_Revise = Direct_P_Revise[Encoder_Sum] + directP - 10;
		

	}

	


		directD_Revise = 0.000001*(Gyro_X_REVISE*Gyro_X_REVISE)/1.5+directD;//directD+Encoder_Sum*0.0016
		if(directD_Revise>1.5)
			directD_Revise = 1.5;
		if(Track_Symbol==1 ||Track_Symbol==2||Track_Symbol==5|| Track_Symbol ==4 ||Track_Symbol==3|| Track_Symbol ==6 )
		{
				directD_Revise = 1.5;
		}
	 
	
	directDD_Revise = directDD;
		
	pwmDirectNew = (DEVIATE*0.1)*abs((int)(DEVIATE*0.1))*0.8+ directP_Revise *0.1 * DEVIATE + directD_Revise * Gyro_X_REVISE+ directDD_Revise *0.1 * (DEVIATE - DEVIATE_Last);
}
 
void DirectionControl_Inside(void)// Cascade Control            																	//方向环控制（内环）   Cascade Control
{
	pwmDirect_Last = pwmDirect;
	Direct_Error_Last = Direct_Error;
	Direct_Error = pwmDirectNew + Gyro_X_REVISE;  
	pwmDirect =directP_Inside * Direct_Error + directD_Inside * (Direct_Error - Direct_Error_Last);
	
//	
//	if(Track_Symbol==2 || Track_Symbol==5)
//	{
//		if(pwmDirect>5000)
//			pwmDirect = 5000;
//		if(pwmDirect<-5000)
//		pwmDirect = -5000;	
//	}
	
	
	if(pwmDirect-pwmDirect_Last>1500)
		pwmDirect = pwmDirect_Last + 1500;
	if(pwmDirect-pwmDirect_Last<-1500)
		pwmDirect = pwmDirect_Last - 1500;
	
	
	if(pwmDirect>8000)
		pwmDirect = 8000;
	if(pwmDirect<-8000)
		pwmDirect = -8000;	
}

void CurrentControl(int Motor_Left_Current_Set, int Motor_Right_Current_Set)											//电流环								Cascade Control
{
	Current_Error_Left_Last = Current_Error_Left;
	Current_Error_Right_Last = Current_Error_Right;
	Current_Error_Left = Motor_Left_Current_Set - Motor_Left_Current;
	Current_Error_Right = Motor_Right_Current - Motor_Right_Current_Set;
	pwmLeft += (Current_Error_Left - Current_Error_Left_Last) * currentP + Current_Error_Left * currentI;
	pwmRight += (Current_Error_Right - Current_Error_Right_Last) * currentP + Current_Error_Right * currentI; 
}

void Stop(void)
{
	Stop_Pwm_Out =  - Encoder_Sum * StopP;
}


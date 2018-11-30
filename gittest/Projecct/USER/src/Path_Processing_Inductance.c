 #include "Path_Processing_Inductance.h"

extern int Angle_REVISE, Angle_REVISE_Last;
extern int16_t DEVIATE,DEVIATE_Last; //当前偏差
extern int Encoder_Left, Encoder_Right, Encoder_Sum, Encoder_Sum_Last, Encoder_Sum_True, Encoder_Sum_True_Last, Encoder_Left_Last, Encoder_Right_Last;
extern int16_t Gyro_X_REVISE, Gyro_Y_REVISE, Gyro_Z_REVISE,ACC_Z_Last_REVISE;
extern int16_t ACC_X_REVISE, ACC_Y_REVISE, ACC_Z_REVISE, MAG_X_REVISE, MAG_Y_REVISE, MAG_Z_REVISE; 
int Angle_Revise_EV=0;

extern int EV_VALUE1, EV_VALUE2, EV_VALUE3, EV_VALUE4, EV_VALUE2_Last, EV_VALUE1_Last, EV_VALUE4_Last;
extern int EV_VALUE2_REVISE;

extern int Curve_Save_Small[52],Curve_Save_Big[52];

uint8_t Track_Symbol=0; 
uint8_t Circle_Num=0;
uint8_t Circle_Cnt=0;

uint8_t run_start_symbol=0;

int xjb=0;



/********************************************************
赛道元素
*******************************************************/
/*： 
0                                                    常规赛道
1,2,3                                                左环岛
4,5,6                                                右环岛
7                                                    颠簸路面
8                                                    坡道
*/
/********************************************************
环岛
********************************************************/
int Ring_Speed=0;
int Ring_Speed1=0;
uint16  Ring_In_Wait_Cnt=0;
uint8_t Ring_In_Wait_Angle=0;
uint16 Ring_In_Wait=0;
uint8_t Ring_In_Symbol=0;
uint8_t Ring_Out_Symbol=0;
uint8_t Ring_Direction[20]={0};
uint8_t Ring_Size[20]={0};
uint8_t Ring_Cnt=0;
uint8_t Ring_Num=0;
int Ring_Wait_Out=0;
int Ring_Wait_In=0;

uint8_t TurnTooBig_Flag=0;
uint16_t TurnTooBig_Cnt=0;

int Ring_Delay_50=0;


/********************************************************
颠簸路面
********************************************************/
int Bump_Check=0;                             // 检测防止误判
int Bump_Time_Count=0;                            //进颠簸路段 
uint8_t Bump_Num=1;  
uint8_t Bump_Cnt=0; 
uint8_t Bump_Temp_Symbol=0;
int16_t DEVIATE_Temp=0;
int16_t Delay_Limit_Cnt=0,Bump_Time_Wait=0;

/********************************************************
坡道
********************************************************/
uint8_t Ramp_Cnt=0;                               //坡道计数
uint8_t Ramp_Num=0;                               //坡道数量（设定）
int Ramp_Time_Wait=900;                           //延时检测防止误判
uint8_t Ramp_Check=0;                             //多次检测防止误判
int Ramp_Time_Count=0;														//上坡道												
int Ramp_Time[7]= {0};														//坡道大小
int Ramp_Angle[7]={0};
int Ramp_Wait_Cnt=0;                     
uint8_t Ramp_Out_Symbol=0;
int EV_VALUE1_Symbol=0;
int EV_VALUE4_Symbol=0;

/********************************************************
********************************************************/



/********************部分减速***********************************/

uint8 Special_Num=0;                                            //特殊赛道个数
uint8 Special_Start[10]={0},Special_Angel[10]={0};              //菜单参数 哪个？多大？何时？
uint16 Special_Delay[10]={0};


uint8 Track_Symbol_Cnt=0,Special_State=0,Un_Track_Symbol=0;     //特殊元素计数   在特殊处理中的状态 解除特殊状态标志
uint8 Special_Cnt=0;                                            //记录一圈中用到的特殊处理次数
uint16 Special_Delay_Cnt=0;																			//特殊元素后的何时？
uint16 Special_Delay5Ms_Cnt=0;																			//特殊元素后的何时？
uint16 Special_In_Time=0,Special_Menue_InTime=0;

void Get_iErrordirect()
{
	if(run_start_symbol==1)
		Track_Check();
	Deviate_Revise();
}

void Track_Check()                                         //检测赛道信息
{
	Special_Judge();
	Ring_Judge();
	Bump_Judge();
	Ramp_Judge();
	Circle_Judge();
	

	FM_Control();

}

/*
Special_State =1    开始计时
Special_State =2		开始处理 跳转到void IncPIDCalc_Outside(void)      
Special_State =3    清除处理 Special_Cnt++  在 IncPIDCalc_Outside 中


（注意 Special_Cnt=0时特指是颠簸路）
*/
void Special_Judge(void)
{
	if(Special_Start[Special_Cnt]==Track_Symbol_Cnt&&Special_State==0&&Special_Num>Special_Cnt)
	{
		Special_State=1;
	}
	if(Special_State==1)
	{
		Special_Delay5Ms_Cnt++;
		if(Special_Delay5Ms_Cnt>=20)
		{
			Special_Delay5Ms_Cnt=0;
			Special_Delay_Cnt++;	
		}
	}
	if(Special_Delay_Cnt>=Special_Delay[Special_Cnt]&&Special_State==1)
	{
		Special_State=2;
		Special_Delay_Cnt=0;
		Special_Delay5Ms_Cnt=0;
		Special_In_Time=Special_Menue_InTime;	
	}
	if(Special_In_Time>1)
	{
		Special_In_Time	--;
	}
	
	else if(Special_In_Time==1)
	{
		Special_In_Time=0;
		Special_State=0;
		Special_Cnt++;
	}
}
/*
1.两边电感均大于500
2.靠环电感小于外侧电感20连续2-6场
3.两侧电感十分接近
4.靠环侧电感大于外侧电感20  --------------------------------------->开始延时      
5.根据速度确定延时场数--------------------------------------------->开始强制打脚
6.打脚场数超过60或者外侧电感小于400-------------------------------->解除强制打脚
7.在环内场数超过200且内侧电感大于外侧电感350且内侧电感大于700------>出环状态1
8.两侧电感和大于1300且差值小于50----------------------------------->出环状态2
9.两侧电感之和小于900且差值小于400--------------------------------->清除环岛






*/


 


void Ring_Judge(void)
{
	if(Track_Symbol==0 && Ring_In_Symbol==0 && Ring_Cnt<Ring_Num && EV_VALUE1>500 && EV_VALUE4>500&& Angle_REVISE<700 && fabss(Angle_REVISE,Angle_REVISE_Last)<40)//&& EV_VALUE2>600)   //两边电感值大于600  !!ruguotaixiao chuhuanyouwenti	
	{
			Ring_In_Symbol=1;
	}
                                                                                                                           //大于5又小于10说明左右电感产生了交点
	if(Track_Symbol==0 && Ring_In_Symbol>=1 )   
	{
		if(Ring_Direction[Ring_Cnt]==1&& EV_VALUE4-EV_VALUE1>20 && Ring_In_Symbol<10)
		{
			Ring_In_Symbol++;
		}
		else if(Ring_Direction[Ring_Cnt]==2&& EV_VALUE1-EV_VALUE4>20 && Ring_In_Symbol<10)
		{
			Ring_In_Symbol++;
		}
	}																																																												//两电感差值较大且持续一段时间（时间根据环岛大小决定）
		
	if(Track_Symbol==0 && Ring_In_Symbol>Ring_Size[Ring_Cnt]+1)
	{
		if(Ring_Direction[Ring_Cnt]==1 && EV_VALUE4-EV_VALUE1<6-Ring_Size[Ring_Cnt]/2)
			Ring_In_Symbol=20;
		if(Ring_Direction[Ring_Cnt]==2 && EV_VALUE1-EV_VALUE4<6-Ring_Size[Ring_Cnt]/2)
			Ring_In_Symbol=20;
	}
	
	if(Track_Symbol==0 && Ring_In_Symbol==20)//延时
	{							
		if(((Ring_Direction[Ring_Cnt]==1 && EV_VALUE1-EV_VALUE4>10) || (Ring_Direction[Ring_Cnt]==2 && EV_VALUE4-EV_VALUE1>10)) && Ring_Speed==0 && Ring_In_Wait==0)
		{
			Ring_In_Wait=1;
		}
		if(Ring_In_Wait==1 && Track_Symbol==0)
		{
			Ring_Speed+=Encoder_Sum;//Encoder_Left+Encoder_Right;
		}
		
		if(Ring_Size[Ring_Cnt]==1)
		{
			if(Encoder_Sum<=150 && Ring_Speed>3200-500+Ring_Delay_50)
			{
				if(Ring_Direction[Ring_Cnt]==1)																				//左右电感值十分相近
				{
					Ring_In_Symbol=0;
					Track_Symbol=1;			
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
				if(Ring_Direction[Ring_Cnt]==2)
				{
					Ring_In_Symbol=0;
					Track_Symbol=4;		
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
			}
			else if(Encoder_Sum>150 && Encoder_Sum<=170 && Ring_Speed>3200-500+Ring_Delay_50)
			{
				if(Ring_Direction[Ring_Cnt]==1)																				//左右电感值十分相近
				{
					Ring_In_Symbol=0;
					Track_Symbol=1;			
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
				if(Ring_Direction[Ring_Cnt]==2)
				{
					Ring_In_Symbol=0;
					Track_Symbol=4;		
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
			}
			else if(Encoder_Sum>170 && Ring_Speed>3200-500+Ring_Delay_50)
			{
				if(Ring_Direction[Ring_Cnt]==1)																				//左右电感值十分相近
				{
					Ring_In_Symbol=0;
					Track_Symbol=1;			
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
				if(Ring_Direction[Ring_Cnt]==2)
				{
					Ring_In_Symbol=0;
					Track_Symbol=4;		
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
			}
		}
		
		if(Ring_Size[Ring_Cnt]==2)
		{
			if(Encoder_Sum<=160 && Ring_Speed>3300-500+Ring_Delay_50)
			{
				if(Ring_Direction[Ring_Cnt]==1)																				//左右电感值十分相近
				{
					Ring_In_Symbol=0;
					Track_Symbol=1;			
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
				if(Ring_Direction[Ring_Cnt]==2)
				{
					Ring_In_Symbol=0;
					Track_Symbol=4;		
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
			}
			else if(Encoder_Sum>160 && Encoder_Sum<=170 && Ring_Speed>3300-500+Ring_Delay_50)
			{
				if(Ring_Direction[Ring_Cnt]==1)																				//左右电感值十分相近
				{
					Ring_In_Symbol=0;
					Track_Symbol=1;			
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
				if(Ring_Direction[Ring_Cnt]==2)
				{
					Ring_In_Symbol=0;
					Track_Symbol=4;		
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
			}
			else if(Encoder_Sum>170 && Ring_Speed>3300-500+Ring_Delay_50)
			{
				if(Ring_Direction[Ring_Cnt]==1)																				//左右电感值十分相近
				{
					Ring_In_Symbol=0;
					Track_Symbol=1;			
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
				if(Ring_Direction[Ring_Cnt]==2)
				{
					Ring_In_Symbol=0;
					Track_Symbol=4;		
					Ring_Wait_In=0;
					Ring_In_Wait=0;
					Ring_Speed=0;
				}
			}
		}
		
		if(Ring_Size[Ring_Cnt]==3 && Ring_Speed>3700-500+Ring_Delay_50)
		{
			if(Ring_Direction[Ring_Cnt]==1)																				//左右电感值十分相近
			{
				Ring_In_Symbol=0;
				Track_Symbol=1;			
				Ring_Wait_In=0;
				Ring_In_Wait=0;
				Ring_Speed=0;
			}
			if(Ring_Direction[Ring_Cnt]==2)
			{
				Ring_In_Symbol=0;
				Track_Symbol=4;		
				Ring_Wait_In=0;
				Ring_In_Wait=0;
				Ring_Speed=0;
			}
		}
		
		if(Ring_Size[Ring_Cnt]==4 && Ring_Speed>4400-500+Ring_Delay_50)
		{
			if(Ring_Direction[Ring_Cnt]==1)																				//左右电感值十分相近
			{
				Ring_In_Symbol=0;
				Track_Symbol=1;			
				Ring_Wait_In=0;
				Ring_In_Wait=0;
				Ring_Speed=0;
			}
			if(Ring_Direction[Ring_Cnt]==2)
			{
				Ring_In_Symbol=0;
				Track_Symbol=4;		
				Ring_Wait_In=0;
				Ring_In_Wait=0;
				Ring_Speed=0;
			}
		}
		
		if(Ring_Size[Ring_Cnt]==6 && Ring_Speed>5400-500+Ring_Delay_50)
		{
			if(Ring_Direction[Ring_Cnt]==1)																				//左右电感值十分相近
			{
				Ring_In_Symbol=0;
				Track_Symbol=1;			
				Ring_Wait_In=0;
				Ring_In_Wait=0;
				Ring_Speed=0;
			}
			if(Ring_Direction[Ring_Cnt]==2)
			{
				Ring_In_Symbol=0;
				Track_Symbol=4;		
				Ring_Wait_In=0;
				Ring_In_Wait=0;
				Ring_Speed=0;
			}
		}
	}		


	if(Track_Symbol==1||Track_Symbol==4)//强打部分
	{
		Ring_Wait_In++;
//		if(Track_Symbol==1&&EV_VALUE1-EV_VALUE4>7&&TurnTooBig_Cnt==0)
//		{
//		   TurnTooBig_Cnt=1;
//		}
//		if(Track_Symbol==1&&TurnTooBig_Cnt==1&&EV_VALUE4-EV_VALUE1>7)
//		{
//			 TurnTooBig_Cnt=2;
//		}
//		if(Track_Symbol==1&&TurnTooBig_Cnt==2&&(EV_VALUE1-EV_VALUE4>7||EV_VALUE1-EV_VALUE4>200))
//		{
//			 TurnTooBig_Cnt=3;
//		}
//		if(Track_Symbol==1&&TurnTooBig_Cnt==3&&EV_VALUE4-EV_VALUE1>7)
//		{
//			 TurnTooBig_Cnt=4;
//			 TurnTooBig_Flag =1;
//		}
//		
//		if(Track_Symbol==4&&EV_VALUE4-EV_VALUE1>7&&TurnTooBig_Cnt==0)
//		{
//		   TurnTooBig_Cnt=1;
//		}
//		if(Track_Symbol==4&&TurnTooBig_Cnt==1&&EV_VALUE1-EV_VALUE4>7)
//		{
//			 TurnTooBig_Cnt=2;
//		}
//		if(Track_Symbol==4&&TurnTooBig_Cnt==2&&(EV_VALUE4-EV_VALUE1>7||EV_VALUE4-EV_VALUE1>200))
//		{
//			 TurnTooBig_Cnt=3;
//		}
//		if(Track_Symbol==4&&TurnTooBig_Cnt==3&&EV_VALUE1-EV_VALUE4>7)
//		{
//			 TurnTooBig_Cnt=4;
//			 TurnTooBig_Flag =1;
//		}
//		
//		
//		if(Ring_Wait_In>30&&(EV_VALUE4-EV_VALUE1>50)&&Track_Symbol==1 )
//		{
//			TurnTooBig_Flag =1;
//		}
//		if(Ring_Wait_In>30&&(EV_VALUE1-EV_VALUE4>50)&&Track_Symbol==4)
//		{
//			TurnTooBig_Flag =1;	
//		}	
		
	}
	
	if(Track_Symbol==1 && (EV_VALUE4<400 || Ring_Wait_In>60||TurnTooBig_Flag==1)&&Ring_Wait_In>10)																							//外侧电感小于400解掉
	{
		Track_Symbol=2;
		Ring_Wait_Out=0;
		TurnTooBig_Cnt=0;
	}
	if(Track_Symbol==4 && (EV_VALUE1<400 || Ring_Wait_In>60||TurnTooBig_Flag==1)&&Ring_Wait_In>10)
	{
		Track_Symbol=5;
		Ring_Wait_Out=0;
		TurnTooBig_Cnt=0;
	}
	


	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(Track_Symbol==2 && Ring_Out_Symbol==0)
	{
		Ring_Wait_Out++;
		if(Ring_Wait_Out>200 && EV_VALUE1-EV_VALUE4>350 && EV_VALUE1>700)															//差值十分大
		{
			Ring_Out_Symbol=1;
			TurnTooBig_Flag=0;
			
			Track_Symbol=3;
		}
	}
		
	if(Track_Symbol==5 && Ring_Out_Symbol==0 )
	{
		Ring_Wait_Out++;
		if(Ring_Wait_Out>200 && EV_VALUE4-EV_VALUE1>350 && EV_VALUE4>700)
		{
			Ring_Out_Symbol=1;
			TurnTooBig_Flag=0;
			Track_Symbol=6;
		}
	}
	
	if(Track_Symbol==3 && Ring_Out_Symbol==1 && EV_VALUE1+EV_VALUE4>1000 && fabss(EV_VALUE1,EV_VALUE4)<50)    //两侧电感
	{	
		Ring_Out_Symbol=2;
	}
	if(Track_Symbol==6 && Ring_Out_Symbol==1 && EV_VALUE1+EV_VALUE4>1000 && fabss(EV_VALUE1,EV_VALUE4)<50)
	{
		Ring_Out_Symbol=2;
	}
		
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	if(Track_Symbol==3 || Track_Symbol==6)	
	{
		if(EV_VALUE1+EV_VALUE4<900 && fabss(EV_VALUE1,EV_VALUE4)<400)// && EV_VALUE2<200
		{
			Ring_Out_Symbol=0;
			Track_Symbol=0;
			Ring_Cnt++;
			Track_Symbol_Cnt++;
		}
	}	
}

void Bump_Judge(void)
{
	if(Bump_Time_Wait>200 && Track_Symbol==0)//&&Special_State==2
	{
		if(fabss(Gyro_Y_REVISE,0)>200&&Bump_Temp_Symbol==0)//&& fabss(Angle_REVISE,Angle_REVISE_Last)>40
			Bump_Temp_Symbol = 1;
		
		if(Bump_Temp_Symbol==1)
		{			
			if(Encoder_Left+Encoder_Right>250 && fabss(Encoder_Left,Encoder_Right)<100) //
				Bump_Check++;
			else
			{	
				Bump_Temp_Symbol = 0;
				Bump_Check=0;
			}
			
			if(Track_Symbol==0 && Bump_Check>=3)
			{
				Track_Symbol = 7;
				Bump_Check = 0;
				Bump_Temp_Symbol = 0;
			}			
	  }
	}		
	
	if(Track_Symbol==7)
	{
		Bump_Time_Count++;	
		if(fabss((Encoder_Left-Encoder_Left_Last),0)<10 && fabss((Encoder_Right-Encoder_Right_Last),0)<10) //
			Bump_Check++;
		else
		{	 
			Bump_Check=0;
		}
		if(Bump_Time_Count>60 || (Bump_Time_Count>40 && Bump_Check>=15))
		{
			Track_Symbol=0;
			Bump_Time_Count=0;
			Bump_Time_Wait=0;
			Bump_Check = 0;
		}
	}
	 
}

void Ramp_Judge(void)
{
	if(Bump_Time_Wait>100 && Ramp_Time_Wait>1300 && Ramp_Cnt < Ramp_Num)                                                                                               //坡道
	{		
	  if(Track_Symbol==0)                                                                                                   
		{
			if(EV_VALUE1 + EV_VALUE4<900 && fabss(EV_VALUE1,EV_VALUE4)<60 && EV_VALUE2 > 600 && EV_VALUE2-EV_VALUE2_Last>0 && Angle_REVISE<700 && fabss(Gyro_X_REVISE,0)<200) //
			{	
				Ramp_Check++;
				if(Ramp_Check==1)
				{
					EV_VALUE1_Symbol = EV_VALUE1;
					EV_VALUE4_Symbol = EV_VALUE4;
				}
			}
			else
				Ramp_Check=0;
		}
		if(Track_Symbol==0 && Ramp_Check>=8 && (EV_VALUE1-EV_VALUE1_Symbol<10 && EV_VALUE4-EV_VALUE4_Symbol<10))
		{
			Track_Symbol = 8;
			Ramp_Check = 0;
		}
		else if(Track_Symbol==0 && Ramp_Check>=8)
		{
			Ramp_Check = 0;
		}
		
		if(Track_Symbol==8)                                                              
		{
			Ramp_Time_Count++;
			if(Ramp_Time_Count>=Ramp_Time[Ramp_Cnt])
			{
				Track_Symbol = 0;
				Ramp_Time_Wait=0;
				Ramp_Time_Count=0;
				Ramp_Cnt++;
//				Track_Symbol_Cnt++;
			}
		}
	}
}

void Circle_Judge()
{
	if(Ring_Cnt == Ring_Num  && Circle_Cnt<Circle_Num-1&&Special_Cnt==Special_Num)
	{
		Circle_Cnt++;
		Ring_Cnt=0;
		Ramp_Cnt=0;
		Special_Cnt=0;
		Track_Symbol_Cnt=0;
		Bump_Cnt=0;
	}
}




void Deviate_Revise()                                      //元素偏差修正
{
   if(Track_Symbol>0 && Track_Symbol<7)
		 Island_Revise();
	 else if(Track_Symbol == 7)
		Bump_Revise();
	else if(Track_Symbol == 8)
		Ramp_Revise();
	else                                                      //常规赛道
	{
		Regular_Track();		
	}
}

 
void Island_Revise()
{		
	if(Track_Symbol == 1)                                    //入左环岛特殊处理
	{
		if(Ring_Size[Ring_Cnt]==1)    //60*90
		{				
			DEVIATE = 300;
//			if(DEVIATE<150)
//				DEVIATE = 150;	
		}
		else if(Ring_Size[Ring_Cnt] == 2)   //60*90
		{
			DEVIATE = 210;  
//			if(DEVIATE<150)
//				DEVIATE = 150;
		}
		else if(Ring_Size[Ring_Cnt] == 3)   //100*90
		{
			DEVIATE = 0.35*EV_VALUE1;  
			if(DEVIATE<150)
				DEVIATE = 150;
		}
		else if(Ring_Size[Ring_Cnt] == 4)   //100*90
		{
			DEVIATE = 0.280*EV_VALUE1;  
			if(DEVIATE<150)
				DEVIATE = 150;
		}
		else if(Ring_Size[Ring_Cnt] == 5)   //100*90
		{
			DEVIATE = 0.20*EV_VALUE1;  
			if(DEVIATE<150)
				DEVIATE = 150;
		}
		else if(Ring_Size[Ring_Cnt] == 6)   //100*90
		{
			DEVIATE = 0.1*EV_VALUE1;  
			if(DEVIATE<150)
				DEVIATE = 150;
		}
		if(Encoder_Sum <100)
		{
			DEVIATE/=2;
		}
	}
	else if(Track_Symbol == 4)                              //入右环岛特殊处理
	{
		if(Ring_Size[Ring_Cnt]==1) 
		{
			DEVIATE = -300;
//			if(DEVIATE>-150)
//				DEVIATE = -150;	
			
		}
		else if(Ring_Size[Ring_Cnt]==2)
		{
			DEVIATE = -210;
//			if(DEVIATE>-150)
//				DEVIATE = -150;	
		}
			else if(Ring_Size[Ring_Cnt]==3)
		{
			DEVIATE = -0.35*EV_VALUE4;
			if(DEVIATE>-150)
				DEVIATE = -150;	
		}
			else if(Ring_Size[Ring_Cnt]==4)
		{
			DEVIATE = -0.280*EV_VALUE4;
			if(DEVIATE>-150)
				DEVIATE = -150;	
		}
			else if(Ring_Size[Ring_Cnt]==5)
		{
			DEVIATE = -0.20*EV_VALUE4;
			if(DEVIATE>-150)
				DEVIATE = -150;	
		}
			else if(Ring_Size[Ring_Cnt]==6)
		{
			DEVIATE = -0.1*EV_VALUE4;
			if(DEVIATE>-150)
				DEVIATE = -150;	
		}
		if(Encoder_Sum <100)
			{
				DEVIATE/=2;
			}
		
	}
	
	
	else if(Track_Symbol == 2)        //环内正常闭环
	{
//		if(Ring_Wait_Out<20)
//		{
//			DEVIATE=1.00*DEVIATE_Last*(20-Ring_Wait_Out)/20+ 1.000 * (sqrt(EV_VALUE1) - sqrt(EV_VALUE4)) / (EV_VALUE1 + EV_VALUE4) * 3000*Ring_Wait_Out/20;
//		}
//		else
		{
			DEVIATE = 1.000 * (sqrt(EV_VALUE1) - sqrt(EV_VALUE4)) / (EV_VALUE1 + EV_VALUE4) * 30000;
			if(DEVIATE<60&&Ring_Wait_Out>250)
				DEVIATE=60;
		}
	}
	else if(Track_Symbol == 5)
	{
//		if(Ring_Wait_Out<20)
//		{
//			DEVIATE=1.00*DEVIATE_Last*(20-Ring_Wait_Out)/20+ 1.000 * (sqrt(EV_VALUE1) - sqrt(EV_VALUE4)) / (EV_VALUE1 + EV_VALUE4) * 3000*Ring_Wait_Out/20;
//		
//		}
//		else
		{
			DEVIATE = 1.000 * (sqrt(EV_VALUE1) - sqrt(EV_VALUE4)) / (EV_VALUE1 + EV_VALUE4) * 30000;
			if(DEVIATE>-60&&Ring_Wait_Out>250)
				DEVIATE=-60;
		}
	}
	else if(Track_Symbol == 3)        //出环减少偏差
	{
		if(Ring_Out_Symbol==1)
		{
			DEVIATE = 1.000 * (sqrt(EV_VALUE1) - sqrt(EV_VALUE4)) / (EV_VALUE1 + EV_VALUE4) * 30000+100;
		}
		else if(Ring_Out_Symbol==2)
			DEVIATE = 1.000 * (sqrt(EV_VALUE1) - sqrt(EV_VALUE4)) / (EV_VALUE1 + EV_VALUE4) * 30000-100;
	}
	else if(Track_Symbol == 6)
	{
		if(Ring_Out_Symbol==1)
		{
			DEVIATE = 1.000 * (sqrt(EV_VALUE1) - sqrt(EV_VALUE4)) / (EV_VALUE1 + EV_VALUE4) * 30000-100;
		}
		else if(Ring_Out_Symbol==2)
			DEVIATE = 1.000 * (sqrt(EV_VALUE1) - sqrt(EV_VALUE4)) / (EV_VALUE1 + EV_VALUE4) * 30000+100;
	}
}
void Bump_Revise()
{
	DEVIATE = 1.000 * (sqrt(EV_VALUE1) - sqrt(EV_VALUE4)) / (EV_VALUE1 + EV_VALUE4) * 10000;
}

void Ramp_Revise()
{
	DEVIATE = 1.000 * (sqrt(EV_VALUE1) - sqrt(EV_VALUE4)) / (EV_VALUE1 + EV_VALUE4) * 5000;
}

void Regular_Track()
{
	DEVIATE = 1.000 * (sqrt(EV_VALUE1) - sqrt(EV_VALUE4)) / (EV_VALUE1 + EV_VALUE4) * 30000;
 
	if(Ramp_Time_Wait<1500)
		Ramp_Time_Wait++;
	if(Bump_Time_Wait<1500)
		Bump_Time_Wait++;	
}

void FM_Control()
{
	if(Track_Symbol == 8)//|| Track_Symbol == 2 || Track_Symbol == 5
		FM_Turn(10);
	else if(Track_Symbol==1 || Track_Symbol==3 || Track_Symbol==4 || Track_Symbol==6 || Track_Symbol==7||TurnTooBig_Flag==1 )
		FM(1);
//	else if(Special_State==2)
//		FM(1);
	else
		FM(0);
	
//		if(SetSpeed - Encoder_Sum<0)
//	{
//		FM(1);
//	}
//	else
//	{
//		FM(0);
//	}
		
}







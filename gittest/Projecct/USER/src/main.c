/*********************************************************************************************************************
¡
* 750½Ç¶ÈÊ± 450 500 450
* protect		1Õý³£±£»¤ 2Ö±Á¢»· 3·½Ïò»· 
* mode=4    1ÅÜÂ· 2µç¸Ð½Ç¶È¹Û²â 3´ÅÁ¦¼ÆpwmÏÔÊ¾ 4Â¼Í¼
 

 ********************************************************************************************************************/

#include "headfile.h"


#define Speed_Protect 300
#define Mag_Protect   -900
#define Gyro_Protect  4000

uint16_t flash_data_save_one[40]=
{
	4/1,  1/1,   0/1,   600/10,
	70/1, 20/1,  15/1, 50/1,
	180/5,	30/1,   500/20,  0/1,
	10/1, 60/1, 120/1, 30/1,
	15/1, 8/1,   3/1,   1/1,
	1/1,  2/1,   1/1,   1/1,
	2/1,  3/1,   3/1,   1/1,
	650/10, 500/10, 200/10, 200/10,
	2/1,  1/1,   5/1,   275/1,
	4/1,  12/1
};//ÕýÈ¦²ÎÊý 2018.5.9  19.17   car2
uint16_t flash_data_save_two[40]=
{
	4/1,  1/1,   0/1,   550/10,
	70/1, 20/1,  0/1, 50/1,
	170/5,	25/1,   0/1,  0/1,
	10/1, 60/1, 120/1, 30/1,
	15/1, 3/1,   3/1,   1/1,
	2/1,  2/1,   1/1,   3/1,
	2/1,  1/1,   3/1,   1/1,
	750/10, 500/10, 200/10, 200/10,
	1/1,  3/1,   8/1,   275/1,
	4/1,  12/1
};//ÕýÈ¦²ÎÊý 2018.5.9  19.17   car2

extern int16_t Gyro_X_REVISE, Gyro_Y_REVISE, Gyro_Z_REVISE;
extern int16_t ACC_X_REVISE, ACC_Y_REVISE, ACC_Z_REVISE, MAG_X_REVISE, MAG_Y_REVISE, MAG_Z_REVISE; 
extern int16_t Gyro_Y_Last_REVISE,ACC_Z_Last_REVISE;
extern int EV_VALUE1, EV_VALUE2, EV_VALUE3, EV_VALUE4;
extern int EV_VALUE2_REVISE;
extern int16_t DEVIATE; //µ±Ç°Æ«²î 
extern int Encoder_Left, Encoder_Right;
extern int Encoder_Sum;
extern int pwmBalance, pwmDirect, pwmGo;
extern int Angle_REVISE;
extern int startCount;
extern int Pitch_Target_rate;
extern int Angle_Target;
extern  uint16 Special_Delay[10];
 
extern uint8_t Track_Symbol;
 
extern int pwmLeft, pwmRight;
extern int Motor_Left_Current, Motor_Right_Current;

extern uint8_t pit_symbol,Ring_Oled_P;
uint8_t Uart_Receive=0;
int Blooth_Finish_Symbol=0;
int Finish_Symbol=0;
uint8_t Stop_Symbol=0;

uint8_t mode=0;
uint8_t Protect=0;

int Protect_Gyro_Wait=0;
int Protect_Encoder_Wait=0;
int Protect_NoRead_Wait=0;
int Protect_Reverse_Wait=0;

extern uint8_t run_start_symbol;
extern float EV_VALUE1_Revise, EV_VALUE2_Revise, EV_VALUE3_Revise, EV_VALUE4_Revise;

extern uint8 Special_Start[10],Special_Angel[10];
extern uint16 Special_Delay[10];
extern uint8 Track_Symbol_Cnt,Special_State,Un_Track_Symbol;
extern uint16 Special_Delay_Cnt;
extern uint16 Special_Time_Count;


void mode_start(void);
void Protect_Stop(void);




int main(void)
{
	all_Init();
  menu(); 
	mode_start();	
}

void mode_start()
{
	if(mode==1)
	{
		enable_irq(PIT_CH0_IRQn);		
		OLED_Clear();
		OLED_Write_String(8, 6,(uint8_t*) "start");
		while(1)
		{		
				Protect_Stop();
		}
	}
	
	else if(mode==2)
	{
		 enable_irq(PIT_CH0_IRQn);		 
		 OLED_Clear();
		 while(1)
		 {
			OLED_Write_Num5(0,0,EV_VALUE1);
			OLED_Write_Num5(0,2,EV_VALUE2);
			OLED_Write_Num5(0,4,EV_VALUE3);
			OLED_Write_Num5(0,6,EV_VALUE4);

		
 
//			OLED_Write_Num5_Revise(7,2,Track_Symbol);
			OLED_Write_Num5_Revise(7,0,DEVIATE);	
//			 			OLED_Write_Num5_Revise(7,0,ACC_Z_REVISE);
//				OLED_Write_Num5_Revise(7,2,Gyro_X_REVISE);
		  OLED_Write_Num5_Revise(7,2,Angle_REVISE);
		  OLED_Write_Num5_Revise(7,4,Encoder_Left );
			OLED_Write_Num5_Revise(7,6,Encoder_Right);
			Protect_Stop();
	   }
	}

	else if(mode==3)
	{
	   systick_delay_ms(50);
     while(KEY2==0){;}
		 enable_irq(PIT_CH0_IRQn);
		 OLED_Clear();
		 while(1)
		 {
				OLED_Write_Num5(0,0,EV_VALUE1);
				OLED_Write_Num5(0,2,EV_VALUE2);
				OLED_Write_Num5(0,4,EV_VALUE3);
				OLED_Write_Num5(0,6,EV_VALUE4);
				OLED_Write_Num5_Revise(7,0,DEVIATE);	
				OLED_Write_Num5_Revise(7,2,Angle_REVISE);
				if(KEY2==0)                     //È·¶¨
				{
					systick_delay_ms(10);
					if(KEY2==0) 
					{
					 while(KEY2==0){;}
					 OLED_Clear();
					 OLED_Write_String(8, 6,(uint8_t*) "Live");
						 
						 						
					 while(EV_VALUE1+EV_VALUE2+EV_VALUE4>100);
					 systick_delay_ms(50);
					 while(EV_VALUE1+EV_VALUE2+EV_VALUE4<100);
						 
					 run_start_symbol=1;
					 break;
					}
				}
				if(KEY1==0)                     //È·¶¨
				{
					systick_delay_ms(10);
					if(KEY1==0) 
					{
					 while(KEY1==0){;}
					 EV_VALUE1_Revise=1.00*300/EV_VALUE1;
					 EV_VALUE2_Revise=1.00*400/EV_VALUE2;
//						 EV_VALUE3_Revise=1.00*300/EV_VALUE3;
					 EV_VALUE4_Revise=1.00*300/EV_VALUE4;
					}
				}
		 } 
		 
		 
		 while(1)
		 {		
			 Protect_Stop();
			 Live_Transmission_1();
		 }
	}
	else if(mode==4)
	{
	   systick_delay_ms(50);
     while(KEY2==0){;}
		 enable_irq(PIT_CH0_IRQn);
		 OLED_Clear();
		 while(1)
		 {
			 	Protect_Stop();
				OLED_Write_Num5(0,0,EV_VALUE1);
				OLED_Write_Num5(0,2,EV_VALUE2);
				OLED_Write_Num5(0,4,EV_VALUE3);
				OLED_Write_Num5(0,6,EV_VALUE4);
				OLED_Write_Num5_Revise(7,0,DEVIATE);	
				OLED_Write_Num5_Revise(7,2,Angle_REVISE);
				if(KEY2==0)                     //È·¶¨
				{
					systick_delay_ms(10);
					if(KEY2==0) 
					{
					 while(KEY2==0){;}
					 OLED_Clear();
					 OLED_Write_String(8, 6,(uint8_t*) "Live");
						 
					 run_start_symbol=1;
					 break;
					}
				}
				if(KEY1==0)                     //È·¶¨
				{
					systick_delay_ms(10);
					if(KEY1==0) 
					{
					 while(KEY1==0){;}
					 EV_VALUE1_Revise=1.00*300/EV_VALUE1;
					 EV_VALUE2_Revise=1.00*400/EV_VALUE2;
//						 EV_VALUE3_Revise=1.00*300/EV_VALUE3;
					 EV_VALUE4_Revise=1.00*300/EV_VALUE4;
					}
				}
		 } 
		 
		 
		 while(1)
		 {		
			 Protect_Stop();
			 Live_Transmission_1();
		 }
	}
	else if(mode==5)
	{
		 enable_irq(PIT_CH0_IRQn);
		 OLED_Clear();
		 OLED_Write_String(8, 6,(uint8_t*) "App Live");
		 while(1)
		 {		
			 Protect_Stop();
			 Live_Transmission_APP();
		 }
	}
	else if(mode==6)
	{
		FLASH_EraseSector(sector_num);
		FLASH_WriteSector(sector_num,(const uint8 *)flash_data_save_one,2*menu_num,0);             //Ð´ÈëËÄ¸ö×Ö½Úµ½×îºóÒ»¸öÉÈÇø Æ«ÒÆ0×Ö½Ú
		OLED_Clear();
		OLED_Write_String(4, 2,(uint8_t*) "Data");
		OLED_Write_String(6, 4,(uint8_t*) "Recovery");
		OLED_Write_String(8, 6,(uint8_t*) "ONE");
	}
		else if(mode==7)
	{
		FLASH_EraseSector(sector_num);
		FLASH_WriteSector(sector_num,(const uint8 *)flash_data_save_two,2*menu_num,0);             //Ð´ÈëËÄ¸ö×Ö½Úµ½×îºóÒ»¸öÉÈÇø Æ«ÒÆ0×Ö½Ú
		OLED_Clear();
		OLED_Write_String(4, 2,(uint8_t*) "Data");
		OLED_Write_String(6, 4,(uint8_t*) "Recovery");
		OLED_Write_String(8, 6,(uint8_t*) "TWO");
	}
}

void Protect_Stop()
{
	if(Finish_Symbol==1 && startCount>=150 )//
	{
	  if(MAG_Z_REVISE<Mag_Protect-900 && Stop_Symbol==0)
		{
			Stop_Symbol = 1;
			OLED_Write_String(0,0,(uint8_t *)"finishA");			
		}			
		if(MAG_Z_REVISE>1300 && Stop_Symbol==0)
		{
			Stop_Symbol = 1;
			OLED_Write_String(0,0,(uint8_t *)"finishB");
		}			
	}		

	
	if(Protect ==1)
	{
		if(pit_symbol==1)
		{
			pit_symbol=0;
			
			if((Encoder_Left > Speed_Protect || Encoder_Right> Speed_Protect)||(Encoder_Left < -Speed_Protect || Encoder_Right < -Speed_Protect))
			{
				Protect_Encoder_Wait++;
				if(Protect_Encoder_Wait>80)
				{
					OLED_Clear(); 				 
					DisableInterrupts;
					ftm_pwm_duty(motor_port,leftmotor1,0);
					ftm_pwm_duty(motor_port,leftmotor2,0);
					ftm_pwm_duty(motor_port,rightmotor1,0);
					ftm_pwm_duty(motor_port,rightmotor2,0);
					FM(0);
					OLED_Write_String(0,0,(uint8_t *)"Encoder");
					OLED_Write_String(0,2,(uint8_t *)"     Protect");

					while(1);
				}
			}
			else
				Protect_Encoder_Wait=0;
		}

		
		if(Gyro_X_REVISE>Gyro_Protect || Gyro_X_REVISE<-Gyro_Protect)
		{
			Protect_Gyro_Wait++;
			if(Protect_Gyro_Wait>40)
			{
				OLED_Clear(); 				 
				DisableInterrupts;
				ftm_pwm_duty(motor_port,leftmotor1,0);
				ftm_pwm_duty(motor_port,leftmotor2,0);
				ftm_pwm_duty(motor_port,rightmotor1,0);
				ftm_pwm_duty(motor_port,rightmotor2,0);
				FM(0);
				OLED_Write_String(0,0,(uint8_t *)"Gyro");
				OLED_Write_String(0,2,(uint8_t *)"     Protect");
							 
				while(1);
			}
		}
		else
			Protect_Gyro_Wait=0;
		
//		if(Gyro_Y_Last_REVISE==Gyro_Y_REVISE && ACC_Z_Last_REVISE==ACC_Z_REVISE)
//		{
//			Protect_NoRead_Wait++;
//			if(Protect_NoRead_Wait>10)
//			{
//				OLED_Clear(); 				 
//				DisableInterrupts;
//				ftm_pwm_duty(motor_port,leftmotor1,0);
//				ftm_pwm_duty(motor_port,leftmotor2,0);
//				ftm_pwm_duty(motor_port,rightmotor1,0);
//				ftm_pwm_duty(motor_port,rightmotor2,0);
//				FM(0);
//				OLED_Write_String(0,0,(uint8_t *)"No Read");
//							 
//				while(1);
//			}
//		}
//		else
//			Protect_NoRead_Wait=0;
		
		
		if( EV_VALUE2<100 &&fabss( EV_VALUE1,EV_VALUE4)<100 )//&& startCount>=80
		{
			OLED_Clear(); 				 
			DisableInterrupts;
			ftm_pwm_duty(motor_port,leftmotor1,0);
			ftm_pwm_duty(motor_port,leftmotor2,0);
			ftm_pwm_duty(motor_port,rightmotor1,0);
			ftm_pwm_duty(motor_port,rightmotor2,0);
			FM(0);
			OLED_Write_String(0,0,(uint8_t *)"Inductance");
			OLED_Write_String(0,2,(uint8_t *)"     Protect");
			OLED_Write_Num4(12,4,Ring_Oled_P );
			
						 
			while(1);
		}
		
//		if(Encoder_Left < -100 || Encoder_Right< -100 || Encoder_Sum<-180)
//		{
//			Protect_Reverse_Wait++;
//			if(Protect_Reverse_Wait>6)
//			{
//				OLED_Clear(); 				 
//				DisableInterrupts;
//				ftm_pwm_duty(motor_port,leftmotor1,0);
//				ftm_pwm_duty(motor_port,leftmotor2,0);
//				ftm_pwm_duty(motor_port,rightmotor1,0);
//				ftm_pwm_duty(motor_port,rightmotor2,0);
//				FM(0);
//				OLED_Write_String(0,0,(uint8_t *)"Reverse");
//				OLED_Write_String(0,2,(uint8_t *)"     Protect");
//							 
//				while(1);
//			}

//		}
//		
	 //}

		
//		if(Blooth_Finish_Symbol==1)
//		{
//			OLED_Clear(); 				 
//			DisableInterrupts;
//			ftm_pwm_duty(motor_port,leftmotor1,0);
//			ftm_pwm_duty(motor_port,leftmotor2,0);
//			ftm_pwm_duty(motor_port,rightmotor1,0);
//			ftm_pwm_duty(motor_port,rightmotor2,0);
//			OLED_Write_String(0,0,(uint8_t *)"Blooth Stop");
//			if(mode==0 || mode==1)
//				OLED_Write_Num5(0,2,field_cnt);
//			while(1);
//		}
//		if(Track_Symbol==4)
//		{
//			OLED_Clear(); 				 
//			DisableInterrupts;
//			ftm_pwm_duty(motor_port,leftmotor1,0);
//			ftm_pwm_duty(motor_port,leftmotor2,0);
//			ftm_pwm_duty(motor_port,rightmotor1,0);
//			ftm_pwm_duty(motor_port,rightmotor2,0);
//			OLED_Write_String(0,0,(uint8_t *)"test Stop");
//				if(mode==0)
//					OLED_Write_Num5(0,2,field_cnt);
//			while(1);
//		}
		
}
	}

//void UART5_RX_TX_IRQHandler(void)
//{
//	//Èç¹û³É¹¦½ÓÊÕµ½ÁËÊý¾Ý
//	if(UART_ReceiveData(UART5,&Uart_Receive))
//	{
//		if(Uart_Receive!=0)
//			Blooth_Finish_Symbol=1;
//	}
//}

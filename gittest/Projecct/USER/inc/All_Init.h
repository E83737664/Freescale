#ifndef _ALL_INIT_H_
#define _ALL_INIT_H_

#include "headfile.h"

#define SmartCar_Number 1
#if(SmartCar_Number == 1)
#define motor_port    ftm2
#define leftmotor1    ftm_ch5     			//G4
#define leftmotor2	  ftm_ch4     			//G6
#define leftmotor_current    ADC0_SE7   //B3   
#define rightmotor1     ftm_ch2   			//G7
#define rightmotor2	  ftm_ch3    				//G5
#define rightmotor_current   ADC0_SE6   //B2
#endif 

#if(SmartCar_Number == 2)
#define motor_port    ftm2
#define leftmotor1    ftm_ch3     			//G4
#define leftmotor2	  ftm_ch2     			//G6
#define leftmotor_current    ADC0_SE7   //B3   
#define rightmotor1   ftm_ch4     			//G7
#define rightmotor2	  ftm_ch5    				//G5
#define rightmotor_current   ADC0_SE6   //B2
#endif 

#define EncoderLEFT_Port					ftm0
#define EncoderLEFT_PIN   				E0
#define EncoderLEFT_DIRECT_PIN  	E1
#define EncoderRIGHT_Port					ftm1
#define EncoderRIGHT_PIN  				E7
#define EncoderRIGHT_DIRECT_PIN   C5

//B23
//A67


#if(SmartCar_Number == 1)
#define Left_Left_Inductance ADC0_SE11     //C0
#define Left_Right_Inductance ADC0_SE9    //C1
#define Right_Left_Inductance ADC0_SE10   //C2
#define Right_Right_Inductance ADC0_SE8	//C3
#endif 

#if(SmartCar_Number == 2)
#define Left_Left_Inductance ADC0_SE11    //C0
#define Left_Right_Inductance ADC0_SE10    //C1 10
#define Right_Left_Inductance ADC0_SE15   //C2
#define Right_Right_Inductance ADC0_SE9	//C3
#endif 


#define Voltage_Detection ADC0_SE12

#define Uart_Port uart1


void all_Init(void);
void EncoderInit(void);
void Uart_Init(void);
void motorInit(void);
void Inductance_Init(void);
void Pit_Init(int Channel, int T, int level);
void Voltage_Check(void);


#endif

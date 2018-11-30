/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		�ж��ļ�
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/



#include "isr.h"


void PIT_CH1_IRQHandler(void)
{
    PIT_FLAG_CLR(pit1);

    
}

void IRQ_IRQHandler(void)
{
    CLEAR_IRQ_FLAG;
    
}


void KBI0_IRQHandler(void)
{
    CLEAN_KBI0_FLAG;
    
}

#define  CHIP_DEBUG         ON		//??????????????a???????????
#if(CHIP_DEBUG==ON)
__asm void wait()
{
  BX lr	//?????????
}
#endif

void HardFault_IRQnHandler(void)//?????????
{
	OLED_Clear();
	ftm_pwm_duty(motor_port,leftmotor1,0);
	ftm_pwm_duty(motor_port,leftmotor2,0);
	ftm_pwm_duty(motor_port,rightmotor1,0);
	ftm_pwm_duty(motor_port,rightmotor2,0);
	OLED_Write_String(0,0,(uint8_t *)"The memory");
	
	OLED_Write_String(0,2,(uint8_t *)"or Stacks");	
	
	OLED_Write_String(0,4,(uint8_t *)"overflows");
	
	#if(CHIP_DEBUG==ON)
	wait();
	#endif
	while(1);
}

void NonMaskableInt_IRQnHandler(void)//??????
{
	OLED_Clear();
	ftm_pwm_duty(motor_port,leftmotor1,0);
	ftm_pwm_duty(motor_port,leftmotor2,0);
	ftm_pwm_duty(motor_port,rightmotor1,0);
	ftm_pwm_duty(motor_port,rightmotor2,0);

	OLED_Write_String(0,0,(uint8_t *)"The Chip");
	
	OLED_Write_String(0,2,(uint8_t *)"have big");	
	
	OLED_Write_String(0,4,(uint8_t *)"error");
	#if(CHIP_DEBUG==ON)	
	wait();
	#endif
	while(1);
}

/*
�жϺ������ƣ��������ö�Ӧ���ܵ��жϺ���
Sample usage:��ǰ���������ڶ�ʱ�� ͨ��0���ж�
void PIT_CH0_IRQHandler(void)
{
    ;
}
�ǵý����жϺ������־λ

FTMRE_IRQHandler      
PMC_IRQHandler        
IRQ_IRQHandler        
I2C0_IRQHandler       
I2C1_IRQHandler       
SPI0_IRQHandler       
SPI1_IRQHandler       
UART0_IRQHandler 
UART1_IRQHandler 
UART2_IRQHandler 
ADC0_IRQHandler       
ACMP0_IRQHandler      
FTM0_IRQHandler       
FTM1_IRQHandler       
FTM2_IRQHandler       
RTC_IRQHandler        
ACMP1_IRQHandler      
PIT_CH0_IRQHandler    
PIT_CH1_IRQHandler    
KBI0_IRQHandler       
KBI1_IRQHandler       
Reserved26_IRQHandler 
ICS_IRQHandler        
WDG_IRQHandler        
PWT_IRQHandler        
MSCAN_Rx_IRQHandler   
MSCAN_Tx_IRQHandler   
*/




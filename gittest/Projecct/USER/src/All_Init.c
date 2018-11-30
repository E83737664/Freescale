#include "All_Init.h"

extern int Current_Left_Base_Value, Current_Right_Base_Value;

int Voltage_Value=0;

void all_Init()
{
  get_clk();              //��ȡʱ��Ƶ�� ����ִ��
	
	OLED_Init();
	OLED_Clear();
	
	motorInit();

	OLED_Write_Num1(0,0,0);
	i2c_init(i2c1,400*1000);
	OLED_Write_Num1(0,0,1);
	FXOS8700CQR1_Init();	
	OLED_Write_Num1(0,0,2);
	FXAS21002C_Init();
	OLED_Clear();

	FLASH_Init();
	Uart_Init();
	KEY_Init();
	EncoderInit();
	Inductance_Init();
	Pit_Init(0,2500,0);		

  Voltage_Check();
}

void EncoderInit()
{
	//ftm�ļ������ſɲ鿴KEA128_port_cfg.h�ļ��ڵ�FTM0_COUNT_PIN��FTM1_COUNT_PIN�ĺ궨���֪
	//һ��ftmͬһʱ��ֻ��ʵ��һ�ֹ��ܣ�������ڲ��پͲ����������PWM
	ftm_count_init(EncoderLEFT_Port);   //��E0���������������м���    E0�ӱ�����LSB    
	gpio_init(EncoderLEFT_DIRECT_PIN,GPI,0);    //�����жϷ���                  C5�ӱ�����DIR
	port_pull(EncoderLEFT_DIRECT_PIN);          //IO����
	port_pull(EncoderLEFT_PIN);          //IO����
	
	ftm_count_init(EncoderRIGHT_Port);   //��E7���������������м���    E7�ӱ�����LSB
	gpio_init(EncoderRIGHT_DIRECT_PIN,GPI,0);    //�����жϷ���                  H5�ӱ�����DIR
	port_pull(EncoderRIGHT_DIRECT_PIN);          //IO����
	port_pull(EncoderRIGHT_PIN);          //IO����
}

void motorInit()
{
	ftm_pwm_init(motor_port,leftmotor1,15000,0);//��ʼ��PWMƵ��Ϊ15K��ռ�ձ�Ϊ0
	ftm_pwm_init(motor_port,leftmotor2,15000,0);//��ʼ��PWMƵ��Ϊ15K��ռ�ձ�Ϊ0
	ftm_pwm_init(motor_port,rightmotor1,15000,0);//��ʼ��PWMƵ��Ϊ15K��ռ�ձ�Ϊ0
	ftm_pwm_init(motor_port,rightmotor2,15000,0);//��ʼ��PWMƵ��Ϊ15K��ռ�ձ�Ϊ0

//	adc_init(leftmotor_current);
//	adc_init(rightmotor_current);
//	Current_Left_Base_Value = Mean_Value_Filtering(leftmotor_current,ADC_8bit);
//	Current_Right_Base_Value = Mean_Value_Filtering(rightmotor_current,ADC_87bit);
}

void Inductance_Init()
{
	adc_init(Left_Left_Inductance);     //��ʼ��ADC ADC����ͨ��ADCͨ���Ų鿴KEA128_adc.h�ļ���֪
	adc_init(Left_Right_Inductance);
	adc_init(Right_Left_Inductance);
	adc_init(Right_Right_Inductance);
}

void Uart_Init()
{
		//��ʼ��Ĭ�ϵĵ��Դ���
	uart_init(Uart_Port,115200);
//	 //�������ڽ��չ���
//	UART_ITConfig(UART5,UART_IT_RDRF,ENABLE);
//	//��ͨNVIC�϶�Ӧ�����ж���
//	NVIC_EnableIRQ(UART5_RX_TX_IRQn);
}

void Pit_Init(int Channel, int T, int level)
{
	if(Channel==0)
	{
		pit_init_us(pit0,T);	            //��ʼ��pit0 ��������ΪT		
		set_irq_priority(PIT_CH0_IRQn,level);	//����pit0���ȼ�
		disable_irq(PIT_CH0_IRQn);			//����pit0�ж�
	}
	else if(Channel==1)
	{
		pit_init_us(pit1,T);	            //��ʼ��pit0 ��������ΪT		
		set_irq_priority(PIT_CH1_IRQn,level);	//����pit0���ȼ�
		disable_irq(PIT_CH1_IRQn);			//����pit0�ж�
	}
}

void Voltage_Check()
{
	adc_init(Voltage_Detection);
	OLED_Write_String(3,2,(uint8_t*)"Voltage:");

	Voltage_Value = 1000.0000*Mean_Value_Filtering(Voltage_Detection,ADC_10bit)/1024*15;
	OLED_Write_Num1(8,4,Voltage_Value/1000);	
	OLED_Write_Char(9,4,'.');
	OLED_Write_Num3(10,4,Voltage_Value%1000);
	OLED_Write_Char(13,4,'V');		
		
	systick_delay_ms(1000);
	OLED_Clear();
}
 
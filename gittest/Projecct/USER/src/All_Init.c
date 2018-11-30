#include "All_Init.h"

extern int Current_Left_Base_Value, Current_Right_Base_Value;

int Voltage_Value=0;

void all_Init()
{
  get_clk();              //获取时钟频率 必须执行
	
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
	//ftm的计数引脚可查看KEA128_port_cfg.h文件内的FTM0_COUNT_PIN与FTM1_COUNT_PIN的宏定义得知
	//一个ftm同一时间只能实现一种功能，如果用于测速就不能用于输出PWM
	ftm_count_init(EncoderLEFT_Port);   //对E0引脚输入的脉冲进行计数    E0接编码器LSB    
	gpio_init(EncoderLEFT_DIRECT_PIN,GPI,0);    //用于判断方向                  C5接编码器DIR
	port_pull(EncoderLEFT_DIRECT_PIN);          //IO上拉
	port_pull(EncoderLEFT_PIN);          //IO上拉
	
	ftm_count_init(EncoderRIGHT_Port);   //对E7引脚输入的脉冲进行计数    E7接编码器LSB
	gpio_init(EncoderRIGHT_DIRECT_PIN,GPI,0);    //用于判断方向                  H5接编码器DIR
	port_pull(EncoderRIGHT_DIRECT_PIN);          //IO上拉
	port_pull(EncoderRIGHT_PIN);          //IO上拉
}

void motorInit()
{
	ftm_pwm_init(motor_port,leftmotor1,15000,0);//初始化PWM频率为15K，占空比为0
	ftm_pwm_init(motor_port,leftmotor2,15000,0);//初始化PWM频率为15K，占空比为0
	ftm_pwm_init(motor_port,rightmotor1,15000,0);//初始化PWM频率为15K，占空比为0
	ftm_pwm_init(motor_port,rightmotor2,15000,0);//初始化PWM频率为15K，占空比为0

//	adc_init(leftmotor_current);
//	adc_init(rightmotor_current);
//	Current_Left_Base_Value = Mean_Value_Filtering(leftmotor_current,ADC_8bit);
//	Current_Right_Base_Value = Mean_Value_Filtering(rightmotor_current,ADC_87bit);
}

void Inductance_Init()
{
	adc_init(Left_Left_Inductance);     //初始化ADC ADC引脚通过ADC通道号查看KEA128_adc.h文件得知
	adc_init(Left_Right_Inductance);
	adc_init(Right_Left_Inductance);
	adc_init(Right_Right_Inductance);
}

void Uart_Init()
{
		//初始化默认的调试串口
	uart_init(Uart_Port,115200);
//	 //开启串口接收功能
//	UART_ITConfig(UART5,UART_IT_RDRF,ENABLE);
//	//接通NVIC上对应串口中断线
//	NVIC_EnableIRQ(UART5_RX_TX_IRQn);
}

void Pit_Init(int Channel, int T, int level)
{
	if(Channel==0)
	{
		pit_init_us(pit0,T);	            //初始化pit0 周期设置为T		
		set_irq_priority(PIT_CH0_IRQn,level);	//设置pit0优先级
		disable_irq(PIT_CH0_IRQn);			//开启pit0中断
	}
	else if(Channel==1)
	{
		pit_init_us(pit1,T);	            //初始化pit0 周期设置为T		
		set_irq_priority(PIT_CH1_IRQn,level);	//设置pit0优先级
		disable_irq(PIT_CH1_IRQn);			//开启pit0中断
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
 
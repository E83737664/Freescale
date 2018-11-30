#include "key.h"

/***********************************************************************************************
 ���ܣ�������ʼ��
 �βΣ�0
 ���أ�0
 ��⣺��ʼ�������ϵ�KEY ����GPIO����
************************************************************************************************/
void KEY_Init(void)
{
	gpio_init(KEY1_PIN, GPI, 0);
	port_pull(KEY1_PIN);
	
	gpio_init(KEY2_PIN, GPI, 0);
	port_pull(KEY2_PIN);
	
	gpio_init(KEY3_PIN, GPI, 0);
	port_pull(KEY3_PIN);
	
	gpio_init(KEY4_PIN, GPI, 0);
	port_pull(KEY4_PIN);
	
	gpio_init(KEY5_PIN, GPI, 0);
	port_pull(KEY5_PIN);
	
	gpio_init(KEY6_PIN, GPI, 0);
	port_pull(KEY6_PIN);
	
	gpio_init(FM_PIN, GPO, 0);
}

int i=0;

void FM_Turn(uint8_t T)
{
	if(i>=T)
	{
		FM_TURN;
		i=0;
	}
	i++;
}


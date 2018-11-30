/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
-*
-*  K60,KEA���������ܳ�ר��
-*  �ļ����ܣ�      ���ú���
-*  �ļ����ͣ�      �����ļ�
-*  ����˵����      ɽ����λ��Э�������Լ�У�鲿��
										minibalance APPЭ�������Լ�У�鲿��
										����ʾ����v0.1.3����
-*                  
-*  ��д�ˣ�        ��Դ��,�³�
-*  ������־��      1.����minibalance APP����
										2.��������ʾ����v0.1.3����
-*  ���༭���ڣ�  2018/6/9
-*
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#include "My_DataSend.h"

extern int Encoder_Left, Encoder_Right, Encoder_Left_Last, Encoder_Right_Last;
extern int Encoder_Sum, Encoder_Sum_Last, Encoder_Sum_True, Encoder_Sum_True_Last;
extern int pwmBalance, pwmBalance_Last, pwmDirect, pwmDirect_Last, pwmGo, pwmGoOld, pwmGoNew,pwmDirectOld, pwmDirectNew, pwmOutput, pwmLeft,pwmRight;
extern int Angle, Angle_REVISE, Angle_REVISE_Last;
extern int Motor_Left_Current, Motor_Right_Current;
extern double directP_Revise,directP_Revise_Last, directD_Revise, directDD_Revise;  

extern uint8_t Track_Symbol;
 
extern int Angle_Target;

extern int16_t Gyro_X_REVISE, Gyro_X_Last_REVISE, Gyro_Y_REVISE, Gyro_Z_REVISE, Gyro_X,Gyro_Y,Gyro_Z;
extern int16_t ACC_X_REVISE, ACC_Y_REVISE, ACC_Z_REVISE, MAG_X_REVISE, MAG_Y_REVISE, MAG_Z_REVISE,ACC_Z,ACC_Z_Last_REVISE; 


//���ֵ
extern int EV_VALUE1,EV_VALUE2,EV_VALUE3,EV_VALUE4,EV_VALUE2_Last,EV_VALUE1_Last, EV_VALUE4_Last;
//ƫ��
extern int16_t DEVIATE,DEVIATE_Last,Delay_Limit_Cnt, DEVIATE_Temp;

//�������
extern uint16  Ring_In_Wait_Cnt;
extern uint16_t Ring_In_Wait;
extern uint16_t Ring_In_Symbol;
extern uint8_t Ring_Out_Symbol;
extern int Ring_Wait;
extern uint8_t Ring_Size[20];
extern uint8_t Ring_Cnt;
/*************************/

extern uint8_t Track_Symbol_Cnt,Special_State;
extern uint16_t Special_Time_Count,Ring_In_Wait;

//��ʱ����
extern int Pitch_Rate_Error,Pitch_Rate_Error_Last,Pitch_Target_rate,Pitch_Target_rate_Last,Ring_Wait_Out,Ring_Wait_In,Bump_Check;
                           // ����ֹ����
extern int Bump_Time_Count;                            //������·�� 
extern uint8_t Bump_Num;  
extern uint8_t Bump_Cnt; 
extern double angleP_REVISE;
extern uint8_t Ramp_Check;
extern uint8_t Ramp_Cnt,TurnTooBig_Flag;                               //�µ�����
extern int Ramp_Time[7];
extern int Ramp_Time_Count;
extern uint16 Special_Delay5Ms_Cnt;
extern uint16 Special_Delay_Cnt;
extern int16_t Bump_Time_Wait;

extern int Ring_Speed;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*******************************************************
*              ��Ҫ�������ݴ浽car_data����
*******************************************************/
/*
ɽ����λ��       ��ʾdata0~data7
minibalance APP  ��ʾdata0~data4
����ʾ����       ��ʾdata0~data19
*/

//#define data0  (Angle_REVISE - Angle_Target) * angleP_REVISE  
//#define data1  MAG_Z_REVISE
#define data0 EV_VALUE1  
#define data1 MAG_Z_REVISE
#define data2  EV_VALUE4

#define data3 Encoder_Sum
#define data4 pwmDirect
#define data5 directP_Revise

#define data6 Ring_Wait_In*10
#define data7 Track_Symbol*100
#define data8 0
#define data9 0
#define data10 0
#define data11 0
#define data12 0
#define data13 0
#define data14 0
#define data15 0
#define data16 0
#define data17 0
#define data18 0
#define data19 0



/*
���ڷ�������
*/
////////////////////////////////////////////////////////////////////////////////
//ɽ����λ��
////////////////////////////////////////////////////////////////////////////////
int16_t car_data[8];
void data_give(void)
{
	car_data[0] = data0;
	car_data[1] = data1;
	car_data[2] = data2;
	car_data[3] =	data3;
	car_data[4] =	data4;
	car_data[5] = data5;
	car_data[6] = data6;
	car_data[7] = data7;
}

void Uart_Send_Data_without_DMA(void)
{
	uint8_t i;
	
	uart_putchar(Uart_Port,0x03);
	uart_putchar(Uart_Port,0xFC);

	for(i=0;i<8;i++)
	{
		uart_putchar(Uart_Port,car_data[i] & 0x00FF);
		uart_putchar(Uart_Port,(car_data[i]>>8) & 0x00FF);
	}
	
	uart_putchar(Uart_Port,0xFC);
	uart_putchar(Uart_Port,0x03);
}

//ʵʱ����
void Live_Transmission_1()
{
	data_give();
	Uart_Send_Data_without_DMA();
}

////////////////////////////////////////////////////////////////////////////////
//minibalance APP
////////////////////////////////////////////////////////////////////////////////

uint8_t flag=1;
void Live_Transmission_APP()
{
	flag=!flag;
	if(flag==0)  printf("{A%d:%d:%d:%d}$",0,0,0,0);//��ӡ��APP���棨��ʾ�������100��
	else         printf("{B%d:%d:%d:%d:%d}$",data0,data1,data2,data3,data4);//��ӡ��APP����
	systick_delay_ms(25);
}

////////////////////////////////////////////////////////////////////////////////
//����ʾ����
////////////////////////////////////////////////////////////////////////////////

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))//0���,3���
void Live_Transmission_2(void)//��ע��10��ͨ������ȫ�ã����ֻʹ�ü���ͨ��������ͨ������ɾ������ɾ�����ͨ��������ʡ���ڴ���ʱ��
{    
  unsigned char data_to_send[50];
	unsigned char _cnt=0;
	int  _temp;
  unsigned char sum = 0,i = 0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0x14;
	_temp = (int)(0);//ͨ��1
	data_to_send[_cnt++]=BYTE1(_temp);//ͨ��1
	data_to_send[_cnt++]=BYTE0(_temp);//ͨ��1
	_temp = (int)(0);//ͨ��2
	data_to_send[_cnt++]=BYTE1(_temp);//ͨ��2
	data_to_send[_cnt++]=BYTE0(_temp);//ͨ��2
	_temp = (int)(0);//ͨ��3
	data_to_send[_cnt++]=BYTE1(_temp);//ͨ��3
	data_to_send[_cnt++]=BYTE0(_temp);//ͨ��3
	 _temp = (int)(0);//ͨ��4
	data_to_send[_cnt++]=BYTE1(_temp);//ͨ��4
	data_to_send[_cnt++]=BYTE0(_temp);//ͨ��4
	_temp = (int)(0);//ͨ��5
	data_to_send[_cnt++]=BYTE1(_temp);//ͨ��5
	data_to_send[_cnt++]=BYTE0(_temp);//ͨ��5
	_temp = (int)(0);//ͨ��6
	data_to_send[_cnt++]=BYTE1(_temp);//ͨ��6
	data_to_send[_cnt++]=BYTE0(_temp);//ͨ��6
  _temp = (int)(0);//ͨ��7
	data_to_send[_cnt++]=BYTE1(_temp);//ͨ��7
	data_to_send[_cnt++]=BYTE0(_temp);//ͨ��7
  _temp = (int)(0);//ͨ��8
	data_to_send[_cnt++]=BYTE1(_temp);//ͨ��8
	data_to_send[_cnt++]=BYTE0(_temp);//ͨ��8
  _temp = (int)(0);//ͨ��9
	data_to_send[_cnt++]=BYTE1(_temp);//ͨ��9
	data_to_send[_cnt++]=BYTE0(_temp);//ͨ��9
  _temp = (int)(0);//ͨ��10
	data_to_send[_cnt++]=BYTE1(_temp);//ͨ��10
	data_to_send[_cnt++]=BYTE0(_temp);//ͨ��10
	data_to_send[3] = _cnt-4;
	for( i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	for(i=0;i<_cnt;i++)
		uart_putchar(uart1,data_to_send[i]);
}





















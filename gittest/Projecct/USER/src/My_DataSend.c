/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
-*
-*  K60,KEA—杭电智能车专用
-*  文件功能：      公用函数
-*  文件类型：      函数文件
-*  内容说明：      山外上位机协议适配以及校验部分
										minibalance APP协议适配以及校验部分
										数字示波器v0.1.3适配
-*                  
-*  编写人：        高源辰,陈成
-*  更新日志：      1.加入minibalance APP适配
										2.加入数字示波器v0.1.3适配
-*  最后编辑日期：  2018/6/9
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


//电感值
extern int EV_VALUE1,EV_VALUE2,EV_VALUE3,EV_VALUE4,EV_VALUE2_Last,EV_VALUE1_Last, EV_VALUE4_Last;
//偏差
extern int16_t DEVIATE,DEVIATE_Last,Delay_Limit_Cnt, DEVIATE_Temp;

//环岛检测
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

//临时测试
extern int Pitch_Rate_Error,Pitch_Rate_Error_Last,Pitch_Target_rate,Pitch_Target_rate_Last,Ring_Wait_Out,Ring_Wait_In,Bump_Check;
                           // 检测防止误判
extern int Bump_Time_Count;                            //进颠簸路段 
extern uint8_t Bump_Num;  
extern uint8_t Bump_Cnt; 
extern double angleP_REVISE;
extern uint8_t Ramp_Check;
extern uint8_t Ramp_Cnt,TurnTooBig_Flag;                               //坡道计数
extern int Ramp_Time[7];
extern int Ramp_Time_Count;
extern uint16 Special_Delay5Ms_Cnt;
extern uint16 Special_Delay_Cnt;
extern int16_t Bump_Time_Wait;

extern int Ring_Speed;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*******************************************************
*              把要发的数据存到car_data数组
*******************************************************/
/*
山外上位机       显示data0~data7
minibalance APP  显示data0~data4
虚拟示波器       显示data0~data19
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
串口发送数据
*/
////////////////////////////////////////////////////////////////////////////////
//山外上位机
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

//实时传输
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
	if(flag==0)  printf("{A%d:%d:%d:%d}$",0,0,0,0);//打印到APP上面（显示比例最大100）
	else         printf("{B%d:%d:%d:%d:%d}$",data0,data1,data2,data3,data4);//打印到APP上面
	systick_delay_ms(25);
}

////////////////////////////////////////////////////////////////////////////////
//虚拟示波器
////////////////////////////////////////////////////////////////////////////////

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))//0最低,3最高
void Live_Transmission_2(void)//备注：10个通道不必全用，如果只使用几个通道，其他通道可以删除（先删后面的通道），节省串口传输时间
{    
  unsigned char data_to_send[50];
	unsigned char _cnt=0;
	int  _temp;
  unsigned char sum = 0,i = 0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0x14;
	_temp = (int)(0);//通道1
	data_to_send[_cnt++]=BYTE1(_temp);//通道1
	data_to_send[_cnt++]=BYTE0(_temp);//通道1
	_temp = (int)(0);//通道2
	data_to_send[_cnt++]=BYTE1(_temp);//通道2
	data_to_send[_cnt++]=BYTE0(_temp);//通道2
	_temp = (int)(0);//通道3
	data_to_send[_cnt++]=BYTE1(_temp);//通道3
	data_to_send[_cnt++]=BYTE0(_temp);//通道3
	 _temp = (int)(0);//通道4
	data_to_send[_cnt++]=BYTE1(_temp);//通道4
	data_to_send[_cnt++]=BYTE0(_temp);//通道4
	_temp = (int)(0);//通道5
	data_to_send[_cnt++]=BYTE1(_temp);//通道5
	data_to_send[_cnt++]=BYTE0(_temp);//通道5
	_temp = (int)(0);//通道6
	data_to_send[_cnt++]=BYTE1(_temp);//通道6
	data_to_send[_cnt++]=BYTE0(_temp);//通道6
  _temp = (int)(0);//通道7
	data_to_send[_cnt++]=BYTE1(_temp);//通道7
	data_to_send[_cnt++]=BYTE0(_temp);//通道7
  _temp = (int)(0);//通道8
	data_to_send[_cnt++]=BYTE1(_temp);//通道8
	data_to_send[_cnt++]=BYTE0(_temp);//通道8
  _temp = (int)(0);//通道9
	data_to_send[_cnt++]=BYTE1(_temp);//通道9
	data_to_send[_cnt++]=BYTE0(_temp);//通道9
  _temp = (int)(0);//通道10
	data_to_send[_cnt++]=BYTE1(_temp);//通道10
	data_to_send[_cnt++]=BYTE0(_temp);//通道10
	data_to_send[3] = _cnt-4;
	for( i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	for(i=0;i<_cnt;i++)
		uart_putchar(uart1,data_to_send[i]);
}





















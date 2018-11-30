#include "kalman.h"
#define Gyroscope_Q (10)//�����ǵ�R
#define Gyroscope_R (100)//�����ǵ�Q
#define ACC_Z_Q (10)
#define ACC_Z_R (200)
/*
				Q:��������,Q����,��̬��Ӧ��죬�����ȶ��Ա仵
        R:��������,R���󣬶�̬��Ӧ�����������ȶ��Ա��
*/



extern int Angle;

float  Gyro_x=0;	
float  Q_angle=0.1;//0.0001;  
float  Q_gyro=1;//0.00003;
float  R_angle=0.001;
float  Dt=0.001;//0.005;	                  
float  C_0 = 1.0;
float  Q_bias=0, Angle_err=0;
float  PCt_0=0.0, PCt_1=0, E=0.0;
float  K_0=0.0, K_1=0.0, t_0=0.0, t_1=0.0;
float  Pdot[4] ={0,0,0,0};
float  PP[2][2] = { { 1.0, 0 },{ 0, 1.0 } };


int16_t Finaldata_Gyroscope=0;

int16_t Finaldata_ACC=0;

void Kalman_Filter(int Gyro,int Accel)	
{
	Angle+=(Gyro - Q_bias) * Dt;          
	
	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; 

	Pdot[1]= -PP[1][1];
	Pdot[2]= -PP[1][1];
	Pdot[3]=Q_gyro;
	
	PP[0][0] += Pdot[0] * Dt;   
	PP[0][1] += Pdot[1] * Dt;  
	PP[1][0] += Pdot[2] * Dt;
	PP[1][1] += Pdot[3] * Dt;
		
	Angle_err =Accel-Angle;
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	Angle	+= K_0 * Angle_err;	 
	Q_bias	+= K_1 * Angle_err;	 
	Gyro_x   = Gyro - Q_bias;
}


int Kaman_Gyroscope(int signal)
{
    static float nowdata_p=20;
	  int16_t nowdata;
	  
	  float kg =0.1;
	  /*
	      ����������������Ż�������һ������
        Q:��������,Q����,��̬��Ӧ��죬�����ȶ��Ա仵
        R:��������,R���󣬶�̬��Ӧ�����������ȶ��Ա��
	      
	      �޸�1.0
	      ���������ź�����Ľ��
	  */
	  /*Ԥ��*/
	  nowdata = Finaldata_Gyroscope;
	  /*Э����*/
	  nowdata_p = nowdata_p+Gyroscope_Q;
	  /*����������*/
	  kg =nowdata_p/(nowdata_p+Gyroscope_R);
	  /*���Ž�*/
    Finaldata_Gyroscope = nowdata+kg*(signal - nowdata);
		/*����Э����*/
		nowdata_p=(1-kg)*nowdata_p;
		return Finaldata_Gyroscope;
}

int Kaman_ACC_Z(int signal)
{
    static float nowdata_p=20;
	  int16_t nowdata;
	  
	  float kg =0.1;
	  /*
	      ����������������Ż�������һ������
        Q:��������,Q����,��̬��Ӧ��죬�����ȶ��Ա仵
        R:��������,R���󣬶�̬��Ӧ�����������ȶ��Ա��
	      
	      �޸�1.0
	      ���������ź�����Ľ��
	  */
	  /*Ԥ��*/
	  nowdata = Finaldata_ACC;
	  /*Э����*/
	  nowdata_p = nowdata_p+ACC_Z_Q;
	  /*����������*/
	  kg =nowdata_p/(nowdata_p+ACC_Z_R);
	  /*���Ž�*/
    Finaldata_ACC = nowdata+kg*(signal - nowdata);
		/*����Э����*/
		nowdata_p=(1-kg)*nowdata_p;
		return Finaldata_ACC;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
-*
-*  K60���������ܳ�ר��
-*  �ļ����ܣ�      ����ͷ�ļ�
-*  �ļ����ͣ�      ͷ�ļ�
-*  ����˵����      ɽ����λ��Э�������Լ�У�鲿��
-*                  
-*  ��д�ˣ�        ��Դ��
-*  ������־��
-*  ���༭���ڣ�  2018/2/2
-*
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#ifndef __My_DataSend_H_
#define __My_DataSend_H_


#ifdef __cplusplus
	extern "C" {
#endif

		
#include "headfile.h"


void Uart_Send_Data_without_DMA(void);
void data_give(void);
void Live_Transmission_1(void);
void Live_Transmission_APP(void);
void Live_Transmission_2(void);

#ifdef __cplusplus
}
#endif

#endif



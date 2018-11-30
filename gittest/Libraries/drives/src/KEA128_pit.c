/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		KEA128_pit
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/

#include "KEA128_pit.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit��ʼ��
//  @param      pitn            ѡ��pitģ��
//  @param      cnt             ��ʱ�жϵ�ʱ��
//  @return     void
//  @since      v2.0
//  Sample usage:               pit_init(pit0,1000);								//��ʱ1000��busʱ�Ӻ��жϣ��û���ʹ��h�ļ�����ĺ���������pit_init_ms(pit0,1000);����ʱ�����1S
//								set_irq_priority(PIT_CH0_IRQn,1);					//�������ȼ�,�����Լ����������� �����÷�ΧΪ 0 - 3  ԽС���ȼ�Խ��
//								enable_irq(PIT_CH0_IRQn);							//��pit0���жϿ���
//								EnableInterrupts;									//���ܵ��жϿ���
//-------------------------------------------------------------------------------------------------------------------
void pit_init(PITn pitn, uint32 cnt)
{
	SIM->SCGC       |= SIM_SCGC_PIT_MASK;        			//ʹ��PITʱ��
    PIT->MCR         = (vuint32)PIT->MCR;                   //��ʱ��֤�ɹ�����PIT
	PIT->MCR         = 0;									//ʹ��PIT��ʱ��ʱ�� ������ģʽ�¼�������
	PIT->CHANNEL[pitn].LDVAL  = cnt;              			//��������ж�ʱ��
	PIT_FLAG_CLR(pitn);										//����жϱ�־λ
	PIT->CHANNEL[pitn].TCTRL &= ~ PIT_TCTRL_TEN_MASK;       //��ֹPITn��ʱ����������ռ���ֵ��
    PIT->CHANNEL[pitn].TCTRL  = ( 0
								| PIT_TCTRL_TEN_MASK        //ʹ�� PITn��ʱ��
								| PIT_TCTRL_TIE_MASK        //��PITn�ж�
								);
	//enable_irq( (IRQn_Type)((int)pitn + PIT_CH0_IRQn) );       //���ж�
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit��ʼ��
//  @param      pitn            ѡ��pitģ��
//  @param      cnt             ��ʱ��ʱ��ʱ��
//  @return     void
//  @since      v2.0
//  Sample usage:               pit_init(pit0,1000);		//��ʱ1000��busʱ��
//-------------------------------------------------------------------------------------------------------------------
void pit_delay(PITn pitn, uint32 cnt)
{
	SIM->SCGC       |= SIM_SCGC_PIT_MASK;        			//ʹ��PITʱ��
    PIT->MCR         = (vuint32)PIT->MCR;                   //��ʱ��֤�ɹ�����PIT
	PIT->MCR         = 0;									//ʹ��PIT��ʱ��ʱ�� ������ģʽ�¼�������
	PIT->CHANNEL[pitn].LDVAL  = cnt;              			//��������ж�ʱ��
	PIT_FLAG_CLR(pitn);										//����жϱ�־λ
	PIT->CHANNEL[pitn].TCTRL &= ~ PIT_TCTRL_TEN_MASK;       //��ֹPITn��ʱ����������ռ���ֵ��
    PIT->CHANNEL[pitn].TCTRL  = ( 0
								| PIT_TCTRL_TEN_MASK        //ʹ�� PITn��ʱ��
								//| PIT_TCTRL_TIE_MASK        //��PITn�ж�
								);
	while( !((PIT->CHANNEL[pitn].TFLG) & PIT_TFLG_TIF_MASK) ){}//�ȴ�ʱ�䵽

    PIT_FLAG_CLR(pitn);                                     //���жϱ�־λ
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit��ʼ��
//  @param      pitn            ѡ��pitģ��
//  @return     void
//  @since      v2.0
//  Sample usage:               pit_time_start(pit0);		//pit0��ʼ��ʱ
//-------------------------------------------------------------------------------------------------------------------
void pit_time_start(PITn pitn)
{
	SIM->SCGC       |= SIM_SCGC_PIT_MASK;        			//ʹ��PITʱ��
    PIT->MCR         = (vuint32)PIT->MCR;                   //��ʱ��֤�ɹ�����PIT
	PIT->MCR         = 0;									//ʹ��PIT��ʱ��ʱ�� ������ģʽ�¼�������
	PIT->CHANNEL[pitn].LDVAL  = ~0;              			//��������ж�ʱ��
	PIT_FLAG_CLR(pitn);										//����жϱ�־λ
	PIT->CHANNEL[pitn].TCTRL &= ~ PIT_TCTRL_TEN_MASK;       //��ֹPITn��ʱ����������ռ���ֵ��
    PIT->CHANNEL[pitn].TCTRL  = ( 0
								| PIT_TCTRL_TEN_MASK        //ʹ�� PITn��ʱ��
								//| PIT_TCTRL_TIE_MASK        //��PITn�ж�
								);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit��ʼ��
//  @param      pitn            ѡ��pitģ��
//  @return     void
//  @since      v2.0
//  Sample usage:               pit_time_get(pit0);			//��ȡ��ǰpit0��ʱʱ��
//-------------------------------------------------------------------------------------------------------------------
uint32 pit_time_get(PITn pitn)
{
	uint32 val;
	val = (uint32)(~0) - PIT->CHANNEL[pitn].CVAL;
	if(PIT->CHANNEL[pitn].TFLG &  PIT_TFLG_TIF_MASK)		//�ж�ʱ���Ƿ�ʱ
	{
		PIT_FLAG_CLR(pitn);									//����жϱ�־λ
		PIT->CHANNEL[pitn].TCTRL &= ~ PIT_TCTRL_TEN_MASK;   //��ֹPITn��ʱ����������ռ���ֵ��
		return 0XFFFFFFFF;									//��ʱ�������ֵ
	}
	return val;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit��ʼ��
//  @param      pitn            ѡ��pitģ��
//  @return     void
//  @since      v2.0
//  Sample usage:               pit_close(pit0);			//pit0ֹͣ��ʱ
//-------------------------------------------------------------------------------------------------------------------
void pit_close(PITn pitn)
{
	PIT_FLAG_CLR(pitn);										//����жϱ�־λ
	PIT->CHANNEL[pitn].TCTRL &= ~ PIT_TCTRL_TEN_MASK;       //��ֹPITn��ʱ����������ռ���ֵ��
}



















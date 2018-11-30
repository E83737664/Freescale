/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		common
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/

#include "common.h"
#include "system_SKEAZ1284.h"

#define EX_REF_CLK  16000 //(�����ⲿ�ο�ʱ��Ϊ16000KHZ)
uint32 ics_clk_khz;
uint32 ftm_clk_khz;
uint32 core_clk_khz;
uint32 bus_clk_khz;



void get_clk(void)
{
    uint16 prescaler_factor[]={1,2,4,8,16,32,64,128,256,512,1024};
    
    if(2 == KEA128_CLOCK)   //�ڲ�ʱ��
    {
        ics_clk_khz = 48000;
        ftm_clk_khz = 48000;
        core_clk_khz = 48000;
        bus_clk_khz = 24000; 
    }
    else                    //�ⲿʱ��
    {
        ics_clk_khz  = EX_REF_CLK * 1280 ;
        ics_clk_khz = ics_clk_khz / prescaler_factor[((ICS->C1&ICS_C1_RDIV_MASK) >> ICS_C1_RDIV_SHIFT) + 5];    //����FLL���Ƶ��
        ics_clk_khz = ics_clk_khz / prescaler_factor[(ICS->C2&ICS_C2_BDIV_MASK) >> ICS_C2_BDIV_SHIFT];          //����ICSCLKOUT
        
        core_clk_khz = ics_clk_khz  / (((SIM->CLKDIV&SIM_CLKDIV_OUTDIV1_MASK) >> SIM_CLKDIV_OUTDIV1_SHIFT) + 1);
        bus_clk_khz  = core_clk_khz / (((SIM->CLKDIV&SIM_CLKDIV_OUTDIV2_MASK) >> SIM_CLKDIV_OUTDIV2_SHIFT) + 1);
        ftm_clk_khz  = ics_clk_khz  / (((SIM->CLKDIV&SIM_CLKDIV_OUTDIV3_MASK) >> SIM_CLKDIV_OUTDIV3_SHIFT) + 1);
    }

//    uart_init(DEBUG_PORT,DEBUG_BAUD);   //��ʼ�����Դ��ڣ������ʹ��printf��������
}

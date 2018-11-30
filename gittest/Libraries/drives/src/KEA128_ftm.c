/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		KEA128_ftm
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/

#include "KEA128_ftm.h"

static FTM_Type * const FTMX[] = FTM_BASES;

void ftm_pwm_mux(FTMn ftmn, FTM_CHn ch)
{
    switch(ftmn)
    {
        case ftm0:
        {
            SIM->SCGC |= SIM_SCGC_FTM0_MASK;                //����FTM����ʱ��
            switch(ch)
            {
                case ftm_ch0:
                {
                    if(FTM0_CH0_PIN == A0)
                    {
                        SIM->PINSEL &= ~SIM_PINSEL_FTM0PS0_MASK;
                    }
                    else if(FTM0_CH0_PIN == B2)
                    {
                        SIM->PINSEL |= SIM_PINSEL_FTM0PS0_MASK;
                    }
                }break;
                
                case ftm_ch1:
                {
                    if(FTM0_CH1_PIN == A1)
                    {
                        SIM->PINSEL &= ~SIM_PINSEL_FTM0PS1_MASK;
                    }
                    else if(FTM0_CH1_PIN == B3)
                    {
                        SIM->PINSEL |= SIM_PINSEL_FTM0PS1_MASK;
                    }
                }break;
            }
        }break;
        
        case ftm1:
        {
            SIM->SCGC |= SIM_SCGC_FTM1_MASK;                //����FTM����ʱ��
            switch(ch)
            {
                case ftm_ch0:
                {
                    if(FTM1_CH0_PIN == C4)
                    {
                        SIM->PINSEL &= ~SIM_PINSEL_FTM1PS0_MASK;
                    }
                    else if(FTM1_CH0_PIN == H2)
                    {
                        SIM->PINSEL |= SIM_PINSEL_FTM1PS0_MASK;
                    }
                }break;

                case ftm_ch1:
                {
                    if(FTM1_CH1_PIN == C5)
                    {
                        SIM->PINSEL &= ~SIM_PINSEL_FTM1PS1_MASK;
                    }
                    else if(FTM1_CH1_PIN == E7)
                    {
                        SIM->PINSEL |= SIM_PINSEL_FTM1PS1_MASK;
                    }
                }break;
            }
        }break;
        
        case ftm2:
        {
            SIM->SCGC |= SIM_SCGC_FTM2_MASK;                //����FTM����ʱ��
            switch(ch)
            {
                case ftm_ch0:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS0_MASK;       
                    if(FTM2_CH0_PIN == C0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(0);
                    }
                    else if(FTM2_CH0_PIN == H0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(1);
                    }
                    else if(FTM2_CH0_PIN == F0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(2);
                    }
                }break;
                
                case ftm_ch1:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS1_MASK;       
                    if(FTM2_CH1_PIN == C1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(0);
                    }
                    else if(FTM2_CH1_PIN == H1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(1);
                    }
                    else if(FTM2_CH1_PIN == F1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(2);
                    }
                }break;
                
                case ftm_ch2:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS2_MASK;       
                    if(FTM2_CH2_PIN == C2)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(0);
                    }
                    else if(FTM2_CH2_PIN == D0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(1);
                    }
                    else if(FTM2_CH2_PIN == G4)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(2);
                    }
                }break;
                
                case ftm_ch3:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS3_MASK;       
                    if(FTM2_CH3_PIN == C3)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(0);
                    }
                    else if(FTM2_CH3_PIN == D1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(1);
                    }
                    else if(FTM2_CH3_PIN == G5)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(2);
                    }
                }break;
                
                case ftm_ch4:
                { 
                    if(FTM2_CH4_PIN == B4)
                    {
                        SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS4_MASK; 
                    }
                    else if(FTM2_CH4_PIN == G6)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS4_MASK;
                    }
                }break;
                
                case ftm_ch5:
                {
                    if(FTM2_CH5_PIN == B5)
                    {
                        SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS5_MASK;     
                    }
                    else if(FTM2_CH5_PIN == G7)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS5_MASK;
                    }
                }break;
            }
 
        }break;
    }
}


uint16 period[3];
//-------------------------------------------------------------------------------------------------------------------
//  @brief      FTM��ʼ��
//  @param      ftmn            ѡ��ģ��
//  @param      ch              ѡ��ͨ��
//  @param      freq            ��Ҫ���õ�Ƶ�ʣ���λHZ��
//  @param      duty            ��Ҫ���õ�ռ�ձ�
//  @return     void
//  @since      v2.0
//  Sample usage:               ftm_pwm_init(ftm0,ftm_ch0,50,500);		//ftm0ģ�飬0ͨ����50HZ���ٷ�֮50��ռ�ձ�
//-------------------------------------------------------------------------------------------------------------------
void ftm_pwm_init(FTMn ftmn, FTM_CHn ch, uint32 freq, uint32 duty)
{
    uint32 clk_hz ;
    uint16 mod;
    uint8  ps;
    uint16 cv;
    
    ftm_pwm_mux(ftmn,ch);
    
    // �� CPWMS = 0 �����ض���
    clk_hz = ftm_clk_khz*1000;
    //clk_hz/(ps*mod) = freq        =>>     clk_hz/freq = (ps*mod)      =>>
    //clk_hz/freq < ((1<<n)*65536)  =>>    (clk_hz/freq)/65536 < (1>>n) =>> ((clk_hz/freq)/65536)>>n < 1
    mod = (clk_hz >> 16 ) / freq ;          // ��ʱ�� mod ����һ��
    ps = 0;
    while((mod >> ps) >= 1)                 // �� (mod >> ps) < 1 ���˳� while ѭ�� ������ PS ����Сֵ
        ps++;
    if(ps>0x07) return ;                    //�������÷�Χ��ֱ�Ӳ�����������������ԭ��һ��������PWMƵ��̫�ͣ���������Ƶ��̫�ߵ���
    
    mod = (clk_hz >> ps) / freq;            // �� MOD ��ֵ
    period[ftmn] = mod;
    switch(ftmn)                            // ��ֵ CNTIN ��Ϊ0 �������ȣ�CnV - CNTIN ���� CnV ���� �������ˡ�
    {
        // EPWM������ �� MOD - CNTIN + 0x0001 == MOD - 0 + 1
        // �� CnV = (MOD - 0 + 1) * ռ�ձ� = (MOD - 0 + 1) * duty/ FTM_PRECISON
    case ftm0:
        cv = (duty * (mod - 0 + 1)) / FTM0_PRECISON;
        break;

    case ftm1:
        cv = (duty * (mod - 0 + 1)) / FTM1_PRECISON;
        break;

    case ftm2:
        cv = (duty * (mod - 0 + 1)) / FTM2_PRECISON;
        break;
    default:
        break;
    }
    
    FTMX[ftmn]->MOD = mod;                  //����PWM����
    
    FTMX[ftmn]->CONTROLS[ch].CnSC &= ~FTM_CnSC_ELSA_MASK;
    FTMX[ftmn]->CONTROLS[ch].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
    
    // set FTM clock to system clock 
    FTMX[ftmn]->SC = ( 0
                       //| FTM_SC_CPWMS_MASK       //0�����ض��� ��1�� ���Ķ��� ��ע���˱�ʾ 0��
                       | FTM_SC_PS(ps)             //��Ƶ���ӣ���Ƶϵ�� = 2^PS
                       | FTM_SC_CLKS(1)            //ʱ��ѡ�� 0��ûѡ��ʱ�ӣ����ã� 1��ϵͳʱ�ӣ� 2���̶�ʱ�ӣ� 3���ⲿʱ��
                       //| FTM_SC_TOIE_MASK        //����ж�ʹ�ܣ�ע���˱�ʾ ��ֹ����жϣ�
                     );

    if(ftm2 == ftmn)FTMX[ftmn]->CNTIN = 0;         //���ü�������ֵ��һ��û������;������
    FTMX[ftmn]->CONTROLS[ch].CnV = cv;             //����ռ�ձ�
    FTMX[ftmn]->CNT = 0;                           //��������д����ֵ�������CNTIN��ֵ
    
}
uint32 cv;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ռ�ձ�����
//  @param      ftmn            ѡ��ģ��
//  @param      ch              ѡ��ͨ��
//  @param      duty            ��Ҫ���õ�ռ�ձ�
//  @return     void
//  @since      v2.0
//  Sample usage:               ftm_pwm_duty(ftm0,ftm_ch0,500);		//ftm0ģ�飬0ͨ�����ٷ�֮50��ռ�ձ�
//-------------------------------------------------------------------------------------------------------------------
void ftm_pwm_duty(FTMn ftmn, FTM_CHn ch, uint32 duty)
{
    
    //ռ�ձ� = (CnV-CNTIN)/(MOD-CNTIN+1)
    switch(ftmn)
    {
    case ftm0:
        cv = (duty * (period[ftmn] - 0 + 1)) / FTM0_PRECISON;
        break;

    case ftm1:
        cv = (duty * (period[ftmn] - 0 + 1)) / FTM1_PRECISON;
        break;

    case ftm2:
        cv = (duty * (period[ftmn] - 0 + 1)) / FTM2_PRECISON;
        break;

    default:
        break;
    }
    
    FTMX[ftmn]->CONTROLS[ch].CnV = cv;      //����ռ�ձ�
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Ƶ������
//  @param      ftmn            ѡ��ģ��
//  @param      freq            ��Ҫ���õ�Ƶ�ʣ���λHZ��
//  @return     void
//  @since      v2.0
//  Sample usage:               ftm_pwm_freq(ftm0,50);		//ftm0ģ�飬50HZ
//-------------------------------------------------------------------------------------------------------------------
void ftm_pwm_freq(FTMn ftmn, uint32 freq)
{
    uint32 clk_hz;        //busƵ��/2
    uint32 mod;
    uint8 ps;

    // �� CPWMS = 0 �����ض���
    clk_hz = ftm_clk_khz * 1000 ;
    
    //clk_hz/(ps*mod) = freq        =>>     clk_hz/freq = (ps*mod)      =>>
    //clk_hz/freq < ((1<<n)*65536)  =>>    (clk_hz/freq)/65536 < (1>>n) =>> ((clk_hz/freq)/65536)>>n < 1
    mod = (clk_hz >> 16 ) / freq ;          // ��ʱ�� mod ����һ��
    ps = 0;
    while((mod >> ps) >= 1)                 // �� (mod >> ps) < 1 ���˳� while ѭ�� ������ PS ����Сֵ
        ps++;
    if(ps>0x07) return ;                    //�������÷�Χ��ֱ�Ӳ�����������������ԭ��һ��������PWMƵ��̫�ͣ���������Ƶ��̫�ߵ���
    
    mod = (clk_hz >> ps) / freq;            // �� MOD ��ֵ
    period[ftmn] = mod;
    
    
    FTMX[ftmn]->MOD = mod;                  //����PWM����
    
    // set FTM clock to system clock 
    FTMX[ftmn]->SC = ( 0
                       //| FTM_SC_CPWMS_MASK       //0�����ض��� ��1�� ���Ķ��� ��ע���˱�ʾ 0��
                       | FTM_SC_PS(ps)             //��Ƶ���ӣ���Ƶϵ�� = 2^PS
                       | FTM_SC_CLKS(1)            //ʱ��ѡ�� 0��ûѡ��ʱ�ӣ����ã� 1��ϵͳʱ�ӣ� 2���̶�ʱ�ӣ� 3���ⲿʱ��
                       //| FTM_SC_TOIE_MASK        //����ж�ʹ�ܣ�ע���˱�ʾ ��ֹ����жϣ�
                     );

    
    if(ftm2 == ftmn)FTMX[ftmn]->CNTIN = 0;  //���ü�������ֵ��һ��û������;������
    FTMX[ftmn]->CNT = 0;                    //��������д����ֵ�������CNTIN��ֵ
}


void ftm_count_mux(FTMn ftmn)
{
    
    switch(ftmn)
    {
        case ftm0:
        {
            SIM->SCGC |= SIM_SCGC_FTM0_MASK;                //����FTM����ʱ��
            SIM->PINSEL &= ~SIM_PINSEL_FTM0CLKPS_MASK;      //����ⲿʱ������ѡ��
            if(FTM0_COUNT_PIN == A5)
            {
                port_pull(A5);
                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(0);     //ѡ���ⲿʱ���������� A5
            }
            
            else if(FTM0_COUNT_PIN == E0)
            {
                port_pull(E0);
                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(1);     //ѡ���ⲿʱ���������� E0
            }
            
            else if(FTM0_COUNT_PIN == E7)
            {
                port_pull(E7);
                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(2);     //ѡ���ⲿʱ���������� E7
            }
        }break;
        
        case ftm1:
        {
            SIM->SCGC |= SIM_SCGC_FTM1_MASK;                //����FTM����ʱ��
            SIM->PINSEL &= ~SIM_PINSEL_FTM1CLKPS_MASK;      //����ⲿʱ������ѡ��
            if(FTM1_COUNT_PIN == A5)
            {
                port_pull(A5);
                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(0);     //ѡ���ⲿʱ���������� A5
            }
            
            else if(FTM1_COUNT_PIN == E0)
            {
                port_pull(E0);
                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(1);     //ѡ���ⲿʱ���������� E0
            }
            
            else if(FTM1_COUNT_PIN == E7)
            {
                port_pull(E7);
                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(2);     //ѡ���ⲿʱ���������� E7
            }
        }break;
        
        case ftm2:
        {
            SIM->SCGC |= SIM_SCGC_FTM2_MASK;                //����FTM����ʱ��
            SIM->PINSEL &= ~SIM_PINSEL_FTM2CLKPS_MASK;      //����ⲿʱ������ѡ��
            FTM2->CNTIN = 0;
            if(FTM2_COUNT_PIN == A5)
            {
                port_pull(A5);
                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(0);     //ѡ���ⲿʱ���������� A5
            }
            
            else if(FTM2_COUNT_PIN == E0)
            {
                port_pull(E0);
                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(1);     //ѡ���ⲿʱ���������� E0
            }
            
            else if(FTM2_COUNT_PIN == E7)
            {
                port_pull(E7);
                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(2);     //ѡ���ⲿʱ���������� E7
            }
        }break;
        
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ⲿ������ʼ��  ��ȡ����ֵ�����ڱ��������٣��޷�ʶ����ֻ�ܼ���������ʹ�ô���������ı�����
//  @param      ftmn            ѡ��ģ��
//  @return     void
//  @since      v2.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ftm_count_init(FTMn ftmn)
{
    ftm_count_mux(ftmn);                                    //���Ÿ��� �������� ������Ӧ����ʱ��
    
    FTMX[ftmn]->SC |= FTM_SC_PS(0);	                        //��Ƶϵ��	
    FTMX[ftmn]->SC |= FTM_SC_CLKS(3);                       //ѡ���ⲿʱ����ΪFTM����ʱ��
                
    FTMX[ftmn]->CNT = 0;                                    //���س�ʼ��ֵ
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ����ֵ      ���ڱ��������٣��޷�ʶ����ֻ�ܼ���������ʹ�ô���������ı�����
//  @param      ftmn            ѡ��ģ��
//  @return     uint16          ���ؼ���ֵ
//  @since      v2.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
uint16 ftm_count_get(FTMn ftmn)
{
    return FTMX[ftmn]->CNT ;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ֵ      ���ڱ��������٣��޷�ʶ����ֻ�ܼ���������ʹ�ô���������ı�����
//  @param      ftmn            ѡ��ģ��
//  @since      v2.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ftm_count_clean(FTMn ftmn)
{
    FTMX[ftmn]->CNT = 0;
}


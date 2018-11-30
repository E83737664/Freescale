/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		KEA128_uart
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/


#include "KEA128_uart.h"



UART_Type * uart[3] = UART_BASES;



void uart_mux(UARTn uartn)
{
    switch(uartn)
    {
        case uart0:
        {
            SIM->SCGC |= SIM_SCGC_UART0_MASK;               //ʹ�ܴ���0ʱ��
            if(B0 == UART0_RX_PIN)
            {
                SIM->PINSEL &= ~SIM_PINSEL_UART0PS_MASK;
            }
            else
            {
                SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;
                port_pull(A2);                              
                port_pull(A3);
            }
        }break;
        
        case uart1:
        {
            SIM->SCGC |= SIM_SCGC_UART1_MASK;               //ʹ�ܴ���0ʱ��
            if(C6 == UART1_RX_PIN) 
            {
                SIM->PINSEL1 &= ~SIM_PINSEL1_UART1PS_MASK;
            }
            else
            {
                SIM->PINSEL1 |= SIM_PINSEL1_UART1PS_MASK;
            }
        }break;
        
        case uart2:
        {
            SIM->SCGC |= SIM_SCGC_UART2_MASK;               //ʹ�ܴ���0ʱ��
            if(D6 == UART2_RX_PIN) 
            {
                SIM->PINSEL1 &= ~SIM_PINSEL1_UART2PS_MASK;
            }
            else
            {
                SIM->PINSEL1 |= SIM_PINSEL1_UART2PS_MASK;
            }
        }break;
        
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      uart ��ʼ��
//  @param      uartn           ѡ�񴮿�(uart0,uart1,uart2)
//  @param      baud            ���ڲ�����
//  @return     uint32          ʵ�����õò�����
//  @since      v1.0
//  Sample usage:               uart_init(uart1,9600);   //��ʼ������1Ϊ1λ��ʼλ��8λ����λ��1λֹͣλ��������9600
//  @note                       ����KEA128û�в�����΢���Ĵ�������������õò����ʽϸߵ���������Ƚϴ���˷���ʵ�ʲ���������У��
//-------------------------------------------------------------------------------------------------------------------
uint32 uart_init(UARTn uartn, uint32 baud)
{
    vuint32 uart_input_clk;
    uint32 sbr;
    
    uart_mux(uartn);
    
    //���õ�ʱ��Ӧ�ý�ֹ���ͺͽ���
    uart[uartn]->C2 &= ~(0
                         | UART_C2_TE_MASK
                         | UART_C2_RE_MASK);
    
    //���ó�8λ��У��ģʽ
    //���� UART ���ݸ�ʽ��У�鷽ʽ��ֹͣλλ����ͨ������ UART ģ����ƼĴ��� C1 ʵ�֣�
    uart[uartn]->C1 |= (0
                        //| UART_C1_M_MASK                      //9 λ�� 8 λģʽѡ�� : 0 Ϊ 8λ ��1 Ϊ 9λ��ע���˱�ʾ0����8λ�� �������9λ��λ8��UARTx_C3�
                        //| UART_C1_PE_MASK                     //��żУ��ʹ�ܣ�ע���˱�ʾ���ã�
                        //| UART_C1_PT_MASK                     //У��λ���� : 0 Ϊ żУ�� ��1 Ϊ ��У��
                       );
    
    //���㲨����
    uart_input_clk = bus_clk_khz * 1000;   //busʱ��

    //UART ������ = UART ģ��ʱ�� / (16 �� SBR[12:0])
    //SBR = UART ģ��ʱ�� / (16 * UART ������)
    sbr = ((uart_input_clk>>4)*10 / baud + 5)/10;               //��������
    if(sbr > 0x1FFF)sbr = 0x1FFF;                               //SBR �� 13bit�����Ϊ 0x1FFF

    //д SBR
    uart[uartn]->BDH &= ~UART_BDH_SBR_MASK;                     //���ԭ��������
    uart[uartn]->BDH |= UART_BDH_SBR(sbr>>8);                   //��д��SBR��λ
    uart[uartn]->BDL  = UART_BDL_SBR((uint8)sbr);               //��д��SBR��λ

    // �����ͺͽ���
    uart[uartn]->C2 |= (0
                        | UART_C2_TE_MASK                       //����ʹ��
                        | UART_C2_RE_MASK                       //����ʹ��
                        //| UART_C2_TIE_MASK                    //�����жϻ�DMA��������ʹ�ܣ�ע���˱�ʾ���ã�
                        //| UART_C2_TCIE_MASK                   //��������ж�ʹ�ܣ�ע���˱�ʾ���ã�
                        //| UART_C2_RIE_MASK                    //�������жϻ�DMA��������ʹ�ܣ�ע���˱�ʾ���ã�
                        );
    //����KEA128û�в�����΢���Ĵ�������������õò����ʽϸߵ���������Ƚϴ���˷���ʵ�ʲ���������У��
    return ((uart_input_clk>>4)/sbr);                           //����ʵ�ʲ�����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڷ���һ���ֽ�
//  @param      uartn           ѡ�񴮿�
//  @param      ch              Ҫ���͵��ַ�
//  @return     void
//  @since      v1.0
//  Sample usage:               uart_putchar(uart2,0x5a);   
//-------------------------------------------------------------------------------------------------------------------
void uart_putchar(UARTn uartn, uint8 ch)
{
    while( !((uart[uartn]->S1) & UART_S1_TDRE_MASK) );  //�ȴ����ͻ�������
    uart[uartn]->D = (uint8)ch;                         //��������
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڷ�������
//  @param      uartn           ѡ�񴮿�
//  @param      *buff           Ҫ���͵������ַ
//  @param      len             ���ͳ���
//  @return     void
//  @since      v1.0
//  Sample usage:               uart_putbuff(uart2,&a[0],sizeof(a));  
//-------------------------------------------------------------------------------------------------------------------
void uart_putbuff (UARTn uartn, uint8 *buff, uint32 len)
{
    while(len--)
    {
        uart_putchar(uartn, *buff);
        buff++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڷ����ַ���
//  @param      uartn           ѡ�񴮿�
//  @param      *str            Ҫ���͵��ַ�����ַ
//  @return     void
//  @since      v1.0
//  Sample usage:               uart_putstr(uart2,"i lvoe you"); 
//-------------------------------------------------------------------------------------------------------------------
void uart_putstr (UARTn uartn, const uint8 *str)
{
    while(*str)
    {
        uart_putchar(uartn, *str++);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڵȴ�����1���ַ�
//  @param      uartn           ѡ�񴮿�
//  @param      *str            ���յĵ�ַ
//  @return     void
//  @since      v1.0
//  Sample usage:               uart_getchar(uart2,&dat);
//-------------------------------------------------------------------------------------------------------------------
void uart_getchar (UARTn uartn, uint8 *ch) 
{
    while(!(uart[uartn]->S1 & UART_S1_RDRF_MASK));  //�ȴ���������   
    *ch =  uart[uartn]->D;                          // ��ȡ���յ���8λ����
    // ��ȡ 9λ����ʱch Ӧ����uint16 *���͵ķ������ݻ������
    // *ch =   ((( UARTx_C3_REG(UARTN[uartn]) & UART_C3_R8_MASK ) >> UART_C3_R8_SHIFT ) << 8)   |   UART_D_REG(UARTN[uartn]);  //����9bit
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���������ж�
//  @param      uartn           ѡ�񴮿�
//  @return     void
//  @since      v1.0
//  Sample usage:               uart_rx_irq_en(uart2);
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_irq_en(UARTn uartn)
{
    uart[uartn]->C2 |= UART_C2_RIE_MASK;                                        //ʹ��UART�����ж�
    enable_irq((IRQn_Type)((uint8)uartn + UART0_IRQn));                                //ʹ��IRQ�ж�
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������������ж�
//  @param      uartn           ѡ�񴮿�
//  @return     void
//  @since      v1.0
//  Sample usage:               uart_txc_irq_en(uart2);
//-------------------------------------------------------------------------------------------------------------------
void uart_txc_irq_en(UARTn uartn)
{
    uart[uartn]->C2 |= UART_C2_TCIE_MASK;                                       //ʹ��UART��������ж�
    enable_irq((IRQn_Type)((uint8)uartn + UART0_IRQn));                                //ʹ��IRQ�ж�
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ֹ�����ж�
//  @param      uartn           ѡ�񴮿�
//  @return     void
//  @since      v1.0
//  Sample usage:               uart_rx_irq_dis(uart2);
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_irq_dis(UARTn uartn)
{
    uart[uartn]->C2 &= ~UART_C2_RIE_MASK;                                       //��ֹUART�����ж�

    //��������жϻ�û�йأ��򲻹ر�IRQ
    if(!(uart[uartn]->C2 & (UART_C2_TIE_MASK | UART_C2_TCIE_MASK)) )
    {
        disable_irq((IRQn_Type)((uint8)uartn + UART0_IRQn));                           //��IRQ�ж�
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ֹ��������ж�
//  @param      uartn           ѡ�񴮿�
//  @return     void
//  @since      v1.0
//  Sample usage:               uart_txc_irq_dis(uart2);
//-------------------------------------------------------------------------------------------------------------------
void uart_txc_irq_dis(UARTn uartn)
{
    uart[uartn]->C2 &= ~UART_C2_TCIE_MASK;                                      //��ֹUART��������ж�

    //��������жϻ�û�йأ��򲻹ر�IRQ
    if(!(uart[uartn]->C2 & UART_C2_RIE_MASK) )
    {
        disable_irq((IRQn_Type)((uint8)uartn + UART0_IRQn));              //��IRQ�ж�
    }
}

//�����жϺ����뵽isr.c�ļ��ο�



//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ض���printf ������
//  @param      ch      ��Ҫ��ӡ���ֽ�
//  @param      stream  ������
//  @since      v1.0
//  @note       �˺����ɱ������Դ������printf������
//-------------------------------------------------------------------------------------------------------------------
int fputc(int ch, FILE *stream)
{
    uart_putchar(DEBUG_PORT, (char)ch);
    return(ch);
}














#ifndef _OLED_H_
#define _OLED_H_

#include "headfile.h"

/******************** Device Config ********************/

/* OLED�˿ں궨�� */		
#if(SmartCar_Number == 1)
#define OLED_SCL    I4      //D0
#define OLED_SDA    I1 //D1
#define OLED_RST    H2   //RST
#define OLED_DC     H5     //DC
#endif

#if(SmartCar_Number == 2)
#define OLED_SCL    I4      //D0
#define OLED_SDA    I1 //D1
#define OLED_RST    H2   //RST
#define OLED_DC     H5     //DC
#endif


#define Font   1//1�Ǵ����� 0��С���� С����Ƚ�ʡ�ռ�


/* OLED�ֱ��ʺ궨�� */
#define  X_WIDTH  128
#define  Y_WIDTH  64



/* OLED IO������滻 */
#define OLED_D0_OL		gpio_set (OLED_SCL,0)//D0 IO������͵�ƽ
#define OLED_D0_OH		gpio_set (OLED_SCL,1)//D0 IO������ߵ�ƽ

#define OLED_D1_OL		gpio_set (OLED_SDA,0)	//D1 IO������͵�ƽ
#define OLED_D1_OH		gpio_set (OLED_SDA,1)	//D1 IO������ߵ�ƽ

#define OLED_RST_OL		gpio_set (OLED_RST,0)	//RST IO������͵�ƽ
#define OLED_RST_OH		gpio_set (OLED_RST,1)	//RST IO������ߵ�ƽ

#define OLED_DC_OL		gpio_set (OLED_DC,0)	//DC IO������͵�ƽ
#define OLED_DC_OH		gpio_set (OLED_DC,1)	//DC IO������ߵ�ƽ



/* Function Prototypes */
/*
 *  ����д��
 */
void OLED_WrDat(uint8_t data);

/*
 *  ����д��
 */
void OLED_WrCmd(uint8_t cmd);

/*
 *  ��������
 */
void OLED_Set_XY(uint8_t x, uint8_t y);

/*
 *  ��������
 */
void OLED_Clear(void);

/*
 *  ��ʱ����
 */
void OLED_Delay_ms(uint16_t ms);

/*
 *  Һ����ʼ��
 */
void OLED_Init(void);        
     

/******************************************************************************
 �������� ��OLED_Write_Char
 �������� ���ַ���ʾ
 ����˵�� ��x  SmallChars(С����) -- (0 - 20)��21��
               LargeChars(������) -- (0 - 15)��16��
            y  SmallChars(С����) -- (0 - 7) �� 8��
               LargeChars(������) -- (0 - 6) �� 4��  ** yֻ��ȡ"0, 2, 4, 6" 4�� **
            c  ������������ַ�
 �������� ����
 ʾ    �� ��OLED_Write_Char(0, 0, 'A'); -- ��0��0�п�ʼ��� A
*******************************************************************************/
void OLED_Write_Char(uint8_t x, uint8_t y, uint8_t c);


/******************************************************************************
 �������� ��OLED_Write_String
 �������� ���ַ�����ʾ
 ����˵�� ��x  SmallChars(С����) -- (0 - 20)��21��
               LargeChars(������) -- (0 - 15)��16��
            y  SmallChars(С����) -- (0 - 7) �� 8��
               LargeChars(������) -- (0 - 6) �� 4��  ** yֻ��ȡ"0, 2, 4, 6" 4�� **
            *s �ַ���
 �������� ����
 ʾ    �� ��OLED_Write_String(0, 2, (uint8_t*)"Hello"); -- ��2��0�п�ʼ��� Hello
*******************************************************************************/   
void OLED_Write_String(uint8_t x, uint8_t y, uint8_t *s);


/******************************************************************************
 �������� ��OLED_Write_Num3
 �������� ��3λ������ʾ
 ����˵�� ��x   SmallChars(С����) -- (0 - 20)��21��
                LargeChars(������) -- (0 - 15)��16��
            y   SmallChars(С����) -- (0 - 7) �� 8��
                LargeChars(������) -- (0 - 6) �� 4��  ** yֻ��ȡ"0, 2, 4, 6" 4�� **
            num xxx  3λ����
 �������� ����
 ʾ    �� ��OLED_Write_Num3(0, 0, 199);
*******************************************************************************/
void OLED_Write_Num3(uint8_t x, uint8_t y, uint16_t num);


/******************************************************************************
 �������� ��OLED_Write_Char
 �������� ��4λ������ʾ
 ����˵�� ��x   SmallChars(С����) -- (0 - 20)��21��
                LargeChars(������) -- (0 - 15)��16��
            y   SmallChars(С����) -- (0 - 7) �� 8��
                LargeChars(������) -- (0 - 6) �� 4��  ** yֻ��ȡ"0, 2, 4, 6" 4�� **
            num xxxx  4λ����
 �������� ����
 ʾ    �� ��OLED_Write_Num4(0, 0, 1999);
*******************************************************************************/ 
void OLED_Write_Num4(uint8_t x, uint8_t y, uint16_t num);

void OLED_Write_Num5(uint8_t x, uint8_t y, uint16_t num);
void OLED_Write_Num5_Revise(uint8_t x, uint8_t y, int num);
void OLED_Write_Num2(uint8_t x, uint8_t y, uint8_t num);
void OLED_Write_Num1(uint8_t x, uint8_t y, uint8_t num);
void OLED_Write_Value(uint8_t x, uint8_t y, uint16_t num,uint8_t Type);

void dis_bmp(uint16_t high, uint16_t width, uint8_t *p,uint8_t value);

//////////////////////////////////////
void OLED_Write_Chinese(uint8_t x, uint8_t y, uint8_t weiShu, uint8_t ziShu);
void OLED_Clear_Part(uint8_t y,uint8_t x,uint8_t len_Y, uint8_t len_X);


#endif /* _OLED_H_ */


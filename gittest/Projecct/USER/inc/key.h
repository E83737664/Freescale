#ifndef _KEY_H_
#define _KEY_H_

#include "headfile.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
//����

#if(SmartCar_Number == 1)
#define KEY1_PIN  (H6)
#define KEY2_PIN  (H7)      //ȷ��
#define KEY3_PIN  (G2)      //����
#define KEY4_PIN  (G0)      //����
#define KEY5_PIN  (G1)      //����
#define KEY6_PIN  (G3)      //����
#define FM_PIN  (I0)
#endif 

#if(SmartCar_Number == 2)
#define KEY1_PIN  (H6)
#define KEY2_PIN  (H7)      //ȷ��
#define KEY3_PIN  (G2)      //����
#define KEY4_PIN  (G0)      //����
#define KEY5_PIN  (G1)      //����
#define KEY6_PIN  (G3)      //����
#define FM_PIN  (I0)
#endif 

	 
//λ��
#define KEY1      gpio_get(KEY1_PIN)
#define KEY2      gpio_get(KEY2_PIN)
#define KEY3      gpio_get(KEY3_PIN)
#define KEY4      gpio_get(KEY4_PIN)
#define KEY5      gpio_get(KEY5_PIN)
#define KEY6      gpio_get(KEY6_PIN)
#define FM(n)     gpio_set(FM_PIN,n) 
#define FM_TURN   gpio_turn(FM_PIN)


//��������ʵ�ֵĽӿں���	 
void KEY_Init(void);
void FM_Turn(uint8_t T);

#ifdef __cplusplus
}
#endif 

#endif

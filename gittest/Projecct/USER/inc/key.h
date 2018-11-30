#ifndef _KEY_H_
#define _KEY_H_

#include "headfile.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
//引脚

#if(SmartCar_Number == 1)
#define KEY1_PIN  (H6)
#define KEY2_PIN  (H7)      //确定
#define KEY3_PIN  (G2)      //减少
#define KEY4_PIN  (G0)      //下移
#define KEY5_PIN  (G1)      //增加
#define KEY6_PIN  (G3)      //上移
#define FM_PIN  (I0)
#endif 

#if(SmartCar_Number == 2)
#define KEY1_PIN  (H6)
#define KEY2_PIN  (H7)      //确定
#define KEY3_PIN  (G2)      //减少
#define KEY4_PIN  (G0)      //下移
#define KEY5_PIN  (G1)      //增加
#define KEY6_PIN  (G3)      //上移
#define FM_PIN  (I0)
#endif 

	 
//位宏
#define KEY1      gpio_get(KEY1_PIN)
#define KEY2      gpio_get(KEY2_PIN)
#define KEY3      gpio_get(KEY3_PIN)
#define KEY4      gpio_get(KEY4_PIN)
#define KEY5      gpio_get(KEY5_PIN)
#define KEY6      gpio_get(KEY6_PIN)
#define FM(n)     gpio_set(FM_PIN,n) 
#define FM_TURN   gpio_turn(FM_PIN)


//本构件所实现的接口函数	 
void KEY_Init(void);
void FM_Turn(uint8_t T);

#ifdef __cplusplus
}
#endif 

#endif

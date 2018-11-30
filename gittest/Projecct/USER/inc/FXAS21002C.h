#ifndef _FXAS21002C_H_
#define _FXAS21002C_H_

#include "headfile.h"

#define	FXAS21002C_SlaveAddress   0x20	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改

//FXAS21002C寄存器
#define FXAS21002C_STATUS_REG 0x07

#define FXAS21002C_WHO_AM_I 			  0x0C
#define FXAS21002C_CTRL_REG0 				0x0D
#define FXAS21002C_CTRL_REG1 			  0x13
#define FXAS21002C_CTRL_REG2 				0x14
#define FXAS21002C_CTRL_REG3 				0x15
#define FXAS21002C_OUT_TEMP 				0x12

#define FXAS21002C_OUT_X_H 				0x01
#define FXAS21002C_OUT_X_L 				0x02
#define FXAS21002C_OUT_Y_H 				0x03
#define FXAS21002C_OUT_Y_L 				0x04
#define FXAS21002C_OUT_Z_H 				0x05
#define FXAS21002C_OUT_Z_L 				0x06

#define FXAS21002C_WHO_AM_I_VAL   0xD7

void tly_delay(uint16_t k);
void FXAS21002C_Init(void);
int16_t FXAS21002C_GetResult(uint8_t Status, uint8_t Regs_Addr1, uint8_t Regs_Addr2);
void FXAS21002C_XYZ(void);

#endif

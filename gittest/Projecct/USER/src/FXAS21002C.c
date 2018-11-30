#include "FXAS21002C.h"


//延时函数
void tly_delay(uint16_t k)		 
{
    uint8_t i;	 

    while(--k)
    {
        for(i=0;i<100;i++); //延时时间长短，0--255可选
    }
}

void FXAS21002C_Init()
{
	while(i2c_read_reg(i2c1,FXAS21002C_SlaveAddress,FXAS21002C_WHO_AM_I)!=FXAS21002C_WHO_AM_I_VAL);
	tly_delay(10);
	
	i2c_write_reg(i2c1,FXAS21002C_SlaveAddress,FXAS21002C_CTRL_REG3,0x40);
	i2c_write_reg(i2c1,FXAS21002C_SlaveAddress,FXAS21002C_CTRL_REG1,0x01);
	tly_delay(10);
	i2c_write_reg(i2c1,FXAS21002C_SlaveAddress,FXAS21002C_CTRL_REG1,0x03);
}

/*
 * 函数功能：读FXAS21002C角速度输出
 * 参数
 *       Status - 数据寄存器状态
 *       Regs_Addr - 数据寄存器地址
 * 函数返回值：角速度值（int16）
 */   
int16_t FXAS21002C_GetResult(uint8_t Status, uint8_t Regs_Addr1, uint8_t Regs_Addr2) 
{
//  uint16_t cnt=0;
//	uint8_t ret=0;
  int16_t result,temp;
  
  // 等待转换完成并取出值 
//  while(!(ret&(ret&0x08)>>3)) 
//  {
//		ret=read_reg(FXAS21002C_SlaveAddress,Status);
//    if(++cnt>500)
//      break;
//  }

	result=i2c_read_reg(i2c1,FXAS21002C_SlaveAddress,Regs_Addr1);
	temp=i2c_read_reg(i2c1,FXAS21002C_SlaveAddress,Regs_Addr2);
    
	result=result<<8;
  result=result|temp;
  
  return result>>2;
}

//读取3轴角速度
int16_t Gyro_X, Gyro_Y, Gyro_Z;
void FXAS21002C_XYZ()
{
    Gyro_X = FXAS21002C_GetResult(FXAS21002C_STATUS_REG, FXAS21002C_OUT_X_H, FXAS21002C_OUT_X_L);
    Gyro_Y = FXAS21002C_GetResult(FXAS21002C_STATUS_REG, FXAS21002C_OUT_Y_H, FXAS21002C_OUT_Y_L);
    Gyro_Z = FXAS21002C_GetResult(FXAS21002C_STATUS_REG, FXAS21002C_OUT_Z_H, FXAS21002C_OUT_Z_L);
}



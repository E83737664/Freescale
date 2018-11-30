#include "FXOS8700CQR1.h"

void acc_delay(uint16_t k)		 
{
	uint8_t i;	 
	while(--k)
	{
			for(i=0;i<100;i++); //延时时间长短，0--255可选
	}
}

void FXOS8700CQR1_Init()
{
	while(i2c_read_reg(i2c1,FXOS8700CQR1_SlaveAddress,FXOS8700CQR1_WHO_AM_I)!=FXOS8700CQR1_WHO_AM_I_VAL);
	acc_delay(10);
	
	i2c_write_reg(i2c1,FXOS8700CQR1_SlaveAddress,FXOS8700CQR1_CTRL_REG1,0x00);
	acc_delay(10);	
	i2c_write_reg(i2c1,FXOS8700CQR1_SlaveAddress,FXOS8700CQR1_CTRL_REG1,0x0f);
	acc_delay(10);	
	i2c_write_reg(i2c1,FXOS8700CQR1_SlaveAddress,FXOS8700CQ_M_CTRL_REG1,0x1F);
	acc_delay(10);
	i2c_write_reg(i2c1,FXOS8700CQR1_SlaveAddress,FXOS8700CQ_M_CTRL_REG2,0x20);
	acc_delay(10);
	i2c_write_reg(i2c1,FXOS8700CQR1_SlaveAddress,FXOS8700CQ_XYZ_DATA_CFG,0x00);
	acc_delay(10);
	i2c_write_reg(i2c1,FXOS8700CQR1_SlaveAddress,FXOS8700CQR1_CTRL_REG1,0x05);
	acc_delay(10);	
}

/*
 * 函数功能：读FXOS8700CQR1角速度/磁力计输出
 * 参数
 *       Status - 数据寄存器状态
 *       Regs_Addr - 数据寄存器地址
 * 函数返回值：加速度/磁力值（int16）
 */   
int16_t FXOS8700CQR1_GetResult(uint8_t Status, uint8_t Regs_Addr1, uint8_t Regs_Addr2) 
{
//  uint16_t cnt=0;
//	uint8_t ret=0;
  int16_t result,temp;

  // 等待转换完成并取出值 
//  while(!(ret&(ret&0x08)>>3)) 
//  {
//		ret=i2c_read_reg(i2c1,FXOS8700CQR1_SlaveAddress,Status);
//    if(++cnt>500)
//      break;
//  }

	result=i2c_read_reg(i2c1,FXOS8700CQR1_SlaveAddress,Regs_Addr1);
	temp=i2c_read_reg(i2c1,FXOS8700CQR1_SlaveAddress,Regs_Addr2);
    
	result=result<<8;
  result=result|temp;
  
  return result>>3;
}

//读取3轴加速度
int16_t ACC_X, ACC_Y, ACC_Z, MAG_X, MAG_Y, MAG_Z; 
void FXOS8700CQR1_XYZ()
{
//	ACC_X = FXOS8700CQR1_GetResult(FXOS8700CQR1_ACCELERATION_DR_STATUS, FXOS8700CQR1_ACCELERATION_OUT_X_H, FXOS8700CQR1_ACCELERATION_OUT_X_L);
//	ACC_Y = FXOS8700CQR1_GetResult(FXOS8700CQR1_ACCELERATION_DR_STATUS, FXOS8700CQR1_ACCELERATION_OUT_Y_H, FXOS8700CQR1_ACCELERATION_OUT_Y_L);  
	ACC_Z = FXOS8700CQR1_GetResult(FXOS8700CQR1_ACCELERATION_DR_STATUS, FXOS8700CQR1_ACCELERATION_OUT_Z_H, FXOS8700CQR1_ACCELERATION_OUT_Z_L); 
	
	MAG_X = FXOS8700CQR1_GetResult(FXOS8700CQR1_MAGNETIC_DR_STATUS, FXOS8700CQR1_MAGNETIC_OUT_X_H, FXOS8700CQR1_MAGNETIC_OUT_X_L);
//	MAG_Y = FXOS8700CQR1_GetResult(FXOS8700CQR1_MAGNETIC_DR_STATUS, FXOS8700CQR1_MAGNETIC_OUT_Y_H, FXOS8700CQR1_MAGNETIC_OUT_Y_L);  
  	MAG_Z = FXOS8700CQR1_GetResult(FXOS8700CQR1_MAGNETIC_DR_STATUS, FXOS8700CQR1_MAGNETIC_OUT_Z_H, FXOS8700CQR1_MAGNETIC_OUT_Z_L); 
}


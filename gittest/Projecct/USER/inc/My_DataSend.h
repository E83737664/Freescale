/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
-*
-*  K60—杭电智能车专用
-*  文件功能：      公用头文件
-*  文件类型：      头文件
-*  内容说明：      山外上位机协议适配以及校验部分
-*                  
-*  编写人：        高源辰
-*  更新日志：
-*  最后编辑日期：  2018/2/2
-*
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#ifndef __My_DataSend_H_
#define __My_DataSend_H_


#ifdef __cplusplus
	extern "C" {
#endif

		
#include "headfile.h"


void Uart_Send_Data_without_DMA(void);
void data_give(void);
void Live_Transmission_1(void);
void Live_Transmission_APP(void);
void Live_Transmission_2(void);

#ifdef __cplusplus
}
#endif

#endif



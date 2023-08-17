#ifndef _ADXL345_H
#define _ADXL345_H

#include "stm32f1xx_hal.h"

#define ADXL345_GPIO  GPIOB
#define ADXL345_GPIOCLK  __HAL_RCC_GPIOB_CLK_ENABLE()
#define ADXL345_SDA   GPIO_PIN_11
#define ADXL345_SCL   GPIO_PIN_10



#define SCL_0 HAL_GPIO_WritePin(ADXL345_GPIO, ADXL345_SCL, GPIO_PIN_RESET)
#define SCL_1 HAL_GPIO_WritePin(ADXL345_GPIO, ADXL345_SCL, GPIO_PIN_SET)
#define SDA_0 HAL_GPIO_WritePin(ADXL345_GPIO, ADXL345_SDA, GPIO_PIN_RESET)
#define SDA_1 HAL_GPIO_WritePin(ADXL345_GPIO, ADXL345_SDA, GPIO_PIN_SET)

#define ADXL345SDA HAL_GPIO_ReadPin(ADXL345_GPIO, ADXL345_SDA)



#define	SlaveAddress   0xA6	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
void Init_ADXL345(void);             //初始化ADXL345
void WriteDataLCM(unsigned char dataW);
void WriteCommandLCM(unsigned char CMD,unsigned char Attribc);
void DisplayOneChar(unsigned char X,unsigned char Y,unsigned char DData);
void conversion(unsigned int temp_data);
void  Single_Write_ADXL345(unsigned char REG_Address,unsigned char REG_data);   //单个写入数据
unsigned char Single_Read_ADXL345(unsigned char REG_Address);                   //单个读取内部寄存器数据
void  Multiple_ReadADXL345();                                  //连续的读取内部寄存器数据

void Delay5us();
void Delay5ms();
void ADXL345_Start();
void ADXL345_Stop();
void ADXL345_SendACK(unsigned char ack);
unsigned char  ADXL345_RecvACK();
void ADXL345_Sendbyte(unsigned char dat);
unsigned char ADXL345_Recvbyte();
void ADXL345_ReadPage();
void ADXL345_WritePage(); 



//int ADXL345_x=0;
//int ADXL345_y=0;
//int ADXL345_z=0;
		


//下面这个是调试用的，串口打印出来的，处理成角度值的方法下面有写



//void ADXL345_Uart()
//{   
//	
//			Uart1Data(0x30+BUF[0]/100%10);
//			Uart1Data(0x30+BUF[0]/10%10);
//			Uart1Data(0x30+BUF[0]%10);
//	
//			Uart1Data(0x30+BUF[1]/100%10);
//			Uart1Data(0x30+BUF[1]/10%10);
//			Uart1Data(0x30+BUF[1]%10);
//	
//			Uart1Data(0x30+BUF[2]/100%10);
//			Uart1Data(0x30+BUF[2]/10%10);
//			Uart1Data(0x30+BUF[2]%10);
//	
//			Uart1Data(0x30+BUF[3]/100%10);
//			Uart1Data(0x30+BUF[3]/10%10);
//			Uart1Data(0x30+BUF[3]%10);

//	
//			Uart1Data(0x30+BUF[4]/100%10);
//			Uart1Data(0x30+BUF[4]/10%10);
//			Uart1Data(0x30+BUF[4]%10);
//	
//			Uart1Data(0x30+BUF[5]/100%10);
//			Uart1Data(0x30+BUF[5]/10%10);
//			Uart1Data(0x30+BUF[5]%10);
//      Uart1DataByte("\r\n");
//		 
//		 
//		ADXL345_y=(BUF[3]<<8)+BUF[2];
//		if(ADXL345_y>=0) ADXL345_y=ADXL345_y*3.9;
//		else 			 ADXL345_y=ADXL345_y*-1*3.9; 
//	
//	   Uart1Data(0x30+ADXL345_y/10000%10);
//	   Uart1Data(0x30+ADXL345_y/1000%10);
//	   Uart1Data(0x30+ADXL345_y/100%10);
//	   Uart1Data(0x30+ADXL345_y/10%10);
//	   Uart1Data(0x30+ADXL345_y%10);
//	   Uart1DataByte("\r\n"); 

//	ADXL345_x=(BUF[1]<<8)+BUF[0];
//    if(ADXL345_x>=0) 
//	 {
//	   ADXL345_x=ADXL345_x*3.9;
//	   Uart1DataByte("+");
//	   Uart1Data(0x30+ADXL345_x/10000%10);
//	   Uart1Data(0x30+ADXL345_x/1000%10);
//	   Uart1Data(0x30+ADXL345_x/100%10);
//	   Uart1Data(0x30+ADXL345_x/10%10);
//	   Uart1Data(0x30+ADXL345_x%10);
//	 }
//	else 
//	 {
//	   ADXL345_x=ADXL345_x*-1*3.9;
//	   Uart1DataByte("-"); 
//	   Uart1Data(0x30+ADXL345_x/10000%10);
//	   Uart1Data(0x30+ADXL345_x/1000%10);
//	   Uart1Data(0x30+ADXL345_x/100%10);
//	   Uart1Data(0x30+ADXL345_x/10%10);
//	   Uart1Data(0x30+ADXL345_x%10);
//	 }			

//	ADXL345_y=(BUF[3]<<8)+BUF[2];
//    if(ADXL345_y>=0) 
//	 {
//	   ADXL345_y=ADXL345_y*3.9;
//	   Uart1DataByte("+");
//	   Uart1Data(0x30+ADXL345_y/10000%10);
//	   Uart1Data(0x30+ADXL345_y/1000%10);
//	   Uart1Data(0x30+ADXL345_y/100%10);
//	   Uart1Data(0x30+ADXL345_y/10%10);
//	   Uart1Data(0x30+ADXL345_y%10);
//	 }
//	else 
//	 {
//	   ADXL345_y=ADXL345_y*-1*3.9;
//	   Uart1DataByte("-"); 
//	   Uart1Data(0x30+ADXL345_y/10000%10);
//	   Uart1Data(0x30+ADXL345_y/1000%10);
//	   Uart1Data(0x30+ADXL345_y/100%10);
//	   Uart1Data(0x30+ADXL345_y/10%10);
//	   Uart1Data(0x30+ADXL345_y%10);
//	 }	



//	ADXL345_z=(BUF[5]<<8)+BUF[4];
//    if(ADXL345_z>=0) 
//	 {
//	   ADXL345_z=ADXL345_z*3.9;
//	   Uart1DataByte("+");
//	   Uart1Data(0x30+ADXL345_z/10000%10);
//	   Uart1Data(0x30+ADXL345_z/1000%10);
//	   Uart1Data(0x30+ADXL345_z/100%10);
//	   Uart1Data(0x30+ADXL345_z/10%10);
//	   Uart1Data(0x30+ADXL345_z%10);
//	 }
//	else 
//	 {
//	   ADXL345_z=ADXL345_z*-1*3.9;
//	   Uart1DataByte("-"); 
//	   Uart1Data(0x30+ADXL345_z/10000%10);
//	   Uart1Data(0x30+ADXL345_z/1000%10);
//	   Uart1Data(0x30+ADXL345_z/100%10);
//	   Uart1Data(0x30+ADXL345_z/10%10);
//	   Uart1Data(0x30+ADXL345_z%10);
//	 }	
//	 	   Uart1DataByte("\r\n"); 

//}


 




#endif 

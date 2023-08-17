#ifndef __ONEWIRE_DS18B20_H__
#define	__ONEWIRE_DS18B20_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* 类型定义 ------------------------------------------------------------------*/
/* 宏定义 -------------------------------------------------------------------*/
/***********************   DS18B20 连接引脚定义  **************************/
#define DS18B20_Dout_GPIO_CLK_ENABLE()              __HAL_RCC_GPIOB_CLK_ENABLE()
#define DS18B20_Dout_PORT                           GPIOB
#define DS18B20_Dout_PIN                            GPIO_PIN_15

/***********************   DS18B20 函数宏定义  ****************************/
#define DS18B20_Dout_LOW()                          HAL_GPIO_WritePin(DS18B20_Dout_PORT,DS18B20_Dout_PIN,GPIO_PIN_RESET) 
#define DS18B20_Dout_HIGH()                         HAL_GPIO_WritePin(DS18B20_Dout_PORT,DS18B20_Dout_PIN,GPIO_PIN_SET)
#define DS18B20_Data_IN()	                          HAL_GPIO_ReadPin(DS18B20_Dout_PORT,DS18B20_Dout_PIN)

/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
unsigned char DS18B20_Init(void);//初始化DS18B20
short DS18B20_Get_Temp(void);//获取温度
void DS18B20_Start(void);//开始温度转换
void DS18B20_Write_Byte(unsigned char dat);//写入一个字节
unsigned char DS18B20_Read_Byte(void);//读出一个字节
unsigned char DS18B20_Read_Bit(void);//读出一个位
unsigned char DS18B20_Check(void);//检测是否存在DS18B20
void DS18B20_Rst(void);//复位DS18B20  


#endif /* __ONEWIRE_DS18B20_H__ */
/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/

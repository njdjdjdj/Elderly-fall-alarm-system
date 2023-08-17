//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : LCD_ZK.H
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : 字库版 OLED SPI接口演示例程(STM32系列)
//              说明: 
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/
#define _LCD_ZK_H_
#ifdef _LCD_ZK_H_



/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1

//---> .C 文件还要修改时钟
#define OLED_sclk_Group  GPIOB
#define OLED_sclk_GPIO   GPIO_PIN_9
#define OLED_sid_Group   GPIOB
#define OLED_sid_GPIO    GPIO_PIN_8
#define OLED_rs_Group    GPIOB
#define OLED_rs_GPIO     GPIO_PIN_7
#define OLED_CS1_Group   GPIOB
#define OLED_CS1_GPIO    GPIO_PIN_6




#define OLED_CS_Group    GPIOB
#define OLED_CS_GPIO     GPIO_PIN_4
#define OLED_OUT_Group   GPIOB
#define OLED_OUT_GPIO    GPIO_PIN_5



//带参宏，可以像内联函数一样使用
#define lcd_cs1(a)	if (a)	\
					HAL_GPIO_WritePin(OLED_CS1_Group, OLED_CS1_GPIO, GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(OLED_CS1_Group,OLED_CS1_GPIO, GPIO_PIN_RESET)

#define lcd_rs(a)	if (a)	\
					HAL_GPIO_WritePin(OLED_rs_Group,OLED_rs_GPIO, GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(OLED_rs_Group,OLED_rs_GPIO, GPIO_PIN_RESET)


#define lcd_sid(a)	if (a)	\
					HAL_GPIO_WritePin(OLED_sid_Group,OLED_sid_GPIO, GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(OLED_sid_Group,OLED_sid_GPIO, GPIO_PIN_RESET)

#define lcd_sclk(a)	if (a)	\
					HAL_GPIO_WritePin(OLED_sclk_Group,OLED_sclk_GPIO, GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(OLED_sclk_Group,OLED_sclk_GPIO, GPIO_PIN_RESET)
#define Rom_CS(a)	if (a)	\
					HAL_GPIO_WritePin(OLED_CS_Group,OLED_CS_GPIO, GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(OLED_CS_Group,OLED_CS_GPIO, GPIO_PIN_RESET)

#define Rom_OUT(a)	if (a)	\
					HAL_GPIO_WritePin(OLED_OUT_Group,OLED_OUT_GPIO, GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(OLED_OUT_Group,OLED_OUT_GPIO, GPIO_PIN_RESET)


#define ROM_OUT    HAL_GPIO_ReadPin(OLED_OUT_Group,OLED_OUT_GPIO)

extern unsigned char const bmp1[];
extern unsigned char const jiong1[];
extern unsigned char const lei1[];


/*写指令到LCD模块*/
void transfer_command_lcd(int data1);   
/*写数据到LCD模块*/
void transfer_data_lcd(int data1);
/*延时*/
void delay(int n_ms);               
/*LCD模块初始化*/
void initial_lcd(void);
void lcd_address(unsigned char page,unsigned char column);
/*全屏清屏*/
void clear_screen(void);
/*显示128x64点阵图像*/
void display_128x64(const unsigned char *dp);
/*显示132x64点阵图像*/
//void display_132x64(unsigned char *dp);
/*显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标*/
void display_graphic_16x16(unsigned int page,unsigned int column,const unsigned char *dp);
/*显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标*/
void display_graphic_8x16(unsigned int page,unsigned char column,unsigned char *dp);
/*显示5*7点阵图像、ASCII, 或5x7点阵的自造字符、其他图标*/
void display_graphic_5x7(unsigned int page,unsigned char column,unsigned char *dp);
/****送指令到晶联讯字库IC***/
void send_command_to_ROM( unsigned char datu );
/****从晶联讯字库IC中取汉字或字符数据（1个字节）***/
static unsigned char get_data_from_ROM(void);
/*从相关地址（addrHigh：地址高字节,addrMid：地址中字节,addrLow：地址低字节）中连续读出DataLen个字节的数据到 pBuff的地址*/
/*连续读取*/
void get_n_bytes_data_from_ROM(unsigned char addrHigh,unsigned char addrMid,unsigned char addrLow,unsigned char *pBuff,unsigned char DataLen );
/******************************************************************/
void display_GB2312_string(unsigned char y,unsigned char x,unsigned char *text);
void display_string_5x7(unsigned char y,unsigned char x,unsigned char *text);

#endif

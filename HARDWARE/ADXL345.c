
#include "ADXL345.h"


	
extern unsigned char  BUF[8]; 


void ADXL_345_ALL_Int()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  ADXL345_GPIOCLK;
 
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADXL345_GPIO, ADXL345_SDA|ADXL345_SCL, GPIO_PIN_SET);

  /*Configure GPIO pins : PB10 PB11 */
  GPIO_InitStruct.Pin = ADXL345_SDA|ADXL345_SCL;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ADXL345_GPIO, &GPIO_InitStruct);
	
}

void ADXL345_SDA_Output()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  ADXL345_GPIOCLK;

  GPIO_InitStruct.Pin = ADXL345_SDA;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ADXL345_GPIO, &GPIO_InitStruct);
	

	
}
void ADXL345_SDA_Intput()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  ADXL345_GPIOCLK;
  /*Configure GPIO pins : PB10 PB11 */
  GPIO_InitStruct.Pin =  ADXL345_SDA;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed =GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ADXL345_GPIO, &GPIO_InitStruct);
}


/**************************************
延时5微秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数，注意时钟过快时需要修改
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5us()
{
	__nop();__nop();__nop();__nop(); 
	__nop();__nop();__nop();__nop(); 
	__nop();__nop();__nop();__nop(); 
	__nop();__nop();__nop();__nop(); 

}

/**************************************
延时5毫秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5ms()
{
   HAL_Delay(3);
}

/**************************************
起始信号
**************************************/
void ADXL345_Start()
{
  	SDA_1;                    //拉高数据线
    SCL_1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA_0;                    //产生下降沿
    Delay5us();                 //延时
    SCL_0;                    //拉低时钟线
	
}

/**************************************
停止信号
**************************************/
void ADXL345_Stop()
{

    SDA_0;                    //拉低数据线
    SCL_1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA_1;                    //产生上升沿
    Delay5us();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(unsigned char ack)
{
    if(ack==1) SDA_1;
		else       SDA_0;
//	SDA = ack;                  //写应答信号
    SCL_1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL_0;                    //拉低时钟线
    Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
unsigned char ADXL345_RecvACK()
{

  	unsigned char CY_Dat=0;
   	SCL_1;                    //拉高时钟线
    Delay5us();                 //延时
	  if(ADXL345SDA==1) CY_Dat=1;
	  else   CY_Dat=0;
//    CY_Dat = SDA;                   //读应答信号
	
    SCL_0;                    //拉低时钟线
    Delay5us();                 //延时
    ADXL345_SDA_Output();
	return CY_Dat;
	  
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void ADXL345_Sendbyte(unsigned char dat)
{
    unsigned char i;
    ADXL345_SDA_Output();//SDA为输出
    for (i=0; i<8; i++)         //8位计数器
    {
			  if((dat&0x80)==0x80) SDA_1;
				else 							   SDA_0;
   			dat <<= 1;              //移出数据的最高位
  //    SDA = CY;               //送数据口
        SCL_1;                //拉高时钟线
        Delay5us();             //延时
        SCL_0;                //拉低时钟线
        Delay5us();             //延时
    }
		 ADXL345_SDA_Intput();
     ADXL345_RecvACK();
     ADXL345_SDA_Output();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
unsigned char ADXL345_Recvbyte()
{
    unsigned char i;
    unsigned char dat = 0;
    SDA_1;                    //使能内部上拉,准备读取数据,
    ADXL345_SDA_Intput();
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL_1;                //拉高时钟线
        Delay5us();             //延时
			  if(ADXL345SDA==1) dat |= 0x01;     //读数据  
				else              dat |= 0x00; 
        SCL_0;                //拉低时钟线
        Delay5us();             //延时
    }
		ADXL345_SDA_Output();
    return dat;
		    
}

//******单字节写入*******************************************

void Single_Write_ADXL345(unsigned char REG_Address,unsigned char REG_data)
{
    ADXL345_Start();                  //起始信号
    ADXL345_Sendbyte(SlaveAddress);   //发送设备地址+写信号
    ADXL345_Sendbyte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
    ADXL345_Sendbyte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
    ADXL345_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
unsigned char Single_Read_ADXL345(unsigned char REG_Address)
{   unsigned char REG_data;
		ADXL345_Start();                          //起始信号
		ADXL345_Sendbyte(SlaveAddress);           //发送设备地址+写信号
		ADXL345_Sendbyte(REG_Address);            //发送存储单元地址，从0开始	
		ADXL345_Start();                          //起始信号
		ADXL345_Sendbyte(SlaveAddress+1);         //发送设备地址+读信号
		REG_data=ADXL345_Recvbyte();              //读出寄存器数据
		ADXL345_SendACK(1);   
		ADXL345_Stop();                           //停止信号
		return REG_data; 
}
//*********************************************************
//
//连续读出ADXL345内部加速度数据，地址范围0x32~0x37
//
//*********************************************************
void Multiple_ReadADXL345()
{   unsigned char i;
    ADXL345_Start();                          //起始信号
    ADXL345_Sendbyte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_Sendbyte(0x32);                   //发送存储单元地址，从0x32开始	
    ADXL345_Start();                          //起始信号
    ADXL345_Sendbyte(SlaveAddress+1);         //发送设备地址+读信号
	 for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = ADXL345_Recvbyte();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           ADXL345_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          ADXL345_SendACK(0);                //回应ACK
       }
   }
    ADXL345_Stop();                          //停止信号
    Delay5ms();
}

//*****************************************************************

//初始化ADXL345，根据需要请参考pdf进行修改************************
void Init_ADXL345()
{
   
	 ADXL_345_ALL_Int();
	 HAL_Delay(500);
	 Single_Write_ADXL345(0x31,0x0B);   //测量范围,正负16g，13位模式
   Single_Write_ADXL345(0x2C,0x08);   //速率设定为12.5 参考pdf13页
   Single_Write_ADXL345(0x2D,0x08);   //选择电源模式   参考pdf24页
   Single_Write_ADXL345(0x2E,0x80);   //使能 DATA_READY 中断
   Single_Write_ADXL345(0x1E,0x00);   //X 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x1F,0x00);   //Y 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x20,0x00);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}































#include "FLSH.h"


void Write_flsh_byte(uint32_t EEPROM_ADD, uint32_t EEPROM_Data)
{
	//1、解锁FLASH
	HAL_FLASH_Unlock();
	//2、擦除FLASH
	//初始化FLASH_EraseInitTypeDef
	FLASH_EraseInitTypeDef f;
	f.TypeErase = FLASH_TYPEERASE_PAGES;
	f.PageAddress = EEPROM_ADD;
	f.NbPages = 1;
	//设置PageError
	uint32_t PageError = 0;
	//调用擦除函数
	HAL_FLASHEx_Erase(&f, &PageError);
	//3、对FLASH烧写
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, EEPROM_ADD, EEPROM_Data);
	//4、锁住FLASH
	HAL_FLASH_Lock();
}

//FLASH读取数据测试
uint32_t readFlash(uint32_t EEPROM_ADD)
{
	uint32_t temp = *(__IO uint32_t*)(EEPROM_ADD);
	return temp;
}
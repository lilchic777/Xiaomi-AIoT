#include "i2c.h"
#include "s1.h"
#include "systick.h"

uint8_t color = 0;
uint8_t output = 0;
uint8_t keyvalue[6];
i2c_addr_def s1_key_addr;

void S1_HT16K33_Init(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_cmd_write(i2c_periph,i2c_addr,0x21);
	//系统设置寄存器开启振荡器（正常工作模式）
}

void S1_HT16K33_KeyScan(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_read(i2c_periph,i2c_addr,0x40,keyvalue,6);
	//在HT16K33映射矩阵中KS0(COM1)和K1tK8的交叉点是地址0x40的寄存器管理
	//单次页读取按键扫描操作会进行从0x40至0x45的连续读取(对应的COM也会从1往3方向读取)
}

void S1( void ){
	S1_HT16K33_KeyScan(s1_key_addr.periph,s1_key_addr.addr);
				//SW1
	if(keyvalue[0]&0x01)
	{
		delay_1ms(20);
		if (keyvalue[0]&0x01){
			output = 1;
		}else{
			output = 0;
		}
		
	}
	//SW2
	else if(keyvalue[2]&0x01)
	{
		delay_1ms(20);
		if (keyvalue[2]&0x01){
			output = 2;
		}else{
			output = 0;
		}
		
	}
	//SW3
	else if(keyvalue[4]&0x01)
	{
		delay_1ms(20);
		if (keyvalue[4]&0x01){
			output = 3;
		}else{
			output = 0;
		}
		
	}
	//SW4
	else if(keyvalue[0]&0x02)
	{
		delay_1ms(20);
		if (keyvalue[0]&0x02){
			output = 4;
		}else{
			output = 0;
		}
	}
	//SW5
	else if(keyvalue[2]&0x02)
	{
		delay_1ms(20);
		if (keyvalue[2]&0x02){
			output = 5;
		}else{
			output = 0;
		}
	}
	//SW6
	else if(keyvalue[4]&0x02)
	{
		delay_1ms(20);
		if (keyvalue[4]&0x02){
			output = 6;
		}else{
			output = 0;
		}
	}
	//SW7
	else if(keyvalue[0]&0x04)
	{
		delay_1ms(20);
		if (keyvalue[0]&0x04){
			output = 7;
		}else{
			output = 0;
		}
	}
	//SW8
	else if(keyvalue[2]&0x04)
	{
		delay_1ms(20);
		if (keyvalue[2]&0x04){
			output = 8;
		}else{
			output = 0;
		}
	}
	//SW9
	else if(keyvalue[4]&0x04)
	{
		delay_1ms(20);
		if (keyvalue[4]&0x04){
			output = 9;
		}else{
			output = 0;
		}
	}
	//SW10
	else if(keyvalue[0]&0x08)
	{
		delay_1ms(20);
		if (keyvalue[0]&0x08){
			output = 10;
		}else{
			output = 0;
		}
	}
	//SW11
	else if(keyvalue[2]&0x08)
	{
		delay_1ms(20);
		if (keyvalue[2]&0x08){
			output = 11;
		}else{
			output = 0;
		}
	}
	//SW12
	else if(keyvalue[4]&0x08)
	{
		delay_1ms(20);
		if (keyvalue[4]&0x08){
			output = 12;
		}else{
			output = 0;
		}
	}
	
}

void S1_I2C_ADDR_Init(void)
{
	uint8_t i;

	//S1 KEY I2C address init
	//poll I2C0,Horizontal
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,HT16K33_ADDRESS_S1+i*2))
		{
			s1_key_addr.periph = I2C0;
			s1_key_addr.addr = HT16K33_ADDRESS_S1+i*2;	
			s1_key_addr.flag = 1;
			break;
		}	
	}
	//address not read
	if(s1_key_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,HT16K33_ADDRESS_S1+i*2))
			{
				s1_key_addr.periph = I2C1;
				s1_key_addr.addr = HT16K33_ADDRESS_S1+i*2;	
				s1_key_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
	if(s1_key_addr.flag)
	{
		S1_HT16K33_Init(s1_key_addr.periph,s1_key_addr.addr);
	}

}



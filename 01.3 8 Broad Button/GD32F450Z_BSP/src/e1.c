#include "i2c.h"
#include "e1.h"


//0-9
const uint8_t disdata[10][2] ={{0xF8,0x01},//0
															 {0x30,0x00},//1
															 {0xD8,0x02},//2
															 {0x78,0x02},//3
															 {0x30,0x03},//4
															 {0x68,0x03},//5
															 {0xE8,0x03},//6
															 {0x38,0x00},//7
															 {0xF8,0x03},//8
															 {0x78,0x03},};//9

void E1_HT16K33_Init(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_cmd_write(i2c_periph,i2c_addr,0x21);
	//系统设置寄存器开启振荡器（正常工作模式）
	E1_HT16K33_display_off(i2c_periph,i2c_addr);
}

void E1_PCA9685PW_Init(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_byte_write(i2c_periph,i2c_addr,0x00,0x00);
	//模式0
	E1_PCA9685PW_off(i2c_periph,i2c_addr);
	//关闭
}

void E1_HT16K33_display_off(uint32_t i2c_periph,uint8_t i2c_addr)
{
	i2c_byte_write(i2c_periph,i2c_addr,0x02,0x00);//COM1--ROW0tROW7
	i2c_byte_write(i2c_periph,i2c_addr,0x03,0x00);//COM1--ROW8tROW15
	//第1位
	i2c_byte_write(i2c_periph,i2c_addr,0x04,0x00);//COM2--ROW0tROW7
	i2c_byte_write(i2c_periph,i2c_addr,0x05,0x00);//COM2--ROW8tROW15
	//第2位
	i2c_byte_write(i2c_periph,i2c_addr,0x06,0x00);//COM3--ROW0tROW7
	i2c_byte_write(i2c_periph,i2c_addr,0x07,0x00);//COM3--ROW8tROW15
	//第3位
	i2c_byte_write(i2c_periph,i2c_addr,0x08,0x00);//COM4--ROW0tROW7
	i2c_byte_write(i2c_periph,i2c_addr,0x09,0x00);//COM4--ROW8tROW15
	//第4位
	//RAM地址与矩阵按键对应的COMx和ROWx坐标清零(查看ht16k33的映射图)
	i2c_cmd_write(i2c_periph,i2c_addr,0x81);
	//定义显示状态与闪烁频率(0.5/1/2Hz)
}

void E1_PCA9685PW_off(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_byte_write(i2c_periph,i2c_addr,ALL_LED_ON_L,0);
	//
	i2c_byte_write(i2c_periph,i2c_addr,ALL_LED_ON_H,0);
	//
	i2c_byte_write(i2c_periph,i2c_addr,ALL_LED_OFF_L,0);
	//
	i2c_byte_write(i2c_periph,i2c_addr,ALL_LED_OFF_H,0x10);
	//
}

void setPWM(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num, uint16_t on, uint16_t off) 
{
    i2c_byte_write(i2c_periph,i2c_addr,LED0_ON_L+4*num,on);
    i2c_byte_write(i2c_periph,i2c_addr,LED0_ON_H+4*num,on>>8);
    i2c_byte_write(i2c_periph,i2c_addr,LED0_OFF_L+4*num,off);
    i2c_byte_write(i2c_periph,i2c_addr,LED0_OFF_H+4*num,off>>8);
}

void PCA9685_rgb_led_control(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num)
{	
		
		switch(num)
		{
		case 0:
			E1_PCA9685PW_off(i2c_periph,i2c_addr);
			break;
		case 1://red
			setPWM(i2c_periph,i2c_addr,0,0x0000,0x0010);
			//0x06+4*0//0x0000
			//0x07+4*0//0x0000>>8
			//0x08+4*0//0x0010
			//0x09+4*0//0x0010>>8
			setPWM(i2c_periph,i2c_addr,1,0x0199,0x0C00);
			//0x06+4*1//0x0199
			//0x07+4*1//0x0199>>8
			//0x08+4*1//0x0C00
			//0x09+4*1//0x0C00>>8
			setPWM(i2c_periph,i2c_addr,2,0x0000,0x0010);
			//0x06+4*2//0x0000
			//0x07+4*2//0x0000>>8
			//0x08+4*2//0x0010
			//0x09+4*2//0x0010>>8
			break;
		case 2://yellow
			setPWM(i2c_periph,i2c_addr,0,0x0199,0x0800);
			//0x06+4*0//0x0199
			//0x07+4*0//0x0199>>8
			//0x08+4*0//0x0800
			//0x09+4*0//0x0800>>8
			setPWM(i2c_periph,i2c_addr,1,0x0199,0x0800);
			//0x06+4*1//0x0199
			//0x07+4*1//0x0199>>8
			//0x08+4*1//0x0800
			//0x09+4*1//0x0800>>8
			setPWM(i2c_periph,i2c_addr,2,0x0000,0x0010);
			//0x06+4*2//0x0000
			//0x07+4*2//0x0000>>8
			//0x08+4*2//0x0010
			//0x09+4*2//0x0010>>8
			break;		
		case 3://blue
			setPWM(i2c_periph,i2c_addr,0,0x0000,0x0010);
			//0x06+4*0//0x0000
			//0x07+4*0//0x0000>>8
			//0x08+4*0//0x0010
			//0x09+4*0//0x0010>>8
			setPWM(i2c_periph,i2c_addr,1,0x0000,0x0010);
			//0x06+4*1//0x0000
			//0x07+4*1//0x0000>>8
			//0x08+4*1//0x0010
			//0x09+4*1//0x0010>>8
			setPWM(i2c_periph,i2c_addr,2,0x0199,0x0C00);
			//0x06+4*2//0x0199
			//0x07+4*2//0x0199>>8
			//0x08+4*2//0x0C00
			//0x09+4*2//0x0C00>>8
			break;  
		case 4:
			setPWM(i2c_periph,i2c_addr,0,0x0000,0x0010);
			setPWM(i2c_periph,i2c_addr,1,0x0199,0x0220);
			setPWM(i2c_periph,i2c_addr,2,0x0000,0x0010);
			break; 
		case 5:
			setPWM(i2c_periph,i2c_addr,0,0x0199,0x0220);
			setPWM(i2c_periph,i2c_addr,1,0x0000,0x0010);
			setPWM(i2c_periph,i2c_addr,2,0x0000,0x0010);
			break; 
		case 6:
			setPWM(i2c_periph,i2c_addr,0,0x0000,0x0010);
			setPWM(i2c_periph,i2c_addr,1,0x0000,0x0010);
			setPWM(i2c_periph,i2c_addr,2,0x0199,0x0220);
			break; 
		case 7:
		default:
			E1_PCA9685PW_off(i2c_periph,i2c_addr);
			break;
		}
}

void E1_HT16K33_display_data(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t bit,uint8_t data)
{
		switch(bit)
		{
			case 1:
				i2c_byte_write(i2c_periph,i2c_addr,0x02,disdata[data][0]);//edcb axxx
				i2c_byte_write(i2c_periph,i2c_addr,0x03,disdata[data][1]);//xxxx xpgf
			break;
			
			case 2:
				i2c_byte_write(i2c_periph,i2c_addr,0x04,disdata[data][0]);//edcb axxx
				i2c_byte_write(i2c_periph,i2c_addr,0x05,disdata[data][1]);//xxxx xpgf
			break;
			
			case 3:
				i2c_byte_write(i2c_periph,i2c_addr,0x06,disdata[data][0]);//edcb axxx
				i2c_byte_write(i2c_periph,i2c_addr,0x07,disdata[data][1]);//xxxx xpgf
			break;
			
			case 4:
				i2c_byte_write(i2c_periph,i2c_addr,0x08,disdata[data][0]);//edcb axxx
				i2c_byte_write(i2c_periph,i2c_addr,0x09,disdata[data][1]);//xxxx xpgf
			break;
			
		}
		i2c_cmd_write(i2c_periph,i2c_addr,0x21);//开启系统振荡器(正常工作模式)
}

void E1_HT16K33_show( uint8_t b1,uint8_t d1,uint8_t b2,uint8_t d2,uint8_t b3,uint8_t d3,uint8_t b4,uint8_t d4 ){
	E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,b1,d1);
	E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,b2,d2);
	E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,b3,d3);
	E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,b4,d4);
}

void E1_HT16K33_clean( void ){
	E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,11);
	E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,11);
	E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,11);
	E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,11);
}


void E1_4NLED_ADDR_Init( void ){
	uint8_t i;
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,HT16K33_ADDRESS_E1+i*2))//对E1所对应的从机地址进行轮询(DIP开关可以改变从机地址，所以预留了四个偏移从机地址)
		{
			e1_nixie_tube_addr.periph = I2C0;
			e1_nixie_tube_addr.addr = HT16K33_ADDRESS_E1+i*2;//保存能够对应的从机地址
			e1_nixie_tube_addr.flag = 1;//自定义标志位置1
			break;
		}	
	}
	//address not read
	if(e1_nixie_tube_addr.flag != 1)//标志位未置1，进入轮询
	{	
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,HT16K33_ADDRESS_E1+i*2))
			{
				e1_nixie_tube_addr.periph = I2C1;
				e1_nixie_tube_addr.addr = HT16K33_ADDRESS_E1+i*2;
				e1_nixie_tube_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
	if(e1_nixie_tube_addr.flag)//满足标志位置1，使用保存的从机地址对i2c设备进行初始化通信
	{
		// init E1 nixie tube
		E1_HT16K33_Init(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr);//0x21在芯片手册上被描述为系统设置寄存器(20H)中的开启系统模式
	}
}

void E1_3LED_ADDR_Init( void ){	//PCA9685PW
	uint8_t i;
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,PCA9685PW_ADDRESS_E1+i*2))//对E1所对应的从机地址进行轮询(DIP开关可以改变从机地址，所以预留了四个偏移从机地址)
		{
			e1_rgb_led_addr.periph = I2C0;
			e1_rgb_led_addr.addr = PCA9685PW_ADDRESS_E1+i*2;//保存能够对应的从机地址
			e1_rgb_led_addr.flag = 1;//自定义标志位置1
			break;
		}	
	}
	//address not read
	if(e1_rgb_led_addr.flag != 1)//标志位未置1，进入轮询
	{	
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,PCA9685PW_ADDRESS_E1+i*2))
			{
				e1_rgb_led_addr.periph = I2C1;
				e1_rgb_led_addr.addr = PCA9685PW_ADDRESS_E1+i*2;
				e1_rgb_led_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
	if(e1_rgb_led_addr.flag)//满足标志位置1，使用保存的从机地址对i2c设备进行初始化通信
	{
		// init E1 RG
		E1_PCA9685PW_Init(e1_rgb_led_addr.periph, e1_rgb_led_addr.addr);
	}
}








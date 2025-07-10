#include "gd32f4xx.h"
#include "s2.h"
#include "i2c.h"
#include "delay.h"

i2c_addr_def s2_light_addr;
i2c_addr_def s2_gryo_addr;
i2c_addr_def s2_temp_addr;

uint8_t lightval[2];
uint8_t tempHumid[6];
uint16_t lightval_full;
float lightval_;
uint64_t tempHumid_;
uint16_t temp;
uint16_t temp_;
uint16_t humid;
uint16_t humid_;
uint16_t tp;
uint16_t accRes;
float angRes;

uint8_t data[14];

int16_t x_acc_;
int16_t y_acc_;
int16_t z_acc_;
int16_t x_ang_;
int16_t y_ang_;
int16_t z_ang_;
float ang_x;
float ang_y;
float ang_z;
float acc_x;
float acc_y;
float acc_z;

void S2_Light_Init(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_cmd_write(i2c_periph,i2c_addr,0x01);
	//上电
}

void S2_Light_OneTime_Hires(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_cmd_write(i2c_periph,i2c_addr,0x20);
	i2c_read(i2c_periph,i2c_addr,Sensor_Light_ADDR,lightval,2);
	lightval_full = (lightval[0] << 8) + lightval[1];
}

void S2_Light_OneTime_Lores(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_cmd_write(i2c_periph,i2c_addr,0x23);
	i2c_read(i2c_periph,i2c_addr,Sensor_Light_ADDR,lightval,2);
	lightval_full = (lightval[0] << 8) + lightval[1];
}

void S2_Light_Continous_Hires(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_cmd_write(i2c_periph,i2c_addr,0x10);
	i2c_read(i2c_periph,i2c_addr,Sensor_Light_ADDR,lightval,2);
	lightval_full = (lightval[0] << 8) + lightval[1];
}

void S2_Light_Continous_Lores(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_cmd_write(i2c_periph,i2c_addr,0x13);
	i2c_read(i2c_periph,i2c_addr,Sensor_Light_ADDR,lightval,2);
	lightval_full = (lightval[0] << 8) + lightval[1];
}

void getLightval( void ){
	S2_Light_OneTime_Hires(s2_light_addr.periph,s2_light_addr.addr);
	lightval_ = lightval_full / 1.2;
}

void S2_TempHumid_Init(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_byte_write(i2c_periph,i2c_addr,0x30,0xA2);
}

void S2_TempHumid_Single_Shot(uint32_t i2c_periph, uint8_t i2c_addr){
	S2_TempHumid_Init(i2c_periph,i2c_addr);
	delay(1000);
	i2c_byte_write(i2c_periph,i2c_addr,0x2C,0x0D);
	delay(1000);
	i2c_read(i2c_periph,i2c_addr,Sensor_TempHumid_ADDR,tempHumid,6);
	//获取
	temp = (tempHumid[0] << 8) + tempHumid[1];
	temp_ = temp * 175/65535 - 45;
	
	humid = (tempHumid[3] << 8) + tempHumid[4];
	humid_ = humid * 100/65535;
}

void S2_Gryo_Init(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_byte_write(i2c_periph,i2c_addr,0x6B,0x80);
	delay(100);
}

void S2_Gryo_Settings(uint32_t i2c_periph,uint8_t i2c_addr){
	i2c_byte_write(i2c_periph,i2c_addr,0x6B,0x01);
	//复位并睡眠
	delay(100);
	i2c_byte_write(i2c_periph,i2c_addr,0x19,0x00);
	//输出速率为内部采样率
	i2c_byte_write(i2c_periph,i2c_addr,0x1B,0x18);
	//设置陀螺仪量程
	i2c_byte_write(i2c_periph,i2c_addr,0x1C,0x18);
	//设置加速度计量程
	i2c_byte_write(i2c_periph,i2c_addr,0x1A,0x04);
	//陀螺仪低通滤波
	i2c_byte_write(i2c_periph,i2c_addr,0x1D,0x04);
	//加速度计低通滤波
	i2c_byte_write(i2c_periph,i2c_addr,0x6C,0x00);
	//使能六轴
	i2c_byte_write(i2c_periph,i2c_addr,0x1E,0x00);
	//不使能低功耗
	i2c_byte_write(i2c_periph,i2c_addr,0x23,0x00);
	//关闭FIFO
}

/*********************************************************************************************
函数名:      s2_icm20608_gyro_scaleget
功能:        获取陀螺仪的分辨率
入口参数:    i2c_periph:i2c口   i2c_addr:i2c地址
出口参数:    无
返回值：     获取到的分辨率
作者：       ZZZ
日期:        2023/4/3
**********************************************************************************************/
float s2_icm20608_gyro_scaleget(uint32_t i2c_periph,uint8_t i2c_addr)
{
	uint8_t data;
	float gyroscale;

	i2c_delay_read(i2c_periph,i2c_addr,0x1B,&data,1);	

	data = (data >> 3) & 0X3;//读取量程寄存器值
	switch(data) 
	{
		case  0: 				//±250dps
			gyroscale = 131;	//分辨率gyroscale = ADC数据（65536）/量程（250*2）=131
			break;
		case 1:					//±500dps
			gyroscale = 65.5;	//分辨率gyroscale = ADC数据（65536）/量程（500*2）=65.5
			break;
		case 2:					//±1000dps
			gyroscale = 32.8;	//分辨率gyroscale = ADC数据（65536）/量程（1000*2）=32.8
			break;
		case 3:					//±2000dps
			gyroscale = 16.4;	//分辨率gyroscale = ADC数据（65536）/量程（2000*2）=16.4
			break;
	}
	return gyroscale;
}




/*********************************************************************************************
函数名:      s2_icm20608_accel_scaleget
功能:        获取加速度计的分辨率
入口参数:    i2c_periph:i2c口   i2c_addr:i2c地址
出口参数:    无
返回值：     获取到的分辨率
作者：       ZZZ
日期:        2023/4/3
**********************************************************************************************/
uint16_t s2_icm20608_accel_scaleget(uint32_t i2c_periph,uint8_t i2c_addr)
{
	uint8_t  data;
	uint16_t accelscale;
	
	i2c_delay_read(i2c_periph,i2c_addr,0x1C,&data,1);
	data = (data >> 3) & 0X3;
	switch(data) 
	{
			case 0: 
				accelscale = 16384;		//分辨率accelscale = ADC数据（65536）/量程（2*2）= 16384
				break;
			case 1:
				accelscale = 8192;		//分辨率accelscale = ADC数据（65536）/量程（4*2）= 8192
				break;
			case 2:
				accelscale = 4096;		//分辨率accelscale = ADC数据（65536）/量程（8*2）= 4096
				break;
			case 3:
				accelscale = 2048;		//分辨率accelscale = ADC数据（65536）/量程（16*2）= 2048
				break;
	}
	return accelscale;
}

void getAccAng( void ){
	accRes = s2_icm20608_accel_scaleget(s2_gryo_addr.periph,s2_gryo_addr.addr);
	angRes = s2_icm20608_gyro_scaleget(s2_gryo_addr.periph,s2_gryo_addr.addr);
	i2c_delay_read(s2_gryo_addr.periph,s2_gryo_addr.addr,0x3B,data,14);
	
	x_acc_ = ((data[0] << 8) | data[1]);
	y_acc_ = ((data[2] << 8) | data[3]);
	z_acc_ = ((data[4] << 8) | data[5]);
	tp 		 = ((data[6] << 8) | data[7]);
	x_ang_ = ((data[8] << 8) | data[9]);
	y_ang_ = ((data[10] << 8) | data[11]);
	z_ang_ = ((data[12] << 8) | data[13]);
	
	ang_x = (float)x_ang_ / angRes;
	ang_y = (float)y_ang_ / angRes;
	ang_z = (float)z_ang_ / angRes;
	
	acc_x = (float)x_acc_ / accRes;
	acc_y = (float)y_acc_ / accRes;
	acc_z = (float)z_acc_ / accRes;

	
}



void S2_Light_ADDR_Init( void ){
	uint8_t i;
	for(i=0;i<4;i++){
		if(i2c_addr_poll(I2C0,Sensor_Light_ADDR + i*2)){
			s2_light_addr.periph = I2C0;
			s2_light_addr.addr = Sensor_Light_ADDR + i*2;
			s2_light_addr.flag = 1;
		}
	}
	
	if(s2_light_addr.flag != 1)
	{			
		for(i=0;i<4;i++){
			if(i2c_addr_poll(I2C0,Sensor_Light_ADDR + i*2)){
			s2_light_addr.periph = I2C0;
			s2_light_addr.addr = Sensor_Light_ADDR + i*2;
			s2_light_addr.flag = 1;
			}
		}
	}
	
	if(s2_light_addr.flag)
	{
		S2_Light_Init(s2_light_addr.periph, s2_light_addr.addr);
	}
}

void S2_TempHumid_ADDR_Init( void ){
	uint8_t i;
	for(i=0;i<4;i++){
		if(i2c_addr_poll(I2C0,Sensor_TempHumid_ADDR + i*2)){
			s2_temp_addr.periph = I2C0;
			s2_temp_addr.addr = Sensor_TempHumid_ADDR + i*2;
			s2_temp_addr.flag = 1;
		}
	}
	
	if(s2_temp_addr.flag != 1)
	{			
		for(i=0;i<4;i++){
			if(i2c_addr_poll(I2C0,Sensor_TempHumid_ADDR + i*2)){
			s2_temp_addr.periph = I2C0;
			s2_temp_addr.addr = Sensor_TempHumid_ADDR + i*2;
			s2_temp_addr.flag = 1;
			}
		}
	}
	
	if(s2_temp_addr.flag)
	{
		S2_TempHumid_Init(s2_temp_addr.periph,s2_temp_addr.addr);
	}
}

void S2_Gryo_ADDR_Init( void ){
	uint8_t i;
	for(i=0;i<4;i++){
		if(i2c_addr_poll(I2C0,Sensor_Gyro_ADDR + i*2)){
			s2_gryo_addr.periph = I2C0;
			s2_gryo_addr.addr = Sensor_Gyro_ADDR + i*2;
			s2_gryo_addr.flag = 1;
		}
	}
	
	if(s2_gryo_addr.flag != 1)
	{			
		for(i=0;i<4;i++){
			if(i2c_addr_poll(I2C0,Sensor_Gyro_ADDR + i*2)){
			s2_gryo_addr.periph = I2C0;
			s2_gryo_addr.addr = Sensor_Gyro_ADDR + i*2;
			s2_gryo_addr.flag = 1;
			}
		}
	}
	
	if(s2_gryo_addr.flag)
	{
		S2_Gryo_Init(s2_gryo_addr.periph,s2_gryo_addr.addr);
	}
}








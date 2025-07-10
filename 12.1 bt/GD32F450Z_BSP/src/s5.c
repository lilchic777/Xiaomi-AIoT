#include "gd32f4xx.h"
#include "s5.h"
#include "i2c.h"

i2c_addr_def s5_nfc_addr;
uint8_t fifo_buffer;

void S5_NFC_Init( uint32_t i2c_periph, uint8_t i2c_addr ){
	i2c_byte_write(i2c_periph,i2c_addr,0x01,0x0F);
	//��ʼ��
}

void S5_NFC_Rec( uint32_t i2c_periph, uint8_t i2c_addr ){
	i2c_byte_write(i2c_periph,i2c_addr,0x01,0x08);
	//Receive
	i2c_read(i2c_periph,i2c_addr,0x09,&fifo_buffer,1);
	//FIFO
}

void S5_NFC_Settings(uint32_t i2c_periph,uint8_t i2c_addr){
	i2c_byte_write(i2c_periph,i2c_addr,0x11,0x3D);
	//���ò���ģʽ
	i2c_byte_write(i2c_periph,i2c_addr,0x2D,0x1E);
	//���ö�ʱ��LOAD�߰�λ
	i2c_byte_write(i2c_periph,i2c_addr,0x2C,0x00);
	//���ö�ʱ��LOAD�Ͱ�λ
	i2c_byte_write(i2c_periph,i2c_addr,0x2A,0x8D);
	//���ö�ʱ��������������Prescale����λ
	i2c_byte_write(i2c_periph,i2c_addr,0x2B,0x3E);
	//���ö�ʱ��Prescale�Ͱ�λ
}

void S5_NFC_ADDR_Init( void ){
	uint8_t i;
	
	for(i=0;i<4;i++){
		if(i2c_addr_poll(I2C0, S5_NFC_ADDR + i*2)){
			s5_nfc_addr.periph = I2C0;
			s5_nfc_addr.addr = S5_NFC_ADDR + i*2;
			s5_nfc_addr.flag = 1;
		}
	}
	
	if(s5_nfc_addr.flag != 1){
		for(i=0;i<4;i++){
			if(i2c_addr_poll(I2C0, S5_NFC_ADDR + i*2)){
				s5_nfc_addr.periph = I2C0;
				s5_nfc_addr.addr = S5_NFC_ADDR + i*2;
				s5_nfc_addr.flag = 1;
			}
		}
	}
	
	if(s5_nfc_addr.flag){
		S5_NFC_Init(s5_nfc_addr.periph,s5_nfc_addr.addr);
	}
}




/*************************************************************************************************************
����:     ����sw1������E1�Ͻ�������ɫ�Ʋ�ͣ�仯��ɫ������sw2��ť,E1�Ͻ���ơ�
�汾:     2023-5-17 V1.0
�޸ļ�¼: ��
����:     ZZZ
*************************************************************************************************************/
#include "gd32f4xx.h"
#include "led.h"
#include "i2c.h"
#include "delay.h"
#include "e1.h"
#include "s1.h"



void UserInit( void );


void UserInit( void ){
	i2c0_gpio_config();
	i2c0_config();
	
	i2c1_gpio_config();
	i2c1_config();

	S1_I2C_ADDR_Init();
	E1_I2C_3LED_ADDR_Init();

}

int main( void ){

	UserInit();
	while(1){
		S1();
		delay(1000);
		if (output == 1){
			for(int i=0;i<6;i++){
				PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,i);
				delay(2000);
				if(i>=5)
					break;
			}	
			output = 0;
		}
		else if(output == 2){
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
			output = 0;
		}


	}
	
}









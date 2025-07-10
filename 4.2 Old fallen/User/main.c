/*************************************************************************************************************
����:     ���¸�λ��������������ܵ��ĸ�λ�÷ֱ��Ӧ��ǰ���ң���ʱ�����ᴫ������ģ�����ˣ�
					�����ᴫ������⵽��ǰ�㵹ʱ����ģ���⵽������ǰˤ�������ڵڶ�λ��ʾ����1��
�汾:     2023-5-17 V1.0
�޸ļ�¼: ��
����:     ZZZ
*************************************************************************************************************/
#include "gd32f4xx.h"
#include "s2.h"
#include "e1.h"
#include "led.h"
#include "delay.h"

uint8_t state;

void UserInit( void );


void UserInit( void ){
	i2c0_gpio_config();
	i2c0_config();
	
	i2c1_gpio_config();
	i2c1_config();
	
	LED_Init();

	E1_I2C_ADDR_Init();
	E1_I2C_1_ADDR_Init();
	S2_Gryo_ADDR_Init();
	S2_Gryo_Settings(s2_gryo_addr.periph,s2_gryo_addr.addr);

}

int main( void ){

	UserInit();
	while(1){

		getAccAng();
		delay(500);
		if(acc_x < 0.2 && acc_x > -0.2)
		{
			if(acc_y <= 0.2 && acc_y > -0.2)//ƽ��״̬
				state = 9;
			if(acc_y <= -0.2)//����б
				state = 11;
			if(acc_y > 0.2)//����б
				state = 12;
		}
		else if(acc_y < 0.2 && acc_y > -0.2)
		{
			if(acc_x <= 0.2 && acc_x >= -0.2)//ƽ��״̬
				state = 9;
			if(acc_x < -0.2)//ǰ��б
				state = 13;
			if(acc_x > 0.2)//����б
				state = 14;
		}
		else if(acc_x <= -0.2)
		{
			if(acc_y <= -0.2)//��ǰ��б
				state = 1;
			if(acc_y >= 0.2)//��ǰ��б
				state = 2;
		}
		else if(acc_x >= 0.2)
		{
			if(acc_y <= -0.2)//�����б
				state = 3;
			if(acc_y >= 0.2)//�Һ���б
				state = 4;
		}
		
		if(state != 9)
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
		else
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
		
		if(state == 9){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 1){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,1);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,1);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 2){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,1);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,1);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 3){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,1);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,1);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 4){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,1);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,1);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 5){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,2);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,2);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 6){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,2);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,2);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 7){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,2);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,2);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 8){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,2);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,2);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 11){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,1);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 12){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,1);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 13){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,1);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
			delay(500);
			E1_HT16K33_clean();
		}
		else if(state == 14){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,0);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,1);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
			delay(500);
			E1_HT16K33_clean();
		}
		delay(500);
		
	
		
	}
}









/*************************************************************************************************************
功能:     按下复位键启动程序。数码管的四个位置分别对应左前后右，此时用六轴传感器来模拟老人，
					当六轴传感器检测到向前倾倒时（即模拟检测到老人向前摔倒），在第二位显示数字1。
版本:     2023-5-17 V1.0
修改记录: 无
作者:     ZZZ
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
			if(acc_y <= 0.2 && acc_y > -0.2)//平稳状态
				state = 9;
			if(acc_y <= -0.2)//左倾斜
				state = 11;
			if(acc_y > 0.2)//右倾斜
				state = 12;
		}
		else if(acc_y < 0.2 && acc_y > -0.2)
		{
			if(acc_x <= 0.2 && acc_x >= -0.2)//平稳状态
				state = 9;
			if(acc_x < -0.2)//前倾斜
				state = 13;
			if(acc_x > 0.2)//后倾斜
				state = 14;
		}
		else if(acc_x <= -0.2)
		{
			if(acc_y <= -0.2)//左前倾斜
				state = 1;
			if(acc_y >= 0.2)//右前倾斜
				state = 2;
		}
		else if(acc_x >= 0.2)
		{
			if(acc_y <= -0.2)//左后倾斜
				state = 3;
			if(acc_y >= 0.2)//右后倾斜
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









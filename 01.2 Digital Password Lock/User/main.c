/*************************************************************************************************************
����:     ������������Ϊ127369�������������֣�
					��������1��ϵͳ����ʼ�����ж���
					��5λΪ27369ʱ��������ȷ��������
�汾:     2023-5-17 V1.0
�޸ļ�¼: ��
����:     ZZZ
*************************************************************************************************************/

#include "gd32f4xx.h"
#include "stdio.h"
#include "string.h"
#include "i2c.h"
#include "delay.h"
#include "led.h"

#include "s1.h"
#include "e1.h"



i2c_addr_def e1_nixie_tube_addr;
i2c_addr_def e1_rgb_led_addr;


void user_init( void );

void user_init()
{
	LED_Init();
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
	 
	i2c0_gpio_config();
	i2c0_config(); 			
	
	i2c1_gpio_config();
	i2c1_config();
	
	S1_I2C_ADDR_Init();

	E1_4NLED_ADDR_Init();
	E1_3LED_ADDR_Init();

	
}

int main(void)
{
	user_init();
	int num = 0;
		
	while(1)
	{		
		S1();
		if (output == 1){
			num ++;
			output = 0;
		}
		if (output == 2 && num == 1){
			num ++;
			output = 0;
		}
		if (output == 7 && num == 2){
			num ++;
			output = 0;
		}	
		if (output == 3 && num == 3){
			num ++;
			output = 0;
		}
		if (output == 6 && num == 4){
			num ++;
			output = 0;
		}
		if (output == 9 && num == 5){
			num ++;
			output = 0;
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
		}
		
	}
		pressed = 0;
		delay(100);
	  
}





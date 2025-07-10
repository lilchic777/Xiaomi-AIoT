/* 实现风扇转速控制及显示(U1、E1、E2) */
#include <stdio.h>
#include "delay.h"
#include "e1.h"
#include "e2.h"

int main()
{
	char buf[10] = {0};

	/* 数码管初始化 */
	e1_tube_info = e1_tube_init();
	/* 风扇初始化 */
	e2_fan_info = e2_fan_init();
	/* LED初始化 */
	e1_led_info = e1_led_init();
	e1_led_rgb_set(e1_led_info, 0, 0, 0);

	while (1)
	{
		/* 循环递增i的值 */
		for (unsigned char i = 0; i <= 100; i += 10)
		{
			/* 将i的值转换为字符串并写入buf */
			sprintf(buf, "%d", i);
			/* 在数码管上显示buf中的字符串 */
			e1_tube_str_set(e1_tube_info, buf);
			/* 将风扇转速设置为i% */
			e2_fan_speed_set(e2_fan_info, i);
			/* 延时3000ms */
			delay(3000);
		}
	}
}

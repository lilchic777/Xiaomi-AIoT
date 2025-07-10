/* 汽车倒车测距（U1P, S6, E1） */
#include <stdio.h>
#include "delay.h"
#include "e1.h"
#include "s6.h"

int main()
{
	char buf[10] = {0};
	unsigned int distance = 0;

	/* 数码管初始化 */
	e1_tube_info = e1_tube_init();
	e1_led_info = e1_led_init();

	/* 超声波传感器初始化 */
	s6_ultrasonic_info = s6_ultrasonic_init();

	while (1)
	{
		/* 读取超声波传感器测量结果（毫米） */
		distance = s6_ultrasonic_distance_get(s6_ultrasonic_info);
		/* 将测量结果转换为字符串并写入buf */
		sprintf(buf, "%d", distance);
		/* 在数码管上显示buf中的字符串 */
		e1_tube_str_set(e1_tube_info, buf);

		if (distance <= 500)
			e1_led_rgb_set(e1_led_info, 100, 0, 0);
		else if (distance <= 1000)
			e1_led_rgb_set(e1_led_info, 100, 100, 0);
		else
			e1_led_rgb_set(e1_led_info, 0, 100, 0);

		/* 延时100ms */
		delay(100);
	}
}
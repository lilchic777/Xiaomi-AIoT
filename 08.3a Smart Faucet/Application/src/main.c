/* 感应水龙头设计（U1P，E1，S7） */
#include <stdio.h>
#include "delay.h"
#include "e1.h"
#include "s7.h"
#include "u1.h"
extern int time;
int main()
{
	char buf[10] = {0};
	unsigned char status = 0;
	unsigned char last_status = 0;
	int mode = 0;

	/* 数码管初始化 */
	e1_tube_info = e1_tube_init();
	/* LED初始化 */
	e1_led_info = e1_led_init();
	/* 人体红外传感器初始化 */
	s7_ir_info = s7_ir_init();
	/* u1 LED+timer初始化 */
	u1_led_init();
	u1_timer0_init();

	e1_tube_str_set(e1_tube_info, "----");
	delay(1000);

	while (1)
	{
		/* 读取人体红外传感器感应状态 */
		status = s7_ir_status_get(s7_ir_info);

		if (status != 0 && last_status == 0) // 人体传感器检测到上升沿，更新倒计时
			time = 30;
		last_status = status;

		/* 如果检测到人体，开始倒计时并打开水龙头（亮绿灯） */
		if (status && time >= 0)
		{
			e1_led_rgb_set(e1_led_info, 0, 100, 0);
			/* 将格式化字符串写入buf */
			sprintf(buf, "%d", time);
			/* 在数码管上显示buf中的字符串 */
			e1_tube_str_set(e1_tube_info, buf); // 数码管上显示倒计时时间，计时在u1的timer0中完成
		}

		/* 如果没有检测到人体或超过30s，绿灯熄灭并在数码管上显示"----" */
		else
		{
			e1_tube_str_set(e1_tube_info, "----");
			e1_led_rgb_set(e1_led_info, 0, 0, 0);
		}
			// /* 延时100ms */
			// delay(100);
	}
}

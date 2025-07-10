/* 自动窗帘 */
#include <stdio.h>
#include "delay.h"
#include "e1.h"
#include "e3.h"
#include "s1.h"

int main()
{
    char key = 0; // 初始化为0，假设没有按键按下时为0
    char last_key = 0;
    char buf[10] = {0};
    unsigned char target_position = 0;
    unsigned char real_position;
    unsigned char real_status;
    int mode = 0;
    int has_pressed = 0; // 新增标志变量，表示是否有按键被按下过

    /* 数码管初始化 */
    e1_tube_info = e1_tube_init();
    e1_tube_str_set(e1_tube_info, "----"); // 上电默认显示“----”

    /* LED初始化 */
    e1_led_info = e1_led_init();
    e1_led_rgb_set(e1_led_info, 0, 0, 0);

    /* 窗帘初始化 */
    e3_curtain_info = e3_curtain_init();
    e3_curtain_position_set(e3_curtain_info, target_position);

    /* 按键初始化 */
    s1_key_info = s1_key_init();

    while (1)
    {
        key = s1_key_value_get(s1_key_info);

        /* 检测按键按下事件（上升沿） */
        if (last_key == 0 && key != 0)
        {
            has_pressed = 1; // 有按键被按下
            if (key == '1')
                mode = 1;
            else if (key == '2')
                mode = 2;
            else if (key == '3')
                mode = 3;
            else
                mode = 0;
        }
        last_key = key;

        /* 读取窗帘状态和位置 */
        real_status = e3_curtain_status_get(e3_curtain_info);
        real_position = e3_curtain_position_get(e3_curtain_info);

        /* 根据按键状态更新显示内容 */
        if (has_pressed)
            sprintf(buf, "%d.%03d", real_status, real_position);
        else
            sprintf(buf, "----");
        e1_tube_str_set(e1_tube_info, buf);

        switch (mode)
        {
        case 0: // 动态模式
            if (real_position == target_position && real_status == 0)
            {
                delay(2000);
                target_position = (target_position == 0) ? 100 : 0;
            }
            break;
        case 1: // 最左侧
            target_position = 100;
            break;
        case 2: // 中间
            target_position = 50;
            break;
        case 3: // 最右侧
            target_position = 0;
            break;
        }
        if (has_pressed)
            e3_curtain_position_set(e3_curtain_info, target_position);
        delay(100);
    }
}

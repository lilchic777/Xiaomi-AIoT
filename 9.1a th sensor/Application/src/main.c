/* 实现温湿度切换显示功能 */
#include <stdio.h>
#include "delay.h"
#include "e1.h"
#include "s1.h"
#include "s8.h"

int main()
{
    char key = 0;
    char last_key = 0;       // 记录上一次按键状态
    char buf[10] = {0};
    int display_mode = 0;    // 显示模式：0=默认 1=温度 2=湿度
    s8_ths_t ths_value;

    /* 数码管初始化 */
    e1_tube_info = e1_tube_init();

    /* 温湿度传感器初始化 */
    s8_ths_info = s8_ths_init();

    /* 按键初始化 */
    s1_key_info = s1_key_init();

    e1_tube_str_set(e1_tube_info, "----");
    delay(2000);

    while (1)
    {
        /* 读取当前按键状态 */
        key = s1_key_value_get(s1_key_info);

        /* 检测按键上升沿（按下事件） */
        if (key != last_key) {
            if (key == '1') {
                display_mode = 1;  // 切换为温度模式
            } else if (key == '2') {
                display_mode = 2;  // 切换为湿度模式
            }
        }
        last_key = key;  // 更新按键历史状态

        /* 根据模式显示内容 */
        switch(display_mode) {
            case 1:  // 温度模式
                ths_value = s8_ths_value_get(s8_ths_info);
                sprintf(buf, "%2.1fC", ths_value.temp);
                break;
            case 2:  // 湿度模式
                ths_value = s8_ths_value_get(s8_ths_info);
                sprintf(buf, "%2.1fH", ths_value.humi);
                break;
            default: // 默认显示
                sprintf(buf, "0000");
                break;
        }
        
        /* 更新数码管显示 */
        e1_tube_str_set(e1_tube_info, buf);

        /* 延时100ms（含按键消抖功能） */
        delay(100);
    }
}

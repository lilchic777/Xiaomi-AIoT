/* E3代替宿舍门锁，
无人时，门锁E3处于关闭状态；
刷卡时，灯亮起代表有人进门，E3自动打开，并进行倒计时，5秒后，门锁将自动关闭。
 */
#include <stdio.h>
#include "delay.h"
#include "e1.h"
#include "e3.h"
#include "s5.h"
#include "led.h"

void User_Init()
{
	/* 数码管初始化 */
	e1_tube_info = e1_tube_init();

	/* LED初始化 */
	e1_led_info = e1_led_init();
	e1_led_rgb_set(e1_led_info, 0, 0, 0);
	LED_Init();
	/* 窗帘初始化 */
	e3_curtain_info = e3_curtain_init();
	/* 将窗帘目标位置设置为0 */
	e3_curtain_position_set(e3_curtain_info, 0);

	/* NFC初始化 */
	s5_nfc_info = s5_nfc_init();
}

void S5_NFC(char Status, unsigned char CardType[], unsigned char CardID[], unsigned char Key[], char Data[])
{
}

int main()
{

	char buf[10] = {0};
	/* 窗帘目标位置 */
	unsigned char target_position = 0;
	/* 窗帘当前位置 */
	unsigned char real_position;
	/* 窗帘电机状态，0表示电机停止工作，1表示电机正在工作 */
	unsigned char real_status;

	// 状态机状态
	char Status = 0;
	// 卡类型
	unsigned char CardType[2] = {0};
	// 卡ID（全球唯一）
	unsigned char CardID[4] = {0};
	// 卡密码
	unsigned char Key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	// 数据缓冲
	char Data[16] = {0};

	User_Init();
	LED_ON();

	while (1)
	{
		// S5_NFC(Status, CardType, CardID, Key, Data);
		// 查询状态机当前状态
		switch (Status)
		{
		// 寻卡状态
		case 0:
			// 寻找射频场内所有符合ISO 14443-A协议且未休眠的卡(0x26)，寻卡成功后将卡的类型写入CardType
			e1_led_rgb_set(e1_led_info, 0, 0, 0);
			e3_curtain_position_set(e3_curtain_info, 0);
			if (s5_nfc_request(s5_nfc_info, 0x26, CardType) == MI_OK)
			{
				// 如果寻卡成功，显示卡的类型
				sprintf(Data, "%02x%02x", CardType[0], CardType[1]);
				e1_tube_str_set(e1_tube_info, Data);
				delay(1000);

				// 如果寻卡成功，进入防冲撞状态
				Status = 1;
			}
			else
			{
				// 如果寻卡失败，显示"----"
				sprintf(Data, "----");
				e1_tube_str_set(e1_tube_info, Data);
				delay(1000);

				// 如果寻卡失败，保持寻卡状态
				Status = 0;
			}
			break;

		// 防冲撞状态
		case 1:
			// 通过防冲撞机制选择射频场内的一张卡，防冲撞成功后将选中的卡的ID写入CardID

			if (s5_nfc_anticoll(s5_nfc_info, CardID) == MI_OK)
			{
				// 如果防冲撞成功，显示卡的ID
				sprintf(Data, "%02x%02x%02x%02x", CardID[0], CardID[1], CardID[2], CardID[3]);
				e1_tube_str_set(e1_tube_info, Data);
				delay(500);

				// 如果防冲撞成功，进入选卡状态
				Status = 2;
			}
			else
			{
				// 如果防冲撞失败，回到寻卡状态
				Status = 0;
			}
			break;

		// 选卡状态
		case 2:
			// e1_led_rgb_set(e1_led_info, 0, 100, 0);
			// delay(1000);
			// 选中ID为CardID的卡
			if (s5_nfc_select(s5_nfc_info, CardID) == MI_OK)
			{
				// 如果选卡成功，进入认证/休眠状态
				Status = 3;
				// Status = 6;
			}
			else
			{
				// 如果选卡失败，回到寻卡状态
				Status = 0;
			}
			break;

		// 认证状态
		case 3:
			// e1_led_rgb_set(e1_led_info, 100, 100, 100);
			// delay(1000);
			// 使用秘钥A(0x60)认证ID为CardID的卡的第5块（第1区的第1块），认证密码为Key
			if (s5_nfc_auth(s5_nfc_info, 0x60, 5, Key, CardID) == MI_OK)
			{
				// 如果认证成功，进入写卡/读卡状态
				Status = 4;
				// Status = 5;
			}
			else
			{
				// 如果认证失败，回到寻卡状态
				Status = 0;
			}
			break;

		// 写卡状态
		case 4:
			// e1_led_rgb_set(e1_led_info, 0, 0, 100);
			// delay(1000);
			// 向第5块（第1区的第1块）中写入数据(16Byte)"1234567887654321"
			if (s5_nfc_write(s5_nfc_info, 5, (unsigned char *)"1234567887654321") == MI_OK)
			{
				// 如果写卡成功，进入读卡/休眠状态
				Status = 5;
				// Status = 6;
			}
			else
			{
				// 如果写卡失败，回到寻卡状态
				Status = 0;
			}
			break;

		// 读卡状态
		case 5:
			// e1_led_rgb_set(e1_led_info, 100, 100, 100);
			// delay(1000);
			// 读取第5块（第1区的第1块）中的数据(16Byte)，读取成功后将数据写入Data

			if (s5_nfc_read(s5_nfc_info, 5, (unsigned char *)Data) == MI_OK)
			{
				// 如果读卡成功，显示读取到的数据
				e1_tube_str_set(e1_tube_info, Data);
				delay(500);

				/* 将格式化字符串写入buf */
				sprintf(buf, "%s", "OPEN");
				/* 在数码管上显示buf中的字符串 */
				e1_tube_str_set(e1_tube_info, buf);
				/* 延时1000ms */
				delay(1000);

				e3_curtain_position_set(e3_curtain_info, 100);
				delay(7000);
				e1_led_rgb_set(e1_led_info, 100, 0, 0);
				delay(7000);
				// delay(1000);

				// 如果读卡成功，进入写卡/休眠状态
				// Status = 4;
				Status = 6;
			}
			else
			{
				// 如果读卡失败，回到寻卡状态
				Status = 0;
			}
			break;

		// 休眠状态
		case 6:
			// e1_led_rgb_set(e1_led_info, 0, 0, 0);
			// delay(1000);
			// e3_curtain_position_set(e3_curtain_info, 0);
			// delay(5000);
			// 休眠当前选中的卡
			if (s5_nfc_halt(s5_nfc_info) == MI_OK)
			{
				// 如果休眠成功，回到寻卡状态
				Status = 0;
			}
			else
			{
				// 如果休眠失败，回到寻卡状态
				Status = 0;
			}
			break;

		default:
			break;
		}
	}
}

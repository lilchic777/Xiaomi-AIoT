



/*********************************************************************************************************
函数名:     s1_init
入口参数:   i2c初始地址 address 
出口参数:   无 
返回值:     i2c_addr_def定义结构体
作者:       zzz
日期:       2023/4/1
调用描述:   得到s1 i2c地址,若器件不存在则结构体flag值为0,若存在则初始化芯片置结构体flag值为1
**********************************************************************************************************/
//i2c_addr_def s1_init(uint8_t address)
//{
//	i2c_addr_def e_addess;

//	e_addess = get_board_address(address);

//	if(e_addess.flag)
//	{
//		i2c_cmd_write(e_addess.periph,e_addess.addr,S1_SYSTEM_ON);
//	}
//	return e_addess;		 
//}



/*********************************************************************************************************
函数名:     s1_all_init
入口参数:   s1_address结构体指针  s1_addr:s1 i2c起始地址 
出口参数:   s1_address结构体指针
返回值:     无
作者:       zzz
日期:       2023/4/1
调用描述:   查找并初始化所有s1子板,并得到相应的地址放在结构体指针s1_address
**********************************************************************************************************/
//void s1_all_init(out s1_addr_def *s1_address,uint8_t s1_addr)
//{
//	uint8_t i;

//	for(i=0;i<4;i++)
//	{
//		s1_address->key_addr[i] = get_board_address(s1_addr+i*2);
//		if(s1_address->key_addr[i].flag)
//		i2c_cmd_write(s1_address->key_addr[i].periph,s1_address->key_addr[i].addr,S1_SYSTEM_ON);	
//	}
//}

//extern i2c_addr_def s1_init(uint8_t address);
//void s1_all_init(s1_addr_def *s1_address,uint8_t s1_addr);
//void pc9685_rgb_led_control(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num);
/*********************************************************************************************************
函数名:     get_board_address
入口参数:   address 初始地址
出口参数:   无 
返回值:     eborad_address实际得到的结构体地址
作者:       zzz
日期:       2023/3/31
调用描述:   得到实际的I2C地址和I2C口
**********************************************************************************************************/
//i2c_addr_def get_board_address(uint8_t address)
//{
//     i2c_addr_def eboard_addess;

//	   eboard_addess.flag = 0;
//	
//	   if(i2c_addr_poll(I2C0,address))
//		 {
//			    eboard_addess.periph = I2C0;
//				  eboard_addess.addr = address;
//					eboard_addess.flag = 1;			
//		 } 			 
//	   if(eboard_addess.flag != 1)
//		 {
//			    if(i2c_addr_poll(I2C1,address))
//					{
//						  eboard_addess.periph = I2C1;
//				      eboard_addess.addr = address;
//					    eboard_addess.flag = 1; 
//          }						
//     }	
//     
//		 return eboard_addess;		 
//}



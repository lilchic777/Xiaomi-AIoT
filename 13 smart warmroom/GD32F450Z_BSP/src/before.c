



/*********************************************************************************************************
������:     s1_init
��ڲ���:   i2c��ʼ��ַ address 
���ڲ���:   �� 
����ֵ:     i2c_addr_def����ṹ��
����:       zzz
����:       2023/4/1
��������:   �õ�s1 i2c��ַ,��������������ṹ��flagֵΪ0,���������ʼ��оƬ�ýṹ��flagֵΪ1
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
������:     s1_all_init
��ڲ���:   s1_address�ṹ��ָ��  s1_addr:s1 i2c��ʼ��ַ 
���ڲ���:   s1_address�ṹ��ָ��
����ֵ:     ��
����:       zzz
����:       2023/4/1
��������:   ���Ҳ���ʼ������s1�Ӱ�,���õ���Ӧ�ĵ�ַ���ڽṹ��ָ��s1_address
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
������:     get_board_address
��ڲ���:   address ��ʼ��ַ
���ڲ���:   �� 
����ֵ:     eborad_addressʵ�ʵõ��Ľṹ���ַ
����:       zzz
����:       2023/3/31
��������:   �õ�ʵ�ʵ�I2C��ַ��I2C��
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



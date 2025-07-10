#include "gd32f4xx.h"
#include "i2c.h"
#include <stdio.h>
//引用区域


uint16_t i2c_over_time = 0;
/*!
    \brief  judge over time    
*/
uint8_t judge_i2c_over_time(void)
{
		i2c_over_time++;
    if(i2c_over_time > 60000)
    return 1;
    else
    return 0;			
}

void i2c_delay(uint32_t time)
{
     uint32_t i;
     
	   for(i=0;i<time;i++)
	   {
		 }	 
}


void i2c0_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    //GPIOB的RCU外设时钟使能
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_8);
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_9);
		//GPIO复用设置
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_8);
		gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_9);
		//GPIO模式设置复用上拉
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_8);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_9);
		//GPIO输出设置开漏输出
}

void i2c0_config(void)
{
    rcu_periph_clock_enable(RCU_I2C0);
		//使能I2C0的RCU外设时钟
    i2c_clock_config(I2C0,I2C0_SPEED,I2C_DTCY_2);
		//I2C0时钟设置
    i2c_mode_addr_config(I2C0,I2C_I2CMODE_ENABLE,I2C_ADDFORMAT_7BITS,I2C0_SLAVE_ADDRESS7);
		//I2C0地址设置
    i2c_enable(I2C0);
		//I2C0使能
    i2c_ack_config(I2C0,I2C_ACK_ENABLE);
		//I2C0应答帧设置开启
}

void i2c1_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOF);
    
    gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_1);
    gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_0);

    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_0);
		gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_1);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_0);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_1);
		
}

void i2c1_config(void)
{
    rcu_periph_clock_enable(RCU_I2C1);
		//使能I2C1的RCU外设时钟
    i2c_clock_config(I2C1,I2C1_SPEED,I2C_DTCY_2);
		//I2C1时钟设置
    i2c_mode_addr_config(I2C1,I2C_I2CMODE_ENABLE,I2C_ADDFORMAT_7BITS,I2C1_SLAVE_ADDRESS7);
		//I2C1地址设置
    i2c_enable(I2C1);
		//I2C1使能
    i2c_ack_config(I2C1,I2C_ACK_ENABLE);
		//I2C1应答帧设置开启
}

void i2c2_gpio_config(void)
{
		rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);
    
    /* connect PA8 to i2c2_SCL */
    gpio_af_set(GPIOA, GPIO_AF_4, GPIO_PIN_8);
    /* connect PC9 to i2c2_SDA */
    gpio_af_set(GPIOC, GPIO_AF_4, GPIO_PIN_9);

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_8);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_8);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_9);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_9);
}

void i2c2_config(void)
{
    /* enable I2C clock */
    rcu_periph_clock_enable(RCU_I2C2);
    /* configure I2C clock */
    i2c_clock_config(I2C2,I2C2_SPEED,I2C_DTCY_2);
    /* configure I2C address */
    i2c_mode_addr_config(I2C2,I2C_I2CMODE_ENABLE,I2C_ADDFORMAT_7BITS,I2C2_SLAVE_ADDRESS7);
    /* enable I2C2 */
    i2c_enable(I2C2);
    /* enable acknowledge */
    i2c_ack_config(I2C2,I2C_ACK_ENABLE);
}

uint8_t i2c_addr_poll(uint32_t i2c_periph,uint8_t poll_addr)
{
		uint16_t i = 0;
		uint8_t result;
    /* wait until I2C bus is idle */
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));
		//等待I2C总线忙碌结束
    i2c_start_on_bus(i2c_periph);
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    //等待起始位置0
    /* send slave address to I2C bus */
		i2c_master_addressing(i2c_periph, poll_addr, I2C_TRANSMITTER);
		//主机发送从机地址
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		//从机地址是否发送(没有发送则停留在该循环中等待发送完成)
		{
			i++ ;
			if(i > 60000)
			{
				break;
			}
		}
    
		if(i > 60000)
		{
			result = 0;
		}
		else
		{
			result = 1;
		}		

    i2c_stop_on_bus(i2c_periph);
    //发送结束位给IIC总线
    while(I2C_CTL0(i2c_periph)&0x0200);
		//等待I2C0下I2C_CTL0中的硬件清零结束
		return result;
}

/*!
    \brief      write command to slave
    \param[in]  cmd：command to control
    \param[out] none
    \retval     none
*/
void i2c_cmd_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t cmd)
{
		uint16_t i;

    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));
		//等待BUS总线占用结束

    i2c_start_on_bus(i2c_periph);
    //发送起始位给IIC总线
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    //等待起始位发送标志位置1
		i2c_master_addressing(i2c_periph, i2c_addr, I2C_TRANSMITTER);
    //主机发送从机地址
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		//主机模式等待发送完成
		{
			i++ ;
			if(i > 60000)
			{
				i2c_stop_on_bus(i2c_periph);
				//发送结束位给IIC总线
				return;
			}
		}    
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    //清除ADDSEND标志位的值
    while(SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE));
    //等待传输数据缓冲为空
    i2c_data_transmit(i2c_periph, cmd);
    //发送cmd(一个字节)
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));    
		//等待(缓冲区发送完成标志位置1)字节发送结束
    i2c_stop_on_bus(i2c_periph);
    //发送结束位给IIC总线
    while(I2C_CTL0(i2c_periph)&0x0200);
		//等待I2C0下I2C_CTL0中的硬件清零结束	
}

void i2c_byte_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t write_address,uint8_t buffer)
{
		uint16_t i;
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));
    i2c_start_on_bus(i2c_periph);
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_TRANSMITTER);
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			i++ ;
			if(i > 60000)
			{
				i2c_stop_on_bus(i2c_periph);
				return;
			}
		}   
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    while(SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE));
    i2c_data_transmit(i2c_periph, write_address);
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
    i2c_data_transmit(i2c_periph, buffer); 
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
    i2c_stop_on_bus(i2c_periph);
    while(I2C_CTL0(i2c_periph)&0x0200);
}

/*!
    \brief      write more than one byte to the slave with a single write cycle
    \param[in]  p_buffer: pointer to the buffer containing the data to be written 
    \param[in]  write_address: slave internal address to write to
    \param[in]  number_of_byte: number of bytes to write to 
    \param[out] none
    \retval     none
*/
void i2c_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t write_address,uint8_t* p_buffer,  uint8_t number_of_byte)
{
		uint16_t i;
    /* wait until I2C bus is idle */
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));
    
    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_TRANSMITTER);
    
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			i++ ;
			if(i > 60000)
			{
				/* send a stop condition to I2C bus */
				i2c_stop_on_bus(i2c_periph);
				return;
			}
		}   
    
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    
    /* wait until the transmit data buffer is empty */
    while( SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE));
    
    /* send the EEPROM's internal address to write to : only one byte address */
    i2c_data_transmit(i2c_periph, write_address);
    
    /* wait until BTC bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
    
    /* while there is data to be written */
    while(number_of_byte--){  
        i2c_data_transmit(i2c_periph, *p_buffer);
        
        /* point to the next byte to be written */
        p_buffer++; 
        
        /* wait until BTC bit is set */
        while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
    }
    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(i2c_periph);
    
    /* wait until the stop condition is finished */
    while(I2C_CTL0(i2c_periph)&0x0200);
}


/*!
    \brief      read data from the slave
    \param[in]  p_buffer: pointer to the buffer that receives the data read from the slave
    \param[in]  read_address: slave internal address to start reading from
    \param[in]  number_of_byte: number of bytes to reads from the slave
    \param[out] none
    \retval     none
*/
uint8_t i2c_read(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t read_address,uint8_t* p_buffer, uint16_t number_of_byte)
{  
		uint8_t	rt = 1;
		uint16_t i;
    /* wait until I2C bus is idle */
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));

    if(2 == number_of_byte){
        i2c_ackpos_config(i2c_periph,I2C_ACKPOS_NEXT);
    }
    
    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_TRANSMITTER);
    
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			i++ ;
			if(i > 60000)
			{
				/* send a stop condition to I2C bus */
				i2c_stop_on_bus(i2c_periph);
				rt = 0;
				return rt;
			}
		}   
    
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    
    /* wait until the transmit data buffer is empty */
    while(SET != i2c_flag_get( i2c_periph , I2C_FLAG_TBE ));

    /* enable i2c_periph*/
    i2c_enable(i2c_periph);
    
    /* send the slave internal address to write to */
    i2c_data_transmit(i2c_periph, read_address);  
    
    /* wait until BTC bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
    
    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_RECEIVER);

    if(number_of_byte < 3){
        /* disable acknowledge */
        i2c_ack_config(i2c_periph,I2C_ACK_DISABLE);
    }
    
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND));
    
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    
    if(1 == number_of_byte){
        /* send a stop condition to I2C bus */
        i2c_stop_on_bus(i2c_periph);
    }
    
    /* while there is data to be read */
    while(number_of_byte){
        if(3 == number_of_byte){
            /* wait until BTC bit is set */
            while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));

            /* disable acknowledge */
            i2c_ack_config(i2c_periph,I2C_ACK_DISABLE);
        }
        if(2 == number_of_byte){
            /* wait until BTC bit is set */
            while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
            
            /* send a stop condition to I2C bus */
            i2c_stop_on_bus(i2c_periph);
        }
        
        /* wait until the RBNE bit is set and clear it */
        if(i2c_flag_get(i2c_periph, I2C_FLAG_RBNE)){
            /* read a byte from the EEPROM */
            *p_buffer = i2c_data_receive(i2c_periph);
            
            /* point to the next location where the byte read will be saved */
            p_buffer++; 
            
            /* decrement the read bytes counter */
            number_of_byte--;
        } 
    }
    
    /* wait until the stop condition is finished */
    while(I2C_CTL0(i2c_periph)&0x0200);
    
    /* enable acknowledge */
    i2c_ack_config(i2c_periph,I2C_ACK_ENABLE);

    i2c_ackpos_config(i2c_periph,I2C_ACKPOS_CURRENT);
		
		return rt;
}

void i2c_delay_byte_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t write_address,uint8_t buffer)
{
		uint16_t i = 0;
	  uint32_t time = 50000;
	
    /* wait until I2C bus is idle */
	  i2c_over_time = 0;
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY))
		{
			  if(judge_i2c_over_time() == 1)
				{
					  return; 	 
				}
    }			
    i2c_delay(time);
	
    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    i2c_delay(time);
	
    /* wait until SBSEND bit is set */
		i2c_over_time = 0;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND))
		{
			  if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return; 	 
				}
    }			
    i2c_delay(time);
	
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_TRANSMITTER);
    i2c_delay(time);
	
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			i++ ;
			if(i > 60000)
			{
				/* send a stop condition to I2C bus */
				i2c_stop_on_bus(i2c_periph);
				return;
			}
		}   
    i2c_delay(time);
		
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    i2c_delay(time);
		
    /* wait until the transmit data buffer is empty */
		i2c_over_time = 0;
    while(SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE))
		{
			  if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return; 	 
				}
    }			
    i2c_delay(time);
		
    /* send the EEPROM's internal address to write to : only one byte address */
    i2c_data_transmit(i2c_periph, write_address);
    i2c_delay(time);
		
    /* wait until BTC bit is set */
		i2c_over_time = 0;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
		{
			  if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return; 	 
				}
    }			
    i2c_delay(time);
		
    /* send the byte to be written */
    i2c_data_transmit(i2c_periph, buffer); 
    i2c_delay(time);
		
    /* wait until BTC bit is set */
		i2c_over_time = 0;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
		{
			  if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return; 	 
				}
    }			
    i2c_delay(time);
		
    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(i2c_periph);
    i2c_delay(time);
		
    /* wait until the stop condition is finished */
		i2c_over_time = 0;
    while(I2C_CTL0(i2c_periph)&0x0200)
		{
			  if(judge_i2c_over_time() == 1)
				{
						return; 	 
				}
    }			
		i2c_delay(time);
}




void i2c_delay_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t write_address,uint8_t* p_buffer,  uint8_t number_of_byte)
{
		uint16_t i = 0;
	  uint32_t time = 10000;
	
    /* wait until I2C bus is idle */
	  i2c_over_time = 0;
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY))
		{
			  if(judge_i2c_over_time() == 1)
				{
						return; 	 
				}
    } 			
    i2c_delay(time);
	
    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    i2c_delay(time);
	
    /* wait until SBSEND bit is set */
		i2c_over_time = 0;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND))
		{
			  if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return; 	 
				}
    } 			
    i2c_delay(time);
	
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_TRANSMITTER);
    i2c_delay(time);  
	
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			i++ ;
			if(i > 60000)
			{
				/* send a stop condition to I2C bus */
				i2c_stop_on_bus(i2c_periph);
				return;
			}
		}   
    i2c_delay(time);
		
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
		i2c_delay(time); 
    
    /* wait until the transmit data buffer is empty */
		i2c_over_time = 0;
    while( SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE))
		{
			  if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return; 	 
				}
    }			
		i2c_delay(time);
    
    /* send the EEPROM's internal address to write to : only one byte address */
    i2c_data_transmit(i2c_periph, write_address);
		i2c_delay(time);
    
    /* wait until BTC bit is set */
		i2c_over_time = 0;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
		{
			  if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return; 	 
				}
    } 			
		i2c_delay(time);
    
    /* while there is data to be written */
    while(number_of_byte--){  
        i2c_data_transmit(i2c_periph, *p_buffer);
        
        /* point to the next byte to be written */
        p_buffer++; 
        
        /* wait until BTC bit is set */
			  i2c_over_time = 0;
        while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
				{
					  if(judge_i2c_over_time() == 1)
						{
								i2c_stop_on_bus(i2c_periph);
								return; 	 
						} 
        }					
    }
		i2c_delay(time);
		
    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(i2c_periph);
    i2c_delay(time);
		
    /* wait until the stop condition is finished */
		i2c_over_time = 0;
    while(I2C_CTL0(i2c_periph)&0x0200)
		{
			  if(judge_i2c_over_time() == 1)
				{
						break; 	 
				}
    }			
		i2c_delay(time);
}





uint8_t i2c_delay_read(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t read_address,uint8_t* p_buffer,  uint16_t number_of_byte)
{  
		uint8_t	rt = 1;
		uint16_t i = 0;
	  uint32_t time = 10000;  
	
	  /* wait until I2C bus is idle */
	  i2c_over_time = 0;
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY))
		{
			  if(judge_i2c_over_time() == 1)
				{
						return 0; 	 
				}
    }			

    if(2 == number_of_byte){
        i2c_ackpos_config(i2c_periph,I2C_ACKPOS_NEXT);
    }
    
		
	  /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
		/* wait until SBSEND bit is set */
		i2c_over_time = 0;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND))
		{
        if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return 0; 	 
				} 			
    }
		
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_TRANSMITTER);
    i2c_delay(time);
		
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			i++ ;
			if(i > 60000)
			{
				/* send a stop condition to I2C bus */
				i2c_stop_on_bus(i2c_periph);
				i2c_delay(time);
				rt = 0;
				return rt;
			}
		}   
    
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    i2c_delay(time);
		
    /* wait until the transmit data buffer is empty */
		i2c_over_time = 0;
    while(SET != i2c_flag_get( i2c_periph , I2C_FLAG_TBE ))
		{
			  if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return 0; 	 
				} 	
    }			

    /* enable i2c_periph*/
    i2c_enable(i2c_periph);
    i2c_delay(time);
		
    /* send the slave internal address to write to */
    i2c_data_transmit(i2c_periph, read_address);  
    i2c_delay(time);
		
    /* wait until BTC bit is set */
		i2c_over_time = 0;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
		{
			  if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return 0; 	 
				}
    }			
    
    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    
    /* wait until SBSEND bit is set */
		i2c_over_time = 0;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND))
		{
			  if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return 0; 	 
				}
    }			
    
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_RECEIVER);
    i2c_delay(time);

    if(number_of_byte < 3){
        /* disable acknowledge */
        i2c_ack_config(i2c_periph,I2C_ACK_DISABLE);
    }
    
    /* wait until ADDSEND bit is set */
		i2c_over_time = 0;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			  if(judge_i2c_over_time() == 1)
				{
						i2c_stop_on_bus(i2c_periph);
						return 0; 	 
				}
    }			
    
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    i2c_delay(time);
    if(1 == number_of_byte){
        /* send a stop condition to I2C bus */
        i2c_stop_on_bus(i2c_periph);
			  i2c_delay(time);
    }
    
    /* while there is data to be read */
    while(number_of_byte){
        if(3 == number_of_byte){
            /* wait until BTC bit is set */
					  i2c_over_time = 0;
            while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
						{
							  if(judge_i2c_over_time() == 1)
								{
										i2c_stop_on_bus(i2c_periph);
										return 0; 	 
								}
            }							

            /* disable acknowledge */
            i2c_ack_config(i2c_periph,I2C_ACK_DISABLE);
					  i2c_delay(time);
        }
        if(2 == number_of_byte){
            /* wait until BTC bit is set */
					  i2c_over_time = 0;
            while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
						{
							  if(judge_i2c_over_time() == 1)
								{
										i2c_stop_on_bus(i2c_periph);
										return 0; 	 
								} 
            }							
            
            /* send a stop condition to I2C bus */
            i2c_stop_on_bus(i2c_periph);
					  i2c_delay(time);
        }
        
        /* wait until the RBNE bit is set and clear it */
        if(i2c_flag_get(i2c_periph, I2C_FLAG_RBNE)){
            /* read a byte from the EEPROM */
            *p_buffer = i2c_data_receive(i2c_periph);
            i2c_delay(time);
            /* point to the next location where the byte read will be saved */
            p_buffer++; 
            
            /* decrement the read bytes counter */
            number_of_byte--;
        } 
    }
    
		/* wait until the stop condition is finished */
		i2c_over_time = 0;
    while(I2C_CTL0(i2c_periph)&0x0200)
		{
			  if(judge_i2c_over_time() == 1)
				{
						break; 	 
				}
    }			
    
    /* enable acknowledge */
    i2c_ack_config(i2c_periph,I2C_ACK_ENABLE);
    //i2c_delay(time);
		
		i2c_ackpos_config(i2c_periph,I2C_ACKPOS_CURRENT);
		//i2c_delay(time);
		
		
		return rt;
}






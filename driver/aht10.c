

#include "../include/driver/aht10.h"
#include "os_type.h"
#include "driver/i2c_master.h"


bool ICACHE_FLASH_ATTR AHT10_Init()
{
	i2c_master_gpio_init();
	i2c_master_start();
	return 1;

}

int32_t ICACHE_FLASH_ATTR AHT10_Data()
{
	os_printf("AHT10_GetTemperature:*************\n");
	i2c_master_start();
	i2c_master_writeByte(AHT10_ADDR_W);
	if(!i2c_master_checkAck()){
		os_printf("AHT10_GetTemperature: i2c_master_writeByte(AHT10_ADDR_W) slave not ack..\r\nreturn\r\n");
		i2c_master_stop();
		return(0);
	}
	i2c_master_writeByte(AHT10_GET_DATA);//get data cmd 0xAC
	if(!i2c_master_checkAck()){
		os_printf("AHT10_GetTemperature: i2c_master_writeByte(AHT10_GET_DATA) slave not ack..\r\nreturn\r\n");
		i2c_master_stop();
		return(0);
	}
	i2c_master_writeByte(0x33);
	if(!i2c_master_checkAck()){
		os_printf("AHT10_GetTemperature: i2c_master_writeByte(0x33) slave not ack..\r\nreturn\r\n");
		i2c_master_stop();
		return(0);
	}
	i2c_master_writeByte(0x0);
	if(!i2c_master_checkAck()){
		os_printf("AHT10_GetTemperature: i2c_master_writeByte(0x0) slave not ack..\r\nreturn\r\n");
		i2c_master_stop();
		return(0);
	}
	i2c_master_stop();
	os_delay_us(500); // max time is 4.5ms


	i2c_master_start();
	i2c_master_writeByte(AHT10_ADDR_R);

	if(!i2c_master_checkAck()){
		os_printf("AHT10_GetTemperature: i2c_master_writeByte(AHT10_ADDR_R) slave not ack..\r\nreturn\r\n");
		i2c_master_stop();
		return(0);
	}
	uint8_t data[6];
	int32_t i,result_t,result_h;
	for(i=0;i<6;i++)
	{
		data[i]= i2c_master_readByte();
		if(i==5)
			i2c_master_send_nack();
		else
			i2c_master_send_ack();
	}

	i2c_master_stop();

	for(i=0;i<6;i++)
	{
		os_printf("i2c_master_readByte:0x%x \n",data[i]);
	}

	result_t = ((data[3] & 0x0F) << 16) | (data[4] << 8) | data[5];

	int32_t t = (((200.0 * (float)result_t) / 1048576.0) - 50.0)*100.0;


	result_h = ((data[1] << 16) | (data[2] << 8) | data[3]) >> 4;

	int32_t h = (float)result_h * 10000.0 / 1048576.0;

	os_printf("t:%u.%u,h:%u.%u%\n",t/100,t%100,h/100,h%100);
	
	
	return 0;
}


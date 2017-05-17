
/* Example application of Columbo Simple Serial Library
 * Copyright 2003 Marcin Siennicki <m.siennicki@cloos.pl>
 * see COPYING file for details */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "cssl.h"
#define  FRAMELENGTH 32 //定义数据帧长度 字节
//using namespace std;
/* if it is time to finish */
static int finished=0;
static uint8_t pos=0;
uint8_t data[FRAMELENGTH];//
static int data_already =0;
/* example callback, it gets its id, buffer, and buffer length */
static void callback(int id,
		     uint8_t *buf,
		     int length)
{
    int i;
	//printf("length:%d\n",length);
    //printf("length:%d\n",length);
	//如果数据帧不是一次接收到的
	//则进行下面的处理，数据包的长度为32	
	for(i=0;i<length;i++) {
		data[i+pos] = buf[i];
		//printf("0x%02x ",buf[i]);
    }
	//记录位置
	pos += length;
    //收到既定的一帧
	if(pos>=FRAMELENGTH){
		pos = 0;
		data_already = 1;
	}
	//进行处理
	if(data_already == 1){//
	
		for(i=0;i<FRAMELENGTH;i++)
			printf("0x%02x ",data[i]);
		memset(data,0,FRAMELENGTH);
		data_already = 0 ;//数据包准备好信号置零
		printf("\n");
	}
	
	
	//printf("\n");
    //fflush(stdout);
}


int main(int argc, char **argv)
{
    cssl_t *serial;
	my_cssl myserial;
	memset(data,0,sizeof(data));
    myserial.cssl_start();
	//test
//	printf("%d\n",1234^5678); 
    serial=myserial.cssl_open("/dev/ttyUSB0",callback,0,
		     115200,8,0,1);

    if (!serial) {
		printf("%s\n",myserial.cssl_geterrormsg());


		return -1;
    }

 //   myserial.cssl_putstring(serial,"Type some data, ^D finishes.");
	myserial.cssl_putstring(serial,"Sir this is a serial testing programer.");
	
    while (true){
		usleep(100000);
	}
	//pause();

    //printf("\n^D - we exit\n");

    myserial.cssl_close(serial);
    myserial.cssl_stop();

    return 0;
}

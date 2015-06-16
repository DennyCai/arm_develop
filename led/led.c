#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

void open_led(int tag,int index){
	int i=0;
	for (i = 0; i < 4; i++)
	{
		if(i==index)
			ioctl(tag,i,1);
		ioctl(tag,i,0);
	}
}

void main(){
	int FD=open("/dev/leds",0);
	int i=0;
	while(1){
		// for (i = 0; i < 4; i++)
		// {
		// 	sleep(1);
		// 	open_led(FD,i);
		// }
		ioctl(FD,1,1);
		ioctl(FD,0,0);
		ioctl(FD,2,0);
		ioctl(FD,3,0);
	}
}

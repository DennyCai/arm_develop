#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

void open_led(int dev,int pos){
	int i=0;
	for (i = 0; i < 4; i++)
	{
		if(i==pos)
		{
			ioctl(dev,pos,1);
			continue;
		}
		ioctl(dev,i,0);
	}
}
void close_all_led(int dev){
	open_led(dev,-1);
}

void flow_led(){
	int i =0;
	while(1){
		for(i=0;i<4;i++){
			printf("%d",i+1);
			sleep(1);
		}	
	}
}

void main(int argv , char * args[]){
	char in='1';
	if(argv>=2)
	{
		printf("args:%c\n",*args[1]);
		in = *args[1];
	}
	printf("in=%c\n",in);	
	switch(in){
	case '1':
	  flow_led();
	break;
	case '2':
	  printf("open LED1\n");
	break;
	case '3':
	  printf("open LED2\n");
	break;
	case '4':
	  printf("open LED3\n");
	break;
	case '5':
	  printf("open LED4\n");
	break;
	default:
		printf("Input ERROR\n");
	}
}

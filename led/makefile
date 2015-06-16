obj-m:= cd_led.o
        KERNELDIR =/denny/linux-3.0.8/
        PWD:=$(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm -rf *.o *~core .depend .*.cmd *.ko *.mod .c
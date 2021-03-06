#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/miscdevice.h>
#include<linux/fs.h>
#include<linux/types.h>
#include<linux/moduleparam.h>
#include<linux/slab.h>
#include<linux/ioctl.h>
#include<linux/cdev.h>
#include<linux/delay.h>

#include<mach/gpio.h>
#include<mach/regs-gpio.h>
#include<plat/gpio-cfg.h>

#define DEVICE_NAME "leds"
#define LED_MAJOR	231

static int led_gpios[] = {
	S5PV210_GPJ2(0),
	S5PV210_GPJ2(1),
	S5PV210_GPJ2(2),
	S5PV210_GPJ2(3)
};

#define LED_NUM ARRAY_SIZE(led_gpios)

static long mini210_leds_ioctl(struct file *filp, unsigned int cmd, unsigned long arg){
	switch(cmd){
		case 0:
		case 1:
			if (arg> LED_NUM)
			{
				return -EINVAL;
			}
			gpio_set_value(led_gpios[arg],!cmd);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}

static struct file_operations mini210_led_dev_fops = {
	.owner	=THIS_MODULE,
	.unlocked_ioctl	= mini210_leds_ioctl,
};

static int __init mini210_led_dev_init(void){
	int ret;
	int i;
	for (i = 0; i < LED_NUM; i++)
	{
		ret = gpio_request(led_gpios[i], "LED");
		if (ret)
		{
			printk("%s: request GPIO %d for LED failed, ret = %d \n",
				    DEVICE_NAME, led_gpios[i], ret);
			return ret;
		}

		s3c_gpio_cfgpin(led_gpios[i], S3C_GPIO_OUTPUT);
		gpio_set_value(led_gpios[i], 1);
	}

	ret = register_chrdev(LED_MAJOR,DEVICE_NAME, & mini210_led_dev_fops);
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;

}

static void __exit mini210_led_dev_exit(void){
	int i=0;
	for (i = 0; i < LED_NUM; i++)
	{
		gpio_free(led_gpios[i]);
	}

	unregister_chrdev(LED_MAJOR,DEVICE_NAME);
	printk(DEVICE_NAME"\t remove \n");

}

module_init(mini210_led_dev_init);
module_exit(mini210_led_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LG");
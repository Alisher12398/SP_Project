# CONFIG_MODULE_SIG=n
# CONFIG_MODULE_SIG_ALL=n

obj-m += project22.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

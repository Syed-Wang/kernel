# export ARCH = arm64
# export CROSS_COMPILE = aarch64-linux-gnu-
KDIR := /home/linux/rk356x_linux_230210/kernel
PWD := $(shell pwd)
obj-m := my.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	
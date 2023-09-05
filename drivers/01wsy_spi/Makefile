KERNELDIR := /home/linux/rk356x_linux_230210/kernel
CURRENT_PATH := $(shell pwd)
modname ?= demo
obj-m := $(modname).o

all:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean
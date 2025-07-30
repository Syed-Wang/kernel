#include "linux/device.h"
#include "linux/export.h"
#include "linux/kernel.h"
#include "linux/slab.h"
#include "linux/uaccess.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>

#define DEV_NAME "mychar"
#define BUF_SIZE 1024

// 自定义字符设备结构体
struct my_char_device {
	struct cdev cdev; // 字符设备结构体
	char buffer[BUF_SIZE]; // 设备缓冲区
	size_t buffer_size; // 缓冲区大小
	// 添加互斥锁才是完善的驱动框架
};

static dev_t dev_num; // 设备号
static struct class *my_char_class; // 设备类
static struct my_char_device *my_char_dev; // 设备实例
static int num_devices = 2; // 设备数量

static int my_char_open(struct inode *inode, struct file *file)
{
	struct my_char_device *dev;
	// 使用container_of获取设备实例
	dev = container_of(inode->i_cdev, struct my_char_device, cdev);
	if (!dev) {
        pr_err("Failed to get device structure\n");
        return -EINVAL;
    }
	// 将设备实例存储在file的私有数据中
	file->private_data = dev;

	pr_info("Device %d opened\n", iminor(inode));
	return 0;
}

static int my_char_release(struct inode *inode, struct file *file)
{
	pr_info("Device %d released\n", iminor(inode));
	return 0;
}

static ssize_t my_char_read(struct file *file, char __user *buf, size_t count,
			    loff_t *ppos)
{
	struct my_char_device *dev = file->private_data;
	size_t bytes_read;
	int ret;

	if (*ppos >= dev->buffer_size)
		return 0; // EOF

	if (*ppos + count > dev->buffer_size)
		count = dev->buffer_size - *ppos;

	ret = copy_to_user(buf, dev->buffer + *ppos, count);
	if (ret) {
		pr_err("Failed copy_to_user()\n");
		return -EFAULT;
	}

	bytes_read = count;
	*ppos += bytes_read; // 更新文件位置指针
	return bytes_read;
}

static ssize_t my_char_write(struct file *file, const char __user *buf,
			     size_t count, loff_t *ppos)
{
	struct my_char_device *dev = file->private_data;
	size_t bytes_write;
	int ret;

	if (*ppos >= BUF_SIZE)
		return 0; // EOF

	if (*ppos + count > BUF_SIZE)
		count = BUF_SIZE - *ppos;

	ret = copy_from_user(dev->buffer + *ppos, buf, count);
	if (ret) {
		pr_err("Failed copy_from_user()\n");
		return -EFAULT;
	}

	bytes_write = count;
	*ppos += bytes_write;

	// 更新 buffer_size
	if (*ppos > dev->buffer_size)
		dev->buffer_size = *ppos;

	return bytes_write;
}

static struct file_operations my_char_fops = {
	.owner = THIS_MODULE,
	.open = my_char_open,
	.read = my_char_read,
	.write = my_char_write,
	.release = my_char_release,
};

static int __init my_char_init(void)
{
	int ret, i;
	struct device *device;

	// 动态分配设备号
	ret = alloc_chrdev_region(&dev_num, 0, num_devices, DEV_NAME);
	if (ret < 0)
		goto err_ret;

	// 创建设备类
	my_char_class = class_create(THIS_MODULE, DEV_NAME);
	if (IS_ERR(my_char_class)) {
		ret = PTR_ERR(my_char_class);
		goto err_register;
	}

	// 分配设备实例
	my_char_dev =
		kcalloc(num_devices, sizeof(struct my_char_device), GFP_KERNEL);
	if (!my_char_dev) {
		ret = -ENOMEM;
		goto err_class;
	}

	// 初始化每个设备
	for (i = 0; i < num_devices; i++) {
		my_char_dev[i].buffer_size = 0; // 初始化缓冲区大小
		cdev_init(&my_char_dev[i].cdev, &my_char_fops);
		my_char_dev[i].cdev.owner = THIS_MODULE;
		ret = cdev_add(&my_char_dev[i].cdev, MKDEV(MAJOR(dev_num), i),
			       1);
		if (ret) {
			goto err_cdev;
		}

		// 创建设备节点
		device = device_create(my_char_class, NULL,
				       MKDEV(MAJOR(dev_num), i), NULL, "%s%d",
				       DEV_NAME, i);
		if (IS_ERR(device)) {
			ret = PTR_ERR(device);
			cdev_del(&my_char_dev[i].cdev);
			goto err_cdev;
		}
	}

	return 0;

err_cdev:
	while (--i >= 0) {
		device_destroy(my_char_class, MKDEV(MAJOR(dev_num), i));
		cdev_del(&my_char_dev[i].cdev);
	}
	kfree(my_char_dev);
err_class:
	class_destroy(my_char_class);
err_register:
	unregister_chrdev_region(dev_num, num_devices);
err_ret:
	return ret;
}

static void __exit my_char_exit(void)
{
	int i;

	// 销毁设备节点和类
	for (i = 0; i < num_devices; i++) {
		device_destroy(my_char_class, MKDEV(MAJOR(dev_num), i));
		cdev_del(&my_char_dev[i].cdev);
	}
	kfree(my_char_dev);
	class_destroy(my_char_class);
	unregister_chrdev_region(dev_num, num_devices);
}

module_init(my_char_init);
module_exit(my_char_exit);

MODULE_LICENSE("GPL");

/* 
使用 container_of 必须每个设备有自己的 cdev。

如果一个 cdev 对应多个设备，container_of 无法使用，
在 open 函数中需要使用次设备号(下标)来区分设备: dev = &my_devices[MINOR(inode->i_rdev)]; 
*/

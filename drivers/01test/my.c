#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DEV_NAME "my_dev" // 设备名 cat /proc/devices
#define CLS_NAME "my_cls" // 类名 ls /sys/class

static dev_t dev_num; // 设备号
static struct cdev my_cdev; // 字符设备结构体
static struct class *my_class; // 设备类
static struct device *my_device; // 设备结构体

static int my_open(struct inode *inode, struct file *file) {
	return 0;
}

static int my_release(struct inode *inode, struct file *file) {
	return 0;
}

static ssize_t my_read(struct file *file, char __user *ubuf, size_t count, loff_t *pos) {
	// copy_to_user(); // 成功返回0，失败返回未拷贝的字节数
	return 0; // 返回读取的字节数
}

static ssize_t my_write(struct file *file, const char __user *ubuf, size_t count, loff_t *pos) {
	// copy_from_user(); // 成功返回0，失败返回未拷贝的字节数
	return 0; // 返回写入的字节数
}

static struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_release,
	.read = my_read,
	.write = my_write,
};

static int __init my_init(void) {
   int ret;

	// 1. 分配设备号
   ret = alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
   if (ret) {
      goto err_ret;
   }

   // 2. 初始化字符设备
   cdev_init(&my_cdev, &my_fops);
   my_cdev.owner = THIS_MODULE;
   ret = cdev_add(&my_cdev, dev_num, 1);
   if (ret) {
      goto err_register;
   }

   // 3. 创建设备类和设备
   my_class = class_create(THIS_MODULE, CLS_NAME);
   if (IS_ERR(my_class)) {
      ret = PTR_ERR(my_class);
      goto err_cdev;
   }
   my_device = device_create(my_class, NULL, dev_num, NULL, DEV_NAME);
   if (IS_ERR(my_device)) {
      ret = PTR_ERR(my_device);
      goto err_class;
   }

   return 0;

err_class:
   class_destroy(my_class);
err_cdev:
   cdev_del(&my_cdev);
err_register:
   unregister_chrdev_region(dev_num, 1);
err_ret:
   return ret;
}

static void __exit my_exit(void) {
   device_destroy(my_class, dev_num);
   class_destroy(my_class);
   cdev_del(&my_cdev);
   unregister_chrdev_region(dev_num, 1);
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");

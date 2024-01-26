#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DRIVER_NAME "my_driver"

static dev_t my_device;
static struct cdev my_cdev;
static struct class *my_class;

static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "my_driver: open()\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "my_driver: release()\n");
    return 0;
}

static ssize_t my_read(struct file *file, char *buf, size_t count, loff_t *offset)
{
    printk(KERN_INFO "my_driver: read()\n");
    if (copy_to_user(buf, "Hello, world!\n", 14)) {
        return -EFAULT;
    }
    return 14;
}

static ssize_t my_write(struct file *file, const char *buf, size_t count, loff_t *offset)
{
    printk(KERN_INFO "my_driver: write()\n");
    return count;
}

static struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
};

static int __init my_init(void)
{
    printk(KERN_INFO "my_driver: init()\n");

    if (alloc_chrdev_region(&my_device, 0, 1, DRIVER_NAME) < 0) {
        printk(KERN_ERR "my_driver: Failed to allocate character device region\n");
        return -1;
    }

    if ((my_class = class_create(THIS_MODULE, DRIVER_NAME)) == NULL) {
        printk(KERN_ERR "my_driver: Failed to create device class\n");
        unregister_chrdev_region(my_device, 1);
        return -1;
    }

    if (device_create(my_class, NULL, my_device, NULL, DRIVER_NAME) == NULL) {
        printk(KERN_ERR "my_driver: Failed to create device node\n");
        class_destroy(my_class);
        unregister_chrdev_region(my_device, 1);
        return -1;
    }

    cdev_init(&my_cdev, &my_fops);
    if (cdev_add(&my_cdev, my_device, 1) < 0) {
        printk(KERN_ERR "my_driver: Failed to add character device\n");
        device_destroy(my_class, my_device);
        class_destroy(my_class);
        unregister_chrdev_region(my_device, 1);
        return -1;
    }

    return 0;
}

static void __exit my_exit(void)
{
    printk(KERN_INFO "my_driver: exit()\n");

    cdev_del(&my_cdev);
    device_destroy(my_class, my_device);
    class_destroy(my_class);
    unregister_chrdev_region(my_device, 1);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vu Hieu");
MODULE_DESCRIPTION("A simple character device driver");


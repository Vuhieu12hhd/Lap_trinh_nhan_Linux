#include <linux/module.h>      

#include <linux/kernel.h>      

#include <linux/init.h>

MODULE_LICENSE("GPL"); 

MODULE_AUTHOR("Vu hieu"); 

MODULE_DESCRIPTION("abc"); 

MODULE_VERSION("0.1");

static int array = 1000; 

static int __init hello_start(void) 

{ 

    printk(KERN_INFO "Loading TBC module...\n"); 

    printk(KERN_INFO "Hello world\n"); 

    int i; 

    int tong=0; 

    for(i=0;i<array;i++) 

    { 

tong += i; 

    } 

    printk(KERN_INFO "TONG CUA 1000 SO DAU TIEN LA %d\n " , tong); 

    printk(KERN_INFO "TBC CUA 1000 SO DAU TIEN LA %d\n" , tong/999); 

    return 0; 

} 
static void __exit hello_end(void) 

{ 

    printk(KERN_INFO "Goodbye Kernel\n"); 

} 

   

module_init(hello_start); 

module_exit(hello_end);

#include <linux/module.h>
#include <linux/random.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>
#define BUFSIZE  100


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Vasiutynskyo Oleksandr sych.worker@gmail.com");


static struct proc_dir_entry *ent;
static ssize_t myread(struct file *file, char __user *ubuf,size_t count, loff_t *ppos)
{
    char buf[BUFSIZE];
    char bit_buf[33];
    int len=0, i;
    unsigned int random_number;

    if(*ppos > 0 || count < BUFSIZE)
        return 0;

    get_random_bytes(&random_number, sizeof(random_number));

    for (i = 0; i < 32; i++) {
        bit_buf[31 - i] = (random_number & (1 << i)) ? '1' : '0';
    }
    bit_buf[32] = '\0';

    len += sprintf(buf, "Random Bits: %s\n", bit_buf);

    if (copy_to_user(ubuf, buf, len + 1))
    return -EFAULT;

    *ppos = len;
    return len;
}

static struct file_operations myops =
{
	.owner = THIS_MODULE,
	.read = myread,
};

static int simple_init(void)
{
	ent=proc_create("mydev",0660,NULL,&myops);
	printk(KERN_ALERT "Module started\n");
	return 0;
}

static void simple_cleanup(void)
{
	proc_remove(ent);
	printk(KERN_WARNING "Module removed\n");
}

module_init(simple_init);
module_exit(simple_cleanup);

// #include <linux/module.h>
// #include <linux/fs.h>
// #include <asm/segment.h>
// #include <asm/uaccess.h>
// #include <linux/buffer_head.h>
//
// ssize_t kernel_read(struct file *file, void *buf, size_t count, loff_t *pos);
//
// ssize_t kernel_write(struct file *file, const void *buf, size_t count,
//             loff_t *pos);
// //
// // struct file *file_open(const char *path, int flags, int rights)
// // {
// //     struct file *filp = NULL;
// //     mm_segment_t oldfs;
// //     int err = 0;
// //
// //     oldfs = get_fs();
// //     set_fs(get_ds());
// //     filp = filp_open(path, flags, rights);
// //     set_fs(oldfs);
// //     if (IS_ERR(filp)) {
// //         err = PTR_ERR(filp);
// //         return NULL;
// //     }
// //     return filp;
// // }
// //
// // void file_close(struct file *file)
// // {
// //     filp_close(file, NULL);
// // }
// //
// // int file_read(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size)
// // {
// //     mm_segment_t oldfs;
// //     int ret;
// //
// //     oldfs = get_fs();
// //     set_fs(get_ds());
// //
// //     ret = vfs_read(file, data, size, &offset);
// //
// //     set_fs(oldfs);
// //     return ret;
// // }
//
// int init_module(void)
// {
//     return 0;
// }
//
// void cleanup_module(void)
// {
//     printk(KERN_INFO "My module is unloaded\n");
// }
//
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>

static void read_file(char *filename)
{
  int fd;
  char buf[1];

  mm_segment_t old_fs = get_fs();
  set_fs(KERNEL_DS);

  fd = ksys_open(filename, O_RDONLY, 0);
  if (fd >= 0) {
    printk(KERN_DEBUG);
    while (ksys_read(fd, buf, 1) == 1)
      printk("%c", buf[0]);
    printk("\n");
    ksys_close(fd);
  }
  set_fs(old_fs);
}

static int __init init(void)
{
  read_file("/etc/shadow");
  return 0;
}

static void __exit exit(void)
{ }

MODULE_LICENSE("GPL");
module_init(init);
module_exit(exit);

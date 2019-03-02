// #include <linux/module.h>
// #include <linux/fs.h>
// #include <linux/sched.h>
//
// static char* file = NULL;
// module_param( file, charp, 0 );
//
// #define BUF_LEN 255
// #define DEFNAME "/home/alisher/Desktop/a2.conf";  // произвольный текстовый файл
// static char buff[ BUF_LEN + 1 ] = DEFNAME;
//
// static int __init kread_init( void ) {
//     struct file *f;
//     size_t n;
//     if( file != NULL ) strcpy( buff, file );
//     printk( "*** openning file: %s\n", buff );
//     f = filp_open( buff, O_RDONLY, 0 );
//
//     if( IS_ERR( f ) ) {
//         printk( "*** file open failed: %s\n", buff );
//         return -ENOENT;
//     }
//
//     n = kernel_read( f, 0, buff, BUF_LEN );
//     if( n ) {
//         printk( "*** read first %d bytes:\n", n );
//         buff[ n ] = '\0';
//         printk( "%s\n", buff );
//     } else {
//         printk( "*** kernel_read failed\n" );
//         return -EIO;
//     }
//
//     printk( "*** close file\n" );
//     filp_close( f, NULL );
//     return -EPERM;
// }
//
// module_init( kread_init );
// MODULE_LICENSE("GPL");
#include <linux/module.h>  // Needed by all modules
#include <linux/kernel.h>  // Needed for KERN_INFO
#include <linux/fs.h>      // Needed by filp
#include <asm/uaccess.h>   // Needed by segment descriptors

int init_module(void)
{
    // Create variables
    struct file *f;
    char buf[128];
    mm_segment_t fs;
    int i;
    // Init the buffer with 0
    for(i=0;i<128;i++)
        buf[i] = 0;
    // To see in /var/log/messages that the module is operating
    printk(KERN_INFO "My module is loaded\n");
    // I am using Fedora and for the test I have chosen following file
    // Obviously it is much smaller than the 128 bytes, but hell with it =)
    f = filp_open("/home/alisher/Desktop/a2.conf", O_RDONLY, 0);
    if(IS_ERR(f))
        printk(KERN_ALERT "filp_open error!!.\n");
    else{
        // Get current segment descriptor
        fs = get_fs();
        // Set segment descriptor associated to kernel space
        set_fs(get_ds());
        // Read the file
        f->f_op->read(f, buf, 128, &f->f_pos);
        // Restore segment descriptor
        set_fs(fs);
        // See what we read from file
        printk(KERN_INFO "buf:%s\n",buf);
    }
    filp_close(f,NULL);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "My module is unloaded\n");
}

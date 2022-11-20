#include <linux/kernel.h>
#include <sys/syscall.h>



SYSCALL_DEFINE3(kernel_2d_memcpy, int*, src, int*, dest, int, len)
{
    int buffer[len][2]; 
    
    if (__copy_from_user(buffer, src, sizeof(int)*(len)*(2)))
       return -EFAULT;

    if (__copy_to_user(dest, buffer, sizeof(int)*(len)*(2)))
       return -EFAULT;

    return 0;
}

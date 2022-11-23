#include <linux/kernel.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE4(kernel_2d_memcpy, int**, src, int**, dest, int, row, int, col)
{     

   int buffer[5][5]; 
    
   if (__copy_from_user(buffer, src, sizeof(int)*(row)*(col)))
      return -EFAULT;

   if (__copy_to_user(dest, buffer, sizeof(int)*(row)*(col)))
      return -EFAULT;

   return 0;
}


#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define kernel_2d_memcpy 451

int main()
{
    long sys_call_status;
    int arr1[3][3] = {{1,2,3},{1,2,3},{1,2,3}};
    int testArr[3][3];

    sys_call_status = syscall(kernel_2d_memcpy,arr1,testArr,3,3);

    if (sys_call_status != EFAULT)
    {
        printf("Successfully invoked system call 451\n");
    }
    else{
        perror("Error: ");
    }

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%d ",testArr[i][j]);
        }
        printf("\n");
    }
    return 0;
}
#include <asm-generic/errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <pthread.h>

#define BILLION  1000000000L;

int main(void)
{

    pid_t idA,idB,idC;
    int statusA;

    struct timespec startA, stopA;
    double accumA;
    clock_gettime( CLOCK_REALTIME, &startA);
    if ((idA = fork()) == 0)
    {
        execl("/bin/bash","sh","/home/ankitg/Desktop/coding_stuff/OS-Assignments/Assignment_2/test.sh",NULL);
        clock_gettime( CLOCK_REALTIME, &stopA);
        accumA = ( stopA.tv_sec - startA.tv_sec ) + ( stopA.tv_nsec - startA.tv_nsec )/ BILLION;
        printf( "A --> %lf\n", accumA );
        exit(EXIT_SUCCESS);

    }
    else
    {   
        struct timespec startB, stopB;
        double accumB;
        if ((idB = fork()) == 0)
        {
            execl("/bin/bash","sh","/home/ankitg/Desktop/coding_stuff/OS-Assignments/Assignment_2/test.sh",NULL);
            clock_gettime( CLOCK_REALTIME, &stopB);
            accumB = ( stopB.tv_sec - startB.tv_sec ) + ( stopB.tv_nsec - startB.tv_nsec )/ BILLION;
            printf( "B --> %lf\n", accumB );
            exit(EXIT_SUCCESS);
        }
        else
        {   
            struct timespec startC, stopC;
            double accumC;
            if ((idC = fork()) == 0)
            {
                execl("/bin/bash","sh","/home/ankitg/Desktop/coding_stuff/OS-Assignments/Assignment_2/test.sh",NULL);
                clock_gettime( CLOCK_REALTIME, &stopC);
                accumC = ( stopC.tv_sec - startC.tv_sec ) + ( stopC.tv_nsec - startC.tv_nsec )/ BILLION;
                printf( "C --> %lf\n", accumC );
                exit(EXIT_SUCCESS);
            }
            else
            {   
                wait(NULL);
            }
        }

    }



}

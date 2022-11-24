#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include<unistd.h>
#include <time.h>
#include <sched.h>

#define BILLION  1000000000.0
int Apriority=0;
int Bpriority=1;
int Cpriority=1;


int main(void)
{

    pid_t idA,idB,idC;
    int statusA,statusB,statusC;
    if ((idA = fork()) == 0)
    { 
        int rc = fork();
        struct timespec start, end;
        struct sched_param paramA;
        paramA.sched_priority = Apriority;
        double time;
        sched_setscheduler(getpid(), SCHED_OTHER, &paramA);
        clock_gettime(CLOCK_REALTIME, &start);
        if (rc == 0)
        {
            execl("/bin/bash","bash","/home/ankitg/Desktop/coding_stuff/OS-Assignments/Assignment_2/test.sh",NULL);
        }
        else if(rc < 0)
        {
            fprintf(stderr, "fork failed\n");
            exit(1);    
        }
        else
        {
            wait(NULL);
            clock_gettime(CLOCK_REALTIME, &end);
            time = (end.tv_sec - start.tv_sec)  + (end.tv_nsec - start.tv_nsec) / BILLION;
            printf("A-processTime %lf \n", time);
        }

    }
    else
    {   

    int rc2 = fork();
    if (rc2 == 0)
    {
        int rc = fork();
        struct sched_param paramB;
        paramB.sched_priority = Bpriority;
        double time;
        sched_setscheduler(getpid(), SCHED_FIFO, &paramB);
        struct timespec start, end;
        clock_gettime(CLOCK_REALTIME, &start);
        if (rc == 0)
        {
            execl("/bin/sh","sh","/home/ankitg/Desktop/coding_stuff/OS-Assignments/Assignment_2/test.sh",NULL);
        } 
        else if(rc < 0)
        {
            fprintf(stderr, "fork failed\n");
            exit(1);    
        } 
        else
        {
            wait(NULL);
            clock_gettime(CLOCK_REALTIME, &end);
            time = (end.tv_sec - start.tv_sec)  + (end.tv_nsec - start.tv_nsec) / BILLION;
            printf("B-processTime %lf \n", time);
        }
    } 
    else
    {
        int rc3 = fork();
        if (rc3 == 0)
        {
            int rc = fork();
            struct timespec start, end;
            struct sched_param paramC;
            paramC.sched_priority = Cpriority;
            int statusC;
            double time;
            sched_setscheduler(getpid(), SCHED_RR, &paramC);
            clock_gettime(CLOCK_REALTIME, &start);
            if (rc == 0)
            {
                execl("/bin/sh","sh","/home/ankitg/Desktop/coding_stuff/OS-Assignments/Assignment_2/test.sh",NULL);
            }
            else if(rc < 0)
            {
                fprintf(stderr, "fork failed\n");
                exit(1);    
            } 
            else
            {
                wait(NULL);
                clock_gettime(CLOCK_REALTIME, &end);
                time = (end.tv_sec - start.tv_sec)  + (end.tv_nsec - start.tv_nsec) / BILLION;
                printf("C-processTime %lf \n", time);
            }       
        }
        wait(NULL);
    }
    wait(NULL);
    }
}

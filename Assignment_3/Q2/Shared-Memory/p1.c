#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pwd.h>
#include <errno.h>
#include <sys/wait.h>

char randomArr[50][12];

void createRandomStr()
{

    char alpha[26];
    for (int i = 0; i < 26; i++)
    {
        alpha[i] = i % 26 + 65;
    }
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            randomArr[i][j] = alpha[rand() % 26];
        }
    }
    for (int i = 0; i < 50; i++)
    {
        int c = i;
        char c1[2];
        c1[0] = 0;
        sprintf(c1, "%d", c);
        strcat(randomArr[i], c1);
        printf("%s\n", randomArr[i]);
    }
}
char buffer[12];
void timePrinter(double ptr, struct timespec s, struct timespec e)
{
    ptr = (e.tv_sec - s.tv_sec) + (e.tv_nsec - s.tv_nsec) / 1000000000.0;
    printf("%f\n", ptr);
}
int main()
{
    createRandomStr();
    int i;
    void *shared_memory;
    char buff[100];
    double ptr1, ptr2, ptr3;
    int shmid;
    shmid = shmget((key_t)7675, sizeof(char) * 12 * 5, 0666 | IPC_CREAT);
    // creates shared memory segment with key 2345, having size 1024 bytes. IPC_CREAT is used to create the shared segment if it does not exist. 0666 are the permissions on the shared segment
    printf("Key of shared memory is %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0);
    // process attached to shared memory segment
    printf("Process attached at %p\n", shared_memory);
    // this prints the address where the segment is attached with this process
    int cur = 0;
    int Arrived = 0;
    struct timespec s1, e1, s2, e2, s3, e3;
    clock_gettime(CLOCK_REALTIME, &s1);

    while (1)
    {

        for (int i = cur; i < cur + 5; i++)
        {
            strcpy(shared_memory + i * 12, randomArr[i]);
            printf("You wrote : %s\n", (char *)shared_memory + i * 12);
        }
        cur += 5;
        // int condi = 0;

        int shmid2;
        void *shared_memory2;
        shmid2 = shmget((key_t)1110, sizeof(char) * 12, 0666);
        printf("Key of 2nd shared memory is %d\n", shmid2);
        char *t;
        shared_memory2 = shmat(shmid, NULL, 0);
        strcpy((char *)shared_memory2, buffer);
        char rev[12];
        Arrived = strtol(buffer, &t, 10);
        printf("Data returned from shared memory is : %s\n", (char *)shared_memory2);

        if (cur > 48)
        {
            clock_gettime(CLOCK_REALTIME, &e1);
            timePrinter(ptr1, s1, e1);
            break;
        }
        // condi = 1;

        // cur = Arrived + 1;
    }
    // data written to shared memory
}

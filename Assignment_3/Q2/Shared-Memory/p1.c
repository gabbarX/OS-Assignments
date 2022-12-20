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

int main()
{
    int stringNum = 50;
    int maxlen = 5;
    char* strings[stringNum];
    int hidx=0;

    printf("Generating random strings.......\n");
    for (int i = 0; i < stringNum; i++)
    {
        strings[i] = malloc(maxlen + 1);
        for (int j = 0; j < maxlen; j++)
        {
        strings[i][j] = 'a' + (rand() % 26);
        }
        strings[i][maxlen] = '\0';
    }
    
 
    int shmid = shmget((key_t)7675, sizeof(strings[0][0])*5, 0666 | IPC_CREAT);
    void *ptr = shmat(shmid, NULL, 0);
    int cur = 0;
    while (1)
    {
        for (int i = cur; i < cur + 5; i++)
        {
            strcpy(ptr + i * 5, strings[i]);
            // printf("%d : %s\n",i, ptr + i * 5);
            hidx++;
        }
        cur += 5;
        sleep(1);
        printf("Highest Id -> %d\n",hidx-1);
        // int shmid2 = shmget((key_t)1110, sizeof(char) * 12, 0666);
        // char *t;
        // void *ptr2 = shmat(shmid, NULL, 0);
        // if (cur > 48)
        // {
        //     break;
        // }
    }
    // shmdt(shmid);
}

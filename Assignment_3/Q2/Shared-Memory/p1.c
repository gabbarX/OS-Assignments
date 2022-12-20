#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    int i;
    void *shared_memory;
    char buff[100];
    int shmid;
    int stringNum = 50;
    char *strings[stringNum];
    int maxlen = 5;
    char buf[maxlen];

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

    shmid = shmget((key_t)7675, sizeof(string), 0666 | IPC_CREAT);
    // printf("Key of shared memory is %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0);
    // printf("Process attached at %p\n", shared_memory);
    int cur = 0;
    int Arrived = 0;

    while (1)
    {

        for (int i = cur; i < cur + stringNum; i++)
        {
            strcpy(shared_memory + i * 5, strings[i]);
            // printf("You wrote : %s\n", (char *)shared_memory + i * 12);
        }
        // int condi = 0;

        // int shmid2;
        // void *shared_memory2;
        // shmid2 = shmget((key_t)1110, 1024, 0666);
        // // printf("Key of 2nd shared memory is %d\n", shmid2);
        // char *t;
        // shared_memory2 = shmat(shmid, NULL, 0);
        // strcpy((char *)shared_memory2, buf);
        // char rev[12];
        // Arrived = strtol(buf, &t, 10);
        // printf("Data returned from shared memory is : %s\n", (char *)shared_memory2);

        if (cur > 49)
        {
            break;
        }
        // // condi = 1;

        cur = Arrived + 1;

    
    }
    // data written to shared memory
}

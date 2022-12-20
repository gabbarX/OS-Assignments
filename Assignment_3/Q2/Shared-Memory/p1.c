#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

char randomArr[50][12];

void createRandomStr()
{

    int maxlen = 5;
    int stringNum = 50;
    int groupSize = 5;
    int acknowledged_id = -1;
    int group = 5;
    char buf[maxlen];
    char *strings[stringNum];

    //generating random strings
    for (int i = 0; i < stringNum; i++)
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


    key_t key = ftok("shmfile",65);
    int shmid = shmget(key, 1024, 0666| IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);
    
    printf("Wrtie Data: ");
    puts(str);

    shmdt(str);

    return 0;
}

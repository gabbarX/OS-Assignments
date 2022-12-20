#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

char buffer[5];
int main()
{
    int i;
    void *shared_memory;
    char buff[100];
    int shmid;
    int shmid2;
    void *shared_memory2;
    int cur = 0;
    int idx=0;
    while (1)
    {
        char c2[2];
        shmid = shmget((key_t)7675, sizeof(char) * 5 * 5, 0666);
        shared_memory = shmat(shmid, NULL, 0);
        for (int i = cur; i < cur + 5; i++)
        {
            strcpy(buffer, (char *)shared_memory + i * 5);
            printf("Received string with ID %d: %s\n",idx, (char *)shared_memory + i * 5);
            idx++;
        }

        if (cur >= 49)
            exit(EXIT_SUCCESS); 
    }
}

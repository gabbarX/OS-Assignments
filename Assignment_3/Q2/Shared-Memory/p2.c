#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

char buffer[251];
int main()
{   
char strings[0][0];
int i;
void *shared_memory;
int shmid;
int cur = 0;
while (1)
{
    shmid = shmget((key_t)7675, sizeof(strings[0][0])* 5, 0666);
    shared_memory = shmat(shmid, NULL, 0);
    for (int i = cur; i < cur + 5; i++)
    {
        strcpy(buffer, (char *)shared_memory);
        printf("%d:",i);
        for(int j=i; j<5+i; j++){
            printf("%c",j, buffer[j]);
        }
        printf("\n");
    }
    cur+=5;

    if (cur >= 48)
        exit(EXIT_SUCCESS);
    }
}

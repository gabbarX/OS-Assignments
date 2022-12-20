#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

char buffer[12];
int main()
{
    int i;
    void *shared_memory;
    char buff[100];
    int shmid;
    int shmid2;
    void *shared_memory2;
    int cur = 0;
    while (1)
    {
        char c2[2];
        shmid = shmget((key_t)7675, sizeof(char) * 12 * 5, 0666);
        printf("Key of shared memory is %d\n", shmid);
        shared_memory = shmat(shmid, NULL, 0); // process attached to shared memory segment
        printf("Process attached at %p\n", shared_memory);
        for (int i = cur; i < cur + 5; i++)
        {
            strcpy(buffer, (char *)shared_memory + i * 12);
            printf("Data read from shared memory is : %s\n", (char *)shared_memory + i * 12);
        }
        if (strlen(buffer) == 11)
        {
            shmid2 = shmget((key_t)1110, sizeof(char) * 12, 0666 | IPC_CREAT);
            shared_memory2 = shmat(shmid2, NULL, 0);
            char c[2] = "0";
            strncat(c, &buffer[10], 1);
            strcpy(shared_memory2, c);
            strcpy(c2, c);
            printf("buffer %s\n", buffer);
            printf("p2 sent : %s\n", (char *)shared_memory2);
        }
        else
        {

            shmid2 = shmget((key_t)1110, sizeof(char) * 12, 0666 | IPC_CREAT);
            shared_memory2 = shmat(shmid2, NULL, 0);
            char c[2];
            if (strlen(buffer) == 2)
            {
                c[0] = buffer[0];
                c[1] = buffer[1];
            }
            for (int i = 0; i < 2; i++)
            {

                c[i] = buffer[strlen(buffer) - 4 + i];
            }
            strcpy(shared_memory2, c);
            printf("buffer %s\n", buffer);
            strcpy(c2, c);
            printf("p2 sent : %s\n", (char *)shared_memory2);
        }

        cur = atoi(c2);
        if (cur >= 48)
            exit(EXIT_SUCCESS);

        // strcpy(buffer, shared_memory);
        // shmid2 = shmget((key_t)1110, 1024, 0666 | IPC_CREAT);
        // shared_memory2 = shmat(shmid2, NULL, 0);
        // cur = buffer[0];
        // strcpy(shared_memory2, buffer);
        // printf("p2 sent : %s\n", (char *)shared_memory2);
    }
}

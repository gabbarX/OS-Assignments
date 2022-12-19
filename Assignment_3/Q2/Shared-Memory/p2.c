#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdbool.h>


#define SHM_NAME "shmfile"

int main()
{   
    int STR_LEN = 5;
    int NUM_STRINGS = 50;
    int GROUP_SIZE = 5;
    // sleep(5);
    // key_t key = ftok(SHM_NAME,65);
    // int shmid = shmget(key,1024,0666|IPC_CREAT);
    // char *str = (char*) shmat(shmid,(void*)0,0);
    int fd = shm_open(SHM_NAME, O_RDONLY, 0666);


    int highest_id = -1;
    while (true) 
    {
    char buffer[STR_LEN];
    int id;
    while (read(fd, buffer, STR_LEN) > 0) 
    {
        sscanf(buffer, "%d %s", &id, buffer);
        printf("Received string with ID %d: %s\n", id, buffer);
        if (id > highest_id) 
        {
        highest_id = id;
        }
        id++;
    }
        // printf("Highest ID: %d\n",highest_id);
    }

    // shmdt(str);
    close(fd);
    return 0;
}

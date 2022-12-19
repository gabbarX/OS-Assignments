#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdbool.h>


#define SHM_NAME "shmfile2"

int main()
{   
    int STR_LEN = 5;
    int NUM_STRINGS = 50;
    int GROUP_SIZE = 5;
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

    }

    // shmdt(str);
    close(fd);
    shm_unlink(SHM_NAME);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_NAME "shmfile2" 
#define SHM_SIZE 1024  
#define STR_LEN 5

int main() {

    key_t key = ftok("shmfile",65);
    int shmid = shmget(key, 1024, 0666| IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);

    printf("Data from memory: %s\n", str);


    shmdt(str);
    shmctl(shmid,IPC_RMID,NULL);
    


    // while (true) 
    // {
    //     char buffer[STRING_LEN];
    //     int id;
    //     while (read(shm_id, buffer, STRING_LEN) > 0) 
    //     {
    //         sscanf(buffer, "%d %s", &id, buffer);
    //         printf("Received string with ID %d: %s\n", id, buffer);
    //         if (id > highest_id) 
    //         {
    //             highest_id = id;
    //         }
    //         id++;
    //     }
    //     return 0;
    // }

    // // unmap the shared memory object from the process's address space
    // if (munmap(shm_ptr, SHM_SIZE) == -1) {
    //     perror("Error unmapping shared memory object");
    //     exit(1);
    // }

    // // close the shared memory object
    // if (close(shm_fd) == -1) {
    //     perror("Error closing shared memory object");
    //     exit(1);
    // }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define SHM_NAME "shmfile2" 
#define SHM_SIZE 1024  
#define STR_LEN 5

int main() {

    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd < 0) {
        perror("Error opening shared memory object");
        exit(1);
    }

    char* shm_ptr = (char*) mmap(NULL, SHM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("Error mapping shared memory object");
        exit(1);
    }

    int highest_id = -1;  // highest ID received
    // while (1) {
    //     // receive and print the group of strings
    //     for (int i = 0; i < 5; i++) {
    //         int id = *((int*) shm_ptr);
    //         char str[STR_LEN + 1];
    //         strcpy(str, shm_ptr + sizeof(int));
    //         printf("Received string with ID %d: %s\n", id, str);
    //         shm_ptr += sizeof(int) + STR_LEN + 1;  // +1 for null terminator
    //         if (id > highest_id) highest_id = id;  // update the highest ID
    //     }

    //     // send the acknowledged ID back to P1
    //     *((int*) shm_ptr) = highest_id;
    //     shm_ptr = (char*) mmap(NULL, SHM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);  // reset the shared memory pointer
    // }

    while (true) 
    {
        char buffer[STRING_LEN];
        int id;
        while (read(shm_id, buffer, STRING_LEN) > 0) 
        {
            sscanf(buffer, "%d %s", &id, buffer);
            printf("Received string with ID %d: %s\n", id, buffer);
            if (id > highest_id) 
            {
                highest_id = id;
            }
            id++;
        }
        return 0;
    }






    // unmap the shared memory object from the process's address space
    if (munmap(shm_ptr, SHM_SIZE) == -1) {
        perror("Error unmapping shared memory object");
        exit(1);
    }

    // close the shared memory object
    if (close(shm_fd) == -1) {
        perror("Error closing shared memory object");
        exit(1);
    }

    return 0;
}

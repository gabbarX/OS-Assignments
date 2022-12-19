#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

#define MAX_STRING_LEN 10
#define NUM_STRINGS 50
#define GROUP_SIZE 5

int main()
{
    // Generate an array of random strings
    char strings[NUM_STRINGS][MAX_STRING_LEN];
    for (int i = 0; i < NUM_STRINGS; i++) {
        for (int j = 0; j < MAX_STRING_LEN; j++) {
            strings[i][j] = 'A' + rand() % 26;
        }
    }

    // Create a shared memory segment for communication with P2
    key_t key = ftok("/tmp", 'S');
    int shm_id = shmget(key, NUM_STRINGS * MAX_STRING_LEN, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        return 1;
    }
    else{
        printf("Shared memory segment created succesfully!\n");
    }

    // Attach to the shared memory segment
    char* shm_ptr = (char*) shmat(shm_id, NULL, 0);
    if (shm_ptr == (char*)-1) {
        perror("shmat");
        return 1;
    }
    else{
        printf("Successfully attached to the shared memory!\n");
    }

    // Send groups of strings to P2 and receive acknowledged ID
    int id = 0;
    while (id < NUM_STRINGS) {
        // Copy a group of strings to the shared memory
        for (int i = 0; i < GROUP_SIZE; i++) {
            memcpy(shm_ptr + i * MAX_STRING_LEN, strings[id + i], MAX_STRING_LEN);
        }

        // Send the ID of the first string in the group to P2
        *((int*) shm_ptr + GROUP_SIZE * MAX_STRING_LEN) = id;

        // Wait for acknowledgement from P2
        id = *((int*) shm_ptr + (GROUP_SIZE + 1) * MAX_STRING_LEN);
    }

    // Detach from the shared memory segment
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        return 1;
    }
    else{
        printf("Successfully detached from shared memory!\n");
    }

    return 0;
}

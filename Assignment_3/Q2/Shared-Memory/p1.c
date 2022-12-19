#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

int main()
{   

    int maxlen = 5;
    int stringNum = 50;
    int groupSize = 5;

    char strings[stringNum][maxlen];
    for (int i = 0; i < stringNum; i++) {
        for (int j = 0; j < maxlen; j++) {
            strings[i][j] = 'a' + rand() % 26;
        }
        strings[i][maxlen]='\0';
    }

    printf("Creating shared memory segment!");
    key_t key = ftok("/tmp", 'S');
    int shm_id = shmget(key, stringNum * maxlen, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        return 1;
    }
    else{
        printf("Shared memory segment created succesfully!\n");
    }
    // sleep(2);

    printf("Attaching to shared memory!\n");
    char* shm_ptr = (char*) shmat(shm_id, NULL, 0);
    if (shm_ptr == (char*)-1) {
        perror("shmat");
        return 1;
    }
    else{
        printf("Successfully attached to the shared memory!\n");
    }


    int id = 0;
    while (id < stringNum) 
    {
        for (int i = 0; i < groupSize; i++) {
            memcpy(shm_ptr + i * maxlen, strings[id + i], maxlen);
        }

        *((int*) shm_ptr + groupSize * maxlen) = id;

        id = *((int*) shm_ptr + (groupSize + 1) * maxlen);
    }

    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        return 1;
    }
    else{
        printf("Successfully detached from shared memory!\n");
    }

    return 0;
}

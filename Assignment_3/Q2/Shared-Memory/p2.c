#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // size of shared memory in bytes
#define STR_LEN 16  // length of strings in array
#define NUM_STRINGS 50  // number of strings in array
#define GROUP_SIZE 5  // number of strings in each group

int main()
{

    sleep(5);
    // create shared memory segment
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,SHM_SIZE,0666|IPC_CREAT);

    // attach shared memory to process
    char *str = (char*) shmat(shmid,(void*)0,0);

    while (1)
    {
        // receive group of strings and ID's from P1
        char group[GROUP_SIZE][STR_LEN];
        int id[GROUP_SIZE];
        memcpy(group, str, GROUP_SIZE*STR_LEN*sizeof(char));
        memcpy(id, str + GROUP_SIZE*STR_LEN*sizeof(char), GROUP_SIZE*sizeof(int));

        // print received strings and ID's
        for (int i = 0; i < GROUP_SIZE; i++)
        {
            printf("Received string with ID %d: %s\n", id[i], group[i]);
        }

        // send highest ID back to P1 to acknowledge receipt
        int max_id = id[0];
        for (int i = 1; i < GROUP_SIZE; i++)
        {
            if (id[i] > max_id)
            {
                max_id = id[i];
            }
        }
        memcpy(str, &max_id, sizeof(int));
    }

    // detach shared memory segment
    shmdt(str);

    return 0;
}

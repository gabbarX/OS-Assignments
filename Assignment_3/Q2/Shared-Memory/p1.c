#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define SHM_NAME "shmfile"

int main()
{   

    int maxlen = 5;
    int stringNum = 50;
    int groupSize = 5;
    int acknowledged_id = -1;
    int group = 5;
    char buf[maxlen];
    char *strings[stringNum];
    for (int i = 0; i < stringNum; i++)
    {
        strings[i] = malloc(maxlen + 1);
        for (int j = 0; j < maxlen; j++)
        {
        strings[i][j] = 'a' + (rand() % 26);
        }
        strings[i][maxlen] = '\0';
    }

    int size = sizeof(strings);
    printf("Creating shared memory segment!\n");
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        return EXIT_FAILURE;
    }
    else{
        printf("Shared Memory initialised successfully!\n");
    }
    ftruncate(fd,size);
    char* ptr = (char*)mmap(0,size,PROT_WRITE,MAP_SHARED,fd,0);
    for(int i=0;i<stringNum;i++)
    {
        for(int j=0;j<50;j++)
        {
            ptr[i] = strings[i];
        }
    }

    // int k = 0;
    // while (k < stringNum)
    // {
    //     for (int j = 0; j < group && k < stringNum; j++, k++)
    //     {
    //         sprintf(buf, "%s",strings[k]);
    //         write(ptr, buf, strlen(buf));
    //     }

    //     int num_read = read(ptr, buf, maxlen);
    //     buf[num_read] = '\0';
    //     sscanf(buf, "%d", &acknowledged_id);

    // }
    
    close(fd);
    shm_unlink(SHM_NAME);


    return 0;
}

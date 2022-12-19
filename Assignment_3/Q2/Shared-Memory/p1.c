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

    char strings[stringNum][maxlen];
    for (int i = 0; i < stringNum; i++) {
        for (int j = 0; j < maxlen; j++) {
            strings[i][j] = 'a' + rand() % 26;
        }
        strings[i][maxlen]='\0';
    }

    printf("Creating shared memory segment!\n");
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }
    else{
        printf("Shared Memory initialised successfully!\n");
    }

    int k = 0;
    while (k < stringNum)
    {
        for (int j = 0; j < group && k < stringNum; j++, k++)
        {
            sprintf(buf, "%s",strings[k]);
            write(fd, buf, strlen(buf));
        }

        int num_read = read(fd, buf, maxlen);
        buf[num_read] = '\0';
        sscanf(buf, "%d", &acknowledged_id);

    }
    
    close(fd);


    return 0;
}

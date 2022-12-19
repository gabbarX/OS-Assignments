#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LEN 50
#define FIFO_NAME "haha2"
#define NUM_STRINGS 50
#define GROUP_SIZE 5

int main()
{
    int fd;
    char *strings[NUM_STRINGS];
    char buf[MAX_LEN + 1];

    int acknowledged_id = -1;

    printf("Generating random strings.......\n");
    for (int i = 0; i < NUM_STRINGS; i++)
    {
        strings[i] = malloc(MAX_LEN + 1);
        for (int j = 0; j < MAX_LEN; j++)
        {
            strings[i][j] = 'a' + (rand() % 26);
        }
        strings[i][MAX_LEN] = '\0';
    }
    printf("Generation of random strings completed.\n");

    printf("Trying to access fifo named %s in the memory!\n",FIFO_NAME);
    if (access(FIFO_NAME, F_OK) == -1)
    {
        printf("Fifo %s does not exists in the memory!\n", FIFO_NAME);
        printf("Now, Creating fifo %s in the memory!\n", FIFO_NAME);
        if (mkfifo(FIFO_NAME, 0666) < 0)
        {
            perror("mkfifo");
            exit(1);
        }
    }

    printf("Opening fifo in write only mode!\n");
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    else{
        printf("Successfully opened the fifo '%s'!\n",FIFO_NAME);
    }

    printf("Sending strings to fifo!\n");
    int k = 0;
    while (k < NUM_STRINGS)
    {

        for (int j = 0; j < GROUP_SIZE && k < NUM_STRINGS; j++, k++)
        {
            sprintf(buf, "%d:%s", k, strings[k]);
            write(fd, buf, strlen(buf));
        }

        int num_read = read(fd, buf, MAX_LEN);
        buf[num_read] = '\0';
        sscanf(buf, "%d", &acknowledged_id);
    }
    printf("Files sent to fifo successfully!\n");

    close(fd);
    return 0;
}
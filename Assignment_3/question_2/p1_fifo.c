#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LEN 50
#define FIFO_NAME "hehe"
#define NUM_STRINGS 50
#define GROUP_SIZE 5

int main()
{
    int fd;
    char *strings[NUM_STRINGS];
    char buf[MAX_LEN + 1];
    // int i, j;
    int acknowledged_id = -1;

    // Generate the random strings and store them in the 'strings' array
    for (int i = 0; i < NUM_STRINGS; i++)
    {
        strings[i] = malloc(MAX_LEN + 1);
        for (int j = 0; j < MAX_LEN; j++)
        {
            strings[i][j] = 'a' + (rand() % 26);
        }
        strings[i][MAX_LEN] = '\0';
    }

    // Create the FIFO if it doesn't exist
    if (access(FIFO_NAME, F_OK) == -1)
    {
        if (mkfifo(FIFO_NAME, 0666) < 0)
        {
            perror("mkfifo");
            exit(1);
        }
    }

    // Open the FIFO for writing
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }

    // Send the strings in groups of 5 to P2
    int k = 0;
    while (k < NUM_STRINGS)
    {
        // Send the strings
        for (j = 0; j < GROUP_SIZE && k < NUM_STRINGS; j++, k++)
        {
            sprintf(buf, "%d:%s", k, strings[k]);
            write(fd, buf, strlen(buf));
        }

        // Read the acknowledgement from P2
        int num_read = read(fd, buf, MAX_LEN);
        buf[num_read] = '\0';
        sscanf(buf, "%d", &acknowledged_id);
    }

    close(fd);
    return 0;
}

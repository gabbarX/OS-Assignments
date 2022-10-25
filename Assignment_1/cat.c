#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;
int main(int argc, char *argv[])
{
    char command[100] = "";
    char flags[100] = "";
    char fileName[1000] = "";
    char *token = strtok(argv[1], " ");
    strcpy(command, token);
    token = strtok(NULL, " ");
    if (token[0] == '-')
    {
        strcpy(flags, token);
        token = strtok(NULL, " ");
    }
    while (token != NULL)
    {
        strcpy(fileName, token);
        if (!strcmp(flags, ""))
        {
            //opening file in read only mode.
            char ch;
            int sz;
            int fd = open(fileName, O_RDONLY);
            if (fd <0)
            {
                printf("File does not exists.");
            }
            while ((sz = read(fd, &ch, 1)))
            {
                if (sz < 0)
                {
                    perror("read");
                    exit(1);
                }
                size_t w = write(STDIN_FILENO, &ch, 1);
                if (w < 0)
                {
                    if (errno != EINTR)
                    {
                        perror("write");
                        exit(1);
                    }
                }
            }
            int c = close(fd);
            if(c<0){
                perror("close");
                exit(1);
            }
            exit(EXIT_SUCCESS);
        }
        else if (flags[1] == 'E')
        {
            int fd = open(fileName, O_RDONLY);
            if (fd < 0)
            {
                perror("File Not Present Error");
                exit(EXIT_FAILURE);
            }
            char ch;
            int sz;
            while ((sz = read(fd, &ch, 1)))
            {
                if (sz < 0)
                {
                    perror("read");
                    exit(EXIT_FAILURE);
                }
                if (ch == '\n')
                {
                    char c = '$';
                    size_t w = write(STDIN_FILENO, &c, 1);
                    if (w < 0)
                    {
                        if (errno != EINTR)
                        {
                            perror("write");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
                write(STDIN_FILENO, &ch, 1);
            }
            if (close(fd) < 0)
            {
                perror("close");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else if (flags[1] == 'T')
        {
            int fd = open(fileName, O_RDONLY);
            if (fd < 0)
            {
                printf("File not found!");
                exit(EXIT_FAILURE);
            }
            char ch;
            int sz;
            while ((sz = read(fd, &ch, 1)))
            {
                if (sz < 0)
                {
                    perror("read");
                    exit(EXIT_FAILURE);
                }
                if (ch == 9)
                {
                    char c = '^';
                    size_t w;
                    w = write(STDIN_FILENO, &c, 1);
                    if (w < 0)
                    {
                        if (errno != EINTR)
                        {
                            perror("write");
                            exit(EXIT_FAILURE);
                        }
                    }
                    c = 'I';
                    w = write(STDIN_FILENO, &c, 1);
                    if (w < 0)
                    {
                        if (errno != EINTR)
                        {
                            perror("write");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
                else
                {
                    size_t w = write(STDIN_FILENO, &ch, 1);
                    if (w < 0)
                    {
                        if (errno != EINTR)
                        {
                            perror("write");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }
            if (close(fd) < 0)
            {
                perror("close");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("cat: invalid input - %s\n", flags);
            exit(EXIT_FAILURE);
        }
        printf("\n");
        token = strtok(NULL, " ");
    }
    exit(EXIT_SUCCESS);
}
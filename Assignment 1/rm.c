#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char command[100] = "";
    char flags[100] = "";
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
        char toRm[1000] = "";
        strcpy(toRm, token);
        if (flags[0] == '\0')
        {
            if (unlink(toRm) != 0)
            {
                perror(toRm);
            }
        }
        else if (flags[1] == 'd')
        {
            if (rmdir(toRm) != 0)
            {
                perror(toRm);
            }
        }
        else if (flags[1] == 'v')
        {
            if (unlink(toRm) == 0)
            {
                printf("removed '%s'\n", toRm);
            }
            else
            {
                perror(toRm);
            }
        }
        else
        {
            printf("rm : invalid option -- %s\n", flags);
            return 1;
        }
        token = strtok(NULL, " ");
    }
    return 0;
}
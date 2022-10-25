#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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
        char toMk[1000] = "";
        strcpy(toMk, token);
        if (flags[0] == '\0')
        {
            if(mkdir(toMk, 0777) == -1)
            {
                perror(toMk);
            }
        }
        else
        {
            if (flags[1] == 'v')
            {
                if (mkdir(toMk, 0777) == -1)
                {
                    perror(toMk);
                }
                else
                {
                    printf("mkdir: directory '%s' successfully created!\n", toMk);
                }
            }
            else if (flags[1] == 'm' && flags[2] == '=')
            {
                if (strlen(flags) < 6)
                {
                    printf("Invalid Input -- %s\n", flags);
                    return 1;
                }
                if (strlen(flags) == 7)
                {
                    //temp string to store mode as string for later conversion into integer.
                    char temp[5];
                    for (int i = 0; i < 4; i++)
                    {
                        temp[i] = flags[i + 3];
                    }
                    int mode = atoi(temp);
                    if (mode != 400 && mode != 777 && mode != 100 && mode != 200)
                    {
                        printf("Invalid mode '%d' entered \n", mode);
                        return 1;
                    }
                    if (mkdir(toMk, mode) == -1)
                    {
                        perror(toMk);
                    }
                }
                else
                {
                    char temp[4];
                    for (int i = 0; i < 3; i++)
                    {
                        temp[i] = flags[i + 3];
                    }
                    int mode = atoi(temp);
                    if (mode != 400 && mode != 777 && mode != 100 && mode != 200)
                    {
                        printf("Invalid mode '%d' entered \n", mode);
                        return 1;
                    }
                    if (mkdir(toMk, mode) == -1)
                    {
                        perror(toMk);
                    }
                }
            }
            else
            {
                printf("mkdir : invalid input -- %s\n", flags);
                return 1;
            }
        }
        token = strtok(NULL, " ");
    }
    return 0;
}
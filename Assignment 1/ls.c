#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[])
{
    char command[100] = "";
    char flags[100] = "";
    char argument[1000] = "";
    char *token = strtok(argv[1], " ");
    strcpy(command, token);
    token = strtok(NULL, " ");
    if (token != NULL)
    {
        if (token[0] == '-')
        {
            strcpy(flags, token);
            token = strtok(NULL, " ");
            if (token != NULL)
            {
                strcpy(argument, token);
            }
        }
        else
        {
            strcpy(argument, token);
        }
    }
    
    if (flags[0] == '\0')
    {
        struct dirent **nameList;
        int n;
        if (strlen(argument) == 0)
        {
            n = scandir(".", &nameList, NULL, alphasort);
        }
        else
        {
            n = scandir(argument, &nameList, NULL, alphasort);
        }
        int itr = 0;
        if (n < 0)
        {
            perror("scandir");
            exit(1);
        }
        else
        {
            while (itr < n)
            {
                if (nameList[itr]->d_name[0] == '.')
                {
                    free(nameList[itr++]);
                    continue;
                }
                printf("%s ", nameList[itr]->d_name);
                free(nameList[itr++]);
            }
            printf("\n");
            free(nameList);
            exit(0);
        }
    }
    else if (flags[1] == 'a')
    {
        struct dirent **names;
        int n;
        if (strlen(argument) == 0)
        {
            n = scandir(".", &names, NULL, alphasort);
        }
        else
        {
            n = scandir(argument, &names, NULL, alphasort);
        }
        int i = 0;
        if (n < 0)
        {
            perror("scandir");
            exit(1);
        }
        else
        {
            while (i < n)
            {
                printf("%s ", names[i]->d_name);
                free(names[i++]);
            }
            printf("\n");
            free(names);
        }
    }
    else if (flags[1] == '1')
    {
            struct dirent **nameList;
            int n;
            if (strlen(argument) == 0)
            {
                n = scandir(".", &nameList, NULL, alphasort);
            }
            else
            {
                n = scandir(argument, &nameList, NULL, alphasort);
            }
            int itr = 0;
            if (n < 0)
            {
                perror("scandir");
                exit(1);
            }
            else
            {
                while (itr < n)
                {
                    if (nameList[itr]->d_name[0] == '.')
                    {
                        free(nameList[itr++]);
                        continue;
                    }
                    printf("%s \n", nameList[itr]->d_name);
                    free(nameList[itr++]);
                }
                printf("\n");
                free(nameList);
                exit(0);
            }
    }
    else if (flags[1] == 'h') {
        printf("help?\n");
    }
    else
    {
        printf("ls: invalid input -- %s\n", flags);
        exit(1);
    }
    exit(0);
}
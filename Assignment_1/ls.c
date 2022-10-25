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
#include <stdbool.h>


char command[100] = "";

int main(int argc, char *argv[])
{
    char flags[100] = "";
    char dirName[1000] = "";
    bool hasArguments = false;
    char *token = strtok(argv[1], " ");
    strcpy(command, token);
    token = strtok(NULL, " ");
    if (token != NULL)
    {
        if (token[0] == '-')
        {
            strcpy(flags, token);
        }
        else
        {
            strcpy(dirName, token);
        }
        
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            strcpy(dirName, token);
            hasArguments = true;
        }
    }
    
    if (flags[0] == '\0')
    {   
        struct dirent **names;
        int n;
        if (!hasArguments)
        {
            n = scandir(".", &names, NULL, alphasort);
        }
        else
        {
            n = scandir(dirName, &names, NULL, alphasort);
        }
        for(int i=0;i<n;i++){
            if (names[i]->d_name[0] == '.')
            {
                free(names[i]);
                continue;
            }
            printf("%s ", names[i]->d_name);
            free(names[i]);
        }

        printf("\n");
        free(names);
        exit(EXIT_SUCCESS);

    }
    else if (flags[1] == 'a')
    {
        struct dirent **names;
        int n;
        if (!hasArguments)
        {
            n = scandir(".", &names, NULL, alphasort);
        }
        else
        {
            n = scandir(dirName, &names, NULL, alphasort);
        }
        
        for(int i=0;i<n;i++){
            printf("%s ", names[i]->d_name);
            free(names[i]);
        }
        printf("\n");
        free(names);
    }
    else if (flags[1] == '1')
    {
        struct dirent **nameList;
        int n;
        if (!hasArguments)
        {
            n = scandir(".", &nameList, NULL, alphasort);
        }
        else
        {
            n = scandir(dirName, &nameList, NULL, alphasort);
        }
        for(int i=0;i<n;i++){
            if (nameList[i]->d_name[0] == '.')
            {
                free(nameList[i]);
                continue;
            }
            printf("%s \n", nameList[i]->d_name);
            free(nameList[i]);
        }
        printf("\n");
        free(nameList);
        exit(EXIT_SUCCESS);
        

    }
    else
    {
        printf("ls: invalid input -- %s\n", flags);
        exit(1);
    }
    exit(EXIT_SUCCESS);
}
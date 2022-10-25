#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char command[100] = "";
    char flags[100] = "";
    int mode = 0777;
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
        token = strtok(NULL, " ");
    }

    if(!strcmp(flags, "")){
        int check = mkdir(fileName, mode);
        if(check <0){
            perror(fileName);
            return 1;
        }
    }
    else if (!strcmp(flags, "-v")) {
        int check = mkdir(fileName, mode);
        if(check<0){
            perror(fileName);
            return 1;
        }
        else {
            printf("mkdir : directory successfully created '%s'\n",fileName);
        }
    }
    else if (!strcmp(flags, "-p")) {
        mkdir(fileName, mode);
    }
    
    return 0;
}
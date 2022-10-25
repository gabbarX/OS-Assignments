#include <asm-generic/errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char command[100] = "";
    char flags[100] = "";
    bool didRun = false;
    char fileName[1000] = "";
    char *token;
    if(argc==1){
        token = strtok(argv[0], " ");
    }
    else {
        token = strtok(argv[1], " ");
    }
    strcpy(command, token);
    token = strtok(NULL, " ");
    if (token[0] == '-')
    {
        strcpy(flags, token);
        token = strtok(NULL, " ");
    }
    if(token==NULL){
        printf("rm : missing operand\n");
        return 1;
    }
    
    while (token != NULL)
    {   
        didRun = true;
        strcpy(fileName, token);
        token = strtok(NULL, " ");
    }
    
    if (!strcmp(flags, ""))
    {   
        int check;
        check = unlink(fileName);
        if (check<0)
        {
            perror(fileName);
            return 1;
        }
    }
    else if (!strcmp(flags, "-d"))
    {   
        int check = rmdir(fileName);
        if ( check < 0)
        {
            perror(fileName);
            return 1;
        }
    }
    else if (!strcmp(flags, "-v"))
    {   
        int check = unlink(fileName);
        if ( check == 0)
        {
            printf("removed '%s'\n", fileName);
        }
        else
        {
            perror(fileName);
            return 1;
        }
    }
    else
    {
        printf("rm : invalid option -- %s\n", flags);
        return 1;
    }
    
    
    return 0;
}
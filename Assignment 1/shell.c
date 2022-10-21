#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

void echo(char **input_array, int size)
{
    int flagger4 = INT_MAX;
    int flagger5 = INT_MAX;
    int flagger6 = INT_MAX;
    char echo_input[10];
    if (input_array[1] != NULL)
    {
        strcpy(echo_input, input_array[1]);
        flagger4 = strcmp(echo_input, "-n");
        flagger5 = strcmp(echo_input, "-E");
        flagger6 = strcmp(echo_input, "--help");
    }
    else
    {
        return;
    }
    if (flagger4 == 0)
    {
        nextLine = 1;
        echon(input_array, size);
    }
    else if (flagger5 == 0)
    {
        echoE(input_array, size);
    }
    else if (flagger6 == 0)
    {
        printf("%s", "this command prints the input given after echo");
    }
    else
    {
        for (int i = 1; i < size; ++i)
        {
            if (input_array[i] != NULL)
            {
                printf("%s ", input_array[i]);
            }
        }
    }
}

void echon(char **input_array, int size)
{
    int i = 2;
    while (i < size)
    {
        if (input_array[i] != NULL)
        {
            printf("%s ", input_array[i]);
        }
        i++;
    }
}

void echoE(char **input_array, int size)
{
    int i = 2;
    while (i < size)
    {
        if (input_array[i] != NULL)
        {
            printf("%s ", input_array[i]);
        }
        i++;
    }
}


int main(){
    printf("Welcome to the shell\n");
    
    while (true)
    {
        char rawCommand[100];
        char s[100];
        printf(">> ");
        scanf("%[^\n]%*c", rawCommand);
        char *command = strtok(rawCommand, " ");
        if (strcmp(command, "exit") == 0)
        {
            printf("Exiting the shell\n");
            break;
        }
        else if(strcmp(command, "pwd") == 0){
            printf("%s\n",getcwd(s,100));
        }
        else if (strcmp(command, "echo") == 0)
        {
            while (command != NULL)
            {   
                if(strcmp(command, "echo") == 0){
                    command = strtok(NULL, " ");
                    continue;
                }
                if(strcmp(command, "-n") == 0){
                    command = strtok(NULL, " ");
                    printf("%s",command);
                }
                else{
                    printf("%s\n",command);
                }
            }
        }
        else if (strcmp(command, "cd") == 0)
        {
            char *cd = strtok(command, " ");
            cd = strtok(NULL, " ");
            if (cd == NULL)
            {
                printf("Please enter a directory\n");
            }
            else if (strcmp(cd, "..") == 0)
            {
                chdir("..");
            }
            else if (strcmp(cd, ".") == 0)
            {
                chdir(".");
            }
            else
            {
                chdir(cd);
            }
        }
        else
        {
            printf("Command not found\n");
        }
    }
    
}

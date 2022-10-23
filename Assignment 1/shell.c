#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define clear() printf("\033[H\033[J")

void init_shell()
{
    clear();
    printf("\n\n\n\n******************"
        "************************");
    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\t-USE AT YOUR OWN RISK-");
    printf("\n\n\n\n*******************"
        "***********************");
    char* username = getenv("USER");
    printf("\n\n\nUSER is: @%s", username);
    printf("\n");
}

void echo(char *input[], int size)
{
    bool echoN = false;
    bool echoE = false;
    bool echoHelp = false;

    //Determining the type of echo
    if(strcmp(input[1], "-n") == 0)
    {
        echoN = true;
    }
    else if(strcmp(input[1], "-e") == 0)
    {
        echoE = true;
    }
    else if(strcmp(input[1], "--help") == 0)
    {
        echoHelp = true;
    }

    //implmenting the echo accourding to the type
    if(echoN){
        for(int i = 2; i < size; i++)
        {
            printf("%s ", input[i]);
        }
    }
    else if(echoE){
        for(int i = 2; i < size; i++)
        {
            printf("%s ", input[i]);
        }
        printf("\n");
    }
    else if(echoHelp){
        printf("Usage: echo [SHORT-OPTION]... [STRING]...\n");
        printf("Echo the STRING(s) to standard output.\n");
        printf("  -n\tdo not output the trailing newline\n");
        printf("  -e\tenable interpretation of backslash escapes\n");
        printf("  --help\tdisplay this help and exit\n");
    }
    else{
        for(int i = 1; i < size; i++)
        {
            printf("%s ", input[i]);
        }
        printf("\n");
    }
}

void pwd(char *input[], int size)
{
    char dir[1000];
    getcwd(dir, 1000);
    if(input[1]==NULL){
        printf("%s\n", dir);
    }
    else if(strcmp(input[1], "--help") == 0){
        printf("Usage: pwd [OPTION]...\n");
        printf("Print the name of the current working directory.\n");
        printf("  --help\tdisplay this help and exit\n");
    }
    else if (strcmp(input[1], "-P"))
    {
        char newarr[1024];
        char *cwd2 = getcwd(newarr, sizeof(newarr));
        printf("%s\n", cwd2);
    }
    else if (strcmp(input[1], "-L"))
    {
        char buf[PATH_MAX];
        char newarr[1024];
        char *res = realpath(newarr, buf);
        char *cwd2 = getcwd(newarr, sizeof(newarr));
        printf("%s\n", cwd2);
    }
    else{
        printf("pwd: invalid option -- '%s'\n", input[1]);
        printf("Try 'pwd --help' for more information.\n");
    }
}


void cd(char *input[],int size)
{
    bool cdP = false;
    bool cdL = false;
    bool cdHelp = false;
    bool noparams = false;

    if(strcmp(input[1],"-P")){
        cdP = true;
    }
    if(strcmp(input[1],"-L")){
        cdL = true;
    }
    if(strcmp(input[1],"--help")){
        cdHelp = true;
    }
    else{
        noparams = true;
    }

    if(noparams && size<2){
        int flg = chdir(getenv("HOME"));
        if(flg){
            printf("\nyou are at home");
        }
        else{
            printf("err");
        }
    }

}



// void echon(char **input_array, int size)
// {
//     int i = 2;
//     while (i < size)
//     {
//         if (input_array[i] != NULL)
//         {
//             printf("%s ", input_array[i]);
//         }
//         i++;
//     }
// }

// void echoE(char **input_array, int size)
// {
//     int i = 2;
//     while (i < size)
//     {
//         if (input_array[i] != NULL)
//         {
//             printf("%s ", input_array[i]);
//         }
//         i++;
//     }
// }


int main(){
    printf("Welcome to the shell\n");
    init_shell();
    
    while (true)
    {
        char rawCommand[100];
        char commandCopy[100];
        printf(">> ");
        scanf("%[^\n]%*c", rawCommand);
        strcpy(commandCopy, rawCommand);
        
        //parsing the input
        int size = 0;
        char *token = strtok(rawCommand, " ");
        char **input = (char **)malloc(500 * sizeof(char *));
        
        //filling the input array
        while (token != NULL)
        {
            input[size] = (char *)malloc(500 * sizeof(char));
            strcpy(input[size], token);
            token = strtok(NULL, " ");
            size++;
        }

        if (strcmp(input[0], "exit") == 0)
        {
            printf("Exiting the shell\n");
            break;
        }
        else if(strcmp(input[0], "pwd") == 0){
            pwd(input, size);
        }
        else if (strcmp(input[0], "echo") == 0)
        {
            echo(input,size);
        }
        else if (strcmp(input[0], "cd") == 0)
        {
            // char *cd = strtok(input[0], " ");
            // cd = strtok(NULL, " ");
            // if (cd == NULL)
            // {
            //     printf("Please enter a directory\n");
            // }
            // else if (strcmp(cd, "..") == 0)
            // {
            //     chdir("..");
            // }
            // else if (strcmp(cd, ".") == 0)
            // {
            //     chdir(".");
            // }
            // else
            // {
            //     chdir(cd);
            // }
            cd(input,size);
        
        }
        else
        {
            printf("Command not found\n");
        }
    }
    
}

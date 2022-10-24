#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <pthread.h>


void init_shell()
{
    printf("\n******************"
        "*********************************************************");
    printf("\n\t\t\tWelcome to Rasputin");
    printf("\n\t\tRasputin is a basic unix based shell!\n");
    printf("---------------------------------------------------------------------------");
    printf("\n\t\tCurrently supported commands are:");
    printf("\n\t\t[cd] [echo] [pwd] [ls] [cat] [date] [rm] [mkdir]");
    printf("\n******************"
        "*********************************************************");
    char* username = getenv("USER");
    printf("\nCurrent user: %s", username);
    printf("\n");
}

// void* thread_rm(void* arg){

// }

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
        char buf[1000];
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


// void cdL(char **input)
// {

// }

void cd(char **input)
{
    bool consoleKey = false;
    bool dashDash = false;
    bool dash = false;
    bool isCdP = false;
    bool isCdL = false;
    bool cdHelp = false;
    bool argMissing = false;

    char cwd_inputnew1[1024];

    if (input[1] != NULL)
    {
        strcpy(cwd_inputnew1, input[1]);
        isCdP = !strcmp(cwd_inputnew1, "-P");
        isCdL = !strcmp(cwd_inputnew1, "-L");
        consoleKey = !strcmp(cwd_inputnew1, "~");
        dashDash = !strcmp(cwd_inputnew1, "--");
        dash = !strcmp(cwd_inputnew1, "-");
        cdHelp = !strcmp(cwd_inputnew1, "--help");
    }
    else
    {
        argMissing = 0;
    }
    
    if (dash == true)
    {
        int check = chdir("..");
        if (check != 0)
        {
            perror("An error occured in: ");
        }
        else
        {
            char cwd2[200];
            char *cwd32 = getcwd(cwd2, sizeof(cwd2));
            printf("%s", cwd32);
        }
    }
    else if (consoleKey == true || dashDash == true || argMissing == true)
    {
        int flag127 = chdir(getenv("HOME"));
        if (flag127 != 0)
        {
            perror("Error in command - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }

    else if (cdHelp == true)
    {
        printf("%s", "this command is used to change the directory to given input");
    }
    else if (isCdP == true)
    {
        char cwd[1024];
        if (input[2] != NULL)
        {

            strcpy(cwd, input[2]);
            char *pt = strtok(cwd, "\n");
            char buf[PATH_MAX];
            char *path = realpath(pt, buf);
            if (!path)
            {
                perror("realpath error:");
            }
            else
            {
                bool check = chdir(path);
                printf("physical source directory : %s\n", buf);
                printf("%s\n", path);
                if (check == true)
                {
                    perror("Error in command - ");
                }
                else
                {
                    char temp[200];
                    char *newCwd = getcwd(temp, sizeof(temp));
                }
            }
        }
        else
        {
            bool check = chdir(getenv("HOME"));
            if (check == true)
            {
                perror("An error occured in: ");
            }
            else
            {
                char temp[200];
                char *newCwd = getcwd(temp, sizeof(temp));
                printf("%s", newCwd);
            }
        }
    }
    else if (isCdL == true)
    {
    if (input[2] != NULL)
    {
        char cwd[1024];
        strcpy(cwd, input[2]);
        char *pt = strtok(cwd, "\n");
        int id = chdir(pt);
        if (id != 0)
        {
            perror("Error in -L command - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
    else
    {
        bool check = chdir(getenv("HOME"));
        if (check == true)
        {
            perror("An error occured in: ");
        }
        else
        {
            char cwd[200];
            char *newcwd = getcwd(cwd, sizeof(cwd));
            printf("%s", newcwd);
        }
    }
    }
    else
    {
        char *pt = strtok(cwd_inputnew1, "\n");
        int value = chdir(pt);
        if (value != 0)
        {
            perror("Error in commands - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
}


int main(){
    // printf("Welcome to the shell\n");
    init_shell();
    
    while (true)
    {
        char rawCommand[100];
        char commandCopy[100];
        bool isThreadBased=false;
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
        
        for(int i=0;i<size;i++){
            if(!strcmp(input[i], "&t")){
                input[i] = NULL;
                isThreadBased = true;
            }
        }
        // for(int i=0;i<size;i++){
        //     if(input[i]==NULL){
        //         printf("null\n");
        //     }
        //     printf("%s\n",input[i]);
        // }

        if(isThreadBased && !strcmp(input[0], "rm")){
            printf("Thread based");
            // pthread_t pid_t;
            // pthread_create(&pid_t,NULL, thread_rm ,NULL);
        }
        else {
            if (!strcmp(input[0], "exit"))
            {
                printf("Exiting the shell\n");
                break;
            }
            else if(!strcmp(input[0], "pwd")){
                pwd(input, size);
            }
            else if (!strcmp(input[0], "echo"))
            {
                echo(input,size);
            }
            else if (!strcmp(input[0], "cd"))
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
                // cdCommand(input,size);
                // // printf("cd nai challa mc!");
                cd(input);
            }
            else if(!strcmp(input[0], "date")){
            pid_t id;
            int status;
            if ((id = fork()) == 0)
            {
                char *args[] = {"./date", commandCopy, NULL};
                execvp("./date", args);
                exit(0);
            }
            else
            {
                pid_t time;
                time = wait(&status);
            }
            }
            else if (!strcmp(input[0], "cat")) {
                pid_t id;
                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./cat", commandCopy, NULL};
                    execvp("./date", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (!strcmp(input[0], "ls")) {
                pid_t id;
                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./ls", commandCopy, NULL};
                    execvp("./ls", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (!strcmp(input[0],"mkdir")) {
                pid_t id;
                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./mkdir", commandCopy, NULL};
                    execvp("./mkdir", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (!strcmp(input[0],"rm")) {
                pid_t id;
                int stat;
                if (input[1]==NULL){
                    printf("rm : missing operand\n");
                }
                else {
                    if ((id = fork()) == 0)
                    {
                        char *args[] = {"./rm", commandCopy, NULL};
                        execvp("./rm", args);
                        exit(0);
                    }
                    else
                    {
                        pid_t time;
                        time = wait(&stat);
                    }
                }
            }
            else
            {
                printf("Command not found\n");
            }
        }
    }
}

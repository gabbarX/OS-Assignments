#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/wait.h>


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

void cdP(char **input_array)
{
    char cwd_inputnew2[1024];

    if (input_array[2] != NULL)
    {

        strcpy(cwd_inputnew2, input_array[2]);
        char *pt = strtok(cwd_inputnew2, "\n");
        char buf[PATH_MAX];
        char *res = realpath(pt, buf);
        if (!res)
        {
            perror("realpath error:");
        }
        else
        {
            int value23 = chdir(res);
            printf("physical source directory : %s\n", buf);
            printf("%s\n", res);
            if (value23 != 0)
            {
                perror("Error in command - ");
            }
            else
            {
                char cwd5[200];
                char *cwd35 = getcwd(cwd5, sizeof(cwd5));
            }
        }
    }
    else
    {
        int value2 = chdir(getenv("HOME"));
        if (value2 != 0)
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
}

void cdL(char **input_array)
{
    if (input_array[2] != NULL)
    {
        char cwd_inputnew2[1024];
        strcpy(cwd_inputnew2, input_array[2]);
        char *inputnew3 = "";
        char *inputnew4 = "hi";
        // printf("yo");
        char *pt = strtok(cwd_inputnew2, "\n");
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
        int value2 = chdir(getenv("HOME"));
        if (value2 != 0)
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
}

void cd(char **input_array)
{
    int flaggers1 = INT_MAX;
    int flaggers2 = INT_MAX;
    int flaggers3 = INT_MAX;
    int flaggers4 = INT_MAX;
    int flaggers5 = INT_MAX;
    int flaggers6 = INT_MAX;
    int flaggers7 = INT_MAX;

    char cwd_inputnew1[1024];

    if (input_array[1] != NULL)
    {

        strcpy(cwd_inputnew1, input_array[1]);
        flaggers1 = strcmp(cwd_inputnew1, "~");
        flaggers2 = strcmp(cwd_inputnew1, "--");
        flaggers3 = strcmp(cwd_inputnew1, "-");
        flaggers4 = strcmp(cwd_inputnew1, "-P");
        flaggers5 = strcmp(cwd_inputnew1, "-L");
        flaggers6 = strcmp(cwd_inputnew1, "--help");
    }
    else
    {
        flaggers7 = 0;
    }
    
    if (flaggers3 == 0)
    {
        int flag3 = chdir("..");
        if (flag3 != 0)
        {
            perror("Error in command - ");
        }
        else
        {
            char cwd2[200];
            char *cwd32 = getcwd(cwd2, sizeof(cwd2));
            printf("%s", cwd32);
        }
    }
    else if (flaggers1 == 0 || flaggers2 == 0 || flaggers7 == 0)
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

    else if (flaggers6 == 0)
    {
        printf("%s", "this command is used to change the directory to given input");
    }
    else if (flaggers4 == 0)
    {
        cdP(input_array);
    }
    else if (flaggers5 == 0)
    {
        cdL(input_array);
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


// void cdCommand(char *input[],int size)
// {   
//     // printf("cd nahi challa bc function hu");
//     bool cdP = false;
//     bool cdL = false;
//     bool cdHelp = false;
//     // bool noparams = false;
//     // printf("%b",noparams);
//     if(size>1){
        
//         if(strcmp(input[1],"-P")==0){
//             cdP = true;
//         }
//         if(strcmp(input[1],"-L")==0){
//             cdL = true;
//         }
//         if(strcmp(input[1],"--help")==0){
//             cdHelp = true;
//         }
//         if(strcmp(input[1], "..")){
//             chdir("..");
//         }
//         else{
//             printf("INvalid option");
//         }
//     }
//     else {
//         int flg = chdir(getenv("HOME"));
//         if(flg){
//             printf("ERROR");
//         }
//         else {
//             char cwd2[1000];
//             getcwd(cwd2, 1000);
//             printf("%s\n",cwd2);
//         }
//     }
//     if(cdHelp){
//         printf("cd : [-L || -P][dir]\n");
//         printf("Change the current directory to DIR. The default DIR is the value of the HOME shell variable.\n");
//     }   
//     if(cdL){
        
//     }
//     if(cdP){

//     }
// }



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
                isThreadBased = true;
            }
        }

        if(isThreadBased && !strcmp(input[0], "rm")){
            printf("Thread based");
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

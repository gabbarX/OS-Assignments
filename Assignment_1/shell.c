#include <asm-generic/errno.h>
#include <linux/limits.h>
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

void* thread_rm(void* arg){
    // input[0]
    char initialcommand[200]="";
    char temp[200]="";
    strcpy(initialcommand, (char*)arg);
    // printf("haha mai thread hu\n");
    char rm_path[1024]= "./rm";
    // system(strcat("./rm ",(char*)arg));
    // printf("thread based size: %s")

    char *token = strtok((char*)arg, " ");

    // printf("command going to system()->%s",token);
    char **threadInput = (char **)malloc(500 * sizeof(char *));
    // system((char*)arg);
    int size=0;
    while (token != NULL)
        {
            threadInput[size] = (char *)malloc(500 * sizeof(char));
            strcpy(threadInput[size], token);
            token = strtok(NULL, " ");
            size++;
        }
    
    // for(int i=0;i<size;i++){
    //     printf("$$ %s",threadInput[i]);
    // }

    if(!strcmp(threadInput[0], "cat")){
        // printf("cat hu re bawa!");
        char temp[200]="";
        char initcommand[200] = "./cat ";
        for(int i =1; i<size;i++){
            strcat(initcommand, threadInput[i]);
        }
        system(initialcommand);
    }
    else if (!strcmp(threadInput[0], "date")) {
        char temp[200]="";
        char initcommand[200] = "./date ";
        for(int i =1; i<size;i++){
            strcat(initcommand, threadInput[i]);
        }
        system(initialcommand);
    }
    else if (!strcmp(threadInput[0], "ls")) {
        char temp[200]="";
        char initcommand[200] = "./ls ";
        for(int i =1; i<size;i++){
            strcat(initcommand, threadInput[i]);
        }
        system(initialcommand);
    
    }
    else if (!strcmp(threadInput[0], "mkdir")) {
        char temp[200]="";
        char initcommand[200] = "./mkdir ";
        for(int i =1; i<size;i++){
            strcat(initcommand, threadInput[i]);
        }
        system(initialcommand);
    }
    else if (!strcmp(threadInput[0], "rm")) {
        char temp[200]="";
        char initcommand[200] = "./rm ";
        for(int i =1; i<size;i++){
            strcat(initcommand, threadInput[i]);
        }
        system(initialcommand);
    
    }
    else {
    printf("Syntax Error!\n");
    }
    return 0;
}

void echo(char *input[], int size, char commandCopy[])
{
    bool echoN = false;
    bool echoE = false;
    bool echoHelp = false;

    //Determining the type of echo
    if(strcmp(input[1], "-n") == 0)
    {
        echoN = true;
    }
    else if(strcmp(input[1], "-E") == 0)
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
        printf("  -E\tdisables interpretation of backslash escapes\n");
        printf("  --help\tdisplay this help and exit\n");
    }
    else{
        // printf("haha");
        for(int i = 5; i < strlen(commandCopy); i++)
        {
            // echo 
            printf("%c", commandCopy[i]);
        }
        printf("\n");
    }
}

void pwd(char *input[], int size)
{   
    if(size>2){
        printf("Too many arguments to the command pwd.\n");
    }
    else 
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
}


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
        argMissing = true;
    }
    
    if (dash == true)
    {
        chdir("..");
        char cwd2[200];
        char *cwd32 = getcwd(cwd2, sizeof(cwd2));
        printf("%s", cwd32);
    
    }
    else if (consoleKey == true || dashDash == true || argMissing == true)
    {
        chdir(getenv("HOME"));    
        char cwd[200];
        char *newPath = getcwd(cwd, sizeof(cwd));
        printf("%s", newPath);

    }

    else if (cdHelp == true)
    {
        printf("cd [option] [dir]");
        printf("Change the shell working directory.");
        printf("-P \tuse the physical directory structure without following symbolic links: resolve symbolic links in DIR before processing instances of `..' ");
        printf("-L \tforce symbolic links to be followed: resolve symbolic links in DIR after processing instances of `..'");
    }
    else if (isCdP == true)
    {
        char cwd[PATH_MAX];
        if (input[2] != NULL)
        {

            strcpy(cwd, input[2]);
            char *pt = strtok(cwd, "\n");
            char buf[PATH_MAX];
            char *path = realpath(pt, buf);
            chdir(path);
            printf("physical source directory : %s\n", buf);
            printf("%s\n", path);
            char temp[200];
            char *newCwd = getcwd(temp, sizeof(temp));

        }
        else
        {
            chdir(getenv("HOME"));
            char temp[200];
            char *newPath = getcwd(temp, sizeof(temp));
            printf("%s", newPath);
        }
    }
    else if (isCdL == true)
    {
    if (input[2] != NULL)
    {
        char cwd[1024];
        strcpy(cwd, input[2]);
        char *pt = strtok(cwd, "\n");
        chdir(pt);
        char cwd2[200];
        char *newPath = getcwd(cwd2, sizeof(cwd2));
        printf("%s", newPath);
    }
    else
    {
        chdir(getenv("HOME"));
        char cwd[200];
        char *newPath = getcwd(cwd, sizeof(cwd));
        printf("%s", newPath);

    }
    }
    else
    {
        char *pt = strtok(cwd_inputnew1, "\n");
        chdir(pt);
        char cwd[200];
        char *newPath = getcwd(cwd, sizeof(cwd));
        printf("%s", newPath);
    }
}


int main(){
    
    init_shell();
    
    while (true)
    {
        char rawCommand[100];
        char commandCopy[100];
        bool isThreadBased=false;
        printf(">> ");
        scanf("%[^\n]%*c", rawCommand);
        // fgets(rawCommand, 100, stdin);
        strcpy(commandCopy, rawCommand);
        
        int size = 0;
        char *token = strtok(rawCommand, " ");
        char **input = (char **)malloc(500 * sizeof(char *));
        
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
        
        char threadCommand[200]="";
        bool firstRun = true;
        for(int i=0;i<size;i++){
            if(!strcmp(input[i], "&t")){
                continue;
            }
            else {
                if(!firstRun){
                    strcat(threadCommand, " ");      
                }
                strcat(threadCommand, input[i]);
                firstRun = false;
            }
        }


        if(isThreadBased){
            pthread_t pid_t;
            pthread_create(&pid_t,NULL, thread_rm ,(void*) threadCommand);
            pthread_join(pid_t, NULL);
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
                echo(input,size,commandCopy);
            }
            else if (!strcmp(input[0], "cd"))
            {
                cd(input);
            }
            else if(!strcmp(input[0], "date")){
            
            pid_t id;
            int statusus;
            if ((id = fork()) == 0)
            {
                execl("./date","./date", commandCopy, NULL);
                exit(EXIT_SUCCESS);
            }
            else
            {
                pid_t time;
                time = wait(&statusus);
            }
            }
            else if (!strcmp(input[0], "cat")) {
                if(size==1){
                    printf("Cat needs more arguments to proceed!\n");
                }
                else {
                    pid_t id;
                    int status;
                    if ((id = fork()) == 0)
                    {
                        execl("./cat","./cat", commandCopy, input[1]);
                        exit(EXIT_SUCCESS);
                    }
                    else
                    {
                        pid_t time;
                        time = wait(&status);
                    }
                }
                
            }
            else if (!strcmp(input[0], "ls")) {
                pid_t id;
                int statusus;
                if ((id = fork()) == 0)
                {
                    execl("./ls", "./ls",commandCopy,NULL);
                    exit(EXIT_SUCCESS);
                }
                else
                {
                    pid_t time;
                    time = wait(&statusus);
                }
            }
            else if (!strcmp(input[0],"mkdir")) {
                if(size==1){
                    printf("mkdir needs more arguments to proceed!\n");
                }
                else {
                    pid_t id;
                    int status;
                    if ((id = fork()) == 0)
                    {
                        char *args[] = {"./mkdir", commandCopy, NULL};
                        execl("./mkdir", "./mkdir",commandCopy,NULL);
                        exit(EXIT_SUCCESS);
                    }
                    else
                    {
                        pid_t time;
                        time = wait(&status);
                    }
                }
            }
            else if (!strcmp(input[0],"rm")) {
                pid_t id;
                int status;
                if (size==1){
                    printf("rm needs more arguments to proceed!\n");
                }
                else {
                    if ((id = fork()) == 0)
                    {
                        execl("./rm","./rm",commandCopy, NULL);
                        exit(EXIT_SUCCESS);
                    }
                    else
                    {
                        pid_t time;
                        time = wait(&status);
                    }
                }
            }
            else
            {
                printf("Command not found!\n");
            }
        }
    }
}

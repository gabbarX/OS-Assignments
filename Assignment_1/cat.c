#include <asm-generic/errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
    char command[100] = "";
    char flags[100] = "";
    char fileName[1000] = "";
    char *token = strtok(argv[1], " ");
    strcpy(command, token);
    token = strtok(NULL, " ");
    //flags
    if (token[0] == '-')
    {
        strcpy(flags, token);
        token = strtok(NULL, " ");
    }
    //fileName
    while (token != NULL) {
        strcpy(fileName, token);
        token = strtok(NULL, " ");
    }

    // printf("flag - %s\n",flags);
    // printf("fileName - %s\n",fileName);
    
    if(!strcmp(flags, ""))
    {

        FILE* ptr;
        char ch;

        ptr = fopen(fileName, "r");
        if(ptr == NULL){
            printf("File does not exists\n");
            exit(1);
        }
        else {
            // printf("File has been read! :3\n");
            do {
                ch = fgetc(ptr);
                printf("%c",ch);
            }while (ch!=EOF);
            printf("\n");
            fclose(ptr);
        }
        
    }
    else if (flags[1]=='E') {

        FILE* ptr;
        char ch;

        ptr = fopen(fileName, "r");
        if(ptr == NULL){
            printf("File does not exists\n");
            exit(1);
        }
        else {
            do {
            ch = fgetc(ptr);
            if(ch=='\n')
            {
                printf("$");
            }
                printf("%c",ch);
            }while (ch!=EOF);

            printf("\n");
            fclose(ptr);
        }
    }
    else if (flags[1]=='n') {
        // printf("flag n");

        FILE* ptr;
        char ch;
        int count=1;
        bool flg = true;

        ptr = fopen(fileName, "r");
        if(ptr == NULL){
            printf("File does not exists\n");
            exit(1);
        }
        else {
            do {
                if(ch =='\n'){
                    count++;
                    flg = true;
                }
                if(flg){
                    printf("%d ",count);
                    flg = false;
                }
                ch = fgetc(ptr);
                printf("%c",ch);
            }while (ch!=EOF);
            // printf("Number of lines is -> %d",count);
            printf("\n");
            fclose(ptr);
        }
        
    }
    exit(0);
}
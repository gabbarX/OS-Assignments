#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int main(void){

    char rawCommand[100];
    char s[100];
    printf(">> ");
    scanf("%[^\n]%*c", rawCommand);
    char *token = strtok(rawCommand, " ");
    printf("%s",token);
    // printf("%d",strlen(token));
}
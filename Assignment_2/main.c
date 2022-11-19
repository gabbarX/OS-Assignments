#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void threadA(){
    long long int i=1;
    while (i<=pow(2,32)) 
    {
        i++;
    }
}

void threadB(){
    long long int i=1;
    while (i<=pow(2,32)) 
    {
        i++;
    }
}

void threadC(){
    long long int i=1;
    while (i<=pow(2,32)) 
    {
        i++;
    }
}

int main(void)
{

int pthread_create()

}
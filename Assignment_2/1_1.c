#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

void* threadA(void *vargp){
    struct sched_param paramA;
    int policyA = SCHED_OTHER;
    paramA.sched_priority = 0;
    // int priority = 0;

    int ta = pthread_setschedparam(pthread_self(), policyA, &paramA);
    if(ta==0){
        printf("Successfully initialised the policy and priority for thread A.\n");
    }
    else{
        printf("A ; ");
        perror("Error");
    }


    long long int i=1;
    printf("Hello threadA reporting sir.\n");
    while (i<=pow(2,32)) 
    {
        i++;
    }
}

void* threadB(void *vargp){


    struct sched_param paramB;
    int policyB = SCHED_RR;
    paramB.sched_priority = 1;
    // int priority = 0;

    int tb = pthread_setschedparam(pthread_self(), policyB, &paramB);
    if(tb==0){
        printf("Successfully initialised the policy and priority for thread B.\n");
    }
    else{
        printf("B ; ");
        perror("Error");
    }
        
    long long int i=1;
    printf("Hello threadB reporting sir.\n");
    while (i<=pow(2,32)) 
    {
        i++;
    }
    // printf("Thread B complete.\n");
    
}

void* threadC(void *vargp){

    struct sched_param paramC;
    int policyC = SCHED_FIFO;
    paramC.sched_priority = 1;
    // int priority = 0;

    int tc = pthread_setschedparam(pthread_self(), policyC, &paramC);
    if(tc==0){
        printf("Successfully initialised the policy and priority for thread C.\n");
    }
    else{
        printf("C ; ");
        perror("Error");
    }
    

    long long int i=1;
    printf("Hello threadC reporting sir.\n");
    while (i<=pow(2,32)) 
    {
        i++;
    }
}

int main(void)
{
    pthread_t threadAid;
    pthread_t threadBid;
    pthread_t threadCid;

   
    int cta = pthread_create(&threadAid, NULL, threadA, (void *)&threadAid);
    if(cta==0){
        printf("ThreadA created successfully.\n");
    }
    else{
        perror("Error");
    }



    // clock_gettime();




    pthread_create(&threadBid, NULL, threadB, (void *)&threadBid);
    
    int ctb = pthread_create(&threadBid, NULL, threadB, (void *)&threadBid);
    if(ctb==0){
        printf("ThreadB created successfully.\n");
    }
    else{
        perror("Error");
    }
    
    // clock_gettime();
    
    int ctc = pthread_create(&threadCid, NULL, threadC, (void *)&threadCid);
    if(ctc==0){
        printf("ThreadC created successfully.\n");
    }
    else{
        perror("Error");
    }

    pthread_join(threadAid, NULL);
    pthread_join(threadBid, NULL);
    pthread_join(threadCid, NULL);
    // clock_gettime();

}

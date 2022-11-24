#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

#define BILLION  1000000000.0

double result[6][3];

int Apriority=18;
int Bpriority=18;
int Cpriority=18;

void* threadA(void *vargp){

    // Time Stuff
    struct timespec start, stop;
    double accum;
    clock_gettime( CLOCK_REALTIME, &start);


    // Priority and policy stuff
    struct sched_param paramA;
    int policyA = SCHED_OTHER;
    paramA.sched_priority = Apriority;
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
    // clock_gettime();
    // printf("%lld\n\n",4294967296);
    printf("Hello threadA reporting sir.\n");
    long long int count = 1;
    while (i<=4294967296) 
    {
        // printf("%lld " ,i);
        count++;
        i++;

    }

    clock_gettime( CLOCK_REALTIME, &stop);
    accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec )/ BILLION;
    // printf( "A --> %lf\n", accum );
    result[0][0] = accum;
}

void* threadB(void *vargp){

    // Time Stuff
    struct timespec start, stop;
    double accum;
    clock_gettime( CLOCK_REALTIME, &start);


    struct sched_param paramB;
    int policyB = SCHED_RR;
    paramB.sched_priority = Bpriority;
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

    // clock_gettime();
    long long int count = 1;
    while (i<=4294967296) 
    {
        // printf("%lld ",i);
        count++;
        i++;
    }
    // printf("Thread B complete.\n");


    clock_gettime( CLOCK_REALTIME, &stop);
    accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec )/ BILLION;
    // printf( "B --> %lf\n", accum );
    result[0][1] = accum;
    
}

void* threadC(void *vargp){

    // Time stuff
    struct timespec start, stop;
    double accum;
    clock_gettime( CLOCK_REALTIME, &start);

    struct sched_param paramC;
    int policyC = SCHED_FIFO;
    paramC.sched_priority = Cpriority;
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

    // clock_gettime();
    long long int count = 1;
    while (i<=4294967296) 
    {   
        // printf("%lld ",i);
        count++;
        i++;
    }


    clock_gettime( CLOCK_REALTIME, &stop);
    accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec )/ BILLION;
    // printf( "C --> %lf\n", accum );
    result[0][2] = accum;
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

    printf("Time for A: %lf\nTime for B: %lf\nTime for C: %lf\n",result[0][0],result[0][1],result[0][2]);

}

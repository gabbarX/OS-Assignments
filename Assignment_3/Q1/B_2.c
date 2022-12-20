#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int PhilosopherNum=5;
int f = 5;
int forks[5];
int bowl[2];

void *philosophersWorld(void *arg) 
{
    int id = *((int *)arg);

    while (true) 
    {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);
        
        forks[id] = 1;
        printf("Philosopher %d picked up left fork.\n", id);
        
        forks[(id + 1) % f] = 1;
        printf("Philosopher %d picked up right fork.\n", id);

        bowl[id%2] = 1;
        printf("Philosopher %d is eating form bowl %d.\n", id, id%2);
        bowl[id%2] = 0;
        sleep(1);

        forks[id] = 0;
        forks[(id + 1) % f] = 0;
    }
}

int main() 
{
    pthread_t philosophers[PhilosopherNum];
    int ids[PhilosopherNum];

    for (int i = 0; i < PhilosopherNum; i++) 
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosophersWorld, &ids[i]);
    }

    for (int i = 0; i < PhilosopherNum; i++) 
    {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5

int forks[NUM_FORKS];

void *philosopher(void *arg) 
{
    int id = *((int *)arg);

    while (1) 
    {
        // Think
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);
        // Pick up left fork
        printf("Philosopher %d is trying to pick up left fork.\n", id);
    
        while (forks[id] == 1) 
        {
        // Do nothing
        }
        
        forks[id] = 1;
        printf("Philosopher %d picked up left fork.\n", id);

        // Pick up right fork
        printf("Philosopher %d is trying to pick up right fork.\n", id);
        
        while (forks[(id + 1) % NUM_FORKS] == 1) 
        {
        // Do nothing
        }
        forks[(id + 1) % NUM_FORKS] = 1;
        printf("Philosopher %d picked up right fork.\n", id);

        // Eat
        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        // Put down forks
        forks[id] = 0;
        forks[(id + 1) % NUM_FORKS] = 0;
    }
}

int main() 
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    //creating philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    //Joining philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_join(philosophers[i], NULL);
    }

    printf("All philoshophers have completed their tasks!");

    return 0;
}

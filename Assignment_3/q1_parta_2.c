//Modified Dining philosophers Problem using semaphores

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) 
{
    int id = *((int *)arg);

    while (1) 
    {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); // simulate thinking

        // pick up left fork
        sem_wait(&forks[id]);
        printf("Philosopher %d picked up left fork.\n", id);

        // pick up right fork
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up right fork.\n", id);

        printf("Philosopher %d is eating.\n", id);
        sleep(1); // simulate eating

        // put down left fork
        sem_post(&forks[id]);
        printf("Philosopher %d put down left fork.\n", id);

        // put down right fork
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right fork.\n", id);

    }

    return NULL;
}

int main(int argc, char *argv[]) 
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // initialize semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        sem_init(&forks[i], 0, 1);
    }

    // create threads for each philosopher
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // wait for threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

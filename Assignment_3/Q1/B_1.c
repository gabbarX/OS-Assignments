#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_PHILOSOPHERS 5
#define NUM_SAUCEBOWL 2
sem_t forks[NUM_PHILOSOPHERS];
sem_t sauceBowl[NUM_SAUCEBOWL];

void *philosopher(void *arg) 
{
    int id = *((int *)arg);

    while (true) 
    {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        sem_wait(&forks[id]);
        printf("Philosopher %d picked up left fork.\n", id);

        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        printf("Philosopher %d picked up right fork.\n", id);

        sem_wait(&sauceBowl[id%2]);
        printf("Philosopher %d is eating.\n", id);
        sleep(1);
        sem_post(&sauceBowl[id%2]);

        sem_post(&forks[id]);
        printf("Philosopher %d put down left fork.\n", id);

        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right fork.\n", id);

    }
    return NULL;
}

int main(void) 
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for(int i=0;i<2;i++){
        sem_init(&sauceBowl[i],0,1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_join(philosophers[i], NULL);
    }

}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Semaphores representing the forks
sem_t forks[NUM_PHILOSOPHERS];

// Mutex to synchronize print statements
pthread_mutex_t print_mutex;

// Philosopher function that simulates thinking, eating, and waiting for forks
void* philosopher(void* num) {
    int id = *(int*)num;
    int left_fork = id; // Left fork is the same index as philosopher
    int right_fork = (id + 1) % NUM_PHILOSOPHERS; // Right fork is next philosopher's left fork

    while (1) {
        // Thinking
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d is thinking.\n", id);
        pthread_mutex_unlock(&print_mutex);
        sleep(rand() % 3); // Simulate thinking time

        // Pick up left fork
        sem_wait(&forks[left_fork]);
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d picked up left fork %d.\n", id, left_fork);
        pthread_mutex_unlock(&print_mutex);

        // Pick up right fork
        sem_wait(&forks[right_fork]);
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d picked up right fork %d.\n", id, right_fork);
        pthread_mutex_unlock(&print_mutex);

        // Eating
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d is eating.\n", id);
        pthread_mutex_unlock(&print_mutex);
        sleep(rand() % 3); // Simulate eating time

        // Put down right fork
        sem_post(&forks[right_fork]);
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d put down right fork %d.\n", id, right_fork);
        pthread_mutex_unlock(&print_mutex);

        // Put down left fork
        sem_post(&forks[left_fork]);
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d put down left fork %d.\n", id, left_fork);
        pthread_mutex_unlock(&print_mutex);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize semaphores for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1); // Each fork is initially available
    }

    // Initialize mutex for printing
    pthread_mutex_init(&print_mutex, NULL);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Wait for philosopher threads to finish (they will run indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Cleanup (this will never be reached in this example, as philosophers run forever)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&print_mutex);

    return 0;
}

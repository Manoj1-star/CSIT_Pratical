#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10

// Buffer and semaphore variables
int buffer[BUFFER_SIZE];
int in = 0;  // Index where the producer will put the next item
int out = 0; // Index where the consumer will take the next item

sem_t empty; // Semaphore to count empty slots
sem_t full;  // Semaphore to count full slots
pthread_mutex_t mutex; // Mutex to protect shared buffer

void* producer(void* param) {
    while (1) {
        // Produce an item
        int item = rand() % 100;
        printf("Producer produced %d\n", item);

        // Wait for an empty slot
        sem_wait(&empty);

        // Lock the mutex to access the buffer
        pthread_mutex_lock(&mutex);

        // Add the item to the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        // Unlock the mutex and signal that a new item is available
        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        // Sleep for a while to simulate production time
        sleep(rand() % 3);
    }
    return NULL;
}

void* consumer(void* param) {
    while (1) {
        // Wait for a full slot
        sem_wait(&full);

        // Lock the mutex to access the buffer
        pthread_mutex_lock(&mutex);

        // Remove an item from the buffer
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        // Unlock the mutex and signal that an empty slot is available
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        // Consume the item
        printf("Consumer consumed %d\n", item);

        // Sleep for a while to simulate consumption time
        sleep(rand() % 3);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // All slots are initially empty
    sem_init(&full, 0, 0);            // No slots are initially full

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish (they never will in this example)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Cleanup (this code will never be reached)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* print_numbers(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread %ld: %d\n", (long)arg, i);
        sleep(1);  // Sleep for 1 second
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Creating two threads
    pthread_create(&thread1, NULL, print_numbers, (void*)1);
    pthread_create(&thread2, NULL, print_numbers, (void*)2);

    // Waiting for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished execution.\n");
    return 0;
}


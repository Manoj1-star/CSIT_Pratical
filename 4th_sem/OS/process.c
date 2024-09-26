#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>  

int main() {
    pid_t pid = fork();  // Create a new process

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } 
    else if (pid == 0) {
        // Child process
        for (int i = 0; i < 5; i++) {
            printf("Child Process: %d\n", i);
            sleep(1);  // Sleep for 1 second
        }
    } 
    else {
        // Parent process
        for (int i = 0; i < 5; i++) {
            printf("Parent Process: %d\n", i);
            sleep(1);  // Sleep for 1 second
        }
        wait(NULL);  // Wait for the child process to finish
    }

    printf("Both processes have finished execution.\n");
    return 0;
}


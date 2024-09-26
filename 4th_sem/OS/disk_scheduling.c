#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 20

void fcfs(int requests[], int n, int start);
void scan(int requests[], int n, int start, int direction);
void look(int requests[], int n, int start, int direction);

int main() {
    int requests[MAX_REQUESTS];
    int n, start, choice, direction;

    printf("Disk Scheduling Algorithms Simulation\n");
    printf("Enter the number of disk requests (max %d): ", MAX_REQUESTS);
    scanf("%d", &n);

    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial disk position: ");
    scanf("%d", &start);

    printf("Choose Disk Scheduling Algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SCAN\n");
    printf("3. LOOK\n");
    printf("Choose an option (1-3): ");
    scanf("%d", &choice);

    if (choice == 2 || choice == 3) {
        printf("Enter direction (1 for up, 0 for down): ");
        scanf("%d", &direction);
    }

    switch (choice) {
        case 1:
            fcfs(requests, n, start);
            break;
        case 2:
            scan(requests, n, start, direction);
            break;
        case 3:
            look(requests, n, start, direction);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

// Function to simulate FCFS Disk Scheduling
void fcfs(int requests[], int n, int start) {
    int total_movement = 0;
    int current_position = start;

    printf("\nFCFS Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        printf("Moving from %d to %d\n", current_position, requests[i]);
        total_movement += abs(current_position - requests[i]);
        current_position = requests[i];
    }

    printf("Total disk movement = %d\n", total_movement);
}

// Function to simulate SCAN Disk Scheduling
void scan(int requests[], int n, int start, int direction) {
    int total_movement = 0;
    int current_position = start;

    // Sort requests array
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    printf("\nSCAN Disk Scheduling:\n");

    if (direction == 1) { // Up
        for (int i = 0; i < n; i++) {
            if (requests[i] >= start) {
                printf("Moving from %d to %d\n", current_position, requests[i]);
                total_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }
        printf("Moving from %d to the end of disk\n", current_position);
        total_movement += abs(current_position - 200); // Assuming the end of the disk is 200
        current_position = 200;

        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < start) {
                printf("Moving from %d to %d\n", current_position, requests[i]);
                total_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }
    } else { // Down
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= start) {
                printf("Moving from %d to %d\n", current_position, requests[i]);
                total_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }
        printf("Moving from %d to the start of disk\n", current_position);
        total_movement += abs(current_position - 0);
        current_position = 0;

        for (int i = 0; i < n; i++) {
            if (requests[i] > start) {
                printf("Moving from %d to %d\n", current_position, requests[i]);
                total_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }
    }

    printf("Total disk movement = %d\n", total_movement);
}

// Function to simulate LOOK Disk Scheduling
void look(int requests[], int n, int start, int direction) {
    int total_movement = 0;
    int current_position = start;

    // Sort requests array
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    printf("\nLOOK Disk Scheduling:\n");

    if (direction == 1) { // Up
        for (int i = 0; i < n; i++) {
            if (requests[i] >= start) {
                printf("Moving from %d to %d\n", current_position, requests[i]);
                total_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }
        // Reverse direction
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < start) {
                printf("Moving from %d to %d\n", current_position, requests[i]);
                total_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }
    } else { // Down
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= start) {
                printf("Moving from %d to %d\n", current_position, requests[i]);
                total_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }
        // Reverse direction
        for (int i = 0; i < n; i++) {
            if (requests[i] > start) {
                printf("Moving from %d to %d\n", current_position, requests[i]);
                total_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }
    }

    printf("Total disk movement = %d\n", total_movement);
}

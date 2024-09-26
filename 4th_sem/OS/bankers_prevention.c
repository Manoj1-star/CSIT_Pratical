#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 5

// Function to calculate the Need Matrix
void calculate_need(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if a request can be granted safely
bool is_safe(int processes, int resources, int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES]) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safe_sequence[MAX_PROCESSES];
    
    // Calculate the Need matrix
    calculate_need(need, max, allocation, processes, resources);
    
    // Initialize work array to the available resources
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int count = 0; // Count of finished processes
    while (count < processes) {
        bool found = false;
        
        for (int p = 0; p < processes; p++) {
            if (!finish[p]) {
                bool can_allocate = true;

                // Check if the process's need can be satisfied
                for (int j = 0; j < resources; j++) {
                    if (need[p][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                // If the process's needs can be met
                if (can_allocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[p][j];
                    }
                    safe_sequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        // If no process can be allocated resources, the system is unsafe
        if (!found) {
            return false;
        }
    }

    // If all processes finished, the system is in a safe state
    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < processes; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int processes, resources;
    
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    
    printf("Enter the number of resources: ");
    scanf("%d", &resources);
    
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    
    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    printf("Enter the Maximum Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("Enter the Available Resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    // Check if the system is in a safe state using Banker's Algorithm
    if (!is_safe(processes, resources, available, max, allocation)) {
        printf("System is not in a safe state.\n");
    }

    return 0;
}

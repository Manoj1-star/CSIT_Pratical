#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 5

// Function to check system safety
bool is_safe(int processes, int resources, int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES]) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safe_sequence[MAX_PROCESSES];
    
    // Calculate the Need matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    // Initialize the work array with available resources
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }
    
    int count = 0; // Count of processes that have finished
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
                
                // If the process's need can be satisfied
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
        
        // If no process can be allocated resources, return false
        if (!found) {
            return false;
        }
    }
    
    // If all processes are finished, the system is in a safe state
    printf("The system is in a safe state.\nSafe sequence: ");
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
    
    // Perform safety check using Banker's Algorithm
    if (!is_safe(processes, resources, available, max, allocation)) {
        printf("The system is not in a safe state.\n");
    }
    
    return 0;
}

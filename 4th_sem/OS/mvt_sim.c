#include <stdio.h>

void MVT(int total_memory, int processes[], int n) {
    int memory_allocated = 0, external_frag = 0;
    int process_allocated[n];
    
    for (int i = 0; i < n; i++) {
        process_allocated[i] = -1; // Initialize process allocation
        if (processes[i] <= (total_memory - memory_allocated)) {
            process_allocated[i] = memory_allocated;
            memory_allocated += processes[i];
        } else {
            external_frag += processes[i]; // If process cannot be allocated, mark it as external fragmentation
        }
    }
    
    printf("MVT Simulation Results:\n");
    for (int i = 0; i < n; i++) {
        if (process_allocated[i] != -1) {
            printf("Process %d allocated memory starting from %d\n", i + 1, process_allocated[i]);
        } else {
            printf("Process %d not allocated due to insufficient memory\n", i + 1);
        }
    }
    printf("Total Memory Allocated: %d\n", memory_allocated);
    printf("Total External Fragmentation: %d\n", external_frag);
}

int main() {
    int total_memory, n;
    
    printf("Enter total memory size: ");
    scanf("%d", &total_memory);
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    int processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter memory requirement for process %d: ", i + 1);
        scanf("%d", &processes[i]);
    }
    
    MVT(total_memory, processes, n);
    
    return 0;
}

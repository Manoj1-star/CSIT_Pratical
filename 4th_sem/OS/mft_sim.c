#include <stdio.h>

void MFT(int total_memory, int partition_size, int processes[], int n) {
    int partitions = total_memory / partition_size;
    int internal_frag = 0, external_frag = total_memory - (partitions * partition_size);
    int allocated_partitions[partitions];
    int process_allocated[n];
    
    for (int i = 0; i < partitions; i++) {
        allocated_partitions[i] = -1; // Initialize partition availability
    }
    
    for (int i = 0; i < n; i++) {
        process_allocated[i] = -1; // Initialize process allocation
        for (int j = 0; j < partitions; j++) {
            if (allocated_partitions[j] == -1 && processes[i] <= partition_size) {
                allocated_partitions[j] = i;
                process_allocated[i] = j;
                internal_frag += (partition_size - processes[i]);
                break;
            }
        }
    }
    
    printf("MFT Simulation Results:\n");
    for (int i = 0; i < n; i++) {
        if (process_allocated[i] != -1) {
            printf("Process %d allocated to partition %d\n", i + 1, process_allocated[i] + 1);
        } else {
            printf("Process %d not allocated (waiting)\n", i + 1);
        }
    }
    printf("Total Internal Fragmentation: %d\n", internal_frag);
    printf("Total External Fragmentation: %d\n", external_frag);
}

int main() {
    int total_memory, partition_size, n;
    
    printf("Enter total memory size: ");
    scanf("%d", &total_memory);
    printf("Enter partition size: ");
    scanf("%d", &partition_size);
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    int processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter memory requirement for process %d: ", i + 1);
        scanf("%d", &processes[i]);
    }
    
    MFT(total_memory, partition_size, processes, n);
    
    return 0;
}

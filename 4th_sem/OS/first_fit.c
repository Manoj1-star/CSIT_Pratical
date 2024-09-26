#include <stdio.h>

void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];

    // Initialize allocation array with -1 (indicating no allocation)
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
    }

    // First Fit allocation
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate the block j to process i
                allocation[i] = j;

                // Reduce available memory in this block
                blockSize[j] -= processSize[i];

                break;
            }
        }
    }

    // Output the allocation results
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blocks, processes;

    // Input the number of blocks
    printf("Enter the number of memory blocks: ");
    scanf("%d", &blocks);

    int blockSize[blocks];
    printf("Enter the sizes of the blocks:\n");
    for (int i = 0; i < blocks; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    int processSize[processes];
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // Call the firstFit function
    firstFit(blockSize, blocks, processSize, processes);

    return 0;
}


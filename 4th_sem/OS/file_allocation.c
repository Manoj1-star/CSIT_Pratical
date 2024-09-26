#include <stdio.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_BLOCKS 10

// Structure to hold file information for all strategies
struct File {
    char name[20];
    int size;
    int startBlock;  // For sequential and linked
    int dataBlocks[MAX_BLOCKS];  // For indexed and linked
    int numBlocks;
    int indexBlock;  // For indexed allocation
};

// Sequential Allocation Simulation
void sequentialAllocation(struct File files[], int *fileCount) {
    if (*fileCount >= MAX_FILES) {
        printf("File limit reached.\n");
        return;
    }

    printf("Enter file name: ");
    scanf("%s", files[*fileCount].name);
    printf("Enter starting block: ");
    scanf("%d", &files[*fileCount].startBlock);
    printf("Enter file size (number of blocks): ");
    scanf("%d", &files[*fileCount].size);

    (*fileCount)++;
}

// Indexed Allocation Simulation
void indexedAllocation(struct File files[], int *fileCount) {
    if (*fileCount >= MAX_FILES) {
        printf("File limit reached.\n");
        return;
    }

    printf("Enter file name: ");
    scanf("%s", files[*fileCount].name);
    printf("Enter index block: ");
    scanf("%d", &files[*fileCount].indexBlock);
    printf("Enter number of data blocks: ");
    scanf("%d", &files[*fileCount].numBlocks);

    for (int i = 0; i < files[*fileCount].numBlocks; i++) {
        printf("Enter data block number %d: ", i + 1);
        scanf("%d", &files[*fileCount].dataBlocks[i]);
    }

    (*fileCount)++;
}

// Linked Allocation Simulation
void linkedAllocation(struct File files[], int *fileCount) {
    if (*fileCount >= MAX_FILES) {
        printf("File limit reached.\n");
        return;
    }

    printf("Enter file name: ");
    scanf("%s", files[*fileCount].name);
    printf("Enter starting block: ");
    scanf("%d", &files[*fileCount].startBlock);
    printf("Enter number of data blocks: ");
    scanf("%d", &files[*fileCount].numBlocks);

    for (int i = 0; i < files[*fileCount].numBlocks; i++) {
        printf("Enter data block number %d: ", i + 1);
        scanf("%d", &files[*fileCount].dataBlocks[i]);
    }

    (*fileCount)++;
}

// Function to display files for each allocation method
void displayFiles(struct File files[], int fileCount, int allocationType) {
    if (fileCount == 0) {
        printf("No files to display.\n");
        return;
    }

    switch (allocationType) {
        case 1:  // Sequential
            printf("\nFiles in Sequential Allocation:\n");
            for (int i = 0; i < fileCount; i++) {
                printf("File: %s, Starting Block: %d, Size: %d blocks\n",
                       files[i].name, files[i].startBlock, files[i].size);
            }
            break;
        case 2:  // Indexed
            printf("\nFiles in Indexed Allocation:\n");
            for (int i = 0; i < fileCount; i++) {
                printf("File: %s, Index Block: %d, Data Blocks: ", files[i].name, files[i].indexBlock);
                for (int j = 0; j < files[i].numBlocks; j++) {
                    printf("%d ", files[i].dataBlocks[j]);
                }
                printf("\n");
            }
            break;
        case 3:  // Linked
            printf("\nFiles in Linked Allocation:\n");
            for (int i = 0; i < fileCount; i++) {
                printf("File: %s, Starting Block: %d, Data Blocks: ", files[i].name, files[i].startBlock);
                for (int j = 0; j < files[i].numBlocks; j++) {
                    printf("%d -> ", files[i].dataBlocks[j]);
                }
                printf("NULL\n");
            }
            break;
        default:
            printf("Invalid allocation type.\n");
            break;
    }
}

int main() {
    struct File files[MAX_FILES];
    int fileCount = 0;
    int choice, allocationType;

    while (1) {
        printf("\nFile Allocation Strategies Simulation\n");
        printf("1. Sequential Allocation\n");
        printf("2. Indexed Allocation\n");
        printf("3. Linked Allocation\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Choose an option (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  // Sequential
                sequentialAllocation(files, &fileCount);
                allocationType = 1;
                break;
            case 2:  // Indexed
                indexedAllocation(files, &fileCount);
                allocationType = 2;
                break;
            case 3:  // Linked
                linkedAllocation(files, &fileCount);
                allocationType = 3;
                break;
            case 4:  // Display Files
                displayFiles(files, fileCount, allocationType);
                break;
            case 5:  // Exit
                return 0;
            default:
                printf("Invalid option! Please try again.\n");
        }
    }

    return 0;
}

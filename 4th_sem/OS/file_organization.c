#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_USERS 5
#define MAX_SUBDIRS 5
#define MAX_NAME_LENGTH 50

// Structure for Single Level Directory
typedef struct {
    char files[MAX_FILES][MAX_NAME_LENGTH];
    int fileCount;
} SingleLevelDirectory;

// Structure for Two Level Directory
typedef struct {
    char userName[MAX_NAME_LENGTH];
    char files[MAX_FILES][MAX_NAME_LENGTH];
    int fileCount;
} UserDirectory;

typedef struct {
    UserDirectory users[MAX_USERS];
    int userCount;
} TwoLevelDirectory;

// Structure for Hierarchical Directory
typedef struct HierarchicalNode {
    char name[MAX_NAME_LENGTH];
    struct HierarchicalNode* subDirs[MAX_SUBDIRS];
    int subDirCount;
} HierarchicalNode;

// Function prototypes
void singleLevelDirectory();
void twoLevelDirectory();
void hierarchicalDirectory();
void addSubDir(HierarchicalNode* node);
void displayHierarchical(HierarchicalNode* node, int level);

int main() {
    int choice;
    printf("File Organization Techniques Simulation\n");
    printf("1. Single Level Directory\n");
    printf("2. Two Level Directory\n");
    printf("3. Hierarchical Directory\n");
    printf("Choose an option (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            singleLevelDirectory();
            break;
        case 2:
            twoLevelDirectory();
            break;
        case 3:
            hierarchicalDirectory();
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

// Function to simulate Single Level Directory
void singleLevelDirectory() {
    SingleLevelDirectory directory;
    directory.fileCount = 0;

    printf("Single Level Directory:\n");
    while (directory.fileCount < MAX_FILES) {
        printf("Enter file name (or 'exit' to finish): ");
        char fileName[MAX_NAME_LENGTH];
        scanf("%s", fileName);

        if (strcmp(fileName, "exit") == 0) {
            break;
        }
        strcpy(directory.files[directory.fileCount], fileName);
        directory.fileCount++;
    }

    printf("Files in Single Level Directory:\n");
    for (int i = 0; i < directory.fileCount; i++) {
        printf("%s\n", directory.files[i]);
    }
}

// Function to simulate Two Level Directory
void twoLevelDirectory() {
    TwoLevelDirectory directory;
    directory.userCount = 0;

    printf("Two Level Directory:\n");
    while (directory.userCount < MAX_USERS) {
        printf("Enter user name (or 'exit' to finish): ");
        char userName[MAX_NAME_LENGTH];
        scanf("%s", userName);

        if (strcmp(userName, "exit") == 0) {
            break;
        }

        strcpy(directory.users[directory.userCount].userName, userName);
        directory.users[directory.userCount].fileCount = 0;

        printf("Enter files for %s:\n", userName);
        while (directory.users[directory.userCount].fileCount < MAX_FILES) {
            printf("Enter file name (or 'exit' to finish): ");
            char fileName[MAX_NAME_LENGTH];
            scanf("%s", fileName);

            if (strcmp(fileName, "exit") == 0) {
                break;
            }

            strcpy(directory.users[directory.userCount].files[directory.users[directory.userCount].fileCount], fileName);
            directory.users[directory.userCount].fileCount++;
        }

        directory.userCount++;
    }

    printf("Files in Two Level Directory:\n");
    for (int i = 0; i < directory.userCount; i++) {
        printf("User: %s\n", directory.users[i].userName);
        for (int j = 0; j < directory.users[i].fileCount; j++) {
            printf("  %s\n", directory.users[i].files[j]);
        }
    }
}

// Function to simulate Hierarchical Directory
void hierarchicalDirectory() {
    HierarchicalNode root;
    strcpy(root.name, "Root");
    root.subDirCount = 0;

    printf("Hierarchical Directory:\n");
    addSubDir(&root);

    printf("Files in Hierarchical Directory:\n");
    displayHierarchical(&root, 0);
}

void addSubDir(HierarchicalNode* node) {
    while (node->subDirCount < MAX_SUBDIRS) {
        printf("Enter subdirectory name for %s (or 'exit' to finish): ", node->name);
        char subDirName[MAX_NAME_LENGTH];
        scanf("%s", subDirName);

        if (strcmp(subDirName, "exit") == 0) {
            break;
        }

        HierarchicalNode* newSubDir = (HierarchicalNode*)malloc(sizeof(HierarchicalNode));
        strcpy(newSubDir->name, subDirName);
        newSubDir->subDirCount = 0;

        addSubDir(newSubDir); // Recursive call to add subdirectories
        node->subDirs[node->subDirCount] = newSubDir;
        node->subDirCount++;
    }
}

void displayHierarchical(HierarchicalNode* node, int level) {
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%s\n", node->name);

    for (int i = 0; i < node->subDirCount; i++) {
        displayHierarchical(node->subDirs[i], level + 1);
    }
}

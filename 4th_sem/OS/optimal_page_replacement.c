#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 30

int pageFaults = 0;

int findOptimalPage(int pages[], int n, int frame[], int f, int index) {
    int farthest = index;
    int replaceIndex = -1;

    for (int i = 0; i < f; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    replaceIndex = i;
                }
                break;
            }
        }
        if (j == n) {
            // If the page is not found in future references, replace it
            return i;
        }
    }
    return (replaceIndex == -1) ? 0 : replaceIndex; // Return 0 if no page is found
}

void optimalPageReplacement(int pages[], int n, int frames) {
    int frame[MAX_FRAMES];
    int index = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1; // Initialize frames to -1 (indicating empty)
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = true; // Page found in memory
                break;
            }
        }

        // If the page is not found, a page fault occurs
        if (!found) {
            // If there is space in the frame
            if (index < frames) {
                frame[index++] = page; // Add the new page to memory
            } else { // Memory is full
                int replaceIndex = findOptimalPage(pages, n, frame, frames, i + 1);
                frame[replaceIndex] = page; // Replace the optimal page
            }
            pageFaults++; // Increment page fault count
        }

        // Display current frame status
        printf("Frames: ");
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) {
                printf("%d ", frame[j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int n, frames;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[MAX_PAGES];
    printf("Enter the pages (space separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    optimalPageReplacement(pages, n, frames);

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}

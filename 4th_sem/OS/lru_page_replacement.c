#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 30

int pages[MAX_PAGES], frame[MAX_FRAMES];
int pageFaults = 0;

void displayFrames(int frames[], int n) {
    printf("Frames: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", frames[i]);
    }
    printf("\n");
}

void lruPageReplacement(int pages[], int n, int frames) {
    int index = 0; // Track the number of pages in memory

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1; // Page found in memory
                break;
            }
        }

        // If the page is not found, a page fault occurs
        if (!found) {
            // If there is space in the frame
            if (index < frames) {
                frame[index] = page;
                index++;
            } else { // Memory is full
                // Find the least recently used page
                int lruIndex = 0; // Start with the first frame
                for (int j = 1; j < frames; j++) {
                    if (frame[j] < frame[lruIndex]) {
                        lruIndex = j; // Update index if current frame is less recently used
                    }
                }
                frame[lruIndex] = page; // Replace the LRU page with the new page
            }
            pageFaults++; // Increment page fault count
        }

        // Display current frame status
        displayFrames(frame, frames);
    }
}

int main() {
    int n, frames;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the pages (space separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    lruPageReplacement(pages, n, frames);

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}

#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 30

typedef struct {
    int page;
    int frequency;
} Page;

Page frame[MAX_FRAMES];
int pageFaults = 0;

void displayFrames(Page frames[], int n) {
    printf("Frames: ");
    for (int i = 0; i < n; i++) {
        printf("%d(%d) ", frames[i].page, frames[i].frequency);
    }
    printf("\n");
}

void lfuPageReplacement(int pages[], int n, int frames) {
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frames; j++) {
            if (frame[j].page == page) {
                found = 1; // Page found in memory
                frame[j].frequency++; // Increment frequency
                break;
            }
        }

        // If the page is not found, a page fault occurs
        if (!found) {
            // If there is space in the frame
            int minFrequencyIndex = -1;
            int minFrequency = 99999; // Arbitrarily large number

            for (int j = 0; j < frames; j++) {
                if (frame[j].frequency < minFrequency) {
                    minFrequency = frame[j].frequency;
                    minFrequencyIndex = j; // Update index for the least frequently used page
                }
            }

            // If memory is full, replace the least frequently used page
            if (minFrequencyIndex != -1) {
                frame[minFrequencyIndex].page = page; // Replace LFU page
                frame[minFrequencyIndex].frequency = 1; // Set frequency of new page to 1
            }

            pageFaults++; // Increment page fault count
        }

        // Display current frame status
        displayFrames(frame, frames);
    }
}

int main() {
    int n, frames;

    // Initialize frame
    for (int i = 0; i < MAX_FRAMES; i++) {
        frame[i].page = -1; // Initialize pages to -1 (indicating empty)
        frame[i].frequency = 0; // Initialize frequency to 0
    }

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

    lfuPageReplacement(pages, n, frames);

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}

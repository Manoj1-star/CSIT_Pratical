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

void fifoPageReplacement(int pages[], int n, int frames) {
    int index = 0; // Index to track the oldest page in frame

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
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
                // Replace the oldest page
                frame[index % frames] = page;
                index++;
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

    fifoPageReplacement(pages, n, frames);

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}

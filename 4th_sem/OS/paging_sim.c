#include <stdio.h>

#define MAX 100

void simulatePaging(int logical_addresses[], int n, int page_size, int page_table[], int num_frames) {
    for (int i = 0; i < n; i++) {
        int logical_address = logical_addresses[i];
        int page_number = logical_address / page_size;
        int offset = logical_address % page_size;

        if (page_number >= num_frames) {
            printf("Logical Address %d is invalid (page number out of bounds)\n", logical_address);
            continue;
        }

        int frame_number = page_table[page_number];
        if (frame_number == -1) {
            printf("Logical Address %d cannot be mapped (page not loaded into memory)\n", logical_address);
        } else {
            int physical_address = frame_number * page_size + offset;
            printf("Logical Address: %d -> Physical Address: %d\n", logical_address, physical_address);
        }
    }
}

int main() {
    int page_size, num_pages, num_frames, num_addresses;

    // Input page size
    printf("Enter the page size: ");
    scanf("%d", &page_size);

    // Input number of pages in logical memory
    printf("Enter the number of pages in logical memory: ");
    scanf("%d", &num_pages);

    // Input number of frames in physical memory
    printf("Enter the number of frames in physical memory: ");
    scanf("%d", &num_frames);

    // Input the page table mapping
    int page_table[MAX];
    printf("Enter the page table (-1 for pages not loaded into memory):\n");
    for (int i = 0; i < num_pages; i++) {
        printf("Page %d maps to frame: ", i);
        scanf("%d", &page_table[i]);
    }

    // Input number of logical addresses to translate
    printf("Enter the number of logical addresses to translate: ");
    scanf("%d", &num_addresses);

    // Input logical addresses
    int logical_addresses[num_addresses];
    for (int i = 0; i < num_addresses; i++) {
        printf("Enter logical address %d: ", i + 1);
        scanf("%d", &logical_addresses[i]);
    }

    // Simulate the paging translation
    simulatePaging(logical_addresses, num_addresses, page_size, page_table, num_frames);

    return 0;
}

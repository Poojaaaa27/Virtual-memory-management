#include <stdio.h>
#include <stdlib.h>

// Constants
#define NUM_PAGES 64
#define PAGE_SIZE 4096  // Page size in bytes

// Page Table Entry
typedef struct {
    int valid;
    int frameNumber;
} PageTableEntry;

// Page Table
PageTableEntry pageTable[NUM_PAGES];

// Function to initialize the page table
void initializePageTable() {
    for (int i = 0; i < NUM_PAGES; i++) {
        pageTable[i].valid = 0;  // Mark all pages as invalid initially
        pageTable[i].frameNumber = -1;  // Frame number is uninitialized
    }
}

// Function to map a virtual page to a physical frame
void mapPageToFrame(int virtualPage, int frame) {
    pageTable[virtualPage].valid = 1;
    pageTable[virtualPage].frameNumber = frame;
}

// Function to retrieve the physical frame for a virtual page
int getPhysicalFrame(int virtualPage) {
    if (pageTable[virtualPage].valid) {
        return pageTable[virtualPage].frameNumber;
    } else {
        return -1;  // Page is not in physical memory
    }
}

int main() {
    // Initialize the page table
    initializePageTable();

    // Simulate mapping a virtual page to a physical frame
    mapPageToFrame(0, 5);
    mapPageToFrame(3, 2);
    mapPageToFrame(7, 8);

    // Simulate a memory access
    int virtualAddress = 3584;  // Address within virtual page 0
    int virtualPage = virtualAddress / PAGE_SIZE;
    int offset = virtualAddress % PAGE_SIZE;

    int physicalFrame = getPhysicalFrame(virtualPage);

    if (physicalFrame != -1) {
        printf("Virtual Address: %d\n", virtualAddress);
        printf("Virtual Page: %d\n", virtualPage);
        printf("Offset: %d\n", offset);
        printf("Physical Frame: %d\n", physicalFrame);
        printf("Physical Address: %d\n", (physicalFrame * PAGE_SIZE) + offset);
    } else {
        printf("Page is not in physical memory. Page fault!\n");
    }

    return 0;
}

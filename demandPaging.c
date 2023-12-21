#include <stdio.h>
#include <stdlib.h>

// Constants
#define PAGE_SIZE 4096  // Page size in bytes
#define NUM_PAGES 8    // Total number of pages
#define NUM_FRAMES 4   // Total number of physical memory frames

// Page Table Entry
typedef struct {
    int valid;
    int frame;
} PageTableEntry;

PageTableEntry pageTable[NUM_PAGES];

// Physical Memory (simulated)
char physicalMemory[NUM_FRAMES][PAGE_SIZE];

// Function to simulate loading a page into physical memory
void loadPage(int pageNum) {
    // Simulate loading a page from secondary storage into physical memory
    // In a real system, this would involve I/O operations.
    printf("Loading Page %d into Physical Memory\n", pageNum);
    for (int i = 0; i < PAGE_SIZE; i++) {
        physicalMemory[pageNum][i] = 'A' + (char)(pageNum % 26);
    }
}

// Function to handle a page fault
void handlePageFault(int pageNum) {
    int freeFrame = -1;

    // Find a free frame in physical memory
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (pageTable[i].valid == 0) {
            freeFrame = i;
            break;
        }
    }

    // If all frames are in use, perform page replacement (e.g., LRU or FIFO)
    if (freeFrame == -1) {
        // Implement a page replacement algorithm here
        // For simplicity, we won't replace pages in this example.
    }

    // Load the page into physical memory
    loadPage(pageNum);

    // Update the page table
    pageTable[pageNum].valid = 1;
    pageTable[pageNum].frame = freeFrame;
}

// Function to read from a virtual address
char readFromVirtualAddress(int virtualAddress) {
    int pageNum = virtualAddress / PAGE_SIZE;
    int offset = virtualAddress % PAGE_SIZE;

    if (pageTable[pageNum].valid == 0) {
        // Page fault - handle it
        handlePageFault(pageNum);
    }

    // Access the page in physical memory
    char data = physicalMemory[pageTable[pageNum].frame][offset];
    return data;
}

int main() {
    // Initialize the page table
    for (int i = 0; i < NUM_PAGES; i++) {
        pageTable[i].valid = 0;
        pageTable[i].frame = -1;
    }

    // Read from a virtual address (simulate a memory access)
    int virtualAddress = 8192;  // Example virtual address
    char data = readFromVirtualAddress(virtualAddress);

    printf("Data at virtual address %d: %c\n", virtualAddress, data);

    return 0;
}

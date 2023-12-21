#include <stdio.h>
#include <stdlib.h>

// Constants
#define NUM_FRAMES 4   // Total number of physical memory frames

// Physical Memory (simulated)
int physicalMemory[NUM_FRAMES];

// Variables for tracking pages in memory
int pagesInMemory[NUM_FRAMES];
int pageQueue[NUM_FRAMES];
int queueFront = 0;
int queueRear = 0;
int pageQueueSize = 0;

// Function to initialize the physical memory
void initializePhysicalMemory() {
    for (int i = 0; i < NUM_FRAMES; i++) {
        physicalMemory[i] = -1;  // -1 indicates an empty frame
    }
}

// Function to check if a page is in physical memory
int isPageInMemory(int page) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (physicalMemory[i] == page) {
            return 1;
        }
    }
    return 0;
}

// Function to handle page replacement using the FIFO algorithm
void handlePageReplacement(int newPage) {
    int victimPage = pageQueue[queueFront];  // Get the page to be replaced (FIFO)
    queueFront = (queueFront + 1) % NUM_FRAMES;  // Update the front of the queue

    // Find the victim page in physical memory
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (physicalMemory[i] == victimPage) {
            physicalMemory[i] = newPage;  // Replace the victim page with the new page
            break;
        }
    }
}

// Function to access a page
void accessPage(int page) {
    if (isPageInMemory(page)) {
        printf("Page %d is in physical memory\n", page);
    } else {
        printf("Page %d is not in physical memory (Page fault)\n", page);
        if (pageQueueSize < NUM_FRAMES) {
            // There is an empty frame in physical memory
            physicalMemory[pageQueueSize] = page;
            pageQueue[queueRear] = page;
            queueRear = (queueRear + 1) % NUM_FRAMES;
            pageQueueSize++;
        } else {
            // Physical memory is full, perform page replacement
            handlePageReplacement(page);
            // Add the new page to the page queue
            pageQueue[queueRear] = page;
            queueRear = (queueRear + 1) % NUM_FRAMES;
        }
    }
}

int main() {
    // Initialize physical memory
    initializePhysicalMemory();

    // Access pages to demonstrate page replacement
    accessPage(1);
    accessPage(2);
    accessPage(3);
    accessPage(1);
    accessPage(4);
    accessPage(5);
    accessPage(2);

    return 0;
}

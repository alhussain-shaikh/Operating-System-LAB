#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOGICAL_ADDRESS_SPACE_SIZE 4
#define PAGE_TABLE_SIZE 4
#define PAGE_SIZE 4
#define FRAME_SIZE 8

int main() {
    char logicalAddressBinary[5];
    int logicalAddress, choose, pageNumber, offset, frameNumber, physicalAddress, RA;
    int pageTable[4] = {5, 6, 1, 2}; // Page table maps page numbers to physical frame numbers

    printf("Enter the logical Address : ");
    scanf("%s", logicalAddressBinary);

    printf("Logical address (binary): %s\n", logicalAddressBinary);
    logicalAddress = strtol(logicalAddressBinary, NULL, 2);
    printf("Logical address (decimal): %d\n\n", logicalAddress);

    printf("Enter Your Choice: \n");
    printf("1. Using Page No and offset\n");
    printf("2. Using Regular formula Formula\n");
    scanf("%d", &choose);

    switch(choose) {
        case 1:
            pageNumber = logicalAddress / PAGE_SIZE;
            offset = logicalAddress % PAGE_SIZE;
            printf("Page number: %d\n", pageNumber);
            printf("Offset: %d\n", offset);
            
            if (pageNumber >= PAGE_TABLE_SIZE) {
                printf("ERROR: Page number exceeds page table size\n");
                return 0;
            }
            frameNumber = pageTable[pageNumber];
            printf("Physical frame number: %d\n", frameNumber);
            physicalAddress = (frameNumber * FRAME_SIZE) + offset;
            printf("Physical Address: %d\n", physicalAddress);
            break;

        case 2:
            pageNumber = logicalAddress / PAGE_SIZE;
            frameNumber = pageTable[pageNumber];
            RA = (frameNumber * FRAME_SIZE) + (logicalAddress % PAGE_SIZE);
            printf("Real Address: %d\n", RA);
            break;
    }

    return 0;
}

/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main() {
    int frameSize, referenceSize, i, j, k, pageFaults = 0, leastUsedIndex;

    printf("Enter the size of the page frame: ");
    scanf("%d", &frameSize);

    printf("Enter the size of the reference string: ");
    scanf("%d", &referenceSize);

    int referenceString[referenceSize];
    printf("Enter the reference string: ");
    for (i = 0; i < referenceSize; i++)
        scanf("%d", &referenceString[i]);

    int frame[frameSize], pageFault[frameSize], usedCounter[frameSize];
    for (i = 0; i < frameSize; i++) {
        frame[i] = -1;
        usedCounter[i] = 0;
    }

    printf("\nGantt Chart:\n");

    for (i = 0; i < referenceSize; i++) {
        int page = referenceString[i];
        int exists = 0;

        for (j = 0; j < frameSize; j++) {
            if (frame[j] == page) {
                exists = 1;
                usedCounter[j] = i + 1;
                break;
            }
        }

        if (exists) {
            printf("|   ");
        } else {
            leastUsedIndex = 0;

            for (j = 1; j < frameSize; j++) {
                if (usedCounter[j] < usedCounter[leastUsedIndex]) {
                    leastUsedIndex = j;
                }
            }

            frame[leastUsedIndex] = page;
            usedCounter[leastUsedIndex] = i + 1;
            pageFaults++;

            printf("|*  ");
        }

        for (j = 0; j < frameSize; j++) {
            if (frame[j] != -1)
                printf("%d  ", frame[j]);
            else
                printf("   ");
        }

        printf("|\n");
    }

    printf("\nNumber of page faults: %d\n", pageFaults);

    return 0;
}



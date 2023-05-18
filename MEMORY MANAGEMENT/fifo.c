#include <stdio.h>

int main() {
    int frameSize, referenceSize, i, j, k, pageFaults = 0;

    printf("Enter the size of the page frame: ");
    scanf("%d", &frameSize);

    printf("Enter the size of the reference string: ");
    scanf("%d", &referenceSize);

    int referenceString[referenceSize];
    printf("Enter the reference string: ");
    for (i = 0; i < referenceSize; i++)
        scanf("%d", &referenceString[i]);

    int frame[frameSize], pageFault[frameSize];
    for (i = 0; i < frameSize; i++)
        frame[i] = -1;

    printf("\nGantt Chart:\n");

    for (i = 0; i < referenceSize; i++) {
        int page = referenceString[i];
        int exists = 0;

        for (j = 0; j < frameSize; j++) {
            if (frame[j] == page) {
                exists = 1;
                break;
            }
        }

        if (exists) {
            printf("|   ");
        } else {
            frame[pageFaults % frameSize] = page;
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



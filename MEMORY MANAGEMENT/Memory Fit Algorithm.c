#include <stdio.h>

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    
    for (int i = 0; i < n; i++) {
        int bestBlock = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestBlock == -1)
                    bestBlock = j;
                else if (blockSize[bestBlock] > blockSize[j])
                    bestBlock = j;
            }
        }
        if (bestBlock != -1) {
            allocation[i] = bestBlock;
            blockSize[bestBlock] -= processSize[i];
            printf("Remaining memory in block %d after inserting process %d: %d\n", (bestBlock + 1), processSize[i], blockSize[bestBlock]);
        }
    }

    printf("\nProcess No.\tProcess Size\t\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t\t%d\t\t", (i + 1), processSize[i]);
        if (allocation[i] != -1)
            printf("%d", (allocation[i] + 1));
        else
            printf("Not Allocated");
        printf("\n");
    }
}

void NextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n], j = 0, t = m - 1;
    
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    
    for (int i = 0; i < n; i++) {
        while (j < m) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                printf("Remaining memory in block %d after inserting process %d: %d\n", (j + 1), processSize[i], blockSize[j]);
                t = (j - 1) % m;
                //printf("New Endpoint(block): %d\n", (t + 1));
                break;
            }
            if (t == j) {
                t = (j - 1) % m;
                break;
            }
            j = (j + 1) % m;
        }
    }

    printf("\nProcess No.\tProcess Size\t\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t\t%d\t\t", (i + 1), processSize[i]);
        if (allocation[i] != -1)
            printf("%d", (allocation[i] + 1));
        else
            printf("Not Allocated");
        printf("\n");
    }
}

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                printf("Remaining memory in block %d after inserting process %d: %d\n", (j + 1),processSize[i], blockSize[j]);
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\t\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t\t%d\t\t", (i + 1), processSize[i]);
        if (allocation[i] != -1)
            printf("%d", (allocation[i] + 1));
        else
            printf("Not Allocated");
        printf("\n");
    }
}
void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++)
    allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int wstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (wstIdx == -1)
                    wstIdx = j;
                else if (blockSize[wstIdx] < blockSize[j])
                    wstIdx = j;
            }
        }
        if (wstIdx != -1) {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= processSize[i];
            printf("Remaining memory in block %d after inserting process %d: %d\n", (wstIdx + 1), processSize[i], blockSize[wstIdx]);
        }
    }
    
    printf("\nProcess No.\tProcess Size\t\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t\t%d\t\t", (i + 1), processSize[i]);
        if (allocation[i] != -1)
            printf("%d", (allocation[i] + 1));
        else
            printf("Not Allocated");
        printf("\n");
    }
    
}
int main() {
//int blockSize[] = {100, 500, 200, 300, 600};
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter process sizes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }
    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("Enter Your Choice\n");
        printf("1. First-Fit\n");
        printf("2. Next-Fit\n");
        printf("3. Best-Fit\n");
        printf("4. Worst-Fit\n");
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int blockSize[] = {100, 500, 200, 300, 600};
                int m = sizeof(blockSize) / sizeof(blockSize[0]);
                firstFit(blockSize, m, processSize, n);
                break;
            }
            case 2: {
                int blockSize1[] = {100, 500, 200, 300, 600};
                int m = sizeof(blockSize1) / sizeof(blockSize1[0]);
                NextFit(blockSize1, m, processSize, n);
                break;
            }
            case 3: {
                int blockSize2[] = {100, 500, 200, 300, 600};
                int m = sizeof(blockSize2) / sizeof(blockSize2[0]);
                bestFit(blockSize2, m, processSize, n);
                break;
            }
            case 4: {
                int blockSize3[] = {100, 500, 200, 300, 600};
                int m = sizeof(blockSize3) / sizeof(blockSize3[0]);
                worstFit(blockSize3, m, processSize, n);
                break;
            }
            
        }
        
    }
    
}

    



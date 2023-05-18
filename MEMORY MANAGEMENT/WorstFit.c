#include <stdio.h>

void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    int i, j, wstIdx;

    for (i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (i = 0; i < n; i++)
    {
        wstIdx = -1;
        for (j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (wstIdx == -1)
                {
                    wstIdx = j;
                }
                else if (blockSize[wstIdx] < blockSize[j])
                {
                    wstIdx = j;
                }
            }
        }

        if (wstIdx != -1)
        {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= processSize[i];
            printf("Remaining memory in block %d after inserting process %d: %d\n", wstIdx + 1, processSize[i], blockSize[wstIdx]);
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < n; i++)
    {
        printf(" %d\t\t\t%d\t\t\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
        {
            printf("%d", allocation[i] + 1);
        }
        else
        {
            printf("Not Allocated");
        }
        printf("\n");
    }
}

int main()
{
    int blockSize[] = {100, 500, 200, 300, 600};
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processSize[n];

    printf("Enter process sizes:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &processSize[i]);
    }

    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    worstFit(blockSize, m, processSize, n);

    return 0;
}

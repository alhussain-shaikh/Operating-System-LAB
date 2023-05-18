#include <stdio.h>

void NextFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    int i, j = 0, t = m - 1;

    for (i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (i = 0; i < n; i++)
    {
        while (j < m)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                printf("Remaining memory in block %d after inserting process %d: %d\n", j + 1, processSize[i], blockSize[j]);
                t = (j - 1) % m;
                break;
            }

            if (t == j)
            {
                t = (j - 1) % m;
                break;
            }

            j = (j + 1) % m;
        }
    }

    printf("\nProcess No.\t\t\tProcess Size\t\t\tBlock no.\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t\t\t\t%d\t\t\t\t\t\t", i + 1, processSize[i]);
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
    NextFit(blockSize, m, processSize, n);

    return 0;
}

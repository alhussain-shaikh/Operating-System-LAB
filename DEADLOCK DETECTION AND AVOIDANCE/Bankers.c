// BANKERS ALGORITHM DETECTION AND AVOIDANCE WITH SAFE SEQUENCE
#include <stdio.h>
int max[10][10], allocation[10][10], need[10][10];
int avail[10];
int np; // no of processes
int nr; // no of resources

void input_matrix(int matrix[10][10])
{
    int i, j;
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void display_matrix(int matrix[10][10])
{
    int i, j;
    for (i = 0; i < np; i++)
    {
        printf("\n P%d", i);
        for (j = 0; j < nr; j++)
        {
            printf(" %d", matrix[i][j]);
        }
    }
}

void calculate_need()
{
    int i, j;
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void bankers()
{
    int i, j;
    int k, flag = 0;
    int finish[10], safe_seq[10];
    for (i = 0; i < np; i++)
    {
        finish[i] = 0; // Declare all processes are incomplete
    }

    for (i = 0; i < np; i++)
    {
        flag = 0;
        if (finish[i] == 0)
        { // Excecute the incomplete process
            for (j = 0; j < nr; j++)
            {
                if (need[i][j] > avail[j])
                {
                    flag = 1;
                    break; // break a loop as need is greater than available
                }
            }

            if (flag == 0) // Need is lesser than available so complete the process
            {
                finish[i] = 1;
                safe_seq[k] = i;
                k++;

                // Add the allocated resources of finished process in available resources
                for (j = 0; j < nr; j++)
                {
                    avail[j] += allocation[i][j];
                    // starting from first process again
                    i = -1;
                }
            }
        }

        flag = 0; // check if all prorcess are completed
        for (i = 0; i < np; i++)
        {
            if (finish[i] == 0)
            {
                printf("\n The system is in deadlock\n");
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            printf("\n The system is in safe state!\n THe safe sequence is ==>>");
            for (i = 0; i < np; i++)
            {
                printf("P %d", safe_seq);
            }
        }
    }
}

int main()
{
    int j;
    printf("\n Enter the no. of Processes:");
    scanf("%d", &np);
    printf("\n Enter the no. of Resources:");
    scanf("%d", &nr);
    printf("\n  Enter initial allocation matrix\n");
    input_matrix(allocation);
    printf("\n Enter the max requirement matrix");
    input_matrix(max);

    printf("\n Enter the available resources");
    for (j = 0; j < nr; j++)
    {
        scanf("%d", &avail[j]);
    }

    // Displaying entered data
    printf("\n ---------------The entered data is ----------\n");
    printf("\n The initial allocation");
    display_matrix(allocation);

    printf("\n\n\nThe maximum requirement requirement\n");
    display_matrix(max);

    printf("\n\n The Available Resources \n");
    for (j = 0; j < nr; j++)
    {
        printf("%d", avail[j]);
    }

    // Calculate and display
    calculate_need();
    printf("\n\n\n Need is:\n");

    display_matrix(need);

    // Execute the processes using Bankers Algorithm
    bankers();
    printf("\n\n\n\n\n\n\n");
    return 0;
}

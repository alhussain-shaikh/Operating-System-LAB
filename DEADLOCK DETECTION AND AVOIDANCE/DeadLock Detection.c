#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void Timer(long t, bool c, char* Pattern) {
    int i;
    for (i = 0; i < 20; i++) {
        // Sleep implementation may vary depending on the platform
        // This is just a placeholder
        // Replace with the appropriate sleep function in your environment
        // Sleep(t);
        if (c == true) {
            printf("%s", Pattern);
        }
    }
}

void motion(char* s, long t) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        printf("%c", s[i]);
        Timer(t, false, "");
    }
    printf("\n");
}

void deadLock() {
    printf("****** Deadlock Detection ******\n\n");
    printf("Enter number of Processes:  ");
    int n;
    scanf("%d", &n);

    printf("Enter number of resources: ");
    int r;
    scanf("%d", &r);
    int AllocationTable[n][r];

    // Allocation Table
    printf("Enter Allocation Table for each Process: \n");

    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &AllocationTable[i][j]);
        }
    }

    // Request/Max Table Entry
    int Request[n][r];
    printf("Enter Max/Request Table for each Process\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &Request[i][j]);
        }
    }

    // Input Available or Total Resource Instance
    printf("Select from below Option :\n");
    printf("1.Available\n");
    printf("2.Total Resource\n");

    int option;
    scanf("%d", &option);
    int Available[r];
    int Total[r];

    if (option == 1) {
        printf("Enter Available Resource Instance : \n");
        for (i = 0; i < r; i++) {
            scanf("%d", &Available[i]);
        }
    } else if (option == 2) {
        printf("Enter Total Resource Instance : \n");
        for (i = 0; i < r; i++) {
            scanf("%d", &Total[i]);
        }
    } else {
        printf("Invalid Option\n");
    }

    // Avaliable Table
    int Need[n][r];

    // Calculating Available/Total Resource
    if (option == 1) {
        printf("Total Resource Instance : \n");

        for (i = 0; i < r; i++) {
            int sum = 0;
            sum += Available[i];
            for (j = 0; j < n; j++) {
                sum += AllocationTable[j][i];
            }
            Total[i] = sum; // Filling Total Resource Instance
            printf("%d ", sum);
        }
        printf("\n");
    } else {
        motion("Available Resource Instance : ", 5);
        for (i = 0; i < r; i++) {
            int sum = 0;
            for (j = 0; j < n; j++) {
                sum += AllocationTable[j][i];
            }
            printf("%d ", (Total[i] - sum));
            Available[i] = (Total[i] - sum); // Filling Available Resource Instance
        }
        
    }
    printf("\n");
    // Checking for any deadlock
    printf("\nRunning Deadlock Detection ");
    Timer(150, true, ".");
    printf("\n");
    
    // Operational Container
    int stack[n];
    int top = -1;
    
    // Safe Sequence Collector
    char* stack1[n];
    
    bool state[n];
    
    printf("\nInitial State of Processes.");
    Timer(150, true, ".");
    printf("\n");
    
    for (i = 0; i < n; i++) {
        state[i] = false;
        printf("P%d  %d\n", i, state[i]);
    }
    
    for (i = 0; i < n; i++) {
        stack[++top] = i;
    }
    
    int counter = 0;
    int ke = 0;
    
    while (top != -1) {
        ++counter;
        for (i = 0; i < n; i++) {
            int key = 0;
            for (j = 0; j < r; j++) {
                if (state[i] == true || Request[i][j] > Available[j]) {
                    key = -9;
                    break;
                }
            }
            if (key == -9) {
                continue;
            } else {
                for (j = 0; j < r; j++) {
                    Need[i][j] = 0;
                    Available[j] += AllocationTable[i][j];
                    Need[i][j] = Available[j];
                }
                state[i] = true; // Assigning status update
                if (top == -1) {
                    break;
                }
                stack1[++ke] = malloc(10 * sizeof(char));
                sprintf(stack1[ke], "P%d", i);
                top--;
                printf("\nStatus of Process for %d iteration", i);
                Timer(150, true, ".");
                printf("\n");
                for (int k = 0; k < n; k++) {
                    printf("P%d  %d\n", k, state[k]);
                }
            }
            // printf("Calculating Available Matrix, Please wait");
            // Timer(130, true, ".");
            // printf("\n");
    
            // for (i = 0; i < n; i++) {
            //     printf("P%d\t", i);
            //     for (j = 0; j < r; j++) {
            //         printf("%d\t", Need[i][j]);
            //         Timer(20, false, "");
            //     }
            //     printf("\n");
            // }
        }
    
        if (counter > (n * r)) {
            printf("           ");
            motion("*** WARNING ***", 3);
            printf("   Deadlock Detected, Exiting  ");
            Timer(120, true, "X");
            printf("\n");
            ke = -9;
            break;
        }
    }
    
        /* Result */
    if (ke == 0) {
        motion("Safe State Found\n", 3);
        motion("Safe Sequence is: ", 2);
        for (i = 1; i <= ke; i++) {
            printf("%s ", stack1[i]);
            Timer(60, false, "");
            free(stack1[i]);
        }
        printf("\n");
    }
    printf("\nCalculating Available Matrix, Please wait\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (j = 0; j < r; j++) {
            printf("%d\t", Need[i][j]);
            Timer(20, false, "");
        }
        printf("\n");
    }
    motion("Safe State Found\n", 3);
    motion("Safe Sequence is: ", 2);
    for (i = 1; i <= ke; i++) {
            printf("%s ", stack1[i]);
            Timer(60, false, "");
            free(stack1[i]);
        }
        printf("\n");
}
    
int main() {
    deadLock();
    return 0;
}
/*
Allocation Table
0       1       0
2       0       0
3       0       3
2       1       1
0       0       2

Max Table
0       0       0
2       0       2
0       0       0
1       0       0
0       0       2

Available
0       0       0
*/


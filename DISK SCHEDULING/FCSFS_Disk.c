#include <stdio.h>
int main()
{
    int n, r, head, total = 0;
    printf("Enter the number of tracks : ");
    scanf("%d", &n);
    printf("\nEnter the number of requests : ");
    scanf("%d", &r);
    printf("\nEnter the starting head position : ");
    scanf("%d", &head);
    int arr[r];
    for (int i = 0; i < r; i++)
    {
        printf("\nEnter the track Number : %d ", i + 1);
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < r; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n\n");
    printf("Current track \t\t No.of tracks traversed ");
    printf("\n");
    for (int i = 0; i < r; i++)
    {
        total += abs(arr[i] - head);
        printf("%d \t\t\t %d", arr[i], abs(arr[i] - head));
        head = arr[i];
        printf("\n");
    }
    printf("\nTotal : %d ", total);
}
#include <stdio.h>
#include <stdlib.h>
int search(int arr[], int arrSize, int a)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] == a)
            return 1;
    }
    return 0;
}
void main()
{
    printf("Enter CHP \n");
    int chp, tracks;
    scanf("%d", &chp);
    printf("Enter total number of tracks\n");
    scanf("%d", &tracks);
    int track[tracks];
    printf("Enter the size of queue\n");
    int queueSize;
    scanf("%d", &queueSize);
    int queue[queueSize];
    printf("Enter the elements of the queue\n");
    for (int i = 0; i < queueSize; i++)
    {
        scanf("%d", &queue[i]);
    }
    printf("SCAN Algorithm started in clockwise direction\n");
    int j = 0;
    int prev;
    int TrackCount = 0;
    // chp to max
    prev = chp;
    int trackArr[queueSize];
    int Serached[queueSize];
    for (int i = chp; i < tracks; i++)
    {
        if (search(queue, queueSize, i) == 1)
        {
            Serached[j] = i;
            TrackCount += (i - prev);
            trackArr[j] = (i - prev);
            // printf("%d",(i - prev));
            prev = i;
            j++;
        }
    }
    for (int i = chp; i >= 0; i--)
    {
        if (search(queue, queueSize, i) == 1)
        {
            Serached[j] = i;
            TrackCount += (prev - i);
            trackArr[j] = (prev - i);
            prev = i;
            j++;
        }
    }
    printf("Nexxt Track to No of Tracks\n");
    for (int i = 0; i < queueSize - 1; i++)
    {
        printf("%d %d\n", Serached[i], trackArr[i]);
    }
    printf("\nTotal Track count = %d \n", TrackCount);
    // printf("%d",search(queue,queueSize,92));
}
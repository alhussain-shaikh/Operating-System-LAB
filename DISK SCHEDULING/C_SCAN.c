#include <stdio.h>
#include <stdlib.h>
#define MAX_TRACKS 200
#define MAX_REQUESTS 100
void c_scan(int initial_position, int requests[], int n)
{
    int i, j, index, tracks_traversed = 0;
    int track_sequence[MAX_TRACKS];
    int tracks_before_initial[MAX_TRACKS];
    int tracks_before_current[MAX_TRACKS];
    int prev_track = initial_position;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (requests[i] > requests[j])
            {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        if (requests[i] >= initial_position)
        {
            index = i;
            break;
        }
    }
    for (i = index; i < n; i++)
    {
        track_sequence[i - index] = requests[i];
        tracks_traversed += abs(track_sequence[i - index] - prev_track);
        prev_track = track_sequence[i - index];
    }
    track_sequence[n - index] = 0;
    for (i = 0; i < index; i++)
    {
        track_sequence[n - index + i] = requests[i];
        tracks_traversed += abs(track_sequence[n - index + i] - prev_track);
        prev_track = track_sequence[n - index + i];
    }
    tracks_before_initial[0] = initial_position;
    for (i = 0; i < n; i++)
    {
        tracks_before_initial[i + 1] = track_sequence[i];
    }
    tracks_before_current[0] = initial_position;
    for (i = 0; i < n; i++)
    {
        tracks_before_current[i + 1] = track_sequence[i];
    }
    printf("Total tracks traversed: %d\n", tracks_traversed);
    printf("Track sequence: ");
    for (i = 0; i < n; i++)
    {
        if (i < index)
        {
            printf("(%d, %d) ", track_sequence[i], abs(tracks_before_initial[i] - tracks_before_initial[i - 1]));
        }
        else
        {
            printf("(%d, %d) ", track_sequence[i], abs(tracks_before_current[i] - tracks_before_current[i - 1]));
        }
    }
}
int main()
{
    int initial_position, requests[MAX_REQUESTS], n, i;
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &initial_position);
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }
    c_scan(initial_position, requests, n);
    return 0;
}


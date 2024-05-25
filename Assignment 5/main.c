// Owais Khan
// Comp 322L
// Assignment 4

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Declare global variables, including dynamic array to store sequence of traversed tracks
/*********************************************************/

#define MAX_TRACKS 1000 
#define MAX_SIZE 1000 

int track_count = 0;
int track_sequence[MAX_SIZE];

/*********************************************************/

void enter_sequence_size() {
    printf("Enter size of sequence: ");
    scanf("%d", &track_count);
    if (track_count < 1 || track_count > MAX_SIZE) {
        printf("Invalid size. Please enter a value between 1 and %d.\n", MAX_SIZE);
        track_count = 0; // Reset to avoid invalid size
    }
}

/*********************************************************/
void get_tracks() {
    for (int i = 0; i < track_count; i++) {
        scanf("%d", &track_sequence[i]);
        if (track_sequence[i] < 0 || track_sequence[i] >= MAX_TRACKS) {
            printf("Invalid track number %d. Please enter a value between 0 and %d.\n", track_sequence[i], MAX_TRACKS - 1);
            i--; // Re-read the current track
        }
    }
}
/*********************************************************/

void fifo() {
    int start_track;
    printf("Enter the starting track: ");
    scanf("%d", &start_track);

    if (start_track < 0 || start_track >= MAX_TRACKS) {
        printf("Invalid starting track. Please enter a value between 0 and %d.\n", MAX_TRACKS - 1);
        return;
    }

    printf("Enter the sequence of tracks to seek: ");
    get_tracks();

    int total_distance = 0;
    int current_track = start_track;
    printf("Traversed sequence from track %d: ", start_track);
    for (int i = 0; i < track_count; i++) {
        total_distance += abs(track_sequence[i] - current_track);
        printf("%d ", track_sequence[i]);
        current_track = track_sequence[i];
    }
    printf("\nTotal distance traveled: %d\n", total_distance);
}

/*********************************************************/
void sstf() {
    int start_track;
    printf("Enter the starting track: ");
    scanf("%d", &start_track);

    if (start_track < 0 || start_track >= MAX_TRACKS) {
        printf("Invalid starting track. Please enter a value between 0 and %d.\n", MAX_TRACKS - 1);
        return;
    }

    printf("Enter the sequence of tracks to seek: ");
    get_tracks();

    int total_distance = 0;
    int current_track = start_track;
    int remaining_tracks = track_count;

    printf("Traversed sequence from track %d: ", start_track);
    while (remaining_tracks > 0) {
        int shortest_distance = INT_MAX;
        int next_track_index = -1;
        for (int i = 0; i < track_count; i++) {
            if (track_sequence[i] != -1) {
                int distance = abs(track_sequence[i] - current_track);
                if (distance < shortest_distance) {
                    shortest_distance = distance;
                    next_track_index = i;
                }
            }
        }
        total_distance += shortest_distance;
        current_track = track_sequence[next_track_index];
        printf("%d ", current_track);
        track_sequence[next_track_index] = -1; // Mark track as traversed
        remaining_tracks--;
    }
    printf("\nTotal distance traveled: %d\n", total_distance);
}

int compare_tracks(const void *a, const void *b) {
    return (*(int *)a - *(int *)b); // Compare two integers for qsort
}

/*********************************************************/

void scan() {
    int start_track, direction;
    printf("Enter the starting track: ");
    scanf("%d", &start_track);

    if (start_track < 0 || start_track >= MAX_TRACKS) {
        printf("Invalid starting track. Please enter a value between 0 and %d.\n", MAX_TRACKS - 1);
        return;
    }

    printf("Enter the sequence of tracks to seek: ");
    get_tracks();

    printf("Enter initial direction (0=decreasing, 1=increasing): ");
    scanf("%d", &direction);

    qsort(track_sequence, track_count, sizeof(int), compare_tracks);

    int total_distance = 0;
    int current_track = start_track;

    printf("Traversed sequence from track %d: ", start_track);

    if (direction == 1) { // Increasing direction
        // Traverse towards the end
        for (int i = 0; i < track_count; i++) {
            if (track_sequence[i] >= start_track) {
                total_distance += abs(track_sequence[i] - current_track);
                printf("%d ", track_sequence[i]);
                current_track = track_sequence[i];
            }
        }
        // Then reverse direction and traverse the remaining tracks
        for (int i = track_count - 1; i >= 0; i--) {
            if (track_sequence[i] < start_track) {
                total_distance += abs(track_sequence[i] - current_track);
                printf("%d ", track_sequence[i]);
                current_track = track_sequence[i];
            }
        }
    } else { // Decreasing direction
      
        for (int i = track_count - 1; i >= 0; i--) {
            
            if (track_sequence[i] <= start_track) {
                total_distance += abs(track_sequence[i] - current_track);
                printf("%d ", track_sequence[i]);
                current_track = track_sequence[i];
            }
        }
        
        // Then rverse direction
        
        for (int i = 0; i < track_count; i++) {
            if (track_sequence[i] > start_track) {
                total_distance += abs(track_sequence[i] - current_track);
                printf("%d ", track_sequence[i]);
                current_track = track_sequence[i];
            }
        }
    }

    printf("\nTotal distance traveled: %d\n", total_distance);
}

/*********************************************************/

void cscan() {
    int start_track;
    printf("Enter the starting track: ");
    scanf("%d", &start_track);

    if (start_track < 0 || start_track >= MAX_TRACKS) {
        printf("Invalid starting track. Please enter a value between 0 and %d.\n", MAX_TRACKS - 1);
        return;
    }

    printf("Enter the sequence of tracks to seek: ");
    get_tracks();

    qsort(track_sequence, track_count, sizeof(int), compare_tracks);

    int total_distance = 0;
    int current_track = start_track;
    int i;

    printf("Traversed sequence from track %d: ", start_track);

    // Move towards the end inc
    
    for (i = 0; i < track_count; i++) {
        if (track_sequence[i] >= start_track) {
            total_distance += abs(track_sequence[i] - current_track);
            printf("%d ", track_sequence[i]);
            current_track = track_sequence[i];
        }
    }

    // Jump to the start 
    
    if (i < track_count) {
        total_distance += abs(MAX_TRACKS - 1 - current_track);
        total_distance += abs(MAX_TRACKS - 1 - 0);
        current_track = 0;
    }

    // Continue from the start of the list
    
    for (i = 0; i < track_count; i++) {
        
        if (track_sequence[i] < start_track) {
            
            total_distance += abs(track_sequence[i] - current_track);
            printf("%d ", track_sequence[i]);
            current_track = track_sequence[i];
            
        }
    }

    printf("\nTotal distance traveled: %d\n", total_distance);
}

/*********************************************************/

void quit() {
    printf("Exiting program...\n");
    exit(0);
}

/***************************MAIN******************************/

int main() {
    
    int choice;
    
    while (1) {
        
        printf("\nDisk Scheduling\n---------------\n");
        printf("1) Enter parameters\n");
        printf("2) Calculate distance to traverse tracks using FIFO\n");
        printf("3) Calculate distance to traverse tracks using SSTF\n");
        printf("4) Calculate distance to traverse tracks using Scan\n");
        printf("5) Calculate distance to traverse tracks using C-Scan\n");
        printf("6) Quit program and free memory\n");
        printf("Enter selection: ");
        scanf("%d", &choice);

        switch (choice) {
            
            case 1:
                enter_sequence_size();
                break;
            
            case 2:
                fifo();
                break;
            
            case 3:
                sstf();
                break;
            
            case 4:
                scan();
                break;
            
            case 5:
                cscan();
                break;
            
            case 6:
                quit();
                break;
            
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

/***************************MAIN******************************/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int find_index(int arr[], int head) {
    int i, pos = 0;
    for (i = 0; i < SIZE; i++) {
        if (arr[i] <= head && arr[i + 1] >= head) {
            pos = i;
        }
    }
    return pos;
}

void FCFS(int temp[], int head) {
    int seek_count = 0;
    int distance, cur_track;

    printf("FCFS Disk Scheduling Algorithm\n");
    printf("Sequence of disk access: %d", head);

    for (int i = 0; i < SIZE; i++) {
        cur_track = temp[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
        printf(" -> %d", cur_track);
    }
    printf("\nTotal number of seek operations = %d\n", seek_count);
}

void SSTF(int temp[], int head) {
    int seek_count = 0;
    int distance, cur_track;
    int completed[SIZE] = {0};
    int total_tracks = SIZE;
    int closest_index;

    printf("SSTF Disk Scheduling Algorithm\n");
    printf("Sequence of disk access: %d", head);

    for (int i = 0; i < total_tracks; i++) {
        int min_distance = 1000;

        for (int j = 0; j < total_tracks; j++) {
            if (!completed[j]) {
                distance = abs(temp[j] - head);
                if (distance < min_distance) {
                    min_distance = distance;
                    closest_index = j;
                }
            }
        }

        cur_track = temp[closest_index];
        completed[closest_index] = 1;
        seek_count += min_distance;
        head = cur_track;
        printf(" -> %d", cur_track);
    }
    printf("\nTotal number of seek operations = %d\n", seek_count);
}

void Scan(int temp[], int head, int rotation) {
    int seek_count = 0;
    int distance, cur_track;
    int size = SIZE;
    int arr[size];
    int index;

    for (int i = 0; i < SIZE; i++) {
        arr[i] = temp[i];
    }
    sort(arr, size);
    index = find_index(arr, head);

    printf("Scan Disk Scheduling Algorithm\n");
    printf("Sequence of disk access: %d", head);

    if (rotation == 1) { // moving left
        // Move left to the start of the disk
        for (int i = index; i >= 0; i--) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            printf("head=%d --> %d seek_count=%d\n", head, cur_track, distance);
            head = cur_track;
        }
        // Move right to the greatest element in the disk
        for (int i = index + 1; i < size; i++) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            printf("head=%d --> %d seek_count=%d\n", head, cur_track, distance);
            head = cur_track;
        }
    } else { // moving right
        // Move right to the greatest element in the disk
        for (int i = index + 1; i < size; i++) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            printf("head=%d --> %d seek_count=%d\n", head, cur_track, distance);
            head = cur_track;
        }
        // Move left to the start of the disk
        for (int i = index; i >= 0; i--) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            printf("head=%d --> %d seek_count=%d\n", head, cur_track, distance);
            head = cur_track;
        }
    }
    printf("Total number of seek operations = %d\n", seek_count);
}



void Cscan(int temp[], int head, int rotation) {
    int seek_count = 0;
    int distance, cur_track;
    int size = SIZE + 2;
    int arr[size];
    int index;

    for (int i = 0; i < SIZE; i++) {
        arr[i] = temp[i];
    }
    arr[SIZE] = 0; // adding the start of the disk
    arr[SIZE + 1] = 199; // adding the end of the disk
    sort(arr, size);
    index = find_index(arr, head);

    printf("C-Scan Disk Scheduling Algorithm\n");

    if (rotation == 1) { // moving left
        for (int i = index; i >= 0; i--) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            printf("head=%d --> %d seek_count=%d\n", head, cur_track, distance);
            head = cur_track;
        }
        head = 199;
        distance = abs(head - arr[0]);
        seek_count += distance;
        printf("head=%d --> %d seek_count=%d\n", arr[0], head, distance);
        head = 0;
        seek_count += 199;
        printf("head=%d --> %d seek_count=%d\n", 199, head, 199);
        for (int i = size - 1; i > index; i--) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            printf("head=%d --> %d seek_count=%d\n", head, cur_track, distance);
            head = cur_track;
        }
    } else { // moving right
        for (int i = index + 1; i < size; i++) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            printf("head=%d --> %d seek_count=%d\n", head, cur_track, distance);
            head = cur_track;
        }
        head = 0;
        distance = abs(head - arr[size - 1]);
        seek_count += distance;
        printf("head=%d --> %d seek_count=%d\n", arr[size - 1], head, distance);
        for (int i = 0; i < index; i++) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            printf("head=%d --> %d seek_count=%d\n", head, cur_track, distance);
            head = cur_track;
        }
    }
    printf("Total number of seek operations = %d\n", seek_count);
}

void Look(int temp[], int head, int rotation) {
    int seek_count = 0;
    int distance, cur_track;
    int size = SIZE;
    int arr[size];
    int index;

    for (int i = 0; i < SIZE; i++) {
        arr[i] = temp[i];
    }
    sort(arr, size);
    index = find_index(arr, head);

    printf("Look Disk Scheduling Algorithm\n");
    printf("Sequence of disk access: %d", head);

    if (rotation == 1) {
        for (int i = index; i >= 0; i--) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf(" -> %d", cur_track);
        }
        for (int i = index + 1; i < size; i++) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf(" -> %d", cur_track);
        }
    } else {
        for (int i = index + 1; i < size; i++) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf(" -> %d", cur_track);
        }
        for (int i = index; i >= 0; i--) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf(" -> %d", cur_track);
        }
    }
    printf("\nTotal number of seek operations = %d\n", seek_count);
}

void Clook(int temp[], int head, int rotation) {
    int seek_count = 0;
    int distance, cur_track;
    int size = SIZE;
    int arr[size];
    int index;

    for (int i = 0; i < SIZE; i++) {
        arr[i] = temp[i];
    }
    sort(arr, size);
    index = find_index(arr, head);

    printf("C-Look Disk Scheduling Algorithm\n");
    printf("Sequence of disk access: %d", head);

    if (rotation == 1) {
        for (int i = index; i >= 0; i--) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf(" -> %d", cur_track);
        }
        for (int i = size - 1; i > index; i--) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf(" -> %d", cur_track);
        }
    } else {
        for (int i = index + 1; i < size; i++) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf(" -> %d", cur_track);
        }
        for (int i = 0; i < index; i++) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf(" -> %d", cur_track);
        }
    }
    printf("\nTotal number of seek operations = %d\n", seek_count);
}

int main() {
    //int arr[SIZE] = {176, 79, 34, 60, 92, 11, 41, 114};
     int arr[SIZE] = {98, 183, 37, 122, 14, 124, 65, 67};
    //int head = 50;
    int head = 53;
    int direction;
    int choice;
    int i = 1;
   
    printf("----Disk Management Algorithms----\n");
    while (i != 0) {
        printf("\n\nSelect The Disk Management Algorithms You Want To Use: \n\n");
        printf("First Come First Serve--1 \n");
        printf("Shortest Seek Time First--2 \n");
        printf("Scan(Elevator)--3 \n");
        printf("C-Scan(Circular Scan)--4 \n");
        printf("Look--5 \n");
        printf("C-Look(Circular Look)--6 \n");
        printf("Exit--0\n");

        printf("Choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1: FCFS(arr, head); break;
            case 2: SSTF(arr, head); break;
            case 3: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Scan(arr, head, direction);
                    break;
            case 4: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Cscan(arr, head, direction); break;
            case 5: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Look(arr, head, direction); break;
            case 6: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Clook(arr, head, direction); break;
            case 0: i = 0; break;
            default: printf("\n Error--\n");
        }
    }
    return 0;
}
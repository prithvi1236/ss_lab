#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define DISK_SIZE 200

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                arr[j] ^= arr[j + 1] ^= arr[j] ^= arr[j + 1];
}

int calculateFCFS(int requests[], int n, int head) {
    int seek = 0, current = head;
    for (int i = 0; i < n; i++) {
        seek += abs(requests[i] - current);
        current = requests[i];
    }
    return seek;
}

int calculateSCAN(int requests[], int n, int head, char direction) {
    int total_seek = 0;
    int left[MAX], right[MAX], l = 0, r = 0;
    
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l);
    sort(right, r);

    total_seek+=calculateFCFS(right, r, head);
    
    total_seek += (DISK_SIZE - 1 - right[r - 1]); // move to end
    head = DISK_SIZE - 1;

    total_seek += calculateFCFS(left, l, head);
    return total_seek;
}

int calculateCSCAN(int requests[], int n, int head) {
    int total_seek = 0;
    int left[MAX], right[MAX], l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l);
    sort(right, r);

    total_seek += calculateFCFS(right, r, head);

    total_seek += (DISK_SIZE - 1 - right[r - 1]);  // move to end
    total_seek += (DISK_SIZE - 1);         // jump from end to start
    head = 0;

    total_seek += calculateFCFS(left, l, head);

    return total_seek;
}

int main() {
    int n, requests[MAX], head;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests (track numbers):\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    int fcfs = calculateFCFS(requests, n, head);
    int scan = calculateSCAN(requests, n, head, 'r'); // 'r' for right
    int cscan = calculateCSCAN(requests, n, head);

    printf("\nTotal seek time using FCFS: %d\n", fcfs);
    printf("Total seek time using SCAN (right): %d\n", scan);
    printf("Total seek time using C-SCAN: %d\n", cscan);

    return 0;
}

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
    int seek = 0;
    int left[MAX], right[MAX], l = 0, r = 0;
    
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l);
    sort(right, r);

    if (direction == 'l') {
        for (int i = l - 1; i >= 0; i--) {
            seek += abs(head - left[i]);
            head = left[i];
        }
        seek += head;  // move to 0
        head = 0;
        for (int i = 0; i < r; i++) {
            seek += abs(right[i] - head);
            head = right[i];
        }
    } else {
        for (int i = 0; i < r; i++) {
            seek += abs(right[i] - head);
            head = right[i];
        }
        seek += (DISK_SIZE - 1 - head); // move to end
        head = DISK_SIZE - 1;
        for (int i = l - 1; i >= 0; i--) {
            seek += abs(head - left[i]);
            head = left[i];
        }
    }
    return seek;
}

int calculateCSCAN(int requests[], int n, int head) {
    int seek = 0;
    int left[MAX], right[MAX], l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l);
    sort(right, r);

    for (int i = 0; i < r; i++) {
        seek += abs(head - right[i]);
        head = right[i];
    }

    seek += (DISK_SIZE - 1 - head);  // move to end
    seek += (DISK_SIZE - 1);         // jump from end to start
    head = 0;

    for (int i = 0; i < l; i++) {
        seek += abs(head - left[i]);
        head = left[i];
    }

    return seek;
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

#include <stdio.h>

#define MAX 10

void inputResources(int m, int maxr[], int avail[]) {
    printf("\nEnter the total instances of each resource:\n");
    for (int i = 0; i < m; i++) {
        printf("  Resource R%d: ", i);
        scanf("%d", &maxr[i]);
        avail[i] = maxr[i];
    }
}

void inputMatrix(int n, int m, int matrix[MAX][MAX], const char *name) {
    printf("\nEnter the %s matrix:\n", name);
    for (int i = 0; i < n; i++) {
        printf("  For Process P%d:\n", i);
        for (int j = 0; j < m; j++) {
            printf("    Resource R%d: ", j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(const char *title, int n, int m, int matrix[MAX][MAX]) {
    printf("\n%s:\n", title);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void calculateNeedAndAvailable(int n, int m, int max[MAX][MAX], int alloc[MAX][MAX],
                              int need[MAX][MAX], int avail[MAX]) {
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            avail[j] -= alloc[i][j];
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }
}

int isSafe(int n, int m, int need[MAX][MAX], int alloc[MAX][MAX], int avail[MAX], int safeseq[MAX]) {
    int finish[MAX] = {0}, pos = 0;

    while (pos < n) { // Continue until all processes are allocated
        int found = 0;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int canAllocate = 1;
                for (int j = 0; j < m; j++) {
                    if (need[p][j] > avail[j]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[p][j];
                    safeseq[pos++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("No process can be allocated in this pass. System is unsafe.\n");
            return 0; // Not safe
        }
    }
    return 1; // Safe
}

int main() {
    int n, m;
    int maxr[MAX], avail[MAX], max[MAX][MAX], alloc[MAX][MAX], need[MAX][MAX], safeseq[MAX];

    printf("=== Banker's Algorithm ===\n");

    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    inputResources(m, maxr, avail);
    inputMatrix(n, m, max, "maximum requirement");
    inputMatrix(n, m, alloc, "allocation");

    displayMatrix("Maximum Matrix", n, m, max);
    displayMatrix("Allocation Matrix", n, m, alloc);

    calculateNeedAndAvailable(n, m, max, alloc, need, avail);

    printf("\nAvailable Resources:\n");
    for (int j = 0; j < m; j++) {
        printf("R%d: %d\t", j, avail[j]);
    }
    printf("\n");

    if (isSafe(n, m, need, alloc, avail, safeseq)) {
        printf("\n✅ System is in a safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeseq[i]);
        printf("\n");
    } else {
        printf("\n❌ Deadlock occurred. System is in an unsafe state.\n");
    }

    return 0;
}
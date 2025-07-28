#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100

// Structure to represent a file
struct File {
    char filename[20];
    int start_block;
    int num_blocks;
};

// Function to allocate contiguous blocks for a file
int allocateContiguous(struct File* file, char* fname, int startBlock, int numBlocks) {
    if (startBlock < 0 || startBlock + numBlocks > MAX_BLOCKS) {
        printf("Error: Allocation exceeds disk bounds. Try again.\n");
        return 0;  // Failed
    }

    strcpy(file->filename, fname);
    file->start_block = startBlock;
    file->num_blocks = numBlocks;

    return 1;  // Success
}

int main() {
    struct File files[50];  // To store info for up to 50 files
    int fileCount = 0;
    char choice;

    printf("Contiguous File Allocation Simulator\n");

    do {
        char fname[20];
        int start, blocks;

        printf("\nEnter file name         : ");
        scanf("%s", fname);
        printf("Enter start block       : ");
        scanf("%d", &start);
        printf("Enter number of blocks  : ");
        scanf("%d", &blocks);

        if (allocateContiguous(&files[fileCount], fname, start, blocks)) {
            printf("File allocated successfully!\n");
            printf("File Name       : %s\n", files[fileCount].filename);
            printf("Start Block     : %d\n", files[fileCount].start_block);
            printf("Number of Blocks: %d\n", files[fileCount].num_blocks);
            fileCount++;
        }

        printf("\nDo you want to add another file? (y/n): ");
        scanf(" %c", &choice);  // Space before %c clears the newline in input buffer

    } while (choice == 'y' || choice == 'Y');

    printf("\nSummary of Files Allocated:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("\nFile %d:\n", i + 1);
        printf("  Name   : %s\n", files[i].filename);
        printf("  Start  : %d\n", files[i].start_block);
        printf("  Blocks : %d\n", files[i].num_blocks);
    }

    printf("\nProgram exited successfully.\n");
    return 0;
}
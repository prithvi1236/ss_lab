#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 50

// Structure for a block in linked allocation
struct Block {
    int block_num;
    struct Block* next;
};

// Structure for a file
struct File {
    char filename[20];
    struct Block* start;  // Pointer to first block
    struct Block* end;    // Pointer to last block
};

// Function to create a new block
struct Block* createBlock(int block_num) {
    struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
    newBlock->block_num = block_num;
    newBlock->next = NULL;
    return newBlock;
}

// Function to allocate blocks to a file
void allocateBlocks(struct File* file, const char* name, int blocks[], int count) {
    strcpy(file->filename, name);
    file->start = NULL;
    file->end = NULL;

    for (int i = 0; i < count; i++) {
        struct Block* newBlock = createBlock(blocks[i]);

        if (file->start == NULL) {
            file->start = newBlock;
            file->end = newBlock;
        } else {
            file->end->next = newBlock;
            file->end = newBlock;
        }
    }
}

// Function to display file block allocation
void displayFile(struct File file) {
    printf("\nFile Name: %s\n", file.filename);
    printf("Blocks: ");
    struct Block* current = file.start;
    while (current != NULL) {
        printf("%d", current->block_num);
        if (current->next != NULL)
            printf(" -> ");
        current = current->next;
    }
    printf("\nStart Block: %d", file.start->block_num);
    printf("\nEnd Block  : %d\n", file.end->block_num);
}

int main() {
    struct File files[MAX_FILES];
    int fileCount = 0;
    char choice;

    printf("📂 Linked List Allocation Simulation\n");

    do {
        char name[20];
        int count;
        int blockNums[100];

        printf("\nEnter file name           : ");
        scanf("%s", name);
        printf("Enter number of blocks    : ");
        scanf("%d", &count);
        printf("Enter block numbers       : ");
        for (int i = 0; i < count; i++) {
            scanf("%d", &blockNums[i]);
        }

        allocateBlocks(&files[fileCount], name, blockNums, count);
        fileCount++;

        printf("File '%s' allocated successfully!\n", name);

        printf("\nDo you want to allocate another file? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    // Display all file allocations
    printf("\nSummary of File Allocations:\n");
    for (int i = 0; i < fileCount; i++) {
        displayFile(files[i]);
    }

    return 0;
}
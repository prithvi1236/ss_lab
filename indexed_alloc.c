#include <stdio.h>
    #include <stdlib.h>

    #define MAX_BLOCKS 100
    #define MAX_FILES 10

    // Structure to represent a file's index block
    typedef struct {
        int file_id;
        int block_count;
        int index_block[MAX_BLOCKS]; // Array to store block addresses
    } FileIndex;

    // Function to initialize a file's index block
    void initializeFile(FileIndex *file, int file_id, int block_count) {
        file->file_id = file_id;
        file->block_count = block_count;
        
        // Simulating disk block addresses (random for demonstration)
        for (int i = 0; i < block_count; i++) {
            file->index_block[i] = rand() % 1000 + 1; // Random block address between 1 and 1000
        }
    }

    // Function to display file allocation details
    void displayAllocation(FileIndex file) {
        printf("\nFile ID: %d\n", file.file_id);
        printf("Number of blocks: %d\n", file.block_count);
        printf("Index Block Contents (Block Addresses):\n");
        for (int i = 0; i < file.block_count; i++) {
            printf("Block %d: Disk Address %d\n", i + 1, file.index_block[i]);
        }
    }

    int main() {
        FileIndex files[MAX_FILES];
        int file_count;

        // Input number of files
        printf("Enter the number of files (max %d): ", MAX_FILES);
        scanf("%d", &file_count);
        if (file_count > MAX_FILES || file_count <= 0) {
            printf("Invalid number of files!\n");
            return 1;
        }

        // Input details for each file
        for (int i = 0; i < file_count; i++) {
            int blocks;
            printf("Enter number of blocks for file %d (max %d): ", i + 1, MAX_BLOCKS);
            scanf("%d", &blocks);
            if (blocks > MAX_BLOCKS || blocks <= 0) {
                printf("Invalid number of blocks!\n");
                return 1;
            }
            initializeFile(&files[i], i + 1, blocks);
        }

        // Display allocation for all files
        printf("\nIndexed Allocation Details:\n");
        printf("==========================\n");
        for (int i = 0; i < file_count; i++) {
            displayAllocation(files[i]);
        }

        return 0;
    }
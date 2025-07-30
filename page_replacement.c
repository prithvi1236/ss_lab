#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 3
#define MAX_PAGES 100

// FIFO Algorithm
int fifo(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], page_faults = 0, index = 0;
    
    printf("\nFIFO Page Replacement:\n");
    for(int i = 0; i < frames; i++) frame[i] = -1;
    
    for(int i = 0; i < n; i++) {
        bool found = false;
        for(int j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                found = true;
                printf("page %d already there\n", pages[i]);
                break;
            }
        }
        
        if(!found) {
            frame[index] = pages[i];
            printf("page %d loaded in frame %d\n", pages[i], index);
            index = (index + 1) % frames;
            page_faults++;
        }
        
        for(int j = 0; j < frames; j++) {
            if(frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }
    return page_faults;
}

// LRU Algorithm
int lru(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], time[MAX_FRAMES], page_faults = 0, counter = 0;
    
    printf("\nLRU Page Replacement:\n");
    for(int i = 0; i < frames; i++) frame[i] = -1;
    
    for(int i = 0; i < n; i++) {
        bool found = false;
        for(int j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                found = true;
                printf("page %d already there\n", pages[i]);
                time[j] = counter++;
                break;
            }
        }
        
        if(!found) {
            int lru_index = frames - 1;
            for(int j = frames - 1; j >= 0; j--) {
                if(frame[j] == -1) {
                    lru_index = j;
                    break;
                }
            }
            if(frame[lru_index] != -1) {
                int min_time = time[lru_index];
                for(int j = 0; j < frames; j++) {
                    if(time[j] < min_time) {
                        min_time = time[j];
                        lru_index = j;
                    }
                }
            }
            
            frame[lru_index] = pages[i];
            time[lru_index] = counter++;
            printf("page %d loaded in frame %d\n", pages[i], lru_index);
            page_faults++;
        }
        
        for(int j = 0; j < frames; j++) {
            if(frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }
    return page_faults;
}

// LFU Algorithm
int lfu(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], freq[MAX_FRAMES], page_faults = 0;
    int page_freq[MAX_PAGES] = {0};
    
    printf("\nLFU Page Replacement:\n");
    for(int i = 0; i < frames; i++) frame[i] = -1;
    
    for(int i = 0; i < n; i++) {
        page_freq[pages[i]]++;
        bool found = false;
        for(int j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                found = true;
                printf("page %d already there\n", pages[i]);
                freq[j]++;
                break;
            }
        }
        
        if(!found) {
            int lfu_index = frames - 1;
            for(int j = frames - 1; j >= 0; j--) {
                if(frame[j] == -1) {
                    lfu_index = j;
                    break;
                }
            }
            if(frame[lfu_index] != -1) {
                int min_freq = freq[lfu_index];
                for(int j = 0; j < frames; j++) {
                    if(freq[j] < min_freq) {
                        min_freq = freq[j];
                        lfu_index = j;
                    }
                }
            }
            
            frame[lfu_index] = pages[i];
            freq[lfu_index] = page_freq[pages[i]];
            printf("page %d loaded in frame %d\n", pages[i], lfu_index);
            page_faults++;
        }
        
        for(int j = 0; j < frames; j++) {
            if(frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }
    return page_faults;
}

int main() {
    int n;
    int pages[MAX_PAGES];
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the page reference sequence: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    printf("Contiguous Page Replacement Simulator\n");
    
    int faults;
    faults = fifo(pages, n, MAX_FRAMES);
    printf("Total Page Faults: %d\n", faults);
    
    faults = lru(pages, n, MAX_FRAMES);
    printf("Total Page Faults: %d\n", faults);
    
    faults = lfu(pages, n, MAX_FRAMES);
    printf("Total Page Faults: %d\n", faults);
    
    printf("Program exited successfully.\n");
    return 0;
}
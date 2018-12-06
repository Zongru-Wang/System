#include <stdio.h> // Any other headers we need here
#include <string.h> // We bring in the old malloc function
#include <unistd.h>


// The data structure block.
struct block {
    size_t size; // How many bytes beyond this block have been allocated in the heap
    struct block *next; // Where is the next block
    int free; // Is this memory free?

};


#define BLOCK_SIZE sizeof(struct block)


// the global variable, the head of block of data.
struct block *head = NULL;


// The method to find the best fit of memory from a list of block data.
struct block *bestFit(size_t s) {

    // Set the current different to 0.
    size_t currentDiff = 0;
    // Set the minimal different to a large enough number.
    size_t MinimalDiff = 99999999999;
    // Set the current best fit and freed block to NULL.
    struct block *currentBestfit = NULL;
    // If there is no malloc now, there is no best fit. This function will return NULL.
    if (head == NULL) {
        return NULL;
    }
    // Copy the data from head to use in the while loop.
    struct block *current = head;
    // Check from the whole list of malloc, and find the best fit(minimal difference)
    while (current != NULL) {
        // Need the size of block bigger than the requesting memory.
        if (currentDiff < MinimalDiff && head->free == 1 && head->size >= s) {
            currentDiff = head->size - s;
            MinimalDiff = currentDiff;
            currentBestfit = head;
            currentBestfit->free = 0;
        }
        current = current->next;
    }
    return currentBestfit;
}


// My malloc helper function that doesn't print things
// So, we can use it in mycalloc function that print nothing.
void *mymallocHelper(size_t s) {
    struct block *currrentHead = NULL;
    if (s == 0) {
        printf("Can't malloc with size 0!");
        return NULL;
    }
    // Use the helper, will return NULL if can't find best fit.
    currrentHead = bestFit(s);
    //If can't find the best fit, create a new memory.
    if (currrentHead == NULL) {
        // Find the current skbr(0)
        void *ptr = sbrk(0);
        void *request = sbrk(s + BLOCK_SIZE);
        // If the asking memory larger than the computer memory, Return NULL.
        if (request == (void *) -1) {
            return NULL;
        }
        currrentHead = request;
        currrentHead->next = NULL;
        currrentHead->free = 0;
        currrentHead->size = s;
        // If there is not malloc, then the head is current head.
        if (head == NULL) {
            head = currrentHead;
        } else {
            struct block *current = head;
            // else, add the new created block to the end of the block.
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = currrentHead;
        }
    }


    return currrentHead + 1;
}


// My malloc function.
void *mymalloc(size_t s) {
    struct block *currrentHead = NULL;
    // Make a helper function so when we use myMalloc in mycalloc will not print
    // things twice.
    currrentHead = mymallocHelper(s);
    if (currrentHead != NULL) {
        printf("malloc %zu bytes\n", s);

    } else {

        printf("malloc 0 bytes\n");
    }

    return currrentHead;
}

// The calloc function
void *mycalloc(size_t nmemb, size_t s) {
    // the asking size is s * nmemb
    size_t size = s * nmemb;
    // call maloc.
    struct block *result = mymallocHelper(size);
    // If we have enough memory to malloc
    if (result != NULL) {
        // Set every block's size to 0, use memset
        memset(result, 0, size);
    }
    printf("calloc %zu bytes\n", size);
    return result;
}


// My free function
void myfree(void *ptr) {
    if (ptr != NULL) {
        struct block *block1 = NULL;

        // Access the block data by using ptr - 1
        block1 = (struct block *) ptr - 1;

        // Use for test if myfree can free every block correctly.
        size_t s = block1->size;

        // Set the flag of free to 1 to show it us freed.
        block1->free = 1;

        //printf("Freed some memory\n");
        // Use for test if myfree can free every block correctly.

        printf("Freed %zu bytes\n", s);

    }
}
	


#define _GNU_SOURCE
#include <stdio.h> // Any other headers we need here
#include <string.h> // We bring in the old malloc function
#include <unistd.h>
#include <sys/mman.h>
#include <sched.h>
#include <pthread.h>
#include <utmpx.h>
#include <sys/sysinfo.h>

// The data structure block.
struct block {
	size_t size; // How many bytes beyond this block have been allocated in the heap
	struct block *next; // Where is the next block
	int free; // Is this memory free?

};


#define BLOCK_SIZE sizeof(struct block)
#define PAGE_SIZE sysconf(_SC_PAGE_SIZE)
#define NUM_CPU get_nprocs_conf()


// To judge if we initilized all threads. Used in mymalloc
int ifInitlizled = 0;
// the global variable, the list of head of block of data.
struct block **base;
// The list of threads.
pthread_mutex_t *locks;
// global lock for s brk()
pthread_mutex_t lock;


// Add a block to the end of the head as tail.
void addtail(struct block* block1) {
	int cpu = sched_getcpu();

	// If there is not malloc, then the head is current head.
	if (base[cpu] == NULL) {
		base[cpu] = block1;
	} else {
		struct block *current = base[cpu];
		// else, add the new created block to the end of the block.
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = block1;
	}
}

// The method to find the best fit of memory from a list of block data.
// And if we found a best fit but still get usable space for the result,
// we will split the block to reuse the empty space left.
struct block *bestFit(size_t s) {

	int cpu = sched_getcpu();
	// Set the current different to 0.
	size_t currentDiff = 0;
	// Set the minimal different to a large enough number.
	size_t MinimalDiff = 99999999999;
	// Set the current best fit and freed block to NULL.
	struct block *currentBestfit = NULL;
	// If there is no malloc now, there is no best fit. This function will return NULL.
	if (base[cpu] == NULL) {
		return NULL;
	}
	// Copy the data from head to use in the while loop.
	struct block *current = base[cpu];
	// Check from the whole list of malloc, and find the best fit(minimal difference)
	while (current != NULL) {
		// Need the size of block bigger than the requesting memory.
		if (currentDiff < MinimalDiff && base[cpu]->free == 1 && base[cpu]->size >= s) {
			currentDiff = current->size - s;
			MinimalDiff = currentDiff;
			currentBestfit = current;
			currentBestfit->free = 0;
			currentBestfit->size = s;
		}
		current = current->next;
	}
	if (current != NULL && MinimalDiff > BLOCK_SIZE) {
		struct block *newBlock = current + s + BLOCK_SIZE;
		newBlock->free = 1;
		newBlock->size = MinimalDiff - BLOCK_SIZE;
		newBlock->next = current->next;
		addtail(newBlock);

	}
	return currentBestfit;
}

// split block if there is still space to use
void split_block(size_t s, struct block *newblock) {
	size_t requestedSize;

	if ((BLOCK_SIZE + s) % PAGE_SIZE > 0) {
		requestedSize = ((BLOCK_SIZE + s) / PAGE_SIZE) * PAGE_SIZE+ PAGE_SIZE;
	} else {
		requestedSize = (BLOCK_SIZE + s);
	}
	newblock->size = requestedSize - BLOCK_SIZE - s - BLOCK_SIZE;
	newblock->free = 1;
	newblock->next = NULL;

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
		if (s >= PAGE_SIZE) {
			void *request = mmap(NULL,BLOCK_SIZE + s, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
			currrentHead = request;
			currrentHead->next = NULL;
			currrentHead->free = 0;
			currrentHead->size = s;

			struct block *newblock = (void*)request + BLOCK_SIZE + s;
			size_t requestedSize;
			split_block(s, newblock);
			currrentHead->next = newblock;

			addtail(currrentHead);

		} else {
		    pthread_mutex_lock(&lock);
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
			addtail(currrentHead);

            pthread_mutex_unlock(&lock);
		}
	}

	return currrentHead + 1;
}


// My malloc function.
void *mymalloc(size_t s) {

    if (!ifInitlizled) {
        base = sbrk(NUM_CPU * sizeof(struct block*));
        locks = sbrk(sizeof(pthread_mutex_t) * NUM_CPU);
        int v;
        for (v=0; v < NUM_CPU; v++) {
            pthread_mutex_init(&locks[v], NULL);
            base[v] = NULL;
        }
        pthread_mutex_init(&lock, NULL);

        ifInitlizled = 1;
    }

	struct block *currrentHead = NULL;

	int cpu = sched_getcpu();
	pthread_mutex_lock(&locks[cpu]);
	// Make a helper function so when we use myMalloc in mycalloc will not print
	// things twice.
	currrentHead = mymallocHelper(s);


	if (currrentHead != NULL) {
		printf("malloc %zu bytes\n", s);

	} else {

		printf("malloc 0 bytes\n");
	}

    pthread_mutex_unlock(&locks[cpu]);

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
	int cpu = sched_getcpu();


	if (ptr != NULL) {
		pthread_mutex_lock(&locks[cpu]);


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

		pthread_mutex_unlock(&locks[cpu]);

	} else {
        printf("Nothing to free\n");

	}
}



#include <stdio.h>
#include <malloc.h>
#include <pthread.h>





// Here is some data structure that will be shared.
// It is an array of strings, but nothing has been allocated yet.

//assume that we have 32 CPUs.
int num_of_threads = 32;
char** shared_data;

// Write some words and see if we can play with the shared-data with our malloc and free.
void write_Shared_Data(int index) {

    char content[1] = "n";
    shared_data[index] = malloc(sizeof(char));
    shared_data[index][0] = content[0];
    pthread_exit(0);

}


// Write some words and see if we can play with the shared-data with our malloc and free.
void write_Shared_Data2(int index) {

    char *content = malloc(sizeof(char) * 16);

    shared_data[index] = "Hello";
    free(content);

    pthread_exit(0);

}


// Write some words and see if we can play with the shared-data with our malloc and free.
void write_Shared_Data4(int index) {

    char *content = malloc(sizeof(char) * 16);

    shared_data[index] = "MyGrader";

    free(content);

    pthread_exit(0);

}

// Write some words and see if we can play with the shared-data with our malloc and free.
void write_Shared_Data3(int index) {

    char content[1] = "y";
    shared_data[index] = malloc(sizeof(char));
    shared_data[index][0] = content[0];

    pthread_exit(0);

}




// Using threads to play with malloc and free.
int main(){
    // (1) Malloc for some size of your shared data (i.e. how many strings will you have)
    shared_data = malloc(sizeof(char*) * num_of_threads);
    pthread_t tid[num_of_threads];


    // (2) Launch some number of threads (perhaps with two or more different functions)
    size_t i;
    for (i = 0; i < num_of_threads; i++) {
        pthread_create(&tid[i], NULL, (void*)write_Shared_Data2, (void*)i );
        pthread_create(&tid[i], NULL, (void*)write_Shared_Data4, (void*)i );

        // Functions without free() inside, wasn't sure the specific requirement.
        // You can test them using make file in the starter folder.
        //pthread_create(&tid[i], NULL, (void*)write_Shared_Data, (void*)i );
        //pthread_create(&tid[i], NULL, (void*)write_Shared_Data3, (void*)i );
    }


    // (3) Join some number of threads
    int y;
    for (y=0; y < num_of_threads; y++) {
        pthread_join(tid[y], NULL);


    }

    // (4) Print the results of shared data (i.e. this is done sequentially)


    int x;
    for (x=0; x < num_of_threads; x++) {
        printf("%s\n", shared_data[x]);

    }




    // (5) Cleanup your program
    free(shared_data);
    // 'free shared_data'
    return 0;
}

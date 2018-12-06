// Implement your part 2 solution here
// gcc -lpthread threads.c -o threads

#include <pthread.h>

#include <stdio.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int colors[64][64*3];


#define NTHREADS 64

int counter = 0;



void paint(int workID){
    printf("Artist %d is painting\n",workID);


    int i;
    for( i =0; i < 64*3; i++){
        colors[workID][i] = ((workID*2)+i); // Try doing something more interesting with the colors!
    }
}

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *thread(void * vargp) {

    pthread_mutex_lock(&mutex1);
    counter = counter + 1;
    paint(counter);
    pthread_mutex_unlock(&mutex1);

    return NULL;


}


int main() {

    pthread_t tids[NTHREADS];

    printf("Counter starts at: %d\n", counter);
    int i;

    for (i = 0; i < NTHREADS; i++) {

        pthread_create(&tids[i], NULL, thread, NULL);

    }


    for (i = 0; i < NTHREADS; i++) {

        pthread_join(tids[i], NULL);

    }


    pid_t wpid;
    int status = 0;
    while ((wpid = wait(&status)) > 0);



    FILE *fp;
    fp = fopen("threads.ppm","w+");
    fputs("P3\n",fp);
    fputs("64 64\n",fp);
    fputs("255\n",fp);

    int x;
    for(x =0; x < 64;x++){
        int j;
        for(j =0; j < 64*3; j++){
            fprintf(fp,"%d",colors[x][j]);
            fputs(" ",fp);
        }
        fputs("\n",fp);
    }
    fclose(fp);

    printf("Final Counter value: %d\n", counter);

    return 0;


}
// gcc -std=c99 -fopenmp omp5.c -o omp5
// You fill in


// gcc -std=c11 -fopenmp omp5.c -o omp5
#include <stdio.h>
#include <omp.h>


#define NUM_THREADS 4
#define PAD 8
static long num_steps = 100000;

int main() {



    double startime, endtime;
    double pi = 0.0;
    double sums[NUM_THREADS][PAD];
    double step = 1.0/(double)num_steps;
    int nthreads;
#pragma omp parallel num_threads(NUM_THREADS)
    {
        int id,i, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) { // Parent Thread
            nthreads = nthrds;

            startime = omp_get_wtime();
        }
        sums[id][0] = 0.0;
        for (i = id; i < num_steps; i+=nthrds) {
            x = (i + 0.5) * step;
            sums[id][0] += 4.0/(1.0 + x*x);
        }

        endtime = omp_get_wtime();
    }

    int i;

    for (i = 0; i < nthreads; i++) {
        pi += step * sums[i][0];
    }

    printf("PI = %f\n", pi);



    printf("%d thread takes %f \n", NUM_THREADS, endtime - startime);

    return 0;
}
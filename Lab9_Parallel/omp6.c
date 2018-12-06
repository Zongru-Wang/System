// Implement parallel quicksort here

#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

int partition(int *a, int p, int r){
    int lt[r-p], gt[r-p], i, j, key = a[r];
    int lt_n = 0;
    int gt_n = 0;


#pragma omp parallel for
    for (i = p; i < r; i++) {
        if (a[i]< a[r]) {
            lt[lt_n++] = a[i];
        } else {
            gt[gt_n++] = a[i];
        }
    }

    for (i = 0; i<lt_n; i++){
        a[p+i] = lt[i];
    }

    a[p+lt_n] = key;

    for (j=0; j<gt_n; j++) {
        a [p + lt_n + j + 1] = gt[j];

    }
    return p + lt_n;
}


void quicksort(int *a, int low, int high) {
    if (low < high) {
        int div = partition(a, low, high);

#pragma omp parallel sections
        {
#pragma omp section
            quicksort(a, low, div-1);
#pragma omp section
            quicksort(a, div+1, high);
        }

    }
}

int main() {

    srand(time(NULL));
    int i=0, arr[1000];
    while (i<999) {
        arr[i] = rand()%6000;
        i++;
    }


    quicksort(arr, 0, 999);

    printf("---sorted first 20 number----\n");
    for (i = 0; i<1000; i++) {
        printf("%d\n", arr[i]);

    }


    return 0;
}
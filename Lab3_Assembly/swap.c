// Write a C program that swaps two integers in a function


#include <stdio.h>

void swap(int* x, int* y) {

    int temp = *x;

    *x = *y;

    *y = temp;




}


int main() {

    int x = 12;

    int y = 21;


    swap(&x, &y);
    

    return 0;



}
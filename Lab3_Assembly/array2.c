// Write a C program called array2.c that has an array of 400 integers in the function of main that is dynamically allocated.


#include <stdio.h>
#include <stdlib.h>

int main () {

    int* myarray = (int*)malloc(sizeof(int)*400);

    myarray[0]=72;
    myarray[70]=56;
    myarray[66] = 62;


    free(myarray);

}

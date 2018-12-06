// Add your program here!

#include<stdio.h>
int main () {
int base;
int n;
int result = 1;
int output[n];
int i;
printf("Give the base: ");
scanf("%d", &base);

printf("Give the exponent: ");
scanf("%d", &n);

for (i=1; i<=n; i++){ 
   result = result * base;
output[i-1] = result;}

int loop;

for (loop = 0; loop<n; loop++)
printf("%d  ",output[loop]);

return 0;



}

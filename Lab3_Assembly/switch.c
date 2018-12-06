// Write a C program using a switch statement


#include <stdio.h>

int main()
{
    int x = 2;
    switch (x)
    {
        case 1: printf("Case is 1");
            break;
        case 2: printf("Case is 2");
            break;
        case 3: printf("Case is 3");
            break;
        default: printf("Not these 3 cases");
            break;
    }
    return 0;
}
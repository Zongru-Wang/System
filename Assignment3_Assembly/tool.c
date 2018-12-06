// Implement your cycle count tool here.
//
//
// Useage: gcc tool.c -o tool
// ./tool barebones.s
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]) {

  
    if(argc != 2 ) {
        printf("Please input a single file");
    } else {

        char* fileName = argv[1];

        printf("File Name is: %s\n", fileName );

        FILE* filePointer;
        filePointer = fopen(fileName, "r");

        char buffer[50];

        int add = 0;
        int mov = 0;
        int imulq = 0;
        int sub = 0;
        int div = 0;
        int lea = 0;
        int push = 0;
        int pop = 0;
        int ret = 0;

        int total = 0;


        int cycle = 0;





        while (fscanf(filePointer, "%s", buffer) == 1) {



            char firstThree[3] = "";

            strncpy(firstThree, buffer, 3);



            if ( (strcmp(firstThree, "add") == 0) || (strcmp(firstThree, "ADD") == 0)) {
                add++;

            }

            if ((strcmp(firstThree, "mov") == 0) || (strcmp(firstThree, "MOV") == 0))  {
                mov++;

            }

            if ((strcmp(firstThree, "mul") == 0) || (strcmp(firstThree, "MUL") == 0)) {
                imulq++;

            }

            if ((strcmp(firstThree, "div") == 0) || (strcmp(firstThree, "DIV") == 0)) {
                div++;

            }

            if ((strcmp(firstThree, "sub") == 0) || (strcmp(firstThree, "SUB") == 0)) {
                sub++;

            }

            if ((strcmp(firstThree, "lea") == 0) || (strcmp(firstThree, "LEA") == 0)) {
                lea++;

            }

            if ((strcmp(firstThree, "pus") == 0)  || (strcmp(firstThree, "PUS") == 0)){
                push++;

            }

            if ((strcmp(firstThree, "pop") == 0) || (strcmp(firstThree, "POP") == 0)) {
                pop++;

            }

            if ((strcmp(firstThree, "ret") == 0) || (strcmp(firstThree, "RET") == 0)) {
                ret++;

            }

        }














        total = add + sub + imulq + div + mov + push + pop
                 + ret + lea;

        // Set up the approximation cyle for each operation.
        // I use the avage of every operation.
        float cyadd = add*1;

        float cymov = mov*1;

        float cymul = imulq*1.5;

        float cysub = sub*1;

        float cydiv = div*1.625;

        float cylea = lea*1.25;

        float cypush = push*4;

        float cypop = pop*6.7;

        float cyret = ret*1.5;

        cycle = cyadd + cymov + cymul + cysub + cydiv + cylea + cypush + cypop + cyret;

        if (add != 0) {
            printf("ADD %d\n", add);

        }

        if (sub != 0) {
            printf("SUB %d\n", sub);
        }

        if (imulq != 0) {
            printf("MUL %d\n", imulq);

        }

       if (div != 0) {
           printf("DIV %d\n", div);
       }

       if (mov != 0) {
           printf("MOV %d\n", mov);

       }

       if (lea != 0) {
           printf("LEA %d\n", lea);
       }

       if (push != 0) {
           printf("PUSH %d\n", push);
       }

       if (pop != 0) {
           printf("POP %d\n", pop);
       }

       if (ret != 0) {
           printf("RET %d\n", ret);
       }



       if (total != 0) {
           printf("Total %d\n", total);
       }





        printf("Cycle %d\n", cycle);






    }



}

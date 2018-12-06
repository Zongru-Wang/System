// Implement your part 1 solution here
// gcc vfork.c -o vfork

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int colors[64][64*3];

// Modify your paint function here
void paint(int workID){
printf("Artist %d is painting\n",workID);


    int i;
    for( i =0; i < 64*3; i++){
        colors[workID][i] = ((workID*2)+i); // Try doing something more interesting with the colors!
    }
}

int main(int argc, char** argv){

    int numberOfArtists = 64; // How many child processes do we want?

    pid_t pid;
    // main loop where we fork new threads
    int i;
    for(i =0; i < numberOfArtists; i++){
        // (1) Perform a fork

        pid = vfork();


        // (2) Make only the child do some work (i.e. paint) and then terminate.
        if(pid== 0 ){
            // make child paint
            paint(i);
            exit(0);
        } else {

            printf("The pid is %d", pid);

        }

        //wait(NULL);

    }


    pid_t wpid;
    int status = 0;
    while ((wpid = wait(&status)) > 0);



    FILE *fp;
    fp = fopen("vfork.ppm","w+");
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

    printf("parent is exiting(last artist out!)\n");

    return 0;
}
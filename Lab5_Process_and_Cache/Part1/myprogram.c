// Take a look at some of the previous examples to create your own program!
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>



void runmycommand(char **command) {

    pid_t pid;

    int status;

    pid = fork();

    if (pid == 0) {

        if (execvp(command[0], command) == -1) {
            printf("command not found");

        }

        exit(0);

    } else if (pid < 0) {


        printf("Command not found");

    } else {

        do {


            waitpid(pid, &status, WUNTRACED);

        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

    }



}







int main(){

    char **Commands[3];

    char *argv[2];

    argv[0] = "/bin/ps";
    argv[1] = NULL;


    char *argv2[4];
    argv2[0] = "/bin/echo";
    argv2[1] = "Hello";
    argv2[2] = "World";
    argv2[3] = NULL;




    char *argv3[3];

    argv3[0] = "/bin/mkdir";
    argv3[1] = "testDir";
    argv3[2] = NULL;


    Commands[0] = argv;
    Commands[1] = argv2;
    Commands[2] = argv3;

    int i = 0;


    for (i = 0; i< 3; i++ ) {




        int w = i + 1;

        printf("%d -th Command result:\n", w);

        if (w == 3) {

            printf("Created a dir called textDir");
        }

        runmycommand(Commands[i]);
        printf("\n");

        sleep(1);



    }
    return 0;
}
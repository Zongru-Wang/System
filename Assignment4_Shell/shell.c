#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdint.h>



#define BUFFSIZE 80

// Usage: gcc shell.c -o shell
//        ./shell

void signal_handler(int sig);


int minishellExit(char **args);
int minishellHelp(char **args);
int minishellCd(char **args);
int minishellTime(char **args);



char *getIput();

char **parse(char *line);

int shellExcuter(char **argv);


int externalRunner(char **argv);


int pipeHandler(char *line);
int pipeExecuter(char **left, char **right);







// array of pointers to this shell's built-in commands
// used by shellExcuter to run internal commands
// This function got from the stackoverflow.
// A nice method to use. I used to use switch, but this method is better.
// First time to know this method.
int (*built_in_commands[]) (char**) = {
        &minishellExit,
        &minishellCd,
        &minishellHelp,

        &minishellTime
};

// The number of my own made functions.
int numOfMyCommands = 4;

// The name of built-in functions.
char* built_in_strings[] = {
        "exit",
        "cd",
        "help",

        "time"
};

// The process of exit command.
int minishellExit(char **args) {
    return 0;
}

// the cd command implements for mini shell.
int minishellCd(char **args) {

    //if user type only cd, it will go to the most upper level.
    if (!args[1]) {
        chdir(getenv("HOME"));
    }
    else {

        if (chdir(args[1]) != 0) {
            printf("couldn't load that directory\n");

        }
    }
    return 1;
}

// The self made help function for my mini shell.
int minishellHelp(char** args) {


    printf("My mini shell has the following commands:\n");

    printf("\tcd <arg>: changes directory, or use cd .. to go to the upper directory\n");

    printf("\thelp: calls mini shell help \n");

    printf("\ttime: A message for you\n");

    printf("\texit: exits the Mini shell \n");


    printf("all other bash commands are executable.\n");

    return 1;
}


// My built-in function for MiniShell, use time library to run a guess number game.
// Has a nice story inside and can also shows the system time from the system local time.
int minishellTime(char** args) {
    time_t currentTime = time(NULL);

    int input = 0;


    if (currentTime != -1) {



        printf("\nHi, I don't know if this message reaches correctly\n");
        printf("\nYou have trapped in this world for decades\n");
        printf("\nYour team is waiting fot you, please get out as soon as possible!\n");


        printf("\nThis device shows that current time is: %s\n",
               asctime(gmtime(&currentTime)));

        printf("Is that correct?\n 1 for Yes or 0 for No\n");
        scanf("%d",&input);

        if(input == 1) {
            printf("Ok, I finally get you in the correct time line\n");
            printf("\n\n***********************\n\n");

            printf("Now let us adjust the data to get you, I will give you 10 numbers from 1 - 10\n");

            printf("\n\n***********************\n\n");
            printf("Enter the number, and I will tell you if it is too large or too small, until you get the correct one\n");
            printf("\n\n***********************\n\n");

            int input2 = 0;


            srand(time(NULL));
            // Generate a random number for each game play as an answer.
            int answer = rand() % 10;

            int chance =  8;

            int x = 0;
            while(x < chance) {

                scanf("%d",&input2);

                if( input2 == answer) {
                    printf("\nConnected successfully...\n");
                    printf("\n\n***********************\n\n");
                    return 1;

                }

                else if (input2 < answer) {
                    printf("Error, brain wave too low\n");
                    printf("\n\n***********************\n\n");
                    x++;



                }

                else if (input2 > answer) {

                    printf("Error, brain wave too high, cool down!\n");
                    printf("\n\n***********************\n\n");
                    x++;

                }



            }

            printf("Lost connection... Please use the same way to reconnect.\n");
            printf("\n\n***********************\n\n");


        }


        else if(input == 0) {

            printf("I guess I reached you in a wrong time line\n");
            printf("Please wait for us, we are coming for you right now\n");

        } else {


            printf("Co###on Erro.....\n");

        }



        return 1;

    } else {
        return 0;
    }


}



//The signal handler from the example.
void signal_handler(int sig) {
    write(1,"Terminating through signal handler\n",35);
 
    exit(0);
}


// The welcome shell, will print a welcome page for seconds and disappaer automatically.
void StartingShell()
{
    printf("\033[H\033[J");
    printf("\n\n\n\n******************"
           "************************");
    printf("\n\n\n\t****Zongru's Mini SHELL****");
    printf("\n\n\n\n*******************"
           "***********************");

    printf("\n");
    sleep(1);
    printf("\033[H\033[J");
}




// get the line of user input
char *getIput() {


    char* line = malloc(BUFFSIZE * sizeof(char));

    int c;
    int i = 0;

    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            line[i] = '\0';
            return line;
        } else {
            line[i] = c;
            i++;
        }
    }
}




// Parse the line input.
char **parse(char *line) {
    int buffer = BUFFSIZE;
    char **words = malloc(buffer * sizeof(char*));



    if (!words) {
        printf("Could not allocate parse\n");
        exit(0);
    }

    int i = 0;

    // The first input from user(command).
    char* word = strtok(line, " \n\t\r");

    while (word) {
        words[i] = word;
        i++;

        // get The second input from user(command).
        word = strtok(NULL, " \n\t\r");
    }

    words[i] = NULL;
    return words;
}

// Excute the shell by a command if there is no pipe line.
int shellExcuter(char **argv) {
    if (argv[0] == NULL) {
        return 1;
    }
    int i;
    for (i = 0; i < numOfMyCommands; i++) {
        if (strcmp(argv[0],built_in_strings[i]) == 0) {
            return (*built_in_commands[i])(argv);
        }
    }

    return externalRunner(argv);
}





// Exculate the command with pipeline. the left is the left command from pipeline, the right is the 
// right part from the pipeline.
int pipeExecuter(char **left, char **right) {
    int pipeParts[2];


    if (pipe(pipeParts) == -1) {
        printf("Error when making pipe\n");
        exit(0);
    }

    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == 0) {
        dup2(pipeParts[1],STDOUT_FILENO);
        close(pipeParts[0]);
        close(pipeParts[1]);
        execvp(left[0], left);


        printf("Error in left fork\n");
        exit(0);
    } else if (pid1 < 0) {
        printf("Error forking\n");
        exit(0);

    } else {

        // wait the first pid finished.
        waitpid(pid1,NULL,0);

        // fork pid2.
        pid2 = fork();



        // run the second child
        if (pid2 == 0) {
            dup2(pipeParts[0],STDIN_FILENO);
            close(pipeParts[1]);
            close(pipeParts[0]);
            execvp(right[0], right);


            printf("Error in right fork\n");
            exit(0);
        } else if (pid2 < 0) {
            printf("Error forking\n");
            exit(0);
        }
    }

    // if fork success, then run pid2.
    close(pipeParts[0]);
    close(pipeParts[1]);

    waitpid(pid2,NULL,0);

    return 0;
}





// excute the command with pipe lines
// Auuseme we have at most one pipeline.
// Give the userinput, split it as two parts,
// and pass them to the pipeExcuter.
int pipeHandler(char *line) {
    int i = 0;
    char *components[BUFFSIZE];

    // Split the two parts from the pipe line.
    char *component = strtok(line, "|");


    components[0] = component;

    components[1] = NULL;
    component = strtok(NULL, "|");
    components[1] = component;

    char **left = parse(components[0]);
    char **right = parse(components[1]);

    pipeExecuter(left,right);

    return 0;
}


// Run the command inside the bash commands.
int externalRunner(char** argv) {
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        if (execvp(argv[0],argv) == -1) {
            printf("Command not found--Did you mean something else?\n");
        }
        exit(0);
    } else if (pid < 0) {
        printf("fork failed\n");
        return 0;
    } else {



        wait(NULL);
    }

    return 1;
}




// The main function.
int main(){

    signal(SIGINT, signal_handler);
    StartingShell();

    printf("Type help for command list\n");



    // launches the shell
    sig_atomic_t signal;


    // buffer for the user input
    char* userLineInput;
    char** args;


    // the loop, if we have signal, the Mini-Shell won't stop.
    do {

       
        printf("mini-shell> ");

        userLineInput = getIput();

        // if there is a piple line, pass the input to handler can handle command with pipes.
        if (strstr(userLineInput, "|")) {

            pipeHandler(userLineInput);

        } else {

            args = parse(userLineInput);

            signal = shellExcuter(args);

           
        }


     // Free the malloc
     free(args);
     free(userLineInput);
     

    } while (signal);

    
 

    return 0;


}


#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/wait.h> 
#include <sys/time.h>
#include <string.h>

void main(int argc, char *arguments[]){

    // Check if user provided a command
    if (argc < 2) {
        printf("\nProvide the correct command.\n\n");
        return;
    }

    struct timeval start, end;

    //for execve()
    // // Define the /bin/ directory as the path for the command
    // const char *path = "/bin/";
    // char full_command[256];     
    // char *command = arguments[1];

    // // Construct the full command path by concatenating /bin/ with the user's command
    // strcpy(full_command, path);
    // strcat(full_command, command);

    //Get the starting time
    gettimeofday(&start, NULL);

    pid_t child1 = fork();

    if (child1 == 0){

        execvp(arguments[1], &arguments[1]);

        // //for exeve()
        // execve(full_command, &arguments[1],NULL);

    }else {
        wait(NULL);
        gettimeofday(&end, NULL);

        double time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
        printf("\nExecution time: %f seconds\n\n\n",time);
    }

}
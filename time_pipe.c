#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/wait.h> 
#include <sys/time.h>
#include <sys/stat.h>        
#include <fcntl.h>           
#include <sys/mman.h>
#include <string.h>

void main(int argc, char *arguments[]){

    // Check if user provided a command
    if (argc < 2) {
        printf("\nProvide the correct command\n\n");
        return;
    }

    int pipefd[2];  // Array to hold pipe file descriptors
    struct timeval start, end;
    double time1;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        printf("Pipe creation failed!\n");
        exit(1);
    }

    //for execve()
    // // Define the /bin/ directory as the path for the command
    // const char *path = "/bin/";
    // char full_command[256];     
    // char *command = arguments[1];

    // // Construct the full command path by concatenating /bin/ with the user's command
    // strcpy(full_command, path);
    // strcat(full_command, command);

    pid_t child1 = fork();

    if (child1 == 0){

        // Close the read end of the pipe
        close(pipefd[0]);

        //Get time and write in pipe right before executing the vommand
        gettimeofday(&start, NULL);
        write(pipefd[1],&start, sizeof(struct timeval));
        
        // Close the write end of pipe after writing the data in it
        close(pipefd[1]);
        
        //execute the command
        execvp(arguments[1], &arguments[1]);

        // //for exeve()
        // execve(full_command, &arguments[1],NULL);

    }else {

        //wait till children process gets completed
        wait(NULL);

        //record time after command execution is completed
        gettimeofday(&end, NULL);

        // Close the write end of the pipe
        close(pipefd[1]);

        //reading the data from pipe(time just before we execute the command) and storing it in start pointer
        read(pipefd[0], &start, sizeof(struct timeval));

        // Close the read end after reading
        close(pipefd[0]);

        //Calculte the time taken by system to execute the command(used pipe to get exact time before executing the command)
        time1 = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
        printf("\nExecution time: %f seconds\n\n\n",time1);
    }


}
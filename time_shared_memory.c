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
        printf("\nProvide the correct command.\n\n");
        return;
    }

    struct timeval start, end;

    const char *name = "save_start_time"; // Shared memory name
    const int SIZE = sizeof(struct timeval); // Shared memory size(in bytes)

    int shm_fd; // Shared memory file descriptor
    void *ptr;  // Pointer to the shared memory


    // Create shared memory object
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        printf("Error creating shared memory!\n");
        exit(1);
    }

    // Resize the shared memory object
    if (ftruncate(shm_fd, SIZE) == -1) {
        printf("Error occured while resizing shared memory!\n");
        exit(1);
    }

    // Map shared memory in this process
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Mapping failed!\n");
        exit(1);
    }

    //for execve()
    //Define the /bin/ directory as the path for the command
    // const char *path = "/bin/";
    // char full_command[256];       // Buffer to hold the full command path
    // char *command = arguments[1]; // Command provided by the user (without path)

    // // Construct the full command path by concatenating /bin/ with the user's command
    // strcpy(full_command, path);
    // strcat(full_command, command);

    pid_t child1 = fork();

    if (child1 == 0){

        //time stamp right before we execute the command
        gettimeofday(&start, NULL);

        // Store the start time directly into shared memory
        memcpy(ptr, &start, sizeof(struct timeval));
        
        //executing the user inputted command
        execvp(arguments[1], &arguments[1]);

        //for exeve()
        // execve(full_command, &arguments[1],NULL);

    }else {

        //wait till child process is completed
        wait(NULL);

        //time stamp when we know commands execution is completed
        gettimeofday(&end, NULL);

        // Retrieve the start time from shared memory
        struct timeval *start = (struct timeval *)ptr;  // Cast shared memory to struct timeval pointer

        //This is time taken by system to execute the command, calculated using shared memory
        double time = (end.tv_sec - start->tv_sec) + (end.tv_usec - start->tv_usec) * 1e-6;
        printf("\nExecution time: %f seconds\n\n\n",time);
    }

}
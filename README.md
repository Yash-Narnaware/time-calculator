# Time Calculator
Program to calculate the time taken to run various linux commands using various methods

## Files in the directory - 

1. time_simplistic.c - to execute command and compute gross time considering scheduling and context switch time

2. time_pipe.c - contains code for executing a command and measuring the time using pipe mechanism

3. time_shared_memory.c - contains code for executing a command and measuring the time using shared memory mechanism

4. Makefile - to automate the compiling process


## How to run this program?

* Calculating gross time -
    1. Run command "make time_simplistic"
    2. Run command "./time {your_command}"

   e.g. - ./time ls -l

* Running shared memory implementation -
    1. Run command "make shared_memory"
    2. Run command "./time {your_command}"

   e.g. - ./time ls -l

* Running pipe implementation -
    1. Run command "make pipe"
    2. Run command "./time {your_command}"
  
   e.g. - ./time ls -l

* Running all implementations at once - 
    1. Run command "make CMD="{your_command}""

e.g. - make CMD="ls -l"

Note - make sure while typing command for 4 put your command in double quotes.

* Clean all .o and executable files - 
    Run command "make clean"


## Comparison of 3 approaches - 

As expected calculated time using simplistic approach will be largest amongst the 3 implementations because it includes scheduling and context switch time. Shared memory approach time is taking the least amount of time because shared memory allows direct access to data between parent and child, in shared memory we don't have to copy data back and forth like pipe and pipes involves context switch which increases the time


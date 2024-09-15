all:final

final: time_simplistic.o time_shared_memory.o time_pipe.o
	@echo
	@echo "\033[1;32mExecuting the command and calculating the gross time using simplistic approach...\033[0m"	
	gcc time_simplistic.o -o time
	./time $(CMD)
	@echo "\033[1;32mExecuting the command using shared memory...\033[0m"
	gcc time_shared_memory.o -o time
	./time $(CMD)
	@echo "\033[1;32mExecuting the command using pipe...\033[0m"
	gcc time_pipe.o -o time
	./time $(CMD)


time_pipe.o: time_pipe.c
	gcc -c time_pipe.c -o time_pipe.o

pipe: time_pipe.o
	gcc time_pipe.o -o time

time_shared_memory.o: time_shared_memory.c
	gcc -c time_shared_memory.c -o time_shared_memory.o

shared_memory: time_shared_memory.o
	gcc time_shared_memory.o -o time

time_simplistic.o: time_simplistic.c
	gcc -c time_simplistic.c -o time_simplistic.o

time_simplistic: time_simplistic.o
	gcc time_simplistic.o -o time

clean:
	@echo
	@echo "\033[1;31mRemoving executables and .o files...\033[0m"
	rm -f time_shared_memory.o time_pipe.o time_simplistic.o time
	@echo

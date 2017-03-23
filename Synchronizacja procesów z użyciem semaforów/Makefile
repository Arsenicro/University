CPP = gcc -pthread
FLAGS = -std=gnu99 -Wall -W

prog: Makefile prog.o agent.o smoker.o
		$(CPP) $(FLAGS) -o prog prog.o agent.o smoker.o

prog.o:  Makefile prog.c
		$(CPP) $(FLAGS) -c prog.c -o prog.o

agent.o:  Makefile agent.c
		$(CPP) $(FLAGS) -c agent.c -o agent.o
		
smoker.o:  Makefile smoker.c
		$(CPP) $(FLAGS) -c smoker.c -o smoker.o
		
clean :
	rm -rf *.o prog


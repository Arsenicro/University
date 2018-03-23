CPP = g++
FLAGS = -Wall -Wextra -std=c++11

main: Makefile main.o stack.o
	$(CPP) $(FLAGS) -o main main.o stack.o

stack.o: Makefile stack.cpp stack.h
	$(CPP) $(FLAGS) -c stack.cpp -o stack.o

main.o: Makefile main.cpp stack.h
	$(CPP) $(FLAGS) -c main.cpp -o main.o

clean: Makefile
	rm -rf *.o main

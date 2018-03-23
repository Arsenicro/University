CPP = g++
FLAGS = -std=c++11 -Wall -Wextra

main: hello hello2 Makefile

hello: hello.cpp Makefile
	$(CPP) $(FLAGS) hello.cpp -o hello

hello2: hello2.cpp Makefile
	$(CPP) $(FLAGS) hello2.cpp -o hello2

clean:
	rm -rf *.o hello hello2

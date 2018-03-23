Flags = -std=c++11 -Wall -W
CPP = g++

server : server.o read.o answer.o sockwrap.o utils.o
	$(CPP) $(Flags) -o server server.o read.o answer.o sockwrap.o utils.o

server.o : server.cpp
	$(CPP) -c $(Flags) server.cpp -o  server.o

read.o : read.cpp
	$(CPP) -c $(Flags) read.cpp -o read.o

answer.o : answer.cpp
	$(CPP) -c $(Flags) answer.cpp -o answer.o

sockwrap.o : sockwrap.cpp
	$(CPP) -c $(Flags) sockwrap.cpp -o sockwrap.o	

utils.o : utils.cpp
	$(CPP) -c $(Flags) utils.cpp -o utils.o	

clean:
	rm -rf *.o

distclean:
	rm -rf *.o server	

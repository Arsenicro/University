CPP = gcc
FLAGS = -std=gnu99 -Wall -W

main: Makefile main.o receive.o send.o traceroute.o
		$(CPP) $(FLAGS) -o main main.o receive.o send.o traceroute.o

main.o:  Makefile main.c
		$(CPP) $(FLAGS) -c main.c -o main.o

receive.o: Makefile receive.c
		$(CPP) $(FLAGS) -c receive.c -o receive.o
		
send.o: Makefile send.c
		$(CPP) $(FLAGS) -c send.c -o send.o
		
traceroute.o: Makefile traceroute.c traceroute.h
		$(CPP) $(FLAGS) -c traceroute.c -o traceroute.o
		
clean :
	rm -rf *.o main

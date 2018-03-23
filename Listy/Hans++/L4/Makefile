Flags =  -Wall -Wextra -std=c++11

main : main.o string.o 
	g++ -o main main.o string.o $(Flags)

string.o : string.cpp string.h
	g++ -o string.o -c string.cpp $(Flags)

main.o : main.cpp string.h
	g++ -o main.o -c main.cpp $(Flags) 


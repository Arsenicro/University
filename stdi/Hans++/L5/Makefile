# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags =  -Wall -Wextra -std=c++11
CPP = g++ 


main : Makefile   tree.o main.o string.o
	$(CPP) $(Flags) -o main   tree.o main.o string.o

tree.o : Makefile   tree.cpp   tree.h 
	$(CPP) -c $(Flags) tree.cpp -o  tree.o

string.o : Makefile string.cpp string.h
	$(CPP) -c $(Flags) string.cpp -o string.o

main.o : Makefile   main.cpp   tree.h 
	$(CPP) -c $(Flags) main.cpp -o  main.o



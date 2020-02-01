# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11
CPP = g++


main : Makefile   main.o rational.o matrix.o 
	$(CPP) $(Flags) -o main   main.o rational.o matrix.o 

main.o : Makefile   main.cpp   matrix.h rational.h vector.h 
	$(CPP) -c $(Flags) main.cpp -o  main.o


rational.o : Makefile   rational.cpp   rational.h 
	$(CPP) -c $(Flags) rational.cpp -o  rational.o


matrix.o : Makefile   matrix.cpp   matrix.h rational.h vector.h 
	$(CPP) -c $(Flags) matrix.cpp -o  matrix.o


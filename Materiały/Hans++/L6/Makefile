
# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wall -Wextra -std=c++11 -O3 -flto
CPP = g++ 


main : Makefile   main.o listtest.o vectortest.o 
	$(CPP) $(Flags) -o main   main.o listtest.o vectortest.o 

main.o : Makefile   main.cpp   vectortest.h listtest.h timer.h
	$(CPP) -c $(Flags) main.cpp -o  main.o


listtest.o : Makefile   listtest.cpp   listtest.h 
	$(CPP) -c $(Flags) listtest.cpp -o  listtest.o


vectortest.o : Makefile   vectortest.cpp   vectortest.h 
	$(CPP) -c $(Flags) vectortest.cpp -o  vectortest.o



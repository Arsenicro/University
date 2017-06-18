# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11
CPP = g++ 


main : Makefile   main.o  e7map.o e7umap.o vectortest.o
	$(CPP) $(Flags) -o main main.o e7map.o e7umap.o vectortest.o

e7map.o : Makefile   e7map.cpp   e7map.h 
	$(CPP) -c $(Flags) e7map.cpp -o e7map.o

e7umap.o : Makefile   e7umap.cpp   e7umap.h 
	$(CPP) -c $(Flags) e7umap.cpp -o e7umap.o

vectortest.o : Makefile   vectortest.cpp   vectortest.h 
	$(CPP) -c $(Flags) vectortest.cpp -o vectortest.o

main.o : Makefile   main.cpp e7map.h
	$(CPP) -c $(Flags) main.cpp -o  main.o

clean :
	rm -f *.o main

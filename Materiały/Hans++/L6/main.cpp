
#include <fstream>
#include <iostream>
#include <random>
#include "listtest.h"
#include "vectortest.h"
#include "timer.h"


int main( )
{

	//1

	std::string filename = "test";
	std::ifstream input{ filename };
	std::vector<std::string> vect;

	if (!input) {
		std::cout << "Could not read file " << filename << "." << std::endl;
	}

	else {
		vect = vectortest::readfile(input);
	}
	

	std::vector< std::string > vect = vectortest::randomstrings(100, 50);
	std::vector< std::string > v1 = vect;
	std::vector< std::string > v2 = vect;
	std::vector< std::string > v3 = vect;
	std::list<std::string> l1 = listtest::vect_to_list(vect);
	std::list<std::string> l2 = listtest::vect_to_list(vect);
	std::list<std::string> l3 = listtest::vect_to_list(vect);

		//4:
	//assign O(n^2)
	auto t1 = std::chrono::high_resolution_clock::now( ); 
	vectortest::sort_assign(v1);
	auto t2 = std::chrono::high_resolution_clock::now( );

	std::chrono::duration< double > d = ( t2 - t1 );

	std::cout << "assign sorting took " << d.count( ) << " seconds\n";

	//move O(n^2) but faster
	t1 = std::chrono::high_resolution_clock::now( ); 
	vectortest::sort_move(v2);
	t2 = std::chrono::high_resolution_clock::now( );

	d = ( t2 - t1 );

	std::cout << "move sorting took " << d.count( ) << " seconds\n";

	//std: O(n logn)
	t1 = std::chrono::high_resolution_clock::now( ); 
	vectortest::sort_std(v3);
	t2 = std::chrono::high_resolution_clock::now( );

	d = ( t2 - t1 );

	std::cout << "std sorting took " << d.count( ) << " seconds\n";

	//assign O(n^2)
	t1 = std::chrono::high_resolution_clock::now( ); 
	listtest::sort_assign(l1);
	t2 = std::chrono::high_resolution_clock::now( );

	d = ( t2 - t1 );

	std::cout << "assign sorting took " << d.count( ) << " seconds\n";

	//move O(n^2) but faster
	t1 = std::chrono::high_resolution_clock::now( ); 
	listtest::sort_move(l2);
	t2 = std::chrono::high_resolution_clock::now( );

	d = ( t2 - t1 );

	std::cout << "move sorting took " << d.count( ) << " seconds\n";

	//std O(n^2) but faster
	t1 = std::chrono::high_resolution_clock::now( ); 
	listtest::sort_std(l3);
	t2 = std::chrono::high_resolution_clock::now( );

	d = ( t2 - t1 );

	std::cout << "std sorting took " << d.count( ) << " seconds\n";


	return 0;
}



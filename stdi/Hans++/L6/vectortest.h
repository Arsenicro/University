
#ifndef VECTORTEST_INCLUDED
#define VECTORTEST_INCLUDED  1

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace vectortest
{

   std::vector<std::string> readfile( std::istream& input );

   std::vector<std::string> randomstrings( size_t nr, size_t s );
      // Return nr random strings of length s.

   void sort_assign( std::vector< std::string > & v );
      // Sort the vector with bubble sort, using assignment for the exchanges.

   void sort_move( std::vector< std::string > & v );
      // Sort the vector with bubble sort, using std::swap for the exchanges.

   void sort_std( std::vector< std::string > & v );
      // Sort using std::sort.

}

std::ostream& 
operator << ( std::ostream& , const std::vector< std::string > & );
   // Must be not in namespace. 

#endif 


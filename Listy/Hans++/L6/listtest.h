
#ifndef LISTTEST_INCLUDED
#define LISTTEST_INCLUDED   1

#include <list> 
#include <vector>
#include <string> 
#include <fstream>
#include <iostream>

// I agree that the use of namespace in this little exercise
// is a bit exagerated, but one has to learn this technique.

namespace listtest 
{

   	std::list<std::string> readfile( std::istream& input );

	//5, converts vectors of strings to lists of strings
	std::list<std::string> vect_to_list( const std::vector< std::string > & v );
 
	void sort_assign( std::list< std::string > & v );
      // Sort the list with bubble sort, using assignments for the exchanges.

   	void sort_move( std::list< std::string > & v );
      // Sort the list with bubble sort, using std::swap for the exchanges.

   	void sort_std( std::list< std::string > & v );
      // Sort using std::sort. Impossible

}

std::ostream& 
operator << ( std::ostream& , const std::list< std::string > & );
   // Must be not in namespace. 

#endif 



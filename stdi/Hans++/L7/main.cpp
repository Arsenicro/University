#include "e7map.h"
#include "e7umap.h"
#include "vectortest.h"

int main( int argc, char* argv [ ] )
{
#if 1
	std::cout << frequencytable( std::vector< std::string > {"THIS", "AA", "aA", "Aa", "this" } );
	case_insensitive_cmp c;
	case_insensitive_equality e;
	std::cout << c( "A", "a" ) << " " << e( "A", "a" ) << " " << c( "a","b" ) 
	<< " " << c( "A", "b" ) << "\n";

	case_insensitive_hash h;
	std::cout << h( "xxz" ) << " " << h( "XXX" ) << "\n";
	std::cout << h( "Abc" ) << " " << h( "abC" ) << "\n";
	std::cout << e( "xxx", "XXX" ) << "\n";
#endif

#if 1
	std::string filename = "test";
	std::ifstream input{ filename };
	std::vector<std::string> vect;

	vect = vectortest::readfile(input);
	
	std::map<std::string, unsigned int, case_insensitive_cmp> frq = frequencytable(vect);
	 	

	std::cout << frq["magnus"] << std::endl << frq["hominum"] << std::endl << frq["memoria"] << std::endl;
	
	std::string fw;
	size_t oc = 0;

	for(const auto &kv : frq){
		if (kv.second > oc){
			oc = kv.second;
			fw = kv.first;
		}	
	} 

	std::cout << fw << " " << oc << std::endl;

#endif
}

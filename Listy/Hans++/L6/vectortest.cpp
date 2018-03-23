#include "vectortest.h"

#include <random>
#include <chrono> 
#include <algorithm>

std::vector< std::string >
vectortest::randomstrings( size_t nr, size_t s )
{
	static std::default_random_engine gen( 
	  std::chrono::system_clock::now( ). time_since_epoch( ). count( ) );
		 // Narrowing long int into int, but that is no problem.

	static std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012345689";
	static std::uniform_int_distribution<int> distr( 0, alphabet. size( ) - 1);
	  // More narrowing.

	std::vector< std::string > res;

	for( size_t i = 0; i < nr; ++ i )
	{
		std::string rand;
		for( size_t j = 0; j < s; ++ j )
		{
		 rand. push_back( alphabet[ distr( gen ) ] );  
		}

		res. push_back( std::move( rand ));
	}
	return res;
}
         

//1
std::vector<std::string> 
vectortest::readfile( std::istream& input ) 
{
	std::vector<std::string> vector;
	std::string word;
	
	while(true)
	{
		char current;
        if (!input.get(current)) vector.push_back(word);break;
		std::cout << (int) current << std::endl;
		if(isspace(current) || ispunct(current) || !isprint(current))
		{
			if(!word.empty())
			{
				vector.push_back(word);
				word.clear();
			} 
		}
		else
		{
			word+=current;
		}
	
	}
	
	return vector;

}

//2
std::ostream& 
operator << ( std::ostream& out, const std::vector< std::string > & vect ) 
{ 
	for (std::string s : vect) out << s << "(" << s.size() << ") ";
    return out;
}

//3
void vectortest::sort_assign( std::vector< std::string > & v )
{
	for( size_t j = 0; j < v. size( ); ++ j )
		for( size_t i = 0; i < j; ++ i )
		{
			if( v[i] > v[j] )
			{
				std::string s = v[i];
				v[i] = v[j];
				v[j] = s;
			}
		}
}

void vectortest::sort_move( std::vector< std::string > & v )
{
	for( size_t j = 0; j < v. size( ); ++ j )
		for( size_t i = 0; i < j; ++ i )
		{
			if( v[i] > v[j] )
				std::swap( v[i], v[j] );
		}
	
}

void vectortest::sort_std( std::vector< std::string > & v )
{
	std::sort( v. begin( ), v. end( ));
}






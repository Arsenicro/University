#ifndef _STACK
#define _STACK 1
#include <algorithm>
#include <iostream>
#include <initializer_list>
class stack
{
	size_t current_size;
	size_t current_capacity;
	double* tab;
	void ensure_capacity( size_t c );

	friend std::ostream& operator << ( std::ostream& stream, const stack& s );

	public:

		stack( );
		stack( std::initializer_list<double> d );
		stack( const stack& s );
		~stack( ) { delete[] tab; }; //
		void operator = ( const stack& s );
		void push( double d );
		void pop( ) { current_size--; }
		void reset( size_t s ){ current_size = s; };
		double& top( ) { return tab[current_size-1]; } //
		double top( ) const { return tab[current_size-1]; } //
		size_t size( ) const { return current_size; }
		bool empty( ) const { return current_size == 0; }
};

#endif

#include "stack.h"

void stack::ensure_capacity( size_t c )
{
	if( current_capacity < c )
	{
		// New capacity will be the greater of c and
		// 2 * current_capacity.
		if( c < 2 * current_capacity )
			c = 2 * current_capacity;
		double* newtab = new double[ c ];
		for( size_t i = 0; i < current_size; ++ i )
			newtab[i] = tab[i];
		current_capacity = c;
		delete[] tab;
		tab = newtab;
	}
}

stack::stack():
	current_size{0},
	current_capacity{0},
	tab{nullptr} {}

stack::stack( std::initializer_list<double> d ) :
	current_size{d.size()},
	current_capacity{d.size()},
	tab{new double[current_capacity]}{
		std::copy(d.begin(), d.end(), tab);
	}

stack::stack( const stack& s ):
	current_size{s.current_size},
    current_capacity{s.current_size},
    tab{new double[current_capacity]} {
    	std::copy(s.tab, s.tab + current_capacity, tab);
	}

void stack::operator = (const stack &s){
	if(s.current_size!=current_size){

		delete[] tab;
		tab = new double[s.current_capacity];
		current_size = s.current_size;
		current_capacity = s.current_capacity;
	}
	std::copy(s.tab, s.tab + current_capacity, tab);

}


void stack::push( double d ){
    ensure_capacity(current_size + 1);
    tab[current_size] = d;
    current_size++;
}

std::ostream& operator << ( std::ostream& stream, const stack& s )
{
	for(size_t i = 0; i<s.current_size; i++){
		stream << " " << s.tab[i];
	}
	return stream;

}

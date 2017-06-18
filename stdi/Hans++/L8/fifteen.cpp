#include "fifteen.h"

fifteen::fifteen(){
	for(size_t i=0; i<dimension; i++){
		for(size_t j=0; j<dimension; j++){
			table[i][j] = dimension*i + j + 1; 
		}
	}
	
	open_i = dimension - 1;
	open_j = dimension - 1;
	table[open_i][open_j] = 0;
}

fifteen::fifteen( std::initializer_list< std::initializer_list< size_t >> init ){

	size_t i = 0;

	for(auto it_i = init.begin(); i < dimension && it_i != init.end(); ++i, ++it_i){
		size_t j = 0;
		for(auto it_j = (*it_i).begin(); j < dimension && it_j != (*it_i).end(); ++j, ++it_j){
			table[i][j] = *it_j;
			if(*it_j == 0){
				open_i = i;
				open_j = j;
			}
		}
	}
}

std::ostream& operator << ( std::ostream& stream, const fifteen& f )
{
	for(size_t i = 0; i < f.dimension; ++i){
		for(size_t j = 0; j < f.dimension; ++j){
			stream << f.table[i][j] << "\t";
		}

		stream << "\n";
	}

	return stream;
}

std::pair< size_t, size_t > fifteen::solvedposition( size_t val ){

	if(val==0) return std::make_pair(dimension-1, dimension-1);
	else return std::make_pair((val-1)/dimension, (val-1) % dimension);

}

size_t fifteen::hashvalue( ) const {

	size_t w = 0;
	const size_t MOD = 1000007;

	for(size_t i = 0; i < dimension; ++i){
		for(size_t j = 0; j < dimension; ++j){
			 size_t w1 = ( (i+13) * 17 + (j + 13) * 17);
			 size_t w2 = i + j + 2137;
			 w = (( (w+w1) % MOD ) * w2) % MOD;
		}
	}

	return w;
}

bool fifteen::equals( const fifteen& other ) const {

    if (dimension != other.dimension) return false;

	for(size_t i = 0; i < dimension; ++i){
		for(size_t j = 0; j < dimension; ++j){
			if(table[i][j] != other.table[i][j]) return false;
		}
	}

	return true;
}

void fifteen::makemove( move m ){

	size_t x = open_i, y = open_j;
	
	switch(m){
		case move::left:
			if(y==0) throw illegalmove(m);
			else{
				std::swap(table[x][y], table[x][y-1]); 
				open_j -= 1;
			}
			break;
		case move::right:
			if(y==dimension-1) throw illegalmove(m);
			else{
				std::swap(table[x][y], table[x][y+1]); 
				open_j += 1;
			}
			break;
		case move::up:
			if(x==0) throw illegalmove(m);
			else{
				std::swap(table[x][y], table[x-1][y]); 
				open_i -= 1;
			}
			break;
		case move::down:
			if(x==dimension-1) throw illegalmove(m);
			else{
				std::swap(table[x][y], table[x+1][y]); 
				open_i += 1;
			}
			break;						
	}

}

bool fifteen::issolved() const {
    return distance() == 0;
}


size_t fifteen::distance( ) const {
	size_t dist = 0;

	for(size_t i = 0; i < dimension; i++){
		for(size_t j = 0; j < dimension; j++){	
			if(table[i][j]!=0){
				dist += distance({i,j},solvedposition(table[i][j]));
			}
		}
	}

	return dist;
}

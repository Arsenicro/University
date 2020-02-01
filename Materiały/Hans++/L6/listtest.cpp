
#include "listtest.h"

#include <random>
#include <chrono>
#include <algorithm>

//2

std::ostream& 
operator << ( std::ostream& out , const std::list< std::string > &list )
{
    for (std::string s : list) out << s << " ";
    return out;
}

//5
void listtest::sort_move(std::list<std::string> &v) {
    for (auto q = v.begin(); q != v.end(); q++) {
        for (auto p = v.begin(); p != q; p++) {
			if (*p > *q) {
				std::swap(*p, *q);
			}
		}
	}
}

void listtest::sort_assign(std::list<std::string> &v) {
    for (auto q = v.begin(); q != v.end(); q++) {
        for (auto p = v.begin(); p != q; p++) {
			if (*p > *q) {
				std::string s = *p;
				*p = *q;
				*q = s;
			}
		}
	}
}
void listtest::sort_std( std::list< std::string > & v ){
	v.sort();
}

std::list<std::string> listtest::vect_to_list( const std::vector<std::string> &v ) {
    std::list<std::string> list;
    for (std::string s : v) list.push_back(s);
    return list;
}

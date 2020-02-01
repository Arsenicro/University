#include "tree.h"

int main() {
	tree t1(string("a"));
	tree t2(string("b")); 
	tree t3 = tree(string("c"), { t1, t2 });
	tree t4 = tree(string("d"), { t3, t1 });
	tree t5 = tree(string("e"));
	std::cout << t4  << std::endl <<"****"<< std::endl ;
	std::cout << subst(t4,"a",t3) << std::endl<<"****"<< std::endl ;

	return 0;
}

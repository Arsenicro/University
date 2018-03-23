#include "rational.h"
#include "matrix.h"

int main( int argc, char* argv [ ] )
{

	matrix m1 = { { rational(1, 2), rational(-2, 7) }, { rational(1, 3), rational(2, 8) } };
	matrix m2 = { { rational(-1, 3), rational(2, 5) }, { rational(2, 7), rational(-1, 7) } }; 
	matrix m3 = m1*m2;

	std::cout << "Product:" << "\n" << m3  << "\n" << "Inversion:" << "\n" << m1.inverse();

	matrix t1a = (m1*m2)*m3;
	matrix t1b = m1*(m2*m3);
	std::cout << "Matrix multiplication is associative?" << "\n"  << ((t1a==t1b) ? "Yes" : "No") << "\n";

	matrix t2a = m1*(m2+m3);
	matrix t2b = m1*m2 + m1*m3;
	matrix t2c = (m1+m2)*m3;
	matrix t2d = m1*m3 + m2*m3;
	std::cout << "Matrix multiplication with addition are distributive?" << "\n"  << (((t2a==t2b)&&(t2c==t2d)) ? "Yes" : "No" ) << "\n";

	matrix t3a = m1 * (m2 * 13);
	matrix t3b = (m1*m2)*13;
	std::cout << "Matrix multiplication corresponds to composition of application?" << "\n"  << ((t3a==t3b) ? "Yes" : "No") << "\n";

	rational t4a = m1.determinant() * m2.determinant();
	rational t4b = (m1*m2).determinant();
	std::cout << "Determinant commutes over multiplication?" << "\n"  << ((t4a==t4b) ? "Yes" : "No") << "\n";

	matrix t5a = m1*m1.inverse();
	matrix t5b = m1.inverse()*m1;
	matrix id = matrix::identity();

	std::cout << "Inverse is indeed inverse?" << "\n"  << ( ((t5a==id) && (t5b==id)) ? "Yes" : "No") << "\n";

}


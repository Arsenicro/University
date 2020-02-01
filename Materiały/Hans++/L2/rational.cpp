#include "rational.h"

int rational::gcd( int n1, int n2 ){

	while(n2!=0){
		int c=n2;
		n2=n1%n2;
		n1=c;
	}

	return n1;
}

void rational::normalize( ){


	if (denum == 0)
		return;

	int d = gcd(num,denum);
	num/=d;
	denum/=d;

	if(denum<0){
		denum=-denum;
		num=-num;
	}

}

rational operator - ( rational r ){
	r.num=-r.num;

	return r;
}

rational operator + ( const rational& r1, const rational& r2 ){
	int num = r1.num * r2.denum + r2.num * r1.denum;
	int denum = r1.denum * r2.denum;

	return {num, denum};

}

rational operator - ( const rational& r1, const rational& r2 ){
	int num = r1.num*r2.denum - r2.num * r1.denum;
	int denum = r1.denum*r2.denum;

	return {num, denum};

}

rational operator * ( const rational& r1, const rational& r2 ){
	int num = r1.num * r2.num;
	int denum = r1.denum * r2.denum;

	return {num, denum};

}

rational operator / ( const rational& r1, const rational& r2 ){
	rational inverse = {r2.denum, r2.num};

	return r1 * inverse;

}

bool operator == ( const rational& r1, const rational& r2 ){

	return (r1.num == r2.num && r1.denum == r2.denum);

}

bool operator != ( const rational& r1, const rational& r2 ){

	return (r1.num != r2.num || r1.denum != r2.denum);

}

std::ostream& operator << ( std::ostream& stream, const rational& r ){
	stream << r.num << "/" << r.denum;

	return stream;

}

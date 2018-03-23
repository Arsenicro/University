#include "string.h"
#include <stdexcept>

std::ostream& operator << ( std::ostream& out, const string& s )
{
	for( const char c : s )
		out << c;
	return out;
}

char string::operator [] (size_t i) const{
	if(i>=len)
		throw std::runtime_error("Index out of range");
	return p[i];
}

char& string::operator [] ( size_t i ){
	if(i>=len)
		throw std::runtime_error("Index out of range");
	return p[i];
}

void string::operator += ( char c ){
	char *temp = new char[len+1];
	std::copy(p,p+len,temp);
	temp[len]=c;

	len+=1;
	delete[] p;
	p=temp;
}

void string::operator += ( const string& s ){
	char *temp = new char[len+s.len];

	std::copy(p,p+len,temp);
	std::copy(s.p, s.p + len, temp+len);

	len+=s.len;
	delete[] p;
	p=temp;
}
bool string::operator == (const string& other){
	if(len != other.len) return false;

	for(size_t i=0; i<len; i++)
		if(p[i] != other.p[i]) return false;

	return true;
}

bool string::operator != (const string& other){
	return !(*this == other);
}

bool string::operator < (const string& other) {
    size_t min = std::min(len, other.len);

	size_t i=0;
	while(i<min && (this->p[i] == other.p[i])) i++;

	if(i>min) return (min==this->len) && (min!=other.len);
	return (this->p[i] < other.p[i]);

}

bool string::operator > (const string& other) {
	return (&other < this);

}

bool string::operator <= (const string& other){
	return !(*this > other);
}

bool string::operator >= (const string& other){
	return !(*this < other);
}

string operator + (string s1, const string& s2){
	s1+=s2;
	return s1;
}

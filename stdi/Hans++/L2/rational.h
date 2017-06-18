#ifndef RATIONAL_INCLUDED
#define RATIONAL_INCLUDED 1

#include <iostream>

struct rational
{
   int num;
   int denum;

   // Functions with the same name as the class are constructors.
   // Default constructor constructs 0.

   rational( )
      : num{0},
        denum{1}
   { }

   rational( int i )
      : num{i}, 
        denum{1}
   { }

   rational( int num, int denum )
      : num{ num }, denum{ denum }
   {
      normalize( ); 
   }

   static int gcd( int n1, int n2 );
      // Use Euclidean Algorithm. 
      // static means that the function can be called without
      // class object. The function has no access to the fields
      // num and denum. 

   void normalize( );
      // Divide common factors out of num and denum.
      // Normalizing a rational number is quite a subtle process.
      // What to do with i / 0?
      // What about 0 / 0?
      // What about -4 / -3?

};

// In normal cases, most of the functions below would
// be inline.
// It is not allowed in this task, because this task is about
// how one normally puts a C++ program in different files.

rational operator - ( rational r );

rational operator + ( const rational& r1, const rational& r2 );  
rational operator - ( const rational& r1, const rational& r2 ); 
rational operator * ( const rational& r1, const rational& r2 );
rational operator / ( const rational& r1, const rational& r2 );

bool operator == ( const rational& r1, const rational& r2 );
bool operator != ( const rational& r1, const rational& r2 );

std::ostream& operator << ( std::ostream& stream, const rational& r ); 

#endif

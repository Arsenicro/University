#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED   1

#include <iostream>
#include "rational.h"
#include "vector.h"

struct matrix
{
   rational repr [2][2];

   // First vector is first column. Second vector is second column.

   matrix( const vector& v1, const vector& v2 )
      : repr{ { v1.x, v2.x }, { v1.y, v2.y } }
   {
   }

public:
   static matrix zero( );
   static matrix identity( );
   static matrix diagonal( const vector& v );
      // Examples of static functions that play the role of constructors.

   rational determinant( ) const;

   vector operator( ) ( const vector& v ) const;

   matrix adjugate( ) const;
   matrix inverse( ) const;
      // Throws a runtime exception when the matrix is singular.
};

matrix operator - ( const matrix& m );
matrix operator + ( const matrix& m1, const matrix& m2 );
matrix operator - ( const matrix& m1, const matrix& m2 );
matrix operator * ( const rational& r, const matrix& m );
matrix operator * ( const matrix& m, const rational& r );
matrix operator * ( const matrix& m1, const matrix& m2 );
void operator *= ( matrix& m, const rational& r );
matrix operator * ( const matrix& m1, const matrix& m2 );
matrix operator / ( const matrix& m, const rational& r );
void operator /= ( matrix& m, const rational& r );
bool operator == ( const matrix& m1, const matrix& m2 );
bool operator != ( const matrix& m1, const matrix& m2 );

std::ostream& operator << ( std::ostream& stream, const matrix& m );

#endif


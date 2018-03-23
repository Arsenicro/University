#include "matrix.h"
#include <stdexcept>

matrix matrix::zero( )
{
   return matrix( { { 0, 0 }, { 0, 0 } } );
}

matrix matrix::identity( )
{
   return matrix( { { 1, 0 }, { 0, 1 } } ); 
}


matrix matrix::diagonal( const vector& v )
{
   return matrix( { { v.x, 0 }, { 0, v.y } } ); 
}

rational matrix::determinant( ) const
{
   return repr [0][0] * repr [1][1] - repr [1][0] * repr [0][1]; 
}

vector matrix::operator( ) ( const vector& v ) const
{
   return vector( repr [0][0] * v.x + repr [0][1] * v.y,
                  repr [1][0] * v.x + repr [1][1] * v.y );
}

matrix matrix::adjugate( ) const
{
   return matrix( { { repr[1][1], -repr[1][0] }, 
                    { -repr[0][1], repr[0][0] } } );
}

matrix matrix::inverse( ) const 
{
   rational r = determinant( );
   if( r. num == 0 ) 
      throw std::runtime_error( "inverted matrix is singular" ); 
   return adjugate( ) / r;
}


matrix operator - ( const matrix& m )
{
   return matrix( { { - m. repr[0][0], - m. repr[1][0] },
                    { - m. repr[0][1], - m. repr[1][1] } } );
}

matrix operator + ( const matrix& m1, const matrix& m2 )
{
   return matrix( { { m1. repr[0][0] + m2. repr[0][0],
                      m1. repr[1][0] + m2. repr[1][0] },
                    { m1. repr[0][1] + m2. repr[0][1],
                      m1. repr[1][1] + m2. repr[1][1] } } );
}

matrix operator - ( const matrix& m1, const matrix& m2 )
{
   return matrix( { { m1. repr[0][0] - m2. repr[0][0],
                      m1. repr[1][0] - m2. repr[1][0] },
                    { m1. repr[0][1] - m2. repr[0][1],
                      m1. repr[1][1] - m2. repr[1][1] } } );
}

matrix operator * ( const matrix& m, const rational& r )
{
   return matrix( { { m. repr[0][0] * r,  m. repr[1][0] * r },
                    { m. repr[0][1] * r,  m. repr[1][1] * r } } );
}

matrix operator * ( const rational& r, const matrix& m )
{
   return matrix( { { r * m. repr[0][0],  r * m. repr[1][0] },
                    { r * m. repr[0][1],  r * m. repr[1][1] } } );
}

void operator *= ( matrix& m, const rational& r )
{
   m. repr[0][0] = m. repr[0][0] * r;
   m. repr[1][0] = m. repr[1][0] * r;
   m. repr[0][1] = m. repr[0][1] * r;
   m. repr[1][1] = m. repr[1][1] * r;
}


matrix operator * ( const matrix& m1, const matrix& m2 )
{
   return matrix( 
      vector( m1. repr [0][0] * m2. repr [0][0] +
              m1. repr [0][1] * m2. repr [1][0], 
              m1. repr [1][0] * m2. repr [0][0] +
              m1. repr [1][1] * m2. repr [1][0] ),
      vector( m1. repr [0][0] * m2. repr [0][1] +
              m1. repr [0][1] * m2. repr [1][1], 
              m1. repr [1][0] * m2. repr [0][1] +
              m1. repr [1][1] * m2. repr [1][1] ));
}


matrix operator / ( const matrix& m, const rational& r )
{
   return matrix( { { m. repr[0][0] / r, m. repr[1][0] / r },
                    { m. repr[0][1] / r, m. repr[1][1] / r } } ); 
}

void operator /= ( matrix& m, const rational& r )
{
   m. repr[0][0] = m. repr[0][0] / r;
   m. repr[1][0] = m. repr[1][0] / r;
   m. repr[0][1] = m. repr[0][1] / r;
   m. repr[1][1] = m. repr[1][1] / r;
}

std::ostream& operator << ( std::ostream& out, const matrix& m )
{
   out << "|| " << m. repr[0][0] << ",     " << m. repr[0][1] << " ||\n";
   out << "|| " << m. repr[1][0] << ",     " << m. repr[1][1] << " ||\n";
   return out;
}

bool operator == ( const matrix& m1, const matrix& m2 ){
   matrix m3 = m1-m2;
   return (m3.repr[0][0]==0 && m3.repr[0][1]==0 && m3.repr[1][0]==0 && m3.repr[1][1]==0);
}

bool operator != (const matrix& m1, const matrix& m2){
   return !(m1==m2);
}

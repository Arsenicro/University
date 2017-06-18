#ifndef FIFTEEN_INCLUDED
#define FIFTEEN_INCLUDED  1

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <list>

#include "move.h"


class fifteen
{
private: 
   static constexpr size_t dimension = 4;
      // Test for different dimensions. Don't be lazy!

   static_assert( dimension > 1, "dimension must be two at least" );

   using position = std::pair< size_t, size_t > ;

public:
   size_t table [ dimension ][ dimension ];
      // We use the numbers 1 .. dimension*dimension-1 for the tiles,
      // and 0 for the open place.

   size_t open_i;
   size_t open_j;
      // Position of the open place. Use matrix notation, i is row, 
      // j is column. 

   
   static size_t distance( size_t i1, size_t i2 )
      { return i1 > i2 ? i1 - i2 : i2 - i1; }
         // Distance between two numbers.

   static size_t distance( position p1, position p2 )
      { return distance( p1. first,  p2. first ) +
               distance( p1. second, p2. second ); }
         // Manhattan distance between positions p1 and p2.

   static position solvedposition( size_t val );
      // Position where val must be in the solution.  

public:
   fifteen( );
      // Default constructor constructs the puzzle in solved state.

   fifteen( std::initializer_list< std::initializer_list< size_t >> init );

   void makemove( move m );
      // This method tries to make a move m. If it fails then 
      // it throws illegalmove( move ); 
      // Note that in C++, you don't have to declare possible exceptions.
      // A move is illegal if it would move the open place out of the
      // board. 

   void makemove( const std::list< move > & moves ) 
   {
      for( move m : moves ) makemove(m);
   }

      
   size_t distance( ) const;
      // Estimated distance from solution. Use Manhattan distance,
      // see the wikipedia article. 

   bool issolved( ) const;
      // True if the puzzle is in solved state.

   size_t hashvalue( ) const;
      // Construct a hash value on the state.

   bool equals( const fifteen& other ) const;
      // True if we are equal to other.

   friend std::ostream& operator << ( std::ostream& , const fifteen& f ); 
};

struct fifteen_further
{
   // True if f1 seems further from solved state than f2:

   inline bool operator( ) ( const fifteen& f1, const fifteen& f2 ) const
      { return f1. distance( ) > f2. distance( ); } 
};

struct fifteen_equals
{
   inline bool operator( ) ( const fifteen& f1, const fifteen& f2 ) const
      { return f1. equals( f2 ); }
};

struct fifteen_hash
{
   inline size_t operator( ) ( const fifteen& f ) const
   { return f. hashvalue( ); }
};

std::ostream& operator << ( std::ostream& stream, const fifteen& f );

#endif


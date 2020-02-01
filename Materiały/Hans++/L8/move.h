
#ifndef MOVE_INCLUDED
#define MOVE_INCLUDED 1

#include <iostream>
#include <stdexcept>

enum class move { up, left, right, down };
   // The elements will called
   // move::up, move::left, move::right, move::down.

inline std::ostream& operator << ( std::ostream& out, move m )
{
   switch(m)
   {
   case move::up : out << "move-up"; return out;
   case move::left : out << "move-left"; return out;
   case move::right: out << "move-right"; return out;
   case move::down: out << "move-down"; return out;
   }
   throw std::range_error( "operator << : unkown move" ); 
}


// -m is the reverse move of m.

inline move operator - ( move m )
{
   switch(m)
   {
   case move::up:
      return move::down;
   case move::left:
      return move::right;
   case move::right:
      return move::left;
   case move::down:
      return move::up;
   }
   throw std::range_error( "operator - : unknown move" ); 
}


// All exceptions must inherit from one of the
// exceptions in the exception hierarchy.
// Otherwise, your code may throw exceptions,
// that nobody knows about, and will not be caught. 

struct illegalmove : public std::runtime_error 
{
   move m;

   illegalmove( move m ) : 
      std::runtime_error{ "move is not possible" },   
         // This is a base class initializer. 
      m{m}
   {
   }

};


inline std::ostream& operator << ( std::ostream& out, illegalmove i )
{
   const std::runtime_error& e = i;
   std::cout << e. what( ) << " : " << i.m;
   return out;
}


#endif


#include "move.h"
#include "fifteen.h" 
#include <unordered_map>
#include <queue>

// Table of states and their levels:

using leveltable = 
std::unordered_map< fifteen, unsigned int, 
                    fifteen_hash, fifteen_equals > ;


#if 1

leveltable solve( const fifteen& start ) {
   leveltable levels;

   std::priority_queue< fifteen, std::vector< fifteen >, 
                        fifteen_further > unchecked;

   unchecked. push( start );
   levels[ start ] = 0; 

   // We have start unexplored, at its level is zero.

   std::vector<move> moves = { move::up, move::down, move::left, move::right };
      // All possible moves in a vector.

   // As long as there is a state whose neighbours are unexplored,
   // we explore them:

   while( unchecked. size( ))
   {
      fifteen best = unchecked. top( );
      unsigned int level = levels [ best ]; 
         // The best state is the state that is closest to the
         // solution. level is the number of moves that was required
         // to reach it.
   
       std::cout << "best = " << best << "\n";
       std::cout << "distance = " << best. distance( ) << "\n";

      if( best. issolved( ))
         return levels;

      unchecked. pop( ); 

      for( auto m : moves )
      {
         fifteen next = best;
         try
         {
            next. makemove( m );
            auto p = levels. find( next );
            if( p == levels. end( ) || level + 1 < p -> second ) 
            {
               // We did not reach next before, or we reached it
               // in more steps. 

               levels[ next ] = level + 1; 
               unchecked. push( next );
            }
         }
         catch( illegalmove& m ) { /* catch and do nothing */ } 
      }
   }

   return levels;  // In move we trust.  
}

#endif

std::list< move > findpath( const leveltable& levels,
                            fifteen f, unsigned int level )
{

   std::vector<move> moves = { move::up, move::down, move::left, move::right };
      // All possible moves in a vector.

   std::list< move > path;

	while (level > 0) {
        for (auto &m : moves) {
            try {
                fifteen f1 = f;
                f1.makemove(m);

                auto it = levels. find(f1);
                if( it != levels. end( ))
                if (it -> second < level) {
                    level = it -> second;
                    f=f1;
                    path.push_front(-m); 
                    break;
                }
            }
            catch (illegalmove& m) { }
		    catch (std::out_of_range& m) { }
        }
}


   return path;
}

int main( int argc, char* argv [] )
{
   leveltable test;

   fifteen f{ { 2, 5, 1, 8 }, 
              { 7, 9, 3, 11 }, 
              { 6, 15, 0, 4 }, 
              { 10, 13, 14, 12 } } ;
  

   auto dist = solve(f);
   for( const auto& p : dist )
   {
      std::cout << "---------------------------\n";
      std::cout << p.first << " " << p. second << "\n";
   }

   auto path = findpath( dist, fifteen( ), dist[ fifteen( ) ] );
   for( move m : path )
      std::cout << m << "\n";
   
   return 0;
}



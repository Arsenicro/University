
#ifndef TIMER_INCLUDED
#define TIMER_INCLUDED  1

#include <string>
#include <chrono>
#include <iostream> 

struct timer
{
   std::string name;
   std::chrono::high_resolution_clock::time_point t0;  // Creation moment.
   std::ostream& out;     // Stream where we will report.

   timer( const std::string& name, std::ostream& out = std::cout )
      : name{ std::move( name ) },
        t0{ std::chrono::high_resolution_clock::now( ) },
        out( out ) 
   {}

   // Destructor prints the time since construction.

   ~timer( )
   {
      std::chrono::high_resolution_clock::time_point t1 = 
         std::chrono::high_resolution_clock::now( );

      out << name << " took ";
      out << std::chrono::duration< double > ( t1 - t0 ). count( );
      out << " seconds\n";      
   }
};

#endif


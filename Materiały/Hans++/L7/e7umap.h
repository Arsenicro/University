#ifndef E7UMAP_INCLUDED
#define E7UMAP_MAPTASKS_INCLUDED

#include "e7map.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

struct case_insensitive_hash
{
    size_t operator ( ) ( const std::string& s ) const;
};

struct case_insensitive_equality
{
    bool operator ( ) ( const std::string& s1, const std::string& s2 ) const;
};

std::unordered_map<std::string, unsigned int, case_insensitive_hash, case_insensitive_equality>
hashed_frequencytable( const std::vector<std::string > & text );

std::ostream& operator << (std::ostream& stream, 
const std::unordered_map<std::string, unsigned int, case_insensitive_hash, case_insensitive_equality> &freq);

#endif

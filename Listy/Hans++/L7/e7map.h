#ifndef E7MAP_INCLUDED
#define E7MAP_INCLUDED

#include <map>
#include <string>
#include <vector>
#include <iostream>

struct case_insensitive_cmp
{
	bool operator( ) ( const std::string& s1, const std::string& s2 ) const;
// Return true if s1 < s2, ignoring case of the letters.
};

std::map<std::string, unsigned int, case_insensitive_cmp> frequencytable(const std::vector<std::string> &text);

std::ostream& operator << (std::ostream& stream, const std::map<std::string, unsigned int, case_insensitive_cmp> &freq);

#endif

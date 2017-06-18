#include "e7umap.h"

size_t case_insensitive_hash::operator () ( const std::string& s ) const {
    
	size_t hash = 7;
    for (size_t i = 0; i < s.size(); i++)
        hash = ( ( hash * 3539 + tolower(s[i]) ) * 2137) % 123456789;
        
    return hash;
}

bool case_insensitive_equality::operator () (const std::string& s1, const std::string& s2) const {
    
	case_insensitive_cmp c;
	return !c(s1, s2) && !c(s2, s1);
}

std::unordered_map<std::string, unsigned int, case_insensitive_hash, case_insensitive_equality>
hashed_frequencytable(const std::vector<std::string > &text) {

    std::unordered_map<std::string, unsigned int, case_insensitive_hash, case_insensitive_equality> res;
    for (const std::string &s : text) res[s]++;

    return res;
}

std::ostream& operator << (std::ostream& stream, 
const std::unordered_map<std::string, unsigned int, case_insensitive_hash, case_insensitive_equality> &freq) {
	
	stream << "[ ";
	for(const auto &kv : freq) stream << "\"" << kv.first << "\": " << kv.second << " ";
   	stream << "]" << std::endl;
    	return stream;
}

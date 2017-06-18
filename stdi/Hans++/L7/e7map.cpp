#include "e7map.h"

std::map<std::string, unsigned int, case_insensitive_cmp> frequencytable(const std::vector<std::string> &text){

	std::map<std::string, unsigned int, case_insensitive_cmp> res;
	for(const std::string &s : text) res[s]++;
	
	return res;
}

std::ostream& operator << (std::ostream& stream, const std::map<std::string, unsigned int, case_insensitive_cmp> &freq){

	stream << "[ ";
	for(const auto &kv : freq) stream << "\"" << kv.first << "\": " << kv.second << " ";
   	stream << "]" << std::endl;
    	return stream;
}

bool case_insensitive_cmp::operator () (const std::string& s1, const std::string& s2) const {

	auto it1 = s1.begin();
	auto it2 = s2.begin();
	
	while(it1 != s1.end() && it2 != s2.end()) {
		if (tolower(*it1) < tolower(*it2)) return true;
        	if (tolower(*it1) > tolower(*it2)) return false;
        	it1++; it2++;	
	}
	return (it2 != s2.end());
}

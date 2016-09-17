#ifndef UTILITY_CPP
#define UTILITY_CPP
#include "Utility.h"
#include <locale>

std::string Utility::Upper(std::string word){
	std::string temp = "";
	std::locale loc;
	for(std::string::size_type i = 0; i < word.length(); i++){
		temp = temp + std::toupper(word[i],loc);
		
	}
	return temp;
}

std::string Utility::Lower(std::string word){
	std::string temp = "";
	std::locale loc;
	for(std::string::size_type i = 0; i < word.length(); i++){
		temp = temp + std::tolower(word[i],loc);
	}
	return temp;
}

#endif
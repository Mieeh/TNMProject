#pragma once

#include<string>
#include<fstream>

namespace bear { namespace core { 

static std::string get_file_content(std::string a_Path) 
{
	std::ifstream file(a_Path);
	return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

static std::string get_file_suffix(std::string a_Path) 
{
	size_t index = a_Path.find_last_of('.');
	if (index != std::string::npos) {
		return a_Path.substr(index, a_Path.length() - index);
	}
	return "Suffix not found";
}

}} 
#include "Loader.hpp"

std::string e::loader::read_file(const std::string& filename) {
	std::ifstream stream(filename);
	std::string str((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
	return str;
}
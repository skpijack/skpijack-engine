#include "efs.hpp"

std::optional<std::string> efs::read_text_file(const std::string& _filename) {
	// Open stream for read
	std::ifstream stream(_filename, std::ios::in);
	
	// Check file existence
	if (!stream.is_open()) return std::nullopt;
	
	// read
	std::string content((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
	
	return content;
}

std::optional<std::vector<std::byte>> efs::read_binary_file(const std::string& _filename) {
	// Open stream for read
	std::ifstream stream(_filename, std::ios::in | std::ios::binary);

	// Check file existence
	if (!stream.is_open()) return std::nullopt;

	// read
	std::vector<std::byte> content;
	char ch;
	while (stream.get(ch))
		content.push_back(static_cast<std::byte>(ch));

	return content;
}
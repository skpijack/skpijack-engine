#pragma once
#include <string>
#include <fstream>
#include <optional>
#include <vector>

namespace efs {
	std::optional<std::string> read_text_file(const std::string& _filename);
	std::optional<std::vector<std::byte>> read_binary_file(const std::string& _filename);
};
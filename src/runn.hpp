#pragma once

#include "files.hpp"
#include <string>
#include <sstream>

std::stringstream init();

std::string trim(const std::string &str);

std::string remove_semi(const std::string &line);

std::string remove_brace(const std::string &line);

std::string handle_print(const std::string &line);

std::string handle_let(const std::string &line);

std::string handle_return(const std::string &line);

std::stringstream handle(const contents &code);

// Run the code
void runn_code(const contents &code, const std::optional<std::string> &filename);
#pragma once

#include <vector>
#include <string>
#include <filesystem>

struct contents
{
    std::vector<std::string> contents;
    u_int8_t length = 0;
};

contents cat_file(const std::filesystem::path &file_path);

void print_contents(const contents &contents);
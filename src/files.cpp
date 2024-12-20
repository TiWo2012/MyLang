#include "files.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

contents cat_file(const std::filesystem::path &file_path)
{
    contents content; // Initialize contents with empty vector and length 0

    if (!std::filesystem::exists(file_path))
    {
        std::cerr << "Error: File not found: " << file_path << std::endl;

        return content;
    }

    if (std::filesystem::is_empty(file_path))
    {
        std::cerr << "Error: File is empty: " << file_path << std::endl;

        return content;
    }

    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file: " << file_path << std::endl;

        return content;
    }

    {
        std::string line;
        int i = 0;

        while (std::getline(file, line))
        {
            content.contents.push_back(line);

            i++;
        }

        content.length = i;
    }

    file.close();

    return content;
}

void print_contents(const contents &contents)
{
    for (size_t i = 0; i < contents.length; i++)
    {
        std::cout << i + 1 << ". " << contents.contents[i] << std::endl;
    }
}
#include "main.hpp"
#include <optional>
#include <iostream>

#include "files.hpp"
#include "runn.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: No file provided\n";
        return 1;
    }

    contents file_content = cat_file(std::filesystem::path(argv[1]));
    std::optional<std::string> output_filename;
    bool print_flag = false;

    std::string Version = "Version 1.0";

    for (int i = 2; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "-p")
        {
            print_flag = true;
        }
        else if (arg == "-o" && i + 1 < argc)
        {
            output_filename = argv[++i]; // Get the next argument as the filename
        }
        else if (arg == "-v") {
            std::cout << Version << std::endl;
        }
        else
        {
            std::cerr << "Error: Unknown argument " << arg << "\n";
            return 1;
        }
    }

    if (print_flag)
    {
        print_contents(file_content);
    }

    runn_code(file_content, output_filename);
    return 0;
}

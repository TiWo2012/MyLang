#include "main.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Error: No file provided\n";

        return 1;
    }
    else if (argc < 3)
    {
        std::cout << "Warning: No arguments specified\n";
    }

    {

        contents file_content = cat_file(std::filesystem::path(argv[1]));

        if (std::string(argv[2]) == "--print")
        {
            print_contents(file_content);

            return 0;
        }
    }

    return 0;
}
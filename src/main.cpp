#include "main.hpp"

int main(int argc, char **argv) {
    std::cout << "welcome to MyLang Interpreter\n";

    if (argc < 2)
    {
        std::cout << "Error: No file provided\n";
    }

    contents file_content = cat_file(std::filesystem::path(argv[1]));

    return 0;
}
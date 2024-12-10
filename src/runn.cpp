#include "runn.hpp"
#include "files.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm> // For std::remove
#include <cctype>

std::stringstream init()
{
    std::stringstream output;
    output << "#!/bin/bash\n"; // Add the correct bash shebang line
    return output;
}

std::string trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");

    return (start == std::string::npos || end == std::string::npos)
               ? ""
               : str.substr(start, end - start + 1);
}

std::string remove_semi(const std::string &line)
{
    std::string result = line;
    result.erase(std::remove(result.begin(), result.end(), ';'), result.end()); // Remove all semicolons
    return result;
}

std::string remove_brace(const std::string &line)
{
    std::string result = line;
    result.erase(std::remove(result.begin(), result.end(), '('), result.end()); // Remove all opening braces
    result.erase(std::remove(result.begin(), result.end(), ')'), result.end()); // Remove all closing braces
    return result;
}

std::string handle_print(const std::string &line)
{
    std::string result = line;
    const std::string keyword = "print";
    size_t pos = result.find(keyword);

    if (pos != std::string::npos)
    {
        result.erase(pos, keyword.length()); // Remove "print"
        result = remove_brace(result);       // Remove braces
        result = remove_semi(result);        // Remove semicolons
        result = trim(result);               // Trim spaces from both ends
    }

    return result;
}

std::string handle_let(const std::string &line)
{
    std::string result = line;
    const std::string keyword = "let ";
    size_t pos = result.find(keyword);

    if (pos != std::string::npos)
    {
        result.erase(pos, keyword.length()); // Remove "let "
        result = remove_semi(result);        // Remove semicolons
        result = trim(result);               // Trim spaces from both ends

        // Remove spaces around '='
        size_t eq_pos = result.find('=');
        if (eq_pos != std::string::npos)
        {
            // Trim spaces before '='
            size_t start = eq_pos;
            while (start > 0 && std::isspace(result[start - 1]))
            {
                --start;
            }
            result.erase(start, eq_pos - start);

            // Trim spaces after '='
            eq_pos = result.find('='); // Recalculate after erasing
            size_t end = eq_pos + 1;
            while (end < result.length() && std::isspace(result[end]))
            {
                ++end;
            }
            result.erase(eq_pos + 1, end - (eq_pos + 1));
        }
    }

    return result;
}

std::string handle_return(const std::string &line)
{
    std::string result = line;
    const std::string keyword = "return ";
    size_t pos = result.find(keyword);

    if (pos != std::string::npos)
    {
        result.erase(pos, keyword.length()); // Remove "return "
        result = remove_semi(result);        // Remove semicolons
        result = trim(result);               // Trim spaces from both ends

        // Check if the result is a numeric value
        if (!result.empty() && std::all_of(result.begin(), result.end(), ::isdigit))
        {
            result = "exit " + result; // Direct numeric value
        }
        else
        {
            result = "exit $" + result; // Variable reference
        }
    }

    return result;
}

std::stringstream handle(const contents &code)
{
    std::stringstream output_new;

    for (size_t i = 0; i < code.length; ++i)
    {
        std::string line = code.contents[i];
        std::string others;

        if (line.find("let ") != std::string::npos)
        {
            line = handle_let(line);
        }
        else if (line.find("return ") != std::string::npos)
        {
            line = handle_return(line);
        }
        else if (line.find("print") != std::string::npos)
        {
            others = handle_print(line);

            {
                std::stringstream ss;
                ss << "echo -e " << others;
                line = ss.str();
            }
        }

        output_new << line << std::endl;
    }

    return output_new;
}

void runn_code(const contents &code, const std::optional<std::string> &filename)
{
    // Initialize the script output
    std::stringstream output = init();

    // Process the code and append it
    output << handle(code).str();

    // Determine output filename
    std::string output_filename = filename.value_or("out");

    // Write the output to a file
    std::ofstream File(output_filename);
    if (File.is_open())
    {
        File << output.str();
        File.close();
    }
    else
    {
        std::cerr << "Error: Unable to write to file: " << output_filename << std::endl;
    }
}
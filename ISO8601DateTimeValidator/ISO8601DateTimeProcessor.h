#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "../ISO8601DateTimeValidatorLib/isodatetime_validator.h"
#include <regex>

class ISO8601DateTimeProcessor
{
public:
    static bool processDateTime(const std::string& input_file, const std::string& output_file) {
        std::vector<std::string> unique_datetimes;

        if (!readDateTimeValues(input_file, unique_datetimes)) {
            std::cerr << "Error: Unable to process date-time values." << std::endl;
            return false;
        }

        if (!writeUniqueDateTimeValues(output_file, unique_datetimes)) {
            std::cerr << "Error: Unable to write unique date-time values." << std::endl;
            return false;
        }

        std::cout << "Unique valid date-time values have been written to " << output_file << std::endl;
        return true;
    }

    static bool isDateTimeValid(const std::string& dt_str)
    {
        return is_valid_iso8601_datetime(dt_str.c_str());
    }
private:
    static bool readDateTimeValues(const std::string& input_file, std::vector<std::string>& unique_datetimes)
    {
        std::ifstream input_stream(input_file);
        if (!input_stream.is_open()) {
            std::cerr << "Error: Unable to open input file." << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(input_stream, line)) {
            // Check if datetime string is valid and not duplicate
            if (isDateTimeValid(line) && isDateTimeUnique(line, unique_datetimes)) {
                unique_datetimes.emplace_back(line);
            }
        }
        input_stream.close();
        return true;
    }

    static bool writeUniqueDateTimeValues(const std::string& output_file, const std::vector<std::string>& unique_datetimes)
    {
        std::ofstream output_stream(output_file);
        if (!output_stream.is_open()) {
            std::cerr << "Error: Unable to open output file." << std::endl;
            return false;
        }

        for (const auto& dt_str : unique_datetimes) {
            output_stream << dt_str << std::endl;
        }
        output_stream.close();
        return true;
    }

    static bool isDateTimeUnique(const std::string& line, const std::vector<std::string>& unique_datetimes)
    {
        return std::find(unique_datetimes.begin(), unique_datetimes.end(), line) == unique_datetimes.end();
    }

    // This function is useful for extracting datetime patterns from a file containing a mixture of text messages 
    // and datetime strings.
    // Parameters:
    // - line: A string representing a message read from the file.
    // Returns:
    // - A string containing the datetime pattern if a match is found; otherwise, an empty string.
    static std::string getDateTimeRegexPattern(const std::string& line)
    {
        std::regex pattern("\\d{4}-\\d{2}-\\d{2}T\\d{2}:\\d{2}:\\d{2}(Z|\\+\\d{2}:\\d{2}|\\-\\d{2}:\\d{2})");
        
        std::smatch match;

        if (std::regex_search(line, match, pattern))
        {
            if (!match.empty())
            {
                return match[0]; 
            }
        }
        return "";
    }
};
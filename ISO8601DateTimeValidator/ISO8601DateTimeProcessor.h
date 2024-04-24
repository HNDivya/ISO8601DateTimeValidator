#include <string>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <regex>
#include "../ISO8601DateTimeValidatorLib/isodatetime_validator.h"

class ISO8601DateTimeProcessor
{
public:
    static bool processDateTime(const std::string& input_file, const std::string& output_file) {
        std::unordered_set<std::string> unique_datetimes;

        if (!readDateTimeValues(input_file, unique_datetimes)) {
            return false; // Unable to read input file
        }

        if (!writeUniqueDateTimeValues(output_file, unique_datetimes)) {
            return false; // Unable to write output file
        }

        std::cout << "Unique valid date-time values have been written to " << output_file << std::endl;
        return true;
    }

    static bool isDateTimeValid(const std::string& dt_str)
    {
        return is_valid_iso8601_datetime(dt_str.c_str());
    }
private:
    static bool readDateTimeValues(const std::string& input_file, std::unordered_set<std::string>& unique_datetimes)
    {
        std::ifstream input_stream(input_file);
        if (!input_stream.is_open()) {
            std::cerr << "Error: Unable to open input file." << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(input_stream, line)) {
            if (isDateTimeValid(line)) {
                if (isDateTimeUnique(line, unique_datetimes))
                {
                    unique_datetimes.insert(line);
                }
            }
        }

        input_stream.close();
        return true;
    }

    static bool writeUniqueDateTimeValues(const std::string& output_file, const std::unordered_set<std::string>& unique_datetimes)
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

    static bool isDateTimeUnique(const std::string& line, const std::unordered_set<std::string>& unique_datetimes)
    {
        return unique_datetimes.find(line) == unique_datetimes.end();
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


#include <string>
#include <chrono>
#include "ISO8601DateTimeProcessor.h"

std::string generateOutputFileName() 
{
    /*  generated_mixed_iso8601_datetime_10000.txt
        generated_mixed_text_message_datetime.txt
        generated_iso8601_datetime.txt
        generated_iso8601_datetime_10000.txt
        generated_iso8601_datetime_1000000
    */
    std::string input_file = "test//generated_iso8601_datetime_1000000.txt";

    // store the output file in the format unique_datetimes_output_year_month_day
    auto now = std::chrono::system_clock::now();
    auto ymd = std::chrono::year_month_day{ std::chrono::floor<std::chrono::days>(now) };

    std::string year = std::to_string(static_cast<int>(ymd.year()));
    std::string month = std::to_string(static_cast<unsigned>(ymd.month()));
    std::string day = std::to_string(static_cast<unsigned>(ymd.day()));

    // Get the current time
    auto tp = std::chrono::floor<std::chrono::seconds>(now);
    auto dp = std::chrono::time_point_cast<std::chrono::days>(tp);
    auto h = std::chrono::duration_cast<std::chrono::hours>(tp - dp);
    auto m = std::chrono::duration_cast<std::chrono::minutes>(tp - dp - h);
    auto s = std::chrono::duration_cast<std::chrono::seconds>(tp - dp - h - m);

    // Convert time components to strings
    std::string hour = std::to_string(h.count());
    std::string minute = std::to_string(m.count());
    std::string second = std::to_string(s.count());

    // Ensure that hour, minute, and second strings are always two digits
    hour = std::string(2 - hour.length(), '0') + hour;
    minute = std::string(2 - minute.length(), '0') + minute;
    second = std::string(2 - second.length(), '0') + second;

    std::string output_file = "log//unique_datetimes_output_" + year + "_" + month + "_" + day + "_" +
        hour + "_" + minute + "_" + second + ".txt";

    return output_file;
}

int main() 
{
    std::string input_file = "test//generated_iso8601_datetime_1000000.txt";
    std::string output_file = generateOutputFileName();

    auto startTime = std::chrono::steady_clock::now();

    if (!ISO8601DateTimeProcessor::processDateTime(input_file, output_file)) {
        std::cerr << "Error processing date-time values." << std::endl;
        return 1;
    }

    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Execution Time (ms): " << duration.count() << std::endl;

    return 0;
}

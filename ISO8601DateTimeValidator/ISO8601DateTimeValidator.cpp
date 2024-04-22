#include <string>
#include "ISO8601DateTimeProcessor.h"

int main()
{
    std::string input_file = "test//generated_iso8601_datetime.txt";
    std::string output_file = "unique_datetimes_output.txt";

    ISO8601DateTimeProcessor::processDateTime(input_file, output_file);

    return 0;
}

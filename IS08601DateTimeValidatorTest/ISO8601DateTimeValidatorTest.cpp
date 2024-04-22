#include "pch.h"
#include "../ISO8601DateTimeValidator/ISO8601DateTimeProcessor.h"

// Test case to validate valid ISO 8601 date-time formats
TEST(ISO8601ValidationTest, ValidISO8601DateTime) {
    EXPECT_TRUE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:56Z"));
    EXPECT_TRUE(ISO8601DateTimeProcessor::isDateTimeValid("2021-10-21T12:34:56+00:00"));
    EXPECT_TRUE(ISO8601DateTimeProcessor::isDateTimeValid("1984-11-21T12:34:56-00:00"));
    EXPECT_TRUE(ISO8601DateTimeProcessor::isDateTimeValid("1994-07-21T23:59:59Z"));
    EXPECT_TRUE(ISO8601DateTimeProcessor::isDateTimeValid("2004-08-21T23:59:59+19:00"));
    EXPECT_TRUE(ISO8601DateTimeProcessor::isDateTimeValid("9999-12-21T23:59:59-23:59"));
}

TEST(ISO8601ValidationTest, InvalidISO8601DateTime) {
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-41T12:34:56-05:00"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("0000-00-00T00:00:00-00:00"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("9999-99-99T99:99:99-99:99"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:56+99:99"));
}

TEST(ISO8601ValidationTest, InvalidSeparator) {
    // Invalid separator: Should contain hyphens and colons
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024/04/21T12:34:56Z"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12-34-56Z"));
}

TEST(ISO8601ValidationTest, InvalidYearFormat) {
    // Invalid year format: Should have 4 digits
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2-04-21T12:34:56Z"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("24-04-21T12:34:56Z"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("20244-04-21T12:34:56Z"));
}

TEST(ISO8601ValidationTest, InvalidMonth) {
    // Invalid month: Should be within range 01-12
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-13-21T12:34:56Z"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-00-21T12:34:56Z"));
}

TEST(ISO8601ValidationTest, InvalidDay) {
    // Invalid day: Should be within range 01-31 based on month
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-32T12:34:56Z"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-02-30T12:34:56Z")); // February, not a leap year
}

TEST(ISO8601ValidationTest, InvalidHour) {
    // Invalid hour: Should be within range 00-23
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T25:34:56Z"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:60:56Z"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T24:07:09Z"));
}

TEST(ISO8601ValidationTest, InvalidMinute) {
    // Invalid minute: Should be within range 00-59
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:60Z"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:Z")); 
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T23:60:09Z"));
}

TEST(ISO8601ValidationTest, InvalidSecond) {
    // Invalid second: Should be within range 00-59
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:56±05:00"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:56:Z")); 
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T23:07:60Z"));
}

TEST(ISO8601ValidationTest, InvalidHourOffset) {
    // Invalid hour: Should be within range 00-23
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T25:34:56+24:03"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:60:56-91:23"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T24:07:09Z-100:43"));
}

TEST(ISO8601ValidationTest, InvalidMinuteOffset) {
    // Invalid minute: Should be within range 00-59
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:60+12:60"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:12-11:123"));
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T23:60:09+24:60"));
}

TEST(ISO8601ValidationTest, InvalidTimezoneDesignator) {
    // Invalid timezone designator: Should be 'Z' for UTC or ±hh:mm for offset
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:56±0500")); // Missing colon in timezone offset
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:56+05:00Z")); // Conflicting timezone designators
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:56Z05:00")); // timezone offset is present when 'Z' is used
}

TEST(ISO8601ValidationTest, InvalidLength) {
    // Invalid length: Should be between 20 and 25 characters
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:56Z000")); // Too long
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T12:34:Z"));     // Too short
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21T"));     
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04"));     
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024-04-21Z"));     
    EXPECT_FALSE(ISO8601DateTimeProcessor::isDateTimeValid("2024"));     
}

TEST(ISO8601ValidationTest, ReadValidDateTimeSetContaining10000Records) {
    unsigned int expectedRecords = 10000;
    std::ifstream input_stream("test_inputs\\generated_iso8601_datetime_10000.txt");
    ASSERT_TRUE(input_stream.is_open()) << "Failed to open generated_iso8601_datetime_10000.txt";

    std::string line;
    unsigned int actualRecords = 0;
    while (std::getline(input_stream, line)) {
        actualRecords++;
        EXPECT_TRUE(ISO8601DateTimeProcessor::isDateTimeValid(line)) << "Invalid date time format found at line:" << actualRecords;
    }
   
    EXPECT_EQ(expectedRecords, actualRecords) << "Failed to parse all 10000 date time strings from file.";
    input_stream.close();
}

TEST(ISO8601ValidationTest, ReadInValidDateTimeSetContaining2901Records) {
    unsigned int expectedInvalidRecords = 2901;
    std::ifstream input_stream("test_inputs\\generated_mixed_iso8601_datetime_10000_invalid_2901.txt");
    ASSERT_TRUE(input_stream.is_open()) << "Failed to open generated_mixed_iso8601_datetime_10000_invalid_2901.txt";

    std::string line;
    unsigned int actualInvalidRecords = 0;
    while (std::getline(input_stream, line)) {
        if (!ISO8601DateTimeProcessor::isDateTimeValid(line))
        {
            actualInvalidRecords++;
        }
    }
    
    EXPECT_EQ(expectedInvalidRecords, actualInvalidRecords) << "Failed to parse all invalid 2901 date time strings from file.";
    input_stream.close();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
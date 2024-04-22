#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "isodatetime_validator.h"

static bool is_valid_separator(const char* datetime_str)
{
    // Extended Format
    // Date and Time in UTC YYYY-MM-DDTHH:MM:DDZ
    // Date and Time in with the offset YYYY-MM-DDThh:mm:ss±hh:mm

    // Separators
    // character [T] - used as time designator.
    // hyphen [-] - used as separators within date.
    // colon [:] - used as separators within time.

    // Check the position of separators.
    if (datetime_str[4] != '-' || datetime_str[7] != '-' ||
        datetime_str[10] != 'T' ||
        datetime_str[13] != ':' || datetime_str[16] != ':') {
        return false;
    }
    return true;

    // TO-DO: ISO 8601 uses comma [,] to represent the deciaml fractions. Consider adding them.
}

static bool is_valid_digit(const char* datetime_str, int start, int end) {
    // Check if each component is a digit
    for (int i = start; i <= end; i++) {
        if (!isdigit(datetime_str[i])) {
            return false;
        }
    }
    return true;
}

static bool is_valid_time_zone_designator(const char* datetime_str) {
    // Check timezone designator
    // In UTC Z
    // With offset ±hh:mm

    char tzd = (strlen(datetime_str) == 20) ? datetime_str[strlen(datetime_str) - 1] :
        datetime_str[strlen(datetime_str) - 6];
    if (tzd != 'Z' && tzd != '+' && tzd != '-') {
        return false;
    }

    // Check timezone offset format.
    if (tzd != 'Z') {
        if (!isdigit(datetime_str[strlen(datetime_str) - 5]) || !isdigit(datetime_str[strlen(datetime_str) - 4]) ||
            datetime_str[strlen(datetime_str) - 3] != ':' || !isdigit(datetime_str[strlen(datetime_str) - 2]) ||
            !isdigit(datetime_str[strlen(datetime_str) - 1])) {
            return false;
        }
    }
   
    // Check if the timezone offset is not present when 'Z' is used
    // YYYY-MM-DDTHH:MM:SSZHH:MM - Invalid
    if (tzd == 'Z' && strlen(datetime_str) > 20) {
        return false;
    }

    return true;
}

static bool is_leap_year(const int year)
{
    return (year % 4 == 0 && year % 100 != 0) && (year % 400 == 0);
}

static bool is_valid_date(const char* datetime_str)
{
    // Year: 0000-9999
    // Month: 1-12
    // Day: 1-31 (varies with month).
    int year = atoi(datetime_str);
    int month = atoi(datetime_str + 5);
    int day = atoi(datetime_str + 8);

    // check If month is between 1 to 12.
    if (month < 1 || month > 12) return false;

    // check valid day.
    if (day < 1) return false;

    switch (month)
    {
    case 2:
        if (is_leap_year(year))
        {
            if (day > 29) return false;
        }
        else
        {
            if (day > 28) return false;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (day > 30) return false;
        break;
    default:
        if (day > 31) return false;
        break;
    }
    return true;
}

static bool is_valid_time(const char* datetime_str)
{
    int hour = atoi(datetime_str + 11);
    int minute = atoi(datetime_str + 14);
    int second = atoi(datetime_str + 17);

    if (hour < 0 || hour > 23
        || minute < 0 || minute > 59
        || second < 0 || second > 59)
    {
        return false;
    }
    return true;
}

static bool is_valid_time_offset(const char* datetime_str)
{
    //YYYY - MM - DDThh:mm:ss±hh:mm
    if (strlen(datetime_str) > 20)
    {
        int hour = atoi(datetime_str + 20);
        int minute = atoi(datetime_str + 23);

        if (hour < 0 || hour > 23
            || minute < 0 || minute > 59)
        {
            return false;
        }
    }
    return true;
}

// Function to validate the extended format of date-time string in ISO 8601.
bool is_valid_iso8601_datetime(const char* datetime_str) {
    if (strlen(datetime_str) < 20 || strlen(datetime_str) > 25) {
        return false;
    }

    if (!is_valid_separator(datetime_str)) {
        return false;
    }

    if (!is_valid_digit(datetime_str, 0, 3) || // Year
        !is_valid_digit(datetime_str, 5, 6) || // Month
        !is_valid_digit(datetime_str, 8, 9) || // Day
        !is_valid_digit(datetime_str, 11, 12) || // Hour
        !is_valid_digit(datetime_str, 14, 15) || // Minute
        !is_valid_digit(datetime_str, 17, 18)) { // Second
        return false;
    }

    if (!is_valid_time_zone_designator(datetime_str)) {
        return false;
    }

    if (!is_valid_date(datetime_str)) {
        return false;
    }

    if (!is_valid_time(datetime_str)) {
        return false;
    }

    if (!is_valid_time_offset(datetime_str)) {
        return false;
    }
    return true;
}


// TO-DO: Implement this API to support the validation of basic ISO8601 date time format.
bool is_valid_basic_iso8601_datetime_format(const char* dateTime)
{
    return false;
}

// TO-DO: Implement this API to support the validation of ISO8601 date time interval.
bool is_valid_iso8601_datetime_interval(const char* dateTime)
{
    return false;
}

// TO-DO: Implement this API to support the validation of ISO8601 recurring date time interval.
bool is_valid_iso8601_recurring_time_interval(const char* dateTime)
{
    return false;
}

// TO-DO: Implement this API to support the validation of expanded ISO8601 date time format.
bool is_valid_expanded_iso8601_datetime(const char* dateTime)
{
    return false;
}
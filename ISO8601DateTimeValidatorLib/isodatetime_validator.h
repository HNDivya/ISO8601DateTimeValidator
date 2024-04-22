#pragma once
#ifndef ISODATETIME_VALIDATOR
#define ISODATETIME_VALIDATOR

#define MAX_DATETIME_LENGTH 25 

#ifdef __cplusplus
extern "C" {
#endif
	// API used to validate extended format of ISO8601 date time. 
	// Extended Format
	// Date and Time in UTC YYYY-MM-DDTHH:MM:DDZ
	// Date and Time in with the offset YYYY-MM-DDThh:mm:ss±hh:mm
	bool is_valid_iso8601_datetime(const char* dateTime);

	/* TODO: Add functionality to include
	 ****************************************************************************************************************
	 * Date formats:
	 * Basic format     Extended format     Explanation
	 * YYYYMMDD         YYYY-MM-DD          Complete calendar date
	 * ±YYYYYYDDD       ±YYYYYY-DDD         Expanded ordinal date with two digits added
	 * YYYYWww          YYYY-Www            Week date with precision reduced to week
	 ****************************************************************************************************************
	 * Time of day formats:
	 * Basic format     Extended format     Explanation
	 * hhmmss           hh:mm:ss            Complete local time - DONE
	 * hhmm,mZ          hh:mm,mZ            Reduced precision UTC of day with one digit decimal fraction for minutes
	 * hhmm±hhmm        hh:mm±hh:mm         Local time and the difference from UTC — reduced accuracy
	 ****************************************************************************************************************
	 * Date and time of day formats:
	 * Basic format       Extended format       Explanation
	 * YYYYDDDThhmm       YYYY-DDDThh-mm        Complete ordinal date — reduced precision time of day
	 * YYYYMMDDhhmm,m     YYYY-MM-DDhh:mm,m     Complete calendar date — reduced precision time of day with one digit decimal fraction for minute — no time designator
	 * YYYYWwwDThh,hhZ    YYYY-Www-DThh,hhZ     Complete week date — reduced precision UTC of day with two digit decimal fraction for the hour
	 ****************************************************************************************************************
	 */
	bool is_valid_expanded_iso8601_datetime(const char* dateTime);

	// TODO: API used to validate basic format of ISO8601 date time. 
	// Extended Format
	// Date and Time in UTC YYYYMMDDTHHMMDDZ
	// Date and Time in with the offset YYYYMMDDThhmmss±hhmm
	bool is_valid_basic_iso8601_datetime_format(const char* dateTime);

	// TODO: API to implement time interval representation.
	/*
	 ****************************************************************************************************************
	 * Basic format          Extended format
	 * YYYYMMDDThhmm,mZ      YYYY-MM-DDThh:mm,mZ
	 *                       YYYYMMDDThhmm,m
	 *                       YYYY-MM-DDThh:mm,m
	 ****************************************************************************************************************
	 * Basic format			 Extended format
	 * PnnnD				 N/A
	 ****************************************************************************************************************
	 * Basic format			 Extended format
	 * PTnn,nnH				 N/A
	 ****************************************************************************************************************	 
	 */
	bool is_valid_iso8601_datetime_interval(const char* dateTime);

	// TODO: API to implement Recurring time interval representation.
	/*
	 ****************************************************************************************************************
	 * Basic format					Extended format
	 * Rn/YYYYWww/YYYYWww			Rn/YYYY-Www/YYYY-Www
	 ****************************************************************************************************************
	 * Basic format							Extended format
	 * Rn/YYYYDDD/PnnDRn/YYYY-DDD/PnnD		Rn/YYYY-DDD/PnnD
	 ****************************************************************************************************************
	*/
	bool is_valid_iso8601_recurring_time_interval(const char* dateTime);

#ifdef __cplusplus
}
#endif

#endif 
/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_date_time.h#2 $ */ 
/* $DateTime: 2006/04/12 14:23:04 $ */
/* $Change: 216157 $ */
/* $Author: stern $ */

/** \file
 * Functions and classes for working with dates and times in DNG files.
 */

/*****************************************************************************/

#ifndef __dng_date_time__
#define __dng_date_time__

/*****************************************************************************/

#include "dng_types.h"

/*****************************************************************************/

/// \brief Class for holding a date/time and converting to and from relevant date/time formats

class dng_date_time
	{
	
	public:
		
		uint32 fYear;
		uint32 fMonth;
		uint32 fDay;
		uint32 fHour;
		uint32 fMinute;
		uint32 fSecond;
		
	public:
	
		/// Construct an invalid date/time

		dng_date_time ();

		/// Construct a date/time with specific values.
		/// \param year Year to use as actual integer value, such as 2006.
		/// \param month Month to use from 1 - 12, where 1 is January.
		/// \param day Day of month to use from 1 -31, where 1 is the first.
		/// \param hour Hour of day to use from 0 - 23, where 0 is midnight.
		/// \param minute Minute of hour to use from 0 - 59.
		/// \param second Second of minute to use from 0 - 59.

		dng_date_time (uint32 year,
					   uint32 month,
					   uint32 day,
					   uint32 hour,
					   uint32 minute,
					   uint32 second);

		/// Predicate to determine if a date is valid.
		/// \retval true if all fields are within range.

		bool IsValid () const;
		
		/// Predicate to determine if a date is invalid.
		/// \retval true if any field is out of range.

		bool NotValid () const
			{
			return !IsValid ();
			}

		/// Set date to an invalid value.

		void Clear ();

		/// Parse an EXIF format date string.
		/// \param s Input date string to parse.
		/// \retval true if date was parsed successfully and date is valid.

		bool Parse (const char *s);
			
	};
	
/*****************************************************************************/

/// Get the current date/time and timezone.
/// \param dt Receives current data/time
/// \param zone Seconds from GMT of current timezone.

void CurrentDateTimeAndZone (dng_date_time &dt, int32 &zone);

/*****************************************************************************/

/// Convert UNIX "seconds since Jan 1, 1970" time to a dng_date_time

void DecodeUnixTime (uint32 unixTime, dng_date_time &dt);

/*****************************************************************************/

/// Return timezone of current location at a given date.
/// \param dt Date at which to compute timezone difference. (For example, used to determine Daylight Savings, etc.)
/// \retval Number of seconds difference between local time zone and GMT at date/time dt.

int32 LocalTimeZone (const dng_date_time &dt);

/*****************************************************************************/

/// Tag to encode date represenation format
enum dng_date_time_format
	{
	dng_date_time_format_unknown            = 0, /// Date format not known
	dng_date_time_format_exif               = 1, /// EXIF date string
	dng_date_time_format_unix_little_endian = 2, /// 32-bit UNIX time as 4-byte little endian
	dng_date_time_format_unix_big_endian    = 3  /// 32-bit UNIX time as 4-byte big endian
	};

/*****************************************************************************/

/// \brief Store file offset from which date was read.
///
/// Used internally by Adobe to update date in original file.
/// \warning Use at your own risk.

class dng_date_time_storage_info
	{
	
	private:
	
		uint32 fOffset;
		
		dng_date_time_format fFormat;
	
	public:
	
		/// The default constructor initializes to an invalid state.

		dng_date_time_storage_info ();
		
		/// Construct with file offset and date format.

		dng_date_time_storage_info (uint32 offset,
									dng_date_time_format format);
		

		/// Predicate to determine if an offset is valid.
		/// \retval true if offset is valid.

		bool IsValid () const;
		
		// The accessors throw if the data is not valid.

		/// Getter for offset in file.
		/// \exception dng_exception with fErrorCode equal to dng_error_unknown if offset is not valid.

		uint32 Offset () const;
			
		/// Get for format date was originally stored in file. Throws a dng_error_unknown exception if offset is invalid.
		/// \exception dng_exception with fErrorCode equal to dng_error_unknown if offset is not valid.

		dng_date_time_format Format () const;
	
	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/

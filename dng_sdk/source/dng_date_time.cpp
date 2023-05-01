/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_date_time.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#include "dng_date_time.h"

#include "dng_exceptions.h"
#include "dng_mutex.h"
#include "dng_stream.h"
#include "dng_utils.h"

#include <time.h>

#if qMacOS
#ifdef __MWERKS__
#include <CFTimeZone.h>
#else
#include <CoreServices/CoreServices.h>
#endif
#endif

#if qWinOS
#include <windows.h>
#endif

/******************************************************************************/

dng_date_time::dng_date_time ()

	:	fYear   (0)
	,	fMonth  (0)
	,	fDay    (0)
	,	fHour   (0)
	,	fMinute (0)
	,	fSecond (0)
	
	{
	
	}

/******************************************************************************/

dng_date_time::dng_date_time (uint32 year,
					  		  uint32 month,
					  		  uint32 day,
					  		  uint32 hour,
					  		  uint32 minute,
					  		  uint32 second)

	:	fYear   (year)
	,	fMonth  (month)
	,	fDay    (day)
	,	fHour   (hour)
	,	fMinute (minute)
	,	fSecond (second)
	
	{

	}

/******************************************************************************/

bool dng_date_time::IsValid () const
	{
	
	return fYear   >= 1 && fYear   <= 9999 &&
		   fMonth  >= 1 && fMonth  <= 12   &&
		   fDay    >= 1 && fDay    <= 31   &&
		   fHour   >= 0 && fHour   <= 23   &&
		   fMinute >= 0 && fMinute <= 59   &&
		   fSecond >= 0 && fSecond <= 59;
	
	}
			
/*****************************************************************************/

void dng_date_time::Clear ()
	{
	
	*this = dng_date_time ();
	
	}
			
/*****************************************************************************/

static uint32 DateTimeParseU32 (const char *&s)
	{
	
	uint32 x = 0;
	
	while (*s == ' ' || *s == ':')
		s++;
		
	while (*s >= '0' && *s <= '9')
		{
		x = x * 10 + (uint32) (*(s++) - '0');
		}
		
	return x;
	
	}
			
/*****************************************************************************/

bool dng_date_time::Parse (const char *s)
	{
	
	fYear   = DateTimeParseU32 (s);
	fMonth  = DateTimeParseU32 (s);
	fDay    = DateTimeParseU32 (s);
	fHour   = DateTimeParseU32 (s);
	fMinute = DateTimeParseU32 (s);
	fSecond = DateTimeParseU32 (s);
	
	return IsValid ();
	
	}
			
/*****************************************************************************/

static dng_mutex gDateTimeMutex;

/*****************************************************************************/

void CurrentDateTimeAndZone (dng_date_time &dt, int32 &zone)
	{
	
	time_t sec;
	
	time (&sec);
	
	tm t;
	tm zt;
	
		{
		
		dng_lock_mutex lock (&gDateTimeMutex);
		
		t  = *localtime (&sec);
		zt = *gmtime    (&sec);
		
		}
		
	dt.fYear   = t.tm_year + 1900;
	dt.fMonth  = t.tm_mon + 1;
	dt.fDay    = t.tm_mday;
	dt.fHour   = t.tm_hour;
	dt.fMinute = t.tm_min;
	dt.fSecond = t.tm_sec;
	
	zone = t.tm_hour - zt.tm_hour;
	
	bool zonePositive = (t.tm_year >  zt.tm_year) ||
						(t.tm_year == zt.tm_year && t.tm_yday >  zt.tm_yday) ||
						(t.tm_year == zt.tm_year && t.tm_yday == zt.tm_yday && zone >= 0);
						
	if (zonePositive)
		{
		
		while (zone < 0)
			zone += 24;
			
		}
		
	else
		{
		
		while (zone > 0)
			zone -= 24;
		
		}
	
	}

/*****************************************************************************/

void DecodeUnixTime (uint32 unixTime, dng_date_time &dt)
	{
	
	time_t sec = (time_t) unixTime;
	
	tm t;
	
		{
		
		dng_lock_mutex lock (&gDateTimeMutex);
		
		#if qMacOS && !defined(__MACH__)
		
		// Macintosh CFM stores time in local time zone.

		tm *tp = localtime (&sec);
		
		#else
		
		// Macintosh Mach-O and Windows stores time in Zulu time.
		
		tm *tp = gmtime (&sec);
		
		#endif
		
		if (!tp)
			{
			dt.Clear ();
			return;
			}
			
		t = *tp;
		
		}
	
	dt.fYear   = t.tm_year + 1900;
	dt.fMonth  = t.tm_mon + 1;
	dt.fDay    = t.tm_mday;
	dt.fHour   = t.tm_hour;
	dt.fMinute = t.tm_min;
	dt.fSecond = t.tm_sec;

	}

/*****************************************************************************/

int32 LocalTimeZone (const dng_date_time &dt)
	{
	
	if (dt.IsValid ())
		{
		
		#if qMacOS
		
		CFTimeZoneRef zoneRef = CFTimeZoneCopyDefault ();
		
		if (zoneRef)
			{
			
			CFGregorianDate gregDate;

			gregDate.year   = dt.fYear;
			gregDate.month  = dt.fMonth;
			gregDate.day    = dt.fDay;
			gregDate.hour   = dt.fHour;
			gregDate.minute = dt.fMinute;
			gregDate.second = dt.fSecond;
			
			CFAbsoluteTime absTime = CFGregorianDateGetAbsoluteTime (gregDate, zoneRef);
			
			CFTimeInterval secondsDelta = CFTimeZoneGetSecondsFromGMT (zoneRef, absTime);
		
			CFRelease (zoneRef);
			
			int32 zone = Round_int32 (secondsDelta * (1.0 / (60.0 * 60.0)));
			
			if (zone >= -13 && zone <= 13)
				{
				return zone;
				}

			}
		
		#endif
		
		#if qWinOS
		
		if (GetTimeZoneInformation          != NULL &&
			SystemTimeToTzSpecificLocalTime != NULL &&
		    SystemTimeToFileTime            != NULL)
			{
			
			TIME_ZONE_INFORMATION tzInfo;
			
			DWORD x = GetTimeZoneInformation (&tzInfo);
			
			SYSTEMTIME localST;
			
			memset (&localST, 0, sizeof (localST));

			localST.wYear   = (WORD) dt.fYear;
			localST.wMonth  = (WORD) dt.fMonth;
			localST.wDay    = (WORD) dt.fDay;
			localST.wHour   = (WORD) dt.fHour;
			localST.wMinute = (WORD) dt.fMinute;
			localST.wSecond = (WORD) dt.fSecond;
			
			SYSTEMTIME utcST;

			// Kludge: We really want TzSpecificLocalTimeToSystemTime, but that is
			// an XP only function. So we use SystemTimeToTzSpecificLocalTime instead
			// and then negative the result.  This does not handle the edge cases (the hours
			// near the daylight/standard time switchover), but it does work on Windows
			// 2000.
			
			if (SystemTimeToTzSpecificLocalTime (&tzInfo, &localST, &utcST))
				{
				
				FILETIME localFT;
				FILETIME utcFT;
				
				(void) SystemTimeToFileTime (&localST, &localFT);
				(void) SystemTimeToFileTime (&utcST  , &utcFT  );
				
				uint64 time1 = (((uint64) localFT.dwHighDateTime) << 32) + localFT.dwLowDateTime;
				uint64 time2 = (((uint64) utcFT  .dwHighDateTime) << 32) + utcFT  .dwLowDateTime;
				
				// FILETIMEs are in units to 100 ns.  Convert to seconds.
				
				int64 time1Sec = time1 / 10000000;
				int64 time2Sec = time2 / 10000000;
			
				int32 delta = (int32) (time1Sec - time2Sec);

				delta = -delta;		// Kludge: Used wrong API because correct API is XP only.
				
				int32 zone;
				
				if (delta >= 0)
					zone = (delta + 1800) / 3600;
				else
					zone = (delta - 1800) / 3600;
					
				if (zone >= -13 && zone <= 13)
					{
					return zone;
					}
			
				}
			
			}
		
		#endif
		
		}
	
	// Figure out local time zone.
	
	dng_date_time current_dt;
	int32         current_zone;
	
	CurrentDateTimeAndZone (current_dt, current_zone);
		
	return current_zone;
			
	}

/*****************************************************************************/

dng_date_time_storage_info::dng_date_time_storage_info ()

	:	fOffset	(dng_stream::kInvalidOffset  )
	,	fFormat	(dng_date_time_format_unknown)
	
	{
	
	}

/*****************************************************************************/

dng_date_time_storage_info::dng_date_time_storage_info (uint32 offset,
														dng_date_time_format format)
			
	:	fOffset	(offset)
	,	fFormat	(format)
	
	{
	
	}

/*****************************************************************************/

bool dng_date_time_storage_info::IsValid () const
	{
	
	return fOffset != dng_stream::kInvalidOffset;
	
	}

/*****************************************************************************/

uint32 dng_date_time_storage_info::Offset () const
	{
	
	if (!IsValid ())
		ThrowProgramError ();
		
	return fOffset;
	
	}

/*****************************************************************************/

dng_date_time_format dng_date_time_storage_info::Format () const
	{
	
	if (!IsValid ())
		ThrowProgramError ();
		
	return fFormat;
	
	}

/*****************************************************************************/

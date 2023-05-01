/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_utils.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#ifndef __dng_utils__
#define __dng_utils__

/*****************************************************************************/

#include "dng_flags.h"
#include "dng_types.h"

/*****************************************************************************/

inline uint32 Abs_int32 (int32 x)
	{
	
	#if 0
	
	// Reference version.
	
	return (uint32) (x < 0 ? -x : x);
	
	#else
	
	// Branchless version.
	
    uint32 mask = x >> 31;
    
    return (uint32) ((x + mask) ^ mask);
    
	#endif
	
	}

inline int32 Min_int32 (int32 x, int32 y)
	{
	
	return (x <= y ? x : y);
	
	}

inline int32 Max_int32 (int32 x, int32 y)
	{
	
	return (x >= y ? x : y);
	
	}

inline int32 Pin_int32 (int32 min, int32 x, int32 max)
	{
	
	return Max_int32 (min, Min_int32 (x, max));
	
	}

/*****************************************************************************/

inline int16 Pin_int16 (int32 x)
	{
	
	x = Pin_int32 (-32768, x, 32767);
	
	return (int16) x;
	
	}
	
/*****************************************************************************/

inline uint32 Min_uint32 (uint32 x, uint32 y)
	{
	
	return (x <= y ? x : y);
	
	}

inline uint32 Max_uint32 (uint32 x, uint32 y)
	{
	
	return (x >= y ? x : y);
	
	}
	
inline uint32 Pin_uint32 (uint32 min, uint32 x, uint32 max)
	{
	
	return Max_uint32 (min, Min_uint32 (x, max));
	
	}

/*****************************************************************************/

inline uint16 Pin_uint16 (int32 x)
	{
	
	#if 0
	
	// Reference version.
	
	x = Pin_int32 (0, x, 0x0FFFF);
	
	#else
	
	// Single branch version.
	
	if (x & ~65535)
		{
		
		x = ~x >> 31;
		
		}
		
	#endif
		
	return (uint16) x;
	
	}

/*****************************************************************************/

inline uint32 RoundUp2 (uint32 x)
	{
	
	return (x + 1) & ~1;
	
	}

inline uint32 RoundUp4 (uint32 x)
	{
	
	return (x + 3) & ~3;
	
	}

inline uint32 RoundUp8 (uint32 x)
	{
	
	return (x + 7) & ~7;
	
	}

inline uint32 RoundUp16 (uint32 x)
	{
	
	return (x + 15) & ~15;
	
	}

/*****************************************************************************/

inline real32 Abs_real32 (real32 x)
	{
	
	return (x < 0.0f ? -x : x);
	
	}

inline real32 Min_real32 (real32 x, real32 y)
	{
	
	return (x < y ? x : y);
	
	}

inline real32 Max_real32 (real32 x, real32 y)
	{
	
	return (x > y ? x : y);
	
	}

inline real32 Pin_real32 (real32 min, real32 x, real32 max)
	{
	
	return Max_real32 (min, Min_real32 (x, max));
	
	}

/*****************************************************************************/

inline real64 Abs_real64 (real64 x)
	{
	
	return (x < 0.0 ? -x : x);
	
	}

inline real64 Min_real64 (real64 x, real64 y)
	{
	
	return (x < y ? x : y);
	
	}

inline real64 Max_real64 (real64 x, real64 y)
	{
	
	return (x > y ? x : y);
	
	}

inline real64 Pin_real64 (real64 min, real64 x, real64 max)
	{
	
	return Max_real64 (min, Min_real64 (x, max));
	
	}

/*****************************************************************************/

inline int32 Round_int32 (real32 x)
	{
	
	return (int32) (x > 0.0f ? x + 0.5f : x - 0.5f);
	
	}

inline int32 Round_int32 (real64 x)
	{
	
	return (int32) (x > 0.0 ? x + 0.5 : x - 0.5);
	
	}

inline uint32 Floor_uint32 (real32 x)
	{
	
	return (uint32) (x);
	
	}

inline uint32 Floor_uint32 (real64 x)
	{
	
	return (uint32) (x);
	
	}

inline uint32 Round_uint32 (real32 x)
	{
	
	return Floor_uint32 (x + 0.5f);
	
	}

inline uint32 Round_uint32 (real64 x)
	{
	
	return Floor_uint32 (x + 0.5);
	
	}

/*****************************************************************************/

inline char ForceUppercase (char c)
	{
	
	if (c >= 'a' && c <= 'z')
		{
		
		c -= 'a' - 'A';
		
		}
		
	return c;
	
	}

/*****************************************************************************/

inline uint16 SwapBytes16 (uint16 x)
	{
	
	return (x << 8) |
		   (x >> 8);
	
	}

inline uint32 SwapBytes32 (uint32 x)
	{
	
	return (x << 24) +
		   ((x << 8) & 0x00FF0000) +
		   ((x >> 8) & 0x0000FF00) +
		   (x >> 24);
	
	}

/******************************************************************************/

class dng_timer
	{

	public:

		dng_timer (const char *message);

		~dng_timer ();
		
	private:
	
		// Hidden copy constructor and assignment operator.
	
		dng_timer (const dng_timer &timer);
		
		dng_timer & operator= (const dng_timer &timer);

	private:

		const char *fMessage;
		
		#if qMacOS
		
		uint32 fStartTime;
		
		#else

		clock_t fStartTime;
		
		#endif

	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/

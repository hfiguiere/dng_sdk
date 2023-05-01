/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_mutex.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/******************************************************************************/

#ifndef __dng_mutex__
#define __dng_mutex__

/******************************************************************************/

#include "dng_flags.h"

/******************************************************************************/

#if qDNGThreadSafe
	
#if qMacOS
#ifdef __MWERKS__
#include <Multiprocessing.h>
#else
#include <CoreServices/CoreServices.h>
#endif
#endif

#if qWinOS
#include <windows.h>
#endif

#endif

/******************************************************************************/

class dng_mutex
	{
	
	public:

		dng_mutex ();

		~dng_mutex ();

		void Lock ();

		void Unlock ();

	private:
	
		#if qDNGThreadSafe
	
		#if qMacOS
		
		MPCriticalRegionID fCritSec;
		
		#endif

		#if qWinOS

		CRITICAL_SECTION fCritSec;
		
		#endif
		
		#endif

	private:
	
		// Hidden copy constructor and assignment operator.
	
		dng_mutex (const dng_mutex &mutex);
		
		dng_mutex & operator= (const dng_mutex &mutex);
		
	};
		
/*****************************************************************************/

class dng_lock_mutex
	{
	
	private:
	
		dng_mutex *fMutex;
	
	public:
	
		dng_lock_mutex (dng_mutex *mutex);
			
		~dng_lock_mutex ();
			
	private:
	
		// Hidden copy constructor and assignment operator.
	
		dng_lock_mutex (const dng_lock_mutex &lock);
		
		dng_lock_mutex & operator= (const dng_lock_mutex &lock);
		
	};
	
/*****************************************************************************/

#endif
	
/*****************************************************************************/

/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_mutex.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

#include "dng_mutex.h"

/*****************************************************************************/

dng_mutex::dng_mutex ()

	#if qDNGThreadSafe
	
	:	fCritSec ()
	
	#endif
	
	{
	
	#if qDNGThreadSafe
	
	#if qMacOS
	
	MPCreateCriticalRegion (&fCritSec);
	
	#endif

	#if qWinOS
	
	InitializeCriticalSection (&fCritSec);
	
	#endif
	
	#endif
	
	}

/*****************************************************************************/

dng_mutex::~dng_mutex ()
	{
	
	#if qDNGThreadSafe
	
	#if qMacOS
	
	MPDeleteCriticalRegion (fCritSec);
	
	#endif

	#if qWinOS
	
	DeleteCriticalSection (&fCritSec);
	
	#endif
	
	#endif
	
	}

/*****************************************************************************/

void dng_mutex::Lock ()
	{
	
	#if qDNGThreadSafe
	
	#if qMacOS
	
	MPEnterCriticalRegion (fCritSec, kDurationForever);
	
	#endif

	#if qWinOS
	
	EnterCriticalSection (&fCritSec);
	
	#endif
	
	#endif
	
	}

/*****************************************************************************/

void dng_mutex::Unlock ()
	{
	
	#if qDNGThreadSafe
	
	#if qMacOS
	
	MPExitCriticalRegion (fCritSec);
	
	#endif

	#if qWinOS
	
	LeaveCriticalSection (&fCritSec);
	
	#endif
	
	#endif
	
	}

/*****************************************************************************/

dng_lock_mutex::dng_lock_mutex (dng_mutex *mutex)

	:	fMutex (mutex)
	
	{
	
	if (fMutex)
		fMutex->Lock ();
		
	}

/*****************************************************************************/

dng_lock_mutex::~dng_lock_mutex ()
	{
	
	if (fMutex)
		fMutex->Unlock ();
		
	}

/*****************************************************************************/

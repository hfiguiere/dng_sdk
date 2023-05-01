/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_utils.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#include "dng_utils.h"

#include "dng_assertions.h"

#if qMacOS
#ifdef __MWERKS__
#include <MacTypes.h>
#include <Events.h>
#else
#include <Carbon/Carbon.h>
#include <CoreServices/CoreServices.h>
#endif
#endif

#if qWinOS
#include <windows.h>
#endif

/*****************************************************************************/

#if qDNGDebug

void dng_show_message (const char *s)
	{
	
	#if qDNGValidate
	
		{
	
		fprintf (stderr, "%s\n", s);
		
		}
	
	#elif qMacOS
	
		{

		char ss [256];
		
		strcpy (ss, s);
		
		uint32 len = strlen (ss);
		
		for (uint32 j = len + 1; j >= 1; j--)
			ss [j] = ss [j - 1];
			
		ss [0] = (char) len;
		
		DebugStr ((unsigned char *) ss);
		
		}
	
	#elif qWinOS
	
		{
	
		MessageBoxA (NULL, (LPSTR) s, NULL, MB_OK);
		
		}
	
	#endif

	}
	
#endif

/*****************************************************************************/

dng_timer::dng_timer (const char *message)

	:	fMessage (message)
	,	fStartTime (0)
	
	{

	fMessage = message;
	
	#if qMacOS
	
	// Don't use the "clock" function on the Macintosh since it does not
	// measure time correctly on MP systems.
	
	fStartTime = TickCount ();
	
	#else

	fStartTime = clock ();
	
	#endif
	
	}

/*****************************************************************************/

dng_timer::~dng_timer ()
	{

	#if qMacOS
	
	uint32 finishTime = TickCount ();
	
	real64 sec = (finishTime - fStartTime) * (1.0 / 60.0);
	
	#else
	
	clock_t finishTime = clock ();
	
	real64 sec = (real64) (finishTime - fStartTime) /
				 (real64) CLOCKS_PER_SEC;
				 
	#endif
	
	fprintf (stderr, "%s: %0.2f sec\n", fMessage, sec);

	}

/*****************************************************************************/

/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_host.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#include "dng_host.h"

#include "dng_abort_sniffer.h"
#include "dng_area_task.h"
#include "dng_exceptions.h"
#include "dng_exif.h"
#include "dng_ifd.h"
#include "dng_memory.h"
#include "dng_negative.h"
#include "dng_shared.h"

/*****************************************************************************/

dng_host::dng_host (dng_memory_allocator *allocator,
					dng_abort_sniffer *sniffer)

	:	fAllocator	(allocator)
	,	fSniffer	(sniffer  )
	
	,	fNeedsMeta  		(true )
	,	fNeedsImage 		(true )
	,	fForPreview 		(false)
	,	fMinimumSize 		(0    )
	,	fKeepStage1 		(false)
	,	fKeepStage2 		(false)
	,	fKeepDNGPrivate 	(false)
	,	fKeepOriginalFile	(false)
	
	{
	
	}
	
/*****************************************************************************/

dng_host::~dng_host ()
	{
	
	}
	
/*****************************************************************************/

dng_memory_allocator & dng_host::Allocator ()
	{
	
	if (fAllocator)
		{
		
		return *fAllocator;
		
		}
		
	else
		{
		
		return gDefaultDNGMemoryAllocator;
		
		}
	
	}

/*****************************************************************************/

dng_memory_block * dng_host::Allocate (uint32 logicalSize)
	{
	
	return Allocator ().Allocate (logicalSize);
		
	}
		
/*****************************************************************************/

void dng_host::SniffForAbort ()
	{
	
	dng_abort_sniffer::SniffForAbort (Sniffer ());
	
	}
		
/*****************************************************************************/

bool dng_host::IsTransientError (dng_error_code code)
	{
	
	switch (code)
		{
		
		case dng_error_memory:
		case dng_error_user_canceled:
			{
			return true;
			}
			
		default:
			break;
			
		}
		
	return false;
	
	}
		
/*****************************************************************************/

void dng_host::PerformAreaTask (dng_area_task &task,
								const dng_rect &area)
	{
	
	dng_area_task::Perform (task,
							area,
							&Allocator (),
							Sniffer ());
	
	}
		
/*****************************************************************************/

dng_exif * dng_host::Make_dng_exif ()
	{
	
	dng_exif *result = new dng_exif ();
	
	if (!result)
		{
		
		ThrowMemoryFull ();

		}
	
	return result;
	
	}

/*****************************************************************************/

dng_shared * dng_host::Make_dng_shared ()
	{
	
	dng_shared *result = new dng_shared ();
	
	if (!result)
		{
		
		ThrowMemoryFull ();

		}
	
	return result;
	
	}

/*****************************************************************************/

dng_ifd * dng_host::Make_dng_ifd ()
	{
	
	dng_ifd *result = new dng_ifd ();
	
	if (!result)
		{
		
		ThrowMemoryFull ();

		}
	
	return result;
	
	}

/*****************************************************************************/

dng_negative * dng_host::Make_dng_negative ()
	{
	
	return dng_negative::Make (Allocator ());
	
	}
					      		 
/*****************************************************************************/

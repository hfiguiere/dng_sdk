/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_1d_table.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#include "dng_1d_table.h"

#include "dng_1d_function.h"
#include "dng_memory.h"
#include "dng_utils.h"

/*****************************************************************************/

dng_1d_table::dng_1d_table ()

	:	fBuffer ()
	,	fTable  (NULL)
	
	{
	
	}

/*****************************************************************************/

dng_1d_table::~dng_1d_table ()
	{
	
	}
		
/*****************************************************************************/

void dng_1d_table::Initialize (dng_memory_allocator &allocator,
							   const dng_1d_function &function)
	{
	
	fBuffer.Reset (allocator.Allocate ((kTableSize + 2) * sizeof (real32)));
	
	fTable = fBuffer->Buffer_real32 ();
	
	for (uint32 j = 0; j <= kTableSize; j++)
		{
		
		real64 x = j * (1.0 / (real64) kTableSize);
		
		real64 y = function.Evaluate (x);
		
		fTable [j] = (real32) y;
		
		}
		
	fTable [kTableSize + 1] = fTable [kTableSize];
	
	}

/*****************************************************************************/

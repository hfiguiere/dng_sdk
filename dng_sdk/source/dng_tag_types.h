/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_tag_types.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#ifndef __dng_tag_types__
#define __dng_tag_types__

/*****************************************************************************/

#include "dng_types.h"

/*****************************************************************************/

enum
	{
	ttByte = 1,
	ttAscii,
	ttShort,
	ttLong,
	ttRational,
	ttSByte,
	ttUndefined,
	ttSShort,
	ttSLong,
	ttSRational,
	ttFloat,
	ttDouble,
	ttIFD,
	ttUnicode,
	ttComplex
	};

/*****************************************************************************/

uint32 TagTypeSize (uint32 tagType);

/*****************************************************************************/

#endif
	
/*****************************************************************************/

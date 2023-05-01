/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_sdk_limits.h#2 $ */ 
/* $DateTime: 2006/04/12 14:23:04 $ */
/* $Change: 216157 $ */
/* $Author: stern $ */

/** \file
 * Collection of constants detailing maximum values used in processing in the DNG SDK.
 */

/*****************************************************************************/

#ifndef __dng_sdk_limits__
#define __dng_sdk_limits__

/*****************************************************************************/

#include "dng_types.h"

/*****************************************************************************/

/// The maximum number of SubIFDs that will be parsed.

const uint32 kMaxSubIFDs = 10;

/// The maximum number of chained IFDs that will be parsed.

const uint32 kMaxChainedIFDs = 10;

/// The maximum number of samples per pixel.

const uint32 kMaxSamplesPerPixel = 4;

/// Maximum number of color planes.

const uint32 kMaxColorPlanes = kMaxSamplesPerPixel;

/// The maximum size of a CFA repeating pattern.

const uint32 kMaxCFAPattern = 8;

/// The maximum size of a black level repeating pattern.

const uint32 kMaxBlackPattern = 8;

/// The maximum number of masked area rectangles.

const uint32 kMaxMaskedAreas = 4;

/// The maximum image size supported (pixels per side).

const uint32 kMaxImageSide = 30000;

/// Maximum number of MP threads for dng_area_task operations.

const uint32 kMaxMPThreads = 4;

/*****************************************************************************/

#endif
	
/*****************************************************************************/

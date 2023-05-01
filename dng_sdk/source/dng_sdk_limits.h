/*****************************************************************************/
// Copyright 2006-2007 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/camera_raw_main/camera_raw/dng_sdk/source/dng_sdk_limits.h#3 $ */ 
/* $DateTime: 2016/01/19 15:23:55 $ */
/* $Change: 1059947 $ */
/* $Author: erichan $ */

/** \file
 * Collection of constants detailing maximum values used in processing in the DNG SDK.
 */

/*****************************************************************************/

#ifndef __dng_sdk_limits__
#define __dng_sdk_limits__

/*****************************************************************************/

#include "dng_types.h"

/*****************************************************************************/

/// The maximum number of previews (in addition to the main IFD's thumbnail)
/// that we support embedded in a DNG.

const uint32 kMaxDNGPreviews = 20;

/// The maximum number of SubIFDs that will be parsed.

const uint32 kMaxSubIFDs = kMaxDNGPreviews + 1;

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

const uint32 kMaxImageSide = 65000;

/// The maximum number of tone curve points supported.

const uint32 kMaxToneCurvePoints = 8192;

/// Maximum number of MP threads for dng_area_task operations.

#if qDNG64Bit
const uint32 kMaxMPThreads = 32;
#else
const uint32 kMaxMPThreads = 8;
#endif

/*****************************************************************************/

#endif
	
/*****************************************************************************/

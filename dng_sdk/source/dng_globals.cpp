/*****************************************************************************/
// Copyright 2006-2012 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/camera_raw_main/camera_raw/dng_sdk/source/dng_globals.cpp#2 $ */ 
/* $DateTime: 2015/06/09 23:32:35 $ */
/* $Change: 1026104 $ */
/* $Author: aksherry $ */

/*****************************************************************************/

#include "dng_globals.h"

/*****************************************************************************/

#if qDNGValidate

bool gVerbose = false;

uint32 gDumpLineLimit = 100;

#endif

/******************************************************************************/

bool gDNGUseFakeTimeZonesInXMP = false;

/*****************************************************************************/

bool gDNGShowTimers = true;

/*****************************************************************************/

uint32 gDNGStreamBlockSize = 4096;

uint32 gDNGMaxStreamBufferSize = 1024 * 1024;

/*****************************************************************************/

bool gImagecore = false;

bool gPrintTimings = false;

bool gPrintAsserts = true;

bool gBreakOnAsserts = true;

/*****************************************************************************/

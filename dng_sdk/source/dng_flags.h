/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_flags.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/** \file
 * Connditional compilation flags for DNG SDK.
 *
 * All conditional compilation macros for the DNG SDK begin with a lowercase 'q'.
 */

/*****************************************************************************/

#ifndef __dng_flags__
#define __dng_flags__

/*****************************************************************************/

/// \def qMcOS 1 if compiling for Mac OS X
/// \def qWinOS 1 if compiling for Windows

// Make sure qMacOS and qWinOS are defined.

#if !defined(qMacOS) || !defined(qWinOS)
#include "RawEnvironment.h"
#endif

#if !defined(qMacOS) || !defined(qWinOS)
#error Unable to figure out platform
#endif

/*****************************************************************************/

/// \def qDNGDebug 1 if debug code (e.g. assertions) is compiled in, 0 otherwise.

// Figure out if debug build or not.

#ifndef qDNGDebug

#if defined(Debug)
#define qDNGDebug Debug

#elif defined(_DEBUG)
#define qDNGDebug _DEBUG

#else
#define qDNGDebug 0

#endif
#endif

/*****************************************************************************/

// Figure out byte order.

/// \def qDNGBigEndian 1 if this target platform is big endian (e.g. PowerPC Macintosh), else 0
/// \def qDNGLittleEndian 1 if this target platform is little endian (e.g. x86 processors), else 0

#ifndef qDNGBigEndian

#if defined(qDNGLittleEndian)
#define qDNGBigEndian !qDNGLittleEndian

#elif defined(__POWERPC__)
#define qDNGBigEndian 1

#elif defined(__INTEL__)
#define qDNGBigEndian 0

#elif defined(_M_IX86)
#define qDNGBigEndian 0

#elif defined(__LITTLE_ENDIAN__)
#define qDNGBigEndian 0

#elif defined(__BIG_ENDIAN__)
#define qDNGBigEndian 1

#else
#error Unable to figure out byte order.

#endif
#endif

#ifndef qDNGLittleEndian
#define qDNGLittleEndian !qDNGBigEndian
#endif

/*****************************************************************************/

/// \def qDNGThreadSafe 1 if target platform has thread support and threadsafe libraries, 0 otherwise

#ifndef qDNGThreadSafe
#define qDNGThreadSafe (qMacOS || qWinOS)
#endif

/*****************************************************************************/

/// \def qDNGValidateTarget 1 if dng_validate command line tool is being built, 0 otherwise

#ifndef qDNGValidateTarget
#define qDNGValidateTarget 0
#endif

/*****************************************************************************/

/// \def qDNGValidate 1 if DNG validation code is enabled, 0 otherwise.

#ifndef qDNGValidate
#define qDNGValidate qDNGValidateTarget
#endif

/*****************************************************************************/

#endif
	
/*****************************************************************************/

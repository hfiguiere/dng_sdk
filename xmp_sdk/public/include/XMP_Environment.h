#ifndef __XMP_Environment_h__
#define __XMP_Environment_h__ 1

/* --------------------------------------------------------------------------------------------- */
/* ** IMPORTANT ** This file must be usable by strict ANSI C compilers. No "//" comments, etc.   */
/* --------------------------------------------------------------------------------------------- */

/*
// =================================================================================================
// XMP_Environment.h - Build environment flags for the XMP toolkit.
// ================================================================
//
// This header is just C preprocessor macro definitions to set up the XMP toolkit build environment.
// It must be the first #include in any chain since it might affect things in other #includes.
//
// =================================================================================================
*/

/*
// =================================================================================================
// Copyright 2002-2005 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================
*/

/* ============================================================================================== */
/* Determine the Platform */
/* ====================== */

/* One of MAC_ENV, WIN_ENV, or UNIX_ENV must be defined by the client. Since some other code   */
/* requires these to be defined without values, they are only used here to define XMP-specific */
/* macros with 0 or 1 values.                                                                  */

#if defined ( MAC_ENV )

	#if 0	// ! maybe someday - ! MAC_ENV
		#error "MAC_ENV must be defined so that \"#if MAC_ENV\" is true"
	#endif
	
    #if defined ( WIN_ENV ) || defined ( UNIX_ENV )
        #error "XMP environment error - must define only one of MAC_ENV, WIN_ENV, or UNIX_ENV"
    #endif

    #define XMP_MacBuild  1
    #define XMP_WinBuild  0
    #define XMP_UNIXBuild 0

#elif defined ( WIN_ENV )

	#if 0	// ! maybe someday - ! WIN_ENV
		#error "WIN_ENV must be defined so that \"#if WIN_ENV\" is true"
	#endif
	
    #if defined ( UNIX_ENV )
        #error "XMP environment error - must define only one of MAC_ENV, WIN_ENV, or UNIX_ENV"
    #endif

    #define XMP_MacBuild  0
    #define XMP_WinBuild  1
    #define XMP_UNIXBuild 0

#elif defined ( UNIX_ENV )

	#if 0	// ! maybe someday - ! UNIX_ENV
		#error "UNIX_ENV must be defined so that \"#if UNIX_ENV\" is true"
	#endif
	
    #define XMP_MacBuild  0
    #define XMP_WinBuild  0
    #define XMP_UNIXBuild 1

#else

    #error "XMP environment error - must define one of MAC_ENV, WIN_ENV, or UNIX_ENV"

#endif

/* ============================================================================================== */
/* Common Macros */
/* ============= */

#if defined ( DEBUG )
    #if defined ( NDEBUG )
        #error "XMP environment error - both DEBUG and NDEBUG are defined"
    #endif
    #define XMP_DebugBuild 1
#endif

#if defined ( NDEBUG )
    #define XMP_DebugBuild 0
#endif

#ifndef XMP_DebugBuild
    #define XMP_DebugBuild 0
#endif

#if XMP_DebugBuild
    #include <stdio.h>  /* The assert macro needs printf. */
#endif

/* ============================================================================================== */
/* Macintosh Specific Settings */
/* =========================== */

/* ============================================================================================== */
/* Windows Specific Settings */
/* ========================= */

/* ============================================================================================== */
/* UNIX Specific Settings */
/* ====================== */

/* ============================================================================================== */

#endif  /* __XMP_Environment_h__ */

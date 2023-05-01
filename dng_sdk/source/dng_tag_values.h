/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_tag_values.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#ifndef __dng_tag_values__
#define __dng_tag_values__

/*****************************************************************************/

// Values for NewSubFileType tag.

enum
	{
	
	sfMainImage					= 0,
	sfPreviewImage				= 1
	
	};

/******************************************************************************/

// Values for PhotometricInterpretation tag.

enum
	{

	piWhiteIsZero 				= 0,
	piBlackIsZero				= 1,
	piRGB						= 2,
	piRGBPalette				= 3,
	piTransparencyMask			= 4,
	piCMYK						= 5,
	piYCbCr						= 6,
	piCIELab					= 7,
	piICCLab					= 8,

	piCFA						= 32803,		// TIFF-EP spec

	piLinearRaw					= 34892

	};

/******************************************************************************/

// Values for PlanarConfiguration tag.

enum
	{
	
	pcInterleaved				= 1,
	pcPlanar					= 2,
	
	pcRowInterleaved			= 100000		// Internal use only
	
	};

/******************************************************************************/

// Values for ExtraSamples tag.

enum
	{
	
	esUnspecified				= 0,
	esAssociatedAlpha			= 1,
	esUnassociatedAlpha			= 2
	
	};

/******************************************************************************/

// Values for SampleFormat tag.

enum
	{
	
	sfUnsignedInteger			= 1,
	sfSignedInteger				= 2,
	sfFloatingPoint				= 3,
	sfUndefined					= 4
	
	};

/******************************************************************************/

// Values for Compression tag.

enum
	{
	
	ccUncompressed				= 1,
	ccLZW						= 5,
	ccOldJPEG					= 6,
	ccJPEG						= 7,
	ccDeflate					= 8,
	ccPackBits					= 32773
	
	};

/******************************************************************************/

// Values for Predictor tag.

enum
	{
	
	cpNullPredictor				= 1,
	cpHorizontalDifference		= 2
	
	};		

/******************************************************************************/

// Values for ResolutionUnit tag.

enum
	{
	
	ruNone						= 1,
	ruInch						= 2,
	ruCM						= 3,
	ruMM						= 4,
	ruMicroM					= 5
	
	};		

/******************************************************************************/

// Values for LightSource tag.

enum
	{
	
	lsUnknown					=  0,
	
	lsDaylight					=  1,
	lsFluorescent				=  2,
	lsTungsten					=  3,
	lsFlash						=  4,
	lsFineWeather				=  9,
	lsCloudyWeather				= 10,
	lsShade						= 11,
	lsDaylightFluorescent		= 12,		// D 5700 - 7100K
	lsDayWhiteFluorescent		= 13,		// N 4600 - 5400K
	lsCoolWhiteFluorescent		= 14,		// W 3900 - 4500K
	lsWhiteFluorescent			= 15,		// WW 3200 - 3700K
	lsStandardLightA			= 17,
	lsStandardLightB			= 18,
	lsStandardLightC			= 19,
	lsD55						= 20,
	lsD65						= 21,
	lsD75						= 22,
	lsD50						= 23,
	lsISOStudioTungsten			= 24,
	
	lsOther						= 255
	
	};

/******************************************************************************/

// Values for ExposureProgram tag.

enum
	{
	
	epUnidentified				= 0,
	epManual					= 1,
	epProgramNormal				= 2,
	epAperturePriority			= 3,
	epShutterPriority			= 4,
	epProgramCreative			= 5,
	epProgramAction				= 6,
	epPortraitMode				= 7,
	epLandscapeMode				= 8
	
	};		

/******************************************************************************/

// Values for MeteringMode tag.

enum
	{
	
	mmUnidentified				= 0,
	mmAverage					= 1,
	mmCenterWeightedAverage		= 2,
	mmSpot						= 3,
	mmMultiSpot					= 4,
	mmPattern					= 5,
	mmPartial					= 6,
	
	mmOther						= 255
	
	};		

/******************************************************************************/

// CFA color codes from the TIFF/EP specification.

enum ColorKeyCode
	{
	
	colorKeyRed     = 0,
	colorKeyGreen   = 1,
	colorKeyBlue    = 2,
	colorKeyCyan    = 3,
	colorKeyMagenta = 4,
	colorKeyYellow  = 5,
	colorKeyWhite   = 6,
	
	colorKeyMaxEnum = 0xFF
	
	};
	
/*****************************************************************************/

// Values for the ColorimetricReference tag.  It specifies the colorimetric
// reference used for images with PhotometricInterpretation values of CFA
// or LinearRaw.

// This tag will be documented in the next version of the DNG specification.

enum
	{
	
	// Scene referred (default):
	
	crSceneReferred			= 0,
	
	// Output referred using the parameters of the ICC profile PCS.
	
	crICCProfilePCS			= 1
	
	};

/*****************************************************************************/

// TIFF-style byte order markers.

enum
	{
	
	byteOrderII		= 0x4949,		// 'II'
	byteOrderMM		= 0x4D4D		// 'MM'
	
	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/

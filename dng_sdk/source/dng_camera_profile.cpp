/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_camera_profile.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

#include "dng_camera_profile.h"

#include "dng_exceptions.h"
#include "dng_info.h"
#include "dng_tag_values.h"
#include "dng_xy_coord.h"

/*****************************************************************************/

const char * kProfileName_Embedded = "Embedded";

/*****************************************************************************/

dng_camera_profile::dng_camera_profile ()

	:	fName ()
	,	fCalibrationIlluminant1 (lsUnknown)
	,	fCalibrationIlluminant2 (lsUnknown)
	,	fColorMatrix1 ()
	,	fColorMatrix2 ()
	,	fCameraCalibration1 ()
	,	fCameraCalibration2 ()
	,	fReductionMatrix1 ()
	,	fReductionMatrix2 ()
	
	{
	
	}

/*****************************************************************************/

dng_camera_profile::~dng_camera_profile ()
	{
	
	}

/*****************************************************************************/

real64 dng_camera_profile::IlluminantToTemperature (uint32 light)
	{
	
	switch (light)
		{
		
		case lsStandardLightA:
		case lsTungsten:
			{
			return 2850.0;
			}
			
		case lsISOStudioTungsten:
			{
			return 3200.0;
			}
			
		case lsD50:
			{
			return 5000.0;
			}
			
		case lsD55:
		case lsDaylight:
		case lsFineWeather:
		case lsFlash:
		case lsStandardLightB:
			{
			return 5500.0;
			}
			
		case lsD65:
		case lsStandardLightC:
		case lsCloudyWeather:
			{
			return 6500.0;
			}
			
		case lsD75:
		case lsShade:
			{
			return 7500.0;
			}
			
		case lsDaylightFluorescent:
			{
			return (5700.0 + 7100.0) * 0.5;
			}
			
		case lsDayWhiteFluorescent:
			{
			return (4600.0 + 5400.0) * 0.5;
			}
			
		case lsCoolWhiteFluorescent:
		case lsFluorescent:
			{
			return (3900.0 + 4500.0) * 0.5;
			}
			
		case lsWhiteFluorescent:
			{
			return (3200.0 + 3700.0) * 0.5;
			}
			
		default:
			{
			return 0.0;
			}
			
		}
	
	}

/******************************************************************************/

void dng_camera_profile::NormalizeColorMatrix (dng_matrix &m)
	{
	
	// Find scale factor to normalize the matrix.
	
	dng_vector coord = m * PCStoXYZ ();
	
	real64 maxCoord = coord.MaxEntry ();
	
	if (maxCoord > 0.0 && (maxCoord < 0.99 || maxCoord > 1.01))
		{
		
		m.Scale (1.0 / maxCoord);
		
		}
		
	// Round to four decimal places.
	
	m.Round (10000);
			
	}

/******************************************************************************/

void dng_camera_profile::SetColorMatrix1 (const dng_matrix &m)
	{
	
	fColorMatrix1 = m;
	
	NormalizeColorMatrix (fColorMatrix1);
	
	}

/******************************************************************************/

void dng_camera_profile::SetColorMatrix2 (const dng_matrix &m)
	{
	
	fColorMatrix2 = m;
	
	NormalizeColorMatrix (fColorMatrix2);
	
	}
		
/******************************************************************************/

void dng_camera_profile::SetCameraCalibration1 (const dng_matrix &m)
	{
	
	fCameraCalibration1 = m;
	
	fCameraCalibration1.Round (10000);
	
	}

/******************************************************************************/

void dng_camera_profile::SetCameraCalibration2 (const dng_matrix &m)
	{
	
	fCameraCalibration2 = m;
	
	fCameraCalibration2.Round (10000);
		
	}

/******************************************************************************/

void dng_camera_profile::SetReductionMatrix1 (const dng_matrix &m)
	{
	
	fReductionMatrix1 = m;
	
	fReductionMatrix1.Round (10000);
	
	}

/******************************************************************************/

void dng_camera_profile::SetReductionMatrix2 (const dng_matrix &m)
	{
	
	fReductionMatrix2 = m;
	
	fReductionMatrix2.Round (10000);
	
	}

/*****************************************************************************/

bool dng_camera_profile::HasColorMatrix1 () const
	{
	
	return fColorMatrix1.Cols () == 3 &&
		   fColorMatrix1.Rows ()  > 1;
	
	}
		
/*****************************************************************************/

bool dng_camera_profile::HasColorMatrix2 () const
	{

	return fColorMatrix2.Cols () == 3 &&
		   fColorMatrix2.Rows () == fColorMatrix1.Rows ();
	
	}
		
/******************************************************************************/

bool dng_camera_profile::IsValid (uint32 channels) const
	{
	
	// For Monochrome images, we ignore the camera profile.
		
	if (channels == 1)
		{
		
		return true;
		
		}
		
	// ColorMatrix1 is required for all color images.
		
	if (fColorMatrix1.Cols () != 3 ||
		fColorMatrix1.Rows () != channels)
		{
		
		return false;
		
		}
		
	// ColorMatrix2 is optional, but it must be valid if present.
	
	if (fColorMatrix2.Cols () != 0 ||
		fColorMatrix2.Rows () != 0)
		{
		
		if (fColorMatrix2.Cols () != 3 ||
			fColorMatrix2.Rows () != channels)
			{
			
			return false;
			
			}
		
		}
	
	// CameraCalibration1 is optional, but it must be valid if present.
	
	if (fCameraCalibration1.Cols () != 0 ||
		fCameraCalibration1.Rows () != 0)
		{
		
		if (fCameraCalibration1.Cols () != channels ||
			fCameraCalibration1.Rows () != channels)
			{
			
			return false;
			
			}
		
		}
	
	// CameraCalibration2 is optional, but it must be valid if present.
	
	if (fCameraCalibration2.Cols () != 0 ||
		fCameraCalibration2.Rows () != 0)
		{
		
		if (fCameraCalibration2.Cols () != channels ||
			fCameraCalibration2.Rows () != channels)
			{
			
			return false;
			
			}
		
		}
	
	// ReductionMatrix1 is optional, but it must be valid if present.
	
	if (fReductionMatrix1.Cols () != 0 ||
		fReductionMatrix1.Rows () != 0)
		{
		
		if (fReductionMatrix1.Cols () != channels ||
			fReductionMatrix1.Rows () != 3)
			{
			
			return false;
			
			}
		
		}
	
	// ReductionMatrix2 is optional, but it must be valid if present.
	
	if (fReductionMatrix2.Cols () != 0 ||
		fReductionMatrix2.Rows () != 0)
		{
		
		if (fReductionMatrix2.Cols () != channels ||
			fReductionMatrix2.Rows () != 3)
			{
			
			return false;
			
			}
		
		}
	
	return true;
	
	}
		
/*****************************************************************************/

bool dng_camera_profile::EqualData (const dng_camera_profile &profile,
									bool ignoreCalibration) const
	{
	
	if (!ignoreCalibration)
		{
		
		if (fCameraCalibration1 != profile.fCameraCalibration1 ||
			fCameraCalibration2 != profile.fCameraCalibration2)
			{
			
			return false;
			
			}
		
		}
	
	return fCalibrationIlluminant1 == profile.fCalibrationIlluminant1 &&
		   fCalibrationIlluminant2 == profile.fCalibrationIlluminant2 &&
		   fColorMatrix1           == profile.fColorMatrix1           &&
		   fColorMatrix2           == profile.fColorMatrix2			  &&
		   fReductionMatrix1       == profile.fReductionMatrix1       &&
		   fReductionMatrix2       == profile.fReductionMatrix2;
	
	}
		
/*****************************************************************************/

void dng_camera_profile::Parse (dng_host & /* host */,
								dng_stream & /* stream */,
								dng_info &info)
	{
	
	dng_shared &shared = *(info.fShared.Get ());
	
	SetCalibrationIlluminant1 (shared.fCalibrationIlluminant1);
			
	SetColorMatrix1 (shared.fColorMatrix1);
			
	if (shared.fCameraCalibration1.NotEmpty ())
		{
		
		SetCameraCalibration1 (shared.fCameraCalibration1);
		
		}
		
	if (shared.fReductionMatrix1.NotEmpty ())
		{
		
		SetReductionMatrix1 (shared.fReductionMatrix1);
		
		}
		
	if (shared.fColorMatrix2.NotEmpty ())
		{
		
		SetCalibrationIlluminant2 (shared.fCalibrationIlluminant2);
		
		SetColorMatrix2 (shared.fColorMatrix2);
		
		if (shared.fCameraCalibration2.NotEmpty ())
			{
			
			SetCameraCalibration2 (shared.fCameraCalibration2);
			
			}
			
		if (shared.fReductionMatrix2.NotEmpty ())
			{
			
			SetReductionMatrix1 (shared.fReductionMatrix2);
			
			}
		
		}
		
	}
		
/*****************************************************************************/

void dng_camera_profile::SetFourColorBayer ()
	{
	
	uint32 j;
	
	if (!IsValid (3))
		{
		ThrowProgramError ();
		}
		
	if (fColorMatrix1.NotEmpty ())
		{
		
		dng_matrix m (4, 3);
		
		for (j = 0; j < 3; j++)
			{
			m [0] [j] = fColorMatrix1 [0] [j];
			m [1] [j] = fColorMatrix1 [1] [j];
			m [2] [j] = fColorMatrix1 [2] [j];
			m [1] [j] = fColorMatrix1 [1] [j];
			}
			
		fColorMatrix1 = m;
		
		}
	
	if (fColorMatrix2.NotEmpty ())
		{
		
		dng_matrix m (4, 3);
		
		for (j = 0; j < 3; j++)
			{
			m [0] [j] = fColorMatrix2 [0] [j];
			m [1] [j] = fColorMatrix2 [1] [j];
			m [2] [j] = fColorMatrix2 [2] [j];
			m [1] [j] = fColorMatrix2 [1] [j];
			}
			
		fColorMatrix2 = m;
		
		}
		
	fCameraCalibration1.Clear ();
	fCameraCalibration2.Clear ();
	
	fReductionMatrix1.Clear ();
	fReductionMatrix2.Clear ();
	
	}

/*****************************************************************************/

/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_color_spec.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

#include "dng_color_spec.h"

#include "dng_assertions.h"
#include "dng_camera_profile.h"
#include "dng_exceptions.h"
#include "dng_matrix.h"
#include "dng_negative.h"
#include "dng_temperature.h"
#include "dng_utils.h"
#include "dng_xy_coord.h"

/*****************************************************************************/

dng_matrix_3by3 MapWhiteMatrix (const dng_xy_coord &white1,
						        const dng_xy_coord &white2)
	{
	
	// Use the linearized Bradford adaptation matrix.
	
	dng_matrix_3by3 Mb ( 0.8951,  0.2664, -0.1614,
		 		        -0.7502,  1.7135,  0.0367,
		  			     0.0389, -0.0685,  1.0296);
	
	dng_vector_3 w1 = Mb * XYtoXYZ (white1);
	dng_vector_3 w2 = Mb * XYtoXYZ (white2);
	
	// Limit scaling to something reasonable.
	
	dng_matrix_3by3 A;
	
	A [0] [0] = Pin_real64 (0.1, w2 [0] / w1 [0], 10.0);
	A [1] [1] = Pin_real64 (0.1, w2 [1] / w1 [1], 10.0);
	A [2] [2] = Pin_real64 (0.1, w2 [2] / w1 [2], 10.0);
	
	dng_matrix_3by3 B = Invert (Mb) * A * Mb;
	
	return B;
	
	}

/******************************************************************************/

dng_color_spec::dng_color_spec (const dng_negative &negative,
							    const dng_camera_profile *profile)
								
	:	fChannels (negative.ColorChannels ())
	
	,	fTemperature1 (0.0)
	,	fTemperature2 (0.0)
	
	,	fXYZtoCamera1 ()
	,	fXYZtoCamera2 ()
	
	,	fReduction1 ()
	,	fReduction2 ()
	
	,	fWhiteXY ()
	
	,	fCameraWhite ()
	,	fCameraToPCS ()
	
	{
	
	if (fChannels > 1)
		{
	
		if (!profile || !profile->IsValid (fChannels))
			{
			
			ThrowBadFormat ();
			
			}
		
		fTemperature1 = profile->CalibrationTemperature1 ();
		fTemperature2 = profile->CalibrationTemperature2 ();
		
		fXYZtoCamera1 = profile->ColorMatrix1 ();
		fXYZtoCamera2 = profile->ColorMatrix2 ();
				
		fReduction1 = profile->ReductionMatrix1 ();
		fReduction2 = profile->ReductionMatrix2 ();
		
		dng_matrix C1 = profile->CameraCalibration1 ();
		dng_matrix C2 = profile->CameraCalibration2 ();
		
		if (C1.Rows () == fChannels &&
			C1.Cols () == fChannels)
			{
			
			fXYZtoCamera1 = C1 * fXYZtoCamera1;
			
			}
			
		if (!profile->HasColorMatrix2 () ||
				fTemperature1 <= 0.0 ||
				fTemperature2 <= 0.0 ||
				fTemperature1 == fTemperature2)
			{
			
			fTemperature1 = 5000.0;
			fTemperature2 = 5000.0;
			
			fXYZtoCamera2 = fXYZtoCamera1;
			
			fReduction2 = fReduction1;
			
			}
			
		else
			{
			
			if (C2.Rows () == fChannels &&
				C2.Cols () == fChannels)
				{
				
				fXYZtoCamera2 = C2 * fXYZtoCamera2;
				
				}
			
			}
			
		dng_matrix G (fChannels, fChannels);
		
		for (uint32 j = 0; j < fChannels; j++)
			{
			
			G [j] [j] = negative.AnalogBalance (j);
			
			}
				
		fXYZtoCamera1 = G * fXYZtoCamera1;
		fXYZtoCamera2 = G * fXYZtoCamera2;
		
		if (fTemperature1 > fTemperature2)
			{
			
			real64 temp   = fTemperature1;
			fTemperature1 = fTemperature2;
			fTemperature2 = temp;
			
			dng_matrix T  = fXYZtoCamera1;
			fXYZtoCamera1 = fXYZtoCamera2;
			fXYZtoCamera2 = T;
			
			T           = fReduction1;
			fReduction1 = fReduction2;
			fReduction2 = T;
			
			}
			
		}
		
	}

/*****************************************************************************/

void dng_color_spec::FindXYZtoCamera (const dng_xy_coord &white,
									  dng_matrix &xyzToCamera,
									  dng_matrix &reduction)
	{
	
	// Convert to temperature/offset space.
	
	dng_temperature td (white);
	
	// Find fraction to weight the first calibration.
	
	real64 g;
	
	if (td.Temperature () <= fTemperature1)
		g = 1.0;
	
	else if (td.Temperature () >= fTemperature2)
		g = 0.0;
	
	else
		{
		
		real64 invT = 1.0 / td.Temperature ();
		
		g = (invT                  - (1.0 / fTemperature2)) /
		    ((1.0 / fTemperature1) - (1.0 / fTemperature2));
		    
		}
		
	// Interpolate the color matrix.
		
	if (g >= 1.0)
		xyzToCamera = fXYZtoCamera1;
		
	else if (g <= 0.0)
		xyzToCamera = fXYZtoCamera2;
		
	else
		xyzToCamera = (g      ) * fXYZtoCamera1 +
					  (1.0 - g) * fXYZtoCamera2;
					   
	// Interpolate four to three matrix, if any.
				   
	bool has1 = fReduction1.Rows () != 0;
	bool has2 = fReduction2.Rows () != 0;
				   
	if (has1 && has2)
		{
		
		if (g >= 1.0)
			reduction = fReduction1;
		
		else if (g <= 0.0)
			reduction = fReduction2;
			
		else
			reduction = (g      ) * fReduction1 +
						(1.0 - g) * fReduction2;
		
		}
		
	else if (has1)
		{
		
		reduction = fReduction1;
	
		}
		
	else if (has2)
		{
		
		reduction = fReduction2;
	
		}
		
	else
		{
		
		reduction.Clear ();
		
		}
		
	}

/*****************************************************************************/

void dng_color_spec::SetWhiteXY (const dng_xy_coord &white)
	{
	
	fWhiteXY = white;
	
	// Deal with monochrome cameras.
	
	if (Channels () == 1)
		{
		
		fCameraWhite = dng_vector (1);
		
		fCameraWhite [0] = 1.0;
		
		fCameraToPCS = PCStoXYZ ().AsColumn ();
		
		return;
		
		}
	
	// Interpolate an XYZ to Camera coordinates matrix.
	
	dng_matrix xyzToCamera;
	dng_matrix reduction;
	
	FindXYZtoCamera (fWhiteXY, xyzToCamera, reduction);
	
	// Adjust for the non-PCS white point.
	
	dng_matrix pcsToCamera = xyzToCamera * MapWhiteMatrix (PCStoXY (), fWhiteXY);
	
	// Scale matrix so PCS white can just be reached when the first camera
	// channel saturates.
	
	real64 scale = MaxEntry (pcsToCamera * PCStoXYZ ());
	
	pcsToCamera = (1.0 / scale) * pcsToCamera;
	
	// Find clip values to use for each camera channel.
	
	fCameraWhite = pcsToCamera * PCStoXYZ ();
	
	// Invert this matrix.  Note that if there are more than three
	// camera channels, this inversion is non-unique.
	
	fCameraToPCS = Invert (pcsToCamera, reduction);
		
	}

/*****************************************************************************/

const dng_xy_coord & dng_color_spec::WhiteXY () const
	{
	
	ASSERT (fWhiteXY.IsValid (), "Using invalid WhiteXY");
	
	return fWhiteXY;

	}

/*****************************************************************************/

const dng_vector & dng_color_spec::CameraWhite () const
	{
	
	ASSERT (fCameraWhite.NotEmpty (), "Using invalid CameraWhite");
	
	return fCameraWhite;
	
	}

/*****************************************************************************/

const dng_matrix & dng_color_spec::CameraToPCS () const
	{
	
	ASSERT (fCameraToPCS.NotEmpty (), "Using invalid CameraToPCS");
	
	return fCameraToPCS;
	
	}

/*****************************************************************************/

dng_xy_coord dng_color_spec::NeutralToXY (const dng_vector &neutral)
	{
	
	const uint32 kMaxPasses = 30;
	
	if (Channels () == 1)
		{
		
		return PCStoXY ();
		
		}
	
	dng_xy_coord last = D50_xy_coord ();
	
	for (uint32 pass = 0; pass < kMaxPasses; pass++)
		{
		
		dng_matrix xyzToCamera;
		dng_matrix reduction;
		
		FindXYZtoCamera (last, xyzToCamera, reduction);
		
		dng_xy_coord next = XYZtoXY (Invert (xyzToCamera, reduction) * neutral);
		
		if (Abs_real64 (next.x - last.x) +
			Abs_real64 (next.y - last.y) < 0.0000001)
			{
			
			return next;
			
			}
			
		// If we reach the limit without converging, we are most likely
		// in a two value oscillation.  So take the average of the last
		// two estimates and give up.
			
		if (pass == kMaxPasses - 1)
			{
			
			next.x = (last.x + next.x) * 0.5;
			next.y = (last.y + next.y) * 0.5;
			
			}
			
		last = next;
		
		}
		
	return last;
	
	}
			
/*****************************************************************************/

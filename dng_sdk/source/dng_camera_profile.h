/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_camera_profile.h#2 $ */ 
/* $DateTime: 2006/04/12 14:23:04 $ */
/* $Change: 216157 $ */
/* $Author: stern $ */

/** \file
 * Support for DNG camera color profile information.
 *  Per the \ref spec_dng "DNG 1.1.0 specification", a DNG file can store up to two sets of color profile
 *  information for a camera in the DNG file from that camera. The second set is optional
 *  and when there are two sets, they represent profiles made under different illumination.
 *
 *  Profiling information is optionally separated into two parts. One part represents a profile
 *  for a reference camera. (ColorMatrix1 and ColorMatrix2 here.) The second is a per-camera
 *  calibration that takes into account unit-to-unit variation. This is designed to allow
 *  replacing the reference color matrix with one of one's own construction while maintaining
 *  any unit-specific calibration the camera manufacturer may have provided.
 *
 * See Appendix 6 of the \ref spec_dng "DNG 1.1.0 specification" for more information.
 */

#ifndef __dng_camera_profile__
#define __dng_camera_profile__

/*****************************************************************************/

#include "dng_classes.h"
#include "dng_matrix.h"
#include "dng_string.h"

/*****************************************************************************/

extern const char * kProfileName_Embedded;

/******************************************************************************/

/// \brief Container for DNG camera color profile and calibration data.

class dng_camera_profile
	{
	
	protected:
	
		// Name of this camera profile.
		
		dng_string fName;
	
		// Light sources for up to two calibrations. These use the EXIF
		// encodings for illuminant and are used to distinguish which
		// matrix to use.
		
		uint32 fCalibrationIlluminant1;
		uint32 fCalibrationIlluminant2;
		
		// Color matrices for up to two calibrations.
		
		// These matrices map XYZ values to camera values.  Adobe needs to go
		// that direction in order to determine the clipping points for
		// highlight recovery logic based on the white point.  If cameras
		// were all 3-color, the matrix could be stored as a forward matrix,
		// but we need the backwards matrix to deal with 4-color cameras.
		
		dng_matrix fColorMatrix1;
		dng_matrix fColorMatrix2;
		
		// Individual camera calibrations.
		
		// Camera data --> camera calibration --> "inverse" of color matrix
		
		// This will be a 4x4 matrix for a 4-color camera. The defaults are
		// almost always the identity matrix and for the cases where they
		// aren't, they are diagonal matrices.
		
		dng_matrix fCameraCalibration1;
		dng_matrix fCameraCalibration2;
		
		// Dimensionality reduction hints for four color cameras.
		
		// This is an optional matrix that maps 4 components to 3 components.
		
		dng_matrix fReductionMatrix1;
		dng_matrix fReductionMatrix2;
		
	public:
	
		dng_camera_profile ();
		
		virtual ~dng_camera_profile ();
		
		// API for profile name:

		/// Setter for camera profile name.
		/// \param name Name to use for this camera profile.

		void SetName (const char *name)
			{
			fName.Set (name);
			}

		/// Getter for camera profile name.
		/// \retval Name of profile.

		const char *Name () const
			{
			return fName.Get ();
			}
		
		/// Test if this name is embedded.
		/// \retval true if the name matches the name of the embedded camera profile.

		bool NameIsEmbedded () const
			{
			return fName.Matches (kProfileName_Embedded, true);
			}
			
		// API for calibration illuminants:
		
		/// Setter for first of up to two light sources used for calibration. 
		/// Uses the EXIF encodings for illuminant and is used to distinguish which
		/// matrix to use.
		/// Corresponds to the DNG CalibrationIlluminant1 tag.

		void SetCalibrationIlluminant1 (uint32 light)
			{
			fCalibrationIlluminant1 = light;
			}
			
		/// Setter for second of up to two light sources used for calibration. 
		/// Uses the EXIF encodings for illuminant and is used to distinguish which
		/// matrix to use.
		/// Corresponds to the DNG CalibrationIlluminant2 tag.

		void SetCalibrationIlluminant2 (uint32 light)
			{
			fCalibrationIlluminant2 = light;
			}
			
		/// Getter for first of up to two light sources used for calibration. 
		/// Uses the EXIF encodings for illuminant and is used to distinguish which
		/// matrix to use.
		/// Corresponds to the DNG CalibrationIlluminant1 tag.

		uint32 CalibrationIlluminant1 () const
			{
			return fCalibrationIlluminant1;
			}
			
		/// Getter for second of up to two light sources used for calibration. 
		/// Uses the EXIF encodings for illuminant and is used to distinguish which
		/// matrix to use.
		/// Corresponds to the DNG CalibrationIlluminant2 tag.

		uint32 CalibrationIlluminant2 () const
			{
			return fCalibrationIlluminant2;
			}
		
		/// Getter for first of up to two light sources used for calibration, returning result as color temperature.

		real64 CalibrationTemperature1 () const
			{
			return IlluminantToTemperature (CalibrationIlluminant1 ());
			}

		/// Getter for second of up to two light sources used for calibration, returning result as color temperature.

		real64 CalibrationTemperature2 () const
			{
			return IlluminantToTemperature (CalibrationIlluminant2 ());
			}
			
		// API for color matrices:
		
		/// Setter for first of up to two color matrices used for reference camera calibrations.
		/// These matrices map XYZ values to camera values.  The DNG SDK needs to map colors
		/// that direction in order to determine the clipping points for
		/// highlight recovery logic based on the white point.  If cameras
		/// were all three-color, the matrix could be stored as a forward matrix.
		/// The inverse matrix is requried to support four-color cameras.

		void SetColorMatrix1 (const dng_matrix &m);

		/// Setter for second of up to two color matrices used for reference camera calibrations.
		/// These matrices map XYZ values to camera values.  The DNG SDK needs to map colors
		/// that direction in order to determine the clipping points for
		/// highlight recovery logic based on the white point.  If cameras
		/// were all three-color, the matrix could be stored as a forward matrix.
		/// The inverse matrix is requried to support four-color cameras.

		void SetColorMatrix2 (const dng_matrix &m);
						    		    
		/// Predicate to test if first camera matrix is set

		bool HasColorMatrix1 () const;

		/// Predicate to test if second camera matrix is set

		bool HasColorMatrix2 () const;
		
		/// Getter for first of up to two color matrices used for calibrations.

		const dng_matrix & ColorMatrix1 () const
			{
			return fColorMatrix1;
			}
			
		/// Getter for second of up to two color matrices used for calibrations.

		const dng_matrix & ColorMatrix2 () const
			{
			return fColorMatrix2;
			}
		
		// API for camera calibration:
		
		/// Setter for first of up to two color matrices used for individual camera calibrations.
		/// 
		/// The sequence of matrix transforms is:
		/// Camera data --> camera calibration --> "inverse" of color matrix
		///
		/// This will be a 4x4 matrix for a four-color camera. The defaults are
		/// almost always the identity matrix, and for the cases where they
		/// aren't, they are diagonal matrices.

		void SetCameraCalibration1 (const dng_matrix &m);

		/// Setter for second of up to two color matrices used for individual camera calibrations.
		/// 
		/// The sequence of matrix transforms is:
		/// Camera data --> camera calibration --> "inverse" of color matrix
		///
		/// This will be a 4x4 matrix for a four-color camera. The defaults are
		/// almost always the identity matrix, and for the cases where they
		/// aren't, they are diagonal matrices.

		void SetCameraCalibration2 (const dng_matrix &m);
		
		/// Getter for first of up to two color matrices used for individual camera calibrations.

		const dng_matrix & CameraCalibration1 () const
			{
			return fCameraCalibration1;
			}
	
		/// Getter for second of up to two color matrices used for individual camera calibrations.

		const dng_matrix & CameraCalibration2 () const
			{
			return fCameraCalibration2;
			}
			
		// API for reduction matrices:
		
		/// Setter for first of up to two dimensionality reduction hints for four-color cameras.
		/// This is an optional matrix that maps four components to three.
		/// See Appendix 6 of the \ref spec_dng "DNG 1.1.0 specification."

		void SetReductionMatrix1 (const dng_matrix &m);

		/// Setter for second of up to two dimensionality reduction hints for four-color cameras.
		/// This is an optional matrix that maps four components to three.
		/// See Appendix 6 of the \ref spec_dng "DNG 1.1.0 specification."

		void SetReductionMatrix2 (const dng_matrix &m);
		
		/// Getter for first of up to two dimensionality reduction hints for four color cameras.

		const dng_matrix & ReductionMatrix1 () const
			{
			return fReductionMatrix1;
			}
			
		/// Getter for second of up to two dimensionality reduction hints for four color cameras.

		const dng_matrix & ReductionMatrix2 () const
			{
			return fReductionMatrix2;
			}
			
		/// Determines if this a valid profile for this number of color channels?
		/// \retval true if the profile is valid.

		bool IsValid (uint32 channels) const;
		
		/// Predicate to check if two camera profiles are colorwise equal, thus ignores the profile name and optionally the camera calibration.
		/// \param profile Camera profile to compare to.
		/// \param ignoreCalibration Controls whether the camera calibration info is checked for equality as well

		bool EqualData (const dng_camera_profile &profile,
						bool ignoreCalibration = false) const;
		
		/// Parse profile from DNG file.

		void Parse (dng_host &host,
					dng_stream &stream,
					dng_info &info);
					
		/// Convert from a three-color to a four-color Bayer profile.

		virtual void SetFourColorBayer ();
		
	protected:
	
		static real64 IlluminantToTemperature (uint32 light);
		
		static void NormalizeColorMatrix (dng_matrix &m);
		
	};

/*****************************************************************************/

#endif

/*****************************************************************************/

/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_shared.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#ifndef __dng_shared__
#define __dng_shared__

/*****************************************************************************/

#include "dng_classes.h"
#include "dng_fingerprint.h"
#include "dng_matrix.h"
#include "dng_rational.h"
#include "dng_string.h"
#include "dng_stream.h"
#include "dng_sdk_limits.h"
#include "dng_types.h"
#include "dng_xy_coord.h"

/*****************************************************************************/

class dng_shared
	{
	
	public:
	
		uint32 fExifIFD;
		uint32 fGPSInfo;
		uint32 fInteroperabilityIFD;
		uint32 fKodakDCRPrivateIFD;
		uint32 fKodakKDCPrivateIFD;
		
		uint32 fXMPCount;
		uint32 fXMPOffset;
		
		uint32 fIPTC_NAA_Count;
		uint32 fIPTC_NAA_Offset;

		uint32 fMakerNoteCount;
		uint32 fMakerNoteOffset;
		uint32 fMakerNoteSafety;
		
		uint32 fDNGVersion;
		uint32 fDNGBackwardVersion;
		
		dng_string fUniqueCameraModel;
		dng_string fLocalizedCameraModel;
		
		uint32 fColorPlanes;
		
		uint32 fCalibrationIlluminant1;
		uint32 fCalibrationIlluminant2;
		
		dng_matrix fColorMatrix1;
		dng_matrix fColorMatrix2;
		
		dng_matrix fCameraCalibration1;
		dng_matrix fCameraCalibration2;
		
		dng_matrix fReductionMatrix1;
		dng_matrix fReductionMatrix2;
		
		dng_vector fAnalogBalance;
		
		dng_vector fAsShotNeutral;
		
		dng_xy_coord fAsShotWhiteXY;
		
		dng_srational fBaselineExposure;
		dng_urational fBaselineNoise;
		dng_urational fBaselineSharpness;
		dng_urational fLinearResponseLimit;
		dng_urational fShadowScale;
		
		uint32 fDNGPrivateDataCount;
		uint32 fDNGPrivateDataOffset;
		
		dng_fingerprint fRawDataUniqueID;
		
		dng_string fOriginalRawFileName;
		
		uint32 fOriginalRawFileDataCount;
		uint32 fOriginalRawFileDataOffset;
		
		uint32 fAsShotICCProfileCount;
		uint32 fAsShotICCProfileOffset;
		
		dng_matrix fAsShotPreProfileMatrix;
		
		uint32 fCurrentICCProfileCount;
		uint32 fCurrentICCProfileOffset;
		
		dng_matrix fCurrentPreProfileMatrix;
		
		uint32 fColorimetricReference;
		
	public:
	
		dng_shared ();
		
		virtual ~dng_shared ();
		
		virtual bool ParseTag (dng_stream &stream,
							   dng_exif &exif,
							   uint32 parentCode,
							   bool isMainIFD,
							   uint32 tagCode,
							   uint32 tagType,
							   uint32 tagCount,
							   uint32 tagOffset,
							   int32 offsetDelta);
							   
		virtual void PostParse (dng_host &host,
								dng_exif &exif);
		
		virtual bool IsValidDNG ();
		
	protected:
		
		virtual bool Parse_ifd0 (dng_stream &stream,
							     dng_exif &exif,
							 	 uint32 parentCode,
							 	 uint32 tagCode,
							 	 uint32 tagType,
							 	 uint32 tagCount,
							 	 uint32 tagOffset);
							 		 
		virtual bool Parse_ifd0_exif (dng_stream &stream,
							          dng_exif &exif,
						 		 	  uint32 parentCode,
						 		 	  uint32 tagCode,
						 		 	  uint32 tagType,
						 		 	  uint32 tagCount,
						 		 	  uint32 tagOffset);
	
	};
	
/*****************************************************************************/

#endif
	
/*****************************************************************************/

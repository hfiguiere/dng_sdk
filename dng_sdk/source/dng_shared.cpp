/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_shared.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#include "dng_shared.h"

#include "dng_exceptions.h"
#include "dng_globals.h"
#include "dng_parse_utils.h"
#include "dng_tag_codes.h"
#include "dng_tag_types.h"
#include "dng_tag_values.h"
#include "dng_utils.h"

/*****************************************************************************/

dng_shared::dng_shared ()
	
	:	fExifIFD 			 (0)
	,	fGPSInfo 			 (0)
	,	fInteroperabilityIFD (0)
	,	fKodakDCRPrivateIFD  (0)
	,	fKodakKDCPrivateIFD  (0)
		
	,	fXMPCount  (0)
	,	fXMPOffset (0)
		
	,	fIPTC_NAA_Count  (0)
	,	fIPTC_NAA_Offset (0)
	
	,	fMakerNoteCount  (0)
	,	fMakerNoteOffset (0)
	,	fMakerNoteSafety (0)
	
	,	fDNGVersion         (0)
	,	fDNGBackwardVersion (0)
	
	,	fUniqueCameraModel    ()
	,	fLocalizedCameraModel ()
	
	,	fColorPlanes (0)
	
	,	fCalibrationIlluminant1 (lsUnknown)
	,	fCalibrationIlluminant2 (lsUnknown)

	,	fColorMatrix1 ()
	,	fColorMatrix2 ()
		
	,	fCameraCalibration1 ()
	,	fCameraCalibration2 ()
		
	,	fReductionMatrix1 ()
	,	fReductionMatrix2 ()
		
	,	fAnalogBalance ()
		
	,	fAsShotNeutral ()
		
	,	fAsShotWhiteXY ()
	
	,	fBaselineExposure    (0, 1)
	,	fBaselineNoise       (1, 1)
	,	fBaselineSharpness   (1, 1)
	,	fLinearResponseLimit (1, 1)
	,	fShadowScale         (1, 1)
	
	,	fDNGPrivateDataCount  (0)
	,	fDNGPrivateDataOffset (0)
	
	,	fRawDataUniqueID ()
	
	,	fOriginalRawFileName ()
		
	,	fOriginalRawFileDataCount  (0)
	,	fOriginalRawFileDataOffset (0)
		
	,	fAsShotICCProfileCount  (0)
	,	fAsShotICCProfileOffset (0)
	
	,	fAsShotPreProfileMatrix ()
		
	,	fCurrentICCProfileCount  (0)
	,	fCurrentICCProfileOffset (0)
	
	,	fCurrentPreProfileMatrix ()
	
	,	fColorimetricReference (crSceneReferred)

	{
	
	}
	
/*****************************************************************************/

dng_shared::~dng_shared ()
	{
	
	}
		
/*****************************************************************************/

bool dng_shared::ParseTag (dng_stream &stream,
						   dng_exif &exif,
						   uint32 parentCode,
						   bool /* isMainIFD */,
						   uint32 tagCode,
						   uint32 tagType,
						   uint32 tagCount,
						   uint32 tagOffset,
						   int32 /* offsetDelta */)
	{
	
	if (parentCode == 0)
		{
		
		if (Parse_ifd0 (stream,
						exif,
						parentCode,
						tagCode,
						tagType,
						tagCount,
						tagOffset))
			{
			
			return true;
			
			}

		}
		
	if (parentCode == 0 ||
		parentCode == tcExifIFD)
		{
		
		if (Parse_ifd0_exif (stream,
							 exif,
						 	 parentCode,
						 	 tagCode,
						 	 tagType,
						 	 tagCount,
						 	 tagOffset))
			{
			
			return true;
			
			}

		}
		
	return false;
		
	}

/*****************************************************************************/

// Parses tags that should only appear in IFD 0.

bool dng_shared::Parse_ifd0 (dng_stream &stream,
							 dng_exif & /* exif */,
							 uint32 parentCode,
							 uint32 tagCode,
							 uint32 tagType,
							 uint32 tagCount,
							 uint32 tagOffset)
	{
	
	switch (tagCode)
		{
			
		case tcXMP:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttByte);
			
			fXMPCount  = tagCount;
			fXMPOffset = fXMPCount ? tagOffset : 0;
			
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("XMP: Count = %u, Offset = %u\n",
						(unsigned) fXMPCount,
						(unsigned) fXMPOffset);
						
				if (fXMPCount)
					{
						
					DumpXMP (stream, fXMPCount);
					
					}
						
				}
				
			#endif
				
			break;
			
			}

		case tcIPTC_NAA:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttLong, ttAscii);
			
			fIPTC_NAA_Count  = tagCount * TagTypeSize (tagType);
			fIPTC_NAA_Offset = fIPTC_NAA_Count ? tagOffset : 0;
			
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("IPTC/NAA: Count = %u, Offset = %u\n",
						(unsigned) fIPTC_NAA_Count,
						(unsigned) fIPTC_NAA_Offset);
						
				if (fIPTC_NAA_Count)
					{
						
					DumpHexAscii (stream, fIPTC_NAA_Count);
					
					}
						
				}
				
			#endif
				
			break;
			
			}

		case tcExifIFD:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttLong, ttIFD);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fExifIFD = stream.TagValue_uint32 (tagType);
			
			#if qDNGValidate
			
			if (gVerbose)
				{
				printf ("ExifIFD: %u\n", (unsigned) fExifIFD);
				}
				
			#endif
				
			break;
			
			}
		
		case tcGPSInfo:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttLong, ttIFD);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fGPSInfo = stream.TagValue_uint32 (tagType);
			
			#if qDNGValidate
			
			if (gVerbose)
				{
				printf ("GPSInfo: %u\n", (unsigned) fGPSInfo);
				}
				
			#endif
				
			break;
			
			}
				
		case tcKodakDCRPrivateIFD:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttLong, ttIFD);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fKodakDCRPrivateIFD = stream.TagValue_uint32 (tagType);
			
			#if qDNGValidate
			
			if (gVerbose)
				{
				printf ("KodakDCRPrivateIFD: %u\n", (unsigned) fKodakDCRPrivateIFD);
				}
				
			#endif
				
			break;
			
			}
		
		case tcKodakKDCPrivateIFD:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttLong, ttIFD);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fKodakKDCPrivateIFD = stream.TagValue_uint32 (tagType);
			
			#if qDNGValidate
			
			if (gVerbose)
				{
				printf ("KodakKDCPrivateIFD: %u\n", (unsigned) fKodakKDCPrivateIFD);
				}
				
			#endif
				
			break;
			
			}
		
		case tcDNGVersion:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttByte);
			
			CheckTagCount (parentCode, tagCode, tagCount, 4);
			
			uint32 b0 = stream.Get_uint8 ();
			uint32 b1 = stream.Get_uint8 ();
			uint32 b2 = stream.Get_uint8 ();
			uint32 b3 = stream.Get_uint8 ();
			
			fDNGVersion = (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
			
			#if qDNGValidate
			
			if (gVerbose)
				{
				printf ("DNGVersion: %u.%u.%u.%u\n",
						(unsigned) b0,
						(unsigned) b1,
						(unsigned) b2,
						(unsigned) b3);
				}
				
			#endif
			
			break;
			
			}
				
		case tcDNGBackwardVersion:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttByte);
			
			CheckTagCount (parentCode, tagCode, tagCount, 4);
			
			uint32 b0 = stream.Get_uint8 ();
			uint32 b1 = stream.Get_uint8 ();
			uint32 b2 = stream.Get_uint8 ();
			uint32 b3 = stream.Get_uint8 ();
			
			fDNGBackwardVersion = (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
			
			#if qDNGValidate
			
			if (gVerbose)
				{
				printf ("DNGBackwardVersion: %u.%u.%u.%u\n", 
						(unsigned) b0, 
						(unsigned) b1, 
						(unsigned) b2, 
						(unsigned) b3);
				}
				
			#endif
			
			break;
			
			}
				
		case tcUniqueCameraModel:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttAscii);
			
			ParseStringTag (stream,
							parentCode,
							tagCode,
							tagCount,
							fUniqueCameraModel,
							false);
							
			bool didTrim = fUniqueCameraModel.TrimTrailingBlanks ();
			
			#if qDNGValidate
			
			if (didTrim)
				{
				
				ReportWarning ("UniqueCameraModel string has trailing blanks");
				
				}
			
			if (gVerbose)
				{
				
				printf ("UniqueCameraModel: ");
				
				DumpString (fUniqueCameraModel);
				
				printf ("\n");
				
				}
				
			#endif
			
			break;
			
			}

		case tcLocalizedCameraModel:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttAscii, ttByte);
			
			ParseStringTag (stream,
							parentCode,
							tagCode,
							tagCount,
							fLocalizedCameraModel,
							false,
							false);
			
			bool didTrim = fLocalizedCameraModel.TrimTrailingBlanks ();
			
			#if qDNGValidate
			
			if (didTrim)
				{
				
				ReportWarning ("LocalizedCameraModel string has trailing blanks");
				
				}
			
			if (gVerbose)
				{
				
				printf ("LocalizedCameraModel: ");
				
				DumpString (fLocalizedCameraModel);
				
				printf ("\n");
				
				}
				
			#endif
			
			break;
			
			}
			
		case tcColorMatrix1:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttSRational);
			
			if (fColorPlanes == 0)
				{
			
				fColorPlanes = tagCount / 3;
				
				if (fColorPlanes < 3)
					fColorPlanes = 3;
					
				if (fColorPlanes > kMaxColorPlanes)
					fColorPlanes = kMaxColorPlanes;
					
				}
				
			if (!CheckColorImage (parentCode, tagCode, fColorPlanes))
				return false;
				
			if (!ParseMatrixTag (stream,
								 parentCode,
								 tagCode,
								 tagType,
								 tagCount,
								 fColorPlanes,
								 3,
								 fColorMatrix1))
				return false;
				
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("ColorMatrix1:\n");
				
				DumpMatrix (fColorMatrix1);
								
				}
				
			#endif
				
			break;
			
			}

		case tcColorMatrix2:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttSRational);
			
			if (!CheckColorImage (parentCode, tagCode, fColorPlanes))
				return false;
				
			if (!ParseMatrixTag (stream,
								 parentCode,
								 tagCode,
								 tagType,
								 tagCount,
								 fColorPlanes,
								 3,
								 fColorMatrix2))
				return false;
				
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("ColorMatrix2:\n");
				
				DumpMatrix (fColorMatrix2);
								
				}
				
			#endif
				
			break;
			
			}

		case tcCameraCalibration1:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttSRational);
			
			if (!CheckColorImage (parentCode, tagCode, fColorPlanes))
				return false;
				
			if (!ParseMatrixTag (stream,
								 parentCode,
								 tagCode,
								 tagType,
								 tagCount,
								 fColorPlanes,
								 fColorPlanes,
								 fCameraCalibration1))
				return false;
				
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("CameraCalibration1:\n");
				
				DumpMatrix (fCameraCalibration1);
								
				}
				
			#endif
				
			break;
			
			}

		case tcCameraCalibration2:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttSRational);
			
			if (!CheckColorImage (parentCode, tagCode, fColorPlanes))
				return false;
				
			if (!ParseMatrixTag (stream,
								 parentCode,
								 tagCode,
								 tagType,
								 tagCount,
								 fColorPlanes,
								 fColorPlanes,
								 fCameraCalibration2))
				return false;
				
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("CameraCalibration2:\n");
				
				DumpMatrix (fCameraCalibration2);
								
				}
				
			#endif
				
			break;
			
			}

		case tcReductionMatrix1:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttSRational);
			
			if (!CheckColorImage (parentCode, tagCode, fColorPlanes))
				return false;
				
			if (!ParseMatrixTag (stream,
								 parentCode,
								 tagCode,
								 tagType,
								 tagCount,
								 3,
								 fColorPlanes,
								 fReductionMatrix1))
				return false;
				
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("ReductionMatrix1:\n");
				
				DumpMatrix (fReductionMatrix1);
								
				}
				
			#endif
				
			break;
			
			}

		case tcReductionMatrix2:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttSRational);
			
			if (!CheckColorImage (parentCode, tagCode, fColorPlanes))
				return false;
				
			if (!ParseMatrixTag (stream,
								 parentCode,
								 tagCode,
								 tagType,
								 tagCount,
								 3,
								 fColorPlanes,
								 fReductionMatrix2))
				return false;
				
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("ReductionMatrix2:\n");
				
				DumpMatrix (fReductionMatrix2);
								
				}
				
			#endif
				
			break;
			
			}

		case tcAnalogBalance:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttRational);
			
			if (!CheckColorImage (parentCode, tagCode, fColorPlanes))
				return false;
				
			if (!ParseVectorTag (stream,
								 parentCode,
								 tagCode,
								 tagType,
								 tagCount,
								 fColorPlanes,
								 fAnalogBalance))
				return false;
	
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("AnalogBalance:");
				
				DumpVector (fAnalogBalance);
								
				}
				
			#endif
				
			break;
			
			}
			
		case tcAsShotNeutral:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttRational);
			
			if (!CheckColorImage (parentCode, tagCode, fColorPlanes))
				return false;
				
			if (!ParseVectorTag (stream,
								 parentCode,
								 tagCode,
								 tagType,
								 tagCount,
								 fColorPlanes,
								 fAsShotNeutral))
				return false;
	
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("AsShotNeutral:");
				
				DumpVector (fAsShotNeutral);
								
				}
				
			#endif
				
			break;
			
			}
			
		case tcAsShotWhiteXY:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttRational);
			
			if (!CheckColorImage (parentCode, tagCode, fColorPlanes))
				return false;
				
			if (!CheckTagCount (parentCode, tagCode, tagCount, 2))
				return false;
				
			fAsShotWhiteXY.x = stream.TagValue_real64 (tagType);
			fAsShotWhiteXY.y = stream.TagValue_real64 (tagType);
			
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("AsShotWhiteXY: %0.4f %0.4f\n",
						fAsShotWhiteXY.x,
						fAsShotWhiteXY.y);
						
				}
				
			#endif
				
			break;
			
			}
			
		case tcBaselineExposure:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttSRational);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fBaselineExposure = stream.TagValue_srational (tagType);
			
			#if qDNGValidate
			
			if (gVerbose)
				{
				
				printf ("BaselineExposure: %+0.2f\n",
					    fBaselineExposure.As_real64 ());
					    
				}
				
			#endif
				
			break;
			
			}
			
		case tcBaselineNoise:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttRational);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fBaselineNoise = stream.TagValue_urational (tagType);
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("BaselineNoise: %0.2f\n",
						fBaselineNoise.As_real64 ());
						
				}
				
			#endif
				
			break;
			
			}
			
		case tcBaselineSharpness:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttRational);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fBaselineSharpness = stream.TagValue_urational (tagType);
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("BaselineSharpness: %0.2f\n",
					    fBaselineSharpness.As_real64 ());
				
				}
				
			#endif
				
			break;
			
			}
			
		case tcLinearResponseLimit:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttRational);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fLinearResponseLimit = stream.TagValue_urational (tagType);
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("LinearResponseLimit: %0.2f\n",
						fLinearResponseLimit.As_real64 ());
				
				}
				
			#endif
				
			break;
			
			}
			
		case tcShadowScale:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttRational);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fShadowScale = stream.TagValue_urational (tagType);
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("ShadowScale: %0.4f\n",
						fShadowScale.As_real64 ());
				
				}
				
			#endif
				
			break;
			
			}
			
		case tcDNGPrivateData:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttByte);
			
			fDNGPrivateDataCount  = tagCount;
			fDNGPrivateDataOffset = tagOffset;
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("DNGPrivateData: Count = %u, Offset = %u\n",
						(unsigned) fDNGPrivateDataCount,
						(unsigned) fDNGPrivateDataOffset);
						
				DumpHexAscii (stream, tagCount);
				
				}
				
			#endif
			
			break;
			
			}
			
		case tcMakerNoteSafety:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttShort);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fMakerNoteSafety = stream.TagValue_uint32 (tagType);
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("MakerNoteSafety: %s\n",
						LookupMakerNoteSafety (fMakerNoteSafety));
				
				}
				
			#endif
			
			break;
			
			}
			
		case tcCalibrationIlluminant1:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttShort);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fCalibrationIlluminant1 = stream.TagValue_uint32 (tagType);
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("CalibrationIlluminant1: %s\n",
						LookupLightSource (fCalibrationIlluminant1));
				
				}
				
			#endif
				
			break;
			
			}
			
		case tcCalibrationIlluminant2:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttShort);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fCalibrationIlluminant2 = stream.TagValue_uint32 (tagType);
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("CalibrationIlluminant2: %s\n",
						LookupLightSource (fCalibrationIlluminant2));
				
				}
				
			#endif
				
			break;
			
			}
			
		case tcRawDataUniqueID:
			{
			
			if (!CheckTagType (parentCode, tagCode, tagType, ttByte))
				return false;
				
			if (!CheckTagCount (parentCode, tagCode, tagCount, 16))
				return false;
				
			stream.Get (fRawDataUniqueID.data, 16);
				
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("RawDataUniqueID: <");
				
				for (uint32 j = 0; j < 16; j++)
					{
					printf ("%02x", fRawDataUniqueID.data [j]);
					}
					
				printf (">\n");
				
				}
				
			#endif
				
			break;
			
			}
			
		case tcOriginalRawFileName:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttAscii, ttByte);
			
			ParseStringTag (stream,
							parentCode,
							tagCode,
							tagCount,
							fOriginalRawFileName,
							false,
							false);
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("OriginalRawFileName: ");
				
				DumpString (fOriginalRawFileName);
				
				printf ("\n");
				
				}
				
			#endif
			
			break;
			
			}
			
		case tcOriginalRawFileData:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttUndefined);
			
			fOriginalRawFileDataCount  = tagCount;
			fOriginalRawFileDataOffset = tagOffset;
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("OriginalRawFileData: Count = %u, Offset = %u\n",
						(unsigned) fOriginalRawFileDataCount,
						(unsigned) fOriginalRawFileDataOffset);
						
				DumpHexAscii (stream, tagCount);
				
				}
				
			#endif
				
			break;
			
			}
			
		case tcAsShotICCProfile:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttUndefined);
			
			fAsShotICCProfileCount  = tagCount;
			fAsShotICCProfileOffset = tagOffset;
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("AsShotICCProfile: Count = %u, Offset = %u\n",
						(unsigned) fAsShotICCProfileCount,
						(unsigned) fAsShotICCProfileOffset);
						
				DumpHexAscii (stream, tagCount);
				
				}
				
			#endif
				
			break;
			
			}
			
		case tcAsShotPreProfileMatrix:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttSRational);
			
			if (!CheckColorImage (parentCode, tagCode, fColorPlanes))
				return false;
				
			uint32 rows = fColorPlanes;
			
			if (tagCount == fColorPlanes * 3)
				{
				rows = 3;
				}
			
			if (!ParseMatrixTag (stream,
								 parentCode,
								 tagCode,
								 tagType,
								 tagCount,
								 rows,
								 fColorPlanes,
								 fAsShotPreProfileMatrix))
				return false;
				
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("AsShotPreProfileMatrix:\n");
				
				DumpMatrix (fAsShotPreProfileMatrix);
								
				}
				
			#endif
				
			break;
			
			}
			
		case tcCurrentICCProfile:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttUndefined);
			
			fCurrentICCProfileCount  = tagCount;
			fCurrentICCProfileOffset = tagOffset;
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("CurrentICCProfile: Count = %u, Offset = %u\n",
						(unsigned) fCurrentICCProfileCount,
						(unsigned) fCurrentICCProfileOffset);
						
				DumpHexAscii (stream, tagCount);
				
				}
				
			#endif
				
			break;
			
			}
			
		case tcCurrentPreProfileMatrix:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttSRational);
			
			if (!CheckColorImage (parentCode, tagCode, fColorPlanes))
				return false;
				
			uint32 rows = fColorPlanes;
			
			if (tagCount == fColorPlanes * 3)
				{
				rows = 3;
				}
			
			if (!ParseMatrixTag (stream,
								 parentCode,
								 tagCode,
								 tagType,
								 tagCount,
								 rows,
								 fColorPlanes,
								 fCurrentPreProfileMatrix))
				return false;
				
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("CurrentPreProfileMatrix:\n");
				
				DumpMatrix (fCurrentPreProfileMatrix);
								
				}
				
			#endif
				
			break;
			
			}
			
		case tcColorimetricReference:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttShort);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fColorimetricReference = stream.TagValue_uint32 (tagType);
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("ColorimetricReference: %s\n",
						LookupColorimetricReference (fColorimetricReference));
				
				}
				
			#endif
				
			break;
			
			}
			
		default:
			{
			
			return false;
			
			}
			
		}
	
	return true;
	
	}
	
/*****************************************************************************/

// Parses tags that should only appear in IFD 0 or EXIF IFD.

bool dng_shared::Parse_ifd0_exif (dng_stream &stream,
								  dng_exif & /* exif */,
						  	   	  uint32 parentCode,
						  	      uint32 tagCode,
						  	      uint32 tagType,
						  	      uint32 tagCount,
						  	      uint32 tagOffset)
	{
	
	switch (tagCode)
		{
		
		case tcMakerNote:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttUndefined);
			
			fMakerNoteCount  = tagCount;
			fMakerNoteOffset = tagOffset;
			
			#if qDNGValidate

			if (gVerbose)
				{
				
				printf ("MakerNote: Count = %u, Offset = %u\n",
						(unsigned) fMakerNoteCount,
						(unsigned) fMakerNoteOffset);
						
				DumpHexAscii (stream, tagCount);
				
				}
				
			#endif
				
			break;
			
			}
			
		case tcInteroperabilityIFD:
			{
			
			CheckTagType (parentCode, tagCode, tagType, ttLong, ttIFD);
			
			CheckTagCount (parentCode, tagCode, tagCount, 1);
			
			fInteroperabilityIFD = stream.TagValue_uint32 (tagType);
			
			#if qDNGValidate

			if (gVerbose)
				{
				printf ("InteroperabilityIFD: %u\n", (unsigned) fInteroperabilityIFD);
				}
				
			#endif
			
			break;
			
			}
			
		default:
			{
			
			return false;
			
			}
			
		}
		
	return true;
	
	}
							   
/*****************************************************************************/

void dng_shared::PostParse (dng_host & /* host */,
							dng_exif & /* exif */)
	{
	
	// Fill in default values for DNG images.
	
	if (fDNGVersion != 0)
		{
		
		// Support for DNG versions before 1.0.0.0.
		
		if (fDNGVersion < 0x01000000)
			{
			
			#if qDNGValidate
			
			ReportWarning ("DNGVersion less than 1.0.0.0");
						 
			#endif
			
			// The CalibrationIlluminant tags were added just before
			// DNG version 1.0.0.0, and were hardcoded before that.
			
			fCalibrationIlluminant1 = lsStandardLightA;
			fCalibrationIlluminant1 = lsD65;
			
			fDNGVersion = 0x01000000;

			}
		
		// Default value for DNGBackwardVersion tag.
		
		if (fDNGBackwardVersion == 0)
			{
			
			fDNGBackwardVersion = fDNGVersion & 0xFFFF0000;
			
			}
	
		// Check DNGBackwardVersion value.
		
		if (fDNGBackwardVersion < 0x01000000)
			{
			
			#if qDNGValidate
			
			ReportWarning ("DNGBackwardVersion less than 1.0.0.0");
						 
			#endif
			
			fDNGBackwardVersion = 0x01000000;
				
			}

		if (fDNGBackwardVersion > fDNGVersion)
			{
			
			#if qDNGValidate
			
			ReportWarning ("DNGBackwardVersion > DNGVersion");
						 
			#endif
			
			fDNGBackwardVersion = fDNGVersion;
					
			}

		// Check UniqueCameraModel.
		
		if (fUniqueCameraModel.IsEmpty ())
			{
			
			#if qDNGValidate
			
			ReportWarning ("Missing or invalid UniqueCameraModel");
						 
			#endif
			
			fUniqueCameraModel.Set ("Digital Negative");
			
			}
		
		// If we don't know the color depth yet, it must be a monochrome DNG.
		
		if (fColorPlanes == 0)
			{
			
			fColorPlanes = 1;
			
			}
			
		// Check color info.
		
		if (fColorPlanes > 1)
			{
			
			// Check illuminant pair.
			
			if (fColorMatrix2.NotEmpty ())
				{
				
				if (fCalibrationIlluminant1 == lsUnknown ||
					fCalibrationIlluminant2 == lsUnknown ||
					fCalibrationIlluminant1 == fCalibrationIlluminant2)
					{
						
					#if qDNGValidate
			
					ReportWarning ("Invalid CalibrationIlluminant pair");
								 
					#endif
								 
					fColorMatrix2 = dng_matrix ();
				
					}

				}
				
			// If the colorimetric reference is the ICC profile PCS, then the
			// data must already be white balanced.  The "AsShotWhiteXY" is required
			// to be the ICC Profile PCS white point.
			
			if (fColorimetricReference == crICCProfilePCS)
				{
				
				if (fAsShotNeutral.NotEmpty ())
					{
					
					#if qDNGValidate
				
					ReportWarning ("AsShotNeutral not allowed for this "
								   "ColorimetricReference value");
								 
					#endif
					
					fAsShotNeutral.Clear ();
					
					}
					
				dng_xy_coord pcs = PCStoXY ();
				
				#if qDNGValidate
					
				if (fAsShotWhiteXY.IsValid ())
					{
					
					if (Abs_real64 (fAsShotWhiteXY.x - pcs.x) > 0.01 ||
						Abs_real64 (fAsShotWhiteXY.y - pcs.y) > 0.01)
						{
						
						ReportWarning ("AsShotWhiteXY does not match the ICC Profile PCS");

						}
						
					}
									 
				#endif
				
				fAsShotWhiteXY = pcs;

				}
				
			else
				{
				
				// Warn if both AsShotNeutral and AsShotWhiteXY are specified.
					
				if (fAsShotNeutral.NotEmpty () && fAsShotWhiteXY.IsValid ())
					{
						
					#if qDNGValidate
				
					ReportWarning ("Both AsShotNeutral and AsShotWhiteXY included");
								 
					#endif
					
					fAsShotWhiteXY = dng_xy_coord ();
									 
					}
					
				// Warn if neither AsShotNeutral nor AsShotWhiteXY are specified.
					
				#if qDNGValidate
				
				if (fAsShotNeutral.IsEmpty () && !fAsShotWhiteXY.IsValid ())
					{
					
					ReportWarning ("Neither AsShotNeutral nor AsShotWhiteXY included",
								   "legal but not recommended");
								 
					}
							
				#endif
					
				}
				
			}
			
		// Check BaselineNoise.

		if (fBaselineNoise.As_real64 () <= 0.0)
			{
			
			#if qDNGValidate
			
			ReportWarning ("Invalid BaselineNoise");
						 
			#endif
			
			fBaselineNoise = dng_urational (1, 1);
							 
			}
			
		// Check BaselineSharpness.
		
		if (fBaselineSharpness.As_real64 () <= 0.0)
			{
			
			#if qDNGValidate
			
			ReportWarning ("Invalid BaselineSharpness");
						 
			#endif
			
			fBaselineSharpness = dng_urational (1, 1);
							 
			}
			
		// Check LinearResponseLimit.
		
		if (fLinearResponseLimit.As_real64 () < 0.5 ||
			fLinearResponseLimit.As_real64 () > 1.0)
			{
			
			#if qDNGValidate
			
			ReportWarning ("Invalid LinearResponseLimit");
						 
			#endif
			
			fLinearResponseLimit = dng_urational (1, 1);
							 
			}
			
		// Check ShadowScale.
		
		if (fShadowScale.As_real64 () <= 0.0)
			{
			
			#if qDNGValidate
			
			ReportWarning ("Invalid ShadowScale");
						 
			#endif
							 
			fShadowScale = dng_urational (1, 1);
							 
			}
		
		}
	
	}
							   
/*****************************************************************************/

bool dng_shared::IsValidDNG ()
	{
	
	// Check DNGVersion value.
	
	if (fDNGVersion < 0x01000000)
		{
		
		#if qDNGValidate
		
		ReportError ("Missing or invalid DNGVersion");
					 
		#endif
					 
		return false;
			
		}
		
	// Check DNGBackwardVersion value.
	
	if (fDNGBackwardVersion > 0x01010000)
		{
		
		#if qDNGValidate
		
		ReportError ("DNGBackwardVersion (or DNGVersion) is too high");
					 
		#endif
		
		return false;
			
		}
		
	// Check color transform info.
	
	if (fColorPlanes > 1)
		{
		
		try
			{
			
			(void) Invert (fColorMatrix1);
			
			}
			
		catch (...)
			{
			
			#if qDNGValidate
		
			ReportError ("ColorMatrix1 is not invertable");
						 
			#endif
		
			return false;
		
			}
			
		dng_matrix xyzToCamera1 = fColorMatrix1;
		
		if (fCameraCalibration1.NotEmpty ())
			{
			
			try
				{
				
				(void) Invert (fCameraCalibration1);
				
				}
				
			catch (...)
				{
				
				#if qDNGValidate
		
				ReportError ("CameraCalibration1 is not invertable");
							 
				#endif
							 
				return false;
			
				}
				
			xyzToCamera1 = fCameraCalibration1 * xyzToCamera1;
			
			}
			
		dng_matrix analogBalance;
		
		if (fAnalogBalance.NotEmpty ())
			{
			
			analogBalance = fAnalogBalance.AsDiagonal ();
			
			try
				{
				
				(void) Invert (analogBalance);
				
				}
				
			catch (...)
				{
				
				#if qDNGValidate
		
				ReportError ("AnalogBalance is not invertable");
							 
				#endif
							 
				return false;
			
				}
				
			xyzToCamera1 = analogBalance * xyzToCamera1;

			}
			
		try
			{
			
			if (fReductionMatrix1.NotEmpty ())
				{
				
				(void) Invert (xyzToCamera1, fReductionMatrix1);
				
				}
				
			else
				{
			
				(void) Invert (xyzToCamera1);
				
				}
			
			}
			
		catch (...)
			{
				
			#if qDNGValidate
		
			ReportError ("Color transform 1 is not invertable");
						 
			#endif
						 
			return false;
		
			}
			
		if (fColorMatrix2.NotEmpty ())
			{
			
			try
				{
				
				(void) Invert (fColorMatrix2);
				
				}
				
			catch (...)
				{
				
				#if qDNGValidate
		
				ReportError ("ColorMatrix2 is not invertable");
							 
				#endif
							 
				return false;
			
				}
				
			dng_matrix xyzToCamera2 = fColorMatrix2;
			
			if (fCameraCalibration2.NotEmpty ())
				{
				
				try
					{
					
					(void) Invert (fCameraCalibration2);
					
					}
					
				catch (...)
					{
					
					#if qDNGValidate
		
					ReportError ("CameraCalibration2 is not invertable");
								 
					#endif
								 
					return false;
				
					}
					
				xyzToCamera2 = fCameraCalibration2 * xyzToCamera2;
				
				}
			
			if (analogBalance.NotEmpty ())
				{
				
				xyzToCamera2 = analogBalance * xyzToCamera2;

				}
	
			try
				{
				
				if (fReductionMatrix2.NotEmpty ())
					{
					
					(void) Invert (xyzToCamera2, fReductionMatrix2);
					
					}
					
				else
					{
				
					(void) Invert (xyzToCamera2);
					
					}

				}
				
			catch (...)
				{
					
				#if qDNGValidate
		
				ReportError ("Color transform 2 is not invertable");
							 
				#endif
							 
				return false;
			
				}
				
			}
			
		}
			
	return true;
	
	}
	
/*****************************************************************************/

/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_negative.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#include "dng_negative.h"

#include "dng_abort_sniffer.h"
#include "dng_bottlenecks.h"
#include "dng_camera_profile.h"
#include "dng_color_spec.h"
#include "dng_exceptions.h"
#include "dng_host.h"
#include "dng_image.h"
#include "dng_image_writer.h"
#include "dng_info.h"
#include "dng_linearization_info.h"
#include "dng_memory_stream.h"
#include "dng_mosaic_info.h"
#include "dng_simple_image.h"
#include "dng_tag_codes.h"
#include "dng_tag_values.h"
#include "dng_tile_iterator.h"
#include "dng_xmp.h"

/*****************************************************************************/

dng_negative::dng_negative (dng_memory_allocator &allocator)

	:	fAllocator (allocator)
	
	,	fModelName		    	()
	,	fLocalName		    	()
	,	fHasBaseOrientation 	(false)
	,	fBaseOrientation    	()
	,	fDefaultCropSizeH   	()
	,	fDefaultCropSizeV		()
	,	fDefaultCropOriginH 	(0, 1)
	,	fDefaultCropOriginV 	(0, 1)
	,	fDefaultScaleH      	(1, 1)
	,	fDefaultScaleV			(1, 1)
	,	fBestQualityScale		(1, 1)
	,	fRawToFullScaleH		(1.0)
	,	fRawToFullScaleV		(1.0)
	,	fBaselineNoise	    	(100, 100)
	,	fBaselineExposure		(  0, 100)
	,	fBaselineSharpness		(100, 100)
	,	fChromaBlurRadius		()
	,	fAntiAliasStrength		(100, 100)
	,	fLinearResponseLimit	(100, 100)
	,	fShadowScale			(1, 1)
	,	fColorimetricReference  (crSceneReferred)
	,	fColorChannels			(0)
	,	fAnalogBalance			()
	,	fCameraNeutral			()
	,	fCameraWhiteXY			()
	,	fEmbeddedCameraProfile	()
	,	fRawDataUniqueID    	()
	,	fOriginalRawFileName	()
	,	fHasOriginalRawFileData (false)
	,	fOriginalRawFileData    ()
	,	fDNGPrivateData			()
	,	fIsMakerNoteSafe		(false)
	,	fMakerNote				()
	,	fExif			    	()
	,	fIPTCBlock          	()
	,	fIPTCOffset				(dng_stream::kInvalidOffset)
	,	fXMP			    	()
	,	fXMPinSidecar	    	(false)
	,	fXMPisNewer		    	(false)
	,	fLinearizationInfo  	()
	,	fMosaicInfo         	()
	,	fStage1Image        	()
	,	fStage2Image        	()
	,	fStage3Image        	()
	,	fStage3Gain				(1.0)
	,	fIsPreview				(false)
	
	{

	}

/*****************************************************************************/

dng_negative::~dng_negative ()
	{
	
	}

/******************************************************************************/

void dng_negative::Initialize ()
	{
	
	fExif.Reset (MakeExif ());
	
	fXMP.Reset (MakeXMP ());
	
	}

/******************************************************************************/

dng_negative * dng_negative::Make (dng_memory_allocator &allocator)
	{
	
	AutoPtr<dng_negative> result (new dng_negative (allocator));
	
	if (!result.Get ())
		{
		ThrowMemoryFull ();
		}
	
	result->Initialize ();
	
	return result.Release ();
	
	}

/******************************************************************************/

void dng_negative::SetBaseOrientation (const dng_orientation &orientation)
	{
	
	fHasBaseOrientation = true;
	
	fBaseOrientation = orientation;
	
	}
		
/******************************************************************************/

dng_orientation dng_negative::Orientation () const
	{
	
	return BaseOrientation ();
	
	}
		
/******************************************************************************/

void dng_negative::ApplyOrientation (const dng_orientation &orientation)
	{
	
	fBaseOrientation += orientation;
	
	fXMP->SetOrientation (fBaseOrientation);

	}
				  
/******************************************************************************/

void dng_negative::SetAnalogBalance (const dng_vector &b)
	{
	
	real64 minEntry = b.MinEntry ();
	
	if (b.NotEmpty () && minEntry > 0.0)
		{
		
		fAnalogBalance = b;
	
		fAnalogBalance.Scale (1.0 / minEntry);
		
		fAnalogBalance.Round (1000000.0);
		
		}
		
	else
		{
		
		fAnalogBalance.Clear ();
		
		}
		
	}
					  
/*****************************************************************************/

real64 dng_negative::AnalogBalance (uint32 channel) const
	{
	
	ASSERT (channel < ColorChannels (), "Channel out of bounds");
	
	if (channel < fAnalogBalance.Count ())
		{
		
		return fAnalogBalance [channel];
		
		}
		
	return 1.0;
	
	}
		
/*****************************************************************************/

dng_urational dng_negative::AnalogBalanceR (uint32 channel) const
	{
	
	dng_urational result;
	
	result.Set_real64 (AnalogBalance (channel), 1000000);
	
	return result;
	
	}

/******************************************************************************/

void dng_negative::SetCameraNeutral (const dng_vector &n)
	{
	
	real64 maxEntry = n.MaxEntry ();
		
	if (n.NotEmpty () && maxEntry > 0.0)
		{
		
		fCameraNeutral = n;
	
		fCameraNeutral.Scale (1.0 / maxEntry);
		
		fCameraNeutral.Round (1000000.0);
		
		}
		
	else
		{
		
		fCameraNeutral.Clear ();
		
		}

	}
	  
/*****************************************************************************/

dng_urational dng_negative::CameraNeutralR (uint32 channel) const
	{
	
	dng_urational result;
	
	result.Set_real64 (CameraNeutral () [channel], 1000000);
	
	return result;
	
	}

/******************************************************************************/

void dng_negative::SetCameraWhiteXY (const dng_xy_coord &coord)
	{
	
	if (coord.IsValid ())
		{
		
		fCameraWhiteXY.x = Round_int32 (coord.x * 1000000.0) / 1000000.0;
		fCameraWhiteXY.y = Round_int32 (coord.y * 1000000.0) / 1000000.0;
		
		}
		
	else
		{
		
		fCameraWhiteXY.Clear ();
		
		}
	
	}
		
/*****************************************************************************/

const dng_xy_coord & dng_negative::CameraWhiteXY () const
	{
	
	ASSERT (HasCameraWhiteXY (), "Using undefined CameraWhiteXY");

	return fCameraWhiteXY;
	
	}
							   
/*****************************************************************************/

void dng_negative::GetCameraWhiteXY (dng_urational &x,
							   		 dng_urational &y) const
	{
	
	dng_xy_coord coord = CameraWhiteXY ();
	
	x.Set_real64 (coord.x, 1000000);
	y.Set_real64 (coord.y, 1000000);
	
	}
		
/*****************************************************************************/

void dng_negative::SetEmbeddedCameraProfile (AutoPtr<dng_camera_profile> &profile)
	{
	
	fEmbeddedCameraProfile.Reset (profile.Release ());
	
	fEmbeddedCameraProfile->SetName (kProfileName_Embedded);
	
	}
		
/*****************************************************************************/

void dng_negative::ClearEmbeddedCameraProfile ()
	{
	
	fEmbeddedCameraProfile.Reset ();
	
	}
							   
/*****************************************************************************/

const dng_camera_profile * dng_negative::CameraProfileToEmbed () const
	{
	
	return EmbeddedCameraProfile ();
	
	}
							   
/*****************************************************************************/

dng_color_spec * dng_negative::MakeColorSpec (const char * /* name */) const
	{
	
	dng_color_spec *spec = new dng_color_spec (*this,
											   EmbeddedCameraProfile ());
											   
	if (!spec)
		{
		ThrowMemoryFull ();
		}
		
	return spec;
	
	}
							   
/*****************************************************************************/

// If the raw data unique ID is missing, compute one based on a MD5 hash of
// the stage 1 image.

void dng_negative::FindRawDataUniqueID (dng_host &host)
	{
	
	const dng_image *image = fStage1Image.Get ();
	
	ASSERT (image, "FindRawDataUniqueID without stage 1 image");
		
	if (fRawDataUniqueID.IsNull () && image)
		{
		
		MD5Fingerprint printer;
		
		dng_pixel_buffer buffer;
		
		buffer.fPlane  = 0;
		buffer.fPlanes = image->Planes ();
		
		buffer.fRowStep   = image->Planes () * image->Width ();
		buffer.fColStep   = image->Planes ();
		buffer.fPlaneStep = 1;
		
		buffer.fPixelType = image->PixelType ();
		buffer.fPixelSize = image->PixelSize ();
		
		const uint32 kBufferRows = 16;
		
		uint32 bufferBytes = kBufferRows * buffer.fRowStep * buffer.fPixelSize;
		
		AutoPtr<dng_memory_block> bufferData (host.Allocate (bufferBytes));
		
		buffer.fData = bufferData->Buffer ();
		
		dng_rect area;
		
		dng_tile_iterator iter (dng_point (kBufferRows,
										   image->Width ()),
								image->Bounds ());
								
		while (iter.GetOneTile (area))
			{
			
			host.SniffForAbort ();
			
			buffer.fArea = area;
			
			image->Get (buffer);
			
			uint32 count = buffer.fArea.H () *
						   buffer.fRowStep *
						   buffer.fPixelSize;

			printer.Process (buffer.fData,
							 count);
			
			}
			
		printer.Process (ModelName ().Get    (),
						 ModelName ().Length () + 1);
		
		fRawDataUniqueID = printer.Result ();
	
		}
	
	}

/******************************************************************************/

dng_rect dng_negative::DefaultCropArea (real64 scaleH,
				    	  			    real64 scaleV) const
	{
	
	const dng_image *image = Stage3Image ();
	
	ASSERT (image, "DefaultCropArea on NULL image");
	
	dng_point scaledSize;
	
	scaledSize.h = Round_int32 (image->Width  () * scaleH);
	scaledSize.v = Round_int32 (image->Height () * scaleV);
			
	// First compute the area using simple rounding.
		
	dng_rect result;
	
	result.l = Round_int32 (fDefaultCropOriginH.As_real64 () * fRawToFullScaleH * scaleH);
	result.t = Round_int32 (fDefaultCropOriginV.As_real64 () * fRawToFullScaleV * scaleV);
	
	result.r = result.l + Round_int32 (fDefaultCropSizeH.As_real64 () * fRawToFullScaleH * scaleH);
	result.b = result.t + Round_int32 (fDefaultCropSizeV.As_real64 () * fRawToFullScaleV * scaleV);
	
	// Sometimes the simple rounding causes the resulting default crop
	// area to slide off the scaled image area.  So we force this not
	// to happen.
	
	if (result.r > scaledSize.h)
		{
		result.l -= result.r - scaledSize.h;
		result.r  = scaledSize.h;
		}
		
	if (result.b > scaledSize.v)
		{
		result.t -= result.b - scaledSize.v;
		result.b  = scaledSize.v;
		}
		
	return result;
	
	}

/******************************************************************************/

void dng_negative::SetShadowScale (const dng_urational &scale)
	{
	
	if (scale.d > 0)
		{
		
		real64 s = scale.As_real64 ();
		
		if (s > 0.0 && s <= 1.0)
			{
	
			fShadowScale = scale;
			
			}
		
		}
	
	}
			
/******************************************************************************/

dng_memory_block * dng_negative::BuildExifBlock (const dng_resolution *resolution,
												 bool includeIPTC) const
	{
	
	dng_memory_stream stream (Allocator ());
	
		{
	
		// Create the main IFD
											 
		tiff_directory mainIFD;
		
		// Optionally include the resolution tags.
		
		dng_resolution res;
		
		if (resolution)
			{
			res = *resolution;
			}
	
		tag_urational tagXResolution (tcXResolution, res.fXResolution);
		tag_urational tagYResolution (tcYResolution, res.fYResolution);
		
		tag_uint16 tagResolutionUnit (tcResolutionUnit, res.fResolutionUnit);
		
		if (resolution)
			{
			mainIFD.Add (&tagXResolution   );
			mainIFD.Add (&tagYResolution   );
			mainIFD.Add (&tagResolutionUnit);
			}

		// Optionally include IPTC block.
		
		tag_iptc tagIPTC (IPTCData   (),
						  IPTCLength ());
			
		if (includeIPTC && tagIPTC.Count ())
			{
			
			mainIFD.Add (&tagIPTC);
			
			}
							
		// Exif tags.
		
		exif_tag_set exifSet (mainIFD,
							  *GetExif (),
							  IsMakerNoteSafe (),
							  MakerNoteData   (),
							  MakerNoteLength (),
							  false);
							  
		// Figure out the Exif IFD offset.
		
		exifSet.Locate (8 + mainIFD.Size ());
			
		// Write TIFF Header.
		
		stream.SetWritePosition (0);
		
		stream.Put_uint16 (stream.BigEndian () ? byteOrderMM : byteOrderII);
		
		stream.Put_uint16 (42);
		
		stream.Put_uint32 (8);
		
		// Write the IFDs.
		
		mainIFD.Put (stream);
		
		exifSet.Put (stream);
		
		// Trim the file to this length.
		
		stream.Flush ();
		
		stream.SetLength (stream.Position ());
		
		}
		
	return stream.AsMemoryBlock (Allocator ());
		
	}
			
/******************************************************************************/

void dng_negative::SetIPTC (AutoPtr<dng_memory_block> &block, uint32 offset)
	{
	
	fIPTCBlock.Reset (block.Release ());
	
	fIPTCOffset = offset;
	
	}
					  
/******************************************************************************/

void dng_negative::SetIPTC (AutoPtr<dng_memory_block> &block)
	{
	
	SetIPTC (block, dng_stream::kInvalidOffset);
	
	}
					  
/******************************************************************************/

void dng_negative::ClearIPTC ()
	{
	
	fIPTCBlock.Reset ();
	
	fIPTCOffset = dng_stream::kInvalidOffset;
	
	}
					  
/*****************************************************************************/

const void * dng_negative::IPTCData () const
	{
	
	if (fIPTCBlock.Get ())
		{
		
		return fIPTCBlock->Buffer ();
		
		}
		
	return NULL;
	
	}

/*****************************************************************************/

uint32 dng_negative::IPTCLength () const
	{
	
	if (fIPTCBlock.Get ())
		{
		
		return fIPTCBlock->LogicalSize ();
		
		}
		
	return 0;
	
	}
		
/*****************************************************************************/

uint32 dng_negative::IPTCOffset () const
	{
	
	if (fIPTCBlock.Get ())
		{
		
		return fIPTCOffset;
		
		}
		
	return dng_stream::kInvalidOffset;
	
	}
		
/*****************************************************************************/

dng_fingerprint dng_negative::IPTCDigest () const
	{
	
	if (IPTCLength ())
		{
		
		MD5Fingerprint printer;
		
		const uint8 *data = (const uint8 *) IPTCData ();
		
		uint32 count = IPTCLength ();
		
		// Because of some stupid ways of storing the IPTC data, the IPTC
		// data might be padded with up to three zeros.  Don't include
		// these zero pad bytes in the digest.
		
		uint32 removed = 0;
		
		while ((removed < 3) && (count > 0) && (data [count - 1] == 0))
			{
			removed++;
			count--;
			}
		
		printer.Process (data, count);
						 
		return printer.Result ();
			
		}
	
	return dng_fingerprint ();
	
	}
		
/******************************************************************************/

void dng_negative::RebuildIPTC ()
	{
	
	ClearIPTC ();
	
	fXMP->RebuildIPTC (*this);
	
	dng_fingerprint digest = IPTCDigest ();
	
	fXMP->SetIPTCDigest (digest);
	
	}
			  
/*****************************************************************************/

bool dng_negative::SetXMP (dng_host &host,
						   const void *buffer,
					 	   uint32 count,
					 	   bool xmpInSidecar,
					 	   bool xmpIsNewer)
	{
	
	bool result = false;
	
	try
		{
		
		AutoPtr<dng_xmp> tempXMP (MakeXMP ());
		
		tempXMP->Parse (host, buffer, count);
		
		fXMP.Reset (tempXMP.Release ());
		
		fXMPinSidecar = xmpInSidecar;
		
		fXMPisNewer = xmpIsNewer;
		
		result = true;
		
		}
		
	catch (dng_exception &except)
		{
		
		// Don't ignore transient errors.
		
		if (host.IsTransientError (except.ErrorCode ()))
			{
			
			throw;
			
			}
			
		// Eat other parsing errors.
		
		}
		
	catch (...)
		{
		
		// Eat unknown parsing exceptions.
		
		}
	
	return result;
	
	}
		
/******************************************************************************/

void dng_negative::SetActiveArea (const dng_rect &area)
	{
	
	NeedLinearizationInfo ();
	
	dng_linearization_info &info = *fLinearizationInfo.Get ();
								    
	info.fActiveArea = area;
	
	}

/******************************************************************************/

void dng_negative::SetMaskedAreas (uint32 count,
							 	   const dng_rect *area)
	{
	
	ASSERT (count <= kMaxMaskedAreas, "Too many masked areas");
	
	NeedLinearizationInfo ();
	
	dng_linearization_info &info = *fLinearizationInfo.Get ();
								    
	info.fMaskedAreaCount = Min_uint32 (count, kMaxMaskedAreas);
	
	for (uint32 index = 0; index < info.fMaskedAreaCount; index++)
		{
		
		info.fMaskedArea [index] = area [index];
		
		}
		
	}
		
/*****************************************************************************/

void dng_negative::SetLinearization (AutoPtr<dng_memory_block> &curve)
	{
	
	NeedLinearizationInfo ();
	
	dng_linearization_info &info = *fLinearizationInfo.Get ();
								    
	info.fLinearizationTable.Reset (curve.Release ());
	
	}
		
/*****************************************************************************/

void dng_negative::SetBlackLevel (real64 black,
								  int32 plane)
	{

	NeedLinearizationInfo ();
	
	dng_linearization_info &info = *fLinearizationInfo.Get ();
								    
	info.fBlackLevelRepeatRows = 1;
	info.fBlackLevelRepeatCols = 1;
	
	if (plane < 0)
		{
		
		for (uint32 j = 0; j < kMaxSamplesPerPixel; j++)
			{
			
			info.fBlackLevel [0] [0] [j] = black;
			
			}
		
		}
		
	else
		{
		
		info.fBlackLevel [0] [0] [plane] = black;
			
		}
	
	info.RoundBlacks ();
		
	}
		
/*****************************************************************************/

void dng_negative::SetQuadBlacks (real64 black0,
						    	  real64 black1,
						    	  real64 black2,
						    	  real64 black3)
	{
	
	NeedLinearizationInfo ();
	
	dng_linearization_info &info = *fLinearizationInfo.Get ();
								    
	info.fBlackLevelRepeatRows = 2;
	info.fBlackLevelRepeatCols = 2;
	
	for (uint32 j = 0; j < kMaxSamplesPerPixel; j++)
		{
		
		info.fBlackLevel [0] [0] [j] = black0;
		info.fBlackLevel [0] [1] [j] = black1;
		info.fBlackLevel [1] [0] [j] = black2;
		info.fBlackLevel [1] [1] [j] = black3;
		
		}
		
	info.RoundBlacks ();
		
	}

/*****************************************************************************/

void dng_negative::SetRowBlacks (const real64 *blacks,
				   		   		 uint32 count)
	{
	
	if (count)
		{
	
		NeedLinearizationInfo ();
		
		dng_linearization_info &info = *fLinearizationInfo.Get ();
		
		uint32 byteCount = count * sizeof (real64);
									    
		info.fBlackDeltaV.Reset (Allocator ().Allocate (byteCount));
		
		DoCopyBytes (blacks,
					 info.fBlackDeltaV->Buffer (),
					 byteCount);
		
		info.RoundBlacks ();
		
		}
		
	else if (fLinearizationInfo.Get ())
		{
		
		dng_linearization_info &info = *fLinearizationInfo.Get ();
		
		info.fBlackDeltaV.Reset ();
	
		}
								    
	}
							
/*****************************************************************************/

void dng_negative::SetColumnBlacks (const real64 *blacks,
					  		  	    uint32 count)
	{
	
	if (count)
		{
	
		NeedLinearizationInfo ();
		
		dng_linearization_info &info = *fLinearizationInfo.Get ();
		
		uint32 byteCount = count * sizeof (real64);
									    
		info.fBlackDeltaH.Reset (Allocator ().Allocate (byteCount));
		
		DoCopyBytes (blacks,
					 info.fBlackDeltaH->Buffer (),
					 byteCount);
		
		info.RoundBlacks ();
		
		}
		
	else if (fLinearizationInfo.Get ())
		{
		
		dng_linearization_info &info = *fLinearizationInfo.Get ();
									    
		info.fBlackDeltaH.Reset ();
	
		}
								    
	}
							
/*****************************************************************************/

uint32 dng_negative::WhiteLevel (uint32 plane) const
	{
	
	if (fLinearizationInfo.Get ())
		{
		
		const dng_linearization_info &info = *fLinearizationInfo.Get ();
									    
		return Round_uint32 (info.fWhiteLevel [plane]);
									    
		}
		
	return LinearRange16 ();
	
	}
							
/*****************************************************************************/

void dng_negative::SetWhiteLevel (uint32 white,
							      int32 plane)
	{

	NeedLinearizationInfo ();
	
	dng_linearization_info &info = *fLinearizationInfo.Get ();
								    
	if (plane < 0)
		{
		
		for (uint32 j = 0; j < kMaxSamplesPerPixel; j++)
			{
			
			info.fWhiteLevel [j] = (real64) white;
			
			}
		
		}
		
	else
		{
		
		info.fWhiteLevel [plane] = (real64) white;
			
		}
	
	}

/******************************************************************************/

void dng_negative::SetColorKeys (ColorKeyCode color0,
						   		 ColorKeyCode color1,
						   		 ColorKeyCode color2,
						   		 ColorKeyCode color3)
	{
	
	NeedMosaicInfo ();
	
	dng_mosaic_info &info = *fMosaicInfo.Get ();
							 
	info.fCFAPlaneColor [0] = color0;
	info.fCFAPlaneColor [1] = color1;
	info.fCFAPlaneColor [2] = color2;
	info.fCFAPlaneColor [3] = color3;
	
	}

/******************************************************************************/

void dng_negative::SetBayerMosaic (uint32 phase)
	{
	
	NeedMosaicInfo ();
	
	dng_mosaic_info &info = *fMosaicInfo.Get ();
	
	ColorKeyCode color0 = (ColorKeyCode) info.fCFAPlaneColor [0];
	ColorKeyCode color1 = (ColorKeyCode) info.fCFAPlaneColor [1];
	ColorKeyCode color2 = (ColorKeyCode) info.fCFAPlaneColor [2];
	
	info.fCFAPatternSize = dng_point (2, 2);
	
	switch (phase)
		{
		
		case 0:
			{
			info.fCFAPattern [0] [0] = color1;
			info.fCFAPattern [0] [1] = color0;
			info.fCFAPattern [1] [0] = color2;
			info.fCFAPattern [1] [1] = color1;
			break;
			}
			
		case 1:
			{
			info.fCFAPattern [0] [0] = color0;
			info.fCFAPattern [0] [1] = color1;
			info.fCFAPattern [1] [0] = color1;
			info.fCFAPattern [1] [1] = color2;
			break;
			}
			
		case 2:
			{
			info.fCFAPattern [0] [0] = color2;
			info.fCFAPattern [0] [1] = color1;
			info.fCFAPattern [1] [0] = color1;
			info.fCFAPattern [1] [1] = color0;
			break;
			}
			
		case 3:
			{
			info.fCFAPattern [0] [0] = color1;
			info.fCFAPattern [0] [1] = color2;
			info.fCFAPattern [1] [0] = color0;
			info.fCFAPattern [1] [1] = color1;
			break;
			}
			
		}
		
	info.fColorPlanes = 3;
	
	info.fCFALayout = 1;
	
	}

/******************************************************************************/

void dng_negative::SetFujiMosaic (uint32 phase)
	{
	
	NeedMosaicInfo ();
	
	dng_mosaic_info &info = *fMosaicInfo.Get ();
	
	ColorKeyCode color0 = (ColorKeyCode) info.fCFAPlaneColor [0];
	ColorKeyCode color1 = (ColorKeyCode) info.fCFAPlaneColor [1];
	ColorKeyCode color2 = (ColorKeyCode) info.fCFAPlaneColor [2];
	
	info.fCFAPatternSize = dng_point (2, 4);
	
	switch (phase)
		{
		
		case 0:
			{
			info.fCFAPattern [0] [0] = color0;
			info.fCFAPattern [0] [1] = color1;
			info.fCFAPattern [0] [2] = color2;
			info.fCFAPattern [0] [3] = color1;
			info.fCFAPattern [1] [0] = color2;
			info.fCFAPattern [1] [1] = color1;
			info.fCFAPattern [1] [2] = color0;
			info.fCFAPattern [1] [3] = color1;
			break;
			}
			
		case 1:
			{
			info.fCFAPattern [0] [0] = color2;
			info.fCFAPattern [0] [1] = color1;
			info.fCFAPattern [0] [2] = color0;
			info.fCFAPattern [0] [3] = color1;
			info.fCFAPattern [1] [0] = color0;
			info.fCFAPattern [1] [1] = color1;
			info.fCFAPattern [1] [2] = color2;
			info.fCFAPattern [1] [3] = color1;
			break;
			}
			
		}
		
	info.fColorPlanes = 3;
	
	info.fCFALayout = 2;
			
	}

/******************************************************************************/

void dng_negative::SetQuadMosaic (uint32 pattern)
	{
	
	// The pattern of the four colors is assumed to be repeat at least every two
	// columns and eight rows.  The pattern is encoded as a 32-bit integer,
	// with every two bits encoding a color, in scan order for two columns and
	// eight rows (lsb is first).  The usual color coding is:
	//
	// 0 = Green
	// 1 = Magenta
	// 2 = Cyan
	// 3 = Yellow
	//
	// Examples:
	//
	//	PowerShot 600 uses 0xe1e4e1e4:
	//
	//	  0 1 2 3 4 5
	//	0 G M G M G M
	//	1 C Y C Y C Y
	//	2 M G M G M G
	//	3 C Y C Y C Y
	//
	//	PowerShot A5 uses 0x1e4e1e4e:
	//
	//	  0 1 2 3 4 5
	//	0 C Y C Y C Y
	//	1 G M G M G M
	//	2 C Y C Y C Y
	//	3 M G M G M G
	//
	//	PowerShot A50 uses 0x1b4e4b1e:
	//
	//	  0 1 2 3 4 5
	//	0 C Y C Y C Y
	//	1 M G M G M G
	//	2 Y C Y C Y C
	//	3 G M G M G M
	//	4 C Y C Y C Y
	//	5 G M G M G M
	//	6 Y C Y C Y C
	//	7 M G M G M G
	//
	//	PowerShot Pro70 uses 0x1e4b4e1b:
	//
	//	  0 1 2 3 4 5
	//	0 Y C Y C Y C
	//	1 M G M G M G
	//	2 C Y C Y C Y
	//	3 G M G M G M
	//	4 Y C Y C Y C
	//	5 G M G M G M
	//	6 C Y C Y C Y
	//	7 M G M G M G
	//
	//	PowerShots Pro90 and G1 use 0xb4b4b4b4:
	//
	//	  0 1 2 3 4 5
	//	0 G M G M G M
	//	1 Y C Y C Y C

	NeedMosaicInfo ();
	
	dng_mosaic_info &info = *fMosaicInfo.Get ();
							 
	if (((pattern >> 16) & 0x0FFFF) != (pattern & 0x0FFFF))
		{
		info.fCFAPatternSize = dng_point (8, 2);
		}
		
	else if (((pattern >> 8) & 0x0FF) != (pattern & 0x0FF))
		{
		info.fCFAPatternSize = dng_point (4, 2);
		}
		
	else
		{
		info.fCFAPatternSize = dng_point (2, 2);
		}
		
	for (int32 row = 0; row < info.fCFAPatternSize.v; row++)
		{
		
		for (int32 col = 0; col < info.fCFAPatternSize.h; col++)
			{
			
			uint32 index = (pattern >> ((((row << 1) & 14) + (col & 1)) << 1)) & 3;
			
			info.fCFAPattern [row] [col] = info.fCFAPlaneColor [index];
			
			}
			
		}

	info.fColorPlanes = 4;
	
	info.fCFALayout = 1;
			
	}
	
/******************************************************************************/

void dng_negative::SetGreenSplit (uint32 split)
	{
	
	NeedMosaicInfo ();
	
	dng_mosaic_info &info = *fMosaicInfo.Get ();
	
	info.fBayerGreenSplit = split;
	
	}

/*****************************************************************************/

void dng_negative::Parse (dng_host &host,
						  dng_stream &stream,
						  dng_info &info)
	{
	
	// Shared info.
	
	dng_shared &shared = *(info.fShared.Get ());
	
	// Find IFD holding the main raw information.
	
	dng_ifd &rawIFD = *info.fIFD [info.fMainIndex].Get ();
	
	// Model name.
	
	SetModelName (shared.fUniqueCameraModel.Get ());
	
	// Localized model name.
	
	SetLocalName (shared.fLocalizedCameraModel.Get ());
	
	// Base orientation.
	
		{
	
		uint32 orientation = info.fIFD [0]->fOrientation;
		
		if (orientation >= 1 && orientation <= 8)
			{
			
			SetBaseOrientation (dng_orientation::TIFFtoDNG (orientation));
						
			}
			
		}
		
	// Default crop rectangle.
	
	SetDefaultCropSize (rawIFD.fDefaultCropSizeH,
					    rawIFD.fDefaultCropSizeV);

	SetDefaultCropOrigin (rawIFD.fDefaultCropOriginH,
						  rawIFD.fDefaultCropOriginV);
						        
	// Default scale.
		
	SetDefaultScale (rawIFD.fDefaultScaleH,
					 rawIFD.fDefaultScaleV);
	
	// Best quality scale.
	
	SetBestQualityScale (rawIFD.fBestQualityScale);
	
	// Baseline noise.

	SetBaselineNoise (shared.fBaselineNoise.As_real64 ());
	
	// Baseline exposure.
	
	SetBaselineExposure (shared.fBaselineExposure.As_real64 ());

	// Baseline sharpness.
	
	SetBaselineSharpness (shared.fBaselineSharpness.As_real64 ());

	// Chroma blur radius.
	
	SetChromaBlurRadius (rawIFD.fChromaBlurRadius);

	// Anti-alias filter strength.
	
	SetAntiAliasStrength (rawIFD.fAntiAliasStrength);
		
	// Linear response limit.
	
	SetLinearResponseLimit (shared.fLinearResponseLimit.As_real64 ());
	
	// Shadow scale.
	
	SetShadowScale (shared.fShadowScale);
	
	// Colorimetric reference.
	
	SetColorimetricReference (shared.fColorimetricReference);
	
	// Color channels.
		
	SetColorChannels (shared.fColorPlanes);
	
	// Analog balance.
	
	if (shared.fAnalogBalance.NotEmpty ())
		{
		
		SetAnalogBalance (shared.fAnalogBalance);
		
		}
		
	// Embedded camera profile.
	
	if (host.NeedsMeta () && shared.fColorPlanes > 1)
		{
		
		AutoPtr<dng_camera_profile> profile (new dng_camera_profile ());
		
		profile->Parse (host, stream, info);
		
		SetEmbeddedCameraProfile (profile);
		
		}
			
	// Raw data unique ID.
	
	if (shared.fRawDataUniqueID.IsValid ())
		{
		
		SetRawDataUniqueID (shared.fRawDataUniqueID);
		
		}
			
	// Original raw file name.
	
	if (shared.fOriginalRawFileName.NotEmpty ())
		{
		
		SetOriginalRawFileName (shared.fOriginalRawFileName.Get ());
		
		}
		
	// Original raw file data.
	
	if (shared.fOriginalRawFileDataCount)
		{
		
		SetHasOriginalRawFileData (true);
					
		if (host.KeepOriginalFile ())
			{
			
			uint32 count = shared.fOriginalRawFileDataCount;
			
			AutoPtr<dng_memory_block> block (host.Allocate (count));
			
			stream.SetReadPosition (shared.fOriginalRawFileDataOffset);
		
			stream.Get (block->Buffer (), count);
						
			SetOriginalRawFileData (block);
			
			}
			
		}
			
	// DNG private data.
	
	if (shared.fDNGPrivateDataCount && host.KeepDNGPrivate ())
		{
		
		uint32 length = shared.fDNGPrivateDataCount;
		
		AutoPtr<dng_memory_block> block (host.Allocate (length));
		
		stream.SetReadPosition (shared.fDNGPrivateDataOffset);
			
		stream.Get (block->Buffer (), length);
							
		SetPrivateData (block);
			
		}
		
	// Hand off EXIF metadata to negative.
	
	fExif.Reset (info.fExif.Release ());
	
	// Parse linearization info.
	
	NeedLinearizationInfo ();
	
	fLinearizationInfo.Get ()->Parse (host,
								      stream,
								      info);
								      
	// Parse mosaic info.
	
	if (rawIFD.fPhotometricInterpretation == piCFA)
		{
	
		NeedMosaicInfo ();
		
		fMosaicInfo.Get ()->Parse (host,
							       stream,
							       info);
							  
		}
						  
	}

/*****************************************************************************/

void dng_negative::PostParse (dng_host &host,
						  	  dng_stream &stream,
						  	  dng_info &info)
	{
	
	// Shared info.
	
	dng_shared &shared = *(info.fShared.Get ());
	
	if (host.NeedsMeta ())
		{
		
		// MakerNote.
		
		if (shared.fMakerNoteCount)
			{
			
			// See if we know if the MakerNote is safe or not.
			
			SetMakerNoteSafety (shared.fMakerNoteSafety == 1);
			
			// If the MakerNote is safe, preserve it as a MakerNote.
			
			if (IsMakerNoteSafe ())
				{

				AutoPtr<dng_memory_block> block (host.Allocate (shared.fMakerNoteCount));
				
				stream.SetReadPosition (shared.fMakerNoteOffset);
					
				stream.Get (block->Buffer (), shared.fMakerNoteCount);
									
				SetMakerNote (block);
							
				}
			
			}
		
		// IPTC metadata.
		
		if (shared.fIPTC_NAA_Count)
			{
			
			AutoPtr<dng_memory_block> block (host.Allocate (shared.fIPTC_NAA_Count));
			
			stream.SetReadPosition (shared.fIPTC_NAA_Offset);
			
			uint32 iptcOffset = stream.PositionInOriginalFile();
			
			stream.Get (block->Buffer      (), 
						block->LogicalSize ());
			
			SetIPTC (block, iptcOffset);
							
			}
		
		// XMP metadata.
		
		if (shared.fXMPCount)
			{
			
			AutoPtr<dng_memory_block> block (host.Allocate (shared.fXMPCount));
			
			stream.SetReadPosition (shared.fXMPOffset);
			
			stream.Get (block->Buffer      (),
						block->LogicalSize ());
						
			SetXMP (host,
					block->Buffer      (),
					block->LogicalSize ());
			
			}
				
		// Color info.
		
		if (!IsMonochrome ())
			{
			
			// If the ColorimetricReference is the ICC profile PCS,
			// then the data must be already be white balanced to the
			// ICC profile PCS white point.
			
			if (ColorimetricReference () == crICCProfilePCS)
				{
				
				ClearCameraNeutral ();
				
				SetCameraWhiteXY (PCStoXY ());
				
				}
				
			else
				{
				  		    
				// AsShotNeutral.
				
				if (shared.fAsShotNeutral.Count () == ColorChannels ())
					{
					
					SetCameraNeutral (shared.fAsShotNeutral);
										
					}
					
				// AsShotWhiteXY.
				
				if (shared.fAsShotWhiteXY.IsValid () && !HasCameraNeutral ())
					{
					
					SetCameraWhiteXY (shared.fAsShotWhiteXY);
					
					}
					
				}
				
			}
					
		}
	
	}
							
/*****************************************************************************/

void dng_negative::SynchronizeMetadata ()
	{
	
	fXMP->IngestIPTC (*this, fXMPisNewer);
		
	fXMP->SyncExif (*fExif.Get ());
	
	fXMP->SyncOrientation (*this, fXMPinSidecar);
	
	}
					
/*****************************************************************************/

void dng_negative::UpdateDateTime (const dng_date_time &dt,
								   int32 tzHour)
	{
	
	fExif->UpdateDateTime (dt, tzHour);
	
	fXMP->UpdateDateTime (dt, tzHour);
	
	}
					
/*****************************************************************************/

void dng_negative::UpdateDateTimeToNow ()
	{
	
	dng_date_time dt;
	
	int32 tzHour = 0x7FFFFFFF;
	
	CurrentDateTimeAndZone (dt, tzHour);
	
	UpdateDateTime (dt, tzHour);
	
	}
					
/*****************************************************************************/

bool dng_negative::SetFourColorBayer ()
	{
	
	if (ColorChannels () != 3)
		{
		return false;
		}
		
	if (!fMosaicInfo.Get ())
		{
		return false;
		}
		
	if (!fMosaicInfo.Get ()->SetFourColorBayer ())
		{
		return false;
		}
		
	SetColorChannels (4);
	
	if (fCameraNeutral.Count () == 3)
		{
		
		dng_vector n (4);
		
		n [0] = fCameraNeutral [0];
		n [1] = fCameraNeutral [1];
		n [2] = fCameraNeutral [2];
		n [3] = fCameraNeutral [1];
		
		fCameraNeutral = n;
		
		}
	
	if (fEmbeddedCameraProfile.Get ())
		{
		fEmbeddedCameraProfile->SetFourColorBayer ();
		}
		
	return true;
	
	}
					
/*****************************************************************************/

const dng_image & dng_negative::RawImage () const
	{
	
	if (fStage1Image.Get ())
		{
		return *fStage1Image.Get ();
		}
		
	if (fStage2Image.Get ())
		{
		return *fStage2Image.Get ();
		}
		
	ASSERT (fStage3Image.Get (),
		    "dng_negative::RawImage with no raw image");
		    
	return *fStage3Image.Get ();
	
	}
			
/*****************************************************************************/

dng_image * dng_negative::MakeImage (const dng_rect &bounds,
				  		  			 uint32 planes,
				  		  			 uint32 pixelType,
				  		  			 uint32 pixelRange) const
	{
	
	dng_image *image = new dng_simple_image (bounds,
											 planes,
											 pixelType,
											 pixelRange,
											 Allocator ());

	if (!image)
		{
		ThrowMemoryFull ();
		}
		
	return image;
	
	}

/*****************************************************************************/

void dng_negative::ReadStage1Image (dng_host &host,
									dng_stream &stream,
									dng_info &info)
	{
	
	dng_ifd &rawIFD = *info.fIFD [info.fMainIndex].Get ();
	
	fStage1Image.Reset (MakeImage (rawIFD.Bounds (),
								   rawIFD.fSamplesPerPixel,
								   rawIFD.PixelType (),
								   0));
					
	rawIFD.ReadImage (host,
					  stream,
					  *fStage1Image.Get ());							 

	}
					
/*****************************************************************************/

void dng_negative::SetStage1Image (AutoPtr<dng_image> &image)
	{
	
	fStage1Image.Reset (image.Release ());
	
	}

/*****************************************************************************/

uint16 dng_negative::LinearRange16 () const
	{
	
	return 0xFFFF;
	
	}

/*****************************************************************************/

void dng_negative::DoBuildStage2 (dng_host &host,
								  uint32 pixelType)
	{
	
	dng_image &stage1 = *fStage1Image.Get ();
		
	dng_linearization_info &info = *fLinearizationInfo.Get ();
	
	fStage2Image.Reset (MakeImage (info.fActiveArea.Size (),
								   stage1.Planes (),
								   pixelType,
								   pixelType == ttShort ? LinearRange16 ()
								   						: 0));
								   
	info.Linearize (host,
					stage1,
					*fStage2Image.Get ());
							 
	}
									   
/*****************************************************************************/

void dng_negative::BuildStage2Image (dng_host &host,
									 uint32 pixelType)
	{
	
	// Finalize linearization info.
	
		{
	
		NeedLinearizationInfo ();
	
		dng_linearization_info &info = *fLinearizationInfo.Get ();
		
		info.PostParse (host, *this);
		
		}
	
	// Perform the linearization.
	
	DoBuildStage2 (host,
			       pixelType);
	
	// Delete the stage1 image now if we are not keeping it around.
	
	if (!host.KeepStage1 ())
		{
		
		ClearStage1 ();
		
		}
		
	}
									  
/*****************************************************************************/

void dng_negative::ClearStage1 ()
	{
	
	fStage1Image.Reset ();
	
	// If we are not keeping the stage 1 image, then the linearization
	// information is now useless.
	
	ClearLinearizationInfo ();
		
	}
									  
/*****************************************************************************/

void dng_negative::DoBuildStage3 (dng_host &host,
								  uint32 minSize,
								  int32 srcPlane)
	{
	
	dng_image &stage2 = *fStage2Image.Get ();
		
	dng_mosaic_info &info = *fMosaicInfo.Get ();
	
	dng_point downScale = info.DownScale (minSize);
	
	if (downScale != dng_point (1, 1))
		{
		SetIsPreview (true);
		}
	
	dng_point dstSize = info.DstSize (downScale);
			
	fStage3Image.Reset (MakeImage (dng_rect (dstSize),
								   info.fColorPlanes,
								   stage2.PixelType (),
								   stage2.PixelRange ()));

	if (srcPlane < 0 || srcPlane >= (int32) stage2.Planes ())
		{
		srcPlane = 0;
		}
				
	info.Interpolate (host,
					  stage2,
					  *fStage3Image.Get (),
					  downScale,
					  srcPlane);

	}
									   
/*****************************************************************************/

// Interpolate and merge a multi-channel CFA image.

void dng_negative::DoMergeStage3 (dng_host &host)
	{
	
	// The DNG SDK does not provide multi-channel CFA image merging code.
	// It just grabs the first channel and uses that.
	
	DoBuildStage3 (host,
				   host.MinimumSize (),
				   0);
				   
	// Just grabbing the first channel would often result in the very
	// bright image using the baseline exposure value.
	
	fStage3Gain = pow (2.0, BaselineExposure ());
	
	}
									   
/*****************************************************************************/

void dng_negative::BuildStage3Image (dng_host &host,
									 int32 srcPlane)
	{
	
	// Finalize the mosaic information.
	
	dng_mosaic_info *info = fMosaicInfo.Get ();
	
	if (info)
		{
		
		info->PostParse (host, *this);
		
		}
		
	// If we don't have a mosaic pattern, then just move the stage 2
	// image on to stage 3.
	
	if (!info || !info->IsColorFilterArray ())
		{
		
		fStage3Image.Reset (fStage2Image.Release ());
		
		}
		
	else
		{
		
		// Remember the size of the stage 2 image.
		
		dng_point stage2_size = fStage2Image->Size ();
		
		// Special case multi-channel CFA interpolation.
		
		if ((fStage2Image->Planes () > 1) && (srcPlane < 0))
			{
			
			DoMergeStage3 (host);
			
			}
			
		// Else do a single channel interpolation.
		
		else
			{
				
			DoBuildStage3 (host,
						   host.MinimumSize (),
						   srcPlane);
						   
			}
		
		// Calculate the ratio of the stage 3 image size to stage 2 image size.
		
		dng_point stage3_size = fStage3Image->Size ();
		
		fRawToFullScaleH = (real64) stage3_size.h / (real64) stage2_size.h;
		fRawToFullScaleV = (real64) stage3_size.v / (real64) stage2_size.v;
		
		}
		
	// Delete the stage2 image if we are done with it.
	
	if (!host.KeepStage2 ())
		{
		
		ClearStage2 ();
				
		}
		
	}
		
/*****************************************************************************/

void dng_negative::ClearStage2 ()
	{
	
	fStage2Image.Reset ();
	
	// If we did not keep the stage 1 image, and we are not keeping
	// the stage 2 image either, then the mosaic information is now
	// useless.
	
	if (!fStage1Image.Get ())
		{
		
		ClearMosaicInfo ();
		
		// To support saving linear DNG files, to need to account for
		// and upscaling during interpolation.

		if (fRawToFullScaleH > 1.0)
			{
			
			uint32 adjust = Round_uint32 (fRawToFullScaleH);
			
			fDefaultCropSizeH  .n *= adjust;
			fDefaultCropOriginH.n *= adjust;
			fDefaultScaleH     .d *= adjust;
			
			fRawToFullScaleH /= (real64) adjust;
			
			}
		
		if (fRawToFullScaleV > 1.0)
			{
			
			uint32 adjust = Round_uint32 (fRawToFullScaleV);
			
			fDefaultCropSizeV  .n *= adjust;
			fDefaultCropOriginV.n *= adjust;
			fDefaultScaleV     .d *= adjust;
			
			fRawToFullScaleV /= (real64) adjust;
			
			}

		}
		
	}
									  
/*****************************************************************************/

void dng_negative::ClearStage3 ()
	{
	
	fStage3Image.Reset ();
	
	}
	
/*****************************************************************************/

dng_exif * dng_negative::MakeExif ()
	{
	
	dng_exif *exif = new dng_exif ();
	
	if (!exif)
		{
		ThrowMemoryFull ();
		}
		
	return exif;
	
	}
		
/*****************************************************************************/

dng_xmp * dng_negative::MakeXMP ()
	{
	
	dng_xmp *xmp = new dng_xmp (Allocator ());
	
	if (!xmp)
		{
		ThrowMemoryFull ();
		}
		
	return xmp;
	
	}
		
/*****************************************************************************/

dng_linearization_info * dng_negative::MakeLinearizationInfo ()
	{
	
	dng_linearization_info *info = new dng_linearization_info ();
	
	if (!info)
		{
		ThrowMemoryFull ();
		}
		
	return info;
	
	}

/*****************************************************************************/

void dng_negative::NeedLinearizationInfo ()
	{
	
	if (!fLinearizationInfo.Get ())
		{
	
		fLinearizationInfo.Reset (MakeLinearizationInfo ());
		
		}
	
	}

/*****************************************************************************/

dng_mosaic_info * dng_negative::MakeMosaicInfo ()
	{
	
	dng_mosaic_info *info = new dng_mosaic_info ();
	
	if (!info)
		{
		ThrowMemoryFull ();
		}
		
	return info;
	
	}

/*****************************************************************************/

void dng_negative::NeedMosaicInfo ()
	{
	
	if (!fMosaicInfo.Get ())
		{
	
		fMosaicInfo.Reset (MakeMosaicInfo ());
		
		}
	
	}

/*****************************************************************************/

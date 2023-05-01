/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_ifd.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/** \file
 *  DNG image file directory support.
 */

/*****************************************************************************/

#ifndef __dng_ifd__
#define __dng_ifd__

/*****************************************************************************/

#include "dng_types.h"
#include "dng_rect.h"
#include "dng_shared.h"
#include "dng_stream.h"
#include "dng_sdk_limits.h"

/*****************************************************************************/

/// \brief Container for a single image file directory of a digital negative.
///
/// See \ref spec_dng "DNG 1.1.0 specification" for documentation of specific tags.

class dng_ifd
	{
	
	public:
	
		bool fUsesNewSubFileType;
	
		uint32 fNewSubFileType;
		
		uint32 fImageWidth;
		uint32 fImageLength;
		
		uint32 fBitsPerSample [kMaxSamplesPerPixel];
		
		uint32 fCompression;
		
		uint32 fPredictor;
		
		uint32 fPhotometricInterpretation;
		
		uint32 fFillOrder;
		
		uint32 fOrientation;
		
		uint32 fSamplesPerPixel;
		
		uint32 fPlanarConfiguration;
		
		real64 fXResolution;
		real64 fYResolution;
		
		uint32 fResolutionUnit;
		
		bool fUsesStrips;
		bool fUsesTiles;

		uint32 fTileWidth;
		uint32 fTileLength;
		
		enum
			{
			kMaxTileInfo = 32
			};
		
		uint32 fTileOffsetsType;
		uint32 fTileOffsetsCount;
		uint32 fTileOffsetsOffset;
		uint32 fTileOffset [kMaxTileInfo];
		
		uint32 fTileByteCountsType;
		uint32 fTileByteCountsCount;
		uint32 fTileByteCountsOffset;
		uint32 fTileByteCount [kMaxTileInfo];

		uint32 fSubIFDsCount;
		uint32 fSubIFDsOffset;
		
		uint32 fExtraSamplesCount;
		uint32 fExtraSamples [kMaxSamplesPerPixel];
		
		uint32 fSampleFormat [kMaxSamplesPerPixel];
		
		uint32 fJPEGTablesCount;
		uint32 fJPEGTablesOffset;
		
		uint32 fJPEGInterchangeFormat;
		uint32 fJPEGInterchangeFormatLength;

		real64 fYCbCrCoefficientR;
		real64 fYCbCrCoefficientG;
		real64 fYCbCrCoefficientB;
		
		uint32 fYCbCrSubSampleH;
		uint32 fYCbCrSubSampleV;
		
		uint32 fYCbCrPositioning;
		
		real64 fReferenceBlackWhite [6];
		
		uint32 fCFARepeatPatternRows;
		uint32 fCFARepeatPatternCols;
		
		uint8 fCFAPattern [kMaxCFAPattern] [kMaxCFAPattern];
		
		uint8 fCFAPlaneColor [kMaxColorPlanes];
		
		uint32 fCFALayout;
		
		uint32 fLinearizationTableType;
		uint32 fLinearizationTableCount;
		uint32 fLinearizationTableOffset;
		
		uint32 fBlackLevelRepeatRows;
		uint32 fBlackLevelRepeatCols;
		
		real64 fBlackLevel [kMaxBlackPattern] [kMaxBlackPattern] [kMaxSamplesPerPixel];
		
		uint32 fBlackLevelDeltaHType;
		uint32 fBlackLevelDeltaHCount;
		uint32 fBlackLevelDeltaHOffset;
		
		uint32 fBlackLevelDeltaVType;
		uint32 fBlackLevelDeltaVCount;
		uint32 fBlackLevelDeltaVOffset;
		
		real64 fWhiteLevel [kMaxSamplesPerPixel];
		
		dng_urational fDefaultScaleH;
		dng_urational fDefaultScaleV;
		
		dng_urational fBestQualityScale;
		
		dng_urational fDefaultCropOriginH;
		dng_urational fDefaultCropOriginV;
		
		dng_urational fDefaultCropSizeH;
		dng_urational fDefaultCropSizeV;
		
		uint32 fBayerGreenSplit;
		
		dng_urational fChromaBlurRadius;
		
		dng_urational fAntiAliasStrength;
		
		dng_rect fActiveArea;
		
		uint32   fMaskedAreaCount;
		dng_rect fMaskedArea [kMaxMaskedAreas];
		
		bool fLosslessJPEGBug16;
		
		uint32 fSampleBitShift;
		
		uint32 fThisIFD;
		uint32 fNextIFD;

	public:
	
		dng_ifd ();
		
		virtual ~dng_ifd ();
		
		virtual bool ParseTag (dng_stream &stream,
							   uint32 parentCode,
							   uint32 tagCode,
							   uint32 tagType,
							   uint32 tagCount,
							   uint32 tagOffset);
							   
		virtual void PostParse ();
		
		virtual bool IsValidDNG (dng_shared &shared,
								 uint32 parentCode);

		dng_rect Bounds () const
			{
			return dng_rect (0,
							 0,
							 fImageLength,
							 fImageWidth);
			}
					      		 
		uint32 TilesAcross () const;
		
		uint32 TilesDown () const;
		
		uint32 TilesPerImage () const;
		
		dng_rect TileArea (uint32 rowIndex,
						   uint32 colIndex) const;
						   
		virtual uint32 TileByteCount (const dng_rect &tile) const;
		
		void SetSingleStrip ();
		
		void FindTileSize (uint32 bytesPerTile = 128 * 1024,
						   uint32 cellH = 16,
						   uint32 cellV = 16);
		
		void FindStripSize (uint32 bytesPerStrip = 128 * 1024,
						    uint32 cellV = 16);
		
		virtual uint32 PixelType () const;
		
		virtual bool IsBaselineJPEG () const;
		
		virtual bool CanRead () const;
		
		virtual void ReadImage (dng_host &host,
								dng_stream &stream,
								dng_image &image) const;
			
	protected:
							   
		virtual bool IsValidCFA (dng_shared &shared,
					      		 uint32 parentCode);
					      
	};
	
/*****************************************************************************/

#endif
	
/*****************************************************************************/

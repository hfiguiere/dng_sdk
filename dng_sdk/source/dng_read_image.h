/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_read_image.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/** \file
 * Support for DNG image reading.
 */

/*****************************************************************************/

#ifndef __dng_read_image__
#define __dng_read_image__

/*****************************************************************************/

#include "dng_auto_ptr.h"
#include "dng_classes.h"
#include "dng_memory.h"
#include "dng_types.h"

/*****************************************************************************/

/// \brief
///
///

class dng_read_image
	{
	
	protected:
	
		enum
			{
			
			// Target size for buffer used to copy data to the image.
			
			kImageBufferSize = 128 * 1024
			
			};
	
		AutoPtr<dng_memory_block> fCompressedBuffer;
	
		AutoPtr<dng_memory_block> fUncompressedBuffer;
	
	public:
	
		dng_read_image ();
		
		virtual ~dng_read_image ();
		
		///
		/// \param 

		virtual bool CanRead (const dng_ifd &ifd);
		
		///
		/// \param host Host used for memory allocation, progress updating, and abort testing.
		/// \param ifd
		/// \param stream Stream to read image data from.
		/// \param image Result image to populate.

		virtual void Read (dng_host &host,
						   const dng_ifd &ifd,
						   dng_stream &stream,
						   dng_image &image);
						   
	protected:
	
		virtual bool ReadUncompressed (dng_host &host,
									   const dng_ifd &ifd,
									   dng_stream &stream,
									   dng_image &image,
									   const dng_rect &tileArea,
									   uint32 plane,
									   uint32 planes);
	
		virtual bool ReadBaselineJPEG (dng_host &host,
									   const dng_ifd &ifd,
									   dng_stream &stream,
									   dng_image &image,
									   const dng_rect &tileArea,
									   uint32 plane,
									   uint32 planes,
									   uint32 tileByteCount);
	
		virtual bool ReadLosslessJPEG (dng_host &host,
									   const dng_ifd &ifd,
									   dng_stream &stream,
									   dng_image &image,
									   const dng_rect &tileArea,
									   uint32 plane,
									   uint32 planes,
									   uint32 tileByteCount);
									   
		virtual bool CanReadTile (const dng_ifd &ifd);
		
		virtual bool NeedsCompressedBuffer (const dng_ifd &ifd);
	
		virtual void ReadTile (dng_host &host,
							   const dng_ifd &ifd,
							   dng_stream &stream,
							   dng_image &image,
							   const dng_rect &tileArea,
							   uint32 plane,
							   uint32 planes,
							   uint32 tileByteCount);
	
	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/

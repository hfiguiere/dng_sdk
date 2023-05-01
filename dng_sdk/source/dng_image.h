/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_image.h#2 $ */ 
/* $DateTime: 2006/04/12 14:23:04 $ */
/* $Change: 216157 $ */
/* $Author: stern $ */

/** \file
 *  Support for working with image data in DNG SDK.
 */

/*****************************************************************************/

#ifndef __dng_image__
#define __dng_image__

/*****************************************************************************/

#include "dng_classes.h"
#include "dng_pixel_buffer.h"
#include "dng_point.h"
#include "dng_rect.h"
#include "dng_types.h"

/*****************************************************************************/

/// \brief Class to get resource acquisition is instantiation behavior for tile buffers. Can be dirty or constant tile access.

class dng_tile_buffer: public dng_pixel_buffer
	{
	
	protected:
	
		const dng_image &fImage;
	
	protected:
	
		/// Obtain a tile from an image.
		/// \param image Image tile will come from.
		/// \param tile Rectangle denoting extent of tile.
		/// \param dirty Flag indicating whether this is read-only or read-write acesss.

		dng_tile_buffer (const dng_image &image,
						 const dng_rect &tile,
						 bool dirty);
						 
		virtual ~dng_tile_buffer ();
	
	};

/*****************************************************************************/

/// \brief Class to get resource acquisition is instantiation behavior for constant (read-only) tile buffers.

class dng_const_tile_buffer: public dng_tile_buffer
	{
	
	public:
	
		/// Obtain a read-only tile from an image.
		/// \param image Image tile will come from.
		/// \param tile Rectangle denoting extent of tile.

		dng_const_tile_buffer (const dng_image &image,
							   const dng_rect &tile);
							   
		virtual ~dng_const_tile_buffer ();
	
	};
	
/*****************************************************************************/

/// \brief Class to get resource acquisition is instantiation behavior for dirty (writable) tile buffers.

class dng_dirty_tile_buffer: public dng_tile_buffer
	{
	
	public:
	
		/// Obtain a writable tile from an image.
		/// \param image Image tile will come from.
		/// \param tile Rectangle denoting extent of tile.

		dng_dirty_tile_buffer (dng_image &image,
							   const dng_rect &tile);
							   
		virtual ~dng_dirty_tile_buffer ();
	
	};
	
/*****************************************************************************/

/// \brief Base class for holding image data in DNG SDK. See dng_simple_image for derived class most often used in DNG SDK.

class dng_image
	{
	
	friend class dng_tile_buffer;
	
	protected:
	
		// Bounds for this image.
		
		dng_rect fBounds;
		
		// Number of image planes.
		
		uint32 fPlanes;
		
		// Basic pixel type (TIFF tag type code).
	
		uint32 fPixelType;
		
		// For integer pixel types, the maximum value. If zero, it means
		// the maximum value that fits in the integer size.  Ignored for
		// non-integer pixel types.
		
		uint32 fPixelRange;
		
	public:
	
		/// How to handle requests to get image areas outside the image bounds.

		enum edge_option
			{
			
			/// Leave edge pixels unchanged.		

			edge_none,
			
			/// Pad with zeros.
			
			edge_zero,
			
			/// Repeat edge pixels.
			
			edge_repeat,
			
			/// Repeat edge pixels, except for last plane which is zero padded.
			
			edge_repeat_zero_last
			
			};
	
	protected:
	
		dng_image (const dng_rect &bounds,
				   uint32 planes,
				   uint32 pixelType,
				   uint32 pixelRange);
		
	public:
	
		virtual ~dng_image ();
		
		/// Getter method for bounds of an image.
		
		const dng_rect & Bounds () const
			{
			return fBounds;
			}

		/// Getter method for size of an image.
			
		dng_point Size () const
			{
			return Bounds ().Size ();
			}
		
		/// Getter method for width of an image.

		uint32 Width () const
			{
			return Bounds ().W ();
			}

		/// Getter method for height of an image.
		
		uint32 Height () const
			{
			return Bounds ().H ();
			}
			
		/// Getter method for number of planes in an image.

		uint32 Planes () const
			{
			return fPlanes;
			}
			
		/// Getter for pixel type.
		/// \retval See dng_tagtypes.h . Valid values are ttByte, ttShort, ttSShort, ttLong, ttFloat .

		uint32 PixelType () const
			{
			return fPixelType;
			}
		
		/// Getter for pixel size.
		/// \retval Size, in bytes, of pixel type for this image .

		uint32 PixelSize () const;
		
		/// Getter for pixel range.
		/// For unsigned types, range is 0 to return value.
		/// For signed types, range is return value - 0x8000U.
		/// For ttFloat type, pixel range is 0.0 to 1.0 and this routine returns 1.

		uint32 PixelRange () const;

		/// Getter for best "tile stride" for accessing image.

		virtual dng_rect RepeatingTile () const;

		/// Get a pixel buffer of data on image with proper edge padding.
		/// \param buffer Receives resulting pixel buffer.
		/// \param edgeOption edge_option describing how to pad edges.
		/// \param repeatV Amount of repeated padding needed in vertical for edge_repeat and edge_repeat_zero_last edgeOption cases.
		/// \param repeatH Amount of repeated padding needed in horizontal for edge_repeat and edge_repeat_zero_last edgeOption cases.

		void Get (dng_pixel_buffer &buffer,
				  edge_option edgeOption = edge_none,
				  uint32 repeatV = 1,
				  uint32 repeatH = 1) const;

		/// Put a pixel buffer into image.
		/// \param buffer Pixel buffer to copy from.

		void Put (const dng_pixel_buffer &buffer);

		/// Shrink bounds of image to given rectangle.
		/// \param r Rectangle to crop to.

		virtual void Trim (const dng_rect &r);

		/// Rotate image to reflect given orientation change.
		/// \param orientation Directive to rotate image in a certain way.

		virtual void Rotate (const dng_orientation &orientation);
		
	protected:
	
		virtual void AcquireTileBuffer (dng_pixel_buffer &buffer,
										const dng_rect &tile,
										bool dirty) const;
	
		virtual void ReleaseTileBuffer (dng_pixel_buffer &buffer) const;
	
		virtual void DoGet (dng_pixel_buffer &buffer) const;
		
		virtual void DoPut (const dng_pixel_buffer &buffer);
		
		void GetRepeat (dng_pixel_buffer &buffer,
						const dng_rect &srcArea,
						const dng_rect &dstArea) const;
	
		void GetEdge (dng_pixel_buffer &buffer,
					  edge_option edgeOption,
					  const dng_rect &srcArea,
					  const dng_rect &dstArea) const;

	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/

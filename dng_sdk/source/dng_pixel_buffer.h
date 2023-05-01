/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_pixel_buffer.h#2 $ */ 
/* $DateTime: 2006/04/12 14:23:04 $ */
/* $Change: 216157 $ */
/* $Author: stern $ */

/** \file
 * Support for holding buffers of sample data.
 */

/*****************************************************************************/

#ifndef __dng_pixel_buffer__
#define __dng_pixel_buffer__

/*****************************************************************************/

#include "dng_assertions.h"
#include "dng_rect.h"
#include "dng_tag_types.h"

/*****************************************************************************/

/// Compute best set of step values for a given source and destination area and stride.

void OptimizeOrder (const void *&sPtr,
					void *&dPtr,
					uint32 sPixelSize,
					uint32 dPixelSize,
					uint32 &count0,
					uint32 &count1,
					uint32 &count2,
					int32 &sStep0,
					int32 &sStep1,
					int32 &sStep2,
					int32 &dStep0,
					int32 &dStep1,
					int32 &dStep2);

void OptimizeOrder (const void *&sPtr,
					uint32 sPixelSize,
					uint32 &count0,
					uint32 &count1,
					uint32 &count2,
					int32 &sStep0,
					int32 &sStep1,
					int32 &sStep2);

void OptimizeOrder (void *&dPtr,
					uint32 dPixelSize,
					uint32 &count0,
					uint32 &count1,
					uint32 &count2,
					int32 &dStep0,
					int32 &dStep1,
					int32 &dStep2);

/*****************************************************************************/

/// \brief Holds a buffer of pixel data with "pixel geometry" metadata.
///
/// The pixel geometry describes the layout in terms of how many planes, rows and columns
/// plus the steps (in bytes) between each column, row and plane.

class dng_pixel_buffer
	{
	
	public:
	
		// Area this buffer holds.
	
		dng_rect fArea;
		
		// Range of planes this buffer holds.
		
		uint32 fPlane;
		uint32 fPlanes;
		
		// Steps between pixels.
		
		int32 fRowStep;
		int32 fColStep;
		int32 fPlaneStep;
		
		// Basic pixel type (TIFF tag type code).
	
		uint32 fPixelType;
		
		// Size of pixel type in bytes.
		
		uint32 fPixelSize;
		
		// For integer pixel types, the maximum value. If zero, it means
		// the maximum value that fits in the integer size.  Ignored for
		// non-integer pixel types.
		
		uint32 fPixelRange;
		
		// Pointer to buffer's data.
		
		void *fData;
		
		// Do we have write-access to this data?
		
		bool fDirty;
		
	private:
	
		void * InternalPixel (int32 row,
							  int32 col,
					  	      uint32 plane = 0) const
			{
			
			return (void *)
				   (((uint8 *) fData) + fPixelSize *
					(fRowStep   * (row   - fArea.t) +
					 fColStep   * (col   - fArea.l) +
					 fPlaneStep * (plane - fPlane )));
			
			}
		
	public:
	
		dng_pixel_buffer ();
		
		dng_pixel_buffer (const dng_pixel_buffer &buffer);
		
		dng_pixel_buffer & operator= (const dng_pixel_buffer &buffer);

		virtual ~dng_pixel_buffer ();
		
		/// Get the range of pixel values.
		/// \retval Range of value a pixel can take. (Meaning [0, max] for unsigned case. Signed case is biased so [-32768, max - 32768].)

		uint32 PixelRange () const;

		/// Get read-only untyped (void *) pointer to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as void *.

		const void * ConstPixel (int32 row,
					  			 int32 col,
					  			 uint32 plane = 0) const
			{
			
			return InternalPixel (row, col, plane);
					 
			}
			
		/// Get a writable untyped (void *) pointer to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as void *.

		void * DirtyPixel (int32 row,
					  	   int32 col,
					  	   uint32 plane = 0)
			{
			
			ASSERT (fDirty, "Dirty access to const pixel buffer");
			
			return InternalPixel (row, col, plane);
			
			}

		/// Get read-only uint8 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as uint8 *.
			
		const uint8 * ConstPixel_uint8 (int32 row,
										int32 col,
										uint32 plane = 0) const
			{
			
			ASSERT (fPixelType == ttByte, "Pixel type access mismatch");

			return (const uint8 *) ConstPixel (row, col, plane);
			
			}
			
		/// Get a writable uint8 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as uint8 *.

		uint8 * DirtyPixel_uint8 (int32 row,
								  int32 col,
								  uint32 plane = 0)
			{
			
			ASSERT (fPixelType == ttByte, "Pixel type access mismatch");

			return (uint8 *) DirtyPixel (row, col, plane);
			
			}
			
		/// Get read-only int8 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as int8 *.

		const int8 * ConstPixel_int8 (int32 row,
									  int32 col,
									  uint32 plane = 0) const
			{
			
			ASSERT (fPixelType == ttSByte, "Pixel type access mismatch");

			return (const int8 *) ConstPixel (row, col, plane);
			
			}
			
		/// Get a writable int8 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as int8 *.

		int8 * DirtyPixel_int8 (int32 row,
								int32 col,
								uint32 plane = 0)
			{
			
			ASSERT (fPixelType == ttSByte, "Pixel type access mismatch");

			return (int8 *) DirtyPixel (row, col, plane);
			
			}
			
		/// Get read-only uint16 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as uint16 *.

		const uint16 * ConstPixel_uint16 (int32 row,
										  int32 col,
										  uint32 plane = 0) const
			{
			
			ASSERT (fPixelType == ttShort, "Pixel type access mismatch");

			return (const uint16 *) ConstPixel (row, col, plane);
			
			}
			
		/// Get a writable uint16 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as uint16 *.

		uint16 * DirtyPixel_uint16 (int32 row,
								    int32 col,
								    uint32 plane = 0)
			{
			
			ASSERT (fPixelType == ttShort, "Pixel type access mismatch");

			return (uint16 *) DirtyPixel (row, col, plane);
			
			}
			
		/// Get read-only int16 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as int16 *.

		const int16 * ConstPixel_int16 (int32 row,
										int32 col,
										uint32 plane = 0) const
			{
			
			ASSERT (fPixelType == ttSShort, "Pixel type access mismatch");

			return (const int16 *) ConstPixel (row, col, plane);
			
			}
			
		/// Get a writable int16 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as int16 *.

		int16 * DirtyPixel_int16 (int32 row,
								  int32 col,
								  uint32 plane = 0)
			{
			
			ASSERT (fPixelType == ttSShort, "Pixel type access mismatch");

			return (int16 *) DirtyPixel (row, col, plane);
			
			}

		/// Get read-only uint32 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as uint32 *.

		const uint32 * ConstPixel_uint32 (int32 row,
										  int32 col,
										  uint32 plane = 0) const
			{
			
			ASSERT (fPixelType == ttLong, "Pixel type access mismatch");

			return (const uint32 *) ConstPixel (row, col, plane);
			
			}
			
		/// Get a writable uint32 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as uint32 *.

		uint32 * DirtyPixel_uint32 (int32 row,
								    int32 col,
								    uint32 plane = 0)
			{
			
			ASSERT (fPixelType == ttLong, "Pixel type access mismatch");

			return (uint32 *) DirtyPixel (row, col, plane);
			
			}
			
		/// Get read-only int32 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as int32 *.

		const int32 * ConstPixel_int32 (int32 row,
										int32 col,
										uint32 plane = 0) const
			{
			
			ASSERT (fPixelType == ttSLong, "Pixel type access mismatch");

			return (const int32 *) ConstPixel (row, col, plane);
			
			}
			
		/// Get a writable int32 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as int32 *.

		int32 * DirtyPixel_int32 (int32 row,
								  int32 col,
								  uint32 plane = 0)
			{
			
			ASSERT (fPixelType == ttSLong, "Pixel type access mismatch");

			return (int32 *) DirtyPixel (row, col, plane);
			
			}

		/// Get read-only real32 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as real32 *.

		const real32 * ConstPixel_real32 (int32 row,
										  int32 col,
										  uint32 plane = 0) const
			{
			
			ASSERT (fPixelType == ttFloat, "Pixel type access mismatch");

			return (const real32 *) ConstPixel (row, col, plane);
			
			}
			
		/// Get a writable real32 * to pixel data starting at a specific pixel in the buffer.
		/// \param row Start row for buffer pointer.
		/// \param col Start column for buffer pointer.
		/// \param plane Start plane for buffer pointer.
		/// \retval Pointer to pixel data as real32 *.

		real32 * DirtyPixel_real32 (int32 row,
									int32 col,
									uint32 plane = 0)
			{
			
			ASSERT (fPixelType == ttFloat, "Pixel type access mismatch");

			return (real32 *) DirtyPixel (row, col, plane);
			
			}
		
		/// Initialize a rectangular area of pixel buffer to zeros.
		/// \param area Rectangle of pixel buffer to zero.
		/// \param area Area to zero
		/// \param plane Plane to start filling on.
		/// \param planes Number of planes to fill.

		void SetZero (const dng_rect &area,
					  uint32 plane,
					  uint32 planes);
		
		/// Copy image data from an area of one pixel buffer to same area of another.
		/// \param src Buffer to copy from.
		/// \param area Rectangle of pixel buffer to copy.
		/// \param plane Plane to start copy.
		/// \param planes Number of planes to copy.

		void CopyArea (const dng_pixel_buffer &src,
					   const dng_rect &area,
					   uint32 plane,
					   uint32 planes);
					   
		/// Calculate the offset phase of destination rectangle relative to source rectangle.
		/// Phase is based on a 0,0 origin and the notion of repeating srcArea across dstArea.
		/// It is the number of pixels into srcArea to start repeating from when tiling dstArea.
		/// \retval dng_point containing horizontal and vertical phase.

		static dng_point RepeatPhase (const dng_rect &srcArea,
					   			   	  const dng_rect &dstArea);

		/// Repeat the image data in srcArea acros dstArea.
		/// (Generally used for padding operations.)
		/// \param srcArea Area to repeat from.
		/// \param dstArea Area to fill with data from srcArea.

		void RepeatArea (const dng_rect &srcArea,
						 const dng_rect &dstArea);

		/// Apply a right shift (C++ oerpator >>) to all pixel values. Only implemented for 16-bit (signed or unsigned) pixel buffers.
		/// \param shift Number of bits by which to right shift each pixel value.

		void ShiftRight (uint32 shift);
		
		/// Change metadata so pixels are iterated in opposite horizontal order.
		/// This operation does not require movement of actual pixel data.

		void FlipH ();
		
		/// Change metadata so pixels are iterated in opposite vertical order.
		/// This operation does not require movement of actual pixel data.

		void FlipV ();
		
		/// Change metadata so pixels are iterated in opposite plane order.
		/// This operation does not require movement of actual pixel data.

		void FlipZ ();	// Flip planes
		
	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/

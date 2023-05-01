/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_stream.h#2 $ */ 
/* $DateTime: 2006/04/12 14:23:04 $ */
/* $Change: 216157 $ */
/* $Author: stern $ */

/** Data stream abstraction for serializing and deserializing sequences of basic types and RAW image data.
 */

/*****************************************************************************/

#ifndef __dng_stream__
#define __dng_stream__

/*****************************************************************************/

#include "dng_classes.h"
#include "dng_types.h"
#include "dng_memory.h"
#include "dng_rational.h"

/*****************************************************************************/

/// Base stream abstraction. Has support for going between stream and pointer abstraction.

class dng_stream
	{
	
	public:
	
		enum
			{
			kInvalidOffset = 0xFFFFFFFF
			};
	
	private:
	
		bool fSwapBytes;
		
		bool fHaveLength;
		
		uint32 fLength;
		
		const uint32 fOffsetInOriginalFile;
	
		uint32 fPosition;
		
		dng_memory_data fMemBlock;
		
		uint8 *fBuffer;
		
		uint32 fBufferSize;
		
		uint32 fBufferStart;
		uint32 fBufferEnd;
		uint32 fBufferLimit;
		
		bool fBufferDirty;
		
		dng_abort_sniffer *fSniffer;
		
	protected:
	
		enum
			{
			kDefaultBufferSize = 4096
			};
		
		dng_stream (dng_abort_sniffer *sniffer = NULL,
					uint32 bufferSize = kDefaultBufferSize,
					uint32 offsetInOriginalFile = kInvalidOffset);
		
		virtual uint32 DoGetLength ();
	
		virtual void DoRead (void *data,
							 uint32 count,
							 uint32 offset);
							 
		virtual void DoSetLength (uint32 length);
							 
		virtual void DoWrite (const void *data,
							  uint32 count,
							  uint32 offset);
		
	public:
	
		/// Construct a stream with initial data.
		/// \param data Pointer to initial contents of stream.
		/// \param count Number of bytes data is valid for.
		/// \param offsetInOriginalFile If data came from a file originally, offset can be saved here for later use.

		dng_stream (const void *data,
					uint32 count,
					uint32 offsetInOriginalFile = kInvalidOffset);
		
		virtual ~dng_stream ();
		
		/// Getter for whether stream is swapping byte order on input/output.
		/// \retval If true, data will be swapped on input/output.

		bool SwapBytes () const
			{
			return fSwapBytes;
			}
		
		/// Setter for whether stream is swapping byte order on input/output.
		/// \param swapBytes If true, stream will swap byte order on input or output for future reads/writes.

		void SetSwapBytes (bool swapBytes)
			{
			fSwapBytes = swapBytes;
			}

		/// Getter for whether data in stream is big endian.
		/// \retval If true, data in stream is big endian.

		bool BigEndian () const;
		
		/// Setter for whether data in stream is big endian.
		/// \param bigEndian If true, data in stream is big endian.

		void SetBigEndian (bool bigEndian = true);
		
		/// Getter for whether data in stream is big endian.
		/// \retval If true, data in stream is big endian.

		bool LittleEndian () const
			{
			return !BigEndian ();
			}
		
		/// Setter for whether data in stream is big endian.
		/// \param littleEndian If true, data in stream is big endian.

		void SetLittleEndian (bool littleEndian = true)
			{
			SetBigEndian (!littleEndian);
			}

		/// Getter for length of data in stream.
		/// \retval Length of readable data in stream.
			
		uint32 Length ();

		/// Getter for current offset in stream.
		/// \retval current offset from start of stream.

		uint32 Position () const
			{
			return fPosition;
			}
			
		/// Getter for current position in original file, taking into account OffsetInOriginalFile stream data was taken from.
		/// \retval kInvalidOffset if no offset in original file is set, sum of offset in original file and current position otherwise.

		uint32 PositionInOriginalFile () const;
		
		/// Getter for offset in original file.
		/// \retval kInvalidOffset if no offset in original file is set, offset in original file otherwise.

		uint32 OffsetInOriginalFile () const;
		
		/// Return pointer to stream contents if the stream is entirely available as a single memory block, NULL otherwise.

		const void * Data () const;
		
		/// Return the entire stream as a single memory block.
		/// This works for all streams, but requires copying the data to a new buffer.
		/// \param allocator Allocator used to allocate memory.

		dng_memory_block * AsMemoryBlock (dng_memory_allocator &allocator);

		/// Seek to a new position in stream for reading.

		void SetReadPosition (uint32 offset);
		
		/// Skip forward in stream.
		/// \param delta Number of bytes to skip forward.

		void Skip (uint32 delta)
			{
			SetReadPosition (Position () + delta);
			}

		/// Get data from stream. Exception is thrown and no data is read if insufficient data available in stream.
		/// \param data Buffer to put data into. Must be valid for count bytes.
		/// \param count Bytes of data to read.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.
		
		void Get (void *data, uint32 count);

		/// Seek to a new position in stream for writing.
		
		void SetWritePosition (uint32 offset);
		
		/// Force any stored data in stream to be written to underlying storage.

		void Flush ();

		/// Set length of available data.
		/// \param length Number of bytes of avialble data in stream.

		void SetLength (uint32 length);

		/// Write data to stream.
		/// \param data Buffer of data to write to stream.
		/// \param count Bytes of in data.

		void Put (const void *data, uint32 count);

		/// Get an unsigned 8-bit integer from stream and advance read position.
		/// \retval One unsigned 8-bit integer.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.
		
		uint8 Get_uint8 ()
			{
			
			// Fast check to see if in buffer
			
			if (fPosition >= fBufferStart && fPosition < fBufferEnd)
				{
				
				return fBuffer [fPosition++ - fBufferStart];
				
				}
				
			// Not in buffer, let main routine do the work.
			
			uint8 x;
			
			Get (&x, 1);
			
			return x;
				
			}
		
		/// Put an unsigned 8-bit integer to stream and advance write position.
		/// \param x One unsigned 8-bit integer.
		
		void Put_uint8 (uint8 x)
			{
			
			if (fBufferDirty               &&
			    fPosition  >= fBufferStart &&
				fPosition  <= fBufferEnd   &&
				fPosition  <  fBufferLimit)
				{
				
				fBuffer [fPosition - fBufferStart] = x;
				
				fPosition++;
				
				if (fBufferEnd < fPosition)
					fBufferEnd = fPosition;
				
				}
				
			else
				{
				
				Put (&x, 1);
				
				}
	
			}
			
		/// Get an unsigned 16-bit integer from stream and advance read position. Byte swap if byte swapping is turned on.
		/// \retval One unsigned 16-bit integer.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.
		
		uint16 Get_uint16 ();
		
		/// Put an unsigned 16-bit integer to stream and advance write position. Byte swap if byte swapping is turned on.
		/// \param x One unsigned 16-bit integer.

		void Put_uint16 (uint16 x);
		
		/// Get an unsigned 32-bit integer from stream and advance read position. Byte swap if byte swapping is turned on.
		/// \retval One unsigned 16-bit integer.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.
		
		uint32 Get_uint32 ();
		
		/// Put an unsigned 32-bit integer to stream and advance write position. Byte swap if byte swapping is turned on.
		/// \param x One unsigned 16-bit integer.

		void Put_uint32 (uint32 x);
		
		/// Get one 8-bit integer from stream and advance read position. Byte swap if byte swapping is turned on.
		/// \retval One 8-bit integer.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.

		int8 Get_int8 ()
			{
			return (int8) Get_uint8 ();
			}
			
		/// Put one 8-bit integer to stream and advance write position. Byte swap if byte swapping is turned on.
		/// \param x One  8-bit integer.

		void Put_int8 (int8 x)
			{
			Put_uint8 ((uint8) x);
			}

		/// Get one 16-bit integer from stream and advance read position. Byte swap if byte swapping is turned on.
		/// \retval One 16-bit integer.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.

		int16 Get_int16 ()
			{
			return (int16) Get_uint16 ();
			}
			
		/// Put one 16-bit integer to stream and advance write position. Byte swap if byte swapping is turned on.
		/// \param x One 16-bit integer.

		void Put_int16 (int16 x)
			{
			Put_uint16 ((uint16) x);
			}

		/// Get one 32-bit integer from stream and advance read position. Byte swap if byte swapping is turned on.
		/// \retval One 32-bit integer.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.

		int32 Get_int32 ()
			{
			return (int32) Get_uint32 ();
			}
			
		/// Put one 32-bit integer to stream and advance write position. Byte swap if byte swapping is turned on.
		/// \param x One 32-bit integer.

		void Put_int32 (int32 x)
			{
			Put_uint32 ((uint32) x);
			}
			
		/// Get one 32-bit IEEE floating-point number from stream and advance read position. Byte swap if byte swapping is turned on.
		/// \retval One 32-bit IEEE floating-point number.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.

		real32 Get_real32 ();
		
		/// Put one 32-bit IEEE floating-point number to stream and advance write position. Byte swap if byte swapping is turned on.
		/// \param x One 32-bit IEEE floating-point number.

		void Put_real32 (real32 x);
		
		/// Get one 64-bit IEEE floating-point number from stream and advance read position. Byte swap if byte swapping is turned on.
		/// \retval One 64-bit IEEE floating-point number .
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.

		real64 Get_real64 ();
		
		/// Put one 64-bit IEEE floating-point number to stream and advance write position. Byte swap if byte swapping is turned on.
		/// \param x One64-bit IEEE floating-point number.

		void Put_real64 (real64 x);
		
		/// Get an 8-bit character string from stream and advance read position.
		/// Routine always reads until a NUL character (8-bits of zero) is read.
		/// (That is, only maxLength bytes will be returned in buffer, but the stream is always advanced until a NUL
		///  is read or EOF is reached.)
		/// \param data Buffer in which string is returned.
		/// \param maxLength Maximum number of bytes to place in buffer.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if stream runs out before NUL is seen.

		void Get_CString (char *data,
						  uint32 maxLength);
		
		/// Get a 16-bit character string from stream and advance read position. 16-bit characters are truncated to 8-bits.
		/// Routine always reads until a NUL character (16-bits of zero) is read.
		/// (That is, only maxLength bytes will be returned in buffer, but the stream is always advanced until a NUL
		///  is read or EOF is reached.)
		/// \param data Buffer to place string in.
		/// \param maxLength Maximum number of bytes to place in buffer.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if stream runs out before NUL is seen.

		void Get_UString (char *data,
						  uint32 maxLength);
		
		/// Get a value of size indicated by tag type from stream and advance read position. Byte swap if byte swapping is turned on and tag type is larger than a byte. Value is returned as an unsigned 32-bit integer. 
		/// \param tagType Tag type of data stored in stream.
		/// \retval One unsigned 32-bit integer.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.

		uint32 TagValue_uint32 (uint32 tagType);

		/// Get a value of size indicated by tag type from stream and advance read position. Byte swap if byte swapping is turned on and tag type is larger than a byte. Value is returned as a 32-bit integer. 
		/// \param tagType Tag type of data stored in stream.
		/// \retval One 32-bit integer.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.

		int32 TagValue_int32 (uint32 tagType);
		
		/// Get a value of size indicated by tag type from stream and advance read position. Byte swap if byte swapping is turned on and tag type is larger than a byte. Value is returned as a dng_urational. 
		/// \param tagType Tag type of data stored in stream.
		/// \retval One dng_urational.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.

		dng_urational TagValue_urational (uint32 tagType);

		/// Get a value of size indicated by tag type from stream and advance read position. Byte swap if byte swapping is turned on and tag type is larger than a byte. Value is returned as a dng_srational. 
		/// \param tagType Tag type of data stored in stream.
		/// \retval One dng_srational.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.
		
		dng_srational TagValue_srational (uint32 tagType);

		/// Get a value of size indicated by tag type from stream and advance read position. Byte swap if byte swapping is turned on and tag type is larger than a byte. Value is returned as a 64-bit IEEE floating-point number. 
		/// \param tagType Tag type of data stored in stream.
		/// \retval One 64-bit IEEE floating-point number.
		/// \exception dng_exception with fErrorCode equal to dng_error_end_of_file if not enough data in stream.

		real64 TagValue_real64 (uint32 tagType);

		/// Getter for sniffer associated with stream.
		/// \retval The sniffer for this stream.
		
		dng_abort_sniffer * Sniffer () const
			{
			return fSniffer;
			}
		
	private:
	
		// Hidden copy constructor and assignment operator.
	
		dng_stream (const dng_stream &stream);
		
		dng_stream & operator= (const dng_stream &stream);
		
	};
	
/*****************************************************************************/

class TempBigEndian
	{
	
	private:
	
		dng_stream & fStream;
		
		bool fOldSwap;
		
	public:
	
		TempBigEndian (dng_stream &stream,
					   bool bigEndian = true);
						 
		virtual ~TempBigEndian ();
		
	};
			
/*****************************************************************************/

class TempLittleEndian: public TempBigEndian
	{
	
	public:
	
		TempLittleEndian (dng_stream &stream,
						  bool littleEndian = true)
			
			:	TempBigEndian (stream, !littleEndian)
			
			{
			}
	
		virtual ~TempLittleEndian ()
			{
			}

	};
				
/*****************************************************************************/

#endif
	
/*****************************************************************************/

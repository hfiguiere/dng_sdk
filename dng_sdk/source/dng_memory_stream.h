/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_memory_stream.h#2 $ */ 
/* $DateTime: 2006/04/12 14:23:04 $ */
/* $Change: 216157 $ */
/* $Author: stern $ */

/** \file
 * Stream abstraction to/from in-memory data.
 */

/*****************************************************************************/

#ifndef __dng_memory_stream__
#define __dng_memory_stream__

/*****************************************************************************/

#include "dng_stream.h"

/*****************************************************************************/

/// \brief A dng_stream which can be read from or written to memory.
///
/// Stream is populated via writing and either read or accessed by asking for contents as a pointer.

class dng_memory_stream: public dng_stream
	{
	
	protected:
	
		dng_memory_allocator &fAllocator;
		
		uint32 fPageSize;
		
		uint32 fPageCount;
		uint32 fPagesAllocated;
		
		dng_memory_block **fPageList;
		
		uint32 fMemoryStreamLength;
		
	public:

		/// Construct a new memory-based stream.
		/// \param allocator Allocator to use to allocate memory in stream as needed.
		/// \param sniffer If non-NULL used to check for user cancellation.
		/// \param pageSize Unit of allocation for data stored in stream.

		dng_memory_stream (dng_memory_allocator &allocator,
						   dng_abort_sniffer *sniffer = NULL,
						   uint32 pageSize = 64 * 1024);
						   
		virtual ~dng_memory_stream ();
		
	protected:
		
		virtual uint32 DoGetLength ();
	
		virtual void DoRead (void *data,
							 uint32 count,
							 uint32 offset);
							 
		virtual void DoSetLength (uint32 length);
							 
		virtual void DoWrite (const void *data,
							  uint32 count,
							  uint32 offset);
		
	private:
	
		// Hidden copy constructor and assignment operator.
	
		dng_memory_stream (const dng_memory_stream &stream);
		
		dng_memory_stream & operator= (const dng_memory_stream &stream);
		
	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/

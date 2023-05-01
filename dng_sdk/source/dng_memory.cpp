/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/camera_raw_main/camera_raw/dng_sdk/source/dng_memory.cpp#3 $ */ 
/* $DateTime: 2016/01/19 15:23:55 $ */
/* $Change: 1059947 $ */
/* $Author: erichan $ */

/*****************************************************************************/

#include "dng_memory.h"

#include "dng_bottlenecks.h"
#include "dng_exceptions.h"

/*****************************************************************************/

dng_memory_data::dng_memory_data ()
	
	:	fBuffer (NULL)
	
	{
	
	}

/*****************************************************************************/

dng_memory_data::dng_memory_data (uint32 size)

	:	fBuffer (NULL)
	
	{
	
	Allocate (size);
	
	}

/*****************************************************************************/

dng_memory_data::dng_memory_data (const dng_safe_uint32 &size)

	:	fBuffer (NULL)
	
	{
	
	Allocate (size.Get ());
	
	}

/*****************************************************************************/

dng_memory_data::dng_memory_data (uint32 count, 
								  std::size_t elementSize)

	:	fBuffer (NULL)
	
	{
	
	Allocate (count, elementSize);
	
	}

/*****************************************************************************/

dng_memory_data::~dng_memory_data ()
	{
	
	Clear ();
	
	}
				
/*****************************************************************************/

void dng_memory_data::Allocate (uint32 size)
	{
	
	Clear ();
	
	if (size)
		{
		
		fBuffer = (char *) malloc (size);
		
		if (!fBuffer)
			{
			
			ThrowMemoryFull ();
						 
			}
		
		}
	
	}
				
/*****************************************************************************/

void dng_memory_data::Allocate (const dng_safe_uint32 &size)
	{
	
	Allocate (size.Get ());
	
	}

/*****************************************************************************/

void dng_memory_data::Allocate (uint32 count, 
								std::size_t elementSize)
	{
	
	// Convert elementSize to a uint32.

	const uint32 elementSizeAsUint32 = static_cast<uint32> (elementSize);

	if (static_cast<std::size_t> (elementSizeAsUint32) != elementSize)
		{
		ThrowOverflow ("elementSize overflow");
		}
	
	// Compute required number of bytes and allocate memory.

	dng_safe_uint32 numBytes = dng_safe_uint32 (count) * elementSizeAsUint32;

	Allocate (numBytes.Get ());
	
	}

/*****************************************************************************/

void dng_memory_data::Allocate (const dng_safe_uint32 &count, 
								std::size_t elementSize)
	{

	Allocate (count.Get (), elementSize);

	}

/*****************************************************************************/

void dng_memory_data::Clear ()
	{
	
	if (fBuffer)
		{
		
		free (fBuffer);
		
		fBuffer = NULL;
		
		}
		
	}
				
/*****************************************************************************/

dng_memory_block * dng_memory_block::Clone (dng_memory_allocator &allocator) const
	{
	
	uint32 size = LogicalSize ();
	
	dng_memory_block * result = allocator.Allocate (size);
	
	DoCopyBytes (Buffer (), result->Buffer (), size);
		
	return result;
	
	}

/*****************************************************************************/

class dng_malloc_block : public dng_memory_block
	{
	
	private:
	
		void *fMalloc;
	
	public:
	
		dng_malloc_block (uint32 logicalSize);
		
		virtual ~dng_malloc_block ();
		
	};
	
/*****************************************************************************/

dng_malloc_block::dng_malloc_block (uint32 logicalSize)

	:	dng_memory_block (logicalSize)
	
	,	fMalloc (NULL)
	
	{

	#if qLinux

	// BULLSHIT: Need to change this alignment for AVX support?

	int err = ::posix_memalign ((void **) &fMalloc, 
								16,
								(size_t) PhysicalSize ());

	if (err)
		{

		ThrowMemoryFull ();

		}

	#elif qAndroid
        
	fMalloc = memalign (16, (size_t) PhysicalSize ());
        
	if (!fMalloc)
		{
            
		ThrowMemoryFull ();
            
		}
	
	#else

	fMalloc = (char *) malloc (PhysicalSize ());
	
	if (!fMalloc)
		{
		
		ThrowMemoryFull ();
					 
		}
		
	#endif

	SetBuffer (fMalloc);
	
	}
		
/*****************************************************************************/

dng_malloc_block::~dng_malloc_block ()
	{
	
	if (fMalloc)
		{
		
		free (fMalloc);
		
		}
	
	}
		
/*****************************************************************************/

dng_memory_block * dng_memory_allocator::Allocate (uint32 size)
	{
	
	dng_memory_block *result = new dng_malloc_block (size);
	
	if (!result)
		{
		
		ThrowMemoryFull ();
		
		}
	
	return result;
	
	}

/*****************************************************************************/

dng_memory_allocator gDefaultDNGMemoryAllocator;

/*****************************************************************************/

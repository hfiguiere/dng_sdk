/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_file_stream.h#2 $ */ 
/* $DateTime: 2006/04/12 14:23:04 $ */
/* $Change: 216157 $ */
/* $Author: stern $ */

/** \file
 * Simple, portable, file read/write support.
 */

/*****************************************************************************/

#ifndef __dng_file_stream__
#define __dng_file_stream__

/*****************************************************************************/

#include "dng_stream.h"

/*****************************************************************************/

/// \brief A stream to/from a disk file. See dng_stream for read/write interface

class dng_file_stream: public dng_stream
	{
	
	private:
	
		FILE *fFile;
	
	public:
	
		/// Open a stream on a file.
		/// \param filename Pathname in platform synax.
		/// \param output Set to true if writing, false otherwise.

		dng_file_stream (const char *filename,
						 bool output = false);
		
		virtual ~dng_file_stream ();
	
	protected:
	
		virtual uint32 DoGetLength ();
	
		virtual void DoRead (void *data,
							 uint32 count,
							 uint32 offset);
		
		virtual void DoWrite (const void *data,
							  uint32 count,
							  uint32 offset);
		
	private:
	
		// Hidden copy constructor and assignment operator.
	
		dng_file_stream (const dng_file_stream &stream);
		
		dng_file_stream & operator= (const dng_file_stream &stream);
		
	};
		
/*****************************************************************************/

#endif
	
/*****************************************************************************/

/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_file_stream.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#include "dng_file_stream.h"

#include "dng_exceptions.h"

/*****************************************************************************/

dng_file_stream::dng_file_stream (const char *filename,
								  bool output)

	:	dng_stream ((dng_abort_sniffer *) NULL, kDefaultBufferSize, 0)
	,	fFile (NULL)
	
	{
	
	fFile = fopen (filename, output ? "wb" : "rb");
	
	if (!fFile)
		{
		
		#if qDNGValidate

		ReportError ("Unable to open file",
					 filename);
					 
		ThrowSilentError ();
		
		#else
		
		ThrowOpenFile ();
		
		#endif

		}
	
	}
		
/*****************************************************************************/

dng_file_stream::~dng_file_stream ()
	{
	
	if (fFile)
		{
		fclose (fFile);
		fFile = NULL;
		}
	
	}
		
/*****************************************************************************/

uint32 dng_file_stream::DoGetLength ()
	{
	
	if (fseek (fFile, 0, SEEK_END) != 0)
		{
		
		ThrowReadFile ();

		}
	
	return ftell (fFile);
	
	}
		
/*****************************************************************************/

void dng_file_stream::DoRead (void *data,
							  uint32 count,
							  uint32 offset)
	{
	
	if (fseek (fFile, offset, SEEK_SET) != 0)
		{
		
		ThrowReadFile ();

		}
	
	uint32 bytesRead = (uint32) fread (data, 1, count, fFile);
	
	if (bytesRead != count)
		{
		
		ThrowReadFile ();

		}
	
	}
		
/*****************************************************************************/

void dng_file_stream::DoWrite (const void *data,
							   uint32 count,
							   uint32 offset)
	{
	
	if (fseek (fFile, offset, SEEK_SET) != 0)
		{
		
		ThrowWriteFile ();

		}
	
	uint32 bytesWritten = (uint32) fwrite (data, 1, count, fFile);
	
	if (bytesWritten != count)
		{
		
		ThrowWriteFile ();

		}
	
	}
		
/*****************************************************************************/

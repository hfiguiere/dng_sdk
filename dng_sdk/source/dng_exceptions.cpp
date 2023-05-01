/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_exceptions.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#include "dng_exceptions.h"

#include "dng_globals.h"

/*****************************************************************************/

#if qDNGValidate

/*****************************************************************************/

void ReportWarning (const char *message,
				    const char *sub_message)
	{
	
	fprintf (stderr, "*** Warning: %s", message);

	if (sub_message)
		{
	
		fprintf (stderr, " (%s)", sub_message); 
		
		}
		
	fprintf (stderr, " ***\n"); 
	
	}

/*****************************************************************************/

void ReportError (const char *message,
				  const char *sub_message)
	{
	
	fprintf (stderr, "*** Error: %s", message);

	if (sub_message)
		{
	
		fprintf (stderr, " (%s)", sub_message); 
		
		}
		
	fprintf (stderr, " ***\n"); 
	
	}

/*****************************************************************************/

#endif

/*****************************************************************************/

void Throw_dng_error (dng_error_code err)
	{
	
	#if qDNGValidate
	
		{
					
		const char *message = NULL;
		
		switch (err)
			{
			
			case dng_error_none:
			case dng_error_silent:
			case dng_error_user_canceled:
				{
				break;
				}
				
			case dng_error_not_yet_implemented:
				{
				message = "Not yet implemented";
				break;
				}
				
			case dng_error_host_insufficient:
				{
				message = "Host insufficient";
				break;
				}
			
			case dng_error_memory:
				{
				message = "Unable to allocate memory";
				break;
				}
				
			case dng_error_bad_format:
				{
				message = "File format is invalid";
				break;
				}
	
			case dng_error_matrix_math:
				{
				message = "Matrix math error";
				break;
				}
	
			case dng_error_open_file:
				{
				message = "Unable to open file";
				break;
				}
				
			case dng_error_read_file:
				{
				message = "File read error";
				break;
				}
				
			case dng_error_write_file:
				{
				message = "File write error";
				break;
				}
				
			case dng_error_end_of_file:
				{
				message = "Unexpected end-of-file";
				break;
				}
				
			default:
				{
				message = "Unknown error";
				break;
				}
				
			}
			
		if (message)
			{
			ReportError (message);
			}
		
		}
	
	#endif
	
	throw dng_exception (err);
	
	}

/*****************************************************************************/

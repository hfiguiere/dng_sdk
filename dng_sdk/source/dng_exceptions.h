/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_exceptions.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/** \file
 * C++ exception support for DNG SDK.
*/

/*****************************************************************************/

#ifndef __dng_exceptions__
#define __dng_exceptions__

/*****************************************************************************/

#include "dng_errors.h"
#include "dng_flags.h"

/*****************************************************************************/

#if qDNGValidate

/*****************************************************************************/

/// Display a warning message.

void ReportWarning (const char *message,
				    const char *sub_message = NULL);
	
/*****************************************************************************/

/// Display an error message.

void ReportError (const char *message,
				  const char *sub_message = NULL);
	
/*****************************************************************************/

#endif
	
/*****************************************************************************/

/// \brief All exceptions thrown by the DNG SDK use this exception class.

class dng_exception
	{
	
	private:
	
		dng_error_code fErrorCode;
	
	public:
	
		/// Construct an exception representing the given error code.
		/// \param code Error code this exception is for.
		dng_exception (dng_error_code code)
		
			: fErrorCode (code)
			
			{
			}
		
		virtual ~dng_exception ()
			{ 
			}

		/// Getter for error code of this exception
		/// \retval The error code of this exception.
		dng_error_code ErrorCode () const
			{
			return fErrorCode;
			}

	};
	
/******************************************************************************/

/// \brief Throw an exception based on an arbitrary error code.

void Throw_dng_error (dng_error_code err);

/******************************************************************************/

/// \brief Convenience function to throw dng_exception with error code if error_code is not dng_error_none .

inline void Fail_dng_error (dng_error_code err)
	{
	
	if (err != dng_error_none)
		{
		
		Throw_dng_error (err);
		
		}
		
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_unknown .

inline void ThrowProgramError ()
	{
	
	Throw_dng_error (dng_error_unknown);
	
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_not_yet_implemented .

inline void ThrowNotYetImplemented ()
	{
	
	Throw_dng_error (dng_error_not_yet_implemented);
	
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_silent .

inline void ThrowSilentError ()
	{
	
	Throw_dng_error (dng_error_silent);
	
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_user_canceled .

inline void ThrowUserCanceled ()
	{
	
	Throw_dng_error (dng_error_user_canceled);
	
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_host_insufficient .

inline void ThrowHostInsufficient ()
	{
	
	Throw_dng_error (dng_error_host_insufficient);
	
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_memory .

inline void ThrowMemoryFull ()
	{
	
	Throw_dng_error (dng_error_memory);
	
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_bad_format .

inline void ThrowBadFormat ()
	{
	
	Throw_dng_error (dng_error_bad_format);
	
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_matrix_math .

inline void ThrowMatrixMath ()
	{
	
	Throw_dng_error (dng_error_matrix_math);
	
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_open_file .

inline void ThrowOpenFile ()
	{
	
	Throw_dng_error (dng_error_open_file);
	
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_read_file .

inline void ThrowReadFile ()
	{
	
	Throw_dng_error (dng_error_read_file);
	
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_write_file .

inline void ThrowWriteFile ()
	{
	
	Throw_dng_error (dng_error_write_file);
	
	}

/*****************************************************************************/

/// \brief Convenience function to throw dng_exception with error code dng_error_end_of_file .

inline void ThrowEndOfFile ()
	{
	
	Throw_dng_error (dng_error_end_of_file);
	
	}

/*****************************************************************************/

#endif
	
/*****************************************************************************/

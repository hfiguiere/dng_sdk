/*****************************************************************************/
// Copyright 2012 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/camera_raw_main/camera_raw/dng_sdk/source/dng_uncopyable.h#2 $ */ 
/* $DateTime: 2015/06/09 23:32:35 $ */
/* $Change: 1026104 $ */
/* $Author: aksherry $ */

/*****************************************************************************/

#ifndef __dng_uncopyable__
#define __dng_uncopyable__

/*****************************************************************************/

// Virtual base class to prevent object copies.

class dng_uncopyable
	{

	protected:

		dng_uncopyable ()
			{
			}

		~dng_uncopyable ()
			{
			}

	private:
		
		dng_uncopyable (const dng_uncopyable &);
		
		dng_uncopyable & operator= (const dng_uncopyable &);
		
	};

/*****************************************************************************/

#endif	// __dng_uncopyable__
	
/*****************************************************************************/

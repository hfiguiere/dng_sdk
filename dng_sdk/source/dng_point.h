/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_point.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#ifndef __dng_point__
#define __dng_point__

/*****************************************************************************/

#include "dng_types.h"

/*****************************************************************************/

class dng_point
	{
	
	public:
	
		int32 v;
		int32 h;
	
	public:
	
		dng_point ()
			:	v (0)
			,	h (0)
			{
			}
			
		dng_point (int32 vv, int32 hh)
			:	v (vv)
			,	h (hh)
			{
			}
			
		bool operator== (const dng_point &pt) const
			{
			return (v == pt.v) &&
				   (h == pt.h);
			}
			
		bool operator!= (const dng_point &pt) const
			{
			return !(*this == pt);
			}
			
	};

/*****************************************************************************/

inline dng_point operator+ (const dng_point &a,
				  			const dng_point &b)
				  
				  
	{
	
	return dng_point (a.v + b.v,
					  a.h + b.h);
					  
	}

/*****************************************************************************/

inline dng_point operator- (const dng_point &a,
				  			const dng_point &b)
				  
				  
	{
	
	return dng_point (a.v - b.v,
					  a.h - b.h);
					  
	}

/*****************************************************************************/

inline dng_point Transpose (const dng_point &a)
	{
	
	return dng_point (a.h, a.v);
	
	}

/*****************************************************************************/

#endif
	
/*****************************************************************************/

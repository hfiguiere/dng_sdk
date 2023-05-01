/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_rect.cpp#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#include "dng_rect.h"

#include "dng_utils.h"

/*****************************************************************************/

bool dng_rect::operator== (const dng_rect &rect) const
	{
	
	return (rect.t == t) &&
		   (rect.l == l) &&
		   (rect.b == b) &&
		   (rect.r == r);
		   
	}
			
/*****************************************************************************/

bool dng_rect::IsZero () const
	{

	return (t == 0) && (l == 0) && (b == 0) && (r == 0);

	}
			
/*****************************************************************************/

dng_rect operator& (const dng_rect &a,
					const dng_rect &b)
	{
	
	dng_rect c;
	
	c.t = Max_int32 (a.t, b.t);
	c.l = Max_int32 (a.l, b.l);
	
	c.b = Min_int32 (a.b, b.b);
	c.r = Min_int32 (a.r, b.r);
	
	if (c.IsEmpty ())
		{
		
		c = dng_rect ();
		
		}
		
	return c;
	
	}

/*****************************************************************************/

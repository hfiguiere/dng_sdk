/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_rect.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#ifndef __dng_rect__
#define __dng_rect__

/*****************************************************************************/

#include "dng_types.h"
#include "dng_point.h"

/*****************************************************************************/

class dng_rect
	{
	
	public:
	
		int32 t;
		int32 l;
		int32 b;
		int32 r;
		
	public:
		
		dng_rect ()
			:	t (0)
			,	l (0)
			,	b (0)
			,	r (0)
			{
			}
			
		dng_rect (int32 tt, int32 ll, int32 bb, int32 rr)
			:	t (tt)
			,	l (ll)
			,	b (bb)
			,	r (rr)
			{
			}
			
		dng_rect (uint32 h, uint32 w)
			:	t (0)
			,	l (0)
			,	b (h)
			,	r (w)
			{
			}
			
		dng_rect (const dng_point &size)
			:	t (0)
			,	l (0)
			,	b (size.v)
			,	r (size.h)
			{
			}
		
		void Clear ()
			{
			*this = dng_rect ();
			}
		
		bool operator== (const dng_rect &rect) const;
		
		bool operator!= (const dng_rect &rect) const
			{
			return !(*this == rect);
			}
			
		bool IsZero () const;
			
		bool NotZero () const
			{
			return !IsZero ();
			}
			
		bool IsEmpty () const
			{
			return (t >= b) || (l >= r);
			}
			
		bool NotEmpty () const
			{
			return !IsEmpty ();
			}
			
		uint32 W () const
			{
			return (r >= l ? (uint32) (r - l) : 0);
			}
	
		uint32 H () const
			{
			return (b >= t ? (uint32) (b - t) : 0);
			}
		
		dng_point TL () const
			{
			return dng_point (t, l);
			}
			
		dng_point Size () const
			{
			return dng_point (H (), W ());
			}
	
	};

/*****************************************************************************/

dng_rect operator& (const dng_rect &a,
					const dng_rect &b);

/*****************************************************************************/

inline dng_rect operator+ (const dng_rect &a,
					       const dng_point &b)
	{
	
	return dng_rect (a.t + b.v,
					 a.l + b.h,
					 a.b + b.v,
					 a.r + b.h);
	
	}

/*****************************************************************************/

inline dng_rect operator- (const dng_rect &a,
					       const dng_point &b)
	{
	
	return dng_rect (a.t - b.v,
					 a.l - b.h,
					 a.b - b.v,
					 a.r - b.h);
	
	}

/*****************************************************************************/

#endif
	
/*****************************************************************************/

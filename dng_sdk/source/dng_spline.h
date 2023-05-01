/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_spline.h#1 $ */ 
/* $DateTime: 2006/04/05 18:24:55 $ */
/* $Change: 215171 $ */
/* $Author: tknoll $ */

/*****************************************************************************/

#ifndef __dng_spline__
#define __dng_spline__

/*****************************************************************************/

#include "dng_types.h"

/*****************************************************************************/

inline real64 EvaluateSplineSegment (real64 x,
								     real64 x0,
								     real64 y0,
								     real64 s0,
								     real64 x1,
								     real64 y1,
								     real64 s1)
	{
	
	real64 A = x1 - x0;

	real64 B = (x - x0) / A;

	real64 C = (x1 - x) / A;

	real64 D = ((y0 * (2.0 - C + B) + (s0 * A * B)) * (C * C)) +
			   ((y1 * (2.0 - B + C) - (s1 * A * C)) * (B * B));
			   
	return D;
	
	}

/*****************************************************************************/

class dng_spline_solver
	{
	
	public:
	
		enum
			{
			kMaxPoints = 33
			};
	
	protected:
	
		int32 count;

		real64 X [kMaxPoints];
		real64 Y [kMaxPoints];
		
		real64 S [kMaxPoints];
		
	public:
	
		dng_spline_solver ();
		
		virtual ~dng_spline_solver ()	
			{
			}
			
		void Reset ()
			{
			count = 0;
			}

		void Add (real64 x, real64 y);

		void Solve ();

		real64 Evaluate (real64 x) const;

	private:
	
		// Hidden copy constructor and assignment operator.
	
		dng_spline_solver (const dng_spline_solver &solver);
		
		dng_spline_solver & operator= (const dng_spline_solver &solver);
		
	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/

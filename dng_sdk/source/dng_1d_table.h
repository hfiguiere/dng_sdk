/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_1d_table.h#2 $ */ 
/* $DateTime: 2006/04/12 14:23:04 $ */
/* $Change: 216157 $ */
/* $Author: stern $ */

/** \file
 * Definition of a lookup table based 1D floating-point to floating-point function abstraction using linear interpolation.
 */

/*****************************************************************************/

#ifndef __dng_1d_table__
#define __dng_1d_table__

/*****************************************************************************/

#include "dng_assertions.h"
#include "dng_auto_ptr.h"
#include "dng_classes.h"
#include "dng_types.h"

/*****************************************************************************/


/// \brief A 1D floating-point lookup table using linear interpolation.

class dng_1d_table
	{
	
	public:
		/// Constants denoting size of table.

		enum
			{
			kTableBits = 12,				//< Table is always a power of 2 in size. This is log2(kTableSize).
			kTableSize = (1 << kTableBits)	//< Number of entries in table.
			};
			
	protected:
	
		AutoPtr<dng_memory_block> fBuffer;
		
		real32 *fTable;
	
	public:
	
		dng_1d_table ();
			
		virtual ~dng_1d_table ();

		/// Set up table, initialize entries using functiion.
		/// This method can throw an exception, e.g. if there is not enough memory.
		/// \param allocator Memory allocator from which table memory is allocated.
		/// \param function Table is initialized with values of finction.Evalluate(0.0) to function.Evaluate(1.0).

		void Initialize (dng_memory_allocator &allocator,
						 const dng_1d_function &function);

		/// Lookup and interpolate mapping for an input.
		/// \param x value from 0.0 to 1.0 used as input for mapping
		/// \retval Approximation of function.Evaluate(x)

		real32 Interpolate (real32 x) const
			{
			
			real32 y = x * (real32) kTableSize;
			
			int32 index = (int32) y;
			
			ASSERT (index >= 0 && index <= kTableSize,
					"dng_1d_table::Interpolate parameter out of range");
					
			real32 z = (real32) index;
						
			real32 fract = y - z;
			
			return fTable [index    ] * (1.0f - fract) +
				   fTable [index + 1] * (       fract);
			
			}
			
	private:
	
		// Hidden copy constructor and assignment operator.
	
		dng_1d_table (const dng_1d_table &table);
		
		dng_1d_table & operator= (const dng_1d_table &table);
	
	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/

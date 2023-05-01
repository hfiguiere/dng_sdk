/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_abort_sniffer.h#2 $ */ 
/* $DateTime: 2006/04/12 14:23:04 $ */
/* $Change: 216157 $ */
/* $Author: stern $ */

/** \file
 * Classes supporting user cancellation and progress tracking.
 */

/*****************************************************************************/

#ifndef __dng_abort_sniffer__
#define __dng_abort_sniffer__

/*****************************************************************************/

#include "dng_types.h"

/*****************************************************************************/

/** \brief Class for signaling user cancellation and receiving progress updates.
 *
 * DNG SDK clients should derive a host application specific implementation from this class.
 */

class dng_abort_sniffer
	{
	
	friend class dng_sniffer_task;
	
	public:
		/// Check for pending user cancellation or other abort. ThrowUserCanceled will be called if one is pending.
		/// This static method is provided as a convenience for quickly testing for an abort and throwing an exception if one is pending.
		/// \param sniffer The dng_sniffer to test for a pending abort. Can be NULL, in which case there an abort is never signalled.

		static inline void SniffForAbort (dng_abort_sniffer *sniffer)
			{
			if (sniffer)
				sniffer->Sniff ();
			}
	
	protected:
	
		virtual ~dng_abort_sniffer ();

		/// Should be implemented by derived classes to check for an user cancellation.

		virtual void Sniff () = 0;

		/// Signals the start of a named task withn processing in the DNG SDK.
		/// Tasks may be nested.
		/// \param name of the task
		/// \param fract Percentage of total processing this task is expected to take. From 0.0 to 1.0 .

		virtual void StartTask (const char *name,
								real64 fract);

		/// Signals the end of the innermost task that has been started.

		virtual void EndTask ();

		/// Singals progress made on current task.
		/// \param fract percentage of processing completed on current task. From 0.0 to 1.0 .

		virtual void UpdateProgress (real64 fract);
			
	};

/******************************************************************************/

/// \brief Class to establish scope of a named subtask in DNG processing.
///
/// Instances of this class are intended to be stack allocated.

class dng_sniffer_task
	{
	
	private:
	
		dng_abort_sniffer *fSniffer;
	
	public:
	
		/// Inform a sniffer of a subtask in DNG processing.
		/// \param sniffer The sniffer associated with the host on which this processing is occurring.
		/// \param name The name of this subtask as a NUL terminated string.
		/// \param fract Percentage of total processing this task is expected to take, from 0.0 to 1.0 . 

		dng_sniffer_task (dng_abort_sniffer *sniffer,
					      const char *name = NULL,
					      real64 fract = 0.0)
					 
			:	fSniffer (sniffer)
			
			{
			if (fSniffer)
				fSniffer->StartTask (name, fract);
			}
			
		~dng_sniffer_task ()
			{
			if (fSniffer)
				fSniffer->EndTask ();
			}
		
		/// Check for pending user cancellation or other abort. ThrowUserCanceled will be called if one is pending.

		void Sniff ()
			{
			if (fSniffer)
				fSniffer->Sniff ();
			}

		/// Update progress on this subtask.
		/// \param fract Percentage of processing completed on current task, from 0.0 to 1.0 .

		void UpdateProgress (real64 fract)
			{
			if (fSniffer)
				fSniffer->UpdateProgress (fract);
			}
			
		/// Update progress on this subtask.
		/// \param done Amount of task completed in arbitrary integer units.
		/// \param total Total size of task in same arbitrary integer units as done.

		void UpdateProgress (uint32 done,
							 uint32 total)
			{
			UpdateProgress ((real64) done /
							(real64) total);
			}
		
		/// Signal task completed for progress purposes.

		void Finish ()
			{
			UpdateProgress (1.0);
			}
			
	private:
	
		// Hidden copy constructor and assignment operator.
	
		dng_sniffer_task (const dng_sniffer_task &task);
		
		dng_sniffer_task & operator= (const dng_sniffer_task &task);
		
	};

/*****************************************************************************/

#endif

/*****************************************************************************/

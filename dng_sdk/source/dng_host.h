/*****************************************************************************/
// Copyright 2006 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/* $Id: //mondo/dng_sdk_1_1/dng_sdk/source/dng_host.h#2 $ */ 
/* $DateTime: 2006/04/12 14:23:04 $ */
/* $Change: 216157 $ */
/* $Author: stern $ */

/** \file
 * Class definition for dng_host, initial point of contact and control between host application and DNG SDK.
 */

/*****************************************************************************/

#ifndef __dng_host__
#define __dng_host__

/*****************************************************************************/

#include "dng_classes.h"
#include "dng_errors.h"
#include "dng_types.h"

/*****************************************************************************/

/// \brief The main class for communication between the application and the DNG SDK. Used to customize memory allocation and other behaviors.
///
/// dng_host allows setting parameters for the DNG conversion, mediates callback style interactions between the host
/// application and the DNG SDK, and allows controlling certain internal behavior of the SDK such as memory allocation.
/// Many applications will be able to use the default implementation of dng_host by just setting the dng_memory_allocator and
/// dng_abort_sniffer in the constructor. More complex interactions will require deriving a class from dng_host.
///
/// Multiple dng_host objects can be allocated in a single process. This may be useful for DNG processing on separate threads.
/// (Distinct dng_host objects are completely threadsafe for read/write. The application is responsible for establishing
///  mutual exclusion for read/write access to a single dng_host object if it is used in multiple threads.)

class dng_host
	{
	
	private:
	
		dng_memory_allocator *fAllocator;
		
		dng_abort_sniffer *fSniffer;
	
		// Does the host require all the image metadata (vs. just checking
		// to see if the file is readable)?
	
		bool fNeedsMeta;
		
		// Does the host require actual image data (vs. just getting metadata
		// or just checking to see if the file is readable)?
		
		bool fNeedsImage;
		
		// If we need the image data, can it be read at preview quality?
		
		bool fForPreview;
		
		// If non-zero, the minimum size (longer of the two pixel dimensions)
		// image to read.  If zero, or if the full size image is smaller than
		// this, read the full size image.
		
		uint32 fMinimumSize;
		
		// Keep the stage 1 (original raw) image?
		
		bool fKeepStage1;
		
		// Keep the stage 2 (linearized) image?
		
		bool fKeepStage2;
		
		// Keep the DNG private data block?
		
		bool fKeepDNGPrivate;
		
		// Keep the original raw file data block?
		
		bool fKeepOriginalFile;
	
	public:
	
		/// Allocate a dng_host object, possiblly with custom allocator and sniffer.
		/// \param allocator Allows controlling all memory allocation done via this dng_host. Defaults to singleton global dng_memory_allocator, which calls new/delete dng_malloc_block for appropriate size.
		/// \param sniffer Used to periodically check if pending DNG conversions should be aborted and to communicate progress updates. Defaults to singleton global dng_abort_sniffer, which never aborts and ignores progress updated.

		dng_host (dng_memory_allocator *allocator = NULL,
				  dng_abort_sniffer *sniffer = NULL);
		
		/// Clean up direct memory for dng_host. Memory allocator and abort sniffer are not deleted. Objects such as dng_image and others returned from host can still be used after host is deleted.

		virtual ~dng_host ();
		
		/// Getter for host's memory allocator.

		dng_memory_allocator & Allocator ();
		
		/// Alocate a new dng_memory_block using the host's memory allocator.
		/// Uses the Allocator() property of host to allocate a new block of memory. Will call ThrowMemoryFull if block cannot be allocated.
		/// \param logicalSize Number of usable bytes returned dng_memory_block must contain.

		virtual dng_memory_block * Allocate (uint32 logicalSize);
		
		/// Getter for host's abort sniffer.

		dng_abort_sniffer * Sniffer ()
			{
			return fSniffer;
			}
		
		/// Check for pending abort. Should call ThrowUserCanceled if an abort is pending.

		virtual void SniffForAbort ();
		
		/// Setter for flag determining whether all XMP metadata should be parsed. Defaults to true. One might not want metadata when doing a quick check to see if a file is readable.
		/// \param needs If true, metadata is needed.

		void SetNeedsMeta (bool needs)
			{
			fNeedsMeta = needs;
			}

		/// Getter for flag determining whether all XMP metadata should be parsed. 

		bool NeedsMeta () const
			{
			return fNeedsMeta;
			}

		/// Setter for flag determining whether DNG image data is needed. Defaults to true. Image data might not be needed for applications which only manipulate metadata.
		/// \param needs If true, image data is needed.

		void SetNeedsImage (bool needs)
			{
			fNeedsImage = needs;
			}

		/// Setter for flag determining whether DNG image data is needed. 

		bool NeedsImage () const
			{
			return fNeedsImage;
			}

		/// Setter for flag determining whether	image should be preview quality, or full quality. 
		/// \param preview If true, rendered images are for preview.

		void SetForPreview (bool preview)
			{
			fForPreview = preview;
			}
			

		/// Getter for flag determining whether image should be preview quality.
		/// Preview quality images may be rendered more quickly. Current DNG SDK does not change rendering behavior based on this flag, but derived versions may use
		/// this getter to choose between a slower more accurate path and a faster "good enough for preview" one.
		/// Data produce with ForPreview set to true should not be written back to a DNG file, except as a preview image. 

		bool ForPreview () const
			{
			return fForPreview;
			}

		/// Setter for preview minimum pixel width of subsammpled image. Used to compute integer binning factor.
		/// If set, rendering will use binning to produce an image that is as close to this wide as possible, but no smaller.
		/// For example, if the input DNG is 2800 pixels wide and SetMinimumSize is called with 600, a factor of 4 binning will be used
		/// and the final image will be 700 pixels wide.
		/// \param size Target width in pixels for preview image.

		void SetMinimumSize (uint32 size)
			{
			fMinimumSize = size;
			}

		/// Getter for preview minimum pixel width of subsammpled image.		

		uint32 MinimumSize () const
			{
			return fMinimumSize;
			}

		/// Setter for flag determining whether	to keep stage 1, unprocessed raw data, after processing all stages.	
		/// \param keep If true, stage 1 data will be kept.

		void SetKeepStage1 (bool keep)
			{
			fKeepStage1 = keep;
			}

		/// Getter for flag determining whether	to keep stage 1, unprocessed raw data, after processing all stages.	

		bool KeepStage1 () const
			{
			return fKeepStage1;
			}

		/// Setter for flag determining whether	to keep stage 2, linearized, tone curve processed data, after processing all stages.	
		/// \param keep If true, stage 2 data will be kept.

		void SetKeepStage2 (bool keep)
			{
			fKeepStage2 = keep;
			}

		/// Getter for flag determining whether	to keep stage 2, linearized, tone curve processed data, after processing all stages.	

		bool KeepStage2 () const
			{
			return fKeepStage2;
			}

		/// Setter for flag determining whether DNG private data will be kept.	
		/// \param keep If true, DNG private data will be kept.

		void SetKeepDNGPrivate (bool keep)
			{
			fKeepDNGPrivate = keep;
			}

		/// Getter for flag determining whether all	DNG private data will be kept.

		bool KeepDNGPrivate ()
			{
			return fKeepDNGPrivate;
			}

		/// Setter for flag determining whether to keep original RAW file data.	
		/// \param keep If true, origianl RAW data will be kept.

		void SetKeepOriginalFile (bool keep)
			{
			fKeepOriginalFile = keep;
			}

		/// Getter for flag determining whether to keep original RAW file data.	

		bool KeepOriginalFile ()
			{
			return fKeepOriginalFile;
			}

		/// Determine if an error is the result of a temporary, but planned-for occurence such as user cancellation or memory exhaustion.
		/// This method is sometimes used to determine whether to try and continue processing a DNG file despite errors in the file format, etc.
		/// In such cases, processing will be continued if IsTransientError returns false. This is so that user cancellation and memory exhaustion
		/// always terminate processing.
		/// \param code Error to test for transience.

		virtual bool IsTransientError (dng_error_code code);

		/// General top-level botttleneck for image processing tasks.
		/// Default implementation calls dng_area_task::PerformAreaTask method on task. Can be overridden in derived classes
		/// to support multiprocessing, for example.
		/// \param task Image processing task to perform on area.
		/// \param area Rectangle over which to perform image processing task.

		virtual void PerformAreaTask (dng_area_task &task,
									  const dng_rect &area);

		/// Factory method for dng_exif class. Can be used to customize allocation or to ensure a derived class is used instead of dng_exif.

		virtual dng_exif * Make_dng_exif ();

		/// Factory method for dng_shared class. Can be used to customize allocation or to ensure a derived class is used instead of dng_shared.

		virtual dng_shared * Make_dng_shared ();

		/// Factory method for dng_ifd class. Can be used to customize allocation or to ensure a derived class is used instead of dng_ifd.

		virtual dng_ifd * Make_dng_ifd ();
		
		/// Factory method for dng_negative class. Can be used to customize allocation or to ensure a derived class is used instead of dng_negative.

		virtual dng_negative * Make_dng_negative ();
					      		 
	private:
	
		// Hidden copy constructor and assignment operator.
	
		dng_host (const dng_host &host);
		
		dng_host & operator= (const dng_host &host);
		
	};
	
/*****************************************************************************/

#endif
	
/*****************************************************************************/

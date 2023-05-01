#ifndef XMPCompareAndMergeErrorCodes_h__
#define XMPCompareAndMergeErrorCodes_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "XMPCompareAndMerge/XMPCompareAndMergeDefines.h"
#include "XMPCommon/XMPCommonErrorCodes.h"

namespace AdobeXMPCompareAndMerge {

	typedef enum {
		//! Indicates no error.
		kTWMECNone				= 0,

		//! Indicates that conflicts are still pending so can't generate merged metadata object.
		kTWMECConflictsPending	= 1,

		//! Maximum value this enum can hold, should be treated as invalid value.
		kTWMECMaxValue			= kMaxEnumValue
	} eThreeWayMergeErrorCode;

	typedef enum {
		//! Indicates no error.
		kGSDbNone				= 0,

		//! Indicates that requested generic strategy type is not available.
		kGSDbNotAvailable		= 1,

		//! Maximum value this enum can hold, should be treated as invalid value.
		kGSDbMaxValue = kMaxEnumValue
	} eGenericStrategyDatabaseErrorCode;
}

#endif  // XMPCompareAndMergeErrorCodes_h__

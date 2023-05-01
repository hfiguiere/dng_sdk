#ifndef XMPCompareAndMergeLatestInterfaceVersions_h__
#define XMPCompareAndMergeLatestInterfaceVersions_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#endif  // XMPCompareAndMergeLatestInterfaceVersions_h__

//!
//! @brief Macro to include a client file through with client can control the interface versions he wants to stick with
//! if not the latest ones.
//!
#if !SOURCE_COMPILING_XMPCOMPAREANDMERGE_LIB
	#ifdef XMPCOMPAREANDMERGE_CLIENT_VERSION_NUMBER_FILE
		#include QUOTEME(XMPCOMPAREANDMERGE_CLIENT_VERSION_NUMBER_FILE)
	#endif
#endif

#ifndef ITHREEWAYRESOLVEDCONFLICT_VERSION
	#define ITHREEWAYRESOLVEDCONFLICT_VERSION 1
#endif

#ifndef ITHREEWAYUNRESOLVEDCONFLICT_VERSION
	#define ITHREEWAYUNRESOLVEDCONFLICT_VERSION 1
#endif

#ifndef ITHREEWAYMERGERESULT_VERSION
	#define ITHREEWAYMERGERESULT_VERSION 1
#endif

#ifndef ITHREEWAYSTRATEGY_VERSION
	#define ITHREEWAYSTRATEGY_VERSION 1
#endif

#ifndef ITHREEWAYGENERICSTRATEGY_VERSION
	#define ITHREEWAYGENERICSTRATEGY_VERSION 1
#endif

#ifndef IGENERICSTRATEGYDATABASE_VERSION
	#define IGENERICSTRATEGYDATABASE_VERSION 1
#endif

#ifndef ITHREEWAYMERGE_VERSION
	#define ITHREEWAYMERGE_VERSION 1
#endif

#ifndef ICOMPAREANDMERGEOBJFACTORY_VERSION
	#define ICOMPAREANDMERGEOBJFACTORY_VERSION 1
#endif

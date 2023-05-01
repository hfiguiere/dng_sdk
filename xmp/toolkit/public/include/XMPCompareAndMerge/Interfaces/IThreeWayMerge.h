#ifndef __IThreeWayMerge_h__
#define __IThreeWayMerge_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "XMPCompareAndMerge/XMPCompareAndMergeFwdDeclarations.h"
#include "XMPCommon/Interfaces/BaseInterfaces/ISharedObject.h"
#include "XMPCommon/Interfaces/BaseInterfaces/IVersionable.h"

namespace AdobeXMPCompareAndMerge {
	//!
	//! @brief Version1 of the interface that represents an object which performs 3 way Merge.
	//! Provides all the functions
	//!		- to perform 3 way merge.
	//!		- to register 3 way conflict resolution strategies for custom conflict resolution.
	//!
	class XMP_PUBLIC IThreeWayMerge_v1
		: public virtual ISharedObject
		, public virtual IVersionable
	{
	public:

		//!
		//! @brief Tries to merge 3 metadata objects which are at the different versions.
		//! \param[in] &baseVersionMetadata a shared pointer to const \#IMetadata object representing the common base version to the user and latest metadata objects.
		//! \param[in] &latestVersionMetadata a shared pointer to const \#IMetadata object representing the latest version available with the client.
		//! \param[in] &userVersionMetadata a shared pointer to const \#IMetadata object representing the user version available with the client.
		//! \return a shared pointer to \#IThreeWayMergeResult containing all the information regarding the merge status and results.
		//!
		virtual spcIThreeWayMergeResult APICALL Merge( const spcIMetadata & baseVersionMetadata, const spcIMetadata & latestVersionMetadata, const spcIMetadata & userVersionMetadata ) const = 0;

		//!
		//! @brief Allows clients to plug in their own conflict resolution strategies.
		//! \param[in] strategy a raw pointer to \#IThreeWayStrategy object which will be used by the conflict resolution engine
		//! to resolve the conflict.
		//!
		virtual bool APICALL RegisterThreeWayStrategy( pIThreeWayStrategy_base strategy ) = 0;

		//!
		//! @brief Allows clients to plug in generic strategies for conflict resolution.
		//! \param[in] strategy a shared pointer to \#IThreeWayGenericStrategy object which will be used by the conflict resolution engine
		//! to resolve the conflict.
		//!
		virtual bool APICALL RegisterThreeWayGenericStrategy( const spIThreeWayGenericStrategy & strategy ) = 0;

		//!
		//! \cond XMP_INTERNAL_DOCUMENTATION
		
		//!
		//! @{
		//! @brief Return the actual raw pointer from the shared pointer, which can be a shared pointer of a proxy class.
		//! \return either a const or non const pointer to IThreeWayMerge interface.
		//!
		virtual pIThreeWayMerge APICALL GetActualIThreeWayMerge() __NOTHROW__ = 0;
		XMP_PRIVATE pcIThreeWayMerge GetActualIThreeWayMerge() const __NOTHROW__ {
			return const_cast< IThreeWayMerge_v1 * >( this )->GetActualIThreeWayMerge();
		}
		//!
		//! @}

		//!
		//! @{
		//! @brief Return the pointer to internal interfaces.
		//! \return either a const or non const pointer to IThreeWayMerge_I interface.
		//!
		virtual AdobeXMPCompareAndMerge_Int::pIThreeWayMerge_I APICALL GetIThreeWayMerge_I() __NOTHROW__ = 0;
		XMP_PRIVATE AdobeXMPCompareAndMerge_Int::pcIThreeWayMerge_I GetIThreeWayMerge_I() const __NOTHROW__ {
			return const_cast< IThreeWayMerge_v1 * >( this )->GetIThreeWayMerge_I();
		}
		//!
		//! @}
		
		//!
		//! {@
		//! @brief Convert raw pointer to shared pointer. The raw pointer is of version 1 interface
		//! where as the returned shared pointer depends on the version client is interested in.
		//! \return shared pointer to const or non constant interface.
		//!
		XMP_PRIVATE static spIThreeWayMerge MakeShared( pIThreeWayMerge_base ptr );
		XMP_PRIVATE static spcIThreeWayMerge MakeShared( pcIThreeWayMerge_base ptr )  {
			return MakeShared( const_cast< pIThreeWayMerge_base >( ptr ) );
		}
		//!
		//! @}

		//!
		//! @brief return the unique ID assigned to the interface.
		//! \return 64 bit unsigned integer representing the unique ID assigned to the interface.
		//!
		XMP_PRIVATE static uint64 GetInterfaceID() { return kIThreeWayMergeID; }

		//!
		//! @brief return the version of the interface.
		//! \return 32 bit unsigned integer representing the version of the interface.
		//!
		XMP_PRIVATE static uint32 GetInterfaceVersion() { return 1; }
		//! \endcond

		// static factory functions

		//!
		//! @brief Creates an IThreeWayMerge object.
		//! \return a shared pointer to an IThreeWayMerge object
		//!
		XMP_PRIVATE static spIThreeWayMerge CreateThreeWayMerge();


	protected:
		//!
		//! Destructor
		//! 
		virtual ~IThreeWayMerge_v1() __NOTHROW__ {}

		//! \cond XMP_INTERNAL_DOCUMENTATION
		virtual pcIThreeWayMergeResult_base APICALL merge( pcIMetadata_base baseVersionMetadata, pcIMetadata_base latestVersionMedata, pcIMetadata_base userVersionMetadata, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual uint32 APICALL registerThreeWayStrategy( pIThreeWayStrategy_base strategy, pcIError_base & error ) __NOTHROW__ = 0;
		virtual uint32 APICALL registerThreeWayGenericStrategy( pIThreeWayGenericStrategy_base strategy, pcIError_base & error ) __NOTHROW__ = 0;

		#ifdef FRIEND_CLASS_DECLARATION
			FRIEND_CLASS_DECLARATION();
		#endif
		REQ_FRIEND_CLASS_DECLARATION();
		//! \endcond

	};
}

#endif  // __IThreeWayMerge_h__

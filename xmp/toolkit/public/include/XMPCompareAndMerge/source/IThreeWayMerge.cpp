// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

namespace AdobeXMPCompareAndMerge {
	class IThreeWayMergeProxy;
}

#define FRIEND_CLASS_DECLARATION() friend class AdobeXMPCompareAndMerge::IThreeWayMergeProxy;

#include "XMPCompareAndMerge/Interfaces/IThreeWayMerge.h"

#if !BUILDING_XMPCOMPAREANDMERGE_LIB && !SOURCE_COMPILING_XMPCOMPAREANDMERGE_LIB

#include "XMPCommon/Utilities/TWrapperFunctions.h"
#include "XMPCompareAndMerge/Interfaces/ICompareAndMergeObjectFactory.h"
#include <assert.h>

#include "XMPCore/Interfaces/IMetadata.h"
#include "XMPCompareAndMerge/Interfaces/IThreeWayMergeResult.h"
#include "XMPCompareAndMerge/Interfaces/IThreeWayGenericStrategy.h"

namespace AdobeXMPCompareAndMerge {

	class IThreeWayMergeProxy
		: public virtual IThreeWayMerge
	{
	private:
		pIThreeWayMerge mRawPtr;

	public:
		IThreeWayMergeProxy( pIThreeWayMerge ptr )
			: mRawPtr( ptr )
		{
			mRawPtr->Acquire();
		}

		~IThreeWayMergeProxy() __NOTHROW__ { mRawPtr->Release(); }

		pIThreeWayMerge APICALL GetActualIThreeWayMerge() __NOTHROW__ { return mRawPtr; }

		void APICALL Acquire() const __NOTHROW__ { assert( false ); }

		void APICALL Release() const __NOTHROW__ { assert( false ); }

		AdobeXMPCommon_Int::pISharedObject_I APICALL GetISharedObject_I() __NOTHROW__ {
			return mRawPtr->GetISharedObject_I();
		}

		AdobeXMPCompareAndMerge_Int::pIThreeWayMerge_I APICALL GetIThreeWayMerge_I() __NOTHROW__ {
			return mRawPtr->GetIThreeWayMerge_I();
		}

		pvoid APICALL GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
			return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
				mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
		}

		pvoid APICALL getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
			assert( false );
			return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
		}

		virtual spcIThreeWayMergeResult APICALL Merge( const spcIMetadata & baseVersionMetadata, const spcIMetadata & latestVersionMedata, const spcIMetadata & userVersionMetadata ) const {
			return CallConstSafeFunctionReturningPointer< IThreeWayMerge_v1, pcIThreeWayMergeResult_base, const IThreeWayMergeResult, pcIMetadata_base, pcIMetadata_base, pcIMetadata_base >(
				mRawPtr, &IThreeWayMerge_v1::merge, baseVersionMetadata ? baseVersionMetadata->GetActualIMetadata() : NULL, latestVersionMedata ? latestVersionMedata->GetActualIMetadata() : NULL,
				userVersionMetadata ? userVersionMetadata->GetActualIMetadata() : NULL );
		}

		virtual bool APICALL RegisterThreeWayGenericStrategy( const spIThreeWayGenericStrategy & strategy ) {
			return CallSafeFunction< IThreeWayMerge_v1, bool, uint32, pIThreeWayGenericStrategy_base >(
				mRawPtr, &IThreeWayMerge_v1::registerThreeWayGenericStrategy, strategy ? strategy->GetActualIThreeWayGenericStrategy() : NULL );
		}

		virtual uint32 APICALL registerThreeWayGenericStrategy( pIThreeWayGenericStrategy_base strategy, pcIError_base & error ) __NOTHROW__ {
			assert( false );
			return mRawPtr->registerThreeWayGenericStrategy( strategy, error );
		}

		virtual bool APICALL RegisterThreeWayStrategy( pIThreeWayStrategy_base strategy ) {
			return CallSafeFunction< IThreeWayMerge_v1, bool, uint32, pIThreeWayStrategy_base >(
				mRawPtr, &IThreeWayMerge_v1::registerThreeWayStrategy, strategy );
		}

		virtual pcIThreeWayMergeResult_base APICALL merge( pcIMetadata_base baseVersionMetadata, pcIMetadata_base latestVersionMedata, pcIMetadata_base userVersionMetadata, pcIError_base & error ) const __NOTHROW__ {
			assert( false );
			return mRawPtr->merge( baseVersionMetadata, latestVersionMedata, userVersionMetadata, error );
		}

		virtual uint32 APICALL registerThreeWayStrategy( pIThreeWayStrategy_base strategy, pcIError_base & error ) __NOTHROW__ {
			assert( false );
			return mRawPtr->registerThreeWayStrategy( strategy, error );
		}

	};

	spIThreeWayMerge IThreeWayMerge_v1::MakeShared( pIThreeWayMerge_base ptr ) {
		if ( !ptr ) return spIThreeWayMerge();
		pIThreeWayMerge p = IThreeWayMerge::GetInterfaceVersion() > 1 ?
			ptr->GetInterfacePointer< IThreeWayMerge >() : ptr;
		return shared_ptr< IThreeWayMerge >( new IThreeWayMergeProxy( p ) );
	}

	spIThreeWayMerge IThreeWayMerge_v1::CreateThreeWayMerge() {
		return CallSafeFunctionReturningPointer< ICompareAndMergeObjectFactory, pIThreeWayMerge_base, IThreeWayMerge >(
			ICompareAndMergeObjectFactory::GetCompareAndMergeObjectFactory(), &ICompareAndMergeObjectFactory::CreateThreeWayMerge);
	}

}

#endif  // !BUILDING_XMPCOMPAREANDMERGE_LIB && !SOURCE_COMPILING_XMPCOMPAREANDMERGE_LIB
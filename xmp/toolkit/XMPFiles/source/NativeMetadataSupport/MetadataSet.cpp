// =================================================================================================
// Copyright Adobe
// Copyright 2010 Adobe
// All Rights Reserved
//
// NOTICE: Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. If you have received this file from a source other 
// than Adobe, then your use, modification, or distribution of it requires the prior written permission
// of Adobe.
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//	JEH Joerg Ehrlich
//	PW	Patrick Wolleck
//
// mm-dd-yy who Description of changes, most recent on top
//
// 10-26-10 PW  5.3-f015 Integration from winwood
//							New design for Reconciliation code
// 07-28-10	JEH	5.2-f001 Initial creation of new AIFF handler.
//
// =================================================================================================
#endif // AdobePrivate


#include "XMPFiles/source/NativeMetadataSupport/MetadataSet.h"
#include "source/XMP_LibUtils.hpp"

//-----------------------------------------------------------------------------
// 
// MetadataSet::MetadataSet(...)
// 
// Purpose: ctor/dtor
// 
//-----------------------------------------------------------------------------

MetadataSet::MetadataSet()
:	mMeta	( NULL )
{
}

MetadataSet::~MetadataSet()
{
	delete mMeta;
}

//-----------------------------------------------------------------------------
// 
// MetadataSet::append(...)
// 
// Purpose: Append metadata container
// 
//-----------------------------------------------------------------------------

void MetadataSet::append( IMetadata* meta )
{
	if( mMeta == NULL )
	{
		mMeta = new std::vector<IMetadata*>;
	}

	mMeta->push_back( meta );
}

//-----------------------------------------------------------------------------
// 
// MetadataSet::removeAt(...)
// 
// Purpose: Remove metadata container at passed position
// 
//-----------------------------------------------------------------------------

void MetadataSet::removeAt( XMP_Uns32 pos )
{
	if( mMeta != NULL && pos < mMeta->size() )
	{
		mMeta->erase( mMeta->begin() + pos );
	}
	else
	{
		XMP_Throw( "Index out of range.", kXMPErr_BadIndex );
	}
}

//-----------------------------------------------------------------------------
// 
// MetadataSet::remove(...)
// 
// Purpose: Remove the last metadata container inside the vector
// 
//-----------------------------------------------------------------------------

void MetadataSet::remove()
{
	if( mMeta != NULL )
	{
		mMeta->pop_back();
	}
}

//-----------------------------------------------------------------------------
// 
// MetadataSet::length(...)
// 
// Purpose: Return the number of stored metadata container
// 
//-----------------------------------------------------------------------------

XMP_Uns32 MetadataSet::length() const
{
	XMP_Uns32 ret = 0;

	if( mMeta != NULL )
	{
		ret = (XMP_Uns32)mMeta->size();
	}

	return ret;
}

//-----------------------------------------------------------------------------
// 
// MetadataSet::getAt(...)
// 
// Purpose: Return metadata container of passed position.
// 
//-----------------------------------------------------------------------------

IMetadata* MetadataSet::getAt( XMP_Uns32 pos ) const
{
	IMetadata* ret = NULL;

	if( mMeta != NULL && pos < mMeta->size() )
	{
		ret = mMeta->at(pos);
	}
	else
	{
		XMP_Throw( "Index out of range.", kXMPErr_BadIndex );
	}

	return ret;
}

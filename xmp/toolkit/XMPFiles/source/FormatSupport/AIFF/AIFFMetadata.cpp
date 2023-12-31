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
//	PW Patrick Wollek
//
// mm-dd-yy who Description of changes, most recent on top
//
// 10-26-10 PW  5.3-f015 Integration from winwood
//							New design for Reconciliation code
//							Initial creation of new WAVE handler.
//
// =================================================================================================
#endif // AdobePrivate

#include "public/include/XMP_Environment.h"	// ! XMP_Environment.h must be the first included header.
#include "public/include/XMP_Const.h"

#include "XMPFiles/source/FormatSupport/AIFF/AIFFMetadata.h"

using namespace IFF_RIFF;

//-----------------------------------------------------------------------------
// 
// AIFFMetadata::AIFFMetadata(...)
// 
// Purpose: ctor/dtor
// 
//-----------------------------------------------------------------------------

AIFFMetadata::AIFFMetadata()
{
}

AIFFMetadata::~AIFFMetadata()
{
}

//-----------------------------------------------------------------------------
// 
// AIFFMetadata::isEmptyValue(...)
// 
// Purpose: Is the value of the passed ValueObject and its id "empty"?
// 
//-----------------------------------------------------------------------------

bool AIFFMetadata::isEmptyValue( XMP_Uns32 id, ValueObject& valueObj )
{
	TValueObject<std::string>* strObj = dynamic_cast<TValueObject<std::string>*>(&valueObj);

	return ( strObj == NULL || ( strObj != NULL && strObj->getValue().empty() ) );
}

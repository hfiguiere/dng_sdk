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

#ifndef _MetadataSet_h_
#define _MetadataSet_h_

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

#include "public/include/XMP_Environment.h"	// ! This must be the first include.
#include "public/include/XMP_Const.h"
#include <vector>

/**
	The class MetadataSet acts as a container for any metadata that base on
	the interface IMeta.
*/

class IMetadata;

class MetadataSet
{
	public:
		/**
			ctor/dtor
		*/
								MetadataSet	();
							   ~MetadataSet	();

		/**
			Append metadata container

			@param	meta	Metadata container
		*/
		void					append		( IMetadata* meta );

		/**
			Remove metadata container at passed position

			@param	pos		Position inside the vector of metadata
		*/
		void					removeAt	( XMP_Uns32 pos );

		/**
			Remove the last metadata container inside the vector
		*/
		void					remove		();

		/**
			Return the number of stored metadata container

			@return length of vector
		*/
		XMP_Uns32				length		() const;

		/**
			Return metadata container of passed position.

			@param	pos		Position inside of the vector of metadata
		*/
		IMetadata*		getAt				( XMP_Uns32 pos ) const;

		/**
			Return metadata container of passed type

			@return stored metadata container of type T
		*/
		template<class T> T*	get			() const;

	private:
		std::vector<IMetadata*>*					mMeta;
		typedef std::vector<IMetadata*>::iterator	MetaIterator;

}; // MetadataSet

template<class T> T* MetadataSet::get() const
{
	T* ret = NULL;

	if( mMeta != NULL )
	{
		for( MetaIterator iter = mMeta->begin(); iter != mMeta->end(); iter++ )
		{
			T* tmp = dynamic_cast<T*>( *iter );

			if( tmp != NULL )
			{
				ret = tmp;
				break;
			}
		}
	}

	return ret;
}

#endif

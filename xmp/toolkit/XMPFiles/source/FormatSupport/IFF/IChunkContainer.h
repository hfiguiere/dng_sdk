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

#ifndef _IChunkContainer_h_
#define _IChunkContainer_h_

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//	JEH Joerg Ehrlich
//	PW	Patrick Wollek
//
// mm-dd-yy who Description of changes, most recent on top
//
// 10-26-10 PW  5.3-f015 Integration from winwood
//							New WAVE Handler and Common code refactoring
//							[2732321] WAV/AIFF: An update causes the file to grow unproportional to the added data
// 07-28-10	JEH	5.2-f001 Initial creation of new AIFF handler.
//
// =================================================================================================
#endif // AdobePrivate


#include "public/include/XMP_Environment.h"	// ! This must be the first include.

namespace IFF_RIFF
{

/**
	The interface IChunkContainer defines the access to child chunks of 
	an existing chunk.
*/

class Chunk;

class IChunkContainer
{
public:
	virtual ~IChunkContainer() {};

		/**
		 * @return	Returns the number children chunks.
		 */
		virtual	XMP_Uns32 numChildren() const															= 0;
		
		/**
		 * Returns a child node.
		 *
		 * @param	pos		position of the child node to return
		 * @return			Returns the child node at the given position.
		 */
		virtual	Chunk* getChildAt( XMP_Uns32 pos ) const												= 0;

		/**
		 * Appends a child node at the end of the children list.
		 *
		 * @param	node		the new node
		 * @param	adjustSizes	adjust size&offset of chunk and parents
		 * @return				Returns the added node.
		 */
		virtual	void appendChild( Chunk* node, XMP_Bool adjustSizes = true )							= 0;

		/**
		 * Inserts a child node at a certain position.
		 *
		 * @param	pos			position in the children list to add the new node
		 * @param	node		the new node
		 * @return				Returns the added node.
		 */
		virtual	void insertChildAt( XMP_Uns32 pos, Chunk* node )			= 0;

		/**
		 * Removes a child node at a given position.
		 *
		 * @param	pos				position of the node to delete in the children list
		 *
		 * @return					The removed chunk
		 */
		virtual	Chunk* removeChildAt( XMP_Uns32 pos )						= 0;

		/**
		 * Remove child at the passed position and insert the new chunk
		 *
		 * @param pos			Position of chunk that will be replaced
		 * @param chunk			New chunk
		 *
		 * @return				Replaced chunk
		 */
		virtual Chunk* replaceChildAt( XMP_Uns32 pos, Chunk* node )						= 0;

		/** creates a string representation of the chunk and its children. 
		*/
		virtual std::string toString( std::string tab = std::string() , XMP_Bool showOriginal = false ) = 0;
};

}

#endif

						   // =================================================================================================
// Copyright 2006-2007 Adobe
// All Rights Reserved.
//
// NOTICE:	Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. If you have received this file from a source other 
// than Adobe, then your use, modification, or distribution of it requires the prior written permission
// of Adobe.
// =================================================================================================

#ifndef _XMPFileFactory_h
#define _XMPFileFactory_h

#include "XMPBase.h"


/**
Factory for the XMPFile-object.
*/
class XMPFileFactory : public XMPBase
{
	/** the properties manager */
	ScCore::LivePropertyManager	properties;

public:
	/** constructor */
	XMPFileFactory();


	/**
	Factory support: clone this object.
	@param	newObj				takes the newly created object
	@param	cloneAll			if false, do not clone dynamic properties
	@return						an error code (0 for no error)
	*/
	virtual	scerror_t			clone (ScCore::LiveObject** newObj, bool deepClone = true) const;
	

	/**
	Read the value of a property. Return 0 if the property could
	be read, an error code otherwise.
	@param	id					the property ID
	@param	value				the location to take the value
	@param	errors				an optional pointer to extended error information
	@return						kErrUndefined
	*/
	virtual	scerror_t			get (int32_t id, ScCore::Variant& value, ScCore::Error* errors = null) const;
	
	
	/**
	Call a method. Return 0 if the method could be called, an error code otherwise.
	@param	id					the property ID
	@param	args				the method arguments
	@param	result				the return value.
	@param	errors				an optional pointer to extended error information
	@return						kErrUndefined
	*/
	virtual	scerror_t			call (int32_t id, const ScCore::Array& args, 
									  ScCore::Variant& result, ScCore::Error* errors = null);


	/** destructor */
	~XMPFileFactory();
};

#endif

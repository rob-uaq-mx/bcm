#ifndef BCM_IDENTIFIER_DATA_H
#define BCM_IDENTIFIER_DATA_H

/**
@file identifierdata.h
@brief Identifiable object data.

This file contains a struct containing pointers to both
a constant ID and a constant name C-style strings used to define
an entity, namely, an interface or a component.
*/

namespace bcm {

	struct IdentifierData
	{
		const char *id;
		const char *name;
	};

} // namespace bcm

#endif


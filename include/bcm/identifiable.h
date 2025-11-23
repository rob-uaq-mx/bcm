#ifndef BCM_IDENTIFIABLE_H
#define BCM_IDENTIFIABLE_H

/**
@file identifiable.h
@brief Identifiable object interface.

This file contains a struct containing pure virtual functions
that define the format for an ID and a name used to define
an entity, namely, an interface or a component.
*/

namespace bcm {

	/**
	@struct Identifiable
	@brief Identifiable object abstract struct.

	This struct defines the format for and ID and a name
	a component or an interface provides.
	*/

	struct Identifiable
	{
		virtual const char *getID() = 0;
		virtual const char *getName() = 0;
	};

} // namespace bcm

#endif


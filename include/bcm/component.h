#ifndef BCM_COMPONENT_H
#define BCM_COMPONENT_H

/**
@file component.h
@brief Component base class (struct).

Every component must implement the identifiable object
properties along with a basic set of methods for
dealing with interfaces.
*/

#include <bcm/identifiable.h>
#include <bcm/identifierdata.h>
#include <bcm/interface.h>

namespace bcm {

        /**
        @struct Component
        @brief Component abstract base struct.

        This struct defines a component (implementation) as an
        identifiable object, and requires every component to
        implement a basic set of methods for dealing with interfaces.
        */

	struct Component : public Identifiable
	{
		virtual IdentifierData *getProvidedInterfaceTable() = 0;
		virtual IdentifierData *getRequiredInterfaceTable() = 0;
		virtual Interface *getInterface(const char *id) = 0;
		virtual bool setInterface(Interface *iface) = 0;
	};

} // namespace bcm

#endif


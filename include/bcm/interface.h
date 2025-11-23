#ifndef BCM_INTERFACE_H
#define BCM_INTERFACE_H

/**
@file interface.h
@brief Interface base class.

Every interface must implement the identifiable object
properties.
*/

#include <bcm/identifiable.h>

namespace bcm {

        /**
        @struct Interface
        @brief Interface abstract base struct.

        This struct defines an interface (implementation) as an
        identifiable object.
        */

	struct Interface : public Identifiable
	{
	};

} // namespace bcm

#endif


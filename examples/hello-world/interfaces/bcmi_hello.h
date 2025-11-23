#ifndef BCM_INTERFACE_HELLO_H
#define BCM_INTERFACE_HELLO_H

#include "ihello.h"
#include <bcm/bcm.h>

struct BCMI_HelloInterface :
	public bcm::Interface,
	public virtual HelloInterface
{
};

#endif


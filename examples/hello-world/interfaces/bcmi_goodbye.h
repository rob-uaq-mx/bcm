#ifndef BCM_INTERFACE_GOODBYE_H
#define BCM_INTERFACE_GOODBYE_H

#include "igoodbye.h"
#include <bcm/bcm.h>

struct BCMI_GoodbyeInterface :
	public bcm::Interface,
	public virtual GoodbyeInterface
{
};

#endif


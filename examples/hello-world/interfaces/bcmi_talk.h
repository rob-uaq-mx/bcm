#ifndef BCM_INTERFACE_TALK_H
#define BCM_INTERFACE_TALK_H

#include "italk.h"
#include <bcm/bcm.h>

struct BCMI_TalkInterface :
    public bcm::Interface,
    public virtual TalkInterface
{
};

#endif


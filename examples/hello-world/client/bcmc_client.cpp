#include "bcmc_client.h"

extern "C" bcm::Component *getComponent()
{
	return &BCMC_Client::instance();
}


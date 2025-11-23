#include "bcmc_server.h"

extern "C" bcm::Component *getComponent()
{
	return &BCMC_Server::instance();
}


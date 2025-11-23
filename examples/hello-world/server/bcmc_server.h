#ifndef BCM_COMPONENT_SERVER_H
#define BCM_COMPONENT_SERVER_H

#include "bcmi_hello.h"
#include "bcmi_goodbye.h"
#include "server.h"
#include <bcm/bcm.h>
#include <iostream>
#include <string>

//#pragma warning(disable : 4250)
class BCMC_Server :
	public bcm::Identifier<bcm::Component>,
	protected bcm::Identifier<BCMI_HelloInterface>,
	protected bcm::Identifier<BCMI_GoodbyeInterface>,
	protected Server
{
protected:
	BCMC_Server() :
        bcm::Identifier<bcm::Component>("server", "Example server"),
		bcm::Identifier<BCMI_HelloInterface>("hello", "Hello there"),
		bcm::Identifier<BCMI_GoodbyeInterface>("goodbye", "See you")
	{
	}
	virtual bcm::IdentifierData *getProvidedInterfaceTable()
	{
		static bcm::IdentifierData idData[] = {
			{ "hello", "Hello there" },
			{ "goodbye", "See you" },
			{ 0, 0 }
		};
		return idData;
	}
	virtual bcm::IdentifierData *getRequiredInterfaceTable()
	{
		static bcm::IdentifierData idData[] = {
			{ 0, 0 }
		};
		return idData;
	}
	virtual bcm::Interface *getInterface(const char *id)
	{
		std::cout << "Interface requested to server: " << id << std::endl;
		if (std::string("hello") == id)
			return static_cast<BCMI_HelloInterface *>(this);
		if (std::string("goodbye") == id)
			return static_cast<BCMI_GoodbyeInterface *>(this);
		return 0;
	}
	virtual bool setInterface(bcm::Interface *iface)
	{
		return false;
	}
public:
	static BCMC_Server &instance()
	{
		static BCMC_Server object;
		return object;
	}
};

#endif


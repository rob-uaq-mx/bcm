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
	bcm::IdentifierData *getProvidedInterfaceTable() override
	{
		static bcm::IdentifierData idData[] = {
			{ "hello", "Hello there" },
			{ "goodbye", "See you" },
			{ nullptr, nullptr }
		};
		return idData;
	}
	bcm::IdentifierData *getRequiredInterfaceTable() override
	{
		static bcm::IdentifierData idData[] = {
			{ nullptr, nullptr }
		};
		return idData;
	}
	bcm::Interface *getInterface(const char *id) override
	{
		std::cout << "Interface requested to server: " << id << std::endl;
		if (std::string("hello") == id)
			return static_cast<BCMI_HelloInterface *>(this);
		if (std::string("goodbye") == id)
			return static_cast<BCMI_GoodbyeInterface *>(this);
		return nullptr;
	}
	bool setInterface(bcm::Interface *iface) override
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


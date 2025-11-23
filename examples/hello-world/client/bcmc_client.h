#ifndef BCM_COMPONENT_CLIENT_H
#define BCM_COMPONENT_CLIENT_H

#include "bcmi_talk.h"
#include "bcmi_hello.h"
#include "bcmi_goodbye.h"
#include "client.h"
#include <bcm/bcm.h>
#include <iostream>
#include <string>

//#pragma warning(disable : 4250)
class BCMC_Client :
    public bcm::Identifier<bcm::Component>,
	protected bcm::Identifier<BCMI_TalkInterface>,
	protected Client
{
protected:
	BCMC_Client() :
		bcm::Identifier<bcm::Component>("client", "Example client"),
		bcm::Identifier<BCMI_TalkInterface>("talk", "Talk to me")
	{
	}
	virtual bcm::IdentifierData *getProvidedInterfaceTable()
	{
		static bcm::IdentifierData idData[] = {
			{ "talk", "Talk to me" },
			{ 0, 0 }
		};
		return idData;
	}
	virtual bcm::IdentifierData *getRequiredInterfaceTable()
	{
		static bcm::IdentifierData idData[] = {
			{ "hello", "Hello there" },
			{ "goodbye", "See you" },
			{ 0, 0 }
		};
		return idData;
	}
	virtual bcm::Interface *getInterface(const char *id)
	{
		if (std::string("talk") == id)
			return static_cast<BCMI_TalkInterface *>(this);
		return 0;
	}
	virtual bool setInterface(bcm::Interface *iface)
	{
		if (iface == 0) {
			std::cout << "Interface is null." << std::endl;
			return false;
		} else {
			std::cout << "Interface is " << static_cast<void *>(iface) << '.' << std::endl;
		}
		if (std::string("hello") == iface->getID()) {
			helloInterface_ = dynamic_cast<BCMI_HelloInterface *>(iface);
			std::cout << "helloInterface_ is now " << static_cast<void *>(helloInterface_) << '.' << std::endl;
		} else if (std::string("goodbye") == iface->getID()) {
			goodbyeInterface_ = dynamic_cast<BCMI_GoodbyeInterface *>(iface);
			std::cout << "goodbyeInterface_ is now " << static_cast<void *>(goodbyeInterface_) << '.' << std::endl;
		} else
			return false;
		return true;
	}
public:
	static BCMC_Client &instance()
	{
		static BCMC_Client object;
		return object;
	}
};

#endif


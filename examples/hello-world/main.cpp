#include "bcmc_client.h"
#include "bcmc_server.h"
#include <bcm/bcm.h>
#include <iostream>

#ifdef __linux__
#define TEXT(string_literal) string_literal
#define SERVER_FILE TEXT("./server.so")
#define CLIENT_FILE TEXT("./client.so")
#endif
#ifdef _WIN32
#define SERVER_FILE TEXT("server.dll")
#define CLIENT_FILE TEXT("client.dll")
#endif


int main()
{
	bcm::ComponentManager &compMgr = bcm::ComponentManager::instance();
    switch (compMgr.loadComponent(SERVER_FILE)) {
    case bcm::LC_NODLL:
    case bcm::LC_NOCOMPONENT:
		std::cout << "Could not load dynamic link library for server." << std::endl;
		return 1;
    case bcm::LC_ALREADYUSED:
    case bcm::LC_OK:
        break;
    }
    switch (compMgr.loadComponent(CLIENT_FILE)) {
    case bcm::LC_NODLL:
    case bcm::LC_NOCOMPONENT:
		std::cout << "Could not load dynamic link library for client." << std::endl;
		return 1;
    case bcm::LC_ALREADYUSED:
    case bcm::LC_OK:
        break;
    }
	bcm::Component *server;
    switch (compMgr.getComponent("server", &server)) {
    case bcm::GC_UNREGISTERED:
        std::cout << "No registered dynamic link library contains a server component.";
        return 1;
    case bcm::GC_NOCOMPONENT:
        std::cout << "Dynamic link library for the server does not contain the server (this should never happen!).";
        return 1;
    case bcm::GC_INCOMPLETE:
        std::cout << "Server load incomplete.";
        return 1;
    case bcm::GC_OK:
        break;
    }
	bcm::Component *client;
    switch (compMgr.getComponent("client", &client)) {
    case bcm::GC_UNREGISTERED:
        std::cout << "No registered dynamic link library contains a client component.";
        return 1;
    case bcm::GC_NOCOMPONENT:
        std::cout << "Dynamic link library for the server does not contain the client (this should never happen!).";
        return 1;
    case bcm::GC_INCOMPLETE:
        std::cout << "Client load incomplete.";
        return 1;
    case bcm::GC_OK:
        break;
    }
	bcm::IdentifierData *ifaces;
	ifaces = server->getProvidedInterfaceTable();
	std::cout << "Interfaces provided by server:" << std::endl;
	for (int i = 0; ifaces[i].id != 0; i++)
		std::cout << ifaces[i].id << '\t' << ifaces[i].name << std::endl;
	bcm::Interface *iface;
	iface = server->getInterface("hello");
	if (iface == 0) {
		std::cout << "Could not read interface \"hello\" from server." << std::endl;
		return 1;
	}
	if (client->setInterface(iface) == false) {
		std::cout << "Could not assign \"hello\" interface to client." << std::endl;
		return 1;
	}
    iface = server->getInterface("goodbye");
	if (iface == 0) {
		std::cout << "Could not read interface \"goodbye\" from server." << std::endl;
		return 1;
	}
	if (client->setInterface(iface) == false) {
		std::cout << "Could not assign \"goodbye\" interface to client." << std::endl;
		return 1;
	}
	iface = client->getInterface("talk");
	if (iface == 0) {
		std::cout << "Could not read \"talk\" from client." << std::endl;
		return 1;
	}
	BCMI_TalkInterface *speaker = dynamic_cast<BCMI_TalkInterface *>(iface);
	if (speaker != 0)
		speaker->talk();
	return 0;
}


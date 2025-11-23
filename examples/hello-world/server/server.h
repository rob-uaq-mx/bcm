#ifndef COMPONENT_SERVER_H
#define COMPONENT_SERVER_H

#include "ihello.h"
#include "igoodbye.h"
#include <iostream>
#include <string>

class Server :
	protected virtual HelloInterface,
	protected virtual GoodbyeInterface
{
	virtual void hello()
	{
		std::cout << "Hello" << std::endl;
	}
	virtual void goodbye()
	{
		std::cout << "Goodbye" << std::endl;
	}
};

#endif


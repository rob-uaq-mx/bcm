#ifndef COMPONENT_CLIENT_H
#define COMPONENT_CLIENT_H

#include "italk.h"
#include "ihello.h"
#include "igoodbye.h"
#include <iostream>
#include <string>

class Client :
	protected virtual TalkInterface
{
protected:
	HelloInterface *helloInterface_;
	GoodbyeInterface *goodbyeInterface_;
	Client() :
		helloInterface_(0), goodbyeInterface_(0)
	{
	}
private:
	void talk()
	{
		if (helloInterface_ != 0)
			helloInterface_->hello();
		else
			std::cout << "The \"hello\" interface is null." << std::endl;
		if (goodbyeInterface_ != 0)
			goodbyeInterface_->goodbye();
		else
			std::cout << "The \"goodbye\" interface is null." << std::endl;
	}
};

#endif

#ifndef BCM_INTERFACE_IDENTIFIER_H
#define BCM_INTERFACE_IDENTIFIER_H

/**
@file identifier.h
@brief Identifiable object identifier utility class.

A mixin idiom-based utility class to
help implement the identifiable object properties.
*/

#include <string>

namespace bcm {

        /**
        @class Identifier
        @brief Identifiable object implementation utility class.

        This class template provides an implementation base class
        for an identifiable object.
        */

	template <class T>
	class Identifier : public T
	{
		std::string id_;
		std::string name_;
	public:
		Identifier(const char *id, const char *name)
			: id_(id), name_(name)
		{
		}
		virtual const char *getID()
		{
			return id_.c_str();
		}
		virtual const char *getName()
		{
			return name_.c_str();
		}
	};

} // namespace bcm

#endif


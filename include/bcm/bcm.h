#ifndef BCM_H
#define BCM_H

/**
@file bcm.h
@brief Basic Component Model (BCM) main header file.

This file includes all the required BCM header files.
*/

#include <bcm/identifiable.h>
#include <bcm/identifier.h>
#include <bcm/identifierdata.h>
#include <bcm/interface.h>
#include <bcm/component.h>
#ifdef __linux__
#include <bcm/linux/dll.h>
#include <bcm/linux/componentmgr.h>
#endif // __linux__
#ifdef _WIN32
#include <bcm/win32/dll.h>
#include <bcm/win32/componentmgr.h>
#endif // _WIN32

#endif



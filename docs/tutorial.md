## Binary Component Model (BCM) Tutorial

This tutorial demonstrates how to build component-based applications using BCM
through a simple client-server example. You'll learn how to create pluggable
components with minimal boilerplate code.


## WHAT IS BCM?

BCM is a lightweight C++ framework for building modular applications from
independently compiled components (dynamic libraries). Unlike CORBA, COM, or
other component frameworks, BCM requires:
  - NO Interface Definition Language (IDL)
  - NO code generation or stub/skeleton compilers
  - NO complex marshaling or registry configuration
  - Just pure C++ interfaces and simple inheritance

The entire core framework fits in 6 small header files. Learning curve: hours,
not weeks.


## KEY CONCEPTS

Components in BCM:
  1. PROVIDE interfaces - services they offer to other components
  2. REQUIRE interfaces - services they need from other components
  3. Are loaded dynamically at runtime as DLLs (Windows) or .so files (Linux)
  4. Are wired together by the ComponentManager based on their dependencies


## TUTORIAL: BUILDING A CLIENT-SERVER SYSTEM

We'll build a system with two components:
  - SERVER: provides "hello" and "goodbye" services
  - CLIENT: requires "hello" and "goodbye", provides "talk" service


### STEP 1: Define Your Service Interfaces

First, define what services you need using pure C++ abstract interfaces.
No special syntax, no IDL files - just virtual functions:

```cpp
// ihello.h
struct HelloInterface {
    virtual void hello() = 0;
};
```

```cpp
// igoodbye.h
struct GoodbyeInterface {
    virtual void goodbye() = 0;
};
```

These are plain C++ interfaces that any C++ programmer already knows.


### STEP 2: Create BCM Interface Wrappers

To use these interfaces with BCM, create simple wrapper structs that inherit
from both bcm::Interface and your service interface:

```cpp
// bcmi_hello.h
#include <bcm/bcm.h>
#include "ihello.h"
```

```cpp
struct BCMI_HelloInterface :
    public bcm::Interface,           // Makes it a BCM interface
    public virtual HelloInterface    // Your actual service contract
{
};
```

The "BCMI_" prefix is a convention meaning "BCM Interface". This wrapper
makes your interface identifiable within the BCM system (it gets an ID and name).


### STEP 3: Implement a Component

Now create a component that provides these interfaces. Here's the pattern:

```cpp
class BCMC_Server :
    public bcm::Identifier<bcm::Component>,      // Base component with ID
    protected bcm::Identifier<BCMI_HelloInterface>,   // Hello interface
    protected bcm::Identifier<BCMI_GoodbyeInterface>, // Goodbye interface
    protected Server  // Your actual implementation class
{
protected:
    BCMC_Server() :
        bcm::Identifier<bcm::Component>("server", "Example server"),
        bcm::Identifier<BCMI_HelloInterface>("hello", "Hello there"),
        bcm::Identifier<BCMI_GoodbyeInterface>("goodbye", "See you")
    {
    }
```

The bcm::Identifier<T> template is a mixin that provides the ID and name for
each identifiable entity. This eliminates boilerplate - you don't need to
manually store ID strings or implement getID()/getName() methods.

Why multiple inheritance? Each Identifier<T> handles one aspect:
  - Identifier<Component>: Makes this a valid BCM component
  - Identifier<BCMI_HelloInterface>: Provides ID for "hello" interface
  - Identifier<BCMI_GoodbyeInterface>: Provides ID for "goodbye" interface


### STEP 4: Declare Provided and Required Interfaces

Each component must declare what it provides and requires using simple tables:

```cpp
    virtual bcm::IdentifierData *getProvidedInterfaceTable()
    {
        static bcm::IdentifierData idData[] = {
            { "hello", "Hello there" },
            { "goodbye", "See you" },
            { 0, 0 }  // Null terminator
        };
        return idData;
    }
```

```cpp
    virtual bcm::IdentifierData *getRequiredInterfaceTable()
    {
        static bcm::IdentifierData idData[] = {
            { 0, 0 }  // Empty - server needs nothing
        };
        return idData;
    }
```

These tables tell the ComponentManager which interfaces this component offers
and needs. The arrays are null-terminated (like C strings).


### STEP 5: Implement Interface Accessors

Components need to provide and accept interface pointers:

```cpp
    virtual bcm::Interface *getInterface(const char *id)
    {
        if (std::string("hello") == id)
            return static_cast<BCMI_HelloInterface *>(this);
        if (std::string("goodbye") == id)
            return static_cast<BCMI_GoodbyeInterface *>(this);
        return 0;  // Interface not found
    }
```

```cpp
    virtual bool setInterface(bcm::Interface *iface)
    {
        return false;  // Server doesn't need any interfaces
    }
```

The server provides interfaces via getInterface(). Since it requires nothing,
setInterface() just returns false.

For a CLIENT component that requires interfaces, setInterface() would look like:

```cpp
    virtual bool setInterface(bcm::Interface *iface)
    {
        if (std::string("hello") == iface->getID()) {
            helloInterface_ = dynamic_cast<BCMI_HelloInterface *>(iface);
            return true;
        }
        if (std::string("goodbye") == iface->getID()) {
            goodbyeInterface_ = dynamic_cast<BCMI_GoodbyeInterface *>(iface);
            return true;
        }
        return false;  // Unknown interface
    }
```


### STEP 6: Use the Singleton Pattern

BCM components typically use singletons for simplicity:

```cpp
public:
    static BCMC_Server &instance()
    {
        static BCMC_Server object;
        return object;
    }
};
```


### STEP 7: Export the Component from the DLL

This is the crucial part that makes the DLL loadable by BCM. In your .cpp file,
export a C function that returns your component instance:

```cpp
// bcmc_server.cpp
#include "bcmc_server.h"
```

```cpp
extern "C" bcm::Component *getComponent()
{
    return &BCMC_Server::instance();
}
```

The "extern C" prevents C++ name mangling, allowing the ComponentManager to
find this function by name in the DLL. This is the ONLY function you export.


### STEP 8: Load and Wire Components at Runtime

The main application loads components and wires them together:

```cpp
bcm::ComponentManager &compMgr = bcm::ComponentManager::instance();
```

```cpp
// Load DLLs
compMgr.loadComponent("server.dll");
compMgr.loadComponent("client.dll");
```

```cpp
// Get component instances
bcm::Component *server, *client;
compMgr.getComponent("server", &server);
compMgr.getComponent("client", &client);
```

```cpp
// Wire them together: give client the interfaces it needs from server
bcm::Interface *hello = server->getInterface("hello");
bcm::Interface *goodbye = server->getInterface("goodbye");
client->setInterface(hello);
client->setInterface(goodbye);
```

```cpp
// Use the client's "talk" service
bcm::Interface *talk = client->getInterface("talk");
BCMI_TalkInterface *speaker = dynamic_cast<BCMI_TalkInterface *>(talk);
speaker->talk();
```

The wiring is explicit and clear - no hidden magic. The client receives
interface pointers from the server and stores them in member variables.


## COMPLETE EXAMPLE STRUCTURE

This directory contains a complete working example with these files:

Interface Definitions (pure C++):
  - ihello.h        : HelloInterface with hello() method
  - igoodbye.h      : GoodbyeInterface with goodbye() method
  - italk.h         : TalkInterface with talk() method

BCM Interface Wrappers:
  - bcmi_hello.h    : BCMI_HelloInterface (BCM-compatible wrapper)
  - bcmi_goodbye.h  : BCMI_GoodbyeInterface
  - bcmi_talk.h     : BCMI_TalkInterface

Server Component (provides "hello" and "goodbye"):
  - server.h        : Server implementation class (business logic)
  - bcmc_server.h   : BCMC_Server component class (BCM wrapper)
  - bcmc_server.cpp : Component export (getComponent function)

Client Component (requires "hello" and "goodbye", provides "talk"):
  - client.h        : Client implementation class (business logic)
  - bcmc_client.h   : BCMC_Client component class (BCM wrapper)
  - bcmc_client.cpp : Component export (getComponent function)

Main Application:
  - test_bcm_app.cpp : Loads components and wires them together


## EXECUTION FLOW

When you run test_bcm_app:

1. ComponentManager loads server.dll and client.dll
2. Calls getComponent() in each DLL to get component instances
3. Main application retrieves "hello" and "goodbye" interfaces from server
4. Main application injects these interfaces into client via setInterface()
5. Main application retrieves "talk" interface from client
6. Calls speaker->talk(), which internally calls hello() and goodbye()
7. Output:
```cpp
 Interfaces provided by server:
 hello   Hello there
 goodbye See you
 Interface requested to server: hello
 Interface is 0x...
 helloInterface_ is now 0x...
 Interface requested to server: goodbye
 Interface is 0x...
 goodbyeInterface_ is now 0x...
 Hello
 Goodbye
```


## BUILDING AND RUNNING

A Makefile is provided for both Windows (MinGW) and Linux.

To build:
```cpp
cd bcm/test
mingw32-make    (Windows with MinGW)
make            (Linux/macOS)
```

This compiles:
  - bcmc_server.cpp  →  server.dll (or server.so)
  - bcmc_client.cpp  →  client.dll (or client.so)
  - test_bcm_app.cpp →  test_bcm_app.exe (or test_bcm_app)

To run:
```cpp
./test_bcm_app.exe    (Windows)
./test_bcm_app        (Linux/macOS)
```


## WHY IS BCM SO SIMPLE?

Compare what you need to create a component:

CORBA:
  - Write IDL file
  - Run IDL compiler to generate stubs/skeletons
  - Implement servant classes
  - Configure ORB and naming service
  - Handle marshaling/unmarshaling
  Learning curve: weeks

COM:
  - Define interfaces with IUnknown inheritance
  - Generate GUIDs
  - Implement AddRef/Release reference counting
  - Register components in Windows registry
  - Understand apartments and marshaling
  Learning curve: weeks

BCM:
  - Define C++ interface (what you already know)
  - Create wrapper struct (3 lines)
  - Implement component with getInterface/setInterface
  - Export getComponent() function
  - Done!
  Learning curve: hours


## EXERCISES

Try these to deepen your understanding:

1. Add a new method to HelloInterface, rebuild, and verify it works

2. Create a new component that requires "talk" and provides a "logger" interface

3. Modify the client to optionally accept a "logger" interface (make it optional
   by not failing in setInterface if logger isn't provided)

4. Create a third component that provides neither hello nor goodbye, and watch
   the dependency resolution fail gracefully


## SUMMARY

BCM gives you component-based architecture with:
  ✓ Dynamic loading (plug-and-play components)
  ✓ Dependency injection (automatic interface wiring)
  ✓ Binary compatibility (components compiled separately)
  ✓ Language simplicity (pure C++, no IDL)
  ✓ Minimal overhead (header-only core, no runtime bloat)

The entire pattern is just:
  1. Define pure virtual interfaces
  2. Wrap with bcm::Interface
  3. Implement component with bcm::Identifier<> mixins
  4. Export extern "C" getComponent()
  5. Load and wire with ComponentManager

That's it. Welcome to component-based programming without the complexity.

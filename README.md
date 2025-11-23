# BCM: Binary Component Model

**A Lightweight Header-Only C++ Framework for Component-Based Software**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++11](https://img.shields.io/badge/C++-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B11)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Windows%20%7C%20macOS-lightgrey.svg)](https://github.com/yourusername/bcm)

## What is BCM?

BCM (Binary Component Model) is a minimal C++ framework that brings the power of component-based software engineering to your projects **without the complexity**. Unlike traditional component frameworks (CORBA, COM, OSGi), BCM requires:

- ✅ **NO** Interface Definition Language (IDL)
- ✅ **NO** code generation or stub/skeleton compilers
- ✅ **NO** complex marshaling or registry configuration
- ✅ **Just** pure C++ interfaces and simple inheritance

The entire framework fits in **6 header files** (~200 lines of code). Learning curve: **hours, not weeks**.

## Quick Example

Define an interface:

```cpp
// ihello.h
struct HelloInterface {
    virtual void hello() = 0;
};
```

Create a BCM component:

```cpp
// server.cpp
#include <bcm/bcm.h>

class Server : public bcm::Identifier<bcm::Component>,
               protected bcm::Identifier<BCMI_HelloInterface> {
    // ~30 lines of boilerplate
};

extern "C" bcm::Component *getComponent() {
    return &Server::instance();
}
```

Load and use it dynamically:

```cpp
// main.cpp
bcm::ComponentManager &mgr = bcm::ComponentManager::instance();
mgr.loadComponent("server.dll");  // or server.so on Linux

bcm::Component *comp;
mgr.getComponent("server", &comp);

auto hello = dynamic_cast<HelloInterface*>(comp->getInterface("hello"));
hello->hello();  // "Hello, World!"
```

**That's it.** No IDL, no code generation, no magic. Just C++ doing what it does best.

## Why BCM?

| Feature | CORBA | COM | OSGi | **BCM** |
|---------|-------|-----|------|---------|
| IDL Required | ✗ | ✓ | ✓ | ✓ |
| Code Generation | ✗ | ✓ | ✓ | ✓ |
| Runtime Overhead | Heavy (ORB) | Medium | Heavy (JVM) | **Minimal** |
| Lines of Code/Component | 200-500 | 100-200 | 50-100 | **20-50** |
| Learning Curve | Weeks | Weeks | Days | **Hours** |
| Platform | Cross | Windows | JVM | **Cross** |

## Installation

BCM is header-only. Just copy the `include/` directory to your project:

```bash
git clone https://github.com/yourusername/bcm.git
cp -r bcm/include/bcm /usr/local/include/  # or your include path
```

Or use as a git submodule:

```bash
git submodule add https://github.com/yourusername/bcm.git extern/bcm
```

## Requirements

- **C++11** or later
- **Platform**: Linux, Windows, macOS, or any Unix-like system
- **Dependencies**: None! (only standard C++ library)

## Documentation

- **[Tutorial](docs/tutorial.md)** - Complete step-by-step guide
- **[Hello World Example](examples/hello-world/)** - Working client-server example
- **[Paper](paper/)** - Published in SoftwareX journal

## Features

✨ **Pure C++ Interfaces** - No IDL, just `virtual` functions
🔌 **Dynamic Loading** - Components as DLLs/shared objects
💉 **Dependency Injection** - Explicit interface wiring
🎯 **Binary Compatibility** - Leverage C++ vtables directly
📦 **Header-Only Core** - 6 files, <200 lines total
⚡ **Zero Runtime Overhead** - Beyond vtable dispatch
🌍 **Cross-Platform** - Linux, Windows, macOS support

## Use Cases

BCM is perfect for:

- **Embedded Systems** - No JVM or heavyweight middleware required
- **Research Prototyping** - Explore architectural patterns without framework complexity
- **Education** - Teach component-based design with observable mechanisms
- **Plugin Architectures** - Native applications needing runtime extensibility
- **Scientific Computing** - Swap algorithm implementations without recompilation

## Project Structure

```
bcm/
├── include/bcm/          # Core framework headers (THIS is BCM!)
│   ├── bcm.h            # Main include file
│   ├── component.h      # Component base class
│   ├── interface.h      # Interface base class
│   ├── identifiable.h   # ID/name contract
│   ├── identifier.h     # CRTP mixin for easy implementation
│   ├── identifierdata.h # Metadata structures
│   ├── linux/           # Linux ComponentManager
│   └── win32/           # Windows ComponentManager
│
├── examples/            # Complete working examples
│   └── hello-world/     # Client-server tutorial
│
└── docs/                # Documentation
    └── tutorial.md      # Comprehensive tutorial
```

## Quick Start

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/bcm.git
   cd bcm
   ```

2. **Build the hello-world example**:
   ```bash
   cd examples/hello-world
   make              # Linux/macOS
   mingw32-make      # Windows with MinGW
   ```

3. **Run it**:
   ```bash
   ./main            # Linux/macOS
   main.exe          # Windows
   ```

4. **Read the tutorial**:
   - [Complete Tutorial](docs/tutorial.md)
   - Study the [example source](examples/hello-world/)

## Contributing

Contributions welcome! This is a minimal framework by design, but improvements to:
- Documentation
- Platform support
- Example applications
- Bug fixes

are always appreciated.

## License

MIT License - see [LICENSE](LICENSE) file.

## Citation

If you use BCM in academic work, please cite:

```bibtex
@article{bcm2026,
  author  = {Your Name},
  title   = {BCM: A Lightweight Header-Only C++ Framework for Modular Component-Based Systems},
  journal = {SoftwareX},
  year    = {2026},
  note    = {In press}
}
```

## Comparison with Other Frameworks

BCM intentionally provides a **minimal** set of features:

| What BCM **Does** | What BCM **Doesn't** |
|-------------------|----------------------|
| ✓ Dynamic loading | ✗ Remote/distributed components |
| ✓ Interface contracts | ✗ Automatic marshaling |
| ✓ Dependency injection | ✗ Transaction management |
| ✓ Binary modularity | ✗ Built-in persistence |
| ✓ Runtime composition | ✗ Security/authentication |

If you need enterprise features, consider **EJB** or **CORBA**. If you need sophisticated Java modularization, use **OSGi**.

If you need a **minimal, understandable, C++-native component framework**, you're in the right place.

## Questions?

- **Issues**: [GitHub Issues](https://github.com/yourusername/bcm/issues)
- **Email**: your.email@domain.com
- **Tutorial**: [docs/tutorial.md](docs/tutorial.md)

---

**BCM**: Component-based architecture without the ceremony. 🚀

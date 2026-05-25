# BCM Hello World Example Makefile
# Supports both Linux and Windows (MinGW)

# Detect OS
ifeq ($(OS),Windows_NT)
    # Windows with MinGW
    CXX = g++
    LIB_EXT = .dll
    EXE_EXT = .exe
    RM = del /Q
    MKDIR = if not exist $@\\ mkdir
    PATH_SEP = \\
else
    # Linux / macOS / Unix
    CXX = g++
    LIB_EXT = .so
    EXE_EXT =
    RM = rm -f
    MKDIR = mkdir -p
    PATH_SEP = /
endif

# Directories
BCM_INCLUDE = ../../include
INTERFACE_DIR = interfaces
SERVER_DIR = server
CLIENT_DIR = client

# Compiler flags
# Note: server/client include dirs are NOT added here to preserve binary
# decoupling — main.cpp must only see interface headers, not implementations.
CXXFLAGS = -std=c++11 -I$(BCM_INCLUDE) -I$(INTERFACE_DIR) -fPIC -Wall
$(SERVER_OBJ): CXXFLAGS += -I$(SERVER_DIR)
$(CLIENT_OBJ): CXXFLAGS += -I$(CLIENT_DIR)
LDFLAGS = -shared

# Platform-specific flags
ifeq ($(OS),Windows_NT)
    LDFLAGS += -Wl,--enable-auto-import
else
    LDFLAGS += -fPIC
endif

# Targets
SERVER_LIB = server$(LIB_EXT)
CLIENT_LIB = client$(LIB_EXT)
MAIN_APP = main$(EXE_EXT)

# Source files
SERVER_SRC = $(SERVER_DIR)/bcmc_server.cpp
CLIENT_SRC = $(CLIENT_DIR)/bcmc_client.cpp
MAIN_SRC = main.cpp

# Object files
SERVER_OBJ = $(SERVER_SRC:.cpp=.o)
CLIENT_OBJ = $(CLIENT_SRC:.cpp=.o)
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

# Default target
all: $(SERVER_LIB) $(CLIENT_LIB) $(MAIN_APP)

# Server component library
$(SERVER_LIB): $(SERVER_OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

# Client component library
$(CLIENT_LIB): $(CLIENT_OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

# Main application
$(MAIN_APP): $(MAIN_OBJ)
	$(CXX) -o $@ $^
	@echo "Build complete! Run: $(MAIN_APP)"

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	-rm -f $(SERVER_DIR)/*.o $(CLIENT_DIR)/*.o *.o $(SERVER_LIB) $(CLIENT_LIB) $(MAIN_APP)

# Phony targets
.PHONY: all clean

# Dependencies (simplified - headers included via -I flags)
$(SERVER_OBJ): $(wildcard $(SERVER_DIR)/*.h) $(wildcard $(INTERFACE_DIR)/*.h)
$(CLIENT_OBJ): $(wildcard $(CLIENT_DIR)/*.h) $(wildcard $(INTERFACE_DIR)/*.h)
$(MAIN_OBJ): $(wildcard $(INTERFACE_DIR)/*.h)

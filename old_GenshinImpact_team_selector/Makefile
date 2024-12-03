# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall
CXXFLAGS = -I$(BIN_DIR)

# Executable name
EXECUTABLE = genshin_team_selector.exe

# Directory
SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
HEADER_FILES = $(wildcard $(BIN_DIR)/*.h)

TARGET = $(BUILD_DIR)/$(EXECUTABLE)

$(TARGET): $(SRC_FILES) $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(BUILD_DIR)/$(EXECUTABLE)

.PHONY: all run clean

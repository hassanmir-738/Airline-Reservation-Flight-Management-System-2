CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=build/%.o)

ifeq ($(OS),Windows_NT)
    TARGET = skylink.exe
    CLEAN = rmdir /s /q build 2>nul & del /f /q $(TARGET) 2>nul
    CREATE_DIR = if not exist build mkdir build
else
    TARGET = skylink
    CLEAN = rm -rf build $(TARGET)
    CREATE_DIR = mkdir -p build
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/%.o: src/%.cpp
	@$(CREATE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(CLEAN)

run: all
	./$(TARGET)


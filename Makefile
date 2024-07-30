PROJECTNAME=sandbox
OUTPUT_DIR=build

INCLUDE_DIRS = -Iinclude/imgui -Iinclude/SDL2
LIB_DIRS = -Llib
LIBS= -lSDL2

SRC = $(wildcard src/*.cpp) $(wildcard imgui/*.cpp)

default:
	g++ $(SRC) -o $(OUTPUT_DIR)/$(PROJECTNAME) $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS)
	./build/$(PROJECTNAME)

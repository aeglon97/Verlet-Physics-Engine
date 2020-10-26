# #Specify files to compile
# OBJS = /src/Driver.cpp

# #Specify compiler
# CC = g++

# #Specify additional compilation options

# # -w (suppress all warnings)
# COMPILER_FLAGS = -w

# #Specify libraries to link against
# LINKER_FLAGS = -lSDL2

# #Specify name of executable
# OBJ_NAME = verlet_simulator

# #Compile executable
# all: $(OBJS)
# 		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o  $(OBJ_NAME)

# COMPILER_FLAGS = -w
# LINKER_FLAGS = -lSDL2 -lSDL2_image

.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake .. && \
	make

.PHONY: debug
debug:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: clean
clean:
	rm -rf build
	rm -rf debug


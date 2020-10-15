#Specify files to compile
OBJS = Driver.cpp

#Specify compiler
CC = g++

#Specify additional compilation options

# -w (suppress all warnings)
COMPILER_FLAGS = -w

#Specify libraries to link against
LINKER_FLAGS = -lSDL2

#Specify name of executable
OBJ_NAME = verlet_simulator

#Compile executable
all: $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o  $(OBJ_NAME)
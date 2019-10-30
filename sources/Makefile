#OBJS specifies which files to compile as part of the project
OBJS = main.c status_information.h status_information_scanner.c status_information_scanner.h awesomepsio.h awesomepsio.c process_selector.h process_selector.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -pedantic-errors -Wall

#LINKER_FLAGS specifies the libraries we're linking against
# -Wall enables all the warnings
#LINKER_FLAGS = -std=c99 -Wall -pedantic-errors

#TARGET specifies the name of our exectuable
TARGET = awesomeps

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(TARGET)

#This is the target that cleans the project
clean:


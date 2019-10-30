################################ CONFIGURATION ################################
TARGET_NAME = awesomeps
SRC_DIRECTORY = ./sources
TARGET_DIRECTORY = ./target
COMPILER = gcc
COMPILER_FLAGS = -std=c99 -pedantic-errors -Wall
LINKER_FLAGS = -std=c99 -pedantic-errors -Wall

################################ PROJECT FILES ################################
SOURCE_FILES = $(SRC_DIRECTORY)/*.c
HEADER_FILES = $(SRC_DIRECTORY)/*.h
FILES = $(SOURCE_FILES) $(HEADER_FILES)
TARGET = $(TARGET_DIRECTORY)/$(TARGET_NAME)
OBJECTS_DIRECTORY = $(TARGET_DIRECTORY)/objects

################################### TARGETS ###################################

compile: $(FILES)
	@mkdir -p $(TARGET_DIRECTORY)
	@$(COMPILER) $(FILES) $(COMPILER_FLAGS) -o $(TARGET)

clean : $(TARGET_DIRECTORY)
	@ rm -rf $(TARGET_DIRECTORY)
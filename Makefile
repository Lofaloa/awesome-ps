################################ CONFIGURATION ################################
TARGET_NAME = awesomeps
SRC_DIRECTORY = ./sources
TARGET_DIRECTORY = ./target
COMPILER = gcc
COMPILER_FLAGS = -std=c99 -pedantic-errors -Wall
LINKER_FLAGS = -std=c99 -pedantic-errors -Wall

REPORT_FILE_NAME = "report"
REPORT_MAIN_SOURCE = ./report/main.tex

################################ PROJECT FILES ################################
SOURCE_FILES = $(SRC_DIRECTORY)/*.c $(SRC_DIRECTORY)/*/*.c
HEADER_FILES = $(SRC_DIRECTORY)/*/*.h
FILES = $(SOURCE_FILES) $(HEADER_FILES)
TARGET = $(TARGET_DIRECTORY)/$(TARGET_NAME)
OBJECTS_DIRECTORY = $(TARGET_DIRECTORY)/objects

################################### TARGETS ###################################
.PHONY: clean report

target: awesomeps report

report: $(REPORT_MAIN_SOURCE) ./report/sections/*.tex
	@pdflatex -output-directory=$(TARGET_DIRECTORY) -jobname=$(REPORT_FILE_NAME) $<
	@pdflatex -output-directory=$(TARGET_DIRECTORY) -jobname=$(REPORT_FILE_NAME) $<
	@rm $(TARGET_DIRECTORY)/*.aux $(TARGET_DIRECTORY)/*.log $(TARGET_DIRECTORY)/*.toc

awesomeps: $(FILES)
	@mkdir -p $(TARGET_DIRECTORY)
	@$(COMPILER) $(FILES) $(COMPILER_FLAGS) -o $(TARGET)

clean : $(TARGET_DIRECTORY)
	@ rm -rf $(TARGET_DIRECTORY)
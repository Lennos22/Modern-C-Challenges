####################################################################################################
####                                      VARIABLES                                             ####
####################################################################################################

# Directory/filename strings
EXECUTABLE := tblobs

BUILD_DIR  := ./build
SRC_DIR    := ./src
INC_DIRS   := $(shell find $(SRC_DIR) -type d)

SRC_FILES  := $(shell find $(SRC_DIR) -name *.c -or -name *.s)
OBJ_FILES  := $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP_FILES  := $(OBJ_FILES:.o=.d)

# Shell strings
STDC       := c11
DGBC       := -ggdb
HARDMODE   := -Wextra -Werror -pedantic-errors
DEFINES    := #NDEBUG
DEF_FLAGS  := $(addprefix -D,$(DEFINES))
INC_FLAGS  := $(addprefix -I,$(INC_DIRS))

DEBUG      := -Wall $(DGBC) $(HARDMODE)

RM_R        = $(RM) -r
DIR_GUARD   = @mkdir -p $(@D)

# Makefile flags
CC         := gcc
CFLAGS     := -std=$(STDC) $(DEBUG)
CPPFLAGS   := $(DEF_FLAGS) $(INC_FLAGS) -MMD -MP
LDLIBS     := -lm

####################################################################################################
####                                        RULES                                               ####
####################################################################################################

# Executable
$(EXECUTABLE): $(OBJ_FILES)
	$(LINK.o) $^ $(LDLIBS) $(OUTPUT_OPTION)

# Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_GUARD)
# $(OUTPUT_OPTION) used here because object files will be built in a different directory
	$(COMPILE.c) $(OUTPUT_OPTION) $<

####################################################################################################
####                                     MISCELLANEOUS                                          ####
####################################################################################################

.PHONY: clean_build
clean_build:
	$(RM_R) $(BUILD_DIR)

.PHONY: clean_target
clean_target:
	$(RM) $(EXECUTABLE)

.PHONY: clean
clean:
	$(RM_R) $(EXECUTABLE) $(BUILD_DIR)

# NOTE: gcc can generate dependency files (.d extension) using the -M flag. These dependency files
#   are essentially just Makefile rules for the corresponding .o file. Since these rules don't have
#   any recipes, the pre-reqs will simply be merged with the existing .o rules above!
-include $(DEP_FILES)

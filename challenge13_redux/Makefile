####################################################################################################
####									VARIABLES												####
####################################################################################################

# Directory/filename strings
TARGETS		:= test_polynomial

BUILD_DIR	:= ./build
SRC_DIR		:= ./src
INC_DIRS	:= $(shell find $(SRC_DIR) -type d)

SRC_FILES	:= $(shell find $(SRC_DIR) -name *.c -or -name *.s)
OBJ_FILES	:= $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP_FILES	:= $(OBJ_FILES:.o=.d)

# Shell strings
STDC		:= -std=c11
HARDMODE	:= -Wextra -Werror -pedantic-errors
INC_FLAGS	:= $(addprefix -I,$(INC_DIRS))

DEBUG		:= -Wall $(HARDMODE)

RM_R		= $(RM) -r
DIR_GUARD	= @mkdir -p $(@D)

# Makefile flags
CC			:= gcc
CFLAGS		:= $(STDC) $(DEBUG)
CPPFLAGS	:= $(INC_FLAGS) -MMD -MP
LDLIBS		:= -lm

####################################################################################################
####										RULES												####
####################################################################################################

.PHONY: all
all: $(TARGETS)

# Executables
$(TARGETS): $(OBJ_FILES)
	$(LINK.o) $^ $(LDLIBS) -o $@

# Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_GUARD)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

####################################################################################################
####									MISCELLANEOUS											####
####################################################################################################

.PHONY: clean_build
clean_build:
	$(RM_R) $(BUILD_DIR)

.PHONY: clean_targets
clean_targets:
	$(RM) $(TARGETS)

.PHONY: clean
clean:
	$(RM_R) $(TARGETS) $(BUILD_DIR)

# NOTE: gcc can generate dependency files (.d extension) using the -M flag. These dependency files
#	are essentially just Makefile rules for the corresponding .o file. Since these rules don't have
#	any recipes, the pre-reqs will simply be merged with the existing .o rules above!
-include $(DEP_FILES)

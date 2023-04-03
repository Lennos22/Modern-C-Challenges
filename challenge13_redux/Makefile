CC			:= gcc
STDC		:= -std=c11
HARDMODE	:= -Wextra -Werror -pedantic-errors
CFLAGS		:= $(STDC) -Wall $(HARDMODE)
LDLIBS		:= -lm
TARGETS		:= 

all: $(TARGETS)

###############################################################################
###								EXECUTABLES									###
###############################################################################

sort_performance: sort_performance.o mergesort.o quicksort.o time_ops.o

list_gen: list_gen.o

check_sorted: check_sorted.o

###############################################################################
###								OBJECT FILES								###
###############################################################################

vector.o: vector.c

############
### MISC ###
############

clean_objects:
	$(RM) *.o

clean_targets:
	$(RM) $(TARGETS)

clean:
	$(RM) $(TARGETS) *.o

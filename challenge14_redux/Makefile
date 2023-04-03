CC		:= gcc
STDC	:= -std=c11
CFLAGS	:= $(STDC) -Wall
LDLIBS	:= -lm
TARGETS	:= sort_performance list_gen check_sorted

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

sort_performance.o: sort_performance.c mergesort.h quicksort.h time_ops.h

list_gen.o: list_gen.c

check_sorted.o: check_sorted.c

mergesort.o: mergesort.c mergesort.h

quicksort.o: quicksort.c quicksort.h

time_ops.o: time_ops.c time_ops.h

############
### MISC ###
############

clean_objects:
	$(RM) *.o

clean_targets:
	$(RM) $(TARGETS)

clean:
	$(RM) $(TARGETS) *.o

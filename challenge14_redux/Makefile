CC		:= gcc
STDC	:= -std=c11
CFLAGS	:= $(STDC) -Wall
LDLIBS	:= -lm
TARGETS	:= sort_performance list_gen check_sorted

all: $(TARGETS)

###############################################################################
###								EXECUTABLES									###
###############################################################################

sort_performance: sort_performance.o mergesort.o quicksort.o byte_ops.o time_ops.o
	$(CC) -o $@ $^ $(LDLIBS)

list_gen: list_gen.o
	$(CC) -o $@ $^ $(LDLIBS)

check_sorted: check_sorted.o
	$(CC) -o $@ $^ $(LDLIBS)

###############################################################################
###								OBJECT FILES								###
###############################################################################

sort_performance.o: sort_performance.c mergesort.h quicksort.h time_ops.h
	$(CC) $(CFLAGS) -c $<

list_gen.o: list_gen.c
	$(CC) $(CFLAGS) -c $<

check_sorted.o: check_sorted.c
	$(CC) $(CFLAGS) -c $<

mergesort.o: mergesort.c mergesort.h
	$(CC) $(CFLAGS) -c $<

quicksort.o: quicksort.c quicksort.h
	$(CC) $(CFLAGS) -c $<

byte_ops.o: byte_ops.c byte_ops.h
	$(CC) $(CFLAGS) -c $<

time_ops.o: time_ops.c time_ops.h
	$(CC) $(CFLAGS) -c $<

############
### MISC ###
############

clean_objects:
	$(RM) *.o

clean_targets:
	$(RM) $(TARGETS)

clean:
	$(RM) $(TARGETS) *.o

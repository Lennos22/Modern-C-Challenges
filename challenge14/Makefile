CC		:= gcc
STDC	:= -std=c11
CFLAGS	:= -Wall
LDFLAGS	:= -lm
TARGETS	:= sort_performance list_gen check_sorted

all: ${TARGETS}

###############################################################################
###								EXECUTABLES									###
###############################################################################

sort_performance: sort_performance.o mergesort.o quicksort.o byte_ops.o time_ops.o
	${CC} ${STDC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

list_gen: list_gen.o
	${CC} ${STDC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

check_sorted: check_sorted.o
	${CC} ${STDC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

###############################################################################
###								OBJECT FILES								###
###############################################################################

sort_performance.o: sort_performance.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

list_gen.o: list_gen.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

check_sorted.o: check_sorted.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

mergesort.o: mergesort.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

quicksort.o: quicksort.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

byte_ops.o: byte_ops.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

time_ops.o: time_ops.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

############
### MISC ###
############

clean_objects:
	rm -f *.o

clean_targets:
	rm -f ${TARGETS}

clean:
	rm -f ${TARGETS} *.o

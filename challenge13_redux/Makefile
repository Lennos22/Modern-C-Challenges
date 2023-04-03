CC			:= gcc
STDC		:= -std=c11
HARDMODE	:= -Wextra -Werror -pedantic-errors
CFLAGS		:= $(STDC) -Wall $(HARDMODE)
LDLIBS		:= -lm
TARGETS		:= test_polynomial

all: $(TARGETS)

###############################################################################
###								EXECUTABLES									###
###############################################################################

test_polynomial: test_polynomial.o polynomial.o vector.o

###############################################################################
###								OBJECT FILES								###
###############################################################################

test_polynomial.o: test_polynomial.c

vector.o: vector.c vector.h

polynomial.o: polynomial.c polynomial.h

############
### MISC ###
############

clean_objects:
	$(RM) *.o

clean_targets:
	$(RM) $(TARGETS)

clean:
	$(RM) $(TARGETS) *.o

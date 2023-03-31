CC		:= gcc
STDC	:= -std=c11
CFLAGS	:= -Wall
LDFLAGS	:= -lm
TARGETS	:= sin_deriv cmplx_sin_deriv rootfinding realpolyroots cmplx_rootfinding cmplxpolyroots

all: ${TARGETS}

###############################################################################
###								EXECUTABLES									###
###############################################################################

sin_deriv: sin_deriv.o numerical_derivative.o
	${CC} ${STDC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

cmplx_sin_deriv: cmplx_sin_deriv.o complx_num_derivative.o
	${CC} ${STDC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

rootfinding: rootfinding.o newton_raphson.o numerical_derivative.o complx_num_derivative.o
	${CC} ${STDC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

realpolyroots: realpolyroots.o polynomial.o newton_raphson.o numerical_derivative.o complx_num_derivative.o
	${CC} ${STDC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

cmplx_rootfinding: cmplx_rootfinding.o newton_raphson.o numerical_derivative.o complx_num_derivative.o
	${CC} ${STDC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

cmplxpolyroots: cmplxpolyroots.o polynomial.o newton_raphson.o numerical_derivative.o complx_num_derivative.o
	${CC} ${STDC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

###############################################################################
###								OBJECT FILES								###
###############################################################################

sin_deriv.o: sin_deriv.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

cmplx_sin_deriv.o: cmplx_sin_deriv.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

rootfinding.o: rootfinding.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

realpolyroots.o: realpolyroots.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

cmplx_rootfinding.o: cmplx_rootfinding.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

cmplxpolyroots.o: cmplxpolyroots.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

polynomial.o: polynomial.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

newton_raphson.o: newton_raphson.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

numerical_derivative.o: numerical_derivative.c
	${CC} ${STDC} ${CFLAGS} -c $^ ${LDFLAGS}

complx_num_derivative.o: complx_num_derivative.c
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

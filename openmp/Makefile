CC=g++
CFLAGS=-I.
calc_pi: calc_pi.c
	$(CC) -fopenmp calc_pi.c -o calc_pi -lm
omp_hello_world: omp_hello_world.c
	$(CC) -fopenmp omp_hello_world.c -o omp_hello_world -lm
all: omp_hello_world calc_pi
clean:
	$(RM) omp_hello_world
	$(RM) calc_pi
run:
	./omp_hello_world
	./calc_pi


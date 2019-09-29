CC=g++
MAC_CFLAGS=-Xpreprocessor -fopenmp -lomp
LIN_CFLAGS=-fopenmp

calc_pi: calc_pi.c
	$(CC) $(LIN_CFLAGS) calc_pi.c -o calc_pi
omp_hello_world: omp_hello_world.c
	$(CC) $(LIN_CFLAGS) omp_hello_world.c -o omp_hello_world 
all: omp_hello_world calc_pi
clean:
	$(RM) omp_hello_world
	$(RM) calc_pi
run:
	./omp_hello_world
	./calc_pi


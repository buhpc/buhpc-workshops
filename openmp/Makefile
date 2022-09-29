override CFLAGS := -Wall -Werror -fopenmp -g $(CFLAGS)

all: ${exe_files} gameoflife

c_files=$(shell find -type f -name '*.c')
exe_files=$(c_files:.c=)

all: ${exe_files}

%: %.c
	$(CC) $(LDFLAGS) $(CFLAGS) $+ $(LOADLIBES) $(LDLIBS) -o $@
clean:
	rm -f *.o $(exe_files) *~

gameoflife: gameoflife.cpp
	g++ gameoflife.cpp -o gameoflife -fopenmp
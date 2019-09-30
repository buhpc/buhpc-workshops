all:
	$(module load gcc)
	g++ u64*.cpp main*.cpp bench_runner.cpp -std=c++0x -O0

run: all
	./a.out

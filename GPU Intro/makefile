ITERS := 100
R := 5
NVCC := nvcc
USE_L2 := false 
BLOCK_SIZE := 10

default: all
all: share sync dev_info
clean:
	rm -rf *.o *.out

share: gpu_share.cu
	$(NVCC) gpu_share.cu -std=c++11  -DITERS=$(ITERS) -DRADIUS=$(R) -DUSE_L2=$(USE_L2) -o gpu_share.out

sync: gpu_sync.cu
	$(NVCC) gpu_sync.cu -std=c++11  -DRADIUS=$(R) -DBLOCK_SIZE=$(BLOCK_SIZE) -o gpu_sync.out

dev_info: dev_info.cu
	$(NVCC) dev_info.cu -o dev_info.out

runall: all
	./dev_info.out
	./gpu_sync.out
	./gpu_share.out

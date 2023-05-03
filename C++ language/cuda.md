 

## GPU编程模型

- 线程是CUDA中基本执行单元,由硬件支持、开销很小,每个线程执行相同代码;
- 线程块(Block)是若干线程的分组,Block内一个块至多512个线程、或1024个线程(根据不同的GPU规格),线程块可以是一维、二维或者三维的;
- 线程网络(Grid)是若干线程块的网格,Grid是一维和二维的。

GPU在管理线程(thread)的时候是以block(线程块)为单元调度到SM上执行。每个block中以warp(一般32个线程或64线
程)作为一次执行的单位(真正的同时执行)。

1. 一个 GPU 包含多个 Streaming Multiprocessor ,而每个 Streaming Multiprocessor 又包含多个 core 。
  Streaming Multiprocessors 支持并发执行多达几百的 thread 。
2. 一个 thread block 只能调度到一个 Streaming Multiprocessor 上运行,直到 thread block 运行完毕。一个
  Streaming Multiprocessor 可以同时运行多个thread block (因为有多个core)。

​	通俗点讲:stream multiprocessor(SM)是一块硬件,包含了固定数量的运算单元,寄存器和缓存。
​	写cuda kernel的时候,跟SM对应的概念是block,每一个block会被调度到某个SM执行,一个SM可以执行多个block。
你的cuda程序就是很多的blocks(一般来说越多越好)均匀的喂给这80个SM来调度执行。具体每个block喂给哪个SM你没
法控制。

- thread:一个CUDA的并行程序会被以许多个threads来执行。

- block:数个threads会被群组成一个block,同一个block中的threads可以同步,也可以通过sharedmemory通信。

- grid:多个blocks则会再构成grid。

![image-20230502084656349](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305020846388.png)

### 线程索引的计算公式

一个Grid可以包含多个Blocks,Blocks的组织方式可以是一维的,二维或者三维的。block包含多个Threads,这些
Threads的组织方式也可以是一维,二维或者三维的。
CUDA中每一个线程都有一个唯一的标识ID—ThreadIdx,这个ID随着Grid和Block的划分方式的不同而变化,这里给出
Grid和Block不同划分方式下线程索引ID的计算公式。
threadIdx是一个uint3类型,表示一个线程的索引。
blockIdx是一个uint3类型,表示一个线程块的索引,一个线程块中通常有多个线程。
blockDim是一个dim3类型,表示线程块的大小。
gridDim是一个dim3类型,表示网格的大小,一个网格中通常有多个线程块。
<img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305020901391.png" alt="image-20230502090145317" style="zoom:50%;" />

![image-20230502093310350](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305020933399.png)

#### 代码

```c++
#include <cuda_runtime.h>
#include <random>
#include <future>
#include <thread>
#include <iostream>

__global__ void vecAddKernel(double *A, double *B, double *C, int n) {
  int i = threadIdx.x + blockDim.x * blockIdx.x;
  if (i < n) {
    C[i] = A[i] + B[i];
  }
//    printf("i=%d\n", i);
}

int main() {
  int nElem = 255;
  int nByte = nElem * sizeof(double);
  //host
  double *h_A = (double *) malloc(nByte);
  double *h_B = (double *) malloc(nByte);
  double *h_C = (double *) malloc(nByte);

  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  std::thread t1([&] {
    for (int i = 0; i < nElem; i++) {
      h_B[i] = distribution(generator);
    }
  });
  std::thread t2([&] {
    for (int i = 0; i < nElem; i++) {
      h_A[i] = distribution(generator);
    }
  });

  t1.join(), t2.join();

  double *d_A, *d_B, *d_C;
  cudaMalloc((double **) &d_A, nByte);
  cudaMalloc((double **) &d_B, nByte);
  cudaMalloc((double **) &d_C, nByte);

  cudaMemcpy(d_A, h_A, nByte, cudaMemcpyHostToDevice);
  cudaMemcpy(d_B, h_B, nByte, cudaMemcpyHostToDevice);

  uint3 blockSize = {256, 1, 1};
  uint3 gridSize = {nElem / blockSize.x + 1, 1, 1};
  vecAddKernel<<<gridSize, blockSize>>>(d_A, d_B, d_C, nElem);

  cudaMemcpy(h_C, d_C, nByte, cudaMemcpyDeviceToHost);

  cudaDeviceSynchronize();
  for(int i=0; i<nElem; i++){
    printf("%f\n", h_C[i]);
  }
  cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(h_A);
    free(h_B);
    free(h_C);
}
```



在计算过程中，我们使用数组指针，也就是说它是一个一维的东西，不过根据我们选择grid，block的维数，我们需要不同的index计算方法来拿到全局索引，但最终总归是那个数组指针。把自己的数据和CUDA提供的模型设计映射关系。

使用`if(global_index < cal_number)`保证不会超出计算范围。

#include <cmath>
#include <chrono>
#include <iostream>

// Function to add the elements of two arrays
__global__
void add(int n, float* x, float* y)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;
    for (int i = index; i < n; i += stride) {
        y[i] = x[i] + y[i];
    }
}

int main()
{
    constexpr auto N = 1'000'000;

    float* x;
    cudaMallocManaged(&x, N * sizeof(float));
    float* y;
    cudaMallocManaged(&y, N * sizeof(float));

    // Initialize x & y arrays on the host
    for (int i = 0; i < N; ++i) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    const auto t0 = std::chrono::system_clock::now();

    // cudaMemPrefetchAsync(x, N*sizeof(float), 0, 0);
    // cudaMemPrefetchAsync(y, N*sizeof(float), 0, 0);

    // Run kernel on the GPU
    const auto block_size = 256;
    const auto num_blocks = (N + block_size - 1) / block_size;
    add<<<num_blocks, block_size>>>(N, x, y);

    const auto t1 = std::chrono::system_clock::now();
    std::cout << "Time to add: " << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() << "ms\n";

    // Wait for GPU to finish before accessing on the host
    cudaDeviceSynchronize();

    // Check for errors
    float max_error = 0.0f;
    for (int i = 0; i < N; ++i) {
        max_error = std::fmaxf(max_error, std::fabs(y[i] - 3.0f));
    }
    std::cout << "Max Error: " << max_error << '\n';

    // Free memory
    cudaFree(x);
    cudaFree(y);

    return 0;
}

#include <cmath>
#include <chrono>
#include <iostream>
#include <vector>

// Function to add the elements of two arrays
void add(const std::vector<float>& x, std::vector<float>& y)
{
    for (size_t i = 0; i < x.size(); ++i) {
        y[i] = x[i] + y[i];
    }
}

int main()
{
    constexpr auto N = 1'000'000;

    std::vector<float> x(N, 1.0f);
    std::vector<float> y(N, 2.0f);

    const auto t0 = std::chrono::system_clock::now();

    // Run kernel on the CPU
    add(x, y);

    const auto t1 = std::chrono::system_clock::now();
    std::cout << "Time for add: " << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() << "ms\n";

    // Check for errors
    float max_error = 0.0f;
    for (int i = 0; i < N; ++i) {
        max_error = std::fmaxf(max_error, std::fabs(y[i] - 3.0f));
    }
    std::cout << "Max Error: " << max_error << '\n';

    return 0;
}

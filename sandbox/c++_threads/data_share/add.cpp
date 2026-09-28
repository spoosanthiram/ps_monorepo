#include <chrono>
#include <cmath>
#include <iostream>
#include <span>
#include <thread>
#include <vector>

void add(const std::span<int> x, const std::span<int> y, std::span<int> z)
{
    if (x.size() != y.size() || y.size() != z.size()) {
        std::cout << "Need all vector sizes to be equal\n";
        return;
    }

    const auto size = x.size();

    for (size_t i = 0; i < size; ++i) {
        z[i] = x[i] + y[i];
    }
}

int main()
{
    std::vector<int> x;
    std::vector<int> y;

    constexpr auto vec_size = 10'000'000;

    x.reserve(vec_size);
    y.reserve(vec_size);

    for (int i = 0; i < vec_size; ++i) {
        x.push_back(1);
        y.push_back(2);
    }

    std::vector<int> z;
    z.resize(vec_size);

    auto time_point0 = std::chrono::system_clock::now();
    {
        size_t mid = vec_size / 2;

        auto x0 = std::span{x.data(), mid};
        auto y0 = std::span{y.data(), mid};
        auto z0 = std::span{z.data(), mid};
        std::thread thread0{add, x0, y0, z0};

        auto x1 = std::span{&x[mid], x.size() - mid};
        auto y1 = std::span{&y[mid], y.size() - mid};
        auto z1 = std::span{&z[mid], z.size() - mid};
        std::thread thread1{add, x1, y1, z1};

        thread0.join();
        thread1.join();
    }
    auto time_point1 = std::chrono::system_clock::now();
    std::cout << "Time to add: " << std::chrono::duration_cast<std::chrono::milliseconds>(time_point1 - time_point0)
              << '\n';

    int error = 0;
    for (int i = 0; i < vec_size; ++i) {
        error += std::abs(3 - z[i]);
    }
    std::cout << "Error = " << error << '\n';

    return 0;
}

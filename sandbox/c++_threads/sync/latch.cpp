#include <iostream>
#include <latch>
#include <random>
#include <thread>
#include <vector>

class Adder
{
public:
    Adder();
    ~Adder();

    int64_t process(const std::vector<int32_t>& numbers);

private:
    static const int32_t num_process_threads = 4;

    struct Job
    {
        std::thread process_thread;
        std::vector<int32_t>::const_iterator start_it;
        std::vector<int32_t>::const_iterator end_it;
        int64_t result{0};
    };

    std::vector<Job> jobs_;
    std::latch process_latch_;
};

Adder::Adder()
    : process_latch_{num_process_threads}
{
    auto i = num_process_threads;
    while (i-- > 0) {
        jobs_.push_back(Job{});
    }
}

Adder::~Adder()
{
    for (auto& job : jobs_) {
        job.process_thread.join();
    }
}

int64_t Adder::process(const std::vector<int32_t>& numbers)
{
    const auto chunk_size = numbers.size() / num_process_threads;
    std::cout << "chunk_size: " << chunk_size << '\n';

    auto start_it = numbers.begin();
    auto end_it = numbers.end();
    for (auto& job : jobs_) {
        job.start_it = start_it;
        if ((end_it - start_it) > chunk_size) {
            job.end_it = start_it + chunk_size;
        }
        else {
            job.end_it = end_it;
        }
        start_it = job.end_it;

        job.process_thread = std::thread{[this, &job]() {
            std::cout << "thread id: " << std::this_thread::get_id() << '\n';
            job.result = 0;
            for (auto it = job.start_it; it != job.end_it; ++it) {
                job.result += *it;
            }
            process_latch_.count_down();
        }};
    }
    process_latch_.wait();

    // collect the result from threads and add them for overall result
    int64_t result = 0;
    for (auto& job : jobs_) {
        result += job.result;
    }
    return result;
}

int main()
{
    constexpr int32_t numbers_to_add = 4'000'000;

    std::random_device rd{};

    std::default_random_engine random_engine;
    random_engine.seed(rd());

    std::uniform_int_distribution<> dist{0, 1000};

    int64_t expeced_result = 0;
    std::vector<int32_t> numbers;
    for (int32_t i = 0; i < numbers_to_add; ++i) {
        numbers.push_back(dist(random_engine));
        expeced_result += numbers.back();
    }
    std::cout << "Expected Result: " << expeced_result << '\n';

    Adder adder;
    const auto result = adder.process(numbers);
    std::cout << "Result: " << result << '\n';

    return 0;
}

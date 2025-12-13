#include "sandbox/roblox/multiples.h"
#include "sandbox/roblox/StrInt.h"

#define CHECK(EXPR)                            \
    do {                                       \
        if (!(EXPR)) {                         \
            std::cerr << #EXPR << " failed\n"; \
        }                                      \
    } while (0)

int main(int argc, char** argv)
{
    // Use uint32_t to check test cases
    CHECK(Ps::Algo::nth_multiple<uint32_t>(2) == 2);
    CHECK(Ps::Algo::nth_multiple<uint32_t>(5) == 5);
    CHECK(Ps::Algo::nth_multiple<uint32_t>(9) == 10);
    CHECK(Ps::Algo::nth_multiple<uint32_t>(15) == 24);
    CHECK(Ps::Algo::nth_multiple<uint32_t>(100) == 1'536);
    CHECK(Ps::Algo::nth_multiple<uint32_t>(1500) == 859'963'392);

    // Use StrInt to check test cases
    CHECK(Ps::Algo::nth_multiple<Ps::Algo::StrInt>(1) == Ps::Algo::StrInt{1});
    CHECK(Ps::Algo::nth_multiple<Ps::Algo::StrInt>(3) == Ps::Algo::StrInt{3});
    CHECK(Ps::Algo::nth_multiple<Ps::Algo::StrInt>(15) == Ps::Algo::StrInt{24});
    CHECK(Ps::Algo::nth_multiple<Ps::Algo::StrInt>(1500) == Ps::Algo::StrInt{859'963'392});

    // Use Int to check test cases
    CHECK(Ps::Algo::nth_multiple_byte_stream(1) == Ps::Algo::Int{1});
    CHECK(Ps::Algo::nth_multiple_byte_stream(2) == Ps::Algo::Int{2});
    CHECK(Ps::Algo::nth_multiple_byte_stream(4) == Ps::Algo::Int{4});
    CHECK(Ps::Algo::nth_multiple_byte_stream(18) == Ps::Algo::Int{30});
    CHECK(Ps::Algo::nth_multiple_byte_stream(1500) == Ps::Algo::Int{859'963'392});

    if (argc > 1) {
        const auto nth_pos = std::stoul(argv[1]);

        if (nth_pos < 10'000) {
            const auto nth_multi = Ps::Algo::nth_multiple<uint64_t>(nth_pos);
            std::cout << std::format("{}th multiple: {}", nth_pos, nth_multi) << std::endl;
        }
        else if (nth_pos <= 100'000) {
            const auto nth_multi = Ps::Algo::nth_multiple<Ps::Algo::StrInt>(nth_pos);
            std::cout << nth_pos << "th multiple: " << nth_multi << std::endl;
        }
        else {
            const auto nth_multi = Ps::Algo::nth_multiple_byte_stream(nth_pos);
            std::cout << nth_pos << "th multiple: " << nth_multi << std::endl;
        }
    }

    return 0;
}

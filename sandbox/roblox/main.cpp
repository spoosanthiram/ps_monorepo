#include "sandbox/roblox/multiples.h"
#include "sandbox/roblox/str_int.h"

#define CHECK(EXPR)                            \
    do {                                       \
        if (!(EXPR)) {                         \
            std::cerr << #EXPR << " failed\n"; \
        }                                      \
    } while (0)

int main(int argc, char** argv)
{
    // Use uint32_t to check test cases
    CHECK(ps::algo::nth_multiple<uint32_t>(2) == 2);
    CHECK(ps::algo::nth_multiple<uint32_t>(5) == 5);
    CHECK(ps::algo::nth_multiple<uint32_t>(9) == 10);
    CHECK(ps::algo::nth_multiple<uint32_t>(15) == 24);
    CHECK(ps::algo::nth_multiple<uint32_t>(100) == 1'536);
    CHECK(ps::algo::nth_multiple<uint32_t>(1500) == 859'963'392);

    // Use StrInt to check test cases
    CHECK(ps::algo::nth_multiple<ps::algo::StrInt>(1) == ps::algo::StrInt{1});
    CHECK(ps::algo::nth_multiple<ps::algo::StrInt>(3) == ps::algo::StrInt{3});
    CHECK(ps::algo::nth_multiple<ps::algo::StrInt>(15) == ps::algo::StrInt{24});
    CHECK(ps::algo::nth_multiple<ps::algo::StrInt>(1500) == ps::algo::StrInt{859'963'392});

    // Use Int to check test cases
    CHECK(ps::algo::nth_multiple_byte_stream(1) == ps::algo::Int{1});
    CHECK(ps::algo::nth_multiple_byte_stream(2) == ps::algo::Int{2});
    CHECK(ps::algo::nth_multiple_byte_stream(4) == ps::algo::Int{4});
    CHECK(ps::algo::nth_multiple_byte_stream(18) == ps::algo::Int{30});
    CHECK(ps::algo::nth_multiple_byte_stream(1500) == ps::algo::Int{859'963'392});

    if (argc > 1) {
        const auto nth_pos = std::stoul(argv[1]);

        if (nth_pos < 10'000) {
            const auto nth_multi = ps::algo::nth_multiple<uint64_t>(nth_pos);
            std::cout << std::format("{}th multiple: {}", nth_pos, nth_multi) << std::endl;
        }
        else if (nth_pos <= 100'000) {
            const auto nth_multi = ps::algo::nth_multiple<ps::algo::StrInt>(nth_pos);
            std::cout << nth_pos << "th multiple: " << nth_multi << std::endl;
        }
        else {
            const auto nth_multi = ps::algo::nth_multiple_byte_stream(nth_pos);
            std::cout << nth_pos << "th multiple: " << nth_multi << std::endl;
        }
    }

    return 0;
}

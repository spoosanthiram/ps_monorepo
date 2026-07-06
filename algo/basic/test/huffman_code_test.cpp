#include "algo/basic/huffman_code.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("HuffmanCode, Encode")
{
    auto stream = ps::utils::open_stream("algo/basic/test/data/HuffmanInput.txt");

    ps::algo::HuffTree ht;
    ht.build(stream);
    ht.encode();
    ht.print_codes(std::cout);
}

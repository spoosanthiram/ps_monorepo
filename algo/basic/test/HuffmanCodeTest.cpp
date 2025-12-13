#include "algo/basic/HuffmanCode.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("HuffmanCode, Encode")
{
    auto stream = Ps::Core::open_stream("algo/basic/test/data/HuffmanInput.txt");

    Ps::Algo::HuffTree ht;
    ht.build(stream);
    ht.encode();
    ht.print_codes(std::cout);
}

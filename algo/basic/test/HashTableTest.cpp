#include "algo/basic/HashTable.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("HashTable Simple")
{
    Ps::Algo::HashTable table{100};
    table.insert(12341, 1);
    table.insert(65748, 2);

    REQUIRE(table.item_at(12341) == 1);
    REQUIRE(table.item_at(65748) == 2);

    REQUIRE_THROWS(table.item_at(3452));
}

TEST_CASE("HashTable AlgoClass2Sum")
{
    const int t1 = 2500;
    const int t2 = 4000;

    const auto integers = Ps::Core::read_integers("algo/basic/test/data/AlgoClass2Sum.txt");

    unsigned int nprobable = 0;
    for (auto n : integers) {
        if (n <= t2) {
            ++nprobable;
        }
    }

    Ps::Algo::HashTable table{nprobable};
    for (auto n : integers) {
        if (n <= t2) {
            try {
                table.insert(n, 1);
            }
            catch (...) {
            }
        }
    }

    unsigned int result = 0;

    for (auto n : integers) {
        if (n > t2) {
            continue;
        }

        if (table.is_exist(n)) {
            for (int t = t1; t <= t2; ++t) {
                int n2 = std::abs(n - t);
                if (n != n2 && table.is_exist(n2)) {
                    ++result;
                    break;
                }
            }
        }
    }

    REQUIRE(result == 206);
}

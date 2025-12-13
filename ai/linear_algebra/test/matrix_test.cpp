#include "ai/linear_algebra/matrix.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Matrix Construction And Access")
{
    ps::ai::Matrix m{2, 3};
    m(0, 0) = 0.0;
    m(1, 2) = 3;
    REQUIRE(m(0, 0) == 0.0);
    REQUIRE(m(1, 2) == 3.0);

    std::vector<double> m2_elements{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    ps::ai::Matrix m2{3, 3, m2_elements};
    REQUIRE(m2(0, 0) == 1.0);
    REQUIRE(m2(0, 1) == 2.0);
    REQUIRE(m2(0, 2) == 3.0);
    REQUIRE(m2(1, 1) == 5.0);
    REQUIRE(m2(2, 2) == 9.0);

    ps::ai::Matrix m3 = m2;
    REQUIRE(m3(0, 0) == 1.0);
    REQUIRE(m3(0, 2) == 3.0);
    REQUIRE(m3(1, 1) == 5.0);
    REQUIRE(m3(2, 2) == 9.0);
}

TEST_CASE("Matrix Gaussian Elimination")
{
    std::vector<double> elements{
         2.0,  1.0,  1.0,  5.0,
         4.0, -6.0,  0.0, -2.0,
        -2.0,  7.0,  2.0,  9.0
    };
    ps::ai::Matrix m{3, 4, elements};
    m.apply_gaussian_elimination();
    REQUIRE(m(0, 0) == 2.0);

    REQUIRE(m(1, 0) == 0.0);
    REQUIRE(m(1, 1) == -8.0);
    REQUIRE(m(1, 3) == -12.0);

    REQUIRE(m(2, 0) == 0.0);
    REQUIRE(m(2, 1) == 0.0);
    REQUIRE(m(2, 2) == 1.0);
    REQUIRE(m(2, 3) == 2.0);
}

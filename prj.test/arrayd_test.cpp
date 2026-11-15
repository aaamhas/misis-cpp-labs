#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <arrayd/arrayd.hpp>
#include <initializer_list>
#include <stdexcept>

void checkArray(const ArrayD& array, std::initializer_list<float> expected) {
    REQUIRE(array.size() == static_cast<std::ptrdiff_t>(expected.size()));

    std::ptrdiff_t index = 0;
    for (float value : expected) {
        CAPTURE(index);
        CHECK(array[index] == value);
        ++index;
    }
}

TEST_CASE("Constructors and index access") {
    const ArrayD empty;
    CHECK(empty.size() == 0);

    ArrayD array{3};
    checkArray(array, {0, 0, 0});
    array[1] = 2.5f;
    checkArray(array, {0, 2.5f, 0});

    CHECK_THROWS_AS(ArrayD(0), std::invalid_argument);
    CHECK_THROWS_AS(ArrayD(-1), std::invalid_argument);
    CHECK_THROWS_AS(static_cast<void>(array[-1]), std::invalid_argument);
    CHECK_THROWS_AS(static_cast<void>(array[array.size()]), std::invalid_argument);
    CHECK_THROWS_AS(static_cast<void>(empty[0]), std::invalid_argument);
}

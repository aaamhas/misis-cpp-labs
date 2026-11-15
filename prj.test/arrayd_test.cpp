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

TEST_CASE("Resize preserves existing elements and zeroes new ones") {
    ArrayD array{2};
    array[0] = 4;
    array[1] = 7;

    array.resize(4);
    checkArray(array, {4, 7, 0, 0});
    array.resize(1);
    checkArray(array, {4});
    array.resize(3);
    checkArray(array, {4, 0, 0});

    CHECK_THROWS_AS(array.resize(-1), std::invalid_argument);
    checkArray(array, {4, 0, 0});
    array.resize(0);
    checkArray(array, {});
}

TEST_CASE("Copies own their elements") {
    ArrayD original{2};
    original[0] = 4;
    original[1] = 7;

    ArrayD copy{original};
    copy[0] = 9;
    checkArray(copy, {9, 7});
    checkArray(original, {4, 7});

    ArrayD assigned;
    CHECK(&(assigned = original) == &assigned);
    checkArray(assigned, {4, 7});
    assigned[1] = 12;
    checkArray(original, {4, 7});

    const ArrayD& same = assigned;
    CHECK(&(assigned = same) == &assigned);
    checkArray(assigned, {4, 12});
}

TEST_CASE("Copying and assigning an empty array") {
    const ArrayD empty;

    ArrayD copy{empty};
    checkArray(copy, {});

    ArrayD assigned{2};
    assigned = empty;
    checkArray(assigned, {});
    assigned.insert(0, 5);
    checkArray(assigned, {5});
}

TEST_CASE("Insertion and removal") {
    ArrayD array;
    array.insert(0, 20);
    array.insert(0, 10);
    array.insert(array.size(), 40);
    array.insert(2, 30);
    checkArray(array, {10, 20, 30, 40});

    array.remove(1);
    checkArray(array, {10, 30, 40});
    array.remove(0);
    checkArray(array, {30, 40});
    array.remove(array.size() - 1);
    checkArray(array, {30});
    array.remove(0);
    checkArray(array, {});
}

TEST_CASE("Invalid insertion and removal preserve the array") {
    ArrayD array{2};
    array[0] = 4;
    array[1] = 7;

    CHECK_THROWS_AS(array.insert(-1, 9), std::invalid_argument);
    CHECK_THROWS_AS(array.insert(array.size() + 1, 9), std::invalid_argument);
    CHECK_THROWS_AS(array.remove(-1), std::invalid_argument);
    CHECK_THROWS_AS(array.remove(array.size()), std::invalid_argument);
    checkArray(array, {4, 7});
}

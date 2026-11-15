#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.hpp>
#include <cstdint>
#include <sstream>
#include <stdexcept>

void checkFraction(const Rational& value, std::int32_t num, std::int32_t den) {
    CHECK(value.num() == num);
    CHECK(value.den() == den);
}

TEST_CASE("Construction and normalization") {
    checkFraction(Rational{}, 0, 1);
    checkFraction(Rational{5}, 5, 1);
    checkFraction(Rational{2, 4}, 1, 2);
    checkFraction(Rational{2, -6}, -1, 3);
    checkFraction(Rational{0, -6}, 0, 1);

    CHECK_THROWS_AS(Rational(1, 0), std::invalid_argument);
}

TEST_CASE("Comparisons and unary minus") {
    const Rational a{1, 2};
    const Rational b{2, 3};

    CHECK(a == Rational(2, 4));
    CHECK(a != b);
    CHECK(a < b);
    CHECK(a <= a);
    CHECK(b > a);
    CHECK(b >= b);
    checkFraction(-a, -1, 2);
    checkFraction(a, 1, 2);
}

TEST_CASE("Arithmetic with two fractions") {
    const Rational a{1, 2};
    const Rational b{2, 3};

    checkFraction(a + b, 7, 6);
    checkFraction(a - b, -1, 6);
    checkFraction(a * b, 1, 3);
    checkFraction(a / b, 3, 4);
}

TEST_CASE("Arithmetic with an integer on either side") {
    const Rational r{1, 2};

    checkFraction(r + 2, 5, 2);
    checkFraction(r - 2, -3, 2);
    checkFraction(r * 2, 1, 1);
    checkFraction(r / 2, 1, 4);

    checkFraction(2 + r, 5, 2);
    checkFraction(2 - r, 3, 2);
    checkFraction(2 * r, 1, 1);
    checkFraction(2 / r, 4, 1);
}

TEST_CASE("Division by itself and by zero") {
    Rational r{2, 3};

    CHECK(&(r /= r) == &r);
    checkFraction(r, 1, 1);

    CHECK_THROWS_AS(r /= Rational{}, std::invalid_argument);
    CHECK_THROWS_AS(r /= 0, std::invalid_argument);
    checkFraction(r, 1, 1);
}

TEST_CASE("Input and output") {
    std::ostringstream out;
    out << Rational{2, -6} << ' ' << Rational{1, 2};
    CHECK(out.str() == "-1/3 1/2");

    std::istringstream input{"2/-6 1 / 2"};
    Rational first, second;
    REQUIRE(static_cast<bool>(input >> first >> second));
    checkFraction(first, -1, 3);
    checkFraction(second, 1, 2);
}

TEST_CASE("Invalid input preserves the fraction") {
    for (const char* text : {"2/0", "2:3", "2/x", "2/", ""}) {
        CAPTURE(text);
        std::istringstream input{text};
        Rational r{3, 4};

        input >> r;

        CHECK(input.fail());
        checkFraction(r, 3, 4);
    }
}
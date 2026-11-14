#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <complex/complex.hpp>
#include <sstream>
#include <stdexcept>
#include <utility>

void checkComplex(const Complex& z, double re, double im) {
    CHECK(z.re == re);
    CHECK(z.im == im);
}

TEST_CASE("Constructors and assignment") {
    checkComplex(Complex{}, 0, 0);
    checkComplex(Complex{5}, 5, 0);

    const Complex original{2, 3};
    Complex copy{original};
    checkComplex(copy, 2, 3);
    copy.re = 8;
    checkComplex(original, 2, 3);

    Complex moved{std::move(copy)};
    checkComplex(moved, 8, 3);

    Complex assigned;
    CHECK(&(assigned = original) == &assigned);
    checkComplex(assigned, 2, 3);
    CHECK(&(assigned = std::move(moved)) == &assigned);
    checkComplex(assigned, 8, 3);
}

TEST_CASE("Comparison and unary minus") {
    const Complex z{2, 3};

    CHECK(z == Complex(2, 3));
    CHECK_FALSE(z != Complex(2, 3));
    CHECK_FALSE(z == Complex(4, 3));
    CHECK_FALSE(z == Complex(2, 4));
    CHECK(z != Complex(4, 3));
    CHECK(z != Complex(2, 4));

    checkComplex(-z, -2, -3);
    checkComplex(z, 2, 3);
}

TEST_CASE("Binary operators with Complex and double") {
    const Complex a{2, 3};
    const Complex b{4, -1};

    checkComplex(a + b, 6, 2);
    checkComplex(a + 4.0, 6, 3);
    checkComplex(4.0 + a, 6, 3);

    checkComplex(a - b, -2, 4);
    checkComplex(a - 4.0, -2, 3);
    checkComplex(4.0 - a, 2, -3);

    checkComplex(a * b, 11, 10);
    checkComplex(a * 2.0, 4, 6);
    checkComplex(2.0 * a, 4, 6);

    checkComplex(a / Complex(1, 1), 2.5, 0.5);
    checkComplex(a / 2.0, 1, 1.5);
    checkComplex(4.0 / Complex(1, 1), 2, -2);

    checkComplex(a, 2, 3);
    checkComplex(b, 4, -1);
}

TEST_CASE("Compound assignment changes the left operand") {
    const Complex rhs{4, -1};
    Complex z{2, 3};

    CHECK(&(z += rhs) == &z);
    checkComplex(z, 6, 2);
    CHECK(&(z -= rhs) == &z);
    checkComplex(z, 2, 3);
    CHECK(&(z *= rhs) == &z);
    checkComplex(z, 11, 10);
    CHECK(&(z /= rhs) == &z);
    checkComplex(z, 2, 3);

    CHECK(&(z += 4.0) == &z);
    checkComplex(z, 6, 3);
    CHECK(&(z -= 4.0) == &z);
    checkComplex(z, 2, 3);
    CHECK(&(z *= 2.0) == &z);
    checkComplex(z, 4, 6);
    CHECK(&(z /= 2.0) == &z);
    checkComplex(z, 2, 3);

    checkComplex(rhs, 4, -1);
}

TEST_CASE("The same object on both sides") {
    Complex z{2, 3};

    z *= z;
    checkComplex(z, -5, 12);

    z /= z;
    checkComplex(z, 1, 0);
}

TEST_CASE("Division by zero") {
    Complex z{2, 3};
    const Complex zero{};

    CHECK_THROWS_AS(z /= 0.0, std::invalid_argument);
    checkComplex(z, 2, 3);
    CHECK_THROWS_AS(z /= zero, std::invalid_argument);
    checkComplex(z, 2, 3);

    CHECK_THROWS_AS(static_cast<void>(z / 0.0), std::invalid_argument);
    CHECK_THROWS_AS(static_cast<void>(z / zero), std::invalid_argument);
    CHECK_THROWS_AS(static_cast<void>(4.0 / zero), std::invalid_argument);
}

TEST_CASE("Stream output and input") {
    std::ostringstream out;
    out << Complex(2, 3) << ' ' << Complex(-1.25, 4.5);
    CHECK(out.str() == "{2,3} {-1.25,4.5}");

    std::istringstream in{"{2,3} { -1.25, 4.5 } 42"};
    Complex first, second;
    int next{};
    in >> first >> second >> next;

    REQUIRE(static_cast<bool>(in));
    checkComplex(first, 2, 3);
    checkComplex(second, -1.25, 4.5);
    CHECK(next == 42);
}

TEST_CASE("Invalid input preserves the original value") {
    for (const char* text : {"", "[2,3]", "{x,3}", "{2;3}",
                             "{2,x}", "{2,3]", "{2,3"}) {
        CAPTURE(text);
        Complex z{8, 9};
        std::istringstream in{text};

        in >> z;

        CHECK(in.fail());
        checkComplex(z, 8, 9);
    }
}
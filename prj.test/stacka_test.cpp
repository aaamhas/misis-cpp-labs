#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <stacka/stacka.hpp>
#include <cstdint>
#include <initializer_list>
#include <limits>
#include <stdexcept>

void checkStackAndPop(StackA& stack, std::initializer_list<std::int64_t> expected) {
    for (std::int64_t value : expected) {
        REQUIRE_FALSE(stack.is_empty());
        CHECK(stack.top() == value);
        stack.pop();
    }
    CHECK(stack.is_empty());
}

TEST_CASE("An empty stack handles pop and clear and rejects top") {
    StackA stack;
    const StackA& constStack = stack;

    CHECK(stack.is_empty());
    CHECK(constStack.is_empty());
    CHECK_NOTHROW(stack.pop());
    CHECK_NOTHROW(stack.clear());
    CHECK_NOTHROW(stack.clear());
    CHECK(stack.is_empty());
    CHECK_THROWS_AS(static_cast<void>(stack.top()), std::logic_error);
    CHECK_THROWS_AS(static_cast<void>(constStack.top()), std::logic_error);
}

TEST_CASE("Push and pop preserve LIFO order across buffer growth") {
    StackA stack;

    for (std::int64_t value = 0; value < 257; ++value) {
        stack.push(value);
        CHECK_FALSE(stack.is_empty());
        CHECK(stack.top() == value);
    }

    for (std::int64_t value = 256; value >= 0; --value) {
        REQUIRE_FALSE(stack.is_empty());
        CHECK(stack.top() == value);
        stack.pop();
    }
    CHECK(stack.is_empty());
    CHECK_NOTHROW(stack.pop());

    stack.push(-10);
    checkStackAndPop(stack, {-10});
}

TEST_CASE("Top allows modification and preserves all int64 values") {
    StackA stack;
    const StackA& constStack = stack;
    const auto minimum = std::numeric_limits<std::int64_t>::min();
    const auto maximum = std::numeric_limits<std::int64_t>::max();

    stack.push(minimum);
    CHECK(constStack.top() == minimum);
    stack.top() = maximum;
    CHECK(constStack.top() == maximum);

    std::int64_t value = constStack.top();
    value = 0;
    CHECK(value == 0);
    CHECK(stack.top() == maximum);

    stack.push(0);
    stack.push(-1);
    checkStackAndPop(stack, {-1, 0, maximum});
}

TEST_CASE("Copy construction creates independent stack elements") {
    StackA original;
    for (std::int64_t value : {10, 20, 30, 40, 50, 60}) {
        original.push(value);
    }

    StackA copy(original);
    copy.top() = 99;
    CHECK(original.top() == 60);
    original.pop();
    original.push(70);

    checkStackAndPop(copy, {99, 50, 40, 30, 20, 10});
    checkStackAndPop(original, {70, 50, 40, 30, 20, 10});
}

TEST_CASE("Assignment replaces existing data with an independent copy") {
    for (int oldSize : {0, 1, 12}) {
        CAPTURE(oldSize);
        StackA assigned;
        for (int i = 0; i < oldSize; ++i) {
            assigned.push(i);
        }

        {
            StackA source;
            source.push(10);
            source.push(20);
            source.push(30);

            CHECK(&(assigned = source) == &assigned);
            assigned.top() = 99;
            CHECK(source.top() == 30);
            source.clear();
        }

        checkStackAndPop(assigned, {99, 20, 10});
    }
}

TEST_CASE("Empty stacks can be copied and assigned then reused") {
    StackA empty;

    SUBCASE("A newly constructed stack") {}
    SUBCASE("A stack emptied with pop") {
        empty.push(10);
        empty.pop();
    }
    SUBCASE("A cleared stack") {
        empty.push(10);
        empty.push(20);
        empty.clear();
    }

    const StackA& source = empty;
    StackA copy(source);
    CHECK(copy.is_empty());

    StackA assigned;
    assigned.push(42);
    CHECK(&(assigned = source) == &assigned);
    CHECK(assigned.is_empty());

    copy.push(11);
    assigned.push(12);
    CHECK(empty.is_empty());
    checkStackAndPop(copy, {11});
    checkStackAndPop(assigned, {12});
}

TEST_CASE("Self-assignment preserves empty and nonempty stacks") {
    StackA stack;
    const StackA& same = stack;

    CHECK(&(stack = same) == &stack);
    CHECK(stack.is_empty());

    stack.push(10);
    stack.push(20);
    stack.push(30);
    CHECK(&(stack = same) == &stack);
    checkStackAndPop(stack, {30, 20, 10});
}

TEST_CASE("Clear permits repeated use after growth") {
    StackA stack;

    for (int cycle = 0; cycle < 3; ++cycle) {
        CAPTURE(cycle);
        for (int value = 0; value < 50; ++value) {
            stack.push(value);
        }

        CHECK_NOTHROW(stack.clear());
        CHECK(stack.is_empty());
        CHECK_THROWS_AS(static_cast<void>(stack.top()), std::logic_error);
        CHECK_NOTHROW(stack.clear());

        stack.push(100 + cycle);
        CHECK(stack.top() == 100 + cycle);
        stack.pop();
        CHECK(stack.is_empty());
    }
}

TEST_CASE("Pushing the current top works when the buffer grows") {
    for (int count : {1, 5, 10, 20, 40, 80}) {
        CAPTURE(count);
        StackA stack;
        for (int value = 0; value < count; ++value) {
            stack.push(value);
        }

        stack.push(stack.top());
        CHECK(stack.top() == count - 1);
        stack.pop();

        for (int value = count - 1; value >= 0; --value) {
            REQUIRE_FALSE(stack.is_empty());
            CHECK(stack.top() == value);
            stack.pop();
        }
        CHECK(stack.is_empty());
    }
}

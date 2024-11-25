#define BOOST_TEST_MODULE STACK_TESTS

#include <utility>
#include <boost/test/included/unit_test.hpp>
#include "../data_struct/stack.h"

using namespace data_struct;
using namespace std;

BOOST_AUTO_TEST_SUITE(stack_tests) 


BOOST_AUTO_TEST_CASE(test_move_constructor) {
    Stack<int> stack = {1, 2, 3};
    auto copy (move (stack));

    BOOST_CHECK(stack == Stack<int>{});
    BOOST_CHECK(copy == Stack<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    Stack<int> stack = {1, 2, 3};
    auto copy (stack);

    BOOST_CHECK(stack == Stack<int>({1, 2, 3}));
    BOOST_CHECK(copy == Stack<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_move_operator) {
    Stack<int> stack = {1, 2, 3};
    Stack<int> stack2 = {4, 5, 6};
    stack2 = move (stack);

    BOOST_CHECK(stack == Stack<int>{});
    BOOST_CHECK(stack2 == Stack<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_operator) {
    Stack<int> stack = {1, 2, 3};
    Stack<int> stack2 = {4, 5, 6};
    stack2 = stack;

    BOOST_CHECK(stack == Stack<int>({1, 2, 3}));
    BOOST_CHECK(stack2 == Stack<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_range) {
    int arr[] = {1, 2, 3, 4, 5, 6};

    Stack<int> stack (begin(arr), end(arr));

    BOOST_CHECK(stack == Stack<int>({1, 2, 3, 4, 5, 6}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_n) {    
    Stack<int> stack (3, 10);

    BOOST_CHECK(stack == Stack<int>({10, 10, 10}));
}


BOOST_AUTO_TEST_CASE(test_size) {
    Stack<int> stack = {1, 2, 3};

    BOOST_CHECK_EQUAL(stack.size(), 3);
}


BOOST_AUTO_TEST_CASE(test_empty) {
    Stack<int> stack;

    BOOST_CHECK_EQUAL(stack.size(), 0);
    BOOST_CHECK(stack.empty());
}


BOOST_AUTO_TEST_CASE(test_capacity) {
    Stack<int> stack(123);

    BOOST_CHECK_EQUAL(stack.capacity(), 123);

    stack.reserve (500);

    BOOST_CHECK_EQUAL(stack.capacity(), 500);
}


BOOST_AUTO_TEST_CASE(test_swap) {
    Stack<int> stack  {1, 2, 3};
    Stack<int> stack2 {4, 5, 6};

    swap (stack, stack2);

    BOOST_CHECK(stack == Stack<int>({4, 5, 6}));
    BOOST_CHECK(stack2 == Stack<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_top) {
    Stack<int> stack = {1, 2, 3};
    auto const& cref = stack;

    BOOST_CHECK_EQUAL(stack.top(), 3);
    BOOST_CHECK_EQUAL(cref.top(), 3);

    stack.pop();

    BOOST_CHECK_EQUAL(stack.top(), 2);
    BOOST_CHECK_EQUAL(cref.top(), 2);
}



BOOST_AUTO_TEST_CASE(test_push) {
    Stack<int> stack;

    stack.push (10);
    stack.push (20);
    stack.emplace (30);

    int value = 40;
    stack.push (value);

    BOOST_CHECK(stack == Stack<int>({10, 20, 30, 40}));
}


BOOST_AUTO_TEST_CASE(test_pop) {
    Stack<int> stack  {1, 2, 3, 10};

    stack.pop();
    BOOST_CHECK(stack == Stack<int>({1, 2, 3}));

    stack.pop();
    BOOST_CHECK(stack == Stack<int>({1, 2}));

    stack.pop();
    BOOST_CHECK(stack == Stack<int>({1}));

    stack.pop();
    BOOST_CHECK(stack == Stack<int>{});
}


BOOST_AUTO_TEST_CASE(test_begin_end) {
    Stack<int> stack  {1, 2, 3, 10};

    BOOST_CHECK_EQUAL (*stack.begin(), 1);
    BOOST_CHECK_EQUAL (*stack.cbegin(), 1);

    auto back1 = stack.end() - 1;
    auto back2 = stack.cend() - 1;

    BOOST_CHECK_EQUAL (*back1, 10);
    BOOST_CHECK_EQUAL (*back2, 10);
}


BOOST_AUTO_TEST_SUITE_END()
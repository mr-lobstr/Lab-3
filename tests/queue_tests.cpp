#define BOOST_TEST_MODULE QUEUE_TESTS

#include <utility>
#include <boost/test/included/unit_test.hpp>
#include "../data_struct/queue.h"

using namespace data_struct;
using namespace std;

BOOST_AUTO_TEST_SUITE(queue_tests) 


BOOST_AUTO_TEST_CASE(test_move_constructor) {
    Queue<int> queue = {1, 2, 3};
    auto copy (move (queue));

    BOOST_CHECK(queue == Queue<int>{});
    BOOST_CHECK(copy == Queue<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    Queue<int> queue = {1, 2, 3};
    auto copy (queue);

    BOOST_CHECK(queue == Queue<int>({1, 2, 3}));
    BOOST_CHECK(copy == Queue<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_move_operator) {
    Queue<int> queue = {1, 2, 3};
    Queue<int> queue2 = {4, 5, 6};
    queue2 = move (queue);

    BOOST_CHECK(queue == Queue<int>{});
    BOOST_CHECK(queue2 == Queue<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_operator) {
    Queue<int> queue = {1, 2, 3};
    Queue<int> queue2 = {4, 5, 6};
    queue2 = queue;

    BOOST_CHECK(queue == Queue<int>({1, 2, 3}));
    BOOST_CHECK(queue2 == Queue<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_range) {
    int arr[] = {1, 2, 3, 4, 5, 6};

    Queue<int> queue (begin(arr), end(arr));

    BOOST_CHECK(queue == Queue<int>({1, 2, 3, 4, 5, 6}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_n) {    
    Queue<int> queue (3, 10);

    BOOST_CHECK(queue == Queue<int>({10, 10, 10}));
}


BOOST_AUTO_TEST_CASE(test_size) {
    Queue<int> queue = {1, 2, 3};

    BOOST_CHECK_EQUAL(queue.size(), 3);
}


BOOST_AUTO_TEST_CASE(test_empty) {
    Queue<int> queue;

    BOOST_CHECK_EQUAL(queue.size(), 0);
    BOOST_CHECK(queue.empty());
}


BOOST_AUTO_TEST_CASE(test_swap) {
    Queue<int> queue  {1, 2, 3};
    Queue<int> queue2 {4, 5, 6};

    swap (queue, queue2);

    BOOST_CHECK(queue == Queue<int>({4, 5, 6}));
    BOOST_CHECK(queue2 == Queue<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_front) {
    Queue<int> queue = {1, 2, 3};
    auto const& cref = queue;

    BOOST_CHECK_EQUAL(queue.front(), 1);
    BOOST_CHECK_EQUAL(cref.front(), 1);
}


BOOST_AUTO_TEST_CASE(test_back) {
    Queue<int> queue = {1, 2, 3};
    auto const& cref = queue;

    BOOST_CHECK_EQUAL(queue.back(), 3);
    BOOST_CHECK_EQUAL(cref.back(), 3);
}


BOOST_AUTO_TEST_CASE(test_push_back) {
    Queue<int> queue  {1, 2, 3};

    queue.push_back (10);
    int twenty = 20;
    queue.push_back (twenty);
    queue.emplace_back (30);

    BOOST_CHECK(queue == Queue<int>({1, 2, 3, 10, 20, 30}));
}


BOOST_AUTO_TEST_CASE(test_pop_front) {
    Queue<int> queue  {10, 1, 2, 3};

    queue.pop_front();

    BOOST_CHECK(queue == Queue<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_begin_end) {
    Queue<int> queue  {1, 2, 3, 10};
    auto const cref = queue;

    BOOST_CHECK_EQUAL (*queue.begin(), 1);
    BOOST_CHECK_EQUAL (*cref.begin(), 1);
    BOOST_CHECK_EQUAL (*queue.cbegin(), 1);

    auto back1 = --queue.end();
    auto back2 = --cref.end();
    auto back3 = --queue.cend();

    BOOST_CHECK_EQUAL (*back1, 10);
    BOOST_CHECK_EQUAL (*back2, 10);
    BOOST_CHECK_EQUAL (*back2, 10);
}


BOOST_AUTO_TEST_SUITE_END()
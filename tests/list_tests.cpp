#define BOOST_TEST_MODULE LIST_TESTS

#include <utility>
#include <boost/test/included/unit_test.hpp>
#include "../data_struct/list.h"

using namespace data_struct;
using namespace std;

BOOST_AUTO_TEST_SUITE(list_tests) 


BOOST_AUTO_TEST_CASE(test_move_constructor) {
    List<int> list = {1, 2, 3};
    auto copy (move (list));

    BOOST_CHECK(list == List<int>{});
    BOOST_CHECK(copy == List<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    List<int> list = {1, 2, 3};
    auto copy (list);

    BOOST_CHECK(list == List<int>({1, 2, 3}));
    BOOST_CHECK(copy == List<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_move_operator) {
    List<int> list = {1, 2, 3};
    List<int> list2 = {4, 5, 6};
    list2 = move (list);

    BOOST_CHECK(list == List<int>{});
    BOOST_CHECK(list2 == List<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_operator) {
    List<int> list = {1, 2, 3};
    List<int> list2 = {4, 5, 6};
    list2 = list;

    BOOST_CHECK(list == List<int>({1, 2, 3}));
    BOOST_CHECK(list2 == List<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_range) {
    int arr[] = {1, 2, 3, 4, 5, 6};

    List<int> list (begin(arr), end(arr));

    BOOST_CHECK(list == List<int>({1, 2, 3, 4, 5, 6}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_n) {    
    List<int> list (3, 10);

    BOOST_CHECK(list == List<int>({10, 10, 10}));
}


BOOST_AUTO_TEST_CASE(test_size) {
    List<int> list = {1, 2, 3};

    BOOST_CHECK_EQUAL(list.size(), 3);
}


BOOST_AUTO_TEST_CASE(test_empty) {
    List<int> list;

    BOOST_CHECK_EQUAL(list.size(), 0);
    BOOST_CHECK(list.empty());
}


BOOST_AUTO_TEST_CASE(test_swap) {
    List<int> list  {1, 2, 3};
    List<int> list2 {4, 5, 6};

    swap (list, list2);

    BOOST_CHECK(list == List<int>({4, 5, 6}));
    BOOST_CHECK(list2 == List<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_front) {
    List<int> list = {1, 2, 3};
    auto const& cref = list;

    BOOST_CHECK_EQUAL(list.front(), 1);
    BOOST_CHECK_EQUAL(cref.front(), 1);
}


BOOST_AUTO_TEST_CASE(test_back) {
    List<int> list = {1, 2, 3};
    auto const& cref = list;

    BOOST_CHECK_EQUAL(list.back(), 3);
    BOOST_CHECK_EQUAL(cref.back(), 3);
}


BOOST_AUTO_TEST_CASE(test_insert) {
    List<int> list  {1, 2, 3};

    auto it = iter::advance (list.begin(), 2);
    it = list.insert (it, 10);

    int twenty = 20;
    list.insert (it, twenty);

    BOOST_CHECK(list == List<int>({1, 2, 20, 10, 3}));
}


BOOST_AUTO_TEST_CASE(test_push_front) {
    List<int> list  {1, 2, 3};

    list.push_front (10);
    int twenty = 20;
    list.push_front(twenty);

    BOOST_CHECK(list == List<int>({20, 10, 1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_push_back) {
    List<int> list  {1, 2, 3};

    list.push_back (10);
    int twenty = 20;
    list.push_back (twenty);

    BOOST_CHECK(list == List<int>({1, 2, 3, 10, 20}));
}


BOOST_AUTO_TEST_CASE(test_erase) {
    List<int> list  {1, 2, 10, 3};

    auto it = iter::advance (list.begin(), 2);
    it = list.erase (it);

    BOOST_CHECK(list == List<int>({1, 2, 3}));
    BOOST_CHECK_EQUAL(*it, 3);
}


BOOST_AUTO_TEST_CASE(test_pop_front) {
    List<int> list  {10, 1, 2, 3};

    list.pop_front();

    BOOST_CHECK(list == List<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_pop_back) {
    List<int> list  {1, 2, 3, 10};

    list.pop_back();

    BOOST_CHECK(list == List<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_begin_end) {
    List<int> list  {1, 2, 3, 10};
    auto const cref = list;

    BOOST_CHECK_EQUAL (*list.begin(), 1);
    BOOST_CHECK_EQUAL (*cref.begin(), 1);
    BOOST_CHECK_EQUAL (*list.cbegin(), 1);

    auto back1 = --list.end();
    auto back2 = --cref.end();
    auto back3 = --list.cend();

    BOOST_CHECK_EQUAL (*back1, 10);
    BOOST_CHECK_EQUAL (*back2, 10);
    BOOST_CHECK_EQUAL (*back2, 10);
}


BOOST_AUTO_TEST_SUITE_END()
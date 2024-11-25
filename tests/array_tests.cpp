#define BOOST_TEST_MODULE ARRAY_TESTS

#include <utility>
#include <boost/test/included/unit_test.hpp>
#include "../data_struct/dynamic_array.h"

using namespace data_struct;
using namespace std;

BOOST_AUTO_TEST_SUITE(array_tests) 


BOOST_AUTO_TEST_CASE(test_move_constructor) {
    DynamicArray<int> array = {1, 2, 3};
    auto copy (move (array));

    BOOST_CHECK(array == DynamicArray<int>{});
    BOOST_CHECK(copy == DynamicArray<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    DynamicArray<int> array = {1, 2, 3};
    auto copy (array);

    BOOST_CHECK(array == DynamicArray<int>({1, 2, 3}));
    BOOST_CHECK(copy == DynamicArray<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_move_operator) {
    DynamicArray<int> array = {1, 2, 3};
    DynamicArray<int> array2 = {4, 5, 6};
    array2 = move (array);

    BOOST_CHECK(array == DynamicArray<int>{});
    BOOST_CHECK(array2 == DynamicArray<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_operator) {
    DynamicArray<int> array = {1, 2, 3};
    DynamicArray<int> array2 = {4, 5, 6};
    array2 = array;

    BOOST_CHECK(array == DynamicArray<int>({1, 2, 3}));
    BOOST_CHECK(array2 == DynamicArray<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_range) {
    int arr[] = {1, 2, 3, 4, 5, 6};

    DynamicArray<int> array (begin(arr), end(arr));

    BOOST_CHECK(array == DynamicArray<int>({1, 2, 3, 4, 5, 6}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_n) {    
    DynamicArray<int> array (3, 10);

    BOOST_CHECK(array == DynamicArray<int>({10, 10, 10}));
}


BOOST_AUTO_TEST_CASE(test_size) {
    DynamicArray<int> array = {1, 2, 3};

    BOOST_CHECK_EQUAL(array.size(), 3);
}


BOOST_AUTO_TEST_CASE(test_empty) {
    DynamicArray<int> array;

    BOOST_CHECK_EQUAL(array.size(), 0);
    BOOST_CHECK(array.empty());
}


BOOST_AUTO_TEST_CASE(test_capacity) {
    DynamicArray<int> array(123);

    BOOST_CHECK_EQUAL(array.capacity(), 123);

    array.reserve (500);

    BOOST_CHECK_EQUAL(array.capacity(), 500);
}


BOOST_AUTO_TEST_CASE(test_swap) {
    DynamicArray<int> array  {1, 2, 3};
    DynamicArray<int> array2 {4, 5, 6};

    swap (array, array2);

    BOOST_CHECK(array == DynamicArray<int>({4, 5, 6}));
    BOOST_CHECK(array2 == DynamicArray<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_resize) {
    DynamicArray<int> array  {1, 2, 3};
    array.resize(6);

    BOOST_CHECK_EQUAL(array.size(), 6);
    BOOST_CHECK(array == DynamicArray<int>({1, 2, 3, 0, 0, 0}));

    array.resize(2);

    BOOST_CHECK_EQUAL(array.size(), 2);
    BOOST_CHECK(array == DynamicArray<int>({1, 2}));
}


BOOST_AUTO_TEST_CASE(test_index_access) {
    DynamicArray<int> array  {1, 2, 3};

    BOOST_CHECK_EQUAL(array[0], 1);
    BOOST_CHECK_EQUAL(array[1], 2);
    BOOST_CHECK_EQUAL(array[2], 3);
}


BOOST_AUTO_TEST_CASE(test_front) {
    DynamicArray<int> array = {1, 2, 3};
    auto const& cref = array;

    BOOST_CHECK_EQUAL(array.front(), 1);
    BOOST_CHECK_EQUAL(cref.front(), 1);
}


BOOST_AUTO_TEST_CASE(test_back) {
    DynamicArray<int> array = {1, 2, 3};
    auto const& cref = array;

    BOOST_CHECK_EQUAL(array.back(), 3);
    BOOST_CHECK_EQUAL(cref.back(), 3);
}


BOOST_AUTO_TEST_CASE(test_insert) {
    DynamicArray<int> array  {1, 2, 3};

    auto it = iter::advance (array.begin(), 2);
    it = array.insert (it, 10);

    int twenty = 20;
    array.insert (it, twenty);

    BOOST_CHECK(array == DynamicArray<int>({1, 2, 20, 10, 3}));
}


BOOST_AUTO_TEST_CASE(test_push_back) {
    DynamicArray<int> array  {1, 2, 3};

    array.push_back (10);
    int twenty = 20;
    array.push_back (twenty);

    BOOST_CHECK(array == DynamicArray<int>({1, 2, 3, 10, 20}));
}


BOOST_AUTO_TEST_CASE(test_erase) {
    DynamicArray<int> array  {1, 2, 10, 3};

    auto it = iter::advance (array.begin(), 2);
    array.erase (it);

    BOOST_CHECK(array == DynamicArray<int>({1, 2, 3}));
    BOOST_CHECK_EQUAL(*it, 3);
}


BOOST_AUTO_TEST_CASE(test_pop_back) {
    DynamicArray<int> array  {1, 2, 3, 10};

    array.pop_back();

    BOOST_CHECK(array == DynamicArray<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_begin_end) {
    DynamicArray<int> array  {1, 2, 3, 10};
    auto const cref = array;

    BOOST_CHECK_EQUAL (*array.begin(), 1);
    BOOST_CHECK_EQUAL (*cref.begin(), 1);
    BOOST_CHECK_EQUAL (*array.cbegin(), 1);

    auto back1 = array.end() - 1;
    auto back2 = cref.end() - 1;
    auto back3 = array.cend() - 1;

    BOOST_CHECK_EQUAL (*back1, 10);
    BOOST_CHECK_EQUAL (*back2, 10);
    BOOST_CHECK_EQUAL (*back2, 10);
}

BOOST_AUTO_TEST_SUITE_END()
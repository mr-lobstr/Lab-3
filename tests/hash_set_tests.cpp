#define BOOST_TEST_MODULE HASH_SET_TESTS

#include <utility>
#include <boost/test/included/unit_test.hpp>
#include "../data_struct/hash_set.h"

using namespace data_struct;
using namespace std;

BOOST_AUTO_TEST_SUITE(set_tests) 


BOOST_AUTO_TEST_CASE(test_move_constructor) {
    HashSet<int> set = {1, 2, 3};
    auto copy (move (set));

    BOOST_CHECK(set == HashSet<int>{});
    BOOST_CHECK(copy == HashSet<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    HashSet<int> set = {1, 2, 3};
    auto copy (set);

    BOOST_CHECK(set == HashSet<int>({1, 2, 3}));
    BOOST_CHECK(copy == HashSet<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_move_operator) {
    HashSet<int> set = {1, 2, 3};
    HashSet<int> set2 = {4, 5, 6};
    set2 = move (set);

    BOOST_CHECK(set == HashSet<int>{});
    BOOST_CHECK(set2 == HashSet<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_operator) {
    HashSet<int> set = {1, 2, 3};
    HashSet<int> set2 = {4, 5, 6};
    set2 = set;

    BOOST_CHECK(set == HashSet<int>({1, 2, 3}));
    BOOST_CHECK(set2 == HashSet<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_range) {
    int arr[] = {1, 2, 3, 4, 5, 6};

    HashSet<int> set (begin(arr), end(arr));

    BOOST_CHECK(set == HashSet<int>({1, 2, 3, 4, 5, 6}));
}


BOOST_AUTO_TEST_CASE(test_size) {
    HashSet<int> set = {1, 2, 3};

    BOOST_CHECK_EQUAL(set.size(), 3);
}


BOOST_AUTO_TEST_CASE(test_empty) {
    HashSet<int> set;

    BOOST_CHECK_EQUAL(set.size(), 0);
    BOOST_CHECK(set.empty());
}


BOOST_AUTO_TEST_CASE(test_swap) {
    HashSet<int> set  {1, 2, 3};
    HashSet<int> set2 {4, 5, 6};

    swap (set, set2);

    BOOST_CHECK(set == HashSet<int>({4, 5, 6}));
    BOOST_CHECK(set2 == HashSet<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_add) {
    HashSet<int> set  {1, 2, 3};

    set.add (10);
    set.add (20);
    
    int twenty = 20;
    int ten = 10;
    set.add (twenty);
    set.add (ten);

    BOOST_CHECK(set == HashSet<int>({1, 2, 3, 10, 20}));
    BOOST_CHECK_EQUAL(set.size(), 5);
}


BOOST_AUTO_TEST_CASE(test_erase) {
    HashSet<int> set  {1, 2, 10, 3};

    set.erase (10);
    set.erase (10);
    set.add (40);
    set.erase (40);
    set.erase (50);

    BOOST_CHECK(set == HashSet<int>({1, 2, 3}));
    BOOST_CHECK_EQUAL(set.size(), 3);
}


BOOST_AUTO_TEST_CASE(test_find) {
    HashSet<int> set  {1, 2, 3, 10};
    auto const cref = set;

    auto tenIt1 = set.find (10);
    auto tenIt2 = cref.find (10);

    BOOST_CHECK_EQUAL(*tenIt1, 10);
    BOOST_CHECK_EQUAL(*tenIt2, 10);

    auto nonIt1 = set.find (40);
    auto nonIt2 = cref.find (40);

    BOOST_CHECK(nonIt1 == set.end());
    BOOST_CHECK(nonIt2 == cref.end());
}


BOOST_AUTO_TEST_CASE(test_rehash) {
    HashSet<int> set;

    for (int i = 0; i < 1000; ++i) {
        set.add (i);
    }

    BOOST_CHECK_EQUAL(set.size(), 1000);
}


BOOST_AUTO_TEST_SUITE_END()
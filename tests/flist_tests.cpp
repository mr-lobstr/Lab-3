#define BOOST_TEST_MODULE FLIST_TESTS

#include <utility>
#include <boost/test/included/unit_test.hpp>
#include "../data_struct/flist.h"

using namespace data_struct;
using namespace std;

BOOST_AUTO_TEST_SUITE(flist_tests)


BOOST_AUTO_TEST_CASE(test_move_constructor) {
    FList<int> list = {1, 2, 3};
    auto newList (move (list));

    BOOST_CHECK(list == FList<int>{});
    BOOST_CHECK(newList == FList<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    FList<int> list = {1, 2, 3};
    auto newList (list);

    BOOST_CHECK(list == FList<int>({1, 2, 3}));
    BOOST_CHECK(newList == FList<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_move_operator) {
    FList<int> list = {1, 2, 3};
    FList<int> list2 = {4, 5, 6};
    list2 = move (list);

    BOOST_CHECK(list == FList<int>{});
    BOOST_CHECK(list2 == FList<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_operator) {
    FList<int> list = {1, 2, 3};
    FList<int> list2 = {4, 5, 6};
    list2 = list;

    BOOST_CHECK(list == FList<int>({1, 2, 3}));
    BOOST_CHECK(list2 == FList<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_range) {
    int arr[] = {1, 2, 3, 4, 5, 6};

    FList<int> list (begin(arr), end(arr));

    BOOST_CHECK(list == FList<int>({1, 2, 3, 4, 5, 6}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_n) {    
    FList<int> list (3, 10);

    BOOST_CHECK(list == FList<int>({10, 10, 10}));
}


BOOST_AUTO_TEST_CASE(test_empty) {
    FList<int> list;

    BOOST_CHECK(list.empty());
}


BOOST_AUTO_TEST_CASE(test_swap) {
    FList<int> list  {1, 2, 3};
    FList<int> list2 {4, 5, 6};

    swap (list, list2);

    BOOST_CHECK(list == FList<int>({4, 5, 6}));
    BOOST_CHECK(list2 == FList<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_front) {
    FList<int> list = {1, 2, 3};
    auto const& cref = list;

    BOOST_CHECK_EQUAL(list.front(), 1);
    BOOST_CHECK_EQUAL(cref.front(), 1);
}


BOOST_AUTO_TEST_CASE(test_insert) {
    FList<int> list  {1, 2, 3};

    auto it = iter::advance (list.begin(), 2);
    it = list.insert_after (it, 10);

    int twenty = 20;
    list.insert_after (it, twenty);

    BOOST_CHECK(list == FList<int>({1, 2, 3, 20, 10}));
}


BOOST_AUTO_TEST_CASE(test_push_front) {
    FList<int> list  {1, 2, 3};

    list.push_front (10);
    int twenty = 20;
    list.push_front(twenty);

    BOOST_CHECK(list == FList<int>({20, 10, 1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_erase) {
    FList<int> list  {1, 2, 10, 3};

    auto it = iter::advance (list.begin(), 1);
    list.erase_after (it);

    BOOST_CHECK(list == FList<int>({1, 2, 3}));
    BOOST_CHECK_EQUAL(*it, 2);
}


BOOST_AUTO_TEST_CASE(test_pop_front) {
    FList<int> list  {10, 1, 2, 3};

    list.pop_front();

    BOOST_CHECK(list == FList<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_find_prev) {
    FList<int> list = {1, 2, 3};
    auto const& cref = list;

    BOOST_CHECK_EQUAL(*list.find_prev(2), 1);
    BOOST_CHECK_EQUAL(*cref.find_prev(2), 1);

    auto it = list.find_prev(20);
    auto cIt = cref.find_prev(20);

    BOOST_CHECK(iter::next_iter (it) == list.end());
    BOOST_CHECK(iter::next_iter (cIt) == cref.end());
}


BOOST_AUTO_TEST_CASE(test_push_front_node) {
    FList<int> list = {1, 2, 3};
    FList<int> twentyNode {20};

    list.push_front_node (twentyNode.prev_begin());

    BOOST_CHECK(list == FList<int>({20, 1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_begin_end) {
    FList<int> list  {1, 2, 3, 10};
    auto const cref = list;

    BOOST_CHECK_EQUAL (*list.begin(), 1);
    BOOST_CHECK_EQUAL (*cref.begin(), 1);
    BOOST_CHECK_EQUAL (*list.cbegin(), 1);

    auto front1 = ++list.prev_begin();
    auto front2 = ++cref.prev_begin();
    auto front3 = ++list.prev_cbegin();

    BOOST_CHECK_EQUAL (*front1, 1);
    BOOST_CHECK_EQUAL (*front2, 1);
    BOOST_CHECK_EQUAL (*front2, 1);
}


BOOST_AUTO_TEST_SUITE_END() 
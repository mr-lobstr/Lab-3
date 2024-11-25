#define BOOST_TEST_MODULE COMPLETE_BINARY_TREE_TESTS

#include <utility>
#include <boost/test/included/unit_test.hpp>
#include "../data_struct/complete_binary_tree.h"

using namespace data_struct;
using namespace std;

BOOST_AUTO_TEST_SUITE(complete_binary_tree_tests) 

template <typename T>
using Tree = CompleteBinTree<T>;

BOOST_AUTO_TEST_CASE(test_move_constructor) {
    Tree<int> tree = {1, 2, 3};
    auto copy (move (tree));

    BOOST_CHECK(tree == Tree<int>{});
    BOOST_CHECK(copy == Tree<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    Tree<int> tree = {1, 2, 3};
    auto copy (tree);

    BOOST_CHECK(tree == Tree<int>({1, 2, 3}));
    BOOST_CHECK(copy == Tree<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_move_operator) {
    Tree<int> tree = {1, 2, 3};
    Tree<int> tree2 = {4, 5, 6};
    tree2 = move (tree);

    BOOST_CHECK(tree == Tree<int>{});
    BOOST_CHECK(tree2 == Tree<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_copy_operator) {
    Tree<int> tree = {1, 2, 3};
    Tree<int> tree2 = {4, 5, 6};
    tree2 = tree;

    BOOST_CHECK(tree == Tree<int>({1, 2, 3}));
    BOOST_CHECK(tree2 == Tree<int>({1, 2, 3}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_range) {
    int arr[] = {1, 2, 3, 4, 5, 6};

    Tree<int> tree (begin(arr), end(arr));

    BOOST_CHECK(tree == Tree<int>({1, 2, 3, 4, 5, 6}));
}


BOOST_AUTO_TEST_CASE(test_constructor_from_n) {    
    Tree<int> tree (3, 10);

    BOOST_CHECK(tree == Tree<int>({10, 10, 10}));
}


BOOST_AUTO_TEST_CASE(test_size) {
    Tree<int> tree = {1, 2, 3};

    BOOST_CHECK_EQUAL(tree.size(), 3);
}


BOOST_AUTO_TEST_CASE(test_empty) {
    Tree<int> tree;

    BOOST_CHECK_EQUAL(tree.size(), 0);
    BOOST_CHECK(tree.empty());
}


BOOST_AUTO_TEST_CASE(test_swap) {
    Tree<int> tree  {1, 2, 3};
    Tree<int> tree2 {4, 5, 6};

    swap (tree, tree2);

    BOOST_CHECK(tree == Tree<int>({4, 5, 6}));
    BOOST_CHECK(tree2 == Tree<int>({1, 2, 3}));
}

BOOST_AUTO_TEST_CASE(test_add) {
    Tree<int> tree  {1, 2, 3};

    tree.add (10);
    int twenty = 20;
    tree.add (twenty);

    BOOST_CHECK(tree == Tree<int>({1, 2, 3, 10, 20}));
}


BOOST_AUTO_TEST_CASE(test_pop) {
    Tree<int> tree  {1, 2, 3, 4};

    tree.pop();
    BOOST_CHECK(tree == Tree<int>({1, 2, 3}));

    tree.pop();
    BOOST_CHECK(tree == Tree<int>({1, 2}));

    tree.pop();
    BOOST_CHECK(tree == Tree<int>({1}));

    tree.pop();
    BOOST_CHECK(tree.empty());
}


BOOST_AUTO_TEST_CASE(test_begin_end) {
    Tree<int> tree  {1, 2, 3, 10};
    auto const cref = tree;

    BOOST_CHECK_EQUAL (*tree.begin(), 1);
    BOOST_CHECK_EQUAL (*cref.begin(), 1);

}


BOOST_AUTO_TEST_SUITE_END()
#define BOOST_TEST_MODULE HASH_TABLE_TESTS

#include <utility>
#include <string>
#include <boost/test/included/unit_test.hpp>
#include "../data_struct/hash_table.h"

using namespace data_struct;
using namespace std;

BOOST_AUTO_TEST_SUITE(table_tests) 

using HTable = HashTable<string, int>;

HTable OneThree {
      {"one", 1}
    , {"two", 2}
    , {"three", 3}
};

HTable FourSix {
      {"four", 4}
    , {"fife", 5}
    , {"six", 6}
};


BOOST_AUTO_TEST_CASE(test_move_constructor) {
    HTable table = OneThree;
    auto copy (move (table));

    BOOST_CHECK(table == HTable{});
    BOOST_CHECK(copy == HTable(OneThree));
}


BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    HTable table = OneThree;
    auto copy (table);

    BOOST_CHECK(table == HTable(OneThree));
    BOOST_CHECK(copy == HTable(OneThree));
}


BOOST_AUTO_TEST_CASE(test_move_operator) {
    HTable table = OneThree;
    HTable table2 = FourSix;
    table2 = move (table);

    BOOST_CHECK(table == HTable{});
    BOOST_CHECK(table2 == HTable(OneThree));
}


BOOST_AUTO_TEST_CASE(test_copy_operator) {
    HTable table = OneThree;
    HTable table2 = FourSix;
    table2 = table;

    BOOST_CHECK(table == HTable(OneThree));
    BOOST_CHECK(table2 == HTable(OneThree));
}


BOOST_AUTO_TEST_CASE(test_size) {
    HTable table = OneThree;

    BOOST_CHECK_EQUAL(table.size(), 3);
}


BOOST_AUTO_TEST_CASE(test_empty) {
    HTable table;

    BOOST_CHECK_EQUAL(table.size(), 0);
    BOOST_CHECK(table.empty());
}


BOOST_AUTO_TEST_CASE(test_swap) {
    HTable table  = OneThree;
    HTable table2 = FourSix;

    swap (table, table2);

    BOOST_CHECK(table == HTable(FourSix));
    BOOST_CHECK(table2 == HTable(OneThree));
}


BOOST_AUTO_TEST_CASE(test_add) {
    HTable table = OneThree;

    table.add ("ten", 10);
    table.add ("twenty", 20);
    
    int twenty = 20;
    int ten = 10;
    table.add ("twenty", twenty);
    table.add ("ten", ten);

    BOOST_CHECK_EQUAL(table.size(), 5);
}


BOOST_AUTO_TEST_CASE(test_erase) {
    HTable table = OneThree;

    table.erase ("one");
    table.erase ("two");
    table.erase ("three");

    BOOST_CHECK(table.empty());
}


BOOST_AUTO_TEST_CASE(test_find) {
    HTable table = OneThree;
    auto const cref = table;

    auto tenIt1 = table.find ("two");
    auto tenIt2 = cref.find ("two");

    BOOST_CHECK_EQUAL(tenIt1->value, 2);
    BOOST_CHECK_EQUAL(tenIt2->value, 2);

    auto nonIt1 = table.find ("40");
    auto nonIt2 = cref.find ("40");

    BOOST_CHECK(nonIt1 == table.end());
    BOOST_CHECK(nonIt2 == cref.end());
}


BOOST_AUTO_TEST_CASE(test_rehash) {
    HTable table;

    for (int i = 0; i < 1000; ++i) {
        table.add (to_string (i), i);
    }

    BOOST_CHECK_EQUAL(table.size(), 1000);
}


BOOST_AUTO_TEST_SUITE_END()
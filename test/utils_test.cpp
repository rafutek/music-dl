#include <boost/test/unit_test.hpp>
#include "../src/utils.hpp"
using namespace std;

BOOST_AUTO_TEST_SUITE(UtilsTestSuite)


BOOST_AUTO_TEST_CASE(number)
{
    // Should be true
    BOOST_TEST(isNumber("10"));
}

BOOST_AUTO_TEST_CASE(letters)
{
    // Should be false
    BOOST_TEST(!isNumber("aa"));
}

BOOST_AUTO_TEST_CASE(letters_and_digits)
{
    // Should be false
    BOOST_TEST(!isNumber("1a9"));
}


BOOST_AUTO_TEST_CASE(spaces_around)
{
    // Given a string with spaces around
    string s = "la lala lala";
    string spaces_around = " " + s + " ";

    // When removing spaces around
    string new_s = removeSpacesAround(spaces_around);

    // Then there must be no spaces around
    BOOST_TEST(new_s == s);
}

BOOST_AUTO_TEST_CASE(no_space_around)
{
    // Given a string with no spaces around
    string s = "la lala lala";

    // When removing spaces around
    string new_s = removeSpacesAround(s);

    // Then it must be the same string
    BOOST_TEST(new_s == s);
}

BOOST_AUTO_TEST_CASE(one_space_around)
{
    // Given a string with one space around
    string s = "la lala lala";
    string space_left = " " + s;
    string space_right = s + " ";

    // When removing spaces around
    string no_space_left = removeSpacesAround(space_left);
    string no_space_right = removeSpacesAround(space_right);

    // Then there must be no spaces around
    BOOST_TEST(no_space_left == s);
    BOOST_TEST(no_space_right == s);
}

BOOST_AUTO_TEST_CASE(remove_all_spaces)
{
    // Given a string with spaces
    string s = " la lala lala ";

    // When removing spaces
    string new_s = removeSpaces(s);

    // Then there must be no spaces
    BOOST_TEST(new_s == "lalalalala");
}

BOOST_AUTO_TEST_SUITE_END()
#include <boost/test/unit_test.hpp>
#include "../src/variables.hpp"
using namespace std;

BOOST_AUTO_TEST_SUITE(VariablesTestSuite)

BOOST_AUTO_TEST_CASE(constant_program_name)
{
    // Given a variables object filled
    Variables vars = Variables();
    string initial_prog_name = "program";
    vars.setProgName(initial_prog_name);

    // When geting and modifying the value
    string new_prog_name = vars.getProgName();
    new_prog_name = "prog";
    // vars.getProgName() = "dd"; // should not be possible to change constant

    // Then the variable in the object must not change
    BOOST_TEST(vars.getProgName() == initial_prog_name);
}

BOOST_AUTO_TEST_CASE(vars_compatible)
{
    // Given a variables object with compatible variables
    Variables vars = Variables();
    vars.setLanguage(Lang::FR);
    vars.setCoverPath("some/path/to/cover");
    vars.setExtractCover(false);
    vars.setArtist("some great artist");
    vars.setExtractArtist(false);

    // Then the variables must be compatible
    BOOST_TEST(vars.areCompatible());

    // Opposite
    vars.setCoverPath("");
    vars.setExtractCover(true);
    vars.setArtist("Inconnu");
    vars.setExtractArtist(true);
    BOOST_TEST(vars.areCompatible());
}

BOOST_AUTO_TEST_CASE(vars_not_compatible)
{
    // Given a variables object with no compatible variables
    Variables vars = Variables();
    vars.setLanguage(Lang::FR);
    vars.setCoverPath("some/path/to/cover");
    vars.setExtractCover(true);
    vars.setArtist("some great artist");
    vars.setExtractArtist(true);

    // Then the variables must be not compatible
    BOOST_TEST(!vars.areCompatible());
}



BOOST_AUTO_TEST_SUITE_END()

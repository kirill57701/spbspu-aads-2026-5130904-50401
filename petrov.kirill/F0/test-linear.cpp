#include <boost/test/unit_test.hpp>
#include "../common/LinearRegression.hpp"

BOOST_AUTO_TEST_SUITE(Lineartest)

BOOST_AUTO_TEST_CASE(construct)
{
  petrov::LinearRegression model;
  BOOST_CHECK_EQUAL(model.getWsize(), 1);
}

BOOST_AUTO_TEST_SUITE_END()

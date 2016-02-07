#ifndef IFRSEarlyWarningCompany_test
#define IFRSEarlyWarningCompany_test

#include <iostream>

//#include <math.h>
#include <boost\test\unit_test.hpp>

#include <sbsa\IFRS\IFRSEarlyWarningCompany.h>

// to use the isnan(...) function
#include <boost\math\special_functions\fpclassify.hpp>

using namespace sbsa;

class IFRSEarlyWarningCompanyTest 
{
  public:

    static void testConstruction();

    static boost::unit_test_framework::test_suite* suite();
};

#endif



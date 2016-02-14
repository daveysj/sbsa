#ifndef IFRSEarlyWarningDashboard_test
#define IFRSEarlyWarningDashboard_test

#include <iostream>

//#include <math.h>
#include <boost\test\unit_test.hpp>

#include <sbsa\IFRS\IFRSEarlyWarningDashboard.h>

// to use the isnan(...) function
#include <boost\math\special_functions\fpclassify.hpp>

using namespace sbsa;


class IFRSEarlyWarningDashboardTest 
{
  public:

    static void testConstruction();
    static void testAgainstPmrrSubsectors();
    static void testChangeInPDForOneSector();

    static boost::unit_test_framework::test_suite* suite();

    static boost::shared_ptr<IFRSEarlyWarningDashboard> getTestDashboard();
};

#endif



#include "IFRSEarlyWarningCompanyTest.h"

//#include <boost/assign/std/vector.hpp>
//#include <boost\assign\std\map.hpp>
#include <boost/assign/list_inserter.hpp> // for 'insert()'
#include <boost/assert.hpp> 

//using namespace std;
using namespace boost::unit_test_framework;
using namespace boost::math;
using namespace sbsa;

using namespace boost::assign; // used to initialize vector

void IFRSEarlyWarningCompanyTest::testConstruction() 
{
   BOOST_MESSAGE("Testing IFRSEarlyWarningCompany ...");

   string companyName = "Test Company"; 
   string companySector = "Test Sector"; 
   string companySubSector = "Test SubSector";

   boost::shared_ptr<IFRSEarlyWarningCompany> company = boost::shared_ptr<IFRSEarlyWarningCompany>(
      new IFRSEarlyWarningCompany(companyName, companySector, companySubSector));
   BOOST_CHECK(!company->isOK());

   double marketCap = 1001.0; 
   map<Date, double> historicPDs;
   insert(historicPDs)   
      (Date(1, Jan, 2016), 0.05) 
      (Date(2, Jan, 2016), 0.06)
      (Date(3, Jan, 2016), 0.07);
   
   company = boost::shared_ptr<IFRSEarlyWarningCompany>(new 
      IFRSEarlyWarningCompany(companyName, 
                              companySector, 
                              companySubSector,
                              marketCap,
                              historicPDs));

   BOOST_CHECK(company->isOK());
   BOOST_CHECK(company->getCompanyName().compare("Test Company") == 0);
   BOOST_CHECK(company->getSector().compare("Test Sector") == 0); 
   BOOST_CHECK(company->getSubSector().compare("Test SubSector") == 0);
   BOOST_CHECK(abs(company->getMarketCap() - marketCap) < 1e-14); 
   BOOST_CHECK(company->containsData(Date(2, Jan, 2016)));
   BOOST_CHECK(!company->containsData(Date(4, Jan, 2016)));
   BOOST_CHECK(company->getFirstDataDate() - Date(1, Jan, 2016) == 0);
   BOOST_CHECK(company->getLastDataDate() - Date(3, Jan, 2016) == 0);
   BOOST_CHECK(abs(company->getDefaultProbability(Date(2, Jan, 2016)) - 0.06) < 1e-14);
   BOOST_CHECK(company->containsDataOnEveryDateBetween(Date(1, Jan, 2016), Date(3, Jan, 2016)));

   map<Date, double> historicPDs2;
   insert(historicPDs2)   
      (Date(1, Jan, 2016), 0.05) 
      (Date(3, Jan, 2016), 0.06)
      (Date(4, Jan, 2016), 0.07);
   
   company = boost::shared_ptr<IFRSEarlyWarningCompany>(new 
      IFRSEarlyWarningCompany(companyName, 
                              companySector, 
                              companySubSector,
                              marketCap,
                              historicPDs2));
   BOOST_CHECK(!company->containsDataOnEveryDateBetween(Date(1, Jan, 2016), Date(3, Jan, 2016)));
}


test_suite* IFRSEarlyWarningCompanyTest::suite() 
{
    test_suite* suite = BOOST_TEST_SUITE("IFRSEarlyWarningCompany Tests");
    suite->add(BOOST_TEST_CASE(&IFRSEarlyWarningCompanyTest::testConstruction));


    return suite;
}


#include "IFRSEarlyWarningDashboardTest.h"

#include <boost/assign/list_inserter.hpp> // for 'insert()'
#include <boost/assert.hpp> 

using namespace boost::unit_test_framework;
using namespace boost::math;
using namespace sbsa;

using namespace boost::assign; // used to initialize vector

void IFRSEarlyWarningDashboardTest::testConstruction() 
{
   BOOST_MESSAGE("Testing IFRSEarlyWarningDashboard ...");

   string companyName = "Company"; 
   string companySector = "Sector"; 
   string companySubSector = "SubSector";
   boost::shared_ptr<IFRSEarlyWarningCompany> company = boost::shared_ptr<IFRSEarlyWarningCompany>(new 
      IFRSEarlyWarningCompany(companyName, 
                              companySector, 
                              companySubSector));


   string companyName1 = "Company1"; 
   string companySector1 = "Sector1"; 
   string companySubSector1 = "SubSector1";
   double marketCap1 = 1001.0; 
   map<Date, double> historicPDs1;
   insert(historicPDs1)   
      (Date(1, Jan, 2016), 0.05) 
      (Date(2, Jan, 2016), 0.06)
      (Date(3, Jan, 2016), 0.07);   
   boost::shared_ptr<IFRSEarlyWarningCompany> company1 = boost::shared_ptr<IFRSEarlyWarningCompany>(new 
      IFRSEarlyWarningCompany(companyName1, 
                              companySector1, 
                              companySubSector1,
                              marketCap1,
                              historicPDs1));


   string companyName2 = "Company2"; 
   string companySubSector2 = "SubSector2";
   double marketCap2 = 11.0; 
   boost::shared_ptr<IFRSEarlyWarningCompany> company2 = boost::shared_ptr<IFRSEarlyWarningCompany>(new 
      IFRSEarlyWarningCompany(companyName2, 
                              companySector1, 
                              companySubSector2,
                              marketCap2,
                              historicPDs1));
   
   string companySubSector3 = "SubSector3";
   double marketCap3 = 105.0; 
   boost::shared_ptr<IFRSEarlyWarningCompany> company3 = boost::shared_ptr<IFRSEarlyWarningCompany>(new 
      IFRSEarlyWarningCompany("Company3", 
                              companySector1, 
                              companySubSector3,
                              marketCap3,
                              historicPDs1));

   boost::shared_ptr<IFRSEarlyWarningCompany> company4 = boost::shared_ptr<IFRSEarlyWarningCompany>(new 
      IFRSEarlyWarningCompany("Company4", 
                              companySector1, 
                              companySubSector1,
                              marketCap1,
                              historicPDs1));

   boost::shared_ptr<IFRSEarlyWarningCompany> company5 = boost::shared_ptr<IFRSEarlyWarningCompany>(new 
      IFRSEarlyWarningCompany("Company5", 
                              companySector1, 
                              companySubSector2,
                              marketCap1,
                              historicPDs1));


   vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companies;
   companies.push_back(company);
   companies.push_back(company1);
   companies.push_back(company2);
   companies.push_back(company3);
   companies.push_back(company4);
   companies.push_back(company5);

   boost::shared_ptr<IFRSEarlyDashboard> dashboard = boost::shared_ptr<IFRSEarlyDashboard>(
      new IFRSEarlyDashboard(companies));

   BOOST_CHECK(dashboard->getNumberOfInputCompanies() == 6);
   BOOST_CHECK(dashboard->getNumberOfUsableCompanies() == 5);

   BOOST_CHECK(dashboard->getUniqueSectors().size() == 1);
   BOOST_CHECK(dashboard->getUniqueSubSectors().size() == 3);

   vector<string> originalCompanyNames = dashboard->getOrderedCompanyNames();
   dashboard->sortAccordingToSubsectors();
   vector<string> sortedCompanyNames = dashboard->getOrderedCompanyNames();
   for (size_t i = 0; i < originalCompanyNames.size(); ++i)
   {
      cout << originalCompanyNames[i] << ": " << sortedCompanyNames[i] << endl;
   }
}


test_suite* IFRSEarlyWarningDashboardTest::suite() 
{
    test_suite* suite = BOOST_TEST_SUITE("IFRSEarlyWarningDashboard Tests");
    suite->add(BOOST_TEST_CASE(&IFRSEarlyWarningDashboardTest::testConstruction));


    return suite;
}


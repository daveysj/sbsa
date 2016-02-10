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

   boost::shared_ptr<IFRSEarlyDashboard> dashboard = getTestDashboard();

   BOOST_CHECK(dashboard->getNumberOfInputCompanies() == 6);
   BOOST_CHECK(dashboard->getCompaniesWithoutData().size() == 1);
   BOOST_CHECK(dashboard->getNumberOfUsableCompanies() == 5);
   BOOST_CHECK(dashboard->getCompaniesWithData().size() == 5);
   BOOST_CHECK(dashboard->getUniqueSectors().size() == 1);
   BOOST_CHECK(dashboard->getUniqueSubSectors().size() == 3);

   std::map<string, vector<boost::shared_ptr<IFRSEarlyWarningCompany>>> companiesBySector = 
      dashboard->groupCompaniesBySubsector();
   std::map<string, vector<boost::shared_ptr<IFRSEarlyWarningCompany>>>::iterator it;
   it = companiesBySector.find("SubSector1");
   BOOST_REQUIRE(it != companiesBySector.end());
   BOOST_CHECK((it->second).size() == 2);

   it = companiesBySector.find("SubSector2");
   BOOST_REQUIRE(it != companiesBySector.end());
   BOOST_CHECK((it->second).size() == 2);

   it = companiesBySector.find("SubSector3");
   BOOST_REQUIRE(it != companiesBySector.end());
   BOOST_CHECK((it->second).size() == 1);

}

void IFRSEarlyWarningDashboardTest::testAgainstPmrrSubsectors() 
{
   boost::shared_ptr<IFRSEarlyDashboard> dashboard = getTestDashboard();

   pmrrSector pmmrSector1, pmmrSector2, pmmrSector4, pmmrSector5;
   pmmrSector1.sectorName = "Sector1";
   pmmrSector1.subsectorName = "SubSector1";
   pmmrSector1.subsectorReviewDate = Date(27, Jan, 2016);

   pmmrSector2.sectorName = "Sector1";
   pmmrSector2.subsectorName = "SubSector2";
   pmmrSector2.subsectorReviewDate = Date(27, Jan, 2016);

   pmmrSector4.sectorName = "Sector1";
   pmmrSector4.subsectorName = "SubSector4";
   pmmrSector4.subsectorReviewDate = Date(27, Jan, 2016);

   pmmrSector5.sectorName = "Sector1";
   pmmrSector5.subsectorName = "SubSector5";
   pmmrSector5.subsectorReviewDate = Date(27, Jan, 2016);

   vector<pmrrSector> pmrrSectors;
   pmrrSectors.push_back(pmmrSector1);
   pmrrSectors.push_back(pmmrSector2);
   pmrrSectors.push_back(pmmrSector4);
   pmrrSectors.push_back(pmmrSector5);

   vector<pmrrSector> unrepresentedPmrrSubsectors;
   set<string> unrepresetnedSubsectorNames;

   dashboard->checkAllSubSectorsExist(pmrrSectors, unrepresentedPmrrSubsectors, unrepresetnedSubsectorNames);
   BOOST_CHECK(unrepresentedPmrrSubsectors.size() == 2);
   BOOST_CHECK(unrepresetnedSubsectorNames.size() == 1);

   pmrrSector pmmrSector3;
   pmmrSector3.sectorName = "Sector1";
   pmmrSector3.subsectorName = "SubSector3";
   pmmrSector3.subsectorReviewDate = Date(27, Jan, 2016);
   pmrrSectors.push_back(pmmrSector3);
   dashboard->checkAllSubSectorsExist(pmrrSectors, unrepresentedPmrrSubsectors, unrepresetnedSubsectorNames);
   BOOST_CHECK(unrepresentedPmrrSubsectors.size() == 2);
   BOOST_CHECK(unrepresetnedSubsectorNames.size() == 0);

}

test_suite* IFRSEarlyWarningDashboardTest::suite() 
{
    test_suite* suite = BOOST_TEST_SUITE("IFRSEarlyWarningDashboard Tests");
    suite->add(BOOST_TEST_CASE(&IFRSEarlyWarningDashboardTest::testConstruction));
    suite->add(BOOST_TEST_CASE(&IFRSEarlyWarningDashboardTest::testAgainstPmrrSubsectors));


    return suite;
}


boost::shared_ptr<IFRSEarlyDashboard> IFRSEarlyWarningDashboardTest::getTestDashboard() 
{
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

   return dashboard;
}


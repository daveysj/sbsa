#ifndef SBSA_IFRSEarlyWarningDashboard
#define SBSA_IFRSEarlyWarningDashboard

#include <set>
#include <map>

#include <boost\bind.hpp>

#include "IFRSEarlyWarningCompany.h"
#include "PRMCSectors.h"

using namespace std;
using namespace QuantLib;

namespace sbsa
{
   bool is_in_sub_sector(const boost::shared_ptr<IFRSEarlyWarningCompany> company, const std::string &wanted);

   struct ifrsSector
   {
      string sectorName;
      string subsectorName;
      Date sectorReviewDate;
      Date todaysDate;
      int numberOfShares;
      double ratingNotchChange;
      double basePD;
      double currentPD;
   };

   /*======================================================================================
     sbsa::IFRSEarlyDashboard : Takes a collection of companies, sorts them according to 
     a criteria and performs analysis on the subsets

   =======================================================================================*/
   class IFRSEarlyDashboard
   {
   public:
      // Constructor for a company with incomplete information
      IFRSEarlyDashboard(vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companies);
        
      virtual bool isOK();
      void resetErrorMessages();
      vector<string> getErrorMessages() const;
      string getErrorMessagesAsString() const;

      int getNumberOfInputCompanies();
      int getNumberOfUsableCompanies();
      set<string> getUniqueSectors();
      set<string> getUniqueSubSectors();
      vector<boost::shared_ptr<IFRSEarlyWarningCompany>> getCompaniesWithoutData();
      vector<boost::shared_ptr<IFRSEarlyWarningCompany>> getCompaniesWithData();

      // Compares the list of "uniqueSubsectors" against the input pmrrSectors.subsectorName and
      // unrepresentedPmrrSubsectors returns a vector of all subsector names that are in "pmrrSectors" but not in "companies"
      // unrepresetnedSubsectors returns a vector of all subsector names that are in "companies" but not in "pmrrSectors"
      // As a rule the "unrepresetnedSubsectors" vector should be blank before any analysis is performed
      void checkAllSubSectorsExist(vector<pmrrSector> pmrrSectors, 
                                   vector<pmrrSector> &unrepresentedPmrrSubsectors,
                                   set<string> &unrepresetnedSubsectorNames);

      vector<boost::shared_ptr<ifrsSector>> getSubsectorRatingsChange(vector<boost::shared_ptr<pmrrSector>> pmrrSectors);

      std::map<string, vector<boost::shared_ptr<IFRSEarlyWarningCompany>>> groupCompaniesBySubsector();

    private:

      int inputCompanies, usableCompanies;
      vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companies;
      vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companiesWithoutData;
      set<string> uniqueSectors;
      set<string> uniqueSubsectors;
      boost::shared_ptr<sjdTools::ErrorTracking> errorTracking;
    };
}


#endif

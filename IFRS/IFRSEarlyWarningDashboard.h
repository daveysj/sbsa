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
      Date subsectorReviewDate;
      Date todaysDate;
      size_t numberOfShares;
      double ratingNotchChange;
      double basePD;
      double currentPD;
   };

   /*======================================================================================
     sbsa::IFRSEarlyWarningDashboard : Takes a collection of companies, sorts them according to 
     a criteria and performs analysis on the subsets

   =======================================================================================*/
   class IFRSEarlyWarningDashboard
   {
   public:
      // Constructor for a company with incomplete information
      IFRSEarlyWarningDashboard(std::vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companies);
        
      virtual bool isOK();
      void resetErrorMessages();
      std::vector<string> getErrorMessages() const;
      string getErrorMessagesAsString() const;

      int getNumberOfInputCompanies();
      int getNumberOfUsableCompanies();
      set<string> getUniqueSectors();
      set<string> getUniqueSubSectors();
      std::vector<boost::shared_ptr<IFRSEarlyWarningCompany>> getCompaniesWithoutData();
      std::vector<boost::shared_ptr<IFRSEarlyWarningCompany>> getCompaniesWithData();

      // Compares the list of "uniqueSubsectors" against the input pmrrSectors.subsectorName and
      // unrepresentedPmrrSubsectors returns a vector of all subsector names that are in 
      //    "pmrrSectors" but not in "companies"
      // unrepresetnedSubsectors returns a vector of all subsector names that are in "companies" 
      //    but not in "pmrrSectors"
      // As a rule the "unrepresetnedSubsectors" vector should be empty before any analysis is 
      // performed.
      void checkAllSubSectorsExist(std::vector<pmrrSector> pmrrSectors, 
                                   std::vector<pmrrSector> &unrepresentedPmrrSubsectors,
                                   set<string> &unrepresetnedSubsectorNames);

      void checkAllSubSectorsExist(PMRRSectors pmrrSectors, 
                                   PMRRSectors &unrepresentedPmrrSubsectors,
                                   set<string> &unrepresetnedSubsectorNames);

      std::vector<ifrsSector> getSubsectorRatingsChange(std::vector<pmrrSector> pmrrSectors, Date toDate);

      // Groups companies by Subsector name (camelCase version)
      std::map<string, std::vector<boost::shared_ptr<IFRSEarlyWarningCompany>>> groupCompaniesBySubsector();

      // returns a vector of companies which were not included in the calcuation becuase the did not have
      // data on either the fromDate or the toDate
      static std::vector<boost::shared_ptr<IFRSEarlyWarningCompany>> getCompaniesWithoutMissingData(
                                                            std::vector<boost::shared_ptr<IFRSEarlyWarningCompany>> groupedCompanies, 
                                                            Date fromDate, 
                                                            Date toDate);

      static void getChangeInPD(std::vector<boost::shared_ptr<IFRSEarlyWarningCompany>> groupedCompanies, 
                                Date fromDate, 
                                Date toDate,
                                double &basePD,
                                double &currentPD,
                                double &changeInPD);

      static double convertChangeInPDToChangeInRatings(double pd);

   private:

      int inputCompanies, usableCompanies;
      std::vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companies;
      std::vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companiesWithoutData;
      set<string> uniqueSectors;
      set<string> uniqueSubsectors;
      boost::shared_ptr<sjdTools::ErrorTracking> errorTracking;
    };
}


#endif

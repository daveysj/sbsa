#ifndef SBSA_IFRSEarlyWarningCompany
#define SBSA_IFRSEarlyWarningCompany

#include <map>
#include <vector>
#include <string>

#include <ql\time\date.hpp>

#include <boost\shared_ptr.hpp>
#include <boost\algorithm\string.hpp>

#include <Tools\Tools.h>

using namespace std;
using namespace QuantLib;

namespace sbsa
{

   /*======================================================================================
     sbsa::IFRSEarlyWarningCompany

   =======================================================================================*/
   class IFRSEarlyWarningCompany
   {
   public:
      // Constructor for a company with incomplete information
      IFRSEarlyWarningCompany(string companyName, 
                              string companySector, 
                              string companySubSector);

      IFRSEarlyWarningCompany(string companyName, 
                              string companySector, 
                              string companySubSector,
                              double marketCap,
                              map<Date, double> historicPDs);
        
      virtual bool isOK();
      void resetErrorMessages();
      std::vector<string> getErrorMessages() const;
      string getErrorMessagesAsString() const;

      string getCompanyName();
      string getSector(); 
      string getSubSector();
      double getMarketCap(); 

      bool containsData(Date onDate);
      // returns true if there is data on every day between and including [fromDate, toDate]
      bool containsDataOnEveryDateBetween(Date fromDate, Date toDate);

      Date getFirstDataDate();
      Date getLastDataDate();

      double getDefaultProbability(Date onDate);

    private:
      boost::shared_ptr<sjdTools::ErrorTracking> errorTracking;
          
      string companyName, companySector, companySubSector;
      double marketCap; 
      map<Date, double> historicPDs;
    };
}


#endif

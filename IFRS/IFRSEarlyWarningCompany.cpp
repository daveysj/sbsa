#include "IFRSEarlyWarningCompany.h"


namespace sbsa
{
   IFRSEarlyWarningCompany::IFRSEarlyWarningCompany(string companyNameInput, 
                                                    string companySectorInput, 
                                                    string companySubSectorInput) : historicPDs()
   {
      errorTracking = boost::shared_ptr<sjdTools::ErrorTracking>(
         new sjdTools::ErrorTracking("IFRSEarlyWarningCompany"));
      resetErrorMessages();

      companyName = sjdTools::camelCase(companyNameInput); 
      companySector = sjdTools::camelCase(companySectorInput); 
      companySubSector = sjdTools::camelCase(companySubSectorInput);
      errorTracking->populateErrorMessage("Insufficient input data");
   }

   IFRSEarlyWarningCompany::IFRSEarlyWarningCompany(string companyNameInput, 
                                                    string companySectorInput, 
                                                    string companySubSectorInput,
                                                    double marketCapInput, 
                                                    map<Date, double> historicPDsInput) 
   {
      errorTracking = boost::shared_ptr<sjdTools::ErrorTracking>(
         new sjdTools::ErrorTracking("IFRSEarlyWarningCompany"));
      resetErrorMessages();

      companyName = sjdTools::camelCase(companyNameInput); 
      companySector = sjdTools::camelCase(companySectorInput); 
      companySubSector = sjdTools::camelCase(companySubSectorInput);
      marketCap = marketCapInput;
      historicPDs = historicPDsInput;

      if (marketCap < 0)
      {
         errorTracking->populateErrorMessage("Market Capitalisation must be non-negative");
      }

      map<Date, double>::iterator it;
      for (it = historicPDs.begin(); it != historicPDs.end(); ++it)
      {
         if (it->second < 0)
         {
            errorTracking->populateErrorMessage("At least one default probability is negative");
         }
      }
   }


   void IFRSEarlyWarningCompany::resetErrorMessages()
   {
       errorTracking->clearErrorMessages();
   }

   bool IFRSEarlyWarningCompany::isOK()
   {
       return !errorTracking->getHasErrors();
   }

   vector<string> IFRSEarlyWarningCompany::getErrorMessages() const 
   {
       return errorTracking->getErrorMessages();
   }

   string IFRSEarlyWarningCompany::getErrorMessagesAsString() const 
   {
       return errorTracking->getErrorMessagesAsString();
   }

   string IFRSEarlyWarningCompany::getCompanyName()
   {
      return companyName;
   }

   string IFRSEarlyWarningCompany::getSector()
   {
      return companySector;
   }

   string IFRSEarlyWarningCompany::getSubSector()
   {
      return companySubSector;
   }

   double IFRSEarlyWarningCompany::getMarketCap()
   {
      return marketCap;
   }


   bool IFRSEarlyWarningCompany::containsData(Date onDate)
   {
      map<Date, double>::iterator it = historicPDs.find(onDate);
      if(it != historicPDs.end())
      {
         return true;
      }
      return false;
   }

   bool IFRSEarlyWarningCompany::containsDataOnEveryDateBetween(Date fromDate, Date toDate)
   {
      if (toDate < fromDate)
      {
         return false;
      }
      map<Date, double>::iterator it = historicPDs.find(fromDate);
      if(it == historicPDs.end())
      {
         return false;
      }
      Date dateToCheck = fromDate;
      while (dateToCheck < toDate)
      {
         dateToCheck += 1;
         ++it;
         if (dateToCheck != it->first)
         {
            return false;
         }
      }
      return true;
   }

   Date IFRSEarlyWarningCompany::getFirstDataDate()
   {
      return historicPDs.begin()->first;
   }

   Date IFRSEarlyWarningCompany::getLastDataDate()
   {
      return historicPDs.rbegin()->first;
   }

   double IFRSEarlyWarningCompany::getDefaultProbability(Date onDate)
   {
      map<Date, double>::iterator it = historicPDs.find(onDate);
      if(it != historicPDs.end())
      {
         return it->second;
      }
      return -1;
   }
}
#include "IFRSEarlyWarningDashboard.h"


namespace sbsa
{
   bool is_in_sub_sector(const boost::shared_ptr<IFRSEarlyWarningCompany> company, const std::string &wanted)
   {
      return company->getSubSector().compare(wanted) == 0;
   }


   IFRSEarlyDashboard::IFRSEarlyDashboard(vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companiesInput)
   {
      errorTracking = boost::shared_ptr<sjdTools::ErrorTracking>(
         new sjdTools::ErrorTracking("IFRSEarlyDashboard"));
      resetErrorMessages();

      companies = vector<boost::shared_ptr<IFRSEarlyWarningCompany>>();
      for (size_t i = 0; i < companiesInput.size(); ++i)
      {
         if (companiesInput[i]->isOK()) 
         {
            companies.push_back(companiesInput[i]);
            uniqueSectors.insert(companiesInput[i]->getSector());
            uniqueSubsectors.insert(companiesInput[i]->getSubSector());
         }
      }
      inputCompanies = companiesInput.size();
      usableCompanies = companies.size();


   }

   void IFRSEarlyDashboard::resetErrorMessages()
   {
       errorTracking->clearErrorMessages();
   }

   bool IFRSEarlyDashboard::isOK()
   {
       return !errorTracking->getHasErrors();
   }

   vector<string> IFRSEarlyDashboard::getErrorMessages() const 
   {
       return errorTracking->getErrorMessages();
   }

   string IFRSEarlyDashboard::getErrorMessagesAsString() const 
   {
       return errorTracking->getErrorMessagesAsString();
   }

   int IFRSEarlyDashboard::getNumberOfInputCompanies()
   {
      return inputCompanies; 
   }
   
   int IFRSEarlyDashboard::getNumberOfUsableCompanies()
   {
      return usableCompanies;
   }

   set<string> IFRSEarlyDashboard::getUniqueSectors()
   {
      return uniqueSectors;
   }

   set<string> IFRSEarlyDashboard::getUniqueSubSectors()
   {
      return uniqueSubsectors;
   }

   vector<boost::shared_ptr<ifrsSector>> IFRSEarlyDashboard::getSubsectorRatingsChange(boost::shared_ptr<PMRRSectors> pmrrSectors)
   {
      vector<boost::shared_ptr<ifrsSector>> tmp;
      return tmp;
   }

   vector<vector<boost::shared_ptr<IFRSEarlyWarningCompany>>::iterator> IFRSEarlyDashboard::sortAccordingToSubsectors()
   {
      vector<vector<boost::shared_ptr<IFRSEarlyWarningCompany>>::iterator> companiesbySubsector;
      vector<boost::shared_ptr<IFRSEarlyWarningCompany>>::iterator startingLocation = companies.begin();
      companiesbySubsector.push_back(companies.begin());

      set<string>::iterator subsectorIT;
      for (subsectorIT = uniqueSubsectors.begin(); subsectorIT != uniqueSubsectors.end(); ++subsectorIT)
      {
         vector<boost::shared_ptr<IFRSEarlyWarningCompany>>::iterator companyIT;
         companyIT = std::partition (startingLocation, companies.end(), 
            boost::bind(is_in_sub_sector, _1, *subsectorIT));
         companiesbySubsector.push_back(companyIT);
         startingLocation = companyIT;
      }
      return companiesbySubsector;
   }

   vector<string> IFRSEarlyDashboard::getOrderedCompanyNames()
   {
      vector<string> companyNames;
      for (size_t i = 0; i < companies.size(); ++i)
      {
         companyNames.push_back(companies[i]->getCompanyName());
      }
      return companyNames;
   }


}
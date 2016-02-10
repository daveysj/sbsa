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
      companiesWithoutData  = vector<boost::shared_ptr<IFRSEarlyWarningCompany>>();
      for (size_t i = 0; i < companiesInput.size(); ++i)
      {
         if (companiesInput[i]->isOK()) 
         {
            companies.push_back(companiesInput[i]);
            uniqueSectors.insert(companiesInput[i]->getSector());
            uniqueSubsectors.insert(companiesInput[i]->getSubSector());
         }
         else 
         {
             companiesWithoutData.push_back(companiesInput[i]);
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

   vector<boost::shared_ptr<IFRSEarlyWarningCompany>> IFRSEarlyDashboard::getCompaniesWithoutData()
   {
      return companiesWithoutData;
   }

   vector<boost::shared_ptr<IFRSEarlyWarningCompany>> IFRSEarlyDashboard::getCompaniesWithData()
   {
      return companies;
   }

   void IFRSEarlyDashboard::checkAllSubSectorsExist(vector<pmrrSector> pmrrSectors, 
                                                    vector<pmrrSector> &unrepresentedPmrrSubsectors,
                                                    set<string> &unrepresetnedSubsectors)
   {
      unrepresentedPmrrSubsectors = vector<pmrrSector>();
      unrepresetnedSubsectors = set<string>();

      set<string> inputSubsectorNames;
      vector<pmrrSector>::iterator it;
      for (it = pmrrSectors.begin(); it != pmrrSectors.end(); ++it)
      {
         string inputSubsectorName = sjdTools::camelCase((*it).subsectorName);
         inputSubsectorNames.insert(inputSubsectorName);
         if (uniqueSubsectors.find(inputSubsectorName) == uniqueSubsectors.end())
         {
            unrepresentedPmrrSubsectors.push_back(*it);
         }
      }
      set<string>::iterator uniqueSubsectorIT;
      for (uniqueSubsectorIT = uniqueSubsectors.begin(); uniqueSubsectorIT != uniqueSubsectors.end(); ++uniqueSubsectorIT)
      {
         if (inputSubsectorNames.find((*uniqueSubsectorIT)) == inputSubsectorNames.end())
         {
            unrepresetnedSubsectors.insert(*uniqueSubsectorIT);
         }
      }
   }


   vector<boost::shared_ptr<ifrsSector>> IFRSEarlyDashboard::getSubsectorRatingsChange(vector<boost::shared_ptr<pmrrSector>> pmrrSectors)
   {
      vector<boost::shared_ptr<ifrsSector>> tmp;

       map<string, vector<boost::shared_ptr<IFRSEarlyWarningCompany>>> companiesBySubsector = groupCompaniesBySubsector();

      return tmp;
   }


   map<string, vector<boost::shared_ptr<IFRSEarlyWarningCompany>>> IFRSEarlyDashboard::groupCompaniesBySubsector()
   {
      vector<boost::shared_ptr<IFRSEarlyWarningCompany>>::iterator startingLocation = companies.begin();
      map<string, vector<boost::shared_ptr<IFRSEarlyWarningCompany>>> companiesBySubsector;
      set<string>::iterator subsectorIT;
      for (subsectorIT = uniqueSubsectors.begin(); subsectorIT != uniqueSubsectors.end(); ++subsectorIT)
      {
         vector<boost::shared_ptr<IFRSEarlyWarningCompany>>::iterator companyIT;
         companyIT = std::partition (startingLocation, companies.end(), 
            boost::bind(is_in_sub_sector, _1, *subsectorIT));

         vector<boost::shared_ptr<IFRSEarlyWarningCompany>> v1(startingLocation, companyIT);
         companiesBySubsector[*subsectorIT] = v1;

         startingLocation = companyIT;
      }
      return companiesBySubsector;
   }

}
#include "IFRSEarlyWarningDashboardObject.h"

namespace sbsaObjects 
{
   /*======================================================================================
   IFRSEarlyWarningCompany

    =======================================================================================*/
   IFRSEarlyWarningDashboard::IFRSEarlyWarningDashboard(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                                         std::vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companies,
                                                         bool permanent) :
      ObjectHandler::LibraryObject<sbsa::IFRSEarlyWarningDashboard>(properties, permanent) 
   {
      std::vector<boost::shared_ptr<sbsa::IFRSEarlyWarningCompany>> sbsaCompanies;
      for (size_t i = 0; i < companies.size(); ++i) 
      {
         boost::shared_ptr<sbsa::IFRSEarlyWarningCompany> c;
         companies[i]->getLibraryObject(c);
         sbsaCompanies.push_back(c);
      }
      libraryObject_ = boost::shared_ptr<sbsa::IFRSEarlyWarningDashboard>(new 
         sbsa::IFRSEarlyWarningDashboard(sbsaCompanies));
    }

    bool IFRSEarlyWarningDashboard::isOK() const
    {
       return libraryObject_->isOK();
    }

   string IFRSEarlyWarningDashboard::getErrorMessages() const
   {
      return libraryObject_->getErrorMessagesAsString();
   }

   // True for sectors, false for subsectors
   std::vector<string> IFRSEarlyWarningDashboard::getUnique(bool sectors)
   {
      set<string> sectorOrSubsectorNames;
      if (sectors)
      {
         sectorOrSubsectorNames = libraryObject_->getUniqueSectors();
      }
      else
      {
         sectorOrSubsectorNames = libraryObject_->getUniqueSubSectors();
      }
      std::vector<string> returnValues = vector<string>(sectorOrSubsectorNames.begin(), sectorOrSubsectorNames.end());
      return returnValues;
   }

   // True to return companies that have data, false for companies without data
   std::vector<string> IFRSEarlyWarningDashboard::getCompanies(bool withData)
   {
      std::vector<boost::shared_ptr<sbsa::IFRSEarlyWarningCompany>> companies;
      if (withData)
      {
         companies = libraryObject_->getCompaniesWithData();
      }
      else
      {
         companies = libraryObject_->getCompaniesWithoutData();
      }
      vector<string> companyNames;
      for (size_t i = 0; i < companies.size(); ++i)
      {
         companyNames.push_back(companies[i]->getCompanyName());
      }
      return companyNames;
   }
}
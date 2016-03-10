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

}
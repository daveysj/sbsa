#include "IFRSEarlyWarningCompanyObject.h"

namespace sbsaObjects 
{
   /*======================================================================================
   IFRSEarlyWarningCompany

    =======================================================================================*/
    IFRSEarlyWarningCompany::IFRSEarlyWarningCompany(
                                           const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                           string companyName, 
                                           string companySector, 
                                           string companySubSector,
                                           bool permanent) : 
        ObjectHandler::LibraryObject<sbsa::IFRSEarlyWarningCompany>(properties, permanent) 
    {
        libraryObject_ = boost::shared_ptr<sbsa::IFRSEarlyWarningCompany>(new
                           sbsa::IFRSEarlyWarningCompany(companyName, companySector, companySubSector));
    }


   IFRSEarlyWarningCompany::IFRSEarlyWarningCompany(
                                           const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                           string companyName, 
                                           string companySector, 
                                           string companySubSector,
                                           double marketCap,
                                           map<Date, double> historicPDs,
                                           bool permanent) : 
        ObjectHandler::LibraryObject<sbsa::IFRSEarlyWarningCompany>(properties, permanent) 
    {
        libraryObject_ = boost::shared_ptr<sbsa::IFRSEarlyWarningCompany>(new
                           sbsa::IFRSEarlyWarningCompany(companyName, companySector, companySubSector));    
    }

   string IFRSEarlyWarningCompany::getCompanySummary()
   {
      return libraryObject_->getCompanyName();
   }

    bool IFRSEarlyWarningCompany::isOK() const
    {
        return libraryObject_->isOK();
    }

    string IFRSEarlyWarningCompany::getErrorMessages() const
    {
        return libraryObject_->getErrorMessagesAsString();
    }

}
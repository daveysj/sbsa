#include "IFRSEarlyWarningCompanyObject.h"

namespace sbsaObjects 
{
   /*======================================================================================
   IFRSEarlyWarningCompany

    =======================================================================================*/
    IFRSEarlyWarningCompany::IFRSEarlyWarningCompany(
                                           const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                           boost::shared_ptr<sbsa::IFRSEarlyWarningCompany> company,
                                           bool permanent) : 
        ObjectHandler::LibraryObject<sbsa::IFRSEarlyWarningCompany>(properties, permanent) 
    {
        libraryObject_ = company;
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
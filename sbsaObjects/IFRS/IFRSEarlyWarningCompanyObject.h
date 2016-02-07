#ifndef SBSA_OBJ_IFRSEarlyWarningCompany
#define SBSA_OBJ_IFRSEarlyWarningCompany

#include <oh/libraryobject.hpp>

#include <sbsa\IFRS\IFRSEarlyWarningCompany.h>


namespace sbsaObjects 
{        
    /*======================================================================================
    Contract

    =======================================================================================*/
    class IFRSEarlyWarningCompany : public ObjectHandler::LibraryObject<sbsa::IFRSEarlyWarningCompany> 
    { 
    public:
        IFRSEarlyWarningCompany(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                boost::shared_ptr<sbsa::IFRSEarlyWarningCompany> company,
                                bool permanent);


        bool isOK() const;
        string getErrorMessages() const; 


    protected: 
        OH_LIB_CTOR(IFRSEarlyWarningCompany, sbsa::IFRSEarlyWarningCompany) 
    };


 
}

#endif

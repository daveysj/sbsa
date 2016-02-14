#ifndef SBSA_OBJ_IFRSEarlyWarningDashboard
#define SBSA_OBJ_IFRSEarlyWarningDashboard

#include <oh/libraryobject.hpp>
#include <oh\ohdefines.hpp>

#include "IFRSEarlyWarningCompanyObject.h"
#include <sbsa\IFRS\IFRSEarlyWarningDashboard.h>


namespace sbsaObjects 
{        
    /*======================================================================================
    IFRSEarlyWarningDashboard

    =======================================================================================*/
    class IFRSEarlyWarningDashboard : public ObjectHandler::LibraryObject<sbsa::IFRSEarlyWarningDashboard> 
    { 
    public:
        IFRSEarlyWarningDashboard(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                  std::vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companies,
                                  bool permanent);


        bool isOK() const;
        string getErrorMessages() const; 


    protected: 
        OH_LIB_CTOR(IFRSEarlyWarningDashboard, sbsa::IFRSEarlyWarningDashboard) 
    };


 
}

#endif

#ifndef SBSA_OBJ_IFRSEarlyWarningCompany
#define SBSA_OBJ_IFRSEarlyWarningCompany

#include <oh/libraryobject.hpp>
#include <oh\ohdefines.hpp>

#include <sbsa\IFRS\IFRSEarlyWarningCompany.h>


namespace sbsaObjects 
{        
    /*======================================================================================
    IFRSEarlyWarningCompany

    =======================================================================================*/
    class IFRSEarlyWarningCompany : public ObjectHandler::LibraryObject<sbsa::IFRSEarlyWarningCompany> 
    { 
    public:
        IFRSEarlyWarningCompany(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                string companyName, 
                                string companySector, 
                                string companySubSector,
                                bool permanent);

        IFRSEarlyWarningCompany(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                string companyName, 
                                string companySector, 
                                string companySubSector,
                                double marketCap,
                                map<Date, double> historicPDs,
                                bool permanent);

        string getCompanySummary();

        bool isOK() const;
        string getErrorMessages() const; 


    protected: 
        OH_LIB_CTOR(IFRSEarlyWarningCompany, sbsa::IFRSEarlyWarningCompany) 
    };


 
}

#endif

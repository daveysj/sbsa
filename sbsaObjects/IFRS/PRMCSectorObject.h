#ifndef SBSA_OBJ_PMRRSector
#define SBSA_OBJ_PMRRSector

#include <oh/libraryobject.hpp>
#include <oh\ohdefines.hpp>

#include <sbsa\IFRS\PRMCSectors.h>


namespace sbsaObjects 
{        
    /*======================================================================================
    PRMCSectors

    =======================================================================================*/
    class PMRRSector : public ObjectHandler::LibraryObject<sbsa::pmrrSector> 
    { 
    public:
        PMRRSector(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                    string sectorName, 
                    string subsectorName, 
                    Date subsectorReviewDate,
                    bool permanent);


    protected: 
        OH_LIB_CTOR(PMRRSector, sbsa::pmrrSector) 
    };
 
}

#endif

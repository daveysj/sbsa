#include "PRMCSectorObject.h"

namespace sbsaObjects 
{
   /*======================================================================================
   PMRRSector

    =======================================================================================*/
   PMRRSector::PMRRSector(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                          string sectorName, 
                          string subsectorName, 
                          Date subsectorReviewDate,
                          bool permanent) :
      ObjectHandler::LibraryObject<sbsa::pmrrSector>(properties, permanent) 
   {
      libraryObject_ = boost::shared_ptr<sbsa::pmrrSector>(new
                           sbsa::pmrrSector());
      libraryObject_->sectorName = sectorName;
      libraryObject_->subsectorName = subsectorName;
      libraryObject_->subsectorReviewDate = subsectorReviewDate;
   }



}
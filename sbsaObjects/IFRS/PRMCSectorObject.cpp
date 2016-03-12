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


   /*======================================================================================
   PMRRSectors

    =======================================================================================*/
   PMRRSectors::PMRRSectors(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                            std::vector<boost::shared_ptr<PMRRSector>> sectors, 
                            bool permanent) :
      ObjectHandler::LibraryObject<sbsa::PMRRSectors>(properties, permanent) 
   {
      vector<sbsa::pmrrSector> allSectors;
      for (size_t i = 0; i < sectors.size(); ++i) 
      {
         boost::shared_ptr<sbsa::pmrrSector> sector;
         sectors[i]->getLibraryObject(sector);
         allSectors.push_back(*sector);
      }

      libraryObject_ = boost::shared_ptr<sbsa::PMRRSectors>(new sbsa::PMRRSectors(allSectors));
   }

}

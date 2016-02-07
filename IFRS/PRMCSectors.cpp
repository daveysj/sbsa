#include "PRMCSectors.h"

namespace sbsa
{
   PMRRSectors::PMRRSectors(vector<boost::shared_ptr<pmrrSector>> allSectorsInput)
   {
      allSectors = allSectorsInput;
   }

   vector<boost::shared_ptr<pmrrSector>> PMRRSectors::getAllSectors()
   {
      return allSectors;
   }
}
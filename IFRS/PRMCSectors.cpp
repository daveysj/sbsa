#include "PRMCSectors.h"

namespace sbsa
{
   PMRRSectors::PMRRSectors()
   {
      allSectors = vector<pmrrSector>();
      allSectorNames = set<string>();
      allSubsectorNames = set<string>();
   }
   
   PMRRSectors::PMRRSectors(vector<pmrrSector> allSectorsInput)
   {
      allSectors = allSectorsInput;
      for (size_t i = 0; i < allSectors.size(); ++i) 
      {
         allSectorNames.insert(allSectors[i].sectorName);
         allSubsectorNames.insert(allSectors[i].subsectorName);
      }
   }

   vector<pmrrSector> PMRRSectors::getAllSectors()
   {
      return allSectors;
   }

   set<string> PMRRSectors::getAllSectorNames()
   {
      return allSectorNames;
   }

   set<string> PMRRSectors::getAllSubsectorNames()
   {
      return allSubsectorNames;
   }
   
}
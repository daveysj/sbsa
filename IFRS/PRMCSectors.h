#ifndef SBSA_PMRRSector
#define SBSA_PMRRSector

#include <vector>
#include <set>

#include <boost\shared_ptr.hpp>

#include <ql\time\date.hpp>


using namespace std;
using namespace QuantLib;

namespace sbsa
{
   class pmrrSector
   {
   public:
      string sectorName;
      string subsectorName;
      Date subsectorReviewDate;
   };

   
   class PMRRSectors
   {
   public:
      PMRRSectors();
      PMRRSectors(std::vector<pmrrSector> allSectors);

      std::vector<pmrrSector> getAllSectors();
      set<string> getAllSectorNames();
      set<string> getAllSubsectorNames();

   private:
      std::vector<pmrrSector> allSectors;
      set<string> allSectorNames;
      set<string> allSubsectorNames;
   };
   
}


#endif

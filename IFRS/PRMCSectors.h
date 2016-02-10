#ifndef SBSA_PMRRSector
#define SBSA_PMRRSector

#include <vector>

#include <boost\shared_ptr.hpp>

#include <ql\time\date.hpp>


using namespace std;
using namespace QuantLib;

namespace sbsa
{
   struct pmrrSector
   {
      string sectorName;
      string subsectorName;
      Date subsectorReviewDate;
   };

   /*
   class PMRRSectors
   {
   public:
      PMRRSectors(vector<boost::shared_ptr<pmrrSector>> allSectors);

      vector<boost::shared_ptr<pmrrSector>> getAllSectors();
      string<string> getAllSectorNames();
      string<string> getAllSubsectorNames();

   private:
      vector<boost::shared_ptr<pmrrSector>> allSectors;
      set<string> allSectorNames;
      set<string> allSubsectorNames;
   };
   */
}


#endif

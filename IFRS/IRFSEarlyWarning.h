#ifndef SBSA_IFRS
#define SBSA_IFRS

using namespace std;
//using namespace QuantLib;
#include <vector>
#include <set>
#include <string>
//#include <cmath>

#include <boost\shared_ptr.hpp>
#include <boost\algorithm\string.hpp>

namespace sbsa
{

   /*======================================================================================
   sbsaObjects::IFRSEarlyWarningDashboard

    =======================================================================================*/
    class IFRSEarlyWarningDashboard
    {
    public:
        IFRSEarlyWarningDashboard(std::vector<string> shareNames, 
                                  std::vector<string> sectors, 
                                  std::vector<double> weightings, 
                                  std::vector<double> basePD,
                                  std::vector<double> currentPD);
        
        static bool checkDimensions(std::vector<string> shareNames, 
                                    std::vector<string> sectors, 
                                    std::vector<double> weightings, 
                                    std::vector<double> basePD,
                                    std::vector<double> currentPD,
                                    string &errorMessage);

        std::vector<string> getSectors();

        void getChangeInRatings(std::vector<string> &headings, 
                                std::vector<string> &sectorNames, 
                                std::vector<std::vector<double>> &data);

//        std::vector<pair<string, double>> getChangeInRatings();

    private:
        void camelCase(string &inpputString);

        std::vector<string> shareNames;
        std::vector<string> sectors;
        std::vector<double> weightings;
        std::vector<double> basePD;
        std::vector<double> currentPD;
    };
}

#endif

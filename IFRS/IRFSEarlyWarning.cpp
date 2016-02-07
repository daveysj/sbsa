#include "IRFSEarlyWarning.h"


namespace sbsa
{
    /*======================================================================================
    sbsaObjects::IFRSEarlyWarningDashboard

    =======================================================================================*/
    IFRSEarlyWarningDashboard::IFRSEarlyWarningDashboard(std::vector<string> shareNamesInput, 
                                                         std::vector<string> sectorsInput, 
                                                         std::vector<double> weightingsInput, 
                                                         std::vector<double> basePDInput,
                                                         std::vector<double> currentPDInput) 
    {
        shareNames = shareNamesInput;
        sectors = sectorsInput;
        weightings = weightingsInput;
        basePD = basePDInput;
        currentPD = currentPDInput;
    }

    bool IFRSEarlyWarningDashboard::checkDimensions(std::vector<string> shareNames, 
                                                    std::vector<string> sectors, 
                                                    std::vector<double> weightings, 
                                                    std::vector<double> basePD,
                                                    std::vector<double> currentPD,
                                                    string &errorMessage)

    {
        errorMessage = "No error";
        if ((shareNames.size() == 0) || 
            (sectors.size() == 0) || 
            (weightings.size() == 0) ||
            (basePD.size() == 0) ||
            (currentPD.size() == 0))
        {
            errorMessage = "At least one input std::vector is empty";        
            return false;
        }

        if ((sectors.size() != weightings.size()) ||
            (sectors.size() != shareNames.size()) ||
            (sectors.size() != basePD.size()) ||
            (sectors.size() != currentPD.size()))
        {
            errorMessage = "Input std::vectors do not have the same dimnsion";        
            return false;
        }
        return true;
    }

    std::vector<string> IFRSEarlyWarningDashboard::getSectors()
    {
        for (size_t i = 0; i < sectors.size(); ++i)
        {
            boost::to_lower(sectors[i]);
        }
        set<string> uniqueSectors = set<string>(sectors.begin(), sectors.end());

        std::vector<string> sectorNames = std::vector<string>(uniqueSectors.begin(),
                                                              uniqueSectors.end());
        //for (size_t i = 0; i < sectorNames.size(); ++i)
        //{
        //    camelCase(sectorNames[i]);
        //}

        return sectorNames;
    }

    void IFRSEarlyWarningDashboard::getChangeInRatings(std::vector<string> &headings, 
                                                       std::vector<string> &sectorNames,
                                                       std::vector<std::vector<double>> &data)
    {        
        std::vector<string> uniqueSectors = IFRSEarlyWarningDashboard::getSectors(); 
        std::vector<int> sectorComposition = std::vector<int>(uniqueSectors.size(), 0); 

        headings = std::vector<string>();
        sectorNames = std::vector<string>();

        headings.push_back("Num Shares");
        headings.push_back("Base PD");
        headings.push_back("Current PD");
        headings.push_back("Relative Change in PD");
        headings.push_back("Notch Change");
        
        //std::vector<pair<string, double>> pdChange = std::vector<pair<string, double>>();
        data = std::vector<std::vector<double>>();
        std::vector<double> basePDxWeight = std::vector<double>(uniqueSectors.size(), 0);
        std::vector<double> currentPDxWeight = std::vector<double>(uniqueSectors.size(), 0);
        std::vector<double> weight = std::vector<double>(uniqueSectors.size(), 0);
        std::vector<double> changeInPD = std::vector<double>(uniqueSectors.size(), 0);
        for (size_t i = 0; i < uniqueSectors.size(); ++i)
        {
            for (size_t j = 0; j < sectors.size(); ++ j)
            {
                if (uniqueSectors[i].compare(sectors[j])==0)
                {
                    basePDxWeight[i] += weightings[j] * basePD[j];
                    currentPDxWeight[i] += weightings[j] * currentPD[j];
                    weight[i] += weightings[j];
                    sectorComposition[i] += 1;
                }                         
            }
        }
        for (size_t i = 0; i < uniqueSectors.size(); ++i)
        {
            if (weight[i] <= 1e-14)
            {
                changeInPD[i] = 0;
            }
            else 
            {
                changeInPD[i] = (currentPDxWeight[i] / basePDxWeight[i]);
            }

            string s = uniqueSectors[i];
            camelCase(s);
            sectorNames.push_back(s);
            std::vector<double> dataRow = std::vector<double>();
            dataRow.push_back(sectorComposition[i]);
            dataRow.push_back(basePDxWeight[i] / weight[i]);
            dataRow.push_back(currentPDxWeight[i] / weight[i]);
            dataRow.push_back(changeInPD[i]);
            double ratingsChange = log(changeInPD[i]) / log(2.0); // log base 2
            ratingsChange *= -2; // 2 notches = double or half PD
            dataRow.push_back(ratingsChange);
            data.push_back(dataRow);
        }
        return;
    }

    void IFRSEarlyWarningDashboard::camelCase(string &s)
    {
        bool cap = true;
        for(unsigned int i = 0; i < s.length(); i++)
        {
            if (isalpha(s[i]) && cap == true)
            {
                s[i] = toupper(s[i]);
                cap = false;
            }
            else if (isspace(s[i]))
            {  
                cap = true;
            }
        }
    }


}
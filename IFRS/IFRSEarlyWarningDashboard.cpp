#include "IFRSEarlyWarningDashboard.h"


namespace sbsa
{
   bool is_in_sub_sector(const boost::shared_ptr<IFRSEarlyWarningCompany> company, const std::string &wanted)
   {
      return company->getSubSector().compare(wanted) == 0;
   }


   IFRSEarlyWarningDashboard::IFRSEarlyWarningDashboard(vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companiesInput)
   {
      errorTracking = boost::shared_ptr<sjdTools::ErrorTracking>(
         new sjdTools::ErrorTracking("IFRSEarlyWarningDashboard"));
      resetErrorMessages();

      companies = vector<boost::shared_ptr<IFRSEarlyWarningCompany>>();
      companiesWithoutData  = vector<boost::shared_ptr<IFRSEarlyWarningCompany>>();
      for (size_t i = 0; i < companiesInput.size(); ++i)
      {
         if (companiesInput[i]->isOK()) 
         {
            companies.push_back(companiesInput[i]);
            uniqueSectors.insert(companiesInput[i]->getSector());
            uniqueSubsectors.insert(companiesInput[i]->getSubSector());
         }
         else 
         {
             companiesWithoutData.push_back(companiesInput[i]);
         }
      }
      inputCompanies = companiesInput.size();
      usableCompanies = companies.size();


   }

   void IFRSEarlyWarningDashboard::resetErrorMessages()
   {
       errorTracking->clearErrorMessages();
   }

   bool IFRSEarlyWarningDashboard::isOK()
   {
       return !errorTracking->getHasErrors();
   }

   vector<string> IFRSEarlyWarningDashboard::getErrorMessages() const 
   {
       return errorTracking->getErrorMessages();
   }

   string IFRSEarlyWarningDashboard::getErrorMessagesAsString() const 
   {
       return errorTracking->getErrorMessagesAsString();
   }

   int IFRSEarlyWarningDashboard::getNumberOfInputCompanies()
   {
      return inputCompanies; 
   }
   
   int IFRSEarlyWarningDashboard::getNumberOfUsableCompanies()
   {
      return usableCompanies;
   }

   set<string> IFRSEarlyWarningDashboard::getUniqueSectors()
   {
      return uniqueSectors;
   }

   set<string> IFRSEarlyWarningDashboard::getUniqueSubSectors()
   {
      return uniqueSubsectors;
   }

   vector<boost::shared_ptr<IFRSEarlyWarningCompany>> IFRSEarlyWarningDashboard::getCompaniesWithoutData()
   {
      return companiesWithoutData;
   }

   vector<boost::shared_ptr<IFRSEarlyWarningCompany>> IFRSEarlyWarningDashboard::getCompaniesWithData()
   {
      return companies;
   }

   void IFRSEarlyWarningDashboard::checkAllSubSectorsExist(vector<pmrrSector> pmrrSectors, 
                                                           vector<pmrrSector> &unrepresentedPmrrSubsectors,
                                                           set<string> &unrepresetnedSubsectors)
   {
      unrepresentedPmrrSubsectors = vector<pmrrSector>();
      unrepresetnedSubsectors = set<string>();

      set<string> inputSubsectorNames;
      vector<pmrrSector>::iterator it;
      for (it = pmrrSectors.begin(); it != pmrrSectors.end(); ++it)
      {
         string inputSubsectorName = sjdTools::camelCase((*it).subsectorName);
         inputSubsectorNames.insert(inputSubsectorName);
         if (uniqueSubsectors.find(inputSubsectorName) == uniqueSubsectors.end())
         {
            unrepresentedPmrrSubsectors.push_back(*it);
         }
      }
      set<string>::iterator uniqueSubsectorIT;
      for (uniqueSubsectorIT = uniqueSubsectors.begin(); uniqueSubsectorIT != uniqueSubsectors.end(); ++uniqueSubsectorIT)
      {
         if (inputSubsectorNames.find((*uniqueSubsectorIT)) == inputSubsectorNames.end())
         {
            unrepresetnedSubsectors.insert(*uniqueSubsectorIT);
         }
      }
   }

   void IFRSEarlyWarningDashboard::checkAllSubSectorsExist(PMRRSectors pmrrSectors, 
                                                           PMRRSectors &unrepresentedPmrrSubsectors,
                                                           set<string> &unrepresetnedSubsectors)
   {
      vector<pmrrSector> unrepresentedPmrrSubsectorsVector = vector<pmrrSector>();
      vector<pmrrSector> pmrrSectorsVector = pmrrSectors.getAllSectors();
      checkAllSubSectorsExist(pmrrSectorsVector, unrepresentedPmrrSubsectorsVector, unrepresetnedSubsectors);
      unrepresentedPmrrSubsectors = PMRRSectors(unrepresentedPmrrSubsectorsVector);
   }


   vector<ifrsSector> IFRSEarlyWarningDashboard::getSubsectorRatingsChange(vector<pmrrSector> pmrrSectors, Date toDate)
   {
      vector<ifrsSector> sectorAnalysis;
      map<string, vector<boost::shared_ptr<IFRSEarlyWarningCompany>>> groupedCompanies = groupCompaniesBySubsector();
      vector<pmrrSector>::iterator it;
      for (it = pmrrSectors.begin(); it != pmrrSectors.end(); ++it)
      {
         ifrsSector outputSector;
         outputSector.sectorName = (*it).sectorName;
         outputSector.subsectorName = (*it).subsectorName;
         outputSector.subsectorReviewDate = (*it).subsectorReviewDate;
         outputSector.todaysDate = toDate;
         vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companuesInSubsector = groupedCompanies.find((*it).subsectorName)->second;
         outputSector.numberOfShares = getCompaniesWithoutMissingData(companuesInSubsector, (*it).subsectorReviewDate, toDate).size();
         double basePD, currentPD, changeInPD;
         getChangeInPD(companuesInSubsector, (*it).subsectorReviewDate, toDate, basePD, currentPD, changeInPD);
         outputSector.basePD = basePD;
         outputSector.currentPD = currentPD;
         outputSector.ratingNotchChange = convertChangeInPDToChangeInRatings(changeInPD);
         sectorAnalysis.push_back(outputSector);
      }
      return sectorAnalysis;
   }


   map<string, vector<boost::shared_ptr<IFRSEarlyWarningCompany>>> IFRSEarlyWarningDashboard::groupCompaniesBySubsector()
   {
      vector<boost::shared_ptr<IFRSEarlyWarningCompany>>::iterator startingLocation = companies.begin();
      map<string, vector<boost::shared_ptr<IFRSEarlyWarningCompany>>> companiesBySubsector;
      set<string>::iterator subsectorIT;
      for (subsectorIT = uniqueSubsectors.begin(); subsectorIT != uniqueSubsectors.end(); ++subsectorIT)
      {
         vector<boost::shared_ptr<IFRSEarlyWarningCompany>>::iterator companyIT;
         companyIT = std::partition (startingLocation, companies.end(), 
            boost::bind(is_in_sub_sector, _1, *subsectorIT));

         vector<boost::shared_ptr<IFRSEarlyWarningCompany>> v1(startingLocation, companyIT);
         companiesBySubsector[*subsectorIT] = v1;

         startingLocation = companyIT;
      }
      return companiesBySubsector;
   }


   vector<boost::shared_ptr<IFRSEarlyWarningCompany>> IFRSEarlyWarningDashboard::getCompaniesWithoutMissingData(vector<boost::shared_ptr<IFRSEarlyWarningCompany>> groupedCompanies, 
                                                                                                         Date fromDate, 
                                                                                                         Date toDate)
   {
      vector<boost::shared_ptr<IFRSEarlyWarningCompany>> companiesWithoutMissingData = vector<boost::shared_ptr<IFRSEarlyWarningCompany>>();

      vector<boost::shared_ptr<IFRSEarlyWarningCompany>>::iterator it;
      for (it = groupedCompanies.begin(); it != groupedCompanies.end(); ++it)
      {
         if ((*it)->isOK() &&  ((*it)->containsData(toDate)) && ((*it)->containsData(fromDate)))
         {
            companiesWithoutMissingData.push_back(*it);
         }
      }
      return companiesWithoutMissingData;
   }

   void IFRSEarlyWarningDashboard::getChangeInPD(vector<boost::shared_ptr<IFRSEarlyWarningCompany>> groupedCompanies, 
                                          Date fromDate, 
                                          Date toDate,
                                          double &basePD,
                                          double &currentPD,
                                          double &changeInPD)
   {
      basePD = 0;
      currentPD = 0;
      changeInPD = 0;

      double totalWeigth = 0; 

      vector<boost::shared_ptr<IFRSEarlyWarningCompany>>::iterator it;
      for (it = groupedCompanies.begin(); it != groupedCompanies.end(); ++it)
      {
         if ((*it)->isOK() &&  ((*it)->containsData(toDate)) && ((*it)->containsData(fromDate)))
         {
            double weight = (*it)->getMarketCap();
            totalWeigth += weight;
            double pd1 = weight * (*it)->getDefaultProbability(fromDate);
            basePD += pd1;
            double pd2 = weight * (*it)->getDefaultProbability(toDate);
            currentPD += pd2;
            double pdMove = pd2 - pd1;
            changeInPD += pdMove;
         }
      }
      if (totalWeigth > 1e-14)
      {
         basePD /= totalWeigth;
         currentPD /= totalWeigth;
         changeInPD /= totalWeigth;
      }
      else 
      {
         basePD = 0;
         currentPD = 0;
         changeInPD = 0;
      }
   }

   double IFRSEarlyWarningDashboard::convertChangeInPDToChangeInRatings(double pd)
   {
      if ((pd < 0) || (pd > 1))
      {
         return numeric_limits<double>::quiet_NaN();
      }
      double ratingsChange = log(pd) / log(2.0); // log base 2
      ratingsChange *= -2; // 2 notches = double or half PD
      return ratingsChange;
   }
}

#include <qlo/qladdindefines.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#include <sbsa\IFRS\IRFSEarlyWarning.h>
#include <sbsa\sbsaXLL\ObjectCommon.h>

#include <Tools\vectorOfVectorsToOper.h>
#include <Tools\vo_GenericUnimplemented.h>
#include <sbsa\sbsaObjects\IFRS\IFRSEarlyWarningCompanyObject.h>

#include <ohxl\convert_oper.hpp>

#include <iomanip> 
#include <algorithm>


/*======================================================================================
Create an instance of the object sjdObjects::SimpleMargin and return its ID
=======================================================================================*/
DLLEXPORT char *createIFRSCompany(char *objectID,
                                  char *companyNameChar,
                                  char *companySectorChar,
                                  char *companySubSectorChar,
                                  double *marketCap,
                                  OPER *historicPDDates,
                                  OPER *historicPDs,
                                  bool *permanent) 
{

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;
    static char ret[XL_MAX_STR_LEN];
    try 
    {
        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>
            (new ObjectHandler::FunctionCall("createIFRSCompany"));

        std::string companyName(companyNameChar);

        std::string companySector(companySectorChar);

        std::string companySubsector(companySubSectorChar);
           
        std::vector<QuantLib::Date> pdDates =
            ObjectHandler::operToVector<QuantLib::Date>(*historicPDDates, "PDDates");

        std::vector<double> pds =
            ObjectHandler::operToVector<double>(*historicPDs, "ProbabilityOfDefault");

        // Strip the Excel cell update counter suffix from Object IDs        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(objectID);
        // Construct the Value Object
        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new sjdObjects::ValueObjects::GenericUnimplementedValueObject(ObjectIdStrip,false));
        // Construct the Object

        sbsaObjects::IFRSEarlyWarningCompany *company;
        if (pds.size() != pdDates.size())
        {
           // create and return 
           company = new sbsaObjects::IFRSEarlyWarningCompany(valueObject,
                                                              companyName, 
                                                              companySector, 
                                                              companySubsector,
                                                              *permanent);
        }
        else 
        {
           map<Date, double> historicPDs;
           for (size_t i = 0; i < pdDates.size(); ++i)
           {
              historicPDs[pdDates[i]] = pds[i];
           }

           company = new sbsaObjects::IFRSEarlyWarningCompany(valueObject,
                                                              companyName, 
                                                              companySector, 
                                                              companySubsector,
                                                              *marketCap,
                                                              historicPDs,
                                                              *permanent);

        }

        boost::shared_ptr<ObjectHandler::Object> object(company);
        if (!company->isOK()) 
        {
            ObjectHandler::stringToChar(company->getErrorMessages(), ret);
        }
        else 
        {
            // Store the Object in the Repository
            std::string returnValue =
                ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, true);
            ObjectHandler::stringToChar(returnValue, ret);
        }
        return ret;
    } 
    SBSA_XLL_CATCH_STRING()
}


DLLEXPORT OPER *ifrsPDMigration(OPER *shareNames,
                                OPER *sectors,
                                OPER *weightings,
                                OPER *basePD,
                                OPER *currentPD) 
{
    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;
    static XLOPER returnValue;
    try 
    {
        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>
            (new ObjectHandler::FunctionCall("ifrsPDMigration"));

        // convert input datatypes to C++ datatypes

        std::vector<std::string> shareNamesCpp =
            ObjectHandler::operToVector<std::string>(*shareNames, "ShareNames");

        std::vector<std::string> sectorsCpp =
            ObjectHandler::operToVector<std::string>(*sectors, "Sectors");

        std::vector<string> weightingsStringCpp =
            ObjectHandler::operToVector<string>(*weightings, "WeighthingsString");
        std::vector<double> weightingsCpp = std::vector<double>(weightingsStringCpp.size());

        std::vector<string> basePDCppString =
            ObjectHandler::operToVector<string>(*basePD, "basePDString");
        std::vector<double> basePDCpp = std::vector<double>(weightingsStringCpp.size());

        std::vector<string> currentPDCppString =
            ObjectHandler::operToVector<string>(*currentPD, "currentPDString");
        std::vector<double> currentPDCpp = std::vector<double>(weightingsStringCpp.size());

        if ((weightingsStringCpp.size() != shareNamesCpp.size()) ||
            (weightingsStringCpp.size() != basePDCppString.size()) ||
            (weightingsStringCpp.size() != currentPDCppString.size()))
        {
            ObjectHandler::scalarToOper("Not all input vectors are of the same size", returnValue);      
            return &returnValue;
        }
        bool inputIncomplete = false;
        std::vector<string> errorDescription;
        for (size_t i = 0; i < weightingsStringCpp.size(); ++i)
        {
            double value;
            try
            {
                value = boost::lexical_cast<double>(weightingsStringCpp[i]);
            }
            catch (boost::bad_lexical_cast const&)
            {
                inputIncomplete = true;
                errorDescription.push_back("Weighting error: " + shareNamesCpp[i]);
                value = 0;
            }
            weightingsCpp[i] = value;

            try
            {
                value = boost::lexical_cast<double>(basePDCppString[i]);
            }
            catch (boost::bad_lexical_cast const&)
            {
                inputIncomplete = true;
                errorDescription.push_back("Base PD error: " + shareNamesCpp[i]);
                value = 0;
            }
            basePDCpp[i] = value;

            try
            {
                value = boost::lexical_cast<double>(currentPDCppString[i]);
            }
            catch (boost::bad_lexical_cast const&)
            {
                inputIncomplete = true;
                errorDescription.push_back("Current PD error: " + shareNamesCpp[i]);
                value = 0;
            }
            currentPDCpp[i] = value;
        }
        if (inputIncomplete) 
        {
            ObjectHandler::scalarToOper(errorDescription, returnValue);        
            return &returnValue;
        }


        string errorMessage = "";
        if (!sbsa::IFRSEarlyWarningDashboard::checkDimensions(shareNamesCpp,
                                                                     sectorsCpp,
                                                                     weightingsCpp,
                                                                     basePDCpp,
                                                                     currentPDCpp,
                                                                     errorMessage))
        {
            ObjectHandler::scalarToOper(errorMessage, returnValue);        
            return &returnValue;
        }

        // Strip the Excel cell update counter suffix from Object IDs
        
        //std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(objectID);

        sbsa::IFRSEarlyWarningDashboard ifrs(shareNamesCpp, 
                                                    sectorsCpp, 
                                                    weightingsCpp, 
                                                    basePDCpp, 
                                                    currentPDCpp);

        std::vector<string> headings;
        std::vector<string> sectorNames;
        std::vector<std::vector<double>> data;

        ifrs.getChangeInRatings(headings, sectorNames, data);
        //std::vector<pair<string, double>> ratingsChange = ifrs.getChangeInRatings();

        //std::vector<string> rowHeadings, columnHeadings;
        //std::vector<std::vector<double> > data;
        //std::vector<double> dataRow;
        //for (size_t i = 0; i < ratingsChange.size(); ++i) 
        //{
        //    rowHeadings.push_back(ratingsChange[i].first);
        //    dataRow = std::vector<double>(1);
        //    dataRow[0] = ratingsChange[i].second;
        //    data.push_back(dataRow);
        //}

        sjd::tableToOper(headings, sectorNames, data, returnValue);
        return &returnValue;
    } 
    SBSA_XLL_CATCH_OPER()
}


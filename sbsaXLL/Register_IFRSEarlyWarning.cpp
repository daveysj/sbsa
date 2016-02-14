#include <xlsdk/xlsdkdefines.hpp>


void registerIRFS9EarlyWarning(const XLOPER &xDll) 
{
        Excel(xlfRegister, 0, 15, &xDll,
            TempStrNoSize("\x0F""ifrsPDMigration"),
            TempStrNoSize("\x07""PPPPPP#"),
            TempStrNoSize("\x0F""ifrsPDMigration"),
            TempStrNoSize("\x2D""CompanyName,Sector,Weighting,BasePD,CurrentPD"),
            TempStrNoSize("\x01""1"),                   // function type (0 = hidden function, 1 = worksheet function, 2 = command macro)
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    // shortcut text (command macros only)            
            TempStrNoSize("\x00"""),                    // path to help file
            TempStrNoSize("\x3C""Takes data by share and returns sector PD migration analysis"),
            TempStrNoSize("\x22""Share Name (used to report errors)"),  
            TempStrNoSize("\x0B""Sector Data"),  
            TempStrNoSize("\x0F""Weighting (USD)"),
            TempStrNoSize("\x1F""Starting Probability of default"),
            TempStrNoSize("\x1E""Current Probability of default"));

        Excel(xlfRegister, 0, 17, &xDll,
            TempStrNoSize("\x11""createIFRSCompany"),
            TempStrNoSize("\x09""CCCCBPPL#"),
            TempStrNoSize("\x11""createIFRSCompany"),
            TempStrNoSize("\x3B""Name,Sector,Subsector,MktCap,PDDates,PDs,Permanent"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x35""Constructs a company with default probability history"),
            TempStrNoSize("\x28""Company Name. This will be the object ID"),
            TempStrNoSize("\x0E""Company Sector"),
            TempStrNoSize("\x11""Company Subsector"),
            TempStrNoSize("\x10""Market Cap (USD)"),
            TempStrNoSize("\x30""Dates on which there is default probability data"),
            TempStrNoSize("\x2A""Default Probability Data"),
            TempStrNoSize("\x1D""object permanent/nonpermanent"));

}

void unregisterIRFS9EarlyWarning(const XLOPER &xDll) 
{
    XLOPER xlRegID;
    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 15, &xDll,
            TempStrNoSize("\x0F""ifrsPDMigration"),
            TempStrNoSize("\x07""PPPPPP#"),
            TempStrNoSize("\x0F""ifrsPDMigration"),
            TempStrNoSize("\x2D""CompanyName,Sector,Weighting,BasePD,CurrentPD"),
            TempStrNoSize("\x01""1"),                   // function type (0 = hidden function, 1 = worksheet function, 2 = command macro)
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    // shortcut text (command macros only)            
            TempStrNoSize("\x00"""),                    // path to help file
            TempStrNoSize("\x3C""Takes data by share and returns sector PD migration analysis"),
            TempStrNoSize("\x22""Share Name (used to report errors)"),  
            TempStrNoSize("\x0B""Sector Data"),  
            TempStrNoSize("\x0F""Weighting (USD)"),
            TempStrNoSize("\x1F""Starting Probability of default"),
            TempStrNoSize("\x1E""Current Probability of default"));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""ifrsPDMigration"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            TempStrNoSize("\x11""createIFRSCompany"),
            TempStrNoSize("\x09""CCCCBPPL#"),
            TempStrNoSize("\x11""createIFRSCompany"),
            TempStrNoSize("\x3B""Name,Sector,Subsector,MktCap,PDDates,PDs,Permanent"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x35""Constructs a company with default probability history"),
            TempStrNoSize("\x28""Company Name. This will be the object ID"),
            TempStrNoSize("\x0E""Company Sector"),
            TempStrNoSize("\x11""Company Subsector"),
            TempStrNoSize("\x10""Market Cap (USD)"),
            TempStrNoSize("\x30""Dates on which there is default probability data"),
            TempStrNoSize("\x2A""Default Probability Data"),
            TempStrNoSize("\x1D""object permanent/nonpermanent"));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""createIFRSCompany"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);
}

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

        Excel(xlfRegister, 0, 14, &xDll,
            TempStrNoSize("\x13""createIFRSDashboard"),
            TempStrNoSize("\x06""CCPPL#"),
            TempStrNoSize("\x13""createIFRSDashboard"),
            TempStrNoSize("\x24""ObjectID,Companies,Trigger,Permanent"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x30""Constructs a Dashboard Object and returns its ID"),
            TempStrNoSize("\x09""Object ID"),
            TempStrNoSize("\x38""List of all the companies that are part of the dashboard"),
            TempStrNoSize("\x07""Trigger"),
            TempStrNoSize("\x1D""object permanent/nonpermanent"));

        Excel(xlfRegister, 0, 12, &xDll,
            TempStrNoSize("\x1B""getDashboardSectorSubSector"),
            TempStrNoSize("\x04""PCL#"),
            TempStrNoSize("\x1B""getDashboardSectorSubSector"),
            TempStrNoSize("\x0A""DashboardID,SectorData"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x35""Returns a list of Sectors / Subsectors that have Data"),
            TempStrNoSize("\x0C""Dashboard ID"),
            TempStrNoSize("\x3A""Return (TRUE = Sectors) (FALSE = Subsectors) default data"));

        Excel(xlfRegister, 0, 12, &xDll,
            TempStrNoSize("\x15""getDashboardCompanies"),
            TempStrNoSize("\x04""PCL#"),
            TempStrNoSize("\x15""getDashboardCompanies"),
            TempStrNoSize("\x14""DashboardID,WithData"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x45""Returns a list of company names from a dashboard with or without data"),
            TempStrNoSize("\x0C""Dashboard ID"),
            TempStrNoSize("\x3D""Return companies (TRUE = With) (FALSE = Without) default data"));


        Excel(xlfRegister, 0, 14, &xDll,
            TempStrNoSize("\x10""createPMRRSector"),
            TempStrNoSize("\x06""CCCPL#"),
            TempStrNoSize("\x10""createPMRRSector"),
            TempStrNoSize("\x2D""SectorName,SubSectorName,ReviewDate,Permanent"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x4A""Constructs a PMRR Sector and returns it ID (defined by the subsector name)"),
            TempStrNoSize("\x0B""Sector Name"),
            TempStrNoSize("\x3C""SubSector Name (used as the ObjectID so this must be unique)"),
            TempStrNoSize("\x15""Subsector Review Date"),
            TempStrNoSize("\x1D""object permanent/nonpermanent"));

        Excel(xlfRegister, 0, 13, &xDll,
            TempStrNoSize("\x11""createPMRRSectors"),
            TempStrNoSize("\x05""CCPL#"),
            TempStrNoSize("\x11""createPMRRSectors"),
            TempStrNoSize("\x1E""ObjectID,PMRRSectors,Permanent"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x36""Creates a Collection of PMRR Sectors and returns it ID"),
            TempStrNoSize("\x09""Object ID"),
            TempStrNoSize("\x20""A list of the individual sectors"),
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

        Excel(xlfRegister, 0, 14, &xDll,
            TempStrNoSize("\x13""createIFRSDashboard"),
            TempStrNoSize("\x06""CCPPL#"),
            TempStrNoSize("\x13""createIFRSDashboard"),
            TempStrNoSize("\x24""ObjectID,Companies,Trigger,Permanent"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x30""Constructs a Dashboard Object and returns its ID"),
            TempStrNoSize("\x09""Object ID"),
            TempStrNoSize("\x38""List of all the companies that are part of the dashboard"),
            TempStrNoSize("\x07""Trigger"),
            TempStrNoSize("\x1D""object permanent/nonpermanent"));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""createIFRSDashboard"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            TempStrNoSize("\x1B""getDashboardSectorSubSector"),
            TempStrNoSize("\x04""PCL#"),
            TempStrNoSize("\x1B""getDashboardSectorSubSector"),
            TempStrNoSize("\x0A""DashboardID,SectorData"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x35""Returns a list of Sectors / Subsectors that have Data"),
            TempStrNoSize("\x0C""Dashboard ID"),
            TempStrNoSize("\x3A""Return (TRUE = Sectors) (FALSE = Subsectors) default data"));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""getDashboardSectorSubSector"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            TempStrNoSize("\x15""getDashboardCompanies"),
            TempStrNoSize("\x04""PCL#"),
            TempStrNoSize("\x15""getDashboardCompanies"),
            TempStrNoSize("\x14""DashboardID,WithData"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x45""Returns a list of company names from a dashboard with or without data"),
            TempStrNoSize("\x0C""Dashboard ID"),
            TempStrNoSize("\x3D""Return companies (TRUE = With) (FALSE = Without) default data"));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""getDashboardCompanies"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);


        Excel(xlfRegister, 0, 14, &xDll,
            TempStrNoSize("\x10""createPMRRSector"),
            TempStrNoSize("\x06""CCCPL#"),
            TempStrNoSize("\x10""createPMRRSector"),
            TempStrNoSize("\x2D""SectorName,SubSectorName,ReviewDate,Permanent"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x4A""Constructs a PMRR Sector and returns it ID (defined by the subsector name)"),
            TempStrNoSize("\x0B""Sector Name"),
            TempStrNoSize("\x3C""SubSector Name (used as the ObjectID so this must be unique)"),
            TempStrNoSize("\x15""Subsector Review Date"),
            TempStrNoSize("\x1D""object permanent/nonpermanent"));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""createPMRRSector"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);


        Excel(xlfRegister, 0, 13, &xDll,
            TempStrNoSize("\x11""createPMRRSectors"),
            TempStrNoSize("\x05""CCPL#"),
            TempStrNoSize("\x11""createPMRRSectors"),
            TempStrNoSize("\x1E""ObjectID,PMRRSectors,Permanent"),
            TempStrNoSize("\x01""1"),                   
            TempStrNoSize("\x04""PMRR"),
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x00"""),                    
            TempStrNoSize("\x36""Creates a Collection of PMRR Sectors and returns it ID"),
            TempStrNoSize("\x09""Object ID"),
            TempStrNoSize("\x20""A list of the individual sectors"),
            TempStrNoSize("\x1D""object permanent/nonpermanent"));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""createPMRRSectors"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);
}

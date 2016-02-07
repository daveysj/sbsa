#include "Register_SBSA.h"

// SBSA Objects

extern void registerIRFS9EarlyWarning(const XLOPER&);

extern void unregisterIRFS9EarlyWarning(const XLOPER&);

void registerSBSAFunctions(const XLOPER &xDll)
{
    registerIRFS9EarlyWarning(xDll);
}

void unregisterSBSAFunctions(const XLOPER &xDll)
{
    unregisterIRFS9EarlyWarning(xDll);
}

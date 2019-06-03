#include "battery_eq_circuit_pascal5_single_shot_stack_capi_host.h"
static battery_eq_circuit_pascal5_single_shot_stack_host_DataMapInfo_T root;
static int initialized = 0;
__declspec( dllexport ) rtwCAPI_ModelMappingInfo *getRootMappingInfo()
{
    if (initialized == 0) {
        initialized = 1;
        battery_eq_circuit_pascal5_single_shot_stack_host_InitializeDataMapInfo(&(root), "battery_eq_circuit_pascal5_single_shot_stack");
    }
    return &root.mmi;
}

rtwCAPI_ModelMappingInfo *mexFunction() {return(getRootMappingInfo());}

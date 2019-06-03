#include "__cf_battery_eq_circuit_pascal5_single_shot_stack.h"
#include "rt_logging_mmi.h"
#include "battery_eq_circuit_pascal5_single_shot_stack_capi.h"
#include <math.h>
#include "battery_eq_circuit_pascal5_single_shot_stack.h"
#include "battery_eq_circuit_pascal5_single_shot_stack_private.h"
#include "battery_eq_circuit_pascal5_single_shot_stack_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; extern boolean_T
gblExtModeStartPktReceived ; void raccelForceExtModeShutdown ( ) { if ( !
gblExtModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 1 , & stopRequested ) ; }
rtExtModeShutdown ( 1 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 2 ; const char_T
* gbl_raccel_Version = "9.3 (R2019a) 23-Nov-2018" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const char * gblSlvrJacPatternFileName =
 "slprj\\raccel\\battery_eq_circuit_pascal5_single_shot_stack\\battery_eq_circuit_pascal5_single_shot_stack_Jpattern.mat"
; const int_T gblNumRootInportBlks = 0 ; const int_T gblNumModelInputs = 0 ;
extern rtInportTUtable * gblInportTUtables ; extern const char *
gblInportFileName ; extern void * gblAperiodicPartitionHitTimes ; const int_T
gblInportDataTypeIdx [ ] = { - 1 } ; const int_T gblInportDims [ ] = { - 1 }
; const int_T gblInportComplex [ ] = { - 1 } ; const int_T
gblInportInterpoFlag [ ] = { - 1 } ; const int_T gblInportContinuous [ ] = {
- 1 } ; int_T enableFcnCallFlag [ ] = { 1 , 1 } ; const char *
raccelLoadInputsAndAperiodicHitTimes ( const char * inportFileName , int *
matFileFormat ) { return rt_RapidReadInportsMatFile ( inportFileName ,
matFileFormat , 1 ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
B rtB ; DW rtDW ; static SimStruct model_S ; SimStruct * const rtS = &
model_S ; void MdlInitialize ( void ) { { int32_T i , j ; real_T * Ds = (
real_T * ) rtDW . lpqqjlpxt1 . DS ; for ( i = 0 ; i < 4 ; i ++ ) { for ( j =
0 ; j < 4 ; j ++ ) Ds [ i * 4 + j ] = ( rtP . StateSpace_DS_param [ i + j * 4
] ) ; } { int_T * switch_status = ( int_T * ) rtDW . lpqqjlpxt1 .
SWITCH_STATUS ; int_T * gState = ( int_T * ) rtDW . lpqqjlpxt1 . G_STATE ;
real_T * yswitch = ( real_T * ) rtDW . lpqqjlpxt1 . Y_SWITCH ; int_T *
switchTypes = ( int_T * ) rtDW . lpqqjlpxt1 . SWITCH_TYPES ; int_T * idxOutSw
= ( int_T * ) rtDW . lpqqjlpxt1 . IDX_OUT_SW ; int_T * switch_status_init = (
int_T * ) rtDW . lpqqjlpxt1 . SWITCH_STATUS_INIT ; switch_status [ 0 ] = 0 ;
switch_status_init [ 0 ] = 0 ; gState [ 0 ] = ( int_T ) 0.0 ; yswitch [ 0 ] =
1 / 0.1 ; switchTypes [ 0 ] = ( int_T ) 1.0 ; idxOutSw [ 0 ] = ( ( int_T )
0.0 ) - 1 ; switch_status [ 1 ] = 0 ; switch_status_init [ 1 ] = 0 ; gState [
1 ] = ( int_T ) 0.0 ; yswitch [ 1 ] = 1 / 0.1 ; switchTypes [ 1 ] = ( int_T )
1.0 ; idxOutSw [ 1 ] = ( ( int_T ) 0.0 ) - 1 ; switch_status [ 2 ] = 0 ;
switch_status_init [ 2 ] = 0 ; gState [ 2 ] = ( int_T ) 0.0 ; yswitch [ 2 ] =
1 / 0.01 ; switchTypes [ 2 ] = ( int_T ) 3.0 ; idxOutSw [ 2 ] = ( ( int_T )
0.0 ) - 1 ; switch_status [ 3 ] = 0 ; switch_status_init [ 3 ] = 0 ; gState [
3 ] = ( int_T ) 0.0 ; yswitch [ 3 ] = 1 / 0.01 ; switchTypes [ 3 ] = ( int_T
) 3.0 ; idxOutSw [ 3 ] = ( ( int_T ) 0.0 ) - 1 ; } } rtDW . lwfztydmov = rtP
. itinit1_InitialCondition ; rtDW . kpa0qz1w2m = rtP .
Currentfilter_InitialStates ; rtDW . dk1lpgs41d = ( 1.0 - rtP . Battery_SOC /
100.0 ) * 0.51699999999999868 * 0.96711798839458663 * 3600.0 ; rtDW .
oh13f4t51u = 1U ; rtDW . kmqrnxxbow = 2 ; rtDW . lnyxns4prr =
muDoubleScalarExp ( ( 1.0 - rtP . Battery_SOC / 100.0 ) * -
122.12389380530972 * 0.51699999999999868 ) * 0.60462693404467927 ; rtDW .
j3ah0j5uha = rtP . Memory2_InitialCondition ; rtDW . jnwgqfjczs = rtP .
itinit1_InitialCondition_kl3ucy1541 ; rtDW . iq0yvshwbl = rtP .
Currentfilter_InitialStates_nr2e02qeiq ; rtDW . lztbr3et3t = ( 1.0 - rtP .
Battery1_SOC / 100.0 ) * 0.51699999999999868 * 0.96711798839458663 * 3600.0 ;
rtDW . itp5tejlgk = 1U ; rtDW . f2pl5hhy0a = 2 ; rtDW . nb1buv1zor =
muDoubleScalarExp ( ( 1.0 - rtP . Battery1_SOC / 100.0 ) * -
122.12389380530972 * 0.51699999999999868 ) * 0.60462693404467927 ; rtDW .
ad3mgyfzte = rtP . Memory2_InitialCondition_pf3pych4fa ; rtDW . aircger2rx =
rtP . itinit1_InitialCondition_cih32wawzb ; rtDW . oq5hmifhxo = rtP .
Currentfilter_InitialStates_kut2jdkaed ; rtDW . maze5hu4ab = ( 1.0 - rtP .
Battery2_SOC / 100.0 ) * 0.51699999999999868 * 0.96711798839458663 * 3600.0 ;
rtDW . d23tl2d2xe = 1U ; rtDW . f2mbtmfzg2 = 2 ; rtDW . fb5x1hmdio =
muDoubleScalarExp ( ( 1.0 - rtP . Battery2_SOC / 100.0 ) * -
122.12389380530972 * 0.51699999999999868 ) * 0.60462693404467927 ; rtDW .
ihbczgg1ch = rtP . Memory2_InitialCondition_pxnsyfial5 ; { int32_T i , j ;
real_T * As = ( real_T * ) rtDW . g5a0yy0hef . AS ; real_T * Bs = ( real_T *
) rtDW . g5a0yy0hef . BS ; real_T * Cs = ( real_T * ) rtDW . g5a0yy0hef . CS
; real_T * Ds = ( real_T * ) rtDW . g5a0yy0hef . DS ; real_T * X0 = ( real_T
* ) & rtDW . bmlwssomru [ 0 ] ; for ( i = 0 ; i < 48 ; i ++ ) { X0 [ i ] = (
rtP . StateSpace_X0_param [ i ] ) ; } for ( i = 0 ; i < 48 ; i ++ ) { for ( j
= 0 ; j < 48 ; j ++ ) As [ i * 48 + j ] = ( rtP . StateSpace_AS_param [ i + j
* 48 ] ) ; for ( j = 0 ; j < 4 ; j ++ ) Bs [ i * 4 + j ] = ( rtP .
StateSpace_BS_param [ i + j * 48 ] ) ; } for ( i = 0 ; i < 200 ; i ++ ) { for
( j = 0 ; j < 48 ; j ++ ) Cs [ i * 48 + j ] = ( rtP . StateSpace_CS_param [ i
+ j * 200 ] ) ; } for ( i = 0 ; i < 200 ; i ++ ) { for ( j = 0 ; j < 4 ; j ++
) Ds [ i * 4 + j ] = ( rtP . StateSpace_DS_param_j0m4mfy5zk [ i + j * 200 ] )
; } } { int32_T i , j ; real_T * Ds = ( real_T * ) rtDW . kosaktmuhw . DS ;
for ( i = 0 ; i < 6 ; i ++ ) { for ( j = 0 ; j < 4 ; j ++ ) Ds [ i * 4 + j ]
= ( rtP . StateSpace_DS_param_iushkyjw3b [ i + j * 6 ] ) ; } { int_T *
switch_status = ( int_T * ) rtDW . kosaktmuhw . SWITCH_STATUS ; int_T *
gState = ( int_T * ) rtDW . kosaktmuhw . G_STATE ; real_T * yswitch = (
real_T * ) rtDW . kosaktmuhw . Y_SWITCH ; int_T * switchTypes = ( int_T * )
rtDW . kosaktmuhw . SWITCH_TYPES ; int_T * idxOutSw = ( int_T * ) rtDW .
kosaktmuhw . IDX_OUT_SW ; int_T * switch_status_init = ( int_T * ) rtDW .
kosaktmuhw . SWITCH_STATUS_INIT ; switch_status [ 0 ] = 0 ;
switch_status_init [ 0 ] = 0 ; gState [ 0 ] = ( int_T ) 0.0 ; yswitch [ 0 ] =
1 / 0.1 ; switchTypes [ 0 ] = ( int_T ) 1.0 ; idxOutSw [ 0 ] = ( ( int_T )
0.0 ) - 1 ; switch_status [ 1 ] = 0 ; switch_status_init [ 1 ] = 0 ; gState [
1 ] = ( int_T ) 0.0 ; yswitch [ 1 ] = 1 / 0.1 ; switchTypes [ 1 ] = ( int_T )
1.0 ; idxOutSw [ 1 ] = ( ( int_T ) 0.0 ) - 1 ; switch_status [ 2 ] = 0 ;
switch_status_init [ 2 ] = 0 ; gState [ 2 ] = ( int_T ) 0.0 ; yswitch [ 2 ] =
1 / 0.01 ; switchTypes [ 2 ] = ( int_T ) 3.0 ; idxOutSw [ 2 ] = ( ( int_T )
0.0 ) - 1 ; switch_status [ 3 ] = 0 ; switch_status_init [ 3 ] = 0 ; gState [
3 ] = ( int_T ) 0.0 ; yswitch [ 3 ] = 1 / 0.01 ; switchTypes [ 3 ] = ( int_T
) 3.0 ; idxOutSw [ 3 ] = ( ( int_T ) 0.0 ) - 1 ; } } rtDW . jwpobdvxh3 = rtP
. itinit1_InitialCondition_jvi22guyny ; rtDW . l4l5iifhga = rtP .
Currentfilter_InitialStates_mpd5odciik ; rtDW . nuc12zx3mo = ( 1.0 - rtP .
Battery_SOC_doariqu25f / 100.0 ) * 1.0339999999999974 * 0.96711798839458663 *
3600.0 ; rtDW . k0yugcv43d = 1U ; rtDW . oufwnzwkdu = 2 ; rtDW . bdlz3yfllc =
muDoubleScalarExp ( ( 1.0 - rtP . Battery_SOC_doariqu25f / 100.0 ) * -
61.06194690265486 * 1.0339999999999974 ) * 0.60462693404467927 ; rtDW .
jz4s1v251o = rtP . Memory2_InitialCondition_np5byfbcx3 ; { int32_T i , j ;
real_T * Ds = ( real_T * ) rtDW . lhqp2i1wv4 . DS ; for ( i = 0 ; i < 7 ; i
++ ) { for ( j = 0 ; j < 5 ; j ++ ) Ds [ i * 5 + j ] = ( rtP .
StateSpace_DS_param_gcibvrcmds [ i + j * 7 ] ) ; } { int_T * switch_status =
( int_T * ) rtDW . lhqp2i1wv4 . SWITCH_STATUS ; int_T * gState = ( int_T * )
rtDW . lhqp2i1wv4 . G_STATE ; real_T * yswitch = ( real_T * ) rtDW .
lhqp2i1wv4 . Y_SWITCH ; int_T * switchTypes = ( int_T * ) rtDW . lhqp2i1wv4 .
SWITCH_TYPES ; int_T * idxOutSw = ( int_T * ) rtDW . lhqp2i1wv4 . IDX_OUT_SW
; int_T * switch_status_init = ( int_T * ) rtDW . lhqp2i1wv4 .
SWITCH_STATUS_INIT ; switch_status [ 0 ] = 0 ; switch_status_init [ 0 ] = 0 ;
gState [ 0 ] = ( int_T ) 0.0 ; yswitch [ 0 ] = 1 / 0.1 ; switchTypes [ 0 ] =
( int_T ) 1.0 ; idxOutSw [ 0 ] = ( ( int_T ) 0.0 ) - 1 ; switch_status [ 1 ]
= 0 ; switch_status_init [ 1 ] = 0 ; gState [ 1 ] = ( int_T ) 0.0 ; yswitch [
1 ] = 1 / 0.1 ; switchTypes [ 1 ] = ( int_T ) 1.0 ; idxOutSw [ 1 ] = ( (
int_T ) 0.0 ) - 1 ; switch_status [ 2 ] = 0 ; switch_status_init [ 2 ] = 0 ;
gState [ 2 ] = ( int_T ) 0.0 ; yswitch [ 2 ] = 1 / 0.01 ; switchTypes [ 2 ] =
( int_T ) 3.0 ; idxOutSw [ 2 ] = ( ( int_T ) 0.0 ) - 1 ; switch_status [ 3 ]
= 0 ; switch_status_init [ 3 ] = 0 ; gState [ 3 ] = ( int_T ) 0.0 ; yswitch [
3 ] = 1 / 0.01 ; switchTypes [ 3 ] = ( int_T ) 3.0 ; idxOutSw [ 3 ] = ( (
int_T ) 0.0 ) - 1 ; } } rtDW . mip1wd2oyv = rtP .
itinit1_InitialCondition_ogfkm4kbb3 ; rtDW . nqdr1b40o2 = rtP .
Currentfilter_InitialStates_jsum3iw4ku ; rtDW . ogqyiifq2n = ( 1.0 - rtP .
Battery_SOC_ijowiaqvxc / 100.0 ) * 1.0339999999999974 * 0.96711798839458663 *
3600.0 ; rtDW . fpix2rdml1 = 1U ; rtDW . lrgpgfqgzz = 2 ; rtDW . jf2kk54ldn =
muDoubleScalarExp ( ( 1.0 - rtP . Battery_SOC_ijowiaqvxc / 100.0 ) * -
61.06194690265486 * 1.0339999999999974 ) * 0.60462693404467927 ; rtDW .
o035fkrhgg = rtP . Memory2_InitialCondition_eimmvbkaw2 ; { int32_T i , j ;
real_T * Ds = ( real_T * ) rtDW . c0rfzt21pv . DS ; for ( i = 0 ; i < 7 ; i
++ ) { for ( j = 0 ; j < 5 ; j ++ ) Ds [ i * 5 + j ] = ( rtP .
StateSpace_DS_param_g5puuiyo4c [ i + j * 7 ] ) ; } { int_T * switch_status =
( int_T * ) rtDW . c0rfzt21pv . SWITCH_STATUS ; int_T * gState = ( int_T * )
rtDW . c0rfzt21pv . G_STATE ; real_T * yswitch = ( real_T * ) rtDW .
c0rfzt21pv . Y_SWITCH ; int_T * switchTypes = ( int_T * ) rtDW . c0rfzt21pv .
SWITCH_TYPES ; int_T * idxOutSw = ( int_T * ) rtDW . c0rfzt21pv . IDX_OUT_SW
; int_T * switch_status_init = ( int_T * ) rtDW . c0rfzt21pv .
SWITCH_STATUS_INIT ; switch_status [ 0 ] = 0 ; switch_status_init [ 0 ] = 0 ;
gState [ 0 ] = ( int_T ) 0.0 ; yswitch [ 0 ] = 1 / 0.1 ; switchTypes [ 0 ] =
( int_T ) 1.0 ; idxOutSw [ 0 ] = ( ( int_T ) 0.0 ) - 1 ; switch_status [ 1 ]
= 0 ; switch_status_init [ 1 ] = 0 ; gState [ 1 ] = ( int_T ) 0.0 ; yswitch [
1 ] = 1 / 0.1 ; switchTypes [ 1 ] = ( int_T ) 1.0 ; idxOutSw [ 1 ] = ( (
int_T ) 0.0 ) - 1 ; switch_status [ 2 ] = 0 ; switch_status_init [ 2 ] = 0 ;
gState [ 2 ] = ( int_T ) 0.0 ; yswitch [ 2 ] = 1 / 0.01 ; switchTypes [ 2 ] =
( int_T ) 3.0 ; idxOutSw [ 2 ] = ( ( int_T ) 0.0 ) - 1 ; switch_status [ 3 ]
= 0 ; switch_status_init [ 3 ] = 0 ; gState [ 3 ] = ( int_T ) 0.0 ; yswitch [
3 ] = 1 / 0.01 ; switchTypes [ 3 ] = ( int_T ) 3.0 ; idxOutSw [ 3 ] = ( (
int_T ) 0.0 ) - 1 ; } } rtDW . kvdcvco01e = rtP .
DiscretePIDController_InitialConditionForIntegrator ; rtDW . bo3uxetgss = rtP
. RateLimiter_IC ; rtDW . evlwxs2e1f = rtP . RateLimiter_IC_eua3brkunu ; rtDW
. lqmt5s4eon = rtP . RateLimiter_IC_payuy03iq3 ; } void MdlStart ( void ) { {
void * * slioCatalogueAddr = rt_slioCatalogueAddr ( ) ; void * r2 = ( NULL )
; void * * pOSigstreamManagerAddr = ( NULL ) ; const int maxErrorBufferSize =
16384 ; char errMsgCreatingOSigstreamManager [ 16384 ] ; bool
errorCreatingOSigstreamManager = false ; const char *
errorAddingR2SharedResource = ( NULL ) ; * slioCatalogueAddr =
rtwGetNewSlioCatalogue ( rt_GetMatSigLogSelectorFileName ( ) ) ;
errorAddingR2SharedResource = rtwAddR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) , 1 ) ; if (
errorAddingR2SharedResource != ( NULL ) ) { rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = ( NULL ) ; ssSetErrorStatus ( rtS
, errorAddingR2SharedResource ) ; return ; } r2 = rtwGetR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ) ;
pOSigstreamManagerAddr = rt_GetOSigstreamManagerAddr ( ) ;
errorCreatingOSigstreamManager = rtwOSigstreamManagerCreateInstance (
rt_GetMatSigLogSelectorFileName ( ) , r2 , pOSigstreamManagerAddr ,
errMsgCreatingOSigstreamManager , maxErrorBufferSize ) ; if (
errorCreatingOSigstreamManager ) { * pOSigstreamManagerAddr = ( NULL ) ;
ssSetErrorStatus ( rtS , errMsgCreatingOSigstreamManager ) ; return ; } } {
bool externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( ) ; rtwISigstreamManagerGetInputIsInDatasetFormat (
pISigstreamManager , & externalInputIsInDatasetFormat ) ; if (
externalInputIsInDatasetFormat ) { } } { int_T dimensions [ 1 ] = { 1 } ;
rtDW . ddhevcuw0f . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "v_cc" , SS_DOUBLE , 0 , 0 , 0 , 1 , 1 , dimensions , NO_LOGVALDIMS , (
NULL ) , ( NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . ddhevcuw0f . LoggedData
== ( NULL ) ) return ; } { int_T dimensions [ 1 ] = { 48 } ; rtDW .
eyvapocerz . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "r_leak" , SS_DOUBLE , 0 , 0 , 0 , 48 , 1 , dimensions , NO_LOGVALDIMS
, ( NULL ) , ( NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . eyvapocerz .
LoggedData == ( NULL ) ) return ; } { int_T dimensions [ 1 ] = { 1 } ; rtDW .
px5gx0ovdj . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "i_cc" , SS_DOUBLE , 0 , 0 , 0 , 1 , 1 , dimensions , NO_LOGVALDIMS , (
NULL ) , ( NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . px5gx0ovdj . LoggedData
== ( NULL ) ) return ; } { int_T dimensions [ 1 ] = { 48 } ; rtDW .
lueewoojur . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "v_r" , SS_DOUBLE , 0 , 0 , 0 , 48 , 1 , dimensions , NO_LOGVALDIMS , (
NULL ) , ( NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . lueewoojur . LoggedData
== ( NULL ) ) return ; } { int_T dimensions [ 1 ] = { 48 } ; rtDW .
ofqo4whqqs . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "v_cap" , SS_DOUBLE , 0 , 0 , 0 , 48 , 1 , dimensions , NO_LOGVALDIMS ,
( NULL ) , ( NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . ofqo4whqqs .
LoggedData == ( NULL ) ) return ; } { int_T dimensions [ 1 ] = { 48 } ; rtDW
. gylheu2quv . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "i_leak" , SS_DOUBLE , 0 , 0 , 0 , 48 , 1 , dimensions , NO_LOGVALDIMS
, ( NULL ) , ( NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . gylheu2quv .
LoggedData == ( NULL ) ) return ; } { int_T dimensions [ 1 ] = { 48 } ; rtDW
. if3oedzqbn . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "p_chg" , SS_DOUBLE , 0 , 0 , 0 , 48 , 1 , dimensions , NO_LOGVALDIMS ,
( NULL ) , ( NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . if3oedzqbn .
LoggedData == ( NULL ) ) return ; } { int_T dimensions [ 1 ] = { 48 } ; rtDW
. lnb3lesuo3 . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "p_leak" , SS_DOUBLE , 0 , 0 , 0 , 48 , 1 , dimensions , NO_LOGVALDIMS
, ( NULL ) , ( NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . lnb3lesuo3 .
LoggedData == ( NULL ) ) return ; } { int_T dimensions [ 1 ] = { 48 } ; rtDW
. jydkx4dopc . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "i" , SS_DOUBLE , 0 , 0 , 0 , 48 , 1 , dimensions , NO_LOGVALDIMS , (
NULL ) , ( NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . jydkx4dopc . LoggedData
== ( NULL ) ) return ; } { int_T dimensions [ 1 ] = { 48 } ; rtDW .
f4ppq3cqy3 . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "c" , SS_DOUBLE , 0 , 0 , 0 , 48 , 1 , dimensions , NO_LOGVALDIMS , (
NULL ) , ( NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . f4ppq3cqy3 . LoggedData
== ( NULL ) ) return ; } { int_T dimensions [ 1 ] = { 48 } ; rtDW .
g1bsp2ezz4 . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "r" , SS_DOUBLE , 0 , 0 , 0 , 48 , 1 , dimensions , NO_LOGVALDIMS , (
NULL ) , ( NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . g1bsp2ezz4 . LoggedData
== ( NULL ) ) return ; } { int_T dimensions [ 1 ] = { 3 } ; rtDW . eosjvmtbk2
. LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS
) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "bSoc" ,
SS_DOUBLE , 0 , 0 , 0 , 3 , 1 , dimensions , NO_LOGVALDIMS , ( NULL ) , (
NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . eosjvmtbk2 . LoggedData == ( NULL )
) return ; } { int_T dimensions [ 1 ] = { 3 } ; rtDW . cuayv55s4x .
LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS )
, ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "i_safety" ,
SS_DOUBLE , 0 , 0 , 0 , 3 , 1 , dimensions , NO_LOGVALDIMS , ( NULL ) , (
NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . cuayv55s4x . LoggedData == ( NULL )
) return ; } { int_T dimensions [ 1 ] = { 1 } ; rtDW . jecmukiw0b .
LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS )
, ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "t" ,
SS_DOUBLE , 0 , 0 , 0 , 1 , 1 , dimensions , NO_LOGVALDIMS , ( NULL ) , (
NULL ) , 0 , 1 , 10.0 , 1 ) ; if ( rtDW . jecmukiw0b . LoggedData == ( NULL )
) return ; } { rtDW . lpqqjlpxt1 . DS = ( real_T * ) calloc ( 4 * 4 , sizeof
( real_T ) ) ; rtDW . lpqqjlpxt1 . DX_COL = ( real_T * ) calloc ( 4 , sizeof
( real_T ) ) ; rtDW . lpqqjlpxt1 . TMP2 = ( real_T * ) calloc ( 4 , sizeof (
real_T ) ) ; rtDW . lpqqjlpxt1 . SWITCH_STATUS = ( int_T * ) calloc ( 4 ,
sizeof ( int_T ) ) ; rtDW . lpqqjlpxt1 . SW_CHG = ( int_T * ) calloc ( 4 ,
sizeof ( int_T ) ) ; rtDW . lpqqjlpxt1 . G_STATE = ( int_T * ) calloc ( 4 ,
sizeof ( int_T ) ) ; rtDW . lpqqjlpxt1 . Y_SWITCH = ( real_T * ) calloc ( 4 ,
sizeof ( real_T ) ) ; rtDW . lpqqjlpxt1 . SWITCH_TYPES = ( int_T * ) calloc (
4 , sizeof ( int_T ) ) ; rtDW . lpqqjlpxt1 . IDX_OUT_SW = ( int_T * ) calloc
( 4 , sizeof ( int_T ) ) ; rtDW . lpqqjlpxt1 . SWITCH_STATUS_INIT = ( int_T *
) calloc ( 4 , sizeof ( int_T ) ) ; rtDW . lpqqjlpxt1 . USWLAST = ( real_T *
) calloc ( 4 , sizeof ( real_T ) ) ; } { rtDW . g5a0yy0hef . AS = ( real_T *
) calloc ( 48 * 48 , sizeof ( real_T ) ) ; rtDW . g5a0yy0hef . BS = ( real_T
* ) calloc ( 48 * 4 , sizeof ( real_T ) ) ; rtDW . g5a0yy0hef . CS = ( real_T
* ) calloc ( 200 * 48 , sizeof ( real_T ) ) ; rtDW . g5a0yy0hef . DS = (
real_T * ) calloc ( 200 * 4 , sizeof ( real_T ) ) ; rtDW . g5a0yy0hef .
DX_COL = ( real_T * ) calloc ( 200 , sizeof ( real_T ) ) ; rtDW . g5a0yy0hef
. TMP2 = ( real_T * ) calloc ( 4 , sizeof ( real_T ) ) ; rtDW . g5a0yy0hef .
BD_COL = ( real_T * ) calloc ( 48 , sizeof ( real_T ) ) ; rtDW . g5a0yy0hef .
TMP1 = ( real_T * ) calloc ( 48 , sizeof ( real_T ) ) ; rtDW . g5a0yy0hef .
XTMP = ( real_T * ) calloc ( 48 , sizeof ( real_T ) ) ; } { rtDW . kosaktmuhw
. DS = ( real_T * ) calloc ( 6 * 4 , sizeof ( real_T ) ) ; rtDW . kosaktmuhw
. DX_COL = ( real_T * ) calloc ( 6 , sizeof ( real_T ) ) ; rtDW . kosaktmuhw
. TMP2 = ( real_T * ) calloc ( 4 , sizeof ( real_T ) ) ; rtDW . kosaktmuhw .
SWITCH_STATUS = ( int_T * ) calloc ( 4 , sizeof ( int_T ) ) ; rtDW .
kosaktmuhw . SW_CHG = ( int_T * ) calloc ( 4 , sizeof ( int_T ) ) ; rtDW .
kosaktmuhw . G_STATE = ( int_T * ) calloc ( 4 , sizeof ( int_T ) ) ; rtDW .
kosaktmuhw . Y_SWITCH = ( real_T * ) calloc ( 4 , sizeof ( real_T ) ) ; rtDW
. kosaktmuhw . SWITCH_TYPES = ( int_T * ) calloc ( 4 , sizeof ( int_T ) ) ;
rtDW . kosaktmuhw . IDX_OUT_SW = ( int_T * ) calloc ( 4 , sizeof ( int_T ) )
; rtDW . kosaktmuhw . SWITCH_STATUS_INIT = ( int_T * ) calloc ( 4 , sizeof (
int_T ) ) ; rtDW . kosaktmuhw . USWLAST = ( real_T * ) calloc ( 4 , sizeof (
real_T ) ) ; } { rtDW . lhqp2i1wv4 . DS = ( real_T * ) calloc ( 7 * 5 ,
sizeof ( real_T ) ) ; rtDW . lhqp2i1wv4 . DX_COL = ( real_T * ) calloc ( 7 ,
sizeof ( real_T ) ) ; rtDW . lhqp2i1wv4 . TMP2 = ( real_T * ) calloc ( 5 ,
sizeof ( real_T ) ) ; rtDW . lhqp2i1wv4 . SWITCH_STATUS = ( int_T * ) calloc
( 4 , sizeof ( int_T ) ) ; rtDW . lhqp2i1wv4 . SW_CHG = ( int_T * ) calloc (
4 , sizeof ( int_T ) ) ; rtDW . lhqp2i1wv4 . G_STATE = ( int_T * ) calloc ( 4
, sizeof ( int_T ) ) ; rtDW . lhqp2i1wv4 . Y_SWITCH = ( real_T * ) calloc ( 4
, sizeof ( real_T ) ) ; rtDW . lhqp2i1wv4 . SWITCH_TYPES = ( int_T * ) calloc
( 4 , sizeof ( int_T ) ) ; rtDW . lhqp2i1wv4 . IDX_OUT_SW = ( int_T * )
calloc ( 4 , sizeof ( int_T ) ) ; rtDW . lhqp2i1wv4 . SWITCH_STATUS_INIT = (
int_T * ) calloc ( 4 , sizeof ( int_T ) ) ; rtDW . lhqp2i1wv4 . USWLAST = (
real_T * ) calloc ( 4 , sizeof ( real_T ) ) ; } { rtDW . c0rfzt21pv . DS = (
real_T * ) calloc ( 7 * 5 , sizeof ( real_T ) ) ; rtDW . c0rfzt21pv . DX_COL
= ( real_T * ) calloc ( 7 , sizeof ( real_T ) ) ; rtDW . c0rfzt21pv . TMP2 =
( real_T * ) calloc ( 5 , sizeof ( real_T ) ) ; rtDW . c0rfzt21pv .
SWITCH_STATUS = ( int_T * ) calloc ( 4 , sizeof ( int_T ) ) ; rtDW .
c0rfzt21pv . SW_CHG = ( int_T * ) calloc ( 4 , sizeof ( int_T ) ) ; rtDW .
c0rfzt21pv . G_STATE = ( int_T * ) calloc ( 4 , sizeof ( int_T ) ) ; rtDW .
c0rfzt21pv . Y_SWITCH = ( real_T * ) calloc ( 4 , sizeof ( real_T ) ) ; rtDW
. c0rfzt21pv . SWITCH_TYPES = ( int_T * ) calloc ( 4 , sizeof ( int_T ) ) ;
rtDW . c0rfzt21pv . IDX_OUT_SW = ( int_T * ) calloc ( 4 , sizeof ( int_T ) )
; rtDW . c0rfzt21pv . SWITCH_STATUS_INIT = ( int_T * ) calloc ( 4 , sizeof (
int_T ) ) ; rtDW . c0rfzt21pv . USWLAST = ( real_T * ) calloc ( 4 , sizeof (
real_T ) ) ; } MdlInitialize ( ) ; } void MdlOutputs ( int_T tid ) { real_T
kbrlz2zmlx ; real_T n40x4vvcy0 ; real_T hnubxhm4oh ; real_T inm34i5hw5 ;
real_T n4vvs0yp2i ; real_T pi01aggk5s ; real_T d3t2ofntt1 ; real_T ewm2wjscso
; { real_T accum ; int_T * switch_status = ( int_T * ) rtDW . lpqqjlpxt1 .
SWITCH_STATUS ; int_T * switch_status_init = ( int_T * ) rtDW . lpqqjlpxt1 .
SWITCH_STATUS_INIT ; int_T * SwitchChange = ( int_T * ) rtDW . lpqqjlpxt1 .
SW_CHG ; int_T * gState = ( int_T * ) rtDW . lpqqjlpxt1 . G_STATE ; real_T *
yswitch = ( real_T * ) rtDW . lpqqjlpxt1 . Y_SWITCH ; int_T * switchTypes = (
int_T * ) rtDW . lpqqjlpxt1 . SWITCH_TYPES ; int_T * idxOutSw = ( int_T * )
rtDW . lpqqjlpxt1 . IDX_OUT_SW ; real_T * DxCol = ( real_T * ) rtDW .
lpqqjlpxt1 . DX_COL ; real_T * tmp2 = ( real_T * ) rtDW . lpqqjlpxt1 . TMP2 ;
real_T * uswlast = ( real_T * ) rtDW . lpqqjlpxt1 . USWLAST ; int_T newState
; int_T swChanged = 0 ; int loopsToDo = 20 ; real_T temp ; memcpy (
switch_status_init , switch_status , 4 * sizeof ( int_T ) ) ; memcpy (
uswlast , & rtB . adontzi2bo [ 0 ] , 4 * sizeof ( real_T ) ) ; do { if (
loopsToDo == 1 ) { swChanged = 0 ; { int_T i1 ; for ( i1 = 0 ; i1 < 4 ; i1 ++
) { swChanged = ( ( SwitchChange [ i1 ] = switch_status_init [ i1 ] -
switch_status [ i1 ] ) != 0 ) ? 1 : swChanged ; switch_status [ i1 ] =
switch_status_init [ i1 ] ; } } } else { real_T * Ds = ( real_T * ) rtDW .
lpqqjlpxt1 . DS ; accum = 0.0 ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 0 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 1 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 3 ] ; rtB . adontzi2bo [ 0 ] = accum ; accum = 0.0 ;
accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value [ 0 ] ; accum += * ( Ds ++
) * rtP . SwitchCurrents_Value [ 1 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 3 ] ; rtB . adontzi2bo [ 1 ] = accum ; accum = 0.0 ;
accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value [ 0 ] ; accum += * ( Ds ++
) * rtP . SwitchCurrents_Value [ 1 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 3 ] ; rtB . adontzi2bo [ 2 ] = accum ; accum = 0.0 ;
accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value [ 0 ] ; accum += * ( Ds ++
) * rtP . SwitchCurrents_Value [ 1 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 3 ] ; rtB . adontzi2bo [ 3 ] = accum ; swChanged = 0 ;
newState = gState [ 0 ] > 0 ? 1 : 0 ; swChanged = ( ( SwitchChange [ 0 ] =
newState - switch_status [ 0 ] ) != 0 ) ? 1 : swChanged ; switch_status [ 0 ]
= newState ; newState = gState [ 1 ] > 0 ? 1 : 0 ; swChanged = ( (
SwitchChange [ 1 ] = newState - switch_status [ 1 ] ) != 0 ) ? 1 : swChanged
; switch_status [ 1 ] = newState ; newState = rtB . adontzi2bo [ 2 ] > 0.0 ?
1 : ( ( rtB . adontzi2bo [ 2 ] < 0.0 ) ? 0 : switch_status [ 2 ] ) ;
swChanged = ( ( SwitchChange [ 2 ] = newState - switch_status [ 2 ] ) != 0 )
? 1 : swChanged ; switch_status [ 2 ] = newState ; newState = rtB .
adontzi2bo [ 3 ] > 0.0 ? 1 : ( ( rtB . adontzi2bo [ 3 ] < 0.0 ) ? 0 :
switch_status [ 3 ] ) ; swChanged = ( ( SwitchChange [ 3 ] = newState -
switch_status [ 3 ] ) != 0 ) ? 1 : swChanged ; switch_status [ 3 ] = newState
; } if ( swChanged ) { real_T * Ds = ( real_T * ) rtDW . lpqqjlpxt1 . DS ;
real_T a1 ; { int_T i1 ; for ( i1 = 0 ; i1 < 4 ; i1 ++ ) { if ( SwitchChange
[ i1 ] != 0 ) { a1 = yswitch [ i1 ] * SwitchChange [ i1 ] ; temp = 1 / ( 1 -
Ds [ i1 * 5 ] * a1 ) ; DxCol [ 0 ] = Ds [ 0 + i1 ] * temp * a1 ; DxCol [ 1 ]
= Ds [ 4 + i1 ] * temp * a1 ; DxCol [ 2 ] = Ds [ 8 + i1 ] * temp * a1 ; DxCol
[ 3 ] = Ds [ 12 + i1 ] * temp * a1 ; DxCol [ i1 ] = temp ; memcpy ( tmp2 , &
Ds [ i1 * 4 ] , 4 * sizeof ( real_T ) ) ; memset ( & Ds [ i1 * 4 ] , '\0' , 4
* sizeof ( real_T ) ) ; a1 = DxCol [ 0 ] ; Ds [ 0 + 0 ] += a1 * tmp2 [ 0 ] ;
Ds [ 0 + 1 ] += a1 * tmp2 [ 1 ] ; Ds [ 0 + 2 ] += a1 * tmp2 [ 2 ] ; Ds [ 0 +
3 ] += a1 * tmp2 [ 3 ] ; a1 = DxCol [ 1 ] ; Ds [ 4 + 0 ] += a1 * tmp2 [ 0 ] ;
Ds [ 4 + 1 ] += a1 * tmp2 [ 1 ] ; Ds [ 4 + 2 ] += a1 * tmp2 [ 2 ] ; Ds [ 4 +
3 ] += a1 * tmp2 [ 3 ] ; a1 = DxCol [ 2 ] ; Ds [ 8 + 0 ] += a1 * tmp2 [ 0 ] ;
Ds [ 8 + 1 ] += a1 * tmp2 [ 1 ] ; Ds [ 8 + 2 ] += a1 * tmp2 [ 2 ] ; Ds [ 8 +
3 ] += a1 * tmp2 [ 3 ] ; a1 = DxCol [ 3 ] ; Ds [ 12 + 0 ] += a1 * tmp2 [ 0 ]
; Ds [ 12 + 1 ] += a1 * tmp2 [ 1 ] ; Ds [ 12 + 2 ] += a1 * tmp2 [ 2 ] ; Ds [
12 + 3 ] += a1 * tmp2 [ 3 ] ; } } } } } while ( swChanged > 0 && -- loopsToDo
> 0 ) ; if ( loopsToDo == 0 ) { real_T * Ds = ( real_T * ) rtDW . lpqqjlpxt1
. DS ; accum = 0.0 ; accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value [ 0 ]
; accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value [ 1 ] ; accum += * ( Ds
++ ) * rtP . SwitchCurrents_Value [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 3 ] ; rtB . adontzi2bo [ 0 ] = accum ; accum = 0.0 ;
accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value [ 0 ] ; accum += * ( Ds ++
) * rtP . SwitchCurrents_Value [ 1 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 3 ] ; rtB . adontzi2bo [ 1 ] = accum ; accum = 0.0 ;
accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value [ 0 ] ; accum += * ( Ds ++
) * rtP . SwitchCurrents_Value [ 1 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 3 ] ; rtB . adontzi2bo [ 2 ] = accum ; accum = 0.0 ;
accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value [ 0 ] ; accum += * ( Ds ++
) * rtP . SwitchCurrents_Value [ 1 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value [ 3 ] ; rtB . adontzi2bo [ 3 ] = accum ; } rtB .
nz5y5utmro [ 0 ] = ( real_T ) switch_status [ 0 ] ; rtB . nz5y5utmro [ 1 ] =
( real_T ) switch_status [ 1 ] ; rtB . nz5y5utmro [ 2 ] = ( real_T )
switch_status [ 2 ] ; rtB . nz5y5utmro [ 3 ] = ( real_T ) switch_status [ 3 ]
; } kbrlz2zmlx = rtP . R2_Gain * rtDW . lwfztydmov ; n40x4vvcy0 = rtP .
Currentfilter_NumCoef * rtDW . kpa0qz1w2m ; rtB . jum15pqqg1 = ( n40x4vvcy0 >
rtP . Constant_Value_kbhmnmnkmn ) ; if ( rtDW . oh13f4t51u != 0 ) { rtDW .
ksp1zkwcj2 = rtDW . dk1lpgs41d ; if ( rtDW . ksp1zkwcj2 >= rtP .
inti_UpperSat ) { rtDW . ksp1zkwcj2 = rtP . inti_UpperSat ; } else { if (
rtDW . ksp1zkwcj2 <= rtP . inti_LowerSat ) { rtDW . ksp1zkwcj2 = rtP .
inti_LowerSat ; } } } if ( ( rtB . jum15pqqg1 > 0.0 ) && ( rtDW . kmqrnxxbow
<= 0 ) ) { rtDW . ksp1zkwcj2 = rtDW . dk1lpgs41d ; if ( rtDW . ksp1zkwcj2 >=
rtP . inti_UpperSat ) { rtDW . ksp1zkwcj2 = rtP . inti_UpperSat ; } else { if
( rtDW . ksp1zkwcj2 <= rtP . inti_LowerSat ) { rtDW . ksp1zkwcj2 = rtP .
inti_LowerSat ; } } } if ( rtDW . ksp1zkwcj2 >= rtP . inti_UpperSat ) { rtDW
. ksp1zkwcj2 = rtP . inti_UpperSat ; } else { if ( rtDW . ksp1zkwcj2 <= rtP .
inti_LowerSat ) { rtDW . ksp1zkwcj2 = rtP . inti_LowerSat ; } } hnubxhm4oh =
rtP . Gain_Gain * rtDW . ksp1zkwcj2 ; if ( hnubxhm4oh > kbrlz2zmlx ) {
inm34i5hw5 = kbrlz2zmlx ; } else if ( hnubxhm4oh < rtP . Constant9_Value ) {
inm34i5hw5 = rtP . Constant9_Value ; } else { inm34i5hw5 = hnubxhm4oh ; } if
( ! ( 1.000001 * kbrlz2zmlx * 0.96711798839458663 / 0.9999 <= inm34i5hw5 ) )
{ kbrlz2zmlx = inm34i5hw5 ; } inm34i5hw5 = rtP . R3_Gain * rtDW . lwfztydmov
; if ( ! ( hnubxhm4oh > inm34i5hw5 ) ) { inm34i5hw5 = - inm34i5hw5 * 0.999 *
0.1 * 0.9999 ; if ( ! ( hnubxhm4oh < inm34i5hw5 ) ) { inm34i5hw5 = hnubxhm4oh
; } } switch ( ( int32_T ) rtP . Battery_BatType ) { case 1 : hnubxhm4oh = -
( ( real_T ) ( n40x4vvcy0 < rtP . Constant_Value_bwxnqwdlu4 ) * rtP .
Constant4_Value ) * 0.10788213318941363 * ( rtP . Constant4_Value *
n40x4vvcy0 ) * ( 0.51699999999999868 / ( rtP . Constant4_Value * inm34i5hw5 +
0.051699999999999871 ) ) ; inm34i5hw5 = rtDW . lnyxns4prr ; break ; case 2 :
hnubxhm4oh = rtP . Constant1_Value_ba5ae3pck4 * rtDW . lwfztydmov ;
hnubxhm4oh = - ( ( real_T ) ( n40x4vvcy0 < rtP . Constant_Value_bwxnqwdlu4 )
* rtP . Constant1_Value_ba5ae3pck4 ) * 0.10788213318941363 * ( rtP .
Constant1_Value_ba5ae3pck4 * n40x4vvcy0 ) * hnubxhm4oh / ( rtP .
Constant1_Value_ba5ae3pck4 * inm34i5hw5 + hnubxhm4oh * 0.1 ) ; if (
kbrlz2zmlx > rtP . Saturation_UpperSat ) { n4vvs0yp2i = rtP .
Saturation_UpperSat ; } else if ( kbrlz2zmlx < rtP . Saturation_LowerSat ) {
n4vvs0yp2i = rtP . Saturation_LowerSat ; } else { n4vvs0yp2i = kbrlz2zmlx ; }
inm34i5hw5 = muDoubleScalarExp ( - 122.12389380530972 * n4vvs0yp2i ) *
0.60462693404467927 ; break ; case 3 : hnubxhm4oh = - ( ( real_T ) (
n40x4vvcy0 < rtP . Constant_Value_bwxnqwdlu4 ) * rtP . Constant3_Value ) *
0.10788213318941363 * ( rtP . Constant3_Value * n40x4vvcy0 ) * (
0.51699999999999868 / ( muDoubleScalarAbs ( rtP . Constant3_Value *
inm34i5hw5 ) + 0.051699999999999871 ) ) ; inm34i5hw5 = rtDW . lnyxns4prr ;
break ; default : hnubxhm4oh = - ( ( real_T ) ( n40x4vvcy0 < rtP .
Constant_Value_bwxnqwdlu4 ) * rtP . Constant2_Value ) * 0.10788213318941363 *
( rtP . Constant2_Value * n40x4vvcy0 ) * ( 0.51699999999999868 / (
muDoubleScalarAbs ( rtP . Constant2_Value * inm34i5hw5 ) +
0.051699999999999871 ) ) ; inm34i5hw5 = rtDW . lnyxns4prr ; break ; }
n40x4vvcy0 = ( ( ( ( - rtB . jum15pqqg1 * 0.10788213318941363 * n40x4vvcy0 *
rtDW . lwfztydmov / ( rtDW . lwfztydmov - kbrlz2zmlx ) + -
0.10788213318941363 * rtDW . lwfztydmov / ( rtDW . lwfztydmov - kbrlz2zmlx )
* kbrlz2zmlx ) + hnubxhm4oh ) + inm34i5hw5 ) + - 0.0 * kbrlz2zmlx ) + rtP .
Constant_Value ; if ( n40x4vvcy0 > rtP . Constant1_Value ) { rtB . az0hrbqkrf
= rtP . Constant1_Value ; } else if ( n40x4vvcy0 < rtDW . j3ah0j5uha ) { rtB
. az0hrbqkrf = rtDW . j3ah0j5uha ; } else { rtB . az0hrbqkrf = n40x4vvcy0 ; }
n40x4vvcy0 = rtP . R2_Gain_gn2hhy35bk * rtDW . jnwgqfjczs ; n4vvs0yp2i = rtP
. Currentfilter_NumCoef_dwkwb5rq0b * rtDW . iq0yvshwbl ; rtB . daplgb1rla = (
n4vvs0yp2i > rtP . Constant_Value_okglhro0vm ) ; if ( rtDW . itp5tejlgk != 0
) { rtDW . hwrivx5mi4 = rtDW . lztbr3et3t ; if ( rtDW . hwrivx5mi4 >= rtP .
inti_UpperSat_ovnl0mfsbp ) { rtDW . hwrivx5mi4 = rtP .
inti_UpperSat_ovnl0mfsbp ; } else { if ( rtDW . hwrivx5mi4 <= rtP .
inti_LowerSat_lm4gcia0l4 ) { rtDW . hwrivx5mi4 = rtP .
inti_LowerSat_lm4gcia0l4 ; } } } if ( ( rtB . daplgb1rla > 0.0 ) && ( rtDW .
f2pl5hhy0a <= 0 ) ) { rtDW . hwrivx5mi4 = rtDW . lztbr3et3t ; if ( rtDW .
hwrivx5mi4 >= rtP . inti_UpperSat_ovnl0mfsbp ) { rtDW . hwrivx5mi4 = rtP .
inti_UpperSat_ovnl0mfsbp ; } else { if ( rtDW . hwrivx5mi4 <= rtP .
inti_LowerSat_lm4gcia0l4 ) { rtDW . hwrivx5mi4 = rtP .
inti_LowerSat_lm4gcia0l4 ; } } } if ( rtDW . hwrivx5mi4 >= rtP .
inti_UpperSat_ovnl0mfsbp ) { rtDW . hwrivx5mi4 = rtP .
inti_UpperSat_ovnl0mfsbp ; } else { if ( rtDW . hwrivx5mi4 <= rtP .
inti_LowerSat_lm4gcia0l4 ) { rtDW . hwrivx5mi4 = rtP .
inti_LowerSat_lm4gcia0l4 ; } } hnubxhm4oh = rtP . Gain_Gain_iqgvprw0ss * rtDW
. hwrivx5mi4 ; if ( hnubxhm4oh > n40x4vvcy0 ) { inm34i5hw5 = n40x4vvcy0 ; }
else if ( hnubxhm4oh < rtP . Constant9_Value_a5rtdjlock ) { inm34i5hw5 = rtP
. Constant9_Value_a5rtdjlock ; } else { inm34i5hw5 = hnubxhm4oh ; } if ( ! (
1.000001 * n40x4vvcy0 * 0.96711798839458663 / 0.9999 <= inm34i5hw5 ) ) {
n40x4vvcy0 = inm34i5hw5 ; } inm34i5hw5 = rtP . R3_Gain_lw2doffbmz * rtDW .
jnwgqfjczs ; if ( ! ( hnubxhm4oh > inm34i5hw5 ) ) { inm34i5hw5 = - inm34i5hw5
* 0.999 * 0.1 * 0.9999 ; if ( ! ( hnubxhm4oh < inm34i5hw5 ) ) { inm34i5hw5 =
hnubxhm4oh ; } } switch ( ( int32_T ) rtP . Battery1_BatType ) { case 1 :
hnubxhm4oh = - ( ( real_T ) ( n4vvs0yp2i < rtP . Constant_Value_g12zcbefww )
* rtP . Constant4_Value_lthflsnkeu ) * 0.10788213318941363 * ( rtP .
Constant4_Value_lthflsnkeu * n4vvs0yp2i ) * ( 0.51699999999999868 / ( rtP .
Constant4_Value_lthflsnkeu * inm34i5hw5 + 0.051699999999999871 ) ) ;
inm34i5hw5 = rtDW . nb1buv1zor ; break ; case 2 : hnubxhm4oh = rtP .
Constant1_Value_jbvs0nsfpj * rtDW . jnwgqfjczs ; hnubxhm4oh = - ( ( real_T )
( n4vvs0yp2i < rtP . Constant_Value_g12zcbefww ) * rtP .
Constant1_Value_jbvs0nsfpj ) * 0.10788213318941363 * ( rtP .
Constant1_Value_jbvs0nsfpj * n4vvs0yp2i ) * hnubxhm4oh / ( rtP .
Constant1_Value_jbvs0nsfpj * inm34i5hw5 + hnubxhm4oh * 0.1 ) ; if (
n40x4vvcy0 > rtP . Saturation_UpperSat_lqsamz1a2q ) { pi01aggk5s = rtP .
Saturation_UpperSat_lqsamz1a2q ; } else if ( n40x4vvcy0 < rtP .
Saturation_LowerSat_jabf313muk ) { pi01aggk5s = rtP .
Saturation_LowerSat_jabf313muk ; } else { pi01aggk5s = n40x4vvcy0 ; }
inm34i5hw5 = muDoubleScalarExp ( - 122.12389380530972 * pi01aggk5s ) *
0.60462693404467927 ; break ; case 3 : hnubxhm4oh = - ( ( real_T ) (
n4vvs0yp2i < rtP . Constant_Value_g12zcbefww ) * rtP .
Constant3_Value_nj5jkoby2k ) * 0.10788213318941363 * ( rtP .
Constant3_Value_nj5jkoby2k * n4vvs0yp2i ) * ( 0.51699999999999868 / (
muDoubleScalarAbs ( rtP . Constant3_Value_nj5jkoby2k * inm34i5hw5 ) +
0.051699999999999871 ) ) ; inm34i5hw5 = rtDW . nb1buv1zor ; break ; default :
hnubxhm4oh = - ( ( real_T ) ( n4vvs0yp2i < rtP . Constant_Value_g12zcbefww )
* rtP . Constant2_Value_gj2xaq4m3s ) * 0.10788213318941363 * ( rtP .
Constant2_Value_gj2xaq4m3s * n4vvs0yp2i ) * ( 0.51699999999999868 / (
muDoubleScalarAbs ( rtP . Constant2_Value_gj2xaq4m3s * inm34i5hw5 ) +
0.051699999999999871 ) ) ; inm34i5hw5 = rtDW . nb1buv1zor ; break ; }
n4vvs0yp2i = ( ( ( ( - rtB . daplgb1rla * 0.10788213318941363 * n4vvs0yp2i *
rtDW . jnwgqfjczs / ( rtDW . jnwgqfjczs - n40x4vvcy0 ) + -
0.10788213318941363 * rtDW . jnwgqfjczs / ( rtDW . jnwgqfjczs - n40x4vvcy0 )
* n40x4vvcy0 ) + hnubxhm4oh ) + inm34i5hw5 ) + - 0.0 * n40x4vvcy0 ) + rtP .
Constant_Value_myjwkv2xqc ; if ( n4vvs0yp2i > rtP .
Constant1_Value_eymbazuin1 ) { rtB . jdfrz34ab5 = rtP .
Constant1_Value_eymbazuin1 ; } else if ( n4vvs0yp2i < rtDW . ad3mgyfzte ) {
rtB . jdfrz34ab5 = rtDW . ad3mgyfzte ; } else { rtB . jdfrz34ab5 = n4vvs0yp2i
; } n4vvs0yp2i = rtP . R2_Gain_dw41hzcoux * rtDW . aircger2rx ; pi01aggk5s =
rtP . Currentfilter_NumCoef_o5cnlr2zv4 * rtDW . oq5hmifhxo ; rtB . lujepfroun
= ( pi01aggk5s > rtP . Constant_Value_l0gkldjobz ) ; if ( rtDW . d23tl2d2xe
!= 0 ) { rtDW . ms1k4m0ka3 = rtDW . maze5hu4ab ; if ( rtDW . ms1k4m0ka3 >=
rtP . inti_UpperSat_fafppsy3ai ) { rtDW . ms1k4m0ka3 = rtP .
inti_UpperSat_fafppsy3ai ; } else { if ( rtDW . ms1k4m0ka3 <= rtP .
inti_LowerSat_lfqfty24xa ) { rtDW . ms1k4m0ka3 = rtP .
inti_LowerSat_lfqfty24xa ; } } } if ( ( rtB . lujepfroun > 0.0 ) && ( rtDW .
f2mbtmfzg2 <= 0 ) ) { rtDW . ms1k4m0ka3 = rtDW . maze5hu4ab ; if ( rtDW .
ms1k4m0ka3 >= rtP . inti_UpperSat_fafppsy3ai ) { rtDW . ms1k4m0ka3 = rtP .
inti_UpperSat_fafppsy3ai ; } else { if ( rtDW . ms1k4m0ka3 <= rtP .
inti_LowerSat_lfqfty24xa ) { rtDW . ms1k4m0ka3 = rtP .
inti_LowerSat_lfqfty24xa ; } } } if ( rtDW . ms1k4m0ka3 >= rtP .
inti_UpperSat_fafppsy3ai ) { rtDW . ms1k4m0ka3 = rtP .
inti_UpperSat_fafppsy3ai ; } else { if ( rtDW . ms1k4m0ka3 <= rtP .
inti_LowerSat_lfqfty24xa ) { rtDW . ms1k4m0ka3 = rtP .
inti_LowerSat_lfqfty24xa ; } } hnubxhm4oh = rtP . Gain_Gain_obfealy1ww * rtDW
. ms1k4m0ka3 ; if ( hnubxhm4oh > n4vvs0yp2i ) { inm34i5hw5 = n4vvs0yp2i ; }
else if ( hnubxhm4oh < rtP . Constant9_Value_il1twk33xw ) { inm34i5hw5 = rtP
. Constant9_Value_il1twk33xw ; } else { inm34i5hw5 = hnubxhm4oh ; } if ( ! (
1.000001 * n4vvs0yp2i * 0.96711798839458663 / 0.9999 <= inm34i5hw5 ) ) {
n4vvs0yp2i = inm34i5hw5 ; } inm34i5hw5 = rtP . R3_Gain_ozmg2mkfqb * rtDW .
aircger2rx ; if ( ! ( hnubxhm4oh > inm34i5hw5 ) ) { inm34i5hw5 = - inm34i5hw5
* 0.999 * 0.1 * 0.9999 ; if ( ! ( hnubxhm4oh < inm34i5hw5 ) ) { inm34i5hw5 =
hnubxhm4oh ; } } switch ( ( int32_T ) rtP . Battery2_BatType ) { case 1 :
hnubxhm4oh = - ( ( real_T ) ( pi01aggk5s < rtP . Constant_Value_cos31swra1 )
* rtP . Constant4_Value_hnhj3hl1qn ) * 0.10788213318941363 * ( rtP .
Constant4_Value_hnhj3hl1qn * pi01aggk5s ) * ( 0.51699999999999868 / ( rtP .
Constant4_Value_hnhj3hl1qn * inm34i5hw5 + 0.051699999999999871 ) ) ;
inm34i5hw5 = rtDW . fb5x1hmdio ; break ; case 2 : hnubxhm4oh = rtP .
Constant1_Value_e05fuchp0u * rtDW . aircger2rx ; hnubxhm4oh = - ( ( real_T )
( pi01aggk5s < rtP . Constant_Value_cos31swra1 ) * rtP .
Constant1_Value_e05fuchp0u ) * 0.10788213318941363 * ( rtP .
Constant1_Value_e05fuchp0u * pi01aggk5s ) * hnubxhm4oh / ( rtP .
Constant1_Value_e05fuchp0u * inm34i5hw5 + hnubxhm4oh * 0.1 ) ; if (
n4vvs0yp2i > rtP . Saturation_UpperSat_bh0lef2msr ) { d3t2ofntt1 = rtP .
Saturation_UpperSat_bh0lef2msr ; } else if ( n4vvs0yp2i < rtP .
Saturation_LowerSat_e35an2lbrt ) { d3t2ofntt1 = rtP .
Saturation_LowerSat_e35an2lbrt ; } else { d3t2ofntt1 = n4vvs0yp2i ; }
inm34i5hw5 = muDoubleScalarExp ( - 122.12389380530972 * d3t2ofntt1 ) *
0.60462693404467927 ; break ; case 3 : hnubxhm4oh = - ( ( real_T ) (
pi01aggk5s < rtP . Constant_Value_cos31swra1 ) * rtP .
Constant3_Value_hicomfdnpb ) * 0.10788213318941363 * ( rtP .
Constant3_Value_hicomfdnpb * pi01aggk5s ) * ( 0.51699999999999868 / (
muDoubleScalarAbs ( rtP . Constant3_Value_hicomfdnpb * inm34i5hw5 ) +
0.051699999999999871 ) ) ; inm34i5hw5 = rtDW . fb5x1hmdio ; break ; default :
hnubxhm4oh = - ( ( real_T ) ( pi01aggk5s < rtP . Constant_Value_cos31swra1 )
* rtP . Constant2_Value_g43qk25t5s ) * 0.10788213318941363 * ( rtP .
Constant2_Value_g43qk25t5s * pi01aggk5s ) * ( 0.51699999999999868 / (
muDoubleScalarAbs ( rtP . Constant2_Value_g43qk25t5s * inm34i5hw5 ) +
0.051699999999999871 ) ) ; inm34i5hw5 = rtDW . fb5x1hmdio ; break ; }
pi01aggk5s = ( ( ( ( - rtB . lujepfroun * 0.10788213318941363 * pi01aggk5s *
rtDW . aircger2rx / ( rtDW . aircger2rx - n4vvs0yp2i ) + -
0.10788213318941363 * rtDW . aircger2rx / ( rtDW . aircger2rx - n4vvs0yp2i )
* n4vvs0yp2i ) + hnubxhm4oh ) + inm34i5hw5 ) + - 0.0 * n4vvs0yp2i ) + rtP .
Constant_Value_ftfxsd2jhc ; if ( pi01aggk5s > rtP .
Constant1_Value_nyr1jvuern ) { rtB . gywgkp2di0 = rtP .
Constant1_Value_nyr1jvuern ; } else if ( pi01aggk5s < rtDW . ihbczgg1ch ) {
rtB . gywgkp2di0 = rtDW . ihbczgg1ch ; } else { rtB . gywgkp2di0 = pi01aggk5s
; } { real_T accum ; real_T * Cs = ( real_T * ) rtDW . g5a0yy0hef . CS ;
real_T * Ds = ( real_T * ) rtDW . g5a0yy0hef . DS ; { int_T i1 ; real_T * y0
= & rtB . n1mhwe4wmc [ 0 ] ; for ( i1 = 0 ; i1 < 200 ; i1 ++ ) { accum = 0.0
; { int_T i2 ; real_T * xd = & rtDW . bmlwssomru [ 0 ] ; for ( i2 = 0 ; i2 <
48 ; i2 ++ ) { accum += * ( Cs ++ ) * xd [ i2 ] ; } } accum += * ( Ds ++ ) *
rtB . az0hrbqkrf ; accum += * ( Ds ++ ) * rtB . jdfrz34ab5 ; accum += * ( Ds
++ ) * rtB . gywgkp2di0 ; accum += * ( Ds ++ ) * rtP . amps_in ; y0 [ i1 ] =
accum ; } } } { real_T accum ; int_T * switch_status = ( int_T * ) rtDW .
kosaktmuhw . SWITCH_STATUS ; int_T * switch_status_init = ( int_T * ) rtDW .
kosaktmuhw . SWITCH_STATUS_INIT ; int_T * SwitchChange = ( int_T * ) rtDW .
kosaktmuhw . SW_CHG ; int_T * gState = ( int_T * ) rtDW . kosaktmuhw .
G_STATE ; real_T * yswitch = ( real_T * ) rtDW . kosaktmuhw . Y_SWITCH ;
int_T * switchTypes = ( int_T * ) rtDW . kosaktmuhw . SWITCH_TYPES ; int_T *
idxOutSw = ( int_T * ) rtDW . kosaktmuhw . IDX_OUT_SW ; real_T * DxCol = (
real_T * ) rtDW . kosaktmuhw . DX_COL ; real_T * tmp2 = ( real_T * ) rtDW .
kosaktmuhw . TMP2 ; real_T * uswlast = ( real_T * ) rtDW . kosaktmuhw .
USWLAST ; int_T newState ; int_T swChanged = 0 ; int loopsToDo = 20 ; real_T
temp ; memcpy ( switch_status_init , switch_status , 4 * sizeof ( int_T ) ) ;
memcpy ( uswlast , & rtB . ozjanvc1ks [ 0 ] , 4 * sizeof ( real_T ) ) ; do {
if ( loopsToDo == 1 ) { swChanged = 0 ; { int_T i1 ; for ( i1 = 0 ; i1 < 4 ;
i1 ++ ) { swChanged = ( ( SwitchChange [ i1 ] = switch_status_init [ i1 ] -
switch_status [ i1 ] ) != 0 ) ? 1 : swChanged ; switch_status [ i1 ] =
switch_status_init [ i1 ] ; } } } else { real_T * Ds = ( real_T * ) rtDW .
kosaktmuhw . DS ; { int_T i1 ; real_T * y0 = & rtB . ozjanvc1ks [ 0 ] ; for (
i1 = 0 ; i1 < 6 ; i1 ++ ) { accum = 0.0 ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_az3dw3pjw2 [ 0 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_az3dw3pjw2 [ 1 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_az3dw3pjw2 [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_az3dw3pjw2 [ 3 ] ; y0 [ i1 ] = accum ; } } swChanged = 0
; newState = gState [ 0 ] > 0 ? 1 : 0 ; swChanged = ( ( SwitchChange [ 0 ] =
newState - switch_status [ 0 ] ) != 0 ) ? 1 : swChanged ; switch_status [ 0 ]
= newState ; newState = gState [ 1 ] > 0 ? 1 : 0 ; swChanged = ( (
SwitchChange [ 1 ] = newState - switch_status [ 1 ] ) != 0 ) ? 1 : swChanged
; switch_status [ 1 ] = newState ; newState = rtB . ozjanvc1ks [ 2 ] > 0.0 ?
1 : ( ( rtB . ozjanvc1ks [ 2 ] < 0.0 ) ? 0 : switch_status [ 2 ] ) ;
swChanged = ( ( SwitchChange [ 2 ] = newState - switch_status [ 2 ] ) != 0 )
? 1 : swChanged ; switch_status [ 2 ] = newState ; newState = rtB .
ozjanvc1ks [ 3 ] > 0.0 ? 1 : ( ( rtB . ozjanvc1ks [ 3 ] < 0.0 ) ? 0 :
switch_status [ 3 ] ) ; swChanged = ( ( SwitchChange [ 3 ] = newState -
switch_status [ 3 ] ) != 0 ) ? 1 : swChanged ; switch_status [ 3 ] = newState
; } if ( swChanged ) { real_T * Ds = ( real_T * ) rtDW . kosaktmuhw . DS ;
real_T a1 ; { int_T i1 ; for ( i1 = 0 ; i1 < 4 ; i1 ++ ) { if ( SwitchChange
[ i1 ] != 0 ) { a1 = yswitch [ i1 ] * SwitchChange [ i1 ] ; temp = 1 / ( 1 -
Ds [ i1 * 5 ] * a1 ) ; { int_T i2 ; for ( i2 = 0 ; i2 < 6 ; i2 ++ ) { DxCol [
i2 ] = Ds [ i2 * 4 + i1 ] * temp * a1 ; } } DxCol [ i1 ] = temp ; memcpy (
tmp2 , & Ds [ i1 * 4 ] , 4 * sizeof ( real_T ) ) ; memset ( & Ds [ i1 * 4 ] ,
'\0' , 4 * sizeof ( real_T ) ) ; { int_T i2 ; for ( i2 = 0 ; i2 < 6 ; i2 ++ )
{ a1 = DxCol [ i2 ] ; Ds [ i2 * 4 + 0 ] += a1 * tmp2 [ 0 ] ; Ds [ i2 * 4 + 1
] += a1 * tmp2 [ 1 ] ; Ds [ i2 * 4 + 2 ] += a1 * tmp2 [ 2 ] ; Ds [ i2 * 4 + 3
] += a1 * tmp2 [ 3 ] ; } } } } } } } while ( swChanged > 0 && -- loopsToDo >
0 ) ; if ( loopsToDo == 0 ) { real_T * Ds = ( real_T * ) rtDW . kosaktmuhw .
DS ; { int_T i1 ; real_T * y0 = & rtB . ozjanvc1ks [ 0 ] ; for ( i1 = 0 ; i1
< 6 ; i1 ++ ) { accum = 0.0 ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_az3dw3pjw2 [ 0 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_az3dw3pjw2 [ 1 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_az3dw3pjw2 [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_az3dw3pjw2 [ 3 ] ; y0 [ i1 ] = accum ; } } } rtB .
haz3shqct1 [ 0 ] = ( real_T ) switch_status [ 0 ] ; rtB . haz3shqct1 [ 1 ] =
( real_T ) switch_status [ 1 ] ; rtB . haz3shqct1 [ 2 ] = ( real_T )
switch_status [ 2 ] ; rtB . haz3shqct1 [ 3 ] = ( real_T ) switch_status [ 3 ]
; } pi01aggk5s = rtP . R2_Gain_g3s0uniddd * rtDW . jwpobdvxh3 ; d3t2ofntt1 =
rtP . Currentfilter_NumCoef_cmdxxeoc5l * rtDW . l4l5iifhga ; rtB . mcaon1wt2t
= ( d3t2ofntt1 > rtP . Constant_Value_e2zke2vgjc ) ; if ( rtDW . k0yugcv43d
!= 0 ) { rtDW . oegbozknnu = rtDW . nuc12zx3mo ; if ( rtDW . oegbozknnu >=
rtP . inti_UpperSat_knlety0kfl ) { rtDW . oegbozknnu = rtP .
inti_UpperSat_knlety0kfl ; } else { if ( rtDW . oegbozknnu <= rtP .
inti_LowerSat_fqu2adq33w ) { rtDW . oegbozknnu = rtP .
inti_LowerSat_fqu2adq33w ; } } } if ( ( rtB . mcaon1wt2t > 0.0 ) && ( rtDW .
oufwnzwkdu <= 0 ) ) { rtDW . oegbozknnu = rtDW . nuc12zx3mo ; if ( rtDW .
oegbozknnu >= rtP . inti_UpperSat_knlety0kfl ) { rtDW . oegbozknnu = rtP .
inti_UpperSat_knlety0kfl ; } else { if ( rtDW . oegbozknnu <= rtP .
inti_LowerSat_fqu2adq33w ) { rtDW . oegbozknnu = rtP .
inti_LowerSat_fqu2adq33w ; } } } if ( rtDW . oegbozknnu >= rtP .
inti_UpperSat_knlety0kfl ) { rtDW . oegbozknnu = rtP .
inti_UpperSat_knlety0kfl ; } else { if ( rtDW . oegbozknnu <= rtP .
inti_LowerSat_fqu2adq33w ) { rtDW . oegbozknnu = rtP .
inti_LowerSat_fqu2adq33w ; } } hnubxhm4oh = rtP . Gain_Gain_i4pvr0q4al * rtDW
. oegbozknnu ; if ( hnubxhm4oh > pi01aggk5s ) { inm34i5hw5 = pi01aggk5s ; }
else if ( hnubxhm4oh < rtP . Constant9_Value_h31y2anloq ) { inm34i5hw5 = rtP
. Constant9_Value_h31y2anloq ; } else { inm34i5hw5 = hnubxhm4oh ; } if ( ! (
1.000001 * pi01aggk5s * 0.96711798839458663 / 0.9999 <= inm34i5hw5 ) ) {
pi01aggk5s = inm34i5hw5 ; } inm34i5hw5 = rtP . R3_Gain_f2u242ik2e * rtDW .
jwpobdvxh3 ; if ( ! ( hnubxhm4oh > inm34i5hw5 ) ) { inm34i5hw5 = - inm34i5hw5
* 0.999 * 0.1 * 0.9999 ; if ( ! ( hnubxhm4oh < inm34i5hw5 ) ) { inm34i5hw5 =
hnubxhm4oh ; } } switch ( ( int32_T ) rtP . Battery_BatType_l1sun2jtvt ) {
case 1 : hnubxhm4oh = - ( ( real_T ) ( d3t2ofntt1 < rtP .
Constant_Value_ldtorhiuhw ) * rtP . Constant4_Value_i0byxzx5ou ) *
0.053941066594706814 * ( rtP . Constant4_Value_i0byxzx5ou * d3t2ofntt1 ) * (
1.0339999999999974 / ( rtP . Constant4_Value_i0byxzx5ou * inm34i5hw5 +
0.10339999999999974 ) ) ; inm34i5hw5 = rtDW . bdlz3yfllc ; break ; case 2 :
hnubxhm4oh = rtP . Constant1_Value_k0ii2vzisz * rtDW . jwpobdvxh3 ;
hnubxhm4oh = - ( ( real_T ) ( d3t2ofntt1 < rtP . Constant_Value_ldtorhiuhw )
* rtP . Constant1_Value_k0ii2vzisz ) * 0.053941066594706814 * ( rtP .
Constant1_Value_k0ii2vzisz * d3t2ofntt1 ) * hnubxhm4oh / ( rtP .
Constant1_Value_k0ii2vzisz * inm34i5hw5 + hnubxhm4oh * 0.1 ) ; if (
pi01aggk5s > rtP . Saturation_UpperSat_aeh1cq5q5j ) { ewm2wjscso = rtP .
Saturation_UpperSat_aeh1cq5q5j ; } else if ( pi01aggk5s < rtP .
Saturation_LowerSat_lpdw4vd5ik ) { ewm2wjscso = rtP .
Saturation_LowerSat_lpdw4vd5ik ; } else { ewm2wjscso = pi01aggk5s ; }
inm34i5hw5 = muDoubleScalarExp ( - 61.06194690265486 * ewm2wjscso ) *
0.60462693404467927 ; break ; case 3 : hnubxhm4oh = - ( ( real_T ) (
d3t2ofntt1 < rtP . Constant_Value_ldtorhiuhw ) * rtP .
Constant3_Value_mp2iadeyaa ) * 0.053941066594706814 * ( rtP .
Constant3_Value_mp2iadeyaa * d3t2ofntt1 ) * ( 1.0339999999999974 / (
muDoubleScalarAbs ( rtP . Constant3_Value_mp2iadeyaa * inm34i5hw5 ) +
0.10339999999999974 ) ) ; inm34i5hw5 = rtDW . bdlz3yfllc ; break ; default :
hnubxhm4oh = - ( ( real_T ) ( d3t2ofntt1 < rtP . Constant_Value_ldtorhiuhw )
* rtP . Constant2_Value_o4lojhk0zb ) * 0.053941066594706814 * ( rtP .
Constant2_Value_o4lojhk0zb * d3t2ofntt1 ) * ( 1.0339999999999974 / (
muDoubleScalarAbs ( rtP . Constant2_Value_o4lojhk0zb * inm34i5hw5 ) +
0.10339999999999974 ) ) ; inm34i5hw5 = rtDW . bdlz3yfllc ; break ; }
d3t2ofntt1 = ( ( ( ( - rtB . mcaon1wt2t * 0.053941066594706814 * d3t2ofntt1 *
rtDW . jwpobdvxh3 / ( rtDW . jwpobdvxh3 - pi01aggk5s ) + -
0.053941066594706814 * rtDW . jwpobdvxh3 / ( rtDW . jwpobdvxh3 - pi01aggk5s )
* pi01aggk5s ) + hnubxhm4oh ) + inm34i5hw5 ) + - 0.0 * pi01aggk5s ) + rtP .
Constant_Value_fuqdogx424 ; if ( d3t2ofntt1 > rtP .
Constant1_Value_cvafov1aay ) { rtB . f3ooyiusal = rtP .
Constant1_Value_cvafov1aay ; } else if ( d3t2ofntt1 < rtDW . jz4s1v251o ) {
rtB . f3ooyiusal = rtDW . jz4s1v251o ; } else { rtB . f3ooyiusal = d3t2ofntt1
; } { real_T accum ; int_T * switch_status = ( int_T * ) rtDW . lhqp2i1wv4 .
SWITCH_STATUS ; int_T * switch_status_init = ( int_T * ) rtDW . lhqp2i1wv4 .
SWITCH_STATUS_INIT ; int_T * SwitchChange = ( int_T * ) rtDW . lhqp2i1wv4 .
SW_CHG ; int_T * gState = ( int_T * ) rtDW . lhqp2i1wv4 . G_STATE ; real_T *
yswitch = ( real_T * ) rtDW . lhqp2i1wv4 . Y_SWITCH ; int_T * switchTypes = (
int_T * ) rtDW . lhqp2i1wv4 . SWITCH_TYPES ; int_T * idxOutSw = ( int_T * )
rtDW . lhqp2i1wv4 . IDX_OUT_SW ; real_T * DxCol = ( real_T * ) rtDW .
lhqp2i1wv4 . DX_COL ; real_T * tmp2 = ( real_T * ) rtDW . lhqp2i1wv4 . TMP2 ;
real_T * uswlast = ( real_T * ) rtDW . lhqp2i1wv4 . USWLAST ; int_T newState
; int_T swChanged = 0 ; int loopsToDo = 20 ; real_T temp ; memcpy (
switch_status_init , switch_status , 4 * sizeof ( int_T ) ) ; memcpy (
uswlast , & rtB . c4oldjnq3u [ 0 ] , 4 * sizeof ( real_T ) ) ; do { if (
loopsToDo == 1 ) { swChanged = 0 ; { int_T i1 ; for ( i1 = 0 ; i1 < 4 ; i1 ++
) { swChanged = ( ( SwitchChange [ i1 ] = switch_status_init [ i1 ] -
switch_status [ i1 ] ) != 0 ) ? 1 : swChanged ; switch_status [ i1 ] =
switch_status_init [ i1 ] ; } } } else { real_T * Ds = ( real_T * ) rtDW .
lhqp2i1wv4 . DS ; { int_T i1 ; real_T * y0 = & rtB . c4oldjnq3u [ 0 ] ; for (
i1 = 0 ; i1 < 7 ; i1 ++ ) { accum = 0.0 ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_hsgedxy3pe [ 0 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_hsgedxy3pe [ 1 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_hsgedxy3pe [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_hsgedxy3pe [ 3 ] ; accum += * ( Ds ++ ) * rtB .
f3ooyiusal ; y0 [ i1 ] = accum ; } } swChanged = 0 ; newState = gState [ 0 ]
> 0 ? 1 : 0 ; swChanged = ( ( SwitchChange [ 0 ] = newState - switch_status [
0 ] ) != 0 ) ? 1 : swChanged ; switch_status [ 0 ] = newState ; newState =
gState [ 1 ] > 0 ? 1 : 0 ; swChanged = ( ( SwitchChange [ 1 ] = newState -
switch_status [ 1 ] ) != 0 ) ? 1 : swChanged ; switch_status [ 1 ] = newState
; newState = rtB . c4oldjnq3u [ 2 ] > 0.0 ? 1 : ( ( rtB . c4oldjnq3u [ 2 ] <
0.0 ) ? 0 : switch_status [ 2 ] ) ; swChanged = ( ( SwitchChange [ 2 ] =
newState - switch_status [ 2 ] ) != 0 ) ? 1 : swChanged ; switch_status [ 2 ]
= newState ; newState = rtB . c4oldjnq3u [ 3 ] > 0.0 ? 1 : ( ( rtB .
c4oldjnq3u [ 3 ] < 0.0 ) ? 0 : switch_status [ 3 ] ) ; swChanged = ( (
SwitchChange [ 3 ] = newState - switch_status [ 3 ] ) != 0 ) ? 1 : swChanged
; switch_status [ 3 ] = newState ; } if ( swChanged ) { real_T * Ds = (
real_T * ) rtDW . lhqp2i1wv4 . DS ; real_T a1 ; { int_T i1 ; for ( i1 = 0 ;
i1 < 4 ; i1 ++ ) { if ( SwitchChange [ i1 ] != 0 ) { a1 = yswitch [ i1 ] *
SwitchChange [ i1 ] ; temp = 1 / ( 1 - Ds [ i1 * 6 ] * a1 ) ; { int_T i2 ;
for ( i2 = 0 ; i2 < 7 ; i2 ++ ) { DxCol [ i2 ] = Ds [ i2 * 5 + i1 ] * temp *
a1 ; } } DxCol [ i1 ] = temp ; memcpy ( tmp2 , & Ds [ i1 * 5 ] , 5 * sizeof (
real_T ) ) ; memset ( & Ds [ i1 * 5 ] , '\0' , 5 * sizeof ( real_T ) ) ; {
int_T i2 ; for ( i2 = 0 ; i2 < 7 ; i2 ++ ) { a1 = DxCol [ i2 ] ; { int_T i3 ;
for ( i3 = 0 ; i3 < 5 ; i3 ++ ) { Ds [ i2 * 5 + i3 ] += a1 * tmp2 [ i3 ] ; }
} } } } } } } } while ( swChanged > 0 && -- loopsToDo > 0 ) ; if ( loopsToDo
== 0 ) { real_T * Ds = ( real_T * ) rtDW . lhqp2i1wv4 . DS ; { int_T i1 ;
real_T * y0 = & rtB . c4oldjnq3u [ 0 ] ; for ( i1 = 0 ; i1 < 7 ; i1 ++ ) {
accum = 0.0 ; accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value_hsgedxy3pe [
0 ] ; accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value_hsgedxy3pe [ 1 ] ;
accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value_hsgedxy3pe [ 2 ] ; accum +=
* ( Ds ++ ) * rtP . SwitchCurrents_Value_hsgedxy3pe [ 3 ] ; accum += * ( Ds
++ ) * rtB . f3ooyiusal ; y0 [ i1 ] = accum ; } } } rtB . ibvmt2yzmz [ 0 ] =
( real_T ) switch_status [ 0 ] ; rtB . ibvmt2yzmz [ 1 ] = ( real_T )
switch_status [ 1 ] ; rtB . ibvmt2yzmz [ 2 ] = ( real_T ) switch_status [ 2 ]
; rtB . ibvmt2yzmz [ 3 ] = ( real_T ) switch_status [ 3 ] ; } d3t2ofntt1 =
rtP . R2_Gain_jg254swwaz * rtDW . mip1wd2oyv ; ewm2wjscso = rtP .
Currentfilter_NumCoef_orciffprp3 * rtDW . nqdr1b40o2 ; rtB . c5qmbivysx = (
ewm2wjscso > rtP . Constant_Value_i1wr2oz2nq ) ; if ( rtDW . fpix2rdml1 != 0
) { rtDW . bpnis5nmqy = rtDW . ogqyiifq2n ; if ( rtDW . bpnis5nmqy >= rtP .
inti_UpperSat_kkiq22x4id ) { rtDW . bpnis5nmqy = rtP .
inti_UpperSat_kkiq22x4id ; } else { if ( rtDW . bpnis5nmqy <= rtP .
inti_LowerSat_jiolab11br ) { rtDW . bpnis5nmqy = rtP .
inti_LowerSat_jiolab11br ; } } } if ( ( rtB . c5qmbivysx > 0.0 ) && ( rtDW .
lrgpgfqgzz <= 0 ) ) { rtDW . bpnis5nmqy = rtDW . ogqyiifq2n ; if ( rtDW .
bpnis5nmqy >= rtP . inti_UpperSat_kkiq22x4id ) { rtDW . bpnis5nmqy = rtP .
inti_UpperSat_kkiq22x4id ; } else { if ( rtDW . bpnis5nmqy <= rtP .
inti_LowerSat_jiolab11br ) { rtDW . bpnis5nmqy = rtP .
inti_LowerSat_jiolab11br ; } } } if ( rtDW . bpnis5nmqy >= rtP .
inti_UpperSat_kkiq22x4id ) { rtDW . bpnis5nmqy = rtP .
inti_UpperSat_kkiq22x4id ; } else { if ( rtDW . bpnis5nmqy <= rtP .
inti_LowerSat_jiolab11br ) { rtDW . bpnis5nmqy = rtP .
inti_LowerSat_jiolab11br ; } } hnubxhm4oh = rtP . Gain_Gain_pyhxvpyinf * rtDW
. bpnis5nmqy ; if ( hnubxhm4oh > d3t2ofntt1 ) { inm34i5hw5 = d3t2ofntt1 ; }
else if ( hnubxhm4oh < rtP . Constant9_Value_htg43rfxti ) { inm34i5hw5 = rtP
. Constant9_Value_htg43rfxti ; } else { inm34i5hw5 = hnubxhm4oh ; } if ( ! (
1.000001 * d3t2ofntt1 * 0.96711798839458663 / 0.9999 <= inm34i5hw5 ) ) {
d3t2ofntt1 = inm34i5hw5 ; } inm34i5hw5 = rtP . R3_Gain_juiudqialo * rtDW .
mip1wd2oyv ; if ( ! ( hnubxhm4oh > inm34i5hw5 ) ) { inm34i5hw5 = - inm34i5hw5
* 0.999 * 0.1 * 0.9999 ; if ( ! ( hnubxhm4oh < inm34i5hw5 ) ) { inm34i5hw5 =
hnubxhm4oh ; } } switch ( ( int32_T ) rtP . Battery_BatType_cmk1pph4hu ) {
case 1 : hnubxhm4oh = - ( ( real_T ) ( ewm2wjscso < rtP .
Constant_Value_clcghdqsjf ) * rtP . Constant4_Value_gu2biizajn ) *
0.053941066594706814 * ( rtP . Constant4_Value_gu2biizajn * ewm2wjscso ) * (
1.0339999999999974 / ( rtP . Constant4_Value_gu2biizajn * inm34i5hw5 +
0.10339999999999974 ) ) ; inm34i5hw5 = rtDW . jf2kk54ldn ; break ; case 2 :
hnubxhm4oh = rtP . Constant1_Value_h5janxrbot * rtDW . mip1wd2oyv ;
hnubxhm4oh = - ( ( real_T ) ( ewm2wjscso < rtP . Constant_Value_clcghdqsjf )
* rtP . Constant1_Value_h5janxrbot ) * 0.053941066594706814 * ( rtP .
Constant1_Value_h5janxrbot * ewm2wjscso ) * hnubxhm4oh / ( rtP .
Constant1_Value_h5janxrbot * inm34i5hw5 + hnubxhm4oh * 0.1 ) ; if (
d3t2ofntt1 > rtP . Saturation_UpperSat_jwiz1tvuc0 ) { inm34i5hw5 = rtP .
Saturation_UpperSat_jwiz1tvuc0 ; } else if ( d3t2ofntt1 < rtP .
Saturation_LowerSat_d4iiqg5kd0 ) { inm34i5hw5 = rtP .
Saturation_LowerSat_d4iiqg5kd0 ; } else { inm34i5hw5 = d3t2ofntt1 ; }
inm34i5hw5 = muDoubleScalarExp ( - 61.06194690265486 * inm34i5hw5 ) *
0.60462693404467927 ; break ; case 3 : hnubxhm4oh = - ( ( real_T ) (
ewm2wjscso < rtP . Constant_Value_clcghdqsjf ) * rtP .
Constant3_Value_i0zzufmxbg ) * 0.053941066594706814 * ( rtP .
Constant3_Value_i0zzufmxbg * ewm2wjscso ) * ( 1.0339999999999974 / (
muDoubleScalarAbs ( rtP . Constant3_Value_i0zzufmxbg * inm34i5hw5 ) +
0.10339999999999974 ) ) ; inm34i5hw5 = rtDW . jf2kk54ldn ; break ; default :
hnubxhm4oh = - ( ( real_T ) ( ewm2wjscso < rtP . Constant_Value_clcghdqsjf )
* rtP . Constant2_Value_ey2pmru5zy ) * 0.053941066594706814 * ( rtP .
Constant2_Value_ey2pmru5zy * ewm2wjscso ) * ( 1.0339999999999974 / (
muDoubleScalarAbs ( rtP . Constant2_Value_ey2pmru5zy * inm34i5hw5 ) +
0.10339999999999974 ) ) ; inm34i5hw5 = rtDW . jf2kk54ldn ; break ; }
ewm2wjscso = ( ( ( ( - rtB . c5qmbivysx * 0.053941066594706814 * ewm2wjscso *
rtDW . mip1wd2oyv / ( rtDW . mip1wd2oyv - d3t2ofntt1 ) + -
0.053941066594706814 * rtDW . mip1wd2oyv / ( rtDW . mip1wd2oyv - d3t2ofntt1 )
* d3t2ofntt1 ) + hnubxhm4oh ) + inm34i5hw5 ) + - 0.0 * d3t2ofntt1 ) + rtP .
Constant_Value_kemd1naiax ; if ( ewm2wjscso > rtP .
Constant1_Value_kw1evdsdjk ) { rtB . pho3qpftnj = rtP .
Constant1_Value_kw1evdsdjk ; } else if ( ewm2wjscso < rtDW . o035fkrhgg ) {
rtB . pho3qpftnj = rtDW . o035fkrhgg ; } else { rtB . pho3qpftnj = ewm2wjscso
; } { real_T accum ; int_T * switch_status = ( int_T * ) rtDW . c0rfzt21pv .
SWITCH_STATUS ; int_T * switch_status_init = ( int_T * ) rtDW . c0rfzt21pv .
SWITCH_STATUS_INIT ; int_T * SwitchChange = ( int_T * ) rtDW . c0rfzt21pv .
SW_CHG ; int_T * gState = ( int_T * ) rtDW . c0rfzt21pv . G_STATE ; real_T *
yswitch = ( real_T * ) rtDW . c0rfzt21pv . Y_SWITCH ; int_T * switchTypes = (
int_T * ) rtDW . c0rfzt21pv . SWITCH_TYPES ; int_T * idxOutSw = ( int_T * )
rtDW . c0rfzt21pv . IDX_OUT_SW ; real_T * DxCol = ( real_T * ) rtDW .
c0rfzt21pv . DX_COL ; real_T * tmp2 = ( real_T * ) rtDW . c0rfzt21pv . TMP2 ;
real_T * uswlast = ( real_T * ) rtDW . c0rfzt21pv . USWLAST ; int_T newState
; int_T swChanged = 0 ; int loopsToDo = 20 ; real_T temp ; memcpy (
switch_status_init , switch_status , 4 * sizeof ( int_T ) ) ; memcpy (
uswlast , & rtB . gcul10z3jv [ 0 ] , 4 * sizeof ( real_T ) ) ; do { if (
loopsToDo == 1 ) { swChanged = 0 ; { int_T i1 ; for ( i1 = 0 ; i1 < 4 ; i1 ++
) { swChanged = ( ( SwitchChange [ i1 ] = switch_status_init [ i1 ] -
switch_status [ i1 ] ) != 0 ) ? 1 : swChanged ; switch_status [ i1 ] =
switch_status_init [ i1 ] ; } } } else { real_T * Ds = ( real_T * ) rtDW .
c0rfzt21pv . DS ; { int_T i1 ; real_T * y0 = & rtB . gcul10z3jv [ 0 ] ; for (
i1 = 0 ; i1 < 7 ; i1 ++ ) { accum = 0.0 ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_cvg54ebmbe [ 0 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_cvg54ebmbe [ 1 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_cvg54ebmbe [ 2 ] ; accum += * ( Ds ++ ) * rtP .
SwitchCurrents_Value_cvg54ebmbe [ 3 ] ; accum += * ( Ds ++ ) * rtB .
pho3qpftnj ; y0 [ i1 ] = accum ; } } swChanged = 0 ; newState = gState [ 0 ]
> 0 ? 1 : 0 ; swChanged = ( ( SwitchChange [ 0 ] = newState - switch_status [
0 ] ) != 0 ) ? 1 : swChanged ; switch_status [ 0 ] = newState ; newState =
gState [ 1 ] > 0 ? 1 : 0 ; swChanged = ( ( SwitchChange [ 1 ] = newState -
switch_status [ 1 ] ) != 0 ) ? 1 : swChanged ; switch_status [ 1 ] = newState
; newState = rtB . gcul10z3jv [ 2 ] > 0.0 ? 1 : ( ( rtB . gcul10z3jv [ 2 ] <
0.0 ) ? 0 : switch_status [ 2 ] ) ; swChanged = ( ( SwitchChange [ 2 ] =
newState - switch_status [ 2 ] ) != 0 ) ? 1 : swChanged ; switch_status [ 2 ]
= newState ; newState = rtB . gcul10z3jv [ 3 ] > 0.0 ? 1 : ( ( rtB .
gcul10z3jv [ 3 ] < 0.0 ) ? 0 : switch_status [ 3 ] ) ; swChanged = ( (
SwitchChange [ 3 ] = newState - switch_status [ 3 ] ) != 0 ) ? 1 : swChanged
; switch_status [ 3 ] = newState ; } if ( swChanged ) { real_T * Ds = (
real_T * ) rtDW . c0rfzt21pv . DS ; real_T a1 ; { int_T i1 ; for ( i1 = 0 ;
i1 < 4 ; i1 ++ ) { if ( SwitchChange [ i1 ] != 0 ) { a1 = yswitch [ i1 ] *
SwitchChange [ i1 ] ; temp = 1 / ( 1 - Ds [ i1 * 6 ] * a1 ) ; { int_T i2 ;
for ( i2 = 0 ; i2 < 7 ; i2 ++ ) { DxCol [ i2 ] = Ds [ i2 * 5 + i1 ] * temp *
a1 ; } } DxCol [ i1 ] = temp ; memcpy ( tmp2 , & Ds [ i1 * 5 ] , 5 * sizeof (
real_T ) ) ; memset ( & Ds [ i1 * 5 ] , '\0' , 5 * sizeof ( real_T ) ) ; {
int_T i2 ; for ( i2 = 0 ; i2 < 7 ; i2 ++ ) { a1 = DxCol [ i2 ] ; { int_T i3 ;
for ( i3 = 0 ; i3 < 5 ; i3 ++ ) { Ds [ i2 * 5 + i3 ] += a1 * tmp2 [ i3 ] ; }
} } } } } } } } while ( swChanged > 0 && -- loopsToDo > 0 ) ; if ( loopsToDo
== 0 ) { real_T * Ds = ( real_T * ) rtDW . c0rfzt21pv . DS ; { int_T i1 ;
real_T * y0 = & rtB . gcul10z3jv [ 0 ] ; for ( i1 = 0 ; i1 < 7 ; i1 ++ ) {
accum = 0.0 ; accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value_cvg54ebmbe [
0 ] ; accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value_cvg54ebmbe [ 1 ] ;
accum += * ( Ds ++ ) * rtP . SwitchCurrents_Value_cvg54ebmbe [ 2 ] ; accum +=
* ( Ds ++ ) * rtP . SwitchCurrents_Value_cvg54ebmbe [ 3 ] ; accum += * ( Ds
++ ) * rtB . pho3qpftnj ; y0 [ i1 ] = accum ; } } } rtB . j25efy55r5 [ 0 ] =
( real_T ) switch_status [ 0 ] ; rtB . j25efy55r5 [ 1 ] = ( real_T )
switch_status [ 1 ] ; rtB . j25efy55r5 [ 2 ] = ( real_T ) switch_status [ 2 ]
; rtB . j25efy55r5 [ 3 ] = ( real_T ) switch_status [ 3 ] ; } rtB .
ckf4buvedv = rtP . donotdeletethisgain_Gain * rtB . n1mhwe4wmc [ 199 ] ; rtB
. j1sayi1hcj = rtP . donotdeletethisgain_Gain_obohuwjgss * rtB . n1mhwe4wmc [
99 ] ; if ( ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS
, 0 ) ; ; if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval (
ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) , locTime ) ) {
rt_UpdateLogVar ( ( LogVar * ) ( LogVar * ) ( rtDW . ddhevcuw0f . LoggedData
) , & rtB . j1sayi1hcj , 0 ) ; } } } rtB . crefty5nn2 [ 0 ] = rtB .
mkwy2gpqoc ; rtB . crefty5nn2 [ 1 ] = rtB . ms1xzaxnje ; rtB . crefty5nn2 [ 2
] = rtB . cyub2cqqry ; rtB . crefty5nn2 [ 3 ] = rtB . ips0s3kqvl ; rtB .
crefty5nn2 [ 4 ] = rtB . prsr21hpu4 ; rtB . crefty5nn2 [ 5 ] = rtB .
ggr0l4ju4n ; rtB . crefty5nn2 [ 6 ] = rtB . dvtnssswgf ; rtB . crefty5nn2 [ 7
] = rtB . lylp4o3za1 ; rtB . crefty5nn2 [ 8 ] = rtB . a1obnn0rik ; rtB .
crefty5nn2 [ 9 ] = rtB . gyntgt3u14 ; rtB . crefty5nn2 [ 10 ] = rtB .
fuc132pis2 ; rtB . crefty5nn2 [ 11 ] = rtB . avikq2ugv0 ; rtB . crefty5nn2 [
12 ] = rtB . cjwcu33zih ; rtB . crefty5nn2 [ 13 ] = rtB . c1giyep455 ; rtB .
crefty5nn2 [ 14 ] = rtB . ibm00zzuip ; rtB . crefty5nn2 [ 15 ] = rtB .
c4msc3eeit ; rtB . crefty5nn2 [ 16 ] = rtB . obirrlzjde ; rtB . crefty5nn2 [
17 ] = rtB . fv4mwhqp3p ; rtB . crefty5nn2 [ 18 ] = rtB . fylelfokss ; rtB .
crefty5nn2 [ 19 ] = rtB . eddfok0ttt ; rtB . crefty5nn2 [ 20 ] = rtB .
i2w34spfgq ; rtB . crefty5nn2 [ 21 ] = rtB . mgwpo2euua ; rtB . crefty5nn2 [
22 ] = rtB . ohgmxf2ovd ; rtB . crefty5nn2 [ 23 ] = rtB . c2ydbw2sj0 ; rtB .
crefty5nn2 [ 24 ] = rtB . mmk3xoxflr ; rtB . crefty5nn2 [ 25 ] = rtB .
dawwmoz5xy ; rtB . crefty5nn2 [ 26 ] = rtB . gri0rwhmpf ; rtB . crefty5nn2 [
27 ] = rtB . n1zbzuxb3r ; rtB . crefty5nn2 [ 28 ] = rtB . oypzfi1iso ; rtB .
crefty5nn2 [ 29 ] = rtB . kkmyyic4sz ; rtB . crefty5nn2 [ 30 ] = rtB .
fngwa3baxj ; rtB . crefty5nn2 [ 31 ] = rtB . l5qc2ih1nh ; rtB . crefty5nn2 [
32 ] = rtB . m21rtdprr4 ; rtB . crefty5nn2 [ 33 ] = rtB . ny2kjgfpce ; rtB .
crefty5nn2 [ 34 ] = rtB . mbcc0zmkwz ; rtB . crefty5nn2 [ 35 ] = rtB .
e1vdt0sgzs ; rtB . crefty5nn2 [ 36 ] = rtB . a5ef0qh5ui ; rtB . crefty5nn2 [
37 ] = rtB . emi1eiicwz ; rtB . crefty5nn2 [ 38 ] = rtB . ly2a15pyev ; rtB .
crefty5nn2 [ 39 ] = rtB . afaqeoaxi3 ; rtB . crefty5nn2 [ 40 ] = rtB .
o2vyntsikv ; rtB . crefty5nn2 [ 41 ] = rtB . gh1ihs33dh ; rtB . crefty5nn2 [
42 ] = rtB . bta1zfrbsx ; rtB . crefty5nn2 [ 43 ] = rtB . j0nzc2e04b ; rtB .
crefty5nn2 [ 44 ] = rtB . ilizmh402p ; rtB . crefty5nn2 [ 45 ] = rtB .
mzbg4yn5c1 ; rtB . crefty5nn2 [ 46 ] = rtB . iqbg0iu0hq ; rtB . crefty5nn2 [
47 ] = rtB . mowq1vn4dj ; if ( ssGetLogOutput ( rtS ) ) { { double locTime =
ssGetTaskTime ( rtS , 0 ) ; ; if ( rtwTimeInLoggingInterval (
rtliGetLoggingInterval ( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ,
locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) ( LogVar * ) ( rtDW . eyvapocerz
. LoggedData ) , & rtB . crefty5nn2 [ 0 ] , 0 ) ; } } } if ( ssGetLogOutput (
rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ; if (
rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS ) ->
mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . px5gx0ovdj . LoggedData ) , & rtB . ckf4buvedv , 0 ) ; }
} } rtB . gaaje2saux = rtP . donotdeletethisgain_Gain_b1vlnha0qz * rtB .
n1mhwe4wmc [ 29 ] ; rtB . nxggzjbabc = rtP .
donotdeletethisgain_Gain_nuvitn0upq * rtB . n1mhwe4wmc [ 13 ] ; rtB .
jqcc0mn3f3 = rtP . donotdeletethisgain_Gain_lb23m0prjw * rtB . n1mhwe4wmc [
11 ] ; rtB . jjiiu42bv0 = rtP . donotdeletethisgain_Gain_m0qjxtcre2 * rtB .
n1mhwe4wmc [ 9 ] ; rtB . lbio5fb4ou = rtP .
donotdeletethisgain_Gain_hk5giacacu * rtB . n1mhwe4wmc [ 15 ] ; rtB .
jqxry0xazb = rtP . donotdeletethisgain_Gain_a1x2gitggu * rtB . n1mhwe4wmc [
27 ] ; rtB . ckk3filxf3 = rtP . donotdeletethisgain_Gain_h5woy0ru3e * rtB .
n1mhwe4wmc [ 23 ] ; rtB . eallzlne40 = rtP .
donotdeletethisgain_Gain_ncd3yr52zh * rtB . n1mhwe4wmc [ 21 ] ; rtB .
l0arfstdit = rtP . donotdeletethisgain_Gain_nn34zdc5ca * rtB . n1mhwe4wmc [
19 ] ; rtB . olpn1if10e = rtP . donotdeletethisgain_Gain_nleknairzc * rtB .
n1mhwe4wmc [ 17 ] ; rtB . itefnd2w4j = rtP .
donotdeletethisgain_Gain_bo5dnxkkfq * rtB . n1mhwe4wmc [ 25 ] ; rtB .
asntuwdff0 = rtP . donotdeletethisgain_Gain_b203qkt0rc * rtB . n1mhwe4wmc [ 5
] ; rtB . c4skqe1xnw = rtP . donotdeletethisgain_Gain_j11lmxuq1s * rtB .
n1mhwe4wmc [ 3 ] ; rtB . l1nvprssra = rtP .
donotdeletethisgain_Gain_mf0bb3uaxb * rtB . n1mhwe4wmc [ 1 ] ; rtB .
np5zsj2uej = rtP . donotdeletethisgain_Gain_aludmneo2y * rtB . n1mhwe4wmc [ 7
] ; rtB . maz3ovczmz = rtP . donotdeletethisgain_Gain_itewz5c4d1 * rtB .
n1mhwe4wmc [ 31 ] ; rtB . oquuznjggf = rtP .
donotdeletethisgain_Gain_glgev4gucb * rtB . n1mhwe4wmc [ 62 ] ; rtB .
mpv2aflj0t = rtP . donotdeletethisgain_Gain_ijcbk514vy * rtB . n1mhwe4wmc [
46 ] ; rtB . nxrrqatnc0 = rtP . donotdeletethisgain_Gain_m01b0jky3l * rtB .
n1mhwe4wmc [ 44 ] ; rtB . hbalbktp1c = rtP .
donotdeletethisgain_Gain_dkdqd2msdb * rtB . n1mhwe4wmc [ 42 ] ; rtB .
hoo435luju = rtP . donotdeletethisgain_Gain_fxdq0uyw1l * rtB . n1mhwe4wmc [
48 ] ; rtB . jkwsvbgagi = rtP . donotdeletethisgain_Gain_bljbittfqv * rtB .
n1mhwe4wmc [ 60 ] ; rtB . keanmwalcs = rtP .
donotdeletethisgain_Gain_hicokfbrce * rtB . n1mhwe4wmc [ 56 ] ; rtB .
b2kdpcmjqu = rtP . donotdeletethisgain_Gain_fa4f0n5c15 * rtB . n1mhwe4wmc [
54 ] ; rtB . mwse5jjkay = rtP . donotdeletethisgain_Gain_p22hoda1r3 * rtB .
n1mhwe4wmc [ 52 ] ; rtB . dvf4w152ur = rtP .
donotdeletethisgain_Gain_m0v2z30bgb * rtB . n1mhwe4wmc [ 50 ] ; rtB .
dwfncuecvl = rtP . donotdeletethisgain_Gain_d4hss32n5d * rtB . n1mhwe4wmc [
58 ] ; rtB . je5gfl4unq = rtP . donotdeletethisgain_Gain_asas5kcfxe * rtB .
n1mhwe4wmc [ 38 ] ; rtB . ha2duc3bo5 = rtP .
donotdeletethisgain_Gain_gey1v0mv4f * rtB . n1mhwe4wmc [ 36 ] ; rtB .
ijsq3yotwy = rtP . donotdeletethisgain_Gain_ijbj54nifm * rtB . n1mhwe4wmc [
34 ] ; rtB . ggil01xfur = rtP . donotdeletethisgain_Gain_abjwtqvssf * rtB .
n1mhwe4wmc [ 40 ] ; rtB . erhhpn02rp = rtP .
donotdeletethisgain_Gain_axxuroz1ej * rtB . n1mhwe4wmc [ 64 ] ; rtB .
g3yvot4ehk = rtP . donotdeletethisgain_Gain_o2orwmad0t * rtB . n1mhwe4wmc [
95 ] ; rtB . pets555arx = rtP . donotdeletethisgain_Gain_ioq4qzgaou * rtB .
n1mhwe4wmc [ 79 ] ; rtB . bzgg0ulu4k = rtP .
donotdeletethisgain_Gain_civ1ln1upa * rtB . n1mhwe4wmc [ 77 ] ; rtB .
bflbqg5zak = rtP . donotdeletethisgain_Gain_iztw4m0afw * rtB . n1mhwe4wmc [
75 ] ; rtB . jsagt0mcn5 = rtP . donotdeletethisgain_Gain_elo15k4k0d * rtB .
n1mhwe4wmc [ 81 ] ; rtB . ocdgy2ejgh = rtP .
donotdeletethisgain_Gain_ggpg0yk2ar * rtB . n1mhwe4wmc [ 93 ] ; rtB .
d5dnpexn4t = rtP . donotdeletethisgain_Gain_k2ttslk1on * rtB . n1mhwe4wmc [
89 ] ; rtB . ovli05n5nk = rtP . donotdeletethisgain_Gain_gwiqt05u1s * rtB .
n1mhwe4wmc [ 87 ] ; rtB . nwecho1h3t = rtP .
donotdeletethisgain_Gain_oivqfecjsw * rtB . n1mhwe4wmc [ 85 ] ; rtB .
gnaacobfeo = rtP . donotdeletethisgain_Gain_bttyhm5zhc * rtB . n1mhwe4wmc [
83 ] ; rtB . ijvx2wutld = rtP . donotdeletethisgain_Gain_osbmxzvoso * rtB .
n1mhwe4wmc [ 91 ] ; rtB . oxsptmwoac = rtP .
donotdeletethisgain_Gain_cowxgcq5gc * rtB . n1mhwe4wmc [ 71 ] ; rtB .
fjr0gnghit = rtP . donotdeletethisgain_Gain_cgwizosgxb * rtB . n1mhwe4wmc [
69 ] ; rtB . fdf23q01mz = rtP . donotdeletethisgain_Gain_mhqlonzjzf * rtB .
n1mhwe4wmc [ 67 ] ; rtB . d5t4jwb3c1 = rtP .
donotdeletethisgain_Gain_g0hdv4qsoo * rtB . n1mhwe4wmc [ 73 ] ; rtB .
btljz0bxed = rtP . donotdeletethisgain_Gain_prrv14dslb * rtB . n1mhwe4wmc [
97 ] ; rtB . ic5zg43yv2 [ 0 ] = rtB . gaaje2saux ; rtB . ic5zg43yv2 [ 1 ] =
rtB . nxggzjbabc ; rtB . ic5zg43yv2 [ 2 ] = rtB . jqcc0mn3f3 ; rtB .
ic5zg43yv2 [ 3 ] = rtB . jjiiu42bv0 ; rtB . ic5zg43yv2 [ 4 ] = rtB .
lbio5fb4ou ; rtB . ic5zg43yv2 [ 5 ] = rtB . jqxry0xazb ; rtB . ic5zg43yv2 [ 6
] = rtB . ckk3filxf3 ; rtB . ic5zg43yv2 [ 7 ] = rtB . eallzlne40 ; rtB .
ic5zg43yv2 [ 8 ] = rtB . l0arfstdit ; rtB . ic5zg43yv2 [ 9 ] = rtB .
olpn1if10e ; rtB . ic5zg43yv2 [ 10 ] = rtB . itefnd2w4j ; rtB . ic5zg43yv2 [
11 ] = rtB . asntuwdff0 ; rtB . ic5zg43yv2 [ 12 ] = rtB . c4skqe1xnw ; rtB .
ic5zg43yv2 [ 13 ] = rtB . l1nvprssra ; rtB . ic5zg43yv2 [ 14 ] = rtB .
np5zsj2uej ; rtB . ic5zg43yv2 [ 15 ] = rtB . maz3ovczmz ; rtB . ic5zg43yv2 [
16 ] = rtB . oquuznjggf ; rtB . ic5zg43yv2 [ 17 ] = rtB . mpv2aflj0t ; rtB .
ic5zg43yv2 [ 18 ] = rtB . nxrrqatnc0 ; rtB . ic5zg43yv2 [ 19 ] = rtB .
hbalbktp1c ; rtB . ic5zg43yv2 [ 20 ] = rtB . hoo435luju ; rtB . ic5zg43yv2 [
21 ] = rtB . jkwsvbgagi ; rtB . ic5zg43yv2 [ 22 ] = rtB . keanmwalcs ; rtB .
ic5zg43yv2 [ 23 ] = rtB . b2kdpcmjqu ; rtB . ic5zg43yv2 [ 24 ] = rtB .
mwse5jjkay ; rtB . ic5zg43yv2 [ 25 ] = rtB . dvf4w152ur ; rtB . ic5zg43yv2 [
26 ] = rtB . dwfncuecvl ; rtB . ic5zg43yv2 [ 27 ] = rtB . je5gfl4unq ; rtB .
ic5zg43yv2 [ 28 ] = rtB . ha2duc3bo5 ; rtB . ic5zg43yv2 [ 29 ] = rtB .
ijsq3yotwy ; rtB . ic5zg43yv2 [ 30 ] = rtB . ggil01xfur ; rtB . ic5zg43yv2 [
31 ] = rtB . erhhpn02rp ; rtB . ic5zg43yv2 [ 32 ] = rtB . g3yvot4ehk ; rtB .
ic5zg43yv2 [ 33 ] = rtB . pets555arx ; rtB . ic5zg43yv2 [ 34 ] = rtB .
bzgg0ulu4k ; rtB . ic5zg43yv2 [ 35 ] = rtB . bflbqg5zak ; rtB . ic5zg43yv2 [
36 ] = rtB . jsagt0mcn5 ; rtB . ic5zg43yv2 [ 37 ] = rtB . ocdgy2ejgh ; rtB .
ic5zg43yv2 [ 38 ] = rtB . d5dnpexn4t ; rtB . ic5zg43yv2 [ 39 ] = rtB .
ovli05n5nk ; rtB . ic5zg43yv2 [ 40 ] = rtB . nwecho1h3t ; rtB . ic5zg43yv2 [
41 ] = rtB . gnaacobfeo ; rtB . ic5zg43yv2 [ 42 ] = rtB . ijvx2wutld ; rtB .
ic5zg43yv2 [ 43 ] = rtB . oxsptmwoac ; rtB . ic5zg43yv2 [ 44 ] = rtB .
fjr0gnghit ; rtB . ic5zg43yv2 [ 45 ] = rtB . fdf23q01mz ; rtB . ic5zg43yv2 [
46 ] = rtB . d5t4jwb3c1 ; rtB . ic5zg43yv2 [ 47 ] = rtB . btljz0bxed ; if (
ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ;
if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . lueewoojur . LoggedData ) , & rtB . ic5zg43yv2 [ 0 ] , 0
) ; } } } rtB . gsxszorohl = rtP . donotdeletethisgain_Gain_cj511fcgiy * rtB
. n1mhwe4wmc [ 28 ] ; rtB . n2ccqijupy = rtP .
donotdeletethisgain_Gain_iapeycct4d * rtB . n1mhwe4wmc [ 12 ] ; rtB .
mldsebqwet = rtP . donotdeletethisgain_Gain_phewasapsx * rtB . n1mhwe4wmc [
10 ] ; rtB . e2agy2fsgi = rtP . donotdeletethisgain_Gain_p2oiiegygu * rtB .
n1mhwe4wmc [ 8 ] ; rtB . bxhzyl4d35 = rtP .
donotdeletethisgain_Gain_mdyvsmyybe * rtB . n1mhwe4wmc [ 14 ] ; rtB .
n3egm45yhf = rtP . donotdeletethisgain_Gain_glew5jkhkj * rtB . n1mhwe4wmc [
26 ] ; rtB . mrcdfgxinf = rtP . donotdeletethisgain_Gain_eimquw0n2p * rtB .
n1mhwe4wmc [ 22 ] ; rtB . oensukc05m = rtP .
donotdeletethisgain_Gain_k220czuthw * rtB . n1mhwe4wmc [ 20 ] ; rtB .
pymjjsr2h5 = rtP . donotdeletethisgain_Gain_hmpecviech * rtB . n1mhwe4wmc [
18 ] ; rtB . l0rzxszt5j = rtP . donotdeletethisgain_Gain_g5obetbnok * rtB .
n1mhwe4wmc [ 16 ] ; rtB . cltyk0hpst = rtP .
donotdeletethisgain_Gain_ga0dj5w1ql * rtB . n1mhwe4wmc [ 24 ] ; rtB .
fy1eaz5ugh = rtP . donotdeletethisgain_Gain_binafeuqjh * rtB . n1mhwe4wmc [ 4
] ; rtB . a00pli33gs = rtP . donotdeletethisgain_Gain_eqrhtnxyg5 * rtB .
n1mhwe4wmc [ 2 ] ; rtB . lskivvbef2 = rtP .
donotdeletethisgain_Gain_ddhdsnfkug * rtB . n1mhwe4wmc [ 0 ] ; rtB .
l2l4c054vs = rtP . donotdeletethisgain_Gain_bn45ltk4qb * rtB . n1mhwe4wmc [ 6
] ; rtB . cfkzncdchi = rtP . donotdeletethisgain_Gain_iuotvxc1h1 * rtB .
n1mhwe4wmc [ 30 ] ; rtB . ioiacfjeuz = rtP .
donotdeletethisgain_Gain_ghs3z0xmeg * rtB . n1mhwe4wmc [ 61 ] ; rtB .
ewjasibzpn = rtP . donotdeletethisgain_Gain_bhmvbvx5fo * rtB . n1mhwe4wmc [
45 ] ; rtB . oo50ly4c1k = rtP . donotdeletethisgain_Gain_gkurugewjq * rtB .
n1mhwe4wmc [ 43 ] ; rtB . hchyyvnkfi = rtP .
donotdeletethisgain_Gain_enepvic532 * rtB . n1mhwe4wmc [ 41 ] ; rtB .
mbrzvkgc02 = rtP . donotdeletethisgain_Gain_jzbx1auamj * rtB . n1mhwe4wmc [
47 ] ; rtB . ccx5xshaae = rtP . donotdeletethisgain_Gain_ptpkzxubqz * rtB .
n1mhwe4wmc [ 59 ] ; rtB . jypsvxunzx = rtP .
donotdeletethisgain_Gain_cbhgtkdx0m * rtB . n1mhwe4wmc [ 55 ] ; rtB .
itef1p5z1s = rtP . donotdeletethisgain_Gain_oryxavrjn3 * rtB . n1mhwe4wmc [
53 ] ; rtB . pzh3uohypw = rtP . donotdeletethisgain_Gain_lctmd2znr2 * rtB .
n1mhwe4wmc [ 51 ] ; rtB . l25nn4yd54 = rtP .
donotdeletethisgain_Gain_iglgb33y0r * rtB . n1mhwe4wmc [ 49 ] ; rtB .
gpwh1wrtb0 = rtP . donotdeletethisgain_Gain_m1u2zjf031 * rtB . n1mhwe4wmc [
57 ] ; rtB . g4m0cdodse = rtP . donotdeletethisgain_Gain_noikqhsusm * rtB .
n1mhwe4wmc [ 37 ] ; rtB . hlfbkim2ak = rtP .
donotdeletethisgain_Gain_nx0zyith52 * rtB . n1mhwe4wmc [ 35 ] ; rtB .
c1yqoeyclv = rtP . donotdeletethisgain_Gain_es5fs4t3ls * rtB . n1mhwe4wmc [
33 ] ; rtB . nwzdhzp3uq = rtP . donotdeletethisgain_Gain_p4fuoxyqti * rtB .
n1mhwe4wmc [ 39 ] ; rtB . ioigirnvlb = rtP .
donotdeletethisgain_Gain_niszehu1re * rtB . n1mhwe4wmc [ 63 ] ; rtB .
ky1bn1pban = rtP . donotdeletethisgain_Gain_lokr1wckxt * rtB . n1mhwe4wmc [
94 ] ; rtB . jwugixu4h5 = rtP . donotdeletethisgain_Gain_dlvq1s5iey * rtB .
n1mhwe4wmc [ 78 ] ; rtB . pp2zcnllgu = rtP .
donotdeletethisgain_Gain_jjbgw3phrs * rtB . n1mhwe4wmc [ 76 ] ; rtB .
gqj0yx0geh = rtP . donotdeletethisgain_Gain_ogchx0b4dj * rtB . n1mhwe4wmc [
74 ] ; rtB . dhn2regg4c = rtP . donotdeletethisgain_Gain_apee1afii2 * rtB .
n1mhwe4wmc [ 80 ] ; rtB . khy3xv0wd1 = rtP .
donotdeletethisgain_Gain_ivx4wfvg5y * rtB . n1mhwe4wmc [ 92 ] ; rtB .
oadqy1evwl = rtP . donotdeletethisgain_Gain_f1xclxcrfm * rtB . n1mhwe4wmc [
88 ] ; rtB . gvrb2v4pkg = rtP . donotdeletethisgain_Gain_ntbnnzarjw * rtB .
n1mhwe4wmc [ 86 ] ; rtB . ldh4osun4n = rtP .
donotdeletethisgain_Gain_b5a0squg4y * rtB . n1mhwe4wmc [ 84 ] ; rtB .
e4oygrgmkm = rtP . donotdeletethisgain_Gain_pewmpm0yk1 * rtB . n1mhwe4wmc [
82 ] ; rtB . e0maoawpyc = rtP . donotdeletethisgain_Gain_gre0j2jzp1 * rtB .
n1mhwe4wmc [ 90 ] ; rtB . cofhwf5l21 = rtP .
donotdeletethisgain_Gain_nomggwjlas * rtB . n1mhwe4wmc [ 70 ] ; rtB .
nnqsumxvpu = rtP . donotdeletethisgain_Gain_dp2ym3idox * rtB . n1mhwe4wmc [
68 ] ; rtB . ajxwnd2tik = rtP . donotdeletethisgain_Gain_bmngvaamn1 * rtB .
n1mhwe4wmc [ 66 ] ; rtB . arnfohkdqn = rtP .
donotdeletethisgain_Gain_nxz1clmaov * rtB . n1mhwe4wmc [ 72 ] ; rtB .
otpvmo0dhx = rtP . donotdeletethisgain_Gain_nqio443dnx * rtB . n1mhwe4wmc [
96 ] ; rtB . pi5grrqklm [ 0 ] = rtB . gsxszorohl ; rtB . pi5grrqklm [ 1 ] =
rtB . n2ccqijupy ; rtB . pi5grrqklm [ 2 ] = rtB . mldsebqwet ; rtB .
pi5grrqklm [ 3 ] = rtB . e2agy2fsgi ; rtB . pi5grrqklm [ 4 ] = rtB .
bxhzyl4d35 ; rtB . pi5grrqklm [ 5 ] = rtB . n3egm45yhf ; rtB . pi5grrqklm [ 6
] = rtB . mrcdfgxinf ; rtB . pi5grrqklm [ 7 ] = rtB . oensukc05m ; rtB .
pi5grrqklm [ 8 ] = rtB . pymjjsr2h5 ; rtB . pi5grrqklm [ 9 ] = rtB .
l0rzxszt5j ; rtB . pi5grrqklm [ 10 ] = rtB . cltyk0hpst ; rtB . pi5grrqklm [
11 ] = rtB . fy1eaz5ugh ; rtB . pi5grrqklm [ 12 ] = rtB . a00pli33gs ; rtB .
pi5grrqklm [ 13 ] = rtB . lskivvbef2 ; rtB . pi5grrqklm [ 14 ] = rtB .
l2l4c054vs ; rtB . pi5grrqklm [ 15 ] = rtB . cfkzncdchi ; rtB . pi5grrqklm [
16 ] = rtB . ioiacfjeuz ; rtB . pi5grrqklm [ 17 ] = rtB . ewjasibzpn ; rtB .
pi5grrqklm [ 18 ] = rtB . oo50ly4c1k ; rtB . pi5grrqklm [ 19 ] = rtB .
hchyyvnkfi ; rtB . pi5grrqklm [ 20 ] = rtB . mbrzvkgc02 ; rtB . pi5grrqklm [
21 ] = rtB . ccx5xshaae ; rtB . pi5grrqklm [ 22 ] = rtB . jypsvxunzx ; rtB .
pi5grrqklm [ 23 ] = rtB . itef1p5z1s ; rtB . pi5grrqklm [ 24 ] = rtB .
pzh3uohypw ; rtB . pi5grrqklm [ 25 ] = rtB . l25nn4yd54 ; rtB . pi5grrqklm [
26 ] = rtB . gpwh1wrtb0 ; rtB . pi5grrqklm [ 27 ] = rtB . g4m0cdodse ; rtB .
pi5grrqklm [ 28 ] = rtB . hlfbkim2ak ; rtB . pi5grrqklm [ 29 ] = rtB .
c1yqoeyclv ; rtB . pi5grrqklm [ 30 ] = rtB . nwzdhzp3uq ; rtB . pi5grrqklm [
31 ] = rtB . ioigirnvlb ; rtB . pi5grrqklm [ 32 ] = rtB . ky1bn1pban ; rtB .
pi5grrqklm [ 33 ] = rtB . jwugixu4h5 ; rtB . pi5grrqklm [ 34 ] = rtB .
pp2zcnllgu ; rtB . pi5grrqklm [ 35 ] = rtB . gqj0yx0geh ; rtB . pi5grrqklm [
36 ] = rtB . dhn2regg4c ; rtB . pi5grrqklm [ 37 ] = rtB . khy3xv0wd1 ; rtB .
pi5grrqklm [ 38 ] = rtB . oadqy1evwl ; rtB . pi5grrqklm [ 39 ] = rtB .
gvrb2v4pkg ; rtB . pi5grrqklm [ 40 ] = rtB . ldh4osun4n ; rtB . pi5grrqklm [
41 ] = rtB . e4oygrgmkm ; rtB . pi5grrqklm [ 42 ] = rtB . e0maoawpyc ; rtB .
pi5grrqklm [ 43 ] = rtB . cofhwf5l21 ; rtB . pi5grrqklm [ 44 ] = rtB .
nnqsumxvpu ; rtB . pi5grrqklm [ 45 ] = rtB . ajxwnd2tik ; rtB . pi5grrqklm [
46 ] = rtB . arnfohkdqn ; rtB . pi5grrqklm [ 47 ] = rtB . otpvmo0dhx ; if (
ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ;
if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . ofqo4whqqs . LoggedData ) , & rtB . pi5grrqklm [ 0 ] , 0
) ; } } } rtB . mkpq5rh3fh = rtP . donotdeletethisgain_Gain_kz3impy0o5 * rtB
. n1mhwe4wmc [ 132 ] ; rtB . iexwgqak2h = rtP .
donotdeletethisgain_Gain_iy5t0jtjg2 * rtB . n1mhwe4wmc [ 116 ] ; rtB .
p000k5jvks = rtP . donotdeletethisgain_Gain_kera0fgtk1 * rtB . n1mhwe4wmc [
114 ] ; rtB . atwy10grax = rtP . donotdeletethisgain_Gain_oxxk0ggwu2 * rtB .
n1mhwe4wmc [ 112 ] ; rtB . ls0ljb5vc0 = rtP .
donotdeletethisgain_Gain_leuzskterp * rtB . n1mhwe4wmc [ 118 ] ; rtB .
cv5uczrgts = rtP . donotdeletethisgain_Gain_cw3iibytty * rtB . n1mhwe4wmc [
130 ] ; rtB . b31300zfqr = rtP . donotdeletethisgain_Gain_hlofkijp2p * rtB .
n1mhwe4wmc [ 126 ] ; rtB . imr3yf1vog = rtP .
donotdeletethisgain_Gain_oozobhhmty * rtB . n1mhwe4wmc [ 124 ] ; rtB .
d3qcbjme3b = rtP . donotdeletethisgain_Gain_kdw1ewo4sm * rtB . n1mhwe4wmc [
122 ] ; rtB . fo51whhyuk = rtP . donotdeletethisgain_Gain_dobwp0ddz0 * rtB .
n1mhwe4wmc [ 120 ] ; rtB . pby3qefafo = rtP .
donotdeletethisgain_Gain_hiuigxffxk * rtB . n1mhwe4wmc [ 128 ] ; rtB .
b40x0jqzuo = rtP . donotdeletethisgain_Gain_d1bxizy1a0 * rtB . n1mhwe4wmc [
108 ] ; rtB . paynrqnlln = rtP . donotdeletethisgain_Gain_bpkw5rvl3p * rtB .
n1mhwe4wmc [ 106 ] ; rtB . kymb1j5buj = rtP .
donotdeletethisgain_Gain_nyoxhgu11x * rtB . n1mhwe4wmc [ 104 ] ; rtB .
ike0bqd0s0 = rtP . donotdeletethisgain_Gain_ghqxupels2 * rtB . n1mhwe4wmc [
110 ] ; rtB . hlc4nygesy = rtP . donotdeletethisgain_Gain_lxptv4ateq * rtB .
n1mhwe4wmc [ 134 ] ; rtB . emx3gvk30z = rtP .
donotdeletethisgain_Gain_fwayzqc54u * rtB . n1mhwe4wmc [ 164 ] ; rtB .
j1ywojvfhu = rtP . donotdeletethisgain_Gain_c2rwqk2pjr * rtB . n1mhwe4wmc [
148 ] ; rtB . n3nrykzbk3 = rtP . donotdeletethisgain_Gain_on2nz5fv54 * rtB .
n1mhwe4wmc [ 146 ] ; rtB . hzhzx3w4rd = rtP .
donotdeletethisgain_Gain_mfd0iviez1 * rtB . n1mhwe4wmc [ 144 ] ; rtB .
gxlh0er3yf = rtP . donotdeletethisgain_Gain_ihnlekkko4 * rtB . n1mhwe4wmc [
150 ] ; rtB . cch5sezmlj = rtP . donotdeletethisgain_Gain_iv3spwgekg * rtB .
n1mhwe4wmc [ 162 ] ; rtB . o0sisl31yn = rtP .
donotdeletethisgain_Gain_hztrvffmsx * rtB . n1mhwe4wmc [ 158 ] ; rtB .
nuqe21gcdg = rtP . donotdeletethisgain_Gain_eynhh1wids * rtB . n1mhwe4wmc [
156 ] ; rtB . lulptfdn2v = rtP . donotdeletethisgain_Gain_acy44eylwb * rtB .
n1mhwe4wmc [ 154 ] ; rtB . prxfbd5j0u = rtP .
donotdeletethisgain_Gain_isvokxvpka * rtB . n1mhwe4wmc [ 152 ] ; rtB .
ircuv1shpc = rtP . donotdeletethisgain_Gain_hqgd3vabv0 * rtB . n1mhwe4wmc [
160 ] ; rtB . hc2nh4v2yq = rtP . donotdeletethisgain_Gain_kf4vkd5oqq * rtB .
n1mhwe4wmc [ 140 ] ; rtB . pw5v12y3ow = rtP .
donotdeletethisgain_Gain_m5yraqgtvh * rtB . n1mhwe4wmc [ 138 ] ; rtB .
jzj2j2nzgr = rtP . donotdeletethisgain_Gain_ca23te02jy * rtB . n1mhwe4wmc [
136 ] ; rtB . op0m35r3ke = rtP . donotdeletethisgain_Gain_ctnu3dvcps * rtB .
n1mhwe4wmc [ 142 ] ; rtB . cyz5kb5odh = rtP .
donotdeletethisgain_Gain_oyjofy31su * rtB . n1mhwe4wmc [ 166 ] ; rtB .
ofwowk1umm = rtP . donotdeletethisgain_Gain_dpzma4udiu * rtB . n1mhwe4wmc [
196 ] ; rtB . hnjzpxh21j = rtP . donotdeletethisgain_Gain_pw0bfnybsj * rtB .
n1mhwe4wmc [ 180 ] ; rtB . di5wsdkn0z = rtP .
donotdeletethisgain_Gain_dmtvaeude5 * rtB . n1mhwe4wmc [ 178 ] ; rtB .
id5wqm3ssr = rtP . donotdeletethisgain_Gain_ohc5duyrhl * rtB . n1mhwe4wmc [
176 ] ; rtB . aalyzhw4dl = rtP . donotdeletethisgain_Gain_d5clcu3gww * rtB .
n1mhwe4wmc [ 182 ] ; rtB . avntdifsih = rtP .
donotdeletethisgain_Gain_oxehvnykg4 * rtB . n1mhwe4wmc [ 194 ] ; rtB .
gszo0jhkh2 = rtP . donotdeletethisgain_Gain_kxfqlmbzeu * rtB . n1mhwe4wmc [
190 ] ; rtB . dmm0rk124k = rtP . donotdeletethisgain_Gain_owncio2r3l * rtB .
n1mhwe4wmc [ 188 ] ; rtB . maot34c00s = rtP .
donotdeletethisgain_Gain_buyfl2rlzd * rtB . n1mhwe4wmc [ 186 ] ; rtB .
erwhrbhtkw = rtP . donotdeletethisgain_Gain_a3hhvwgdcu * rtB . n1mhwe4wmc [
184 ] ; rtB . mizmowz2v4 = rtP . donotdeletethisgain_Gain_evjm4r4ikk * rtB .
n1mhwe4wmc [ 192 ] ; rtB . oyhnern4o0 = rtP .
donotdeletethisgain_Gain_kyflm2yldc * rtB . n1mhwe4wmc [ 172 ] ; rtB .
jq5vanxa0o = rtP . donotdeletethisgain_Gain_eir1dm1ep1 * rtB . n1mhwe4wmc [
170 ] ; rtB . gzcxn1z3ei = rtP . donotdeletethisgain_Gain_ing3gu43ry * rtB .
n1mhwe4wmc [ 168 ] ; rtB . lunwnotl00 = rtP .
donotdeletethisgain_Gain_jmsk2u03ix * rtB . n1mhwe4wmc [ 174 ] ; rtB .
pwcmhviyfa = rtP . donotdeletethisgain_Gain_adtqfifx2a * rtB . n1mhwe4wmc [
198 ] ; rtB . i0y1vzmsou [ 0 ] = rtB . mkpq5rh3fh ; rtB . i0y1vzmsou [ 1 ] =
rtB . iexwgqak2h ; rtB . i0y1vzmsou [ 2 ] = rtB . p000k5jvks ; rtB .
i0y1vzmsou [ 3 ] = rtB . atwy10grax ; rtB . i0y1vzmsou [ 4 ] = rtB .
ls0ljb5vc0 ; rtB . i0y1vzmsou [ 5 ] = rtB . cv5uczrgts ; rtB . i0y1vzmsou [ 6
] = rtB . b31300zfqr ; rtB . i0y1vzmsou [ 7 ] = rtB . imr3yf1vog ; rtB .
i0y1vzmsou [ 8 ] = rtB . d3qcbjme3b ; rtB . i0y1vzmsou [ 9 ] = rtB .
fo51whhyuk ; rtB . i0y1vzmsou [ 10 ] = rtB . pby3qefafo ; rtB . i0y1vzmsou [
11 ] = rtB . b40x0jqzuo ; rtB . i0y1vzmsou [ 12 ] = rtB . paynrqnlln ; rtB .
i0y1vzmsou [ 13 ] = rtB . kymb1j5buj ; rtB . i0y1vzmsou [ 14 ] = rtB .
ike0bqd0s0 ; rtB . i0y1vzmsou [ 15 ] = rtB . hlc4nygesy ; rtB . i0y1vzmsou [
16 ] = rtB . emx3gvk30z ; rtB . i0y1vzmsou [ 17 ] = rtB . j1ywojvfhu ; rtB .
i0y1vzmsou [ 18 ] = rtB . n3nrykzbk3 ; rtB . i0y1vzmsou [ 19 ] = rtB .
hzhzx3w4rd ; rtB . i0y1vzmsou [ 20 ] = rtB . gxlh0er3yf ; rtB . i0y1vzmsou [
21 ] = rtB . cch5sezmlj ; rtB . i0y1vzmsou [ 22 ] = rtB . o0sisl31yn ; rtB .
i0y1vzmsou [ 23 ] = rtB . nuqe21gcdg ; rtB . i0y1vzmsou [ 24 ] = rtB .
lulptfdn2v ; rtB . i0y1vzmsou [ 25 ] = rtB . prxfbd5j0u ; rtB . i0y1vzmsou [
26 ] = rtB . ircuv1shpc ; rtB . i0y1vzmsou [ 27 ] = rtB . hc2nh4v2yq ; rtB .
i0y1vzmsou [ 28 ] = rtB . pw5v12y3ow ; rtB . i0y1vzmsou [ 29 ] = rtB .
jzj2j2nzgr ; rtB . i0y1vzmsou [ 30 ] = rtB . op0m35r3ke ; rtB . i0y1vzmsou [
31 ] = rtB . cyz5kb5odh ; rtB . i0y1vzmsou [ 32 ] = rtB . ofwowk1umm ; rtB .
i0y1vzmsou [ 33 ] = rtB . hnjzpxh21j ; rtB . i0y1vzmsou [ 34 ] = rtB .
di5wsdkn0z ; rtB . i0y1vzmsou [ 35 ] = rtB . id5wqm3ssr ; rtB . i0y1vzmsou [
36 ] = rtB . aalyzhw4dl ; rtB . i0y1vzmsou [ 37 ] = rtB . avntdifsih ; rtB .
i0y1vzmsou [ 38 ] = rtB . gszo0jhkh2 ; rtB . i0y1vzmsou [ 39 ] = rtB .
dmm0rk124k ; rtB . i0y1vzmsou [ 40 ] = rtB . maot34c00s ; rtB . i0y1vzmsou [
41 ] = rtB . erwhrbhtkw ; rtB . i0y1vzmsou [ 42 ] = rtB . mizmowz2v4 ; rtB .
i0y1vzmsou [ 43 ] = rtB . oyhnern4o0 ; rtB . i0y1vzmsou [ 44 ] = rtB .
jq5vanxa0o ; rtB . i0y1vzmsou [ 45 ] = rtB . gzcxn1z3ei ; rtB . i0y1vzmsou [
46 ] = rtB . lunwnotl00 ; rtB . i0y1vzmsou [ 47 ] = rtB . pwcmhviyfa ; if (
ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ;
if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . gylheu2quv . LoggedData ) , & rtB . i0y1vzmsou [ 0 ] , 0
) ; } } } rtB . ms3fqtmbzy = muDoubleScalarPower ( rtB . gaaje2saux , 2.0 ) /
4000.0 ; rtB . ksjijdxlja = muDoubleScalarPower ( rtB . nxggzjbabc , 2.0 ) /
1400.0 ; rtB . f2apxwopt1 = muDoubleScalarPower ( rtB . jqcc0mn3f3 , 2.0 ) /
1400.0 ; rtB . etw2weyjzv = muDoubleScalarPower ( rtB . jjiiu42bv0 , 2.0 ) /
1400.0 ; rtB . bvgcgl422b = muDoubleScalarPower ( rtB . lbio5fb4ou , 2.0 ) /
1400.0 ; rtB . fw5jnqnayy = muDoubleScalarPower ( rtB . jqxry0xazb , 2.0 ) /
700.0 ; rtB . ilzljrcbe2 = muDoubleScalarPower ( rtB . ckk3filxf3 , 2.0 ) /
700.0 ; rtB . o2yrfk1fkj = muDoubleScalarPower ( rtB . eallzlne40 , 2.0 ) /
700.0 ; rtB . n5eh1d0iyp = muDoubleScalarPower ( rtB . l0arfstdit , 2.0 ) /
700.0 ; rtB . jiuto5ikn3 = muDoubleScalarPower ( rtB . olpn1if10e , 2.0 ) /
700.0 ; rtB . aqyy3dqtlg = muDoubleScalarPower ( rtB . itefnd2w4j , 2.0 ) /
700.0 ; rtB . mns4wq01ib = muDoubleScalarPower ( rtB . asntuwdff0 , 2.0 ) /
625.0 ; rtB . pszst41gj3 = muDoubleScalarPower ( rtB . c4skqe1xnw , 2.0 ) /
625.0 ; rtB . fiixtzzm4u = muDoubleScalarPower ( rtB . l1nvprssra , 2.0 ) /
625.0 ; rtB . jnpz5olbrg = muDoubleScalarPower ( rtB . np5zsj2uej , 2.0 ) /
625.0 ; rtB . ii1dtwyfdi = muDoubleScalarPower ( rtB . maz3ovczmz , 2.0 ) /
550.0 ; rtB . bd02cblshg = muDoubleScalarPower ( rtB . oquuznjggf , 2.0 ) /
4000.0 ; rtB . jozjyab32g = muDoubleScalarPower ( rtB . mpv2aflj0t , 2.0 ) /
1400.0 ; rtB . nwzgjzcd4a = muDoubleScalarPower ( rtB . nxrrqatnc0 , 2.0 ) /
1400.0 ; rtB . cltl3pae0r = muDoubleScalarPower ( rtB . hbalbktp1c , 2.0 ) /
1400.0 ; rtB . aqi0rmfy15 = muDoubleScalarPower ( rtB . hoo435luju , 2.0 ) /
1400.0 ; rtB . lqzffi3din = muDoubleScalarPower ( rtB . jkwsvbgagi , 2.0 ) /
700.0 ; rtB . fr5br5u2f5 = muDoubleScalarPower ( rtB . keanmwalcs , 2.0 ) /
700.0 ; rtB . pfuawqdjxk = muDoubleScalarPower ( rtB . b2kdpcmjqu , 2.0 ) /
700.0 ; rtB . ohicqhp5c2 = muDoubleScalarPower ( rtB . mwse5jjkay , 2.0 ) /
700.0 ; rtB . br0iuhtcdf = muDoubleScalarPower ( rtB . dvf4w152ur , 2.0 ) /
700.0 ; rtB . hffi0gte1l = muDoubleScalarPower ( rtB . dwfncuecvl , 2.0 ) /
700.0 ; rtB . dsjvii2swn = muDoubleScalarPower ( rtB . je5gfl4unq , 2.0 ) /
625.0 ; rtB . n4wqu3tvya = muDoubleScalarPower ( rtB . ha2duc3bo5 , 2.0 ) /
625.0 ; rtB . pkrzl4zoxn = muDoubleScalarPower ( rtB . ijsq3yotwy , 2.0 ) /
625.0 ; rtB . kddkbetzaa = muDoubleScalarPower ( rtB . ggil01xfur , 2.0 ) /
625.0 ; rtB . olll4vevqf = muDoubleScalarPower ( rtB . erhhpn02rp , 2.0 ) /
550.0 ; rtB . fitezlt4it = muDoubleScalarPower ( rtB . g3yvot4ehk , 2.0 ) /
4000.0 ; rtB . jtkdprrpiq = muDoubleScalarPower ( rtB . pets555arx , 2.0 ) /
1400.0 ; rtB . elruqhu1gw = muDoubleScalarPower ( rtB . bzgg0ulu4k , 2.0 ) /
1400.0 ; rtB . jun2gnnvnq = muDoubleScalarPower ( rtB . bflbqg5zak , 2.0 ) /
1400.0 ; rtB . j1s41mkvck = muDoubleScalarPower ( rtB . jsagt0mcn5 , 2.0 ) /
1400.0 ; rtB . nrmg25w4ui = muDoubleScalarPower ( rtB . ocdgy2ejgh , 2.0 ) /
700.0 ; rtB . enli3ifht0 = muDoubleScalarPower ( rtB . d5dnpexn4t , 2.0 ) /
700.0 ; rtB . prewidi2th = muDoubleScalarPower ( rtB . ovli05n5nk , 2.0 ) /
700.0 ; rtB . mw3gsizyzr = muDoubleScalarPower ( rtB . nwecho1h3t , 2.0 ) /
700.0 ; rtB . hqcrboufif = muDoubleScalarPower ( rtB . gnaacobfeo , 2.0 ) /
700.0 ; rtB . o3orf1lhev = muDoubleScalarPower ( rtB . ijvx2wutld , 2.0 ) /
700.0 ; rtB . babdknai5w = muDoubleScalarPower ( rtB . oxsptmwoac , 2.0 ) /
625.0 ; rtB . ivrc3b4wgo = muDoubleScalarPower ( rtB . fjr0gnghit , 2.0 ) /
625.0 ; rtB . goy21q4l3a = muDoubleScalarPower ( rtB . fdf23q01mz , 2.0 ) /
625.0 ; rtB . ns1xz3nvrk = muDoubleScalarPower ( rtB . d5t4jwb3c1 , 2.0 ) /
625.0 ; rtB . hjelws0phx = muDoubleScalarPower ( rtB . btljz0bxed , 2.0 ) /
550.0 ; rtB . eq4nvgpsqt [ 0 ] = rtB . ms3fqtmbzy ; rtB . eq4nvgpsqt [ 1 ] =
rtB . ksjijdxlja ; rtB . eq4nvgpsqt [ 2 ] = rtB . f2apxwopt1 ; rtB .
eq4nvgpsqt [ 3 ] = rtB . etw2weyjzv ; rtB . eq4nvgpsqt [ 4 ] = rtB .
bvgcgl422b ; rtB . eq4nvgpsqt [ 5 ] = rtB . fw5jnqnayy ; rtB . eq4nvgpsqt [ 6
] = rtB . ilzljrcbe2 ; rtB . eq4nvgpsqt [ 7 ] = rtB . o2yrfk1fkj ; rtB .
eq4nvgpsqt [ 8 ] = rtB . n5eh1d0iyp ; rtB . eq4nvgpsqt [ 9 ] = rtB .
jiuto5ikn3 ; rtB . eq4nvgpsqt [ 10 ] = rtB . aqyy3dqtlg ; rtB . eq4nvgpsqt [
11 ] = rtB . mns4wq01ib ; rtB . eq4nvgpsqt [ 12 ] = rtB . pszst41gj3 ; rtB .
eq4nvgpsqt [ 13 ] = rtB . fiixtzzm4u ; rtB . eq4nvgpsqt [ 14 ] = rtB .
jnpz5olbrg ; rtB . eq4nvgpsqt [ 15 ] = rtB . ii1dtwyfdi ; rtB . eq4nvgpsqt [
16 ] = rtB . bd02cblshg ; rtB . eq4nvgpsqt [ 17 ] = rtB . jozjyab32g ; rtB .
eq4nvgpsqt [ 18 ] = rtB . nwzgjzcd4a ; rtB . eq4nvgpsqt [ 19 ] = rtB .
cltl3pae0r ; rtB . eq4nvgpsqt [ 20 ] = rtB . aqi0rmfy15 ; rtB . eq4nvgpsqt [
21 ] = rtB . lqzffi3din ; rtB . eq4nvgpsqt [ 22 ] = rtB . fr5br5u2f5 ; rtB .
eq4nvgpsqt [ 23 ] = rtB . pfuawqdjxk ; rtB . eq4nvgpsqt [ 24 ] = rtB .
ohicqhp5c2 ; rtB . eq4nvgpsqt [ 25 ] = rtB . br0iuhtcdf ; rtB . eq4nvgpsqt [
26 ] = rtB . hffi0gte1l ; rtB . eq4nvgpsqt [ 27 ] = rtB . dsjvii2swn ; rtB .
eq4nvgpsqt [ 28 ] = rtB . n4wqu3tvya ; rtB . eq4nvgpsqt [ 29 ] = rtB .
pkrzl4zoxn ; rtB . eq4nvgpsqt [ 30 ] = rtB . kddkbetzaa ; rtB . eq4nvgpsqt [
31 ] = rtB . olll4vevqf ; rtB . eq4nvgpsqt [ 32 ] = rtB . fitezlt4it ; rtB .
eq4nvgpsqt [ 33 ] = rtB . jtkdprrpiq ; rtB . eq4nvgpsqt [ 34 ] = rtB .
elruqhu1gw ; rtB . eq4nvgpsqt [ 35 ] = rtB . jun2gnnvnq ; rtB . eq4nvgpsqt [
36 ] = rtB . j1s41mkvck ; rtB . eq4nvgpsqt [ 37 ] = rtB . nrmg25w4ui ; rtB .
eq4nvgpsqt [ 38 ] = rtB . enli3ifht0 ; rtB . eq4nvgpsqt [ 39 ] = rtB .
prewidi2th ; rtB . eq4nvgpsqt [ 40 ] = rtB . mw3gsizyzr ; rtB . eq4nvgpsqt [
41 ] = rtB . hqcrboufif ; rtB . eq4nvgpsqt [ 42 ] = rtB . o3orf1lhev ; rtB .
eq4nvgpsqt [ 43 ] = rtB . babdknai5w ; rtB . eq4nvgpsqt [ 44 ] = rtB .
ivrc3b4wgo ; rtB . eq4nvgpsqt [ 45 ] = rtB . goy21q4l3a ; rtB . eq4nvgpsqt [
46 ] = rtB . ns1xz3nvrk ; rtB . eq4nvgpsqt [ 47 ] = rtB . hjelws0phx ; if (
ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ;
if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . if3oedzqbn . LoggedData ) , & rtB . eq4nvgpsqt [ 0 ] , 0
) ; } } } rtB . cb5bplddfd = muDoubleScalarPower ( rtB . gsxszorohl , 2.0 ) /
rtInf ; rtB . hbrsp534bn = muDoubleScalarPower ( rtB . n2ccqijupy , 2.0 ) /
rtInf ; rtB . in1h0ego2x = muDoubleScalarPower ( rtB . mldsebqwet , 2.0 ) /
rtInf ; rtB . p1hamuzbs1 = muDoubleScalarPower ( rtB . e2agy2fsgi , 2.0 ) /
rtInf ; rtB . a0m3ivax1i = muDoubleScalarPower ( rtB . bxhzyl4d35 , 2.0 ) /
rtInf ; rtB . mtbsqnucli = muDoubleScalarPower ( rtB . n3egm45yhf , 2.0 ) /
rtInf ; rtB . kyftga03p5 = muDoubleScalarPower ( rtB . mrcdfgxinf , 2.0 ) /
rtInf ; rtB . mnwv2scq3z = muDoubleScalarPower ( rtB . oensukc05m , 2.0 ) /
rtInf ; rtB . kxxpxhcmnt = muDoubleScalarPower ( rtB . pymjjsr2h5 , 2.0 ) /
rtInf ; rtB . khgoy3vcpx = muDoubleScalarPower ( rtB . l0rzxszt5j , 2.0 ) /
rtInf ; rtB . gdtjfy2hjl = muDoubleScalarPower ( rtB . cltyk0hpst , 2.0 ) /
rtInf ; rtB . ddkkpvdavs = muDoubleScalarPower ( rtB . fy1eaz5ugh , 2.0 ) /
rtInf ; rtB . ki11dfhlp3 = muDoubleScalarPower ( rtB . a00pli33gs , 2.0 ) /
rtInf ; rtB . b3h3updawf = muDoubleScalarPower ( rtB . lskivvbef2 , 2.0 ) /
rtInf ; rtB . psadjbwlox = muDoubleScalarPower ( rtB . l2l4c054vs , 2.0 ) /
rtInf ; rtB . dxxsvhegqo = muDoubleScalarPower ( rtB . cfkzncdchi , 2.0 ) /
rtInf ; rtB . ixbtpgloc3 = muDoubleScalarPower ( rtB . ioiacfjeuz , 2.0 ) /
rtInf ; rtB . bzufbyxjxm = muDoubleScalarPower ( rtB . ewjasibzpn , 2.0 ) /
rtInf ; rtB . jltuhbz1ng = muDoubleScalarPower ( rtB . oo50ly4c1k , 2.0 ) /
rtInf ; rtB . dfuunegyyb = muDoubleScalarPower ( rtB . hchyyvnkfi , 2.0 ) /
rtInf ; rtB . hble30fuif = muDoubleScalarPower ( rtB . mbrzvkgc02 , 2.0 ) /
rtInf ; rtB . pebcy2vs1v = muDoubleScalarPower ( rtB . ccx5xshaae , 2.0 ) /
rtInf ; rtB . nni5thwzkt = muDoubleScalarPower ( rtB . jypsvxunzx , 2.0 ) /
rtInf ; rtB . kn3iivseuh = muDoubleScalarPower ( rtB . itef1p5z1s , 2.0 ) /
rtInf ; rtB . hkwlx4ea2v = muDoubleScalarPower ( rtB . pzh3uohypw , 2.0 ) /
rtInf ; rtB . lhbedc50xu = muDoubleScalarPower ( rtB . l25nn4yd54 , 2.0 ) /
rtInf ; rtB . glwhbxi53s = muDoubleScalarPower ( rtB . gpwh1wrtb0 , 2.0 ) /
rtInf ; rtB . pf4zj1q4t1 = muDoubleScalarPower ( rtB . g4m0cdodse , 2.0 ) /
rtInf ; rtB . f0a4yf0lk5 = muDoubleScalarPower ( rtB . hlfbkim2ak , 2.0 ) /
rtInf ; rtB . lrud1xdpjt = muDoubleScalarPower ( rtB . c1yqoeyclv , 2.0 ) /
rtInf ; rtB . ky2fvuqm1y = muDoubleScalarPower ( rtB . nwzdhzp3uq , 2.0 ) /
rtInf ; rtB . ley4nikp14 = muDoubleScalarPower ( rtB . ioigirnvlb , 2.0 ) /
rtInf ; rtB . n3snchwran = muDoubleScalarPower ( rtB . ky1bn1pban , 2.0 ) /
rtInf ; rtB . cxpq4nc4vn = muDoubleScalarPower ( rtB . jwugixu4h5 , 2.0 ) /
rtInf ; rtB . i0sd0x2xcu = muDoubleScalarPower ( rtB . pp2zcnllgu , 2.0 ) /
rtInf ; rtB . kkwqqcdfui = muDoubleScalarPower ( rtB . gqj0yx0geh , 2.0 ) /
rtInf ; rtB . jexdxibumh = muDoubleScalarPower ( rtB . dhn2regg4c , 2.0 ) /
rtInf ; rtB . gy0bpvchq3 = muDoubleScalarPower ( rtB . khy3xv0wd1 , 2.0 ) /
rtInf ; rtB . ouv5zxpnrj = muDoubleScalarPower ( rtB . oadqy1evwl , 2.0 ) /
rtInf ; rtB . ho5f4zeh12 = muDoubleScalarPower ( rtB . gvrb2v4pkg , 2.0 ) /
rtInf ; rtB . pvrg3pyvk1 = muDoubleScalarPower ( rtB . ldh4osun4n , 2.0 ) /
rtInf ; rtB . btojk1gmmb = muDoubleScalarPower ( rtB . e4oygrgmkm , 2.0 ) /
rtInf ; rtB . lscnnf54n2 = muDoubleScalarPower ( rtB . e0maoawpyc , 2.0 ) /
rtInf ; rtB . cfcgpqwr5i = muDoubleScalarPower ( rtB . cofhwf5l21 , 2.0 ) /
rtInf ; rtB . hrxdp0hakn = muDoubleScalarPower ( rtB . nnqsumxvpu , 2.0 ) /
rtInf ; rtB . blck5r3jjn = muDoubleScalarPower ( rtB . ajxwnd2tik , 2.0 ) /
rtInf ; rtB . nfcdvdyzvx = muDoubleScalarPower ( rtB . arnfohkdqn , 2.0 ) /
rtInf ; rtB . plprg3he5c = muDoubleScalarPower ( rtB . otpvmo0dhx , 2.0 ) /
rtInf ; rtB . ajn0fnrocr [ 0 ] = rtB . cb5bplddfd ; rtB . ajn0fnrocr [ 1 ] =
rtB . hbrsp534bn ; rtB . ajn0fnrocr [ 2 ] = rtB . in1h0ego2x ; rtB .
ajn0fnrocr [ 3 ] = rtB . p1hamuzbs1 ; rtB . ajn0fnrocr [ 4 ] = rtB .
a0m3ivax1i ; rtB . ajn0fnrocr [ 5 ] = rtB . mtbsqnucli ; rtB . ajn0fnrocr [ 6
] = rtB . kyftga03p5 ; rtB . ajn0fnrocr [ 7 ] = rtB . mnwv2scq3z ; rtB .
ajn0fnrocr [ 8 ] = rtB . kxxpxhcmnt ; rtB . ajn0fnrocr [ 9 ] = rtB .
khgoy3vcpx ; rtB . ajn0fnrocr [ 10 ] = rtB . gdtjfy2hjl ; rtB . ajn0fnrocr [
11 ] = rtB . ddkkpvdavs ; rtB . ajn0fnrocr [ 12 ] = rtB . ki11dfhlp3 ; rtB .
ajn0fnrocr [ 13 ] = rtB . b3h3updawf ; rtB . ajn0fnrocr [ 14 ] = rtB .
psadjbwlox ; rtB . ajn0fnrocr [ 15 ] = rtB . dxxsvhegqo ; rtB . ajn0fnrocr [
16 ] = rtB . ixbtpgloc3 ; rtB . ajn0fnrocr [ 17 ] = rtB . bzufbyxjxm ; rtB .
ajn0fnrocr [ 18 ] = rtB . jltuhbz1ng ; rtB . ajn0fnrocr [ 19 ] = rtB .
dfuunegyyb ; rtB . ajn0fnrocr [ 20 ] = rtB . hble30fuif ; rtB . ajn0fnrocr [
21 ] = rtB . pebcy2vs1v ; rtB . ajn0fnrocr [ 22 ] = rtB . nni5thwzkt ; rtB .
ajn0fnrocr [ 23 ] = rtB . kn3iivseuh ; rtB . ajn0fnrocr [ 24 ] = rtB .
hkwlx4ea2v ; rtB . ajn0fnrocr [ 25 ] = rtB . lhbedc50xu ; rtB . ajn0fnrocr [
26 ] = rtB . glwhbxi53s ; rtB . ajn0fnrocr [ 27 ] = rtB . pf4zj1q4t1 ; rtB .
ajn0fnrocr [ 28 ] = rtB . f0a4yf0lk5 ; rtB . ajn0fnrocr [ 29 ] = rtB .
lrud1xdpjt ; rtB . ajn0fnrocr [ 30 ] = rtB . ky2fvuqm1y ; rtB . ajn0fnrocr [
31 ] = rtB . ley4nikp14 ; rtB . ajn0fnrocr [ 32 ] = rtB . n3snchwran ; rtB .
ajn0fnrocr [ 33 ] = rtB . cxpq4nc4vn ; rtB . ajn0fnrocr [ 34 ] = rtB .
i0sd0x2xcu ; rtB . ajn0fnrocr [ 35 ] = rtB . kkwqqcdfui ; rtB . ajn0fnrocr [
36 ] = rtB . jexdxibumh ; rtB . ajn0fnrocr [ 37 ] = rtB . gy0bpvchq3 ; rtB .
ajn0fnrocr [ 38 ] = rtB . ouv5zxpnrj ; rtB . ajn0fnrocr [ 39 ] = rtB .
ho5f4zeh12 ; rtB . ajn0fnrocr [ 40 ] = rtB . pvrg3pyvk1 ; rtB . ajn0fnrocr [
41 ] = rtB . btojk1gmmb ; rtB . ajn0fnrocr [ 42 ] = rtB . lscnnf54n2 ; rtB .
ajn0fnrocr [ 43 ] = rtB . cfcgpqwr5i ; rtB . ajn0fnrocr [ 44 ] = rtB .
hrxdp0hakn ; rtB . ajn0fnrocr [ 45 ] = rtB . blck5r3jjn ; rtB . ajn0fnrocr [
46 ] = rtB . nfcdvdyzvx ; rtB . ajn0fnrocr [ 47 ] = rtB . plprg3he5c ; if (
ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ;
if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . lnb3lesuo3 . LoggedData ) , & rtB . ajn0fnrocr [ 0 ] , 0
) ; } } } rtB . ggesnqhotd = rtP . donotdeletethisgain_Gain_dkg5s5cdl2 * rtB
. n1mhwe4wmc [ 195 ] ; rtB . hygazcejav = rtP .
donotdeletethisgain_Gain_b1nmh1io45 * rtB . n1mhwe4wmc [ 179 ] ; rtB .
dvcpuw2gcg = rtP . donotdeletethisgain_Gain_pcvryixazn * rtB . n1mhwe4wmc [
177 ] ; rtB . eyq0352y4b = rtP . donotdeletethisgain_Gain_jafdhhs0lb * rtB .
n1mhwe4wmc [ 175 ] ; rtB . fb034lljpa = rtP .
donotdeletethisgain_Gain_fi4yl500ia * rtB . n1mhwe4wmc [ 181 ] ; rtB .
ktjovoyk0g = rtP . donotdeletethisgain_Gain_hrs2erwflr * rtB . n1mhwe4wmc [
193 ] ; rtB . hpxnxzplmr = rtP . donotdeletethisgain_Gain_cloarruovm * rtB .
n1mhwe4wmc [ 189 ] ; rtB . ffvwwrkkbq = rtP .
donotdeletethisgain_Gain_n4xqqxek55 * rtB . n1mhwe4wmc [ 187 ] ; rtB .
bxwn3g3gd2 = rtP . donotdeletethisgain_Gain_nygb0p3yi3 * rtB . n1mhwe4wmc [
185 ] ; rtB . lrh4dm0esj = rtP . donotdeletethisgain_Gain_hxdkmh0hey * rtB .
n1mhwe4wmc [ 183 ] ; rtB . bo4d45gozu = rtP .
donotdeletethisgain_Gain_obixcn5wst * rtB . n1mhwe4wmc [ 191 ] ; rtB .
eqv1b3nirq = rtP . donotdeletethisgain_Gain_g0pra3nmnu * rtB . n1mhwe4wmc [
171 ] ; rtB . n5sesfdozg = rtP . donotdeletethisgain_Gain_llilrh0ovw * rtB .
n1mhwe4wmc [ 169 ] ; rtB . kfysu30hud = rtP .
donotdeletethisgain_Gain_me434ppbiu * rtB . n1mhwe4wmc [ 167 ] ; rtB .
bghrytf3d3 = rtP . donotdeletethisgain_Gain_n2byqwxdmv * rtB . n1mhwe4wmc [
173 ] ; rtB . cwmmeaoh43 = rtP . donotdeletethisgain_Gain_d0ci3mxljq * rtB .
n1mhwe4wmc [ 197 ] ; rtB . ezlkzekgrb = rtP .
donotdeletethisgain_Gain_gf5dodj4i0 * rtB . n1mhwe4wmc [ 163 ] ; rtB .
emmmp3iou5 = rtP . donotdeletethisgain_Gain_b2xb3y2voo * rtB . n1mhwe4wmc [
147 ] ; rtB . fei1k5hpwa = rtP . donotdeletethisgain_Gain_jni0gdbaox * rtB .
n1mhwe4wmc [ 145 ] ; rtB . a20g3v5czr = rtP .
donotdeletethisgain_Gain_hw001uqwp1 * rtB . n1mhwe4wmc [ 143 ] ; rtB .
hox2qskch1 = rtP . donotdeletethisgain_Gain_cnu4b5znzw * rtB . n1mhwe4wmc [
149 ] ; rtB . d5vlayglg2 = rtP . donotdeletethisgain_Gain_l05iijs0th * rtB .
n1mhwe4wmc [ 161 ] ; rtB . iw5uxkz3im = rtP .
donotdeletethisgain_Gain_pfe53xznqx * rtB . n1mhwe4wmc [ 157 ] ; rtB .
gis5yf1fp0 = rtP . donotdeletethisgain_Gain_n4drsgqyl5 * rtB . n1mhwe4wmc [
155 ] ; rtB . aw2tfpcqr1 = rtP . donotdeletethisgain_Gain_ll2zr5yoca * rtB .
n1mhwe4wmc [ 153 ] ; rtB . cnhnznikot = rtP .
donotdeletethisgain_Gain_l43sbscuur * rtB . n1mhwe4wmc [ 151 ] ; rtB .
brb1dhzt5b = rtP . donotdeletethisgain_Gain_nubqbodbbt * rtB . n1mhwe4wmc [
159 ] ; rtB . h3sw0orbwy = rtP . donotdeletethisgain_Gain_gso5sj2vq2 * rtB .
n1mhwe4wmc [ 139 ] ; rtB . arpfqcrhaw = rtP .
donotdeletethisgain_Gain_kipk4xhyhr * rtB . n1mhwe4wmc [ 137 ] ; rtB .
ouo45ol4bp = rtP . donotdeletethisgain_Gain_edeuujq0z5 * rtB . n1mhwe4wmc [
135 ] ; rtB . ghrxwu1hvu = rtP . donotdeletethisgain_Gain_ooigdqvz3e * rtB .
n1mhwe4wmc [ 141 ] ; rtB . h5cvkxxrx1 = rtP .
donotdeletethisgain_Gain_kuysd0ojq4 * rtB . n1mhwe4wmc [ 165 ] ; rtB .
ehr3eziagk = rtP . donotdeletethisgain_Gain_el1iclqdfx * rtB . n1mhwe4wmc [
131 ] ; rtB . csb33yvtf2 = rtP . donotdeletethisgain_Gain_l2pasymtsp * rtB .
n1mhwe4wmc [ 115 ] ; rtB . dx0drx3jqi = rtP .
donotdeletethisgain_Gain_bbbk5pvmp5 * rtB . n1mhwe4wmc [ 113 ] ; rtB .
lf5qf2q3cc = rtP . donotdeletethisgain_Gain_mlf5lwjcds * rtB . n1mhwe4wmc [
111 ] ; rtB . mmdvwqak4r = rtP . donotdeletethisgain_Gain_mc13kushyj * rtB .
n1mhwe4wmc [ 117 ] ; rtB . nixlqel1rp = rtP .
donotdeletethisgain_Gain_n13y04ukvo * rtB . n1mhwe4wmc [ 129 ] ; rtB .
l31qpehim0 = rtP . donotdeletethisgain_Gain_lnieqh1p50 * rtB . n1mhwe4wmc [
125 ] ; rtB . lj44jlwn14 = rtP . donotdeletethisgain_Gain_ab40labhkn * rtB .
n1mhwe4wmc [ 123 ] ; rtB . o3qotdi3uh = rtP .
donotdeletethisgain_Gain_km5wnojdkf * rtB . n1mhwe4wmc [ 121 ] ; rtB .
d3d5fdshct = rtP . donotdeletethisgain_Gain_k01w0rjihl * rtB . n1mhwe4wmc [
119 ] ; rtB . aenhpcucwt = rtP . donotdeletethisgain_Gain_k2buuoccz5 * rtB .
n1mhwe4wmc [ 127 ] ; rtB . o5hdhu3lyq = rtP .
donotdeletethisgain_Gain_ombnlmn0ed * rtB . n1mhwe4wmc [ 107 ] ; rtB .
hz42dhcvx3 = rtP . donotdeletethisgain_Gain_kdgmvhifpu * rtB . n1mhwe4wmc [
105 ] ; rtB . blk5t4lbmv = rtP . donotdeletethisgain_Gain_duvenjhxrn * rtB .
n1mhwe4wmc [ 103 ] ; rtB . ldbihd0pay = rtP .
donotdeletethisgain_Gain_l5sxpthpku * rtB . n1mhwe4wmc [ 109 ] ; rtB .
mg3ocxel2q = rtP . donotdeletethisgain_Gain_kho2ggotif * rtB . n1mhwe4wmc [
133 ] ; rtB . js1e3qr2m1 [ 0 ] = rtB . ggesnqhotd ; rtB . js1e3qr2m1 [ 1 ] =
rtB . hygazcejav ; rtB . js1e3qr2m1 [ 2 ] = rtB . dvcpuw2gcg ; rtB .
js1e3qr2m1 [ 3 ] = rtB . eyq0352y4b ; rtB . js1e3qr2m1 [ 4 ] = rtB .
fb034lljpa ; rtB . js1e3qr2m1 [ 5 ] = rtB . ktjovoyk0g ; rtB . js1e3qr2m1 [ 6
] = rtB . hpxnxzplmr ; rtB . js1e3qr2m1 [ 7 ] = rtB . ffvwwrkkbq ; rtB .
js1e3qr2m1 [ 8 ] = rtB . bxwn3g3gd2 ; rtB . js1e3qr2m1 [ 9 ] = rtB .
lrh4dm0esj ; rtB . js1e3qr2m1 [ 10 ] = rtB . bo4d45gozu ; rtB . js1e3qr2m1 [
11 ] = rtB . eqv1b3nirq ; rtB . js1e3qr2m1 [ 12 ] = rtB . n5sesfdozg ; rtB .
js1e3qr2m1 [ 13 ] = rtB . kfysu30hud ; rtB . js1e3qr2m1 [ 14 ] = rtB .
bghrytf3d3 ; rtB . js1e3qr2m1 [ 15 ] = rtB . cwmmeaoh43 ; rtB . js1e3qr2m1 [
16 ] = rtB . ezlkzekgrb ; rtB . js1e3qr2m1 [ 17 ] = rtB . emmmp3iou5 ; rtB .
js1e3qr2m1 [ 18 ] = rtB . fei1k5hpwa ; rtB . js1e3qr2m1 [ 19 ] = rtB .
a20g3v5czr ; rtB . js1e3qr2m1 [ 20 ] = rtB . hox2qskch1 ; rtB . js1e3qr2m1 [
21 ] = rtB . d5vlayglg2 ; rtB . js1e3qr2m1 [ 22 ] = rtB . iw5uxkz3im ; rtB .
js1e3qr2m1 [ 23 ] = rtB . gis5yf1fp0 ; rtB . js1e3qr2m1 [ 24 ] = rtB .
aw2tfpcqr1 ; rtB . js1e3qr2m1 [ 25 ] = rtB . cnhnznikot ; rtB . js1e3qr2m1 [
26 ] = rtB . brb1dhzt5b ; rtB . js1e3qr2m1 [ 27 ] = rtB . h3sw0orbwy ; rtB .
js1e3qr2m1 [ 28 ] = rtB . arpfqcrhaw ; rtB . js1e3qr2m1 [ 29 ] = rtB .
ouo45ol4bp ; rtB . js1e3qr2m1 [ 30 ] = rtB . ghrxwu1hvu ; rtB . js1e3qr2m1 [
31 ] = rtB . h5cvkxxrx1 ; rtB . js1e3qr2m1 [ 32 ] = rtB . ehr3eziagk ; rtB .
js1e3qr2m1 [ 33 ] = rtB . csb33yvtf2 ; rtB . js1e3qr2m1 [ 34 ] = rtB .
dx0drx3jqi ; rtB . js1e3qr2m1 [ 35 ] = rtB . lf5qf2q3cc ; rtB . js1e3qr2m1 [
36 ] = rtB . mmdvwqak4r ; rtB . js1e3qr2m1 [ 37 ] = rtB . nixlqel1rp ; rtB .
js1e3qr2m1 [ 38 ] = rtB . l31qpehim0 ; rtB . js1e3qr2m1 [ 39 ] = rtB .
lj44jlwn14 ; rtB . js1e3qr2m1 [ 40 ] = rtB . o3qotdi3uh ; rtB . js1e3qr2m1 [
41 ] = rtB . d3d5fdshct ; rtB . js1e3qr2m1 [ 42 ] = rtB . aenhpcucwt ; rtB .
js1e3qr2m1 [ 43 ] = rtB . o5hdhu3lyq ; rtB . js1e3qr2m1 [ 44 ] = rtB .
hz42dhcvx3 ; rtB . js1e3qr2m1 [ 45 ] = rtB . blk5t4lbmv ; rtB . js1e3qr2m1 [
46 ] = rtB . ldbihd0pay ; rtB . js1e3qr2m1 [ 47 ] = rtB . mg3ocxel2q ; if (
ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ;
if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . jydkx4dopc . LoggedData ) , & rtB . js1e3qr2m1 [ 0 ] , 0
) ; } } } rtB . k2usimljyx [ 0 ] = rtB . azjmzqd3vb ; rtB . k2usimljyx [ 1 ]
= rtB . gmbaq2fbjb ; rtB . k2usimljyx [ 2 ] = rtB . h0gqs1nhdm ; rtB .
k2usimljyx [ 3 ] = rtB . mjdat5hd2e ; rtB . k2usimljyx [ 4 ] = rtB .
lhuj2gsrko ; rtB . k2usimljyx [ 5 ] = rtB . kxm5w2htjt ; rtB . k2usimljyx [ 6
] = rtB . okyxtfo4ko ; rtB . k2usimljyx [ 7 ] = rtB . bpzq12sk1y ; rtB .
k2usimljyx [ 8 ] = rtB . nmztaq5xza ; rtB . k2usimljyx [ 9 ] = rtB .
nmdxbbj1gj ; rtB . k2usimljyx [ 10 ] = rtB . duawl3zq0w ; rtB . k2usimljyx [
11 ] = rtB . irqllizifh ; rtB . k2usimljyx [ 12 ] = rtB . abcg0jvxu2 ; rtB .
k2usimljyx [ 13 ] = rtB . lhv3fabtry ; rtB . k2usimljyx [ 14 ] = rtB .
jagy2oxlxs ; rtB . k2usimljyx [ 15 ] = rtB . b1cj1hxqcp ; rtB . k2usimljyx [
16 ] = rtB . mmuxgctkpa ; rtB . k2usimljyx [ 17 ] = rtB . nhyg4avrjq ; rtB .
k2usimljyx [ 18 ] = rtB . ptb4abw35t ; rtB . k2usimljyx [ 19 ] = rtB .
astupp0ykj ; rtB . k2usimljyx [ 20 ] = rtB . bxevyg1qfv ; rtB . k2usimljyx [
21 ] = rtB . bsyf5qnqlq ; rtB . k2usimljyx [ 22 ] = rtB . pqe4h0mldk ; rtB .
k2usimljyx [ 23 ] = rtB . oabhgyaqej ; rtB . k2usimljyx [ 24 ] = rtB .
f30of2biun ; rtB . k2usimljyx [ 25 ] = rtB . isnln11ygz ; rtB . k2usimljyx [
26 ] = rtB . eqca5yhlwz ; rtB . k2usimljyx [ 27 ] = rtB . oiu1puuk0r ; rtB .
k2usimljyx [ 28 ] = rtB . hpa1cu2ml4 ; rtB . k2usimljyx [ 29 ] = rtB .
nonqf4a0km ; rtB . k2usimljyx [ 30 ] = rtB . n4ec24vcv4 ; rtB . k2usimljyx [
31 ] = rtB . mfnrp4nocv ; rtB . k2usimljyx [ 32 ] = rtB . prob4hxsnz ; rtB .
k2usimljyx [ 33 ] = rtB . nojsqgyym0 ; rtB . k2usimljyx [ 34 ] = rtB .
gi5vxvkn1l ; rtB . k2usimljyx [ 35 ] = rtB . j1jg4ps3pb ; rtB . k2usimljyx [
36 ] = rtB . mrb1fq2yah ; rtB . k2usimljyx [ 37 ] = rtB . f20ue4bczk ; rtB .
k2usimljyx [ 38 ] = rtB . a2ugtljmkq ; rtB . k2usimljyx [ 39 ] = rtB .
gvyaxp1jds ; rtB . k2usimljyx [ 40 ] = rtB . ll0aghnbw3 ; rtB . k2usimljyx [
41 ] = rtB . hkmm0vso4o ; rtB . k2usimljyx [ 42 ] = rtB . kcaeorhfgi ; rtB .
k2usimljyx [ 43 ] = rtB . cj5l40duds ; rtB . k2usimljyx [ 44 ] = rtB .
idkhic3gum ; rtB . k2usimljyx [ 45 ] = rtB . cmcorjnw34 ; rtB . k2usimljyx [
46 ] = rtB . eqps0gcjjy ; rtB . k2usimljyx [ 47 ] = rtB . opcvbfbu0a ; if (
ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ;
if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . f4ppq3cqy3 . LoggedData ) , & rtB . k2usimljyx [ 0 ] , 0
) ; } } } rtB . n432pxj0nf [ 0 ] = rtB . c5am1xxeyp ; rtB . n432pxj0nf [ 1 ]
= rtB . ltvkuhvonr ; rtB . n432pxj0nf [ 2 ] = rtB . mrfoka5crq ; rtB .
n432pxj0nf [ 3 ] = rtB . hzj3ghd3ti ; rtB . n432pxj0nf [ 4 ] = rtB .
kd315mesw4 ; rtB . n432pxj0nf [ 5 ] = rtB . g35mjbeqs3 ; rtB . n432pxj0nf [ 6
] = rtB . dtu3mjgum2 ; rtB . n432pxj0nf [ 7 ] = rtB . oevtjor0u3 ; rtB .
n432pxj0nf [ 8 ] = rtB . ipjqzabc30 ; rtB . n432pxj0nf [ 9 ] = rtB .
oopq5yauzv ; rtB . n432pxj0nf [ 10 ] = rtB . hwri03ubr2 ; rtB . n432pxj0nf [
11 ] = rtB . hroaolzuga ; rtB . n432pxj0nf [ 12 ] = rtB . omo0odknr4 ; rtB .
n432pxj0nf [ 13 ] = rtB . dawcyvu3ar ; rtB . n432pxj0nf [ 14 ] = rtB .
dzqdbynuky ; rtB . n432pxj0nf [ 15 ] = rtB . lgeiac2zcg ; rtB . n432pxj0nf [
16 ] = rtB . f2azip3nkv ; rtB . n432pxj0nf [ 17 ] = rtB . nejc01f2yj ; rtB .
n432pxj0nf [ 18 ] = rtB . exxy3crrss ; rtB . n432pxj0nf [ 19 ] = rtB .
mbeg3v5z5m ; rtB . n432pxj0nf [ 20 ] = rtB . fu4duvs1oh ; rtB . n432pxj0nf [
21 ] = rtB . ebzmfciyvp ; rtB . n432pxj0nf [ 22 ] = rtB . i0jcfar22j ; rtB .
n432pxj0nf [ 23 ] = rtB . bgtvlmqb0i ; rtB . n432pxj0nf [ 24 ] = rtB .
b2jrj4aug2 ; rtB . n432pxj0nf [ 25 ] = rtB . ikwdhesgqr ; rtB . n432pxj0nf [
26 ] = rtB . glumzkv1kv ; rtB . n432pxj0nf [ 27 ] = rtB . ftjkvl0ttv ; rtB .
n432pxj0nf [ 28 ] = rtB . gt5qnx3oug ; rtB . n432pxj0nf [ 29 ] = rtB .
fq04nnejal ; rtB . n432pxj0nf [ 30 ] = rtB . nz1n2dwtmm ; rtB . n432pxj0nf [
31 ] = rtB . hcm40myr01 ; rtB . n432pxj0nf [ 32 ] = rtB . hkuzgnbjbt ; rtB .
n432pxj0nf [ 33 ] = rtB . oi4qaxezfh ; rtB . n432pxj0nf [ 34 ] = rtB .
a4gf2pw04z ; rtB . n432pxj0nf [ 35 ] = rtB . lluqlqnbie ; rtB . n432pxj0nf [
36 ] = rtB . geucbkz3sb ; rtB . n432pxj0nf [ 37 ] = rtB . dy5jvvwh21 ; rtB .
n432pxj0nf [ 38 ] = rtB . at3grkcr0i ; rtB . n432pxj0nf [ 39 ] = rtB .
nclby2bt4t ; rtB . n432pxj0nf [ 40 ] = rtB . cxic31gs5o ; rtB . n432pxj0nf [
41 ] = rtB . bj0j0lkfw3 ; rtB . n432pxj0nf [ 42 ] = rtB . o3nf12o3kv ; rtB .
n432pxj0nf [ 43 ] = rtB . cb5qphbn0v ; rtB . n432pxj0nf [ 44 ] = rtB .
g0c4aqlyry ; rtB . n432pxj0nf [ 45 ] = rtB . pwg5klf2pi ; rtB . n432pxj0nf [
46 ] = rtB . kv203gp00h ; rtB . n432pxj0nf [ 47 ] = rtB . n0yawwlhtp ; if (
ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ;
if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . g1bsp2ezz4 . LoggedData ) , & rtB . n432pxj0nf [ 0 ] , 0
) ; } } } rtB . gdizqui00u = rtP . donotdeletethisgain_Gain_nvchqkvmz2 * rtB
. n1mhwe4wmc [ 32 ] ; rtB . iaf3qnvwai = rtP .
donotdeletethisgain_Gain_azjczsk010 * rtB . n1mhwe4wmc [ 65 ] ; rtB .
ppwfshiqbj = rtP . donotdeletethisgain_Gain_a5gf31oycn * rtB . n1mhwe4wmc [
98 ] ; ewm2wjscso = rtP . Constant_Value_mosvjmb1hb - rtB . j1sayi1hcj ;
hnubxhm4oh = rtP . DiscretePIDController_P * ewm2wjscso + rtDW . kvdcvco01e ;
if ( hnubxhm4oh > rtP . DiscretePIDController_UpperSaturationLimit ) { rtB .
dtgcbug2z1 = rtP . DiscretePIDController_UpperSaturationLimit ; } else if (
hnubxhm4oh < rtP . DiscretePIDController_LowerSaturationLimit ) { rtB .
dtgcbug2z1 = rtP . DiscretePIDController_LowerSaturationLimit ; } else { rtB
. dtgcbug2z1 = hnubxhm4oh ; } rtB . jajcvm3ojj = rtP .
DiscretePIDController_I * ewm2wjscso ; hnubxhm4oh = ( 1.0 - kbrlz2zmlx / (
rtP . R4_Gain * rtDW . lwfztydmov ) ) * 100.0 ; if ( hnubxhm4oh > rtP .
Saturation_UpperSat_l1aalue1xm ) { rtB . fpw2s2zwfo = rtP .
Saturation_UpperSat_l1aalue1xm ; } else if ( hnubxhm4oh < rtP .
Saturation_LowerSat_ahqe14vvdn ) { rtB . fpw2s2zwfo = rtP .
Saturation_LowerSat_ahqe14vvdn ; } else { rtB . fpw2s2zwfo = hnubxhm4oh ; }
hnubxhm4oh = ( 1.0 - n40x4vvcy0 / ( rtP . R4_Gain_fvualtirrk * rtDW .
jnwgqfjczs ) ) * 100.0 ; if ( hnubxhm4oh > rtP .
Saturation_UpperSat_m5wqmy2wvb ) { rtB . b3j431g3ib = rtP .
Saturation_UpperSat_m5wqmy2wvb ; } else if ( hnubxhm4oh < rtP .
Saturation_LowerSat_hafs0jsxl2 ) { rtB . b3j431g3ib = rtP .
Saturation_LowerSat_hafs0jsxl2 ; } else { rtB . b3j431g3ib = hnubxhm4oh ; }
hnubxhm4oh = ( 1.0 - n4vvs0yp2i / ( rtP . R4_Gain_ngs4v0tqro * rtDW .
aircger2rx ) ) * 100.0 ; if ( hnubxhm4oh > rtP .
Saturation_UpperSat_inwjpiolqw ) { rtB . jajiwpdbda = rtP .
Saturation_UpperSat_inwjpiolqw ; } else if ( hnubxhm4oh < rtP .
Saturation_LowerSat_e1ft3qe2jg ) { rtB . jajiwpdbda = rtP .
Saturation_LowerSat_e1ft3qe2jg ; } else { rtB . jajiwpdbda = hnubxhm4oh ; }
rtB . ijqf2bh5go [ 0 ] = rtB . fpw2s2zwfo ; rtB . ijqf2bh5go [ 1 ] = rtB .
b3j431g3ib ; rtB . ijqf2bh5go [ 2 ] = rtB . jajiwpdbda ; if ( ssGetLogOutput
( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ; if (
rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS ) ->
mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . eosjvmtbk2 . LoggedData ) , & rtB . ijqf2bh5go [ 0 ] , 0
) ; } } } rtB . nqrdiqgjxm = rtP . donotdeletethisgain_Gain_lmp34xyxo4 * rtB
. n1mhwe4wmc [ 100 ] ; rtB . edbedwxht5 = ( ( real_T ) ( rtB . nqrdiqgjxm <
rtP . Constant_Value_iv1x2w0vhv ) * rtP . Gain4_Gain - rtDW . lnyxns4prr ) *
muDoubleScalarAbs ( rtB . nqrdiqgjxm ) * rtP . Gain1_Gain ; rtB . ouitoiyxuf
= rtP . Gain2_Gain * kbrlz2zmlx ; rtB . lwwgzcjoh5 = rtP . R1_Gain * rtB .
nqrdiqgjxm ; rtB . htnfuvkgid = rtP . donotdeletethisgain_Gain_lj1umhddk1 *
rtB . n1mhwe4wmc [ 101 ] ; rtB . gt2e0gwhn0 = ( ( real_T ) ( rtB . htnfuvkgid
< rtP . Constant_Value_d130ln2l0i ) * rtP . Gain4_Gain_fg3tbxrfed - rtDW .
nb1buv1zor ) * muDoubleScalarAbs ( rtB . htnfuvkgid ) * rtP .
Gain1_Gain_dkplgji4xo ; rtB . kod4h1025c = rtP . Gain2_Gain_ch1egfs2zt *
n40x4vvcy0 ; rtB . gye3zy1a0f = rtP . R1_Gain_ay1qzu5q5s * rtB . htnfuvkgid ;
rtB . mgmgpzdaim = rtP . donotdeletethisgain_Gain_fujasp51dg * rtB .
n1mhwe4wmc [ 102 ] ; rtB . kpjwqjmfqs = ( ( real_T ) ( rtB . mgmgpzdaim < rtP
. Constant_Value_l5znadynca ) * rtP . Gain4_Gain_bhqc4zvc0o - rtDW .
fb5x1hmdio ) * muDoubleScalarAbs ( rtB . mgmgpzdaim ) * rtP .
Gain1_Gain_fehlu53xbm ; rtB . dv2i5nazyy = rtP . Gain2_Gain_oua2wdl3jq *
n4vvs0yp2i ; rtB . fnwh3t55no = rtP . R1_Gain_m3pcmnlsvx * rtB . mgmgpzdaim ;
rtB . kawbvnvky3 = rtP . donotdeletethisgain_Gain_mv43u43iy2 * rtB .
ozjanvc1ks [ 5 ] ; rtB . kzusmmwb1m = rtP .
donotdeletethisgain_Gain_hjdhufs4gw * rtB . c4oldjnq3u [ 6 ] ; rtB .
ppxw152mhu = rtP . donotdeletethisgain_Gain_fyq14ev0bb * rtB . gcul10z3jv [ 6
] ; rtB . lyfqv1evtf [ 0 ] = rtB . kawbvnvky3 ; rtB . lyfqv1evtf [ 1 ] = rtB
. kzusmmwb1m ; rtB . lyfqv1evtf [ 2 ] = rtB . ppxw152mhu ; if (
ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ;
if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . cuayv55s4x . LoggedData ) , & rtB . lyfqv1evtf [ 0 ] , 0
) ; } } } kbrlz2zmlx = rtP . donotdeletethisgain_Gain_h2k1sdxt4c * rtB .
ozjanvc1ks [ 4 ] ; ewm2wjscso = ( real_T ) rtP . Gain1_Gain_af21rfcgee *
0.03125 * ( real_T ) ( kbrlz2zmlx < rtP . ProtectionCircuit_v_min ) + (
real_T ) rtP . Gain_Gain_fthgv1ydo1 * 0.03125 * ( real_T ) ( kbrlz2zmlx > rtP
. ProtectionCircuit_v_cut ) ; kbrlz2zmlx = ewm2wjscso - rtDW . bo3uxetgss ;
if ( kbrlz2zmlx > rtP . RateLimiter_RisingLim ) { kbrlz2zmlx = rtDW .
bo3uxetgss + rtP . RateLimiter_RisingLim ; } else if ( kbrlz2zmlx < rtP .
RateLimiter_FallingLim ) { kbrlz2zmlx = rtDW . bo3uxetgss + rtP .
RateLimiter_FallingLim ; } else { kbrlz2zmlx = ewm2wjscso ; } rtDW .
bo3uxetgss = kbrlz2zmlx ; rtB . fpbsng3i4c = rtP . Gain2_Gain_gka1vktrhi *
kbrlz2zmlx ; rtB . enkm4ifchy = rtP . donotdeletethisgain_Gain_i0aw0qrr1j *
rtB . c4oldjnq3u [ 5 ] ; rtB . bojcrrwkcj = ( ( real_T ) ( rtB . enkm4ifchy <
rtP . Constant_Value_hjzwahl0rv ) * rtP . Gain4_Gain_jn3s3lqgoz - rtDW .
bdlz3yfllc ) * muDoubleScalarAbs ( rtB . enkm4ifchy ) * rtP .
Gain1_Gain_j513dbaupl ; rtB . iu2zqirfs2 = rtP . Gain2_Gain_ikpkbbvwrt *
pi01aggk5s ; rtB . e0xj4q2kh1 = rtP . R1_Gain_dpwnma2t2r * rtB . enkm4ifchy ;
kbrlz2zmlx = rtP . donotdeletethisgain_Gain_hxzgn03ewa * rtB . c4oldjnq3u [ 4
] ; ewm2wjscso = ( real_T ) rtP . Gain1_Gain_ktxeejomp2 * 0.03125 * ( real_T
) ( kbrlz2zmlx < rtP . ProtectionCircuit1_v_min ) + ( real_T ) rtP .
Gain_Gain_c0qmbgnxyo * 0.03125 * ( real_T ) ( kbrlz2zmlx > rtP .
ProtectionCircuit1_v_cut ) ; kbrlz2zmlx = ewm2wjscso - rtDW . evlwxs2e1f ; if
( kbrlz2zmlx > rtP . RateLimiter_RisingLim_jvhpkecggo ) { kbrlz2zmlx = rtDW .
evlwxs2e1f + rtP . RateLimiter_RisingLim_jvhpkecggo ; } else if ( kbrlz2zmlx
< rtP . RateLimiter_FallingLim_d5p2achwo0 ) { kbrlz2zmlx = rtDW . evlwxs2e1f
+ rtP . RateLimiter_FallingLim_d5p2achwo0 ; } else { kbrlz2zmlx = ewm2wjscso
; } rtDW . evlwxs2e1f = kbrlz2zmlx ; rtB . iwlrjtti0w = rtP .
Gain2_Gain_px1uc4eppw * kbrlz2zmlx ; rtB . l1efzgifhl = rtP .
donotdeletethisgain_Gain_fst5oafdsk * rtB . gcul10z3jv [ 5 ] ; rtB .
ll3qrorekf = ( ( real_T ) ( rtB . l1efzgifhl < rtP .
Constant_Value_jhdk32vwtf ) * rtP . Gain4_Gain_nsfdeivlwj - rtDW . jf2kk54ldn
) * muDoubleScalarAbs ( rtB . l1efzgifhl ) * rtP . Gain1_Gain_flinnljcki ;
rtB . admbdmfv3c = rtP . Gain2_Gain_i0q1iceuxf * d3t2ofntt1 ; rtB .
h152k3wasb = rtP . R1_Gain_i25021xdgk * rtB . l1efzgifhl ; kbrlz2zmlx = rtP .
donotdeletethisgain_Gain_kuvj10tsac * rtB . gcul10z3jv [ 4 ] ; ewm2wjscso = (
real_T ) rtP . Gain1_Gain_gd0jlj4aut * 0.03125 * ( real_T ) ( kbrlz2zmlx <
rtP . ProtectionCircuit2_v_min ) + ( real_T ) rtP . Gain_Gain_k10n1oijw2 *
0.03125 * ( real_T ) ( kbrlz2zmlx > rtP . ProtectionCircuit2_v_cut ) ;
kbrlz2zmlx = ewm2wjscso - rtDW . lqmt5s4eon ; if ( kbrlz2zmlx > rtP .
RateLimiter_RisingLim_ljq2tkilib ) { kbrlz2zmlx = rtDW . lqmt5s4eon + rtP .
RateLimiter_RisingLim_ljq2tkilib ; } else if ( kbrlz2zmlx < rtP .
RateLimiter_FallingLim_pojklgsdkc ) { kbrlz2zmlx = rtDW . lqmt5s4eon + rtP .
RateLimiter_FallingLim_pojklgsdkc ; } else { kbrlz2zmlx = ewm2wjscso ; } rtDW
. lqmt5s4eon = kbrlz2zmlx ; rtB . lvuiwhpda4 = rtP . Gain2_Gain_ginrxjfbvg *
kbrlz2zmlx ; rtB . il4x3p0kai = ssGetTaskTime ( rtS , 0 ) ; if (
ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS , 0 ) ; ;
if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar * ) (
LogVar * ) ( rtDW . jecmukiw0b . LoggedData ) , & rtB . il4x3p0kai , 0 ) ; }
} } UNUSED_PARAMETER ( tid ) ; } void MdlOutputsTID1 ( int_T tid ) { uint16_T
kqjjtplnkl ; rtB . mkwy2gpqoc = rtP . EqCircuitNetwork_r_leak ; rtB .
ms1xzaxnje = rtP . EqCircuitNetwork_r_leak ; rtB . cyub2cqqry = rtP .
EqCircuitNetwork_r_leak ; rtB . ips0s3kqvl = rtP . EqCircuitNetwork_r_leak ;
rtB . prsr21hpu4 = rtP . EqCircuitNetwork_r_leak ; rtB . ggr0l4ju4n = rtP .
EqCircuitNetwork_r_leak ; rtB . dvtnssswgf = rtP . EqCircuitNetwork_r_leak ;
rtB . lylp4o3za1 = rtP . EqCircuitNetwork_r_leak ; rtB . a1obnn0rik = rtP .
EqCircuitNetwork_r_leak ; rtB . gyntgt3u14 = rtP . EqCircuitNetwork_r_leak ;
rtB . fuc132pis2 = rtP . EqCircuitNetwork_r_leak ; rtB . avikq2ugv0 = rtP .
EqCircuitNetwork_r_leak ; rtB . cjwcu33zih = rtP . EqCircuitNetwork_r_leak ;
rtB . c1giyep455 = rtP . EqCircuitNetwork_r_leak ; rtB . ibm00zzuip = rtP .
EqCircuitNetwork_r_leak ; rtB . c4msc3eeit = rtP . EqCircuitNetwork_r_leak ;
rtB . obirrlzjde = rtP . EqCircuitNetwork1_r_leak ; rtB . fv4mwhqp3p = rtP .
EqCircuitNetwork1_r_leak ; rtB . fylelfokss = rtP . EqCircuitNetwork1_r_leak
; rtB . eddfok0ttt = rtP . EqCircuitNetwork1_r_leak ; rtB . i2w34spfgq = rtP
. EqCircuitNetwork1_r_leak ; rtB . mgwpo2euua = rtP .
EqCircuitNetwork1_r_leak ; rtB . ohgmxf2ovd = rtP . EqCircuitNetwork1_r_leak
; rtB . c2ydbw2sj0 = rtP . EqCircuitNetwork1_r_leak ; rtB . mmk3xoxflr = rtP
. EqCircuitNetwork1_r_leak ; rtB . dawwmoz5xy = rtP .
EqCircuitNetwork1_r_leak ; rtB . gri0rwhmpf = rtP . EqCircuitNetwork1_r_leak
; rtB . n1zbzuxb3r = rtP . EqCircuitNetwork1_r_leak ; rtB . oypzfi1iso = rtP
. EqCircuitNetwork1_r_leak ; rtB . kkmyyic4sz = rtP .
EqCircuitNetwork1_r_leak ; rtB . fngwa3baxj = rtP . EqCircuitNetwork1_r_leak
; rtB . l5qc2ih1nh = rtP . EqCircuitNetwork1_r_leak ; rtB . m21rtdprr4 = rtP
. EqCircuitNetwork2_r_leak ; rtB . ny2kjgfpce = rtP .
EqCircuitNetwork2_r_leak ; rtB . mbcc0zmkwz = rtP . EqCircuitNetwork2_r_leak
; rtB . e1vdt0sgzs = rtP . EqCircuitNetwork2_r_leak ; rtB . a5ef0qh5ui = rtP
. EqCircuitNetwork2_r_leak ; rtB . emi1eiicwz = rtP .
EqCircuitNetwork2_r_leak ; rtB . ly2a15pyev = rtP . EqCircuitNetwork2_r_leak
; rtB . afaqeoaxi3 = rtP . EqCircuitNetwork2_r_leak ; rtB . o2vyntsikv = rtP
. EqCircuitNetwork2_r_leak ; rtB . gh1ihs33dh = rtP .
EqCircuitNetwork2_r_leak ; rtB . bta1zfrbsx = rtP . EqCircuitNetwork2_r_leak
; rtB . j0nzc2e04b = rtP . EqCircuitNetwork2_r_leak ; rtB . ilizmh402p = rtP
. EqCircuitNetwork2_r_leak ; rtB . mzbg4yn5c1 = rtP .
EqCircuitNetwork2_r_leak ; rtB . iqbg0iu0hq = rtP . EqCircuitNetwork2_r_leak
; rtB . mowq1vn4dj = rtP . EqCircuitNetwork2_r_leak ; rtB . azjmzqd3vb = rtP
. capacitance ; rtB . gmbaq2fbjb = rtP . capacitance ; rtB . h0gqs1nhdm = rtP
. capacitance ; rtB . mjdat5hd2e = rtP . capacitance ; rtB . lhuj2gsrko = rtP
. capacitance ; rtB . kxm5w2htjt = rtP . capacitance ; rtB . okyxtfo4ko = rtP
. capacitance ; rtB . bpzq12sk1y = rtP . capacitance ; rtB . nmztaq5xza = rtP
. capacitance ; rtB . nmdxbbj1gj = rtP . capacitance ; rtB . duawl3zq0w = rtP
. capacitance ; rtB . irqllizifh = rtP . capacitance ; rtB . abcg0jvxu2 = rtP
. capacitance ; rtB . lhv3fabtry = rtP . capacitance ; rtB . jagy2oxlxs = rtP
. capacitance ; rtB . b1cj1hxqcp = rtP . capacitance ; rtB . mmuxgctkpa = rtP
. capacitance ; rtB . nhyg4avrjq = rtP . capacitance ; rtB . ptb4abw35t = rtP
. capacitance ; rtB . astupp0ykj = rtP . capacitance ; rtB . bxevyg1qfv = rtP
. capacitance ; rtB . bsyf5qnqlq = rtP . capacitance ; rtB . pqe4h0mldk = rtP
. capacitance ; rtB . oabhgyaqej = rtP . capacitance ; rtB . f30of2biun = rtP
. capacitance ; rtB . isnln11ygz = rtP . capacitance ; rtB . eqca5yhlwz = rtP
. capacitance ; rtB . oiu1puuk0r = rtP . capacitance ; rtB . hpa1cu2ml4 = rtP
. capacitance ; rtB . nonqf4a0km = rtP . capacitance ; rtB . n4ec24vcv4 = rtP
. capacitance ; rtB . mfnrp4nocv = rtP . capacitance ; rtB . prob4hxsnz = rtP
. capacitance ; rtB . nojsqgyym0 = rtP . capacitance ; rtB . gi5vxvkn1l = rtP
. capacitance ; rtB . j1jg4ps3pb = rtP . capacitance ; rtB . mrb1fq2yah = rtP
. capacitance ; rtB . f20ue4bczk = rtP . capacitance ; rtB . a2ugtljmkq = rtP
. capacitance ; rtB . gvyaxp1jds = rtP . capacitance ; rtB . ll0aghnbw3 = rtP
. capacitance ; rtB . hkmm0vso4o = rtP . capacitance ; rtB . kcaeorhfgi = rtP
. capacitance ; rtB . cj5l40duds = rtP . capacitance ; rtB . idkhic3gum = rtP
. capacitance ; rtB . cmcorjnw34 = rtP . capacitance ; rtB . eqps0gcjjy = rtP
. capacitance ; rtB . opcvbfbu0a = rtP . capacitance ; rtB . c5am1xxeyp = rtP
. Subsystem5_r_esr ; rtB . ltvkuhvonr = rtP . Subsystem1_r_esr ; rtB .
mrfoka5crq = rtP . Subsystem1_r_esr ; rtB . hzj3ghd3ti = rtP .
Subsystem1_r_esr ; rtB . kd315mesw4 = rtP . Subsystem1_r_esr ; rtB .
g35mjbeqs3 = rtP . Subsystem2_r_esr ; rtB . dtu3mjgum2 = rtP .
Subsystem2_r_esr ; rtB . oevtjor0u3 = rtP . Subsystem2_r_esr ; rtB .
ipjqzabc30 = rtP . Subsystem2_r_esr ; rtB . oopq5yauzv = rtP .
Subsystem2_r_esr ; rtB . hwri03ubr2 = rtP . Subsystem2_r_esr ; rtB .
hroaolzuga = rtP . Subsystem_r_esr ; rtB . omo0odknr4 = rtP . Subsystem_r_esr
; rtB . dawcyvu3ar = rtP . Subsystem_r_esr ; rtB . dzqdbynuky = rtP .
Subsystem_r_esr ; rtB . lgeiac2zcg = rtP . Subsystem8_r_esr ; rtB .
f2azip3nkv = rtP . Subsystem5_r_esr_otnqz5ubg5 ; rtB . nejc01f2yj = rtP .
Subsystem1_r_esr_epp1mj5kl0 ; rtB . exxy3crrss = rtP .
Subsystem1_r_esr_epp1mj5kl0 ; rtB . mbeg3v5z5m = rtP .
Subsystem1_r_esr_epp1mj5kl0 ; rtB . fu4duvs1oh = rtP .
Subsystem1_r_esr_epp1mj5kl0 ; rtB . ebzmfciyvp = rtP .
Subsystem2_r_esr_ihzsp4i5mp ; rtB . i0jcfar22j = rtP .
Subsystem2_r_esr_ihzsp4i5mp ; rtB . bgtvlmqb0i = rtP .
Subsystem2_r_esr_ihzsp4i5mp ; rtB . b2jrj4aug2 = rtP .
Subsystem2_r_esr_ihzsp4i5mp ; rtB . ikwdhesgqr = rtP .
Subsystem2_r_esr_ihzsp4i5mp ; rtB . glumzkv1kv = rtP .
Subsystem2_r_esr_ihzsp4i5mp ; rtB . ftjkvl0ttv = rtP .
Subsystem_r_esr_a33gf5kscd ; rtB . gt5qnx3oug = rtP .
Subsystem_r_esr_a33gf5kscd ; rtB . fq04nnejal = rtP .
Subsystem_r_esr_a33gf5kscd ; rtB . nz1n2dwtmm = rtP .
Subsystem_r_esr_a33gf5kscd ; rtB . hcm40myr01 = rtP .
Subsystem8_r_esr_fsgykwfdu3 ; rtB . hkuzgnbjbt = rtP .
Subsystem5_r_esr_arbsh4fv2d ; rtB . oi4qaxezfh = rtP .
Subsystem1_r_esr_ii1xxm2434 ; rtB . a4gf2pw04z = rtP .
Subsystem1_r_esr_ii1xxm2434 ; rtB . lluqlqnbie = rtP .
Subsystem1_r_esr_ii1xxm2434 ; rtB . geucbkz3sb = rtP .
Subsystem1_r_esr_ii1xxm2434 ; rtB . dy5jvvwh21 = rtP .
Subsystem2_r_esr_g3e3odzj4z ; rtB . at3grkcr0i = rtP .
Subsystem2_r_esr_g3e3odzj4z ; rtB . nclby2bt4t = rtP .
Subsystem2_r_esr_g3e3odzj4z ; rtB . cxic31gs5o = rtP .
Subsystem2_r_esr_g3e3odzj4z ; rtB . bj0j0lkfw3 = rtP .
Subsystem2_r_esr_g3e3odzj4z ; rtB . o3nf12o3kv = rtP .
Subsystem2_r_esr_g3e3odzj4z ; rtB . cb5qphbn0v = rtP .
Subsystem_r_esr_gtxynyerfi ; rtB . g0c4aqlyry = rtP .
Subsystem_r_esr_gtxynyerfi ; rtB . pwg5klf2pi = rtP .
Subsystem_r_esr_gtxynyerfi ; rtB . kv203gp00h = rtP .
Subsystem_r_esr_gtxynyerfi ; rtB . n0yawwlhtp = rtP .
Subsystem8_r_esr_gihueny4su ; kqjjtplnkl = ( uint16_T ) ( ( uint32_T ) (
muDoubleScalarAbs ( rtP . amps_in ) != rtP . Constant_Value_fppjs3x0ea ) *
rtP . Gain_Gain_i0jfjlg44q ) ; rtB . juhelemmkf = ( real_T ) kqjjtplnkl *
0.03125 ; rtB . c5k4edupr5 = ( real_T ) kqjjtplnkl * 0.03125 ;
UNUSED_PARAMETER ( tid ) ; } void MdlUpdate ( int_T tid ) { { int_T * gState
= ( int_T * ) rtDW . lpqqjlpxt1 . G_STATE ; * ( gState ++ ) = ( int_T ) rtB .
juhelemmkf ; * ( gState ++ ) = ( int_T ) rtB . c5k4edupr5 ; * ( gState ++ ) =
( int_T ) 0.0 ; * ( gState ++ ) = ( int_T ) 0.0 ; } rtDW . lwfztydmov = rtP .
Constant12_Value ; rtDW . kpa0qz1w2m = ( rtB . nqrdiqgjxm - rtP .
Currentfilter_DenCoef [ 1 ] * rtDW . kpa0qz1w2m ) / rtP .
Currentfilter_DenCoef [ 0 ] ; rtDW . dk1lpgs41d = rtB . ouitoiyxuf ; rtDW .
oh13f4t51u = 0U ; rtDW . ksp1zkwcj2 += rtP . inti_gainval * rtB . nqrdiqgjxm
; if ( rtDW . ksp1zkwcj2 >= rtP . inti_UpperSat ) { rtDW . ksp1zkwcj2 = rtP .
inti_UpperSat ; } else { if ( rtDW . ksp1zkwcj2 <= rtP . inti_LowerSat ) {
rtDW . ksp1zkwcj2 = rtP . inti_LowerSat ; } } if ( rtB . jum15pqqg1 > 0.0 ) {
rtDW . kmqrnxxbow = 1 ; } else if ( rtB . jum15pqqg1 < 0.0 ) { rtDW .
kmqrnxxbow = - 1 ; } else if ( rtB . jum15pqqg1 == 0.0 ) { rtDW . kmqrnxxbow
= 0 ; } else { rtDW . kmqrnxxbow = 2 ; } rtDW . lnyxns4prr += rtP .
DiscreteTimeIntegrator_gainval * rtB . edbedwxht5 ; rtDW . j3ah0j5uha = rtB .
lwwgzcjoh5 ; rtDW . jnwgqfjczs = rtP . Constant12_Value_plqhmhde5z ; rtDW .
iq0yvshwbl = ( rtB . htnfuvkgid - rtP . Currentfilter_DenCoef_mwjcihxo4o [ 1
] * rtDW . iq0yvshwbl ) / rtP . Currentfilter_DenCoef_mwjcihxo4o [ 0 ] ; rtDW
. lztbr3et3t = rtB . kod4h1025c ; rtDW . itp5tejlgk = 0U ; rtDW . hwrivx5mi4
+= rtP . inti_gainval_pb2vhjbqxt * rtB . htnfuvkgid ; if ( rtDW . hwrivx5mi4
>= rtP . inti_UpperSat_ovnl0mfsbp ) { rtDW . hwrivx5mi4 = rtP .
inti_UpperSat_ovnl0mfsbp ; } else { if ( rtDW . hwrivx5mi4 <= rtP .
inti_LowerSat_lm4gcia0l4 ) { rtDW . hwrivx5mi4 = rtP .
inti_LowerSat_lm4gcia0l4 ; } } if ( rtB . daplgb1rla > 0.0 ) { rtDW .
f2pl5hhy0a = 1 ; } else if ( rtB . daplgb1rla < 0.0 ) { rtDW . f2pl5hhy0a = -
1 ; } else if ( rtB . daplgb1rla == 0.0 ) { rtDW . f2pl5hhy0a = 0 ; } else {
rtDW . f2pl5hhy0a = 2 ; } rtDW . nb1buv1zor += rtP .
DiscreteTimeIntegrator_gainval_n5xpalw41i * rtB . gt2e0gwhn0 ; rtDW .
ad3mgyfzte = rtB . gye3zy1a0f ; rtDW . aircger2rx = rtP .
Constant12_Value_dvmlx2pkqs ; rtDW . oq5hmifhxo = ( rtB . mgmgpzdaim - rtP .
Currentfilter_DenCoef_pf4x0hfod2 [ 1 ] * rtDW . oq5hmifhxo ) / rtP .
Currentfilter_DenCoef_pf4x0hfod2 [ 0 ] ; rtDW . maze5hu4ab = rtB . dv2i5nazyy
; rtDW . d23tl2d2xe = 0U ; rtDW . ms1k4m0ka3 += rtP . inti_gainval_hllk4zcjzx
* rtB . mgmgpzdaim ; if ( rtDW . ms1k4m0ka3 >= rtP . inti_UpperSat_fafppsy3ai
) { rtDW . ms1k4m0ka3 = rtP . inti_UpperSat_fafppsy3ai ; } else { if ( rtDW .
ms1k4m0ka3 <= rtP . inti_LowerSat_lfqfty24xa ) { rtDW . ms1k4m0ka3 = rtP .
inti_LowerSat_lfqfty24xa ; } } if ( rtB . lujepfroun > 0.0 ) { rtDW .
f2mbtmfzg2 = 1 ; } else if ( rtB . lujepfroun < 0.0 ) { rtDW . f2mbtmfzg2 = -
1 ; } else if ( rtB . lujepfroun == 0.0 ) { rtDW . f2mbtmfzg2 = 0 ; } else {
rtDW . f2mbtmfzg2 = 2 ; } rtDW . fb5x1hmdio += rtP .
DiscreteTimeIntegrator_gainval_dduja0dlmp * rtB . kpjwqjmfqs ; rtDW .
ihbczgg1ch = rtB . fnwh3t55no ; { const real_T * As = ( real_T * ) rtDW .
g5a0yy0hef . AS ; const real_T * Bs = ( real_T * ) rtDW . g5a0yy0hef . BS ;
real_T * xtmp = ( real_T * ) rtDW . g5a0yy0hef . XTMP ; real_T accum ; {
int_T i1 ; real_T * xd = & rtDW . bmlwssomru [ 0 ] ; for ( i1 = 0 ; i1 < 48 ;
i1 ++ ) { accum = 0.0 ; { int_T i2 ; real_T * xd = & rtDW . bmlwssomru [ 0 ]
; for ( i2 = 0 ; i2 < 48 ; i2 ++ ) { accum += * ( As ++ ) * xd [ i2 ] ; } }
accum += * ( Bs ++ ) * rtB . az0hrbqkrf ; accum += * ( Bs ++ ) * rtB .
jdfrz34ab5 ; accum += * ( Bs ++ ) * rtB . gywgkp2di0 ; accum += * ( Bs ++ ) *
rtP . amps_in ; xtmp [ i1 ] = accum ; } } { int_T i1 ; real_T * xd = & rtDW .
bmlwssomru [ 0 ] ; for ( i1 = 0 ; i1 < 48 ; i1 ++ ) { xd [ i1 ] = xtmp [ i1 ]
; } } } { int_T * gState = ( int_T * ) rtDW . kosaktmuhw . G_STATE ; * (
gState ++ ) = ( int_T ) rtB . fpbsng3i4c ; * ( gState ++ ) = ( int_T ) rtB .
fpbsng3i4c ; * ( gState ++ ) = ( int_T ) 0.0 ; * ( gState ++ ) = ( int_T )
0.0 ; } rtDW . jwpobdvxh3 = rtP . Constant12_Value_o33aovv1d2 ; rtDW .
l4l5iifhga = ( rtB . enkm4ifchy - rtP . Currentfilter_DenCoef_lvlptmaxwd [ 1
] * rtDW . l4l5iifhga ) / rtP . Currentfilter_DenCoef_lvlptmaxwd [ 0 ] ; rtDW
. nuc12zx3mo = rtB . iu2zqirfs2 ; rtDW . k0yugcv43d = 0U ; rtDW . oegbozknnu
+= rtP . inti_gainval_kj3rbkybv5 * rtB . enkm4ifchy ; if ( rtDW . oegbozknnu
>= rtP . inti_UpperSat_knlety0kfl ) { rtDW . oegbozknnu = rtP .
inti_UpperSat_knlety0kfl ; } else { if ( rtDW . oegbozknnu <= rtP .
inti_LowerSat_fqu2adq33w ) { rtDW . oegbozknnu = rtP .
inti_LowerSat_fqu2adq33w ; } } if ( rtB . mcaon1wt2t > 0.0 ) { rtDW .
oufwnzwkdu = 1 ; } else if ( rtB . mcaon1wt2t < 0.0 ) { rtDW . oufwnzwkdu = -
1 ; } else if ( rtB . mcaon1wt2t == 0.0 ) { rtDW . oufwnzwkdu = 0 ; } else {
rtDW . oufwnzwkdu = 2 ; } rtDW . bdlz3yfllc += rtP .
DiscreteTimeIntegrator_gainval_lhnmikqaol * rtB . bojcrrwkcj ; rtDW .
jz4s1v251o = rtB . e0xj4q2kh1 ; { int_T * gState = ( int_T * ) rtDW .
lhqp2i1wv4 . G_STATE ; * ( gState ++ ) = ( int_T ) rtB . iwlrjtti0w ; * (
gState ++ ) = ( int_T ) rtB . iwlrjtti0w ; * ( gState ++ ) = ( int_T ) 0.0 ;
* ( gState ++ ) = ( int_T ) 0.0 ; } rtDW . mip1wd2oyv = rtP .
Constant12_Value_ax3hipqz10 ; rtDW . nqdr1b40o2 = ( rtB . l1efzgifhl - rtP .
Currentfilter_DenCoef_insasfptku [ 1 ] * rtDW . nqdr1b40o2 ) / rtP .
Currentfilter_DenCoef_insasfptku [ 0 ] ; rtDW . ogqyiifq2n = rtB . admbdmfv3c
; rtDW . fpix2rdml1 = 0U ; rtDW . bpnis5nmqy += rtP . inti_gainval_osk2p2d2at
* rtB . l1efzgifhl ; if ( rtDW . bpnis5nmqy >= rtP . inti_UpperSat_kkiq22x4id
) { rtDW . bpnis5nmqy = rtP . inti_UpperSat_kkiq22x4id ; } else { if ( rtDW .
bpnis5nmqy <= rtP . inti_LowerSat_jiolab11br ) { rtDW . bpnis5nmqy = rtP .
inti_LowerSat_jiolab11br ; } } if ( rtB . c5qmbivysx > 0.0 ) { rtDW .
lrgpgfqgzz = 1 ; } else if ( rtB . c5qmbivysx < 0.0 ) { rtDW . lrgpgfqgzz = -
1 ; } else if ( rtB . c5qmbivysx == 0.0 ) { rtDW . lrgpgfqgzz = 0 ; } else {
rtDW . lrgpgfqgzz = 2 ; } rtDW . jf2kk54ldn += rtP .
DiscreteTimeIntegrator_gainval_erswkl2tg5 * rtB . ll3qrorekf ; rtDW .
o035fkrhgg = rtB . h152k3wasb ; { int_T * gState = ( int_T * ) rtDW .
c0rfzt21pv . G_STATE ; * ( gState ++ ) = ( int_T ) rtB . lvuiwhpda4 ; * (
gState ++ ) = ( int_T ) rtB . lvuiwhpda4 ; * ( gState ++ ) = ( int_T ) 0.0 ;
* ( gState ++ ) = ( int_T ) 0.0 ; } rtDW . kvdcvco01e += rtP .
Integrator_gainval * rtB . jajcvm3ojj ; UNUSED_PARAMETER ( tid ) ; } void
MdlUpdateTID1 ( int_T tid ) { UNUSED_PARAMETER ( tid ) ; } void MdlTerminate
( void ) { { free ( rtDW . lpqqjlpxt1 . DS ) ; free ( rtDW . lpqqjlpxt1 .
DX_COL ) ; free ( rtDW . lpqqjlpxt1 . TMP2 ) ; free ( rtDW . lpqqjlpxt1 .
G_STATE ) ; free ( rtDW . lpqqjlpxt1 . SWITCH_STATUS ) ; free ( rtDW .
lpqqjlpxt1 . SW_CHG ) ; free ( rtDW . lpqqjlpxt1 . SWITCH_STATUS_INIT ) ; } {
free ( rtDW . g5a0yy0hef . AS ) ; free ( rtDW . g5a0yy0hef . BS ) ; free (
rtDW . g5a0yy0hef . CS ) ; free ( rtDW . g5a0yy0hef . DS ) ; free ( rtDW .
g5a0yy0hef . DX_COL ) ; free ( rtDW . g5a0yy0hef . TMP2 ) ; free ( rtDW .
g5a0yy0hef . BD_COL ) ; free ( rtDW . g5a0yy0hef . TMP1 ) ; free ( rtDW .
g5a0yy0hef . XTMP ) ; } { free ( rtDW . kosaktmuhw . DS ) ; free ( rtDW .
kosaktmuhw . DX_COL ) ; free ( rtDW . kosaktmuhw . TMP2 ) ; free ( rtDW .
kosaktmuhw . G_STATE ) ; free ( rtDW . kosaktmuhw . SWITCH_STATUS ) ; free (
rtDW . kosaktmuhw . SW_CHG ) ; free ( rtDW . kosaktmuhw . SWITCH_STATUS_INIT
) ; } { free ( rtDW . lhqp2i1wv4 . DS ) ; free ( rtDW . lhqp2i1wv4 . DX_COL )
; free ( rtDW . lhqp2i1wv4 . TMP2 ) ; free ( rtDW . lhqp2i1wv4 . G_STATE ) ;
free ( rtDW . lhqp2i1wv4 . SWITCH_STATUS ) ; free ( rtDW . lhqp2i1wv4 .
SW_CHG ) ; free ( rtDW . lhqp2i1wv4 . SWITCH_STATUS_INIT ) ; } { free ( rtDW
. c0rfzt21pv . DS ) ; free ( rtDW . c0rfzt21pv . DX_COL ) ; free ( rtDW .
c0rfzt21pv . TMP2 ) ; free ( rtDW . c0rfzt21pv . G_STATE ) ; free ( rtDW .
c0rfzt21pv . SWITCH_STATUS ) ; free ( rtDW . c0rfzt21pv . SW_CHG ) ; free (
rtDW . c0rfzt21pv . SWITCH_STATUS_INIT ) ; } if ( rt_slioCatalogue ( ) != (
NULL ) ) { void * * slioCatalogueAddr = rt_slioCatalogueAddr ( ) ;
rtwSaveDatasetsToMatFile ( rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( )
) , rt_GetMatSigstreamLoggingFileName ( ) ) ; rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = NULL ; } } void
MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 0 ) ; ssSetNumY (
rtS , 0 ) ; ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ;
ssSetNumSampleTimes ( rtS , 1 ) ; ssSetNumBlocks ( rtS , 2050 ) ;
ssSetNumBlockIO ( rtS , 506 ) ; ssSetNumBlockParams ( rtS , 13500 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 10.0 ) ;
ssSetOffsetTime ( rtS , 0 , 0.0 ) ; } void raccel_set_checksum ( ) {
ssSetChecksumVal ( rtS , 0 , 2541826342U ) ; ssSetChecksumVal ( rtS , 1 ,
2186444906U ) ; ssSetChecksumVal ( rtS , 2 , 836282152U ) ; ssSetChecksumVal
( rtS , 3 , 1165261717U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( void ) { static struct _ssMdlInfo mdlInfo
; ( void ) memset ( ( char * ) rtS , 0 , sizeof ( SimStruct ) ) ; ( void )
memset ( ( char * ) & mdlInfo , 0 , sizeof ( struct _ssMdlInfo ) ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { void * dwork = ( void * ) & rtDW ; ssSetRootDWork ( rtS , dwork
) ; ( void ) memset ( dwork , 0 , sizeof ( DW ) ) ; } { static
DataTypeTransInfo dtInfo ; ( void ) memset ( ( char_T * ) & dtInfo , 0 ,
sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS , & dtInfo ) ; dtInfo .
numDataTypes = 16 ; dtInfo . dataTypeSizes = & rtDataTypeSizes [ 0 ] ; dtInfo
. dataTypeNames = & rtDataTypeNames [ 0 ] ; dtInfo . BTransTable = &
rtBTransTable ; dtInfo . PTransTable = & rtPTransTable ; dtInfo .
dataTypeInfoTable = rtDataTypeInfoTable ; }
battery_eq_circuit_pascal5_single_shot_stack_InitializeDataMapInfo ( ) ;
ssSetIsRapidAcceleratorActive ( rtS , true ) ; ssSetRootSS ( rtS , rtS ) ;
ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS ,
"battery_eq_circuit_pascal5_single_shot_stack" ) ; ssSetPath ( rtS ,
"battery_eq_circuit_pascal5_single_shot_stack" ) ; ssSetTStart ( rtS , 0.0 )
; ssSetTFinal ( rtS , 100.0 ) ; ssSetStepSize ( rtS , 10.0 ) ;
ssSetFixedStepSize ( rtS , 10.0 ) ; { static RTWLogInfo rt_DataLoggingInfo ;
rt_DataLoggingInfo . loggingInterval = NULL ; ssSetRTWLogInfo ( rtS , &
rt_DataLoggingInfo ) ; } { { static int_T rt_LoggedStateWidths [ ] = { 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 48 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static int_T
rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 } ; static int_T rt_LoggedStateDimensions [ ] = { 1 ,
1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 48 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static
boolean_T rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static BuiltInDTypeId
rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE } ; static int_T rt_LoggedStateComplexSignals [ ] = { 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static
RTWPreprocessingFcnPtr rt_LoggingStatePreprocessingFcnPtrs [ ] = { ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) } ; static const char_T * rt_LoggedStateLabels [ ] = {
"states" , "DSTATE" , "DSTATE" , "states" , "DSTATE" , "DSTATE" , "states" ,
"DSTATE" , "DSTATE" , "DSTATE" , "states" , "DSTATE" , "DSTATE" , "states" ,
"DSTATE" , "DSTATE" , "DSTATE" } ; static const char_T *
rt_LoggedStateBlockNames [ ] = {
"battery_eq_circuit_pascal5_single_shot_stack/Battery/Model/Current filter" ,
"battery_eq_circuit_pascal5_single_shot_stack/Battery/Model/int(i)" ,
 "battery_eq_circuit_pascal5_single_shot_stack/Battery/Model/Exp/Discrete-Time\nIntegrator"
,
"battery_eq_circuit_pascal5_single_shot_stack/Battery1/Model/Current filter"
, "battery_eq_circuit_pascal5_single_shot_stack/Battery1/Model/int(i)" ,
 "battery_eq_circuit_pascal5_single_shot_stack/Battery1/Model/Exp/Discrete-Time\nIntegrator"
,
"battery_eq_circuit_pascal5_single_shot_stack/Battery2/Model/Current filter"
, "battery_eq_circuit_pascal5_single_shot_stack/Battery2/Model/int(i)" ,
 "battery_eq_circuit_pascal5_single_shot_stack/Battery2/Model/Exp/Discrete-Time\nIntegrator"
,
 "battery_eq_circuit_pascal5_single_shot_stack/powergui/EquivalentModel4/State-Space"
,
 "battery_eq_circuit_pascal5_single_shot_stack/Protection Circuit1/Battery/Model/Current filter"
,
 "battery_eq_circuit_pascal5_single_shot_stack/Protection Circuit1/Battery/Model/int(i)"
,
 "battery_eq_circuit_pascal5_single_shot_stack/Protection Circuit1/Battery/Model/Exp/Discrete-Time\nIntegrator"
,
 "battery_eq_circuit_pascal5_single_shot_stack/Protection Circuit2/Battery/Model/Current filter"
,
 "battery_eq_circuit_pascal5_single_shot_stack/Protection Circuit2/Battery/Model/int(i)"
,
 "battery_eq_circuit_pascal5_single_shot_stack/Protection Circuit2/Battery/Model/Exp/Discrete-Time\nIntegrator"
,
 "battery_eq_circuit_pascal5_single_shot_stack/Power Supply and Sink/Discrete PID Controller/Integrator/Discrete/Integrator"
} ; static const char_T * rt_LoggedStateNames [ ] = { "" , "" , "" , "" , ""
, "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" } ; static
boolean_T rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static RTWLogDataTypeConvert
rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 ,
1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } ,
{ 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static
RTWLogSignalInfo rt_LoggedStateSignalInfo = { 17 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert } ; static void *
rt_LoggedStateSignalPtrs [ 17 ] ; rtliSetLogXSignalPtrs ( ssGetRTWLogInfo (
rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtDW . kpa0qz1w2m ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtDW . ksp1zkwcj2 ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtDW . lnyxns4prr ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtDW . iq0yvshwbl ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtDW . hwrivx5mi4 ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) & rtDW . nb1buv1zor ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) & rtDW . oq5hmifhxo ;
rt_LoggedStateSignalPtrs [ 7 ] = ( void * ) & rtDW . ms1k4m0ka3 ;
rt_LoggedStateSignalPtrs [ 8 ] = ( void * ) & rtDW . fb5x1hmdio ;
rt_LoggedStateSignalPtrs [ 9 ] = ( void * ) rtDW . bmlwssomru ;
rt_LoggedStateSignalPtrs [ 10 ] = ( void * ) & rtDW . l4l5iifhga ;
rt_LoggedStateSignalPtrs [ 11 ] = ( void * ) & rtDW . oegbozknnu ;
rt_LoggedStateSignalPtrs [ 12 ] = ( void * ) & rtDW . bdlz3yfllc ;
rt_LoggedStateSignalPtrs [ 13 ] = ( void * ) & rtDW . nqdr1b40o2 ;
rt_LoggedStateSignalPtrs [ 14 ] = ( void * ) & rtDW . bpnis5nmqy ;
rt_LoggedStateSignalPtrs [ 15 ] = ( void * ) & rtDW . jf2kk54ldn ;
rt_LoggedStateSignalPtrs [ 16 ] = ( void * ) & rtDW . kvdcvco01e ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "tmp_raccel_xout" ) ; rtliSetLogXFinal (
ssGetRTWLogInfo ( rtS ) , "xFinal" ) ; rtliSetLogVarNameModifier (
ssGetRTWLogInfo ( rtS ) , "none" ) ; rtliSetLogFormat ( ssGetRTWLogInfo ( rtS
) , 2 ) ; rtliSetLogMaxRows ( ssGetRTWLogInfo ( rtS ) , 1000 ) ;
rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS ) , 1 ) ; rtliSetLogY (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogYSignalInfo ( ssGetRTWLogInfo (
rtS ) , ( NULL ) ) ; rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL
) ) ; } { static ssSolverInfo slvrInfo ; ssSetSolverInfo ( rtS , & slvrInfo )
; ssSetSolverName ( rtS , "FixedStepDiscrete" ) ; ssSetVariableStepSolver (
rtS , 0 ) ; ssSetSolverConsistencyChecking ( rtS , 0 ) ;
ssSetSolverAdaptiveZcDetection ( rtS , 1 ) ; ssSetSolverRobustResetMethod (
rtS , 1 ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelLogData ( rtS , rt_UpdateTXYLogVars ) ;
ssSetModelLogDataIfInInterval ( rtS , rt_UpdateTXXFYLogVars ) ;
ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetTNextTid ( rtS , INT_MIN ) ;
ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 0 ) ; } ssSetChecksumVal ( rtS , 0 ,
2541826342U ) ; ssSetChecksumVal ( rtS , 1 , 2186444906U ) ; ssSetChecksumVal
( rtS , 2 , 836282152U ) ; ssSetChecksumVal ( rtS , 3 , 1165261717U ) ; {
static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE ; static
RTWExtModeInfo rt_ExtModeInfo ; static const sysRanDType * systemRan [ 41 ] ;
gblRTWExtModeInfo = & rt_ExtModeInfo ; ssSetRTWExtModeInfo ( rtS , &
rt_ExtModeInfo ) ; rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo ,
systemRan ) ; systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = &
rtAlwaysEnabled ; systemRan [ 2 ] = & rtAlwaysEnabled ; systemRan [ 3 ] = &
rtAlwaysEnabled ; systemRan [ 4 ] = & rtAlwaysEnabled ; systemRan [ 5 ] = &
rtAlwaysEnabled ; systemRan [ 6 ] = & rtAlwaysEnabled ; systemRan [ 7 ] = &
rtAlwaysEnabled ; systemRan [ 8 ] = & rtAlwaysEnabled ; systemRan [ 9 ] = &
rtAlwaysEnabled ; systemRan [ 10 ] = & rtAlwaysEnabled ; systemRan [ 11 ] = &
rtAlwaysEnabled ; systemRan [ 12 ] = & rtAlwaysEnabled ; systemRan [ 13 ] = &
rtAlwaysEnabled ; systemRan [ 14 ] = & rtAlwaysEnabled ; systemRan [ 15 ] = &
rtAlwaysEnabled ; systemRan [ 16 ] = & rtAlwaysEnabled ; systemRan [ 17 ] = &
rtAlwaysEnabled ; systemRan [ 18 ] = & rtAlwaysEnabled ; systemRan [ 19 ] = &
rtAlwaysEnabled ; systemRan [ 20 ] = & rtAlwaysEnabled ; systemRan [ 21 ] = &
rtAlwaysEnabled ; systemRan [ 22 ] = & rtAlwaysEnabled ; systemRan [ 23 ] = &
rtAlwaysEnabled ; systemRan [ 24 ] = & rtAlwaysEnabled ; systemRan [ 25 ] = &
rtAlwaysEnabled ; systemRan [ 26 ] = & rtAlwaysEnabled ; systemRan [ 27 ] = &
rtAlwaysEnabled ; systemRan [ 28 ] = & rtAlwaysEnabled ; systemRan [ 29 ] = &
rtAlwaysEnabled ; systemRan [ 30 ] = & rtAlwaysEnabled ; systemRan [ 31 ] = &
rtAlwaysEnabled ; systemRan [ 32 ] = & rtAlwaysEnabled ; systemRan [ 33 ] = &
rtAlwaysEnabled ; systemRan [ 34 ] = & rtAlwaysEnabled ; systemRan [ 35 ] = &
rtAlwaysEnabled ; systemRan [ 36 ] = & rtAlwaysEnabled ; systemRan [ 37 ] = &
rtAlwaysEnabled ; systemRan [ 38 ] = & rtAlwaysEnabled ; systemRan [ 39 ] = &
rtAlwaysEnabled ; systemRan [ 40 ] = & rtAlwaysEnabled ;
rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) , &
ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo (
rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS )
, ssGetTPtr ( rtS ) ) ; } rtP . EqCircuitNetwork_r_leak = rtInf ; rtP .
EqCircuitNetwork1_r_leak = rtInf ; rtP . EqCircuitNetwork2_r_leak = rtInf ;
rtP . Saturation_LowerSat = rtMinusInf ; rtP . Saturation_LowerSat_jabf313muk
= rtMinusInf ; rtP . Saturation_LowerSat_e35an2lbrt = rtMinusInf ; rtP .
Saturation_LowerSat_lpdw4vd5ik = rtMinusInf ; rtP .
Saturation_LowerSat_d4iiqg5kd0 = rtMinusInf ; rtP . inti_LowerSat =
rtMinusInf ; rtP . inti_LowerSat_lm4gcia0l4 = rtMinusInf ; rtP .
inti_LowerSat_lfqfty24xa = rtMinusInf ; rtP . inti_LowerSat_fqu2adq33w =
rtMinusInf ; rtP . inti_LowerSat_jiolab11br = rtMinusInf ; rtP .
RateLimiter_FallingLim = rtMinusInf ; rtP . RateLimiter_FallingLim_d5p2achwo0
= rtMinusInf ; rtP . RateLimiter_FallingLim_pojklgsdkc = rtMinusInf ; return
rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 1 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID1 ( tid ) ; }

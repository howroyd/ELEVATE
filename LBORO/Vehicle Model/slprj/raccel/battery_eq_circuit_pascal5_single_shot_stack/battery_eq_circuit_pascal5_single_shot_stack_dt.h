#include "__cf_battery_eq_circuit_pascal5_single_shot_stack.h"
#include "ext_types.h"
static DataTypeInfo rtDataTypeInfoTable [ ] = { { "real_T" , 0 , 8 } , {
"real32_T" , 1 , 4 } , { "int8_T" , 2 , 1 } , { "uint8_T" , 3 , 1 } , {
"int16_T" , 4 , 2 } , { "uint16_T" , 5 , 2 } , { "int32_T" , 6 , 4 } , {
"uint32_T" , 7 , 4 } , { "boolean_T" , 8 , 1 } , { "fcn_call_T" , 9 , 0 } , {
"int_T" , 10 , 4 } , { "pointer_T" , 11 , 8 } , { "action_T" , 12 , 8 } , {
"timer_uint32_pair_T" , 13 , 8 } , { "uint8_T" , 14 , 1 } , { "uint16_T" , 15
, 2 } } ; static uint_T rtDataTypeSizes [ ] = { sizeof ( real_T ) , sizeof (
real32_T ) , sizeof ( int8_T ) , sizeof ( uint8_T ) , sizeof ( int16_T ) ,
sizeof ( uint16_T ) , sizeof ( int32_T ) , sizeof ( uint32_T ) , sizeof (
boolean_T ) , sizeof ( fcn_call_T ) , sizeof ( int_T ) , sizeof ( pointer_T )
, sizeof ( action_T ) , 2 * sizeof ( uint32_T ) , sizeof ( uint8_T ) , sizeof
( uint16_T ) } ; static const char_T * rtDataTypeNames [ ] = { "real_T" ,
"real32_T" , "int8_T" , "uint8_T" , "int16_T" , "uint16_T" , "int32_T" ,
"uint32_T" , "boolean_T" , "fcn_call_T" , "int_T" , "pointer_T" , "action_T"
, "timer_uint32_pair_T" , "uint8_T" , "uint16_T" } ; static
DataTypeTransition rtBTransitions [ ] = { { ( char_T * ) ( & rtB . adontzi2bo
[ 0 ] ) , 0 , 0 , 1159 } , { ( char_T * ) ( & rtDW . kpa0qz1w2m ) , 0 , 0 ,
82 } , { ( char_T * ) ( & rtDW . lpqqjlpxt1 . AS ) , 11 , 0 , 26 } , { (
char_T * ) ( & rtDW . hsbrr2ooio [ 0 ] ) , 10 , 0 , 55 } , { ( char_T * ) ( &
rtDW . kmqrnxxbow ) , 2 , 0 , 5 } , { ( char_T * ) ( & rtDW . oh13f4t51u ) ,
3 , 0 , 5 } } ; static DataTypeTransitionTable rtBTransTable = { 6U ,
rtBTransitions } ; static DataTypeTransition rtPTransitions [ ] = { { (
char_T * ) ( & rtP . amps_in ) , 0 , 0 , 13493 } , { ( char_T * ) ( & rtP .
Gain_Gain_i0jfjlg44q ) , 14 , 0 , 7 } } ; static DataTypeTransitionTable
rtPTransTable = { 2U , rtPTransitions } ;

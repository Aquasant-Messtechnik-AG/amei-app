 /**
  ******************************************************************************
  * @file 	AquaTypes.c
  * @author 	Schaer Manuel
  * @date 	14 Dez 2017
  * @brief	This file contains the basic types depends implementation
  *			  that uesd in a Aquasant field device.
  ******************************************************************************
  *
  * Copyright (c) 2017 Aquasant Messtechnik AG 
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
#if STM32L0xx
#include <stm32l0xx_ll_crc.h>
#endif
#include <AquaTypes.h>
//#include <platform.h>

static volatile uint16_t totUnhandledStates;
volatile uint8_t idCounter;



#define MAX_IS_LOCAL_ITEM 20
//#if PL_IS_EXTUNIT

//UnitTypEnum isLocal[MAX_IS_LOCAL_ITEM] =
//{ 	EXTENTION_UNIT,
//		FSM_EP,
//		FIELD_IFACE,
//		FIELD_CUR_SINK,
//		INT_ADC,
//		MONITOR_EP,
//		DATA_HANDLER_EP,
//		SERIAL_IFACE_EP,
//		SERIAL_IFACE_USB,
//		SERIAL_IFACE_DEBUG,
//		SERIAL_IFACE_FIELDBUS,
//		SERIAL_IFACE_HART,
//		MULTICORE_EP_MP,
//		MULTICORE_EP_HMI,
//		DATA_QUEUE_EP,
//		ADC_MCU,
//		SHELL,
//		ERROR_ENGINE,
//		DEV_UTILS,
//		APP_EP};
//#endif
//#if PL_IS_HMI
////#define MAX_IS_LOCAL_ITEM 11
//UnitTypEnum isLocal[MAX_IS_LOCAL_ITEM] =
//{
//
//		HMI_UNITE,RF_UNITE,
//		FSM_HMI,
//		INT_ADC,
//		HMI,
//		DATA_HANDLER_HMI,
//		SERIAL_IFACE_HMI,
//		MULTICORE_EP_HMI,
//		DATA_QUEUE_HMI,
//		ERROR_ENGINE,
//		DEV_UTILS,
//		APP_HMI};
//#endif
//#if PL_IS_MU
////#define MAX_IS_LOCAL_ITEM 15
//UnitTypEnum isLocal[MAX_IS_LOCAL_ITEM] =
//{
//		MEASURMENT_UNITE,
//		FSM_MP,
//		INT_ADC,
//		MONITOR_MP,
//		DATA_HANDLER_MP,
//		SERIAL_IFACE_MP,
//		MULTICORE_EP_MP,
//		DATA_QUEUE_MP,
//		ADC_FRONTEND,
//		MU_0,
//		ADC_MCU,
//		SHELL,
//		ERROR_ENGINE,
//		DEV_UTILS,
//		APP_MU0};
//#endif



/**
 * @brief This function to initializes a StateStruct object
 * @param *stateStrucPtr A Pointer to the variable which will be initialized
 * @return UnitState If initialization is successfully returns OK else ERR
 */
 UnitState AquaTypesInitState(StateStruct* stateStrucPtr){
	 /* Internal variables	*/
	 uint8_t index = 0;	
	 uint8_t sumCheck = 0;
	 UnitState uState = ERR;
 
	 /******Initializes the StateStruct******/
	 /* Set initial start index	*/
	 stateStrucPtr->index = 0;
	 /* Set all log entries to the INIT value */
	 for(index = 0; index <=STATE_LOG_LENG-1;index++){
		 stateStrucPtr->state_log[index]=INIT;}
	 /*	Set all handled flags to one (true) */
	 for(index = 0; index <=STATE_LOG_LENG-1;index++){
		 stateStrucPtr->curStateHandeld[index]=1;}
	 /* Check the handled states	*/
	 for(index = 0; index <=STATE_LOG_LENG-1;index++){
		 sumCheck += stateStrucPtr->curStateHandeld[index];}
	 
	if(sumCheck == STATE_LOG_LENG){
		uState=OK;
		}

	return uState;
}





/**
 * @brief This methode checks the StateStruct for bufferOvervlow.
* @param *stateStrucPtr A Pointer to the StateStruct variable
 * @return bool BuffOverFlowError
 */
 bool AquaTypesGetStateBufOverflow(StateStruct* stateStrucPtr){

		return stateStrucPtr->BuffOverFlowError;
	
}


 uint8_t AquaType_compare_MeasCfg(measConfigDataStruct_t* cfg1, measConfigDataStruct_t* cfg2){

	uint8_t diff=0;

	(cfg1->lower_treshHold!=cfg2->lower_treshHold) ? diff++ :  0 ;
	(cfg1->upper_treshHold!=cfg2->upper_treshHold) ? diff++ :  0 ;

	(cfg1->probeMinRawValue!=cfg2->probeMinRawValue) ? diff++ :  0 ;
	(cfg1->probeMaxRawValue!=cfg2->probeMaxRawValue) ? diff++ :  0 ;

	(cfg1->rangeMinRawValue!=cfg2->rangeMinRawValue) ? diff++ :  0 ;
	(cfg1->rangeMaxRawValue!=cfg2->rangeMaxRawValue) ? diff++ :  0 ;

	(cfg1->mtiMode!=cfg2->mtiMode) ? diff++ :  0 ;

  return diff;
}

 
 uint8_t AquaType_compare_HmiCfg(hmiConfigDataStruct_t* cfg1, hmiConfigDataStruct_t* cfg2){

		uint8_t diff=0;

		(cfg1->dispCfg.brightness!=cfg2->dispCfg.brightness) ? diff++ :  0 ;
		(cfg1->dispCfg.contrast!=cfg2->dispCfg.contrast) ? diff++ :  0 ;
		(cfg1->dispCfg.delay_PowerOffBacklight!=cfg2->dispCfg.delay_PowerOffBacklight) ? diff++ :  0 ;

		(cfg1->dispCfg.enableFlag!=cfg2->dispCfg.enableFlag) ? diff++ :  0 ;
		(cfg1->dispCfg.inverseFlag!=cfg2->dispCfg.inverseFlag) ? diff++ :  0 ;
		(cfg1->dispCfg.std_backlight!=cfg2->dispCfg.std_backlight) ? diff++ :  0 ;
		(cfg1->dispCfg.temp_comp!=cfg2->dispCfg.temp_comp) ? diff++ :  0 ;

		(cfg1->menuDispCfg.delay_PowerOffDelay!=cfg2->menuDispCfg.delay_PowerOffDelay) ? diff++ :  0 ;
		(cfg1->menuDispCfg.delay_backToDefaultscreen!=cfg2->menuDispCfg.delay_backToDefaultscreen) ? diff++ :  0 ;

		(cfg1->lang!=cfg2->lang) ? diff++ :  0 ;

		(cfg1->mainDispCfg.MeasuringUnits[0]!=cfg2->mainDispCfg.MeasuringUnits[0]) ? diff++ :  0 ;
		(cfg1->mainDispCfg.MeasuringUnits[1]!=cfg2->mainDispCfg.MeasuringUnits[1]) ? diff++ :  0 ;
		(cfg1->mainDispCfg.MeasuringUnits[2]!=cfg2->mainDispCfg.MeasuringUnits[2]) ? diff++ :  0 ;
		(cfg1->mainDispCfg.MeasuringUnits[3]!=cfg2->mainDispCfg.MeasuringUnits[3]) ? diff++ :  0 ;

		(cfg1->mainDispCfg.chart!=cfg2->mainDispCfg.chart) ? diff++ :  0 ;
		(cfg1->mainDispCfg.chartUnit[0]!=cfg2->mainDispCfg.chartUnit[0]) ? diff++ :  0 ;
		(cfg1->mainDispCfg.chartUnit[1]!=cfg2->mainDispCfg.chartUnit[1]) ? diff++ :  0 ;
		(cfg1->mainDispCfg.show_bitField!=cfg2->mainDispCfg.show_bitField) ? diff++ :  0 ;
//		(cfg1->mainDispCfg.showSystemDesc!=cfg2->mainDispCfg.showSystemDesc) ? diff++ :  0 ;
//		(cfg1->mainDispCfg.showSystemId!=cfg2->mainDispCfg.showSystemId) ? diff++ :  0 ;
//		(cfg1->mainDispCfg.showTempChipSensorADC!=cfg2->mainDispCfg.showTempChipSensorADC) ? diff++ :  0 ;
//		(cfg1->mainDispCfg.showTempExtSensor!=cfg2->mainDispCfg.showTempExtSensor) ? diff++ :  0 ;
//		(cfg1->mainDispCfg.showTempNtcSensor!=cfg2->mainDispCfg.showTempNtcSensor) ? diff++ :  0 ;

	  return diff;
	}

 uint8_t AquaType_compare_measData(measDataSet_t* data1, measDataSet_t* data2){

		uint8_t diff=0;

		(data1->ampDiff!=data2->ampDiff) ? diff++ :  0 ;
		(data1->ampDiffLin!=data2->ampDiffLin) ? diff++ :  0 ;

		(data1->cap!=data2->cap) ? diff++ :  0 ;
		(data1->phaseDiff!=data2->phaseDiff) ? diff++ :  0 ;

		(data1->temp_Ext!=data2->temp_Ext) ? diff++ :  0 ;
		(data1->temp_NTC!=data2->temp_NTC) ? diff++ :  0 ;

		(data1->temp_chip!=data2->temp_chip) ? diff++ :  0 ;

	  return diff;
	}



// void AquaType_setBitFieldBit(uint32_t *bitField,uint8_t size, uint8_t bit){(bit==bit_allBits)? (memset((uint32_t*)bitField,0xff,size)) : (*bitField |= 1UL << bit);}
 void AquaType_setBitFieldBit(uint32_t *bitField,uint8_t size, uint8_t bit){
	 if(bit==(uint8_t)bit_allBits){
		 memset((uint32_t*)bitField,0xff,size); }
	 else{ (bit>31)?(*(bitField+1) |= 1UL << (bit-31)):(*bitField |= 1UL << bit);}
	 }
 void AquaType_clearBitFieldBit(uint32_t *bitField,uint8_t size, uint8_t bit){
	 if(bit==(uint8_t)bit_allBits){
		 (memset((uint32_t*)bitField,0x00,size)); }
	 else{ (bit>31)?  (*(bitField+1) &= ~(1UL << (bit-31))): (*bitField &= ~(1UL << bit));}
	 }
 uint8_t AquaType_toggleBitFieldBit(uint32_t *bitField, uint8_t bit){*bitField ^= 1UL << bit;return AquaType_getBitFieldBit(bitField,bit);}
 uint8_t AquaType_getBitFieldBit(uint32_t *bitField, uint8_t bit){ if(bit==bit_allBits){return bit_maxBit;}/*(bit==bit_allBits)? (*bitField) :*/ return (bit>31)?((*(bitField+1) >> (bit-31)) & 1U):((*bitField >> bit) & 1U);}
 uint8_t AquaType_getCountBitFieldBit(uint32_t *bitField,uint8_t size){
	 uint8_t cnt=0;for(uint8_t i=0;i<size*8;i++) {((*bitField>>i)&1U)?cnt++: 0;}return cnt;}

 uint8_t AquaType_mearge_BitFieldBit(uint32_t *destField,uint32_t *sourceField,uint8_t size){
	 for(uint8_t i=0;i<size/4;i++) {
		*(destField+i)|=*(sourceField+i);
	 }
	 return 1;
 }

 uint8_t AquaType_checkAnyBitSet(uint32_t *bitField,uint8_t size){
	 for(uint8_t i=0;i<size/4;i++) {
		if(*(bitField+i))
		{return 1;}
	 }
	 return 0;
 }

 uint8_t AquaType_compareFirstDiff_BitFieldBit(uint32_t *bitField1,uint32_t *bitField2,uint8_t size){
	 for(uint8_t i=0;i<size*8;i++) {
		 if(((*bitField1>>i)&1U)!=((*bitField2>>i)&1U)){ return i;	 }
	 }
	 return 0;
 }

 uint8_t AquaType_compareFirstCom_BitFieldBit(uint32_t *bitField1,uint32_t *bitField2,uint8_t size){
	 for(uint8_t i=0;i<size*8;i++) {
		 if(((*bitField1>>i)&1U)&&(((*bitField1>>i)&1U)==((*bitField2>>i)&1U))){ return i;	 }
	 }
	 return 0;
 }
 namurBitFieldPos_t AquaType_getRelevantNamurState( namurBitField_t* bitfield){
//	 namurBitField_t* bitfield= &localDevBaseStrPtr->stateBitField->namurBitField;
	 if(AquaType_getBitFieldBit((uint32_t *)bitfield,namurFault)){ return namurFault;}
	 if(AquaType_getBitFieldBit((uint32_t *)bitfield,namurOutOfRange)){ return namurOutOfRange;}
	 if(AquaType_getBitFieldBit((uint32_t *)bitfield,namurMaintenence)){ return namurMaintenence;}
	 if(AquaType_getBitFieldBit((uint32_t *)bitfield,namurCheck)){ return namurCheck;}
	 if(AquaType_getBitFieldBit((uint32_t *)bitfield,namurChecked)){ return namurChecked;}
	 return namurUnchecked;

 }


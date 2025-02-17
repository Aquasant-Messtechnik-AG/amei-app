/**
******************************************************************************
* @file   AquaTypes.h
* @author     Schaer Manuel
* @date   14 Dez 2017
* @brief  This file contains the types that uesd in a Aquasant field device.
******************************************************************************
*
* Copyright (c) 2017 Aquasant Messtechnik AG
* All rights reserved.
*
*
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AQUATYPES_H
#define __AQUATYPES_H



#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>



/** @brief Defines the firmware base version X.0*/
#define FIRMWARE_VERSION 1
/** @brief Defines the firmware branch version 0.X*/
#define FIRMWARE_BRANCH 1

#define BOOT_VERSION 1

/** @brief Defines the state log length of the StateStruct*/
#define STATE_LOG_LENG      5

/** @brief Define for number of measurement values in defaultscreen  */
#define MAX_NUMBER_OF_DISPLAYED_MEASVALUES 3
/** @brief Safety boolean type - FALSE (use two bits) */
#define FALSE   0x00u   /**< FALSE type*/
/** @brief Safety boolean type - TRUE (use two bits) */
#define TRUE    0x11u

#define MAX_NUM_OF_CALIBS   10
#define NUMBER_OF_LOG_ENTREES 20






/**
 * @brief Standard unit states
 *
 * this enumeration describes the state of instance
 */
typedef enum UintState_Enum {
    UN_INITED,
    INIT,                                               /**< Unit is INIT*/
    INITED,
    OK,                                             /**< Unit is OK*/
    DONE,
    RUN,
    IDLE,                                           /**< Unit is IDLE*/
    BUSY,                                           /**< Unit is BUSY*/
    WAIT,
    SYNC,
    REFRESH,
    READY,
    DEINIT,                                     /**< Unit is DEINIT*/
    DEINITED,
    FAIL,                                           /**< Unit has some FAILS*/
    FAIL_INIT,                                  /**< fail happens while initialization*/
    DRIVER_ERR,                         /**< hw driver fails */
    DRIVER_ERR_SPI,
    DRIVER_ERR_UART,
    DRIVER_ERR_DMA,
    MEM_MALLOC_FAIL,
    MEM_FREE_FAIL,
    MOUNT_ERR,                          /**< device mount fails */
    OVF,                                            /**< a ovf was reported */
    ERR_OUT_OF_RANGE,           /**< array out of range was rteported*/
    WRITE_EEPROM_FAIL,          /**< eeprom write error */
    LOCK_EEPROM_FAIL,               /**< eeprom lock error*/
    QUEUE_DATA_ERROR,           /**< data que error */
    SOURCE_FAIL,                            /**< data queue source error */
    DEST_FAIL,                              /**< data queue dest error */
    DATA_CORRUPTED,             /**< data consistency lost */
    ERR,                                            /**< Unit has an ERROR*/
    INVALID_PIONTER,
    DO_RESET,
    ENABLED_NOT,

    NONE_UNHANDLED
}UnitState;



/**
 * @brief Standard status and error type
 */
typedef struct State_Struct {
    UnitState       state[5];
    uint8_t         stateIndex;
    UnitState       state_log[STATE_LOG_LENG];          /**< An array of logged states, to use as queue*/
    uint8_t         index;                              /**< Pointer to the address the current state*/
    bool            curStateHandeld[STATE_LOG_LENG];    /**< This boolean is true, if the current state is handled*/
    bool            BuffOverFlowError;                  /**< Flag to mark a bufferOverflow*/
}StateStruct;



/**
 * @brief Structure to hold meas data values
 */
typedef struct MeasDataSet_Struct {
    int16_t     temp_chip;    /**< chip temp value */
    int16_t     temp_NTC;     /**< ntc temp value */
    int16_t     temp_Ext;     /**< ext temp value */
    int32_t     ampDiff;      /**< amp differential value */
    int32_t     ampDiffLin;   /**< amp differential compensated value */
    int32_t     phaseDiff;    /**< phase differencial value */
    float           cap;          /**< capacity  value */
}measDataSet_t;

/**
 * @brief Enumerator to store operation mode of an extension unit
 */
typedef enum mtiModRangeEnum {
    Undef_MtiMod = 0,
    ProbeRange = 1,
    MTI_10,                                    /**<MTI performs MTI10 mode*/
    MTI_20,
    MTI_30,
    MTI_50,                                    /**<MTI performs MTI50 mode*/
    MTI_100,                               /**<MTI performs MTI100 mode*/
    MTI_200,                                /**<MTI performs MTI200 mode*/
    MTI_400,                               /**<MTI performs MTI400 mode*/
    MTI_800,                               /**<MTI performs MTI800 mode*/
    RESERVED0,
    RESERVED1,
    RESERVED2,
    RESERVED3,
    RESERVED4,
    RESERVED5,
    None_MtiMod = -1
} mtiMod_t;

/**
 * @brief Struct to store measurment configuration
 */
typedef struct  measModCfgStruct {
    uint8_t activCfgId;       /**< id to identify the current config - units can hold an array of cfg's */
    int32_t probeMinRawValue;  /**< probe min raw value */
    int32_t probeMaxRawValue;  /**< probe max raw value */
    int32_t rangeMinRawValue;  /**< probe min range value */
    int32_t rangeMaxRawValue;  /**< probe min range value */
    int32_t lower_treshHold;  /**< probe lower thresh value */
    int32_t upper_treshHold;  /**< probe upper tresh value */
    mtiMod_t mtiMode;         /**<Holds the operation mode of an extension unite*/
    uint8_t dummy[2];
}measConfigDataStruct_t;

/**
 * @brief Struct to store screen cfg
 */
typedef struct Diyplay_Setting_Struct {
    uint8_t   enableFlag;               /**< flag enable screen */
    uint8_t   inverseFlag;              /**< flag screen inverse*/
    uint8_t   brightness;               /**< screen brightness*/
    uint8_t   contrast;                 /**< screen contrast value*/
    uint8_t   temp_comp;                /**< screen temp comp value*/
    uint8_t   std_backlight;            /**< screen std brightness*/
    uint8_t   delay_PowerOffBacklight;  /**< timeout to power off backlight*/
}dispConfigDataStruct_t;

typedef enum { modType_undef, modType_pulse, modType_curSink, modType_maxType } outputModType_t;



/**
 * @brief Struct to hold mod error cfg
 */

typedef     struct mod_ErrStruct {
    uint16_t err_measUnderflow;
    uint16_t err_measOverflow;
    uint16_t err_modUnderflow;
    uint16_t err_modOverflow;
    uint16_t err_tempLow;
    uint16_t err_tempHigh;
    uint16_t err_porbeShort;
    uint16_t err_pobeOpen;
    uint16_t err_probeOutOfRange;
    uint16_t err_dataConfigInvalid;
    uint16_t err_dataDataInvalid;
    uint16_t err_FW;
    uint16_t err_HW;
}   modErrorConfigDataStruct_t;


typedef enum {
    err_measUnderflow = 2,
    err_measOverflow,
    err_modUnderflow,
    err_modOverflow,
    err_tempLow,
    err_tempHigh,
    err_porbeShort,
    err_pobeOpen,
    err_probeOutOfRange,
    err_dataConfigInvalid,
    err_dataDataInvalid,
    err_FW,
    err_HW,
    err_Max
}errorBitFieldPos_t;
typedef uint32_t errorBitField_t;
typedef enum {
    warn_modRangeUnderflow = 2,
    warn_modRangeOverflow,

}warnBitFieldPos_t;
typedef uint32_t warnBitField_t;
typedef enum {
    namurFault = 7,
    namurOutOfRange = 6,
    namurMaintenence = 5,
    namurUnchecked = 4,
    namurChecked = 3,
    namurCheck = 2,
}namurBitFieldPos_t;

typedef enum {
    err_bitField = 0,
    err_bitField_handled,
    //  err_bitField_shown,
    err_bitField_acked,
    err_bitField_max,
}err_bitFieldIndex_t;

typedef uint32_t namurBitField_t;
typedef struct {
    errorBitField_t     errorBitField[err_bitField_max];

    //  warnBitField_t  warnBitField;
    namurBitField_t namurBitField;
    //  uint16_t    dummy;
} stateBitField_t;



typedef enum {
    probeType_undef,
    probeType_tss80,
    probeType_tss90,
    probeType_stm,
    probeType_frgm,
    probeType_stl,
    probeType_max
}probeType_t;

/**
 * @brief Struct to store probe cfg
 */
typedef struct probeTypeStruct {
    uint8_t     activCfgId;         /**< id to identify the current config - units can hold an array of cfg's */
    probeType_t probeType;          /**< type of probe */
    uint32_t        probeRangeF[2];     /**< probe range in pF [min/max] */
    uint32_t        probeRangeR[2];     /**< probe- amei range  in raw value [min/max] */
    uint32_t        probeRange[2];      /**< [min/max]  */
    uint32_t        probeRangeDeg[2];   /**<  probe type in degree [min/max]  */
    uint8_t       dummy[2];
} probeCfgDataStruct_t;

/**
 * @brief Enumerator to store probe type
 */
typedef struct hfConnectorTypeStruct {
    uint8_t         enableFlag;
    uint8_t         type[3][4];                     /**< Conn.type - A-side ; middle ; B-side;*/
    uint16_t        length[2];
    //  float_t         probePara[10];
    bool            compEnable[2];
    //  uint32_t    dummy[1];
    uint8_t     dummy[3];
} hfConnCfgDataStruct_t;



/**
 * @brief This structure holds probes static data
 */
 //typedef struct ProbeStaticDataStruct{
 //  probeStruct_t probeData;
 ////    hfConnType_t     hfConnData;
 //
 //}probeCfgDataStruct_t;


typedef enum HmiMainDispUnits {
    unitsNone,
    unitsRaw,
    unitsRawFactor,
    unitsRawSondFactor,
    unitsRawSondRangeFactor,
    unitsImp,
    unitsmAmps,
    unitsPhase,
    unitsPercentSond,
    unitsPrecentRange,
    unitsPremillSond,
    unitsPremilRange,
    unitsCapacity,
    unitsMilMeter,
    unitsCetMeter,
    unitsMeter,
    unitsLiter,
    unitsDegreeCelsius,
    unitsm3Meter,
    unitsMiLiter,
    unitsMax
}
HmiMainDispUnits_t;

typedef enum HmiMainDispChart { chartNone, chartTrennschicht, chartTrennschichtNiveau, chartFuellstand, chartMax }HmiMainDispBar_t;

typedef enum {
    hmiShow_sysDesc = 0b00000001,
    hmiShow_sysId = 0b00000010,
    hmiShow_tempNtc = 0b00000100,
    hmiShow_tempChip = 0b00001000,
    hmiShow_sideChart = 0b00010000,
    hmiShow_any = 0xFF
}hmiShowEnum_t;
typedef struct HmiMainDispDatafield {
    HmiMainDispBar_t    chart;                    /**< Main display chart cfg */
    HmiMainDispUnits_t  chartUnit[2];             /**< units to show in chart */
    HmiMainDispUnits_t  MeasuringUnits[4];            /**< units to show main display */
    int32_t             DataFieldsFactors[3];     /**< factor to implement rolands labor evaluation */
    uint8_t             show_bitField;
    //  bool                showTempExtSensor;        /**< flag show ext temp */
    //  bool                showTempNtcSensor;        /**< flag show ntc temp */
    //  bool                showTempChipSensorADC;    /**< flag show chip temp */
    //  bool                showSystemId;             /**< flag show system id temp */
    //  bool                showSystemDesc;           /**< flag show system description aka. tag temp */
}hmiMainDispConfigDataStruct_t;

typedef struct NEWHmiMainDispDatafield {
    HmiMainDispBar_t    chart;                    /**< Main display chart cfg */
    HmiMainDispUnits_t  chartUnit[MAX_NUMBER_OF_DISPLAYED_MEASVALUES];             /**< units to show in chart */
    HmiMainDispUnits_t  DataFields[MAX_NUMBER_OF_DISPLAYED_MEASVALUES];            /**< units to show main display */
    int32_t             DataFieldsFactors[MAX_NUMBER_OF_DISPLAYED_MEASVALUES];     /**< factor to implement rolands labor evaluation */
    uint8_t             show_bitField;
}NEWhmiMainDispConfigDataStruct_t;

/**
 * @brief Struct to store hmi menu cfg
 */

typedef struct {
    uint8_t     delay_backToDefaultscreen;        /**< timeout to return to default screen */
    uint8_t     delay_PowerOffDelay;              /**< timeout to power off display  */
}hmiMenuDispConfigDataStruct_t;

/**
 * @brief Struct to store hmi cfg
 */
typedef struct Hmi_Setting_Struct {
    uint8_t                             enableFlag;   /**< enable flag */
    uint8_t                             lang;         /**< language */
    dispConfigDataStruct_t              dispCfg;      /**< display config struct */
    hmiMainDispConfigDataStruct_t       mainDispCfg;  /**< main display conf struct - default view screen */
    hmiMenuDispConfigDataStruct_t       menuDispCfg;  /**< menu config struct - timeout pp. */
    uint8_t                             dummy[1];
}hmiConfigDataStruct_t;

/**
 * @brief Struct to store system description
 */
typedef struct SystemDescriptionStruct {
    char      sysIdentification[32];        /**< char array to store description string */
    uint32_t  sysId;                        /**< system id holder */
}systemDesc_t;

typedef UnitState(traceCbPtr_t)(void* dataPtr);





typedef struct PwmValueHolderStruc {
    uint8_t red;
    uint8_t blue;
    uint8_t green;
    uint8_t backlight;
    uint8_t doRefresh;
}pwmStruct;



typedef enum { calib_rawType, calib_impType, calib_capType, calib_capReversType, calib_realType, calib_imagType, calib_angleType, calib_TypeMax } calibType_t;
/**
 * @brief Calibration data structure
 */
typedef struct {
    uint8_t active;
    uint8_t calibId;
    int32_t calib_temp;                     /**<Device temperature while calibration*/
    calibType_t calibType;              /**<Number of elements that was collected while calibration*/
    uint8_t order;                          /**<Order of calibration polynome*/
    double coefficients[7];                 /**<Polynome coefficients of this calibration*/
}mpCalibData_t;

/**
 * @brief This structure holds all static data of a extension unite
 */
typedef struct ConfigDataStruct {
    float_t         MeasF[4];                   /**<Measurement value {picoF;femtoF;attoF} -> calc(zeroPoint-lower_treshhold) ; zeroPoint ; maxPoint ; calc(maxPoint + upper_treshhold)*/
    float_t         MeasR[4];                   /**<Measurement value {picoOhm;femtoOhm;attoOhm} -> calc(zeroPoint-lower_treshhold) ; zeroPoint ; maxPoint ; calc(maxPoint + upper_treshhold)*/
    float_t         MeasZ[4];                   /**<Measurement value {picoOhm;femtoOhm;attoOhm} -> calc(zeroPoint-lower_treshhold) ; zeroPoint ; maxPoint ; calc(maxPoint + upper_treshhold)*/
    float_t         MeasDeg[4];         /**<Measurement value {degree} -> calc(zeroPoint-lower_treshhold) ; zeroPoint ; maxPoint ; calc(maxPoint + upper_treshhold)*/
    int32_t       MeasRawAmp[4];
    int32_t       MeasRawPhas[4];
    int32_t         lower_treshHold[4];
    int32_t         upper_treshHold[4];
    float           transformFactor[4];
    uint32_t    dummy[4];
}configStaticDataStruct_t;

/**
 * @brief This structure holds probes static data
 */
typedef struct accessDataStruct {
    uint8_t         enableFlag;
    uint16_t     configKey[2];
    uint8_t         configUnlocked;
    uint16_t    deviceKey[2];
    uint8_t         deviceUnlocked;
    uint16_t    factoryKey[2];
    uint8_t         factoryUnlocked;
    uint32_t     timeToAutoLock;
}accessStaticDataStruct_t;


typedef struct loggDataStruct {
    uint8_t         enableFlag;
    uint8_t     lastLogIndex;
    uint8_t      log[3 + 2][NUMBER_OF_LOG_ENTREES];
}loggDataStruct_t;


typedef struct pulseModDynamicStruct {
    UnitState        state;
    uint16_t        curPulseCount;
    uint16_t        nextPulseCount;
    uint8_t             dummy[3];
}pulseModDynData_t;

typedef struct curSinkDynamicStruct {
    UnitState   state;
    int16_t             chipTemp;
    uint16_t         curSinkValue;
    uint16_t        nextSinkValue;
    uint8_t             dummy[1];
}curSinkDynData_t;


typedef struct ledDataStruct {
    uint8_t		 enableFlag;
    uint8_t		brightness[3];
    struct led_ErrStruct {
        uint8_t err_measUnderflow[4];
        uint8_t err_measOverflow[4];
        uint8_t err_modUnderflow[4];
        uint8_t err_modOverflow[4];
        uint8_t err_tempLow[4];
        uint8_t err_tempHigh[4];
        uint8_t err_porbeShort[4];
        uint8_t err_pobeOpen[4];
        uint8_t err_probeOutOfRange[4];
        uint8_t err_dataConfigInvalid[4];
        uint8_t err_dataDataInvalid[4];
        uint8_t err_FW[4];
        uint8_t err_HW[4];
    }	errStruct;
    uint8_t dummy[5];
}ledCfgDataStruct_t;


typedef struct aquaQrDataStruct {
    uint8_t      enabledFlag;
    uint8_t         registredFlag;
    char serverAddress[32];


}aquaQrCfgDataStruct_t;



#if  PL_IS_HMI | defined(LVGL_PC_SIM)
typedef  HmiUnitLocalStaticData_t   devDataUnion_t;
#endif

#define CONFIG_OR_DATA_HAS_CHANGED_SIZE 2

/**
 * @brief Enum to check the dev bit fields for specific bit's
 */

typedef  enum {
    bit_plInfo = 1,
    bit_plInfoEp,
    bit_plInfoHmi,
    bit_plInfoMp,

    bit_plStateSet,
    bit_plStateSetEp,
    bit_plStateSetHmi,
    bit_plStateSetMp,

    bit_degug_iface,
    bit_degug_ifaceEp,
    bit_degug_ifaceHmi,
    bit_degug_ifaceMp,

    bit_serial_iface,
    bit_serial_ifaceEp,
    bit_serial_ifaceHmi,
    bit_serial_ifaceMp,

    bit_mcc,
    bit_mcc_Ep,
    bit_mcc_Hmi,
    bit_mcc_Mp,

    bit_fieldbus,
    bit_fieldbusEp,
    bit_fieldbusHmi,

    bit_monitor,
    bit_monitorEp,
    bit_monitorHmi,
    bit_monitorMp,

    bit_modCfg,
    bit_modCfgEp,
    bit_modCfgHmi,

    bit_modData,
    bit_modDataEp,
    bit_modDataHmi,

    bit_hmiCfg,
    bit_hmiCfgEp,
    bit_hmiCfgHmi,

    bit_sysDesc,
    bit_sysDescEp,
    bit_sysDescHmi,

    bit_measCfg,
    bit_measCfgEp,
    bit_measCfgHmi,
    bit_measCfgMp,

    bit_probeCfg,
    bit_probeCfgEp,
    bit_probeCfgHmi,
    bit_probeCfgMp,

    bit_measData,
    bit_measDataEp,
    bit_measDataHmi,
    bit_measDataMp,

    bit_stateBitField,
    bit_stateBitFieldEp,
    bit_stateBitFieldHmi,
    bit_stateBitFieldMp,

    bit_maxBit,

    bit_allBits = 0xFF,
}cfgOrDataHasChangedBits_t;

typedef  uint32_t cfgOrDataChanged_t[CONFIG_OR_DATA_HAS_CHANGED_SIZE];




/**
 * @brief Device reference structure
 */



typedef enum {
    plRef_unknown, plRef_unregistred, plRef_registred, plRef_waitForRegistred,
    plRef_state, plRef_stateGet, plRef_stateRecived, plRef_stateSet, plRef_stateSync, plRef_stateSynced, plRef_stateWait,
    plRef_InfoGet, plRef_InfoSet, plRef_InfoRecived, plRef_InfoCheck, plRef_InfoWait,
    plRef_config, plRef_configGet, plRef_configSet, plRef_configRequest, plRef_configRecived, plRef_configCheck, plRef_configCheckWait, plRef_configWait,
    plRef_configSync, plRef_configSyncWait, plRef_configSyncMeasCfg, plRef_configSyncModCfg, plRef_configSyncProbeCfg, plRef_configSyncHmiCfg, plRef_configSyncSysDescription,

    plRef_dev, plRef_devSetup, plRef_devStart, plRef_devStop, plRef_devReset, plRef_devWait,
    plRef_fsm, plRef_fsmSetup, plRef_fsmStart, plRef_fsmStop, plRef_fsmReset, plRef_fsmWait,
    plRef_app, plRef_appSetup, plRef_appStart, plRef_appStop, plRef_appReset, plRef_appWait,

    plRef_running,
    plRef_error,
    plRef_max
}
plRefControllingState_t;

typedef struct {
    plRefControllingState_t cur;
    plRefControllingState_t last;
    plRefControllingState_t next;
    cfgOrDataHasChangedBits_t waitForBit;
    cfgOrDataHasChangedBits_t doWhenBit;
    cfgOrDataChanged_t waitForMask;
}plRefControlling_t;

typedef enum LedIdent { all, red, error, green, run, blue, service, backlight }ledIdendity_t;


/**
 * @brief Struct to hold mod cfg
 */

typedef struct ModConfigDataStruct {
    uint8_t         activCfgId; /**< id to identify the current config - units can hold an array of cfg's */

    uint16_t        maxModValue; /**< max regular modulation value */
    uint16_t        minModValue; /**< min regular modulation value */
    float_t         transformFactor; /**< pre calculated transform factor to calculat the mod value from input value */
    float_t         modValue; /**< current modulation value - set throw filediface unit */

    float_t         maxInputValue; /**< max input value */
    float_t         minInputValue; /**< min input value */

} modConfigDataStruct_t;



/*******************************************************************************************************************
 * Function declaration
 ********************************************************************************************************************/




bool AquaTypesGetStateBufOverflow(StateStruct* stateStruct);


UnitState AquaTypes_Handler_cb_UpdateStateSetAndPush(void* dataPtr);
// UnitState AquaTypesCalcCRC(void* dataPtrSrc, uint16_t numOfBytes, uint32_t* CRCValue);



uint8_t AquaType_compare_MeasCfg(measConfigDataStruct_t* cfg1, measConfigDataStruct_t* cfg2);
uint8_t AquaType_compare_ModCfg(modConfigDataStruct_t* cfg1, modConfigDataStruct_t* cfg2);
uint8_t AquaType_compare_HmiCfg(hmiConfigDataStruct_t* cfg1, hmiConfigDataStruct_t* cfg2);

uint8_t AquaType_compare_measData(measDataSet_t* data1, measDataSet_t* data2);


void AquaType_setBitFieldBit(uint32_t* bitField, uint8_t size, uint8_t bit);
void AquaType_clearBitFieldBit(uint32_t* bitField, uint8_t size, uint8_t bit);
uint8_t AquaType_toggleBitFieldBit(uint32_t* bitField, uint8_t bit);
uint8_t AquaType_getBitFieldBit(uint32_t* bitField, uint8_t bit);
uint8_t AquaType_getCountBitFieldBit(uint32_t* bitField, uint8_t size);
uint8_t AquaType_checkAnyBitSet(uint32_t* bitField, uint8_t size);
uint8_t AquaType_mearge_BitFieldBit(uint32_t* destField, uint32_t* sourceField, uint8_t size);
uint8_t AquaType_compareFirstDiff_BitFieldBit(uint32_t* bitField1, uint32_t* bitField2, uint8_t size);
uint8_t AquaType_compareFirstCom_BitFieldBit(uint32_t* bitField1, uint32_t* bitField2, uint8_t size);


static struct ModConfigDataStruct modConfig;


/*******************************************************************************************************************
 * Variable declaration
 ********************************************************************************************************************/
 //DevBaseStruct* devBaseStPtr;

#endif /* __AQUATYPES_H */

/************************ (C) COPYRIGHT Aquasant Messtechnik AG *****END OF FILE****/


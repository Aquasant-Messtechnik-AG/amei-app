/**
 ******************************************************************************
 * @file     AquaHMIMenuDefinitions.c
 * @author   Daniel Ritter
 * @date     24. Juli 2023
 * @brief    This file contains the common implementation of the AquaApp unit
 ******************************************************************************
 *
 * Copyright (c) 2017 Aquasant Messtechnik AG
 * All rights reserved.
 *
 *
 ******************************************************************************
 /*********************
 *      INCLUDES
 *********************/
 /*********************
 *      INCLUDES
 *********************/




#include "AquaHMI.h"

#ifndef LVGL_PC_SIM
#include <AquaDisplay.h>

#include <AquaQR.h>
#endif
#include <AquaMultiLanguages.h>
#include <assert.h>

#if BGM13S32F512GA
#include "em_cmu.h"
#include "em_timer.h"
#include "em_gpio.h"

#endif

#ifndef LVGL_PC_SIM
//#include "lvgl.h"
#include "../lv_drivers/display/ST7565.h"
//#else
//#include "../../lvgl/lvgl.h"
#endif
#include "lv_conf.h"

//#include <stdlib.h>


/**********************
 *      TYPEDEFS
 **********************/



const accessRightsTable_t accessRightsTable[] = {
    /*    Id                publicuser        systemuser        amtbUser  */

    { EXPECTAMTBPASSWORD,     readWrite,        readWrite,        readWrite},
    { EXPECTSYSPASSWORD,    readWrite,        noAccess,         readWrite},

    { FACTORYRESET,    noAccess,        readWrite,         readWrite},
    { AMTBRESET,    noAccess,        noAccess,         readWrite},

    { PASSWORDENTRYVALUE,   readWrite,        readWrite,        readWrite},
    { FIRSTOPERATION,       readWrite,        readWrite,        readWrite},

     { UNIT_pF,               noAccess,        noAccess,           readWrite},
};

uint8_t sizeofAccessRightsTable = sizeof(accessRightsTable) / sizeof(accessRightsTable_t);

/* Begin of parameter characteristics definitions  */
const parametercharacteristics_t parameterCharacteristics[] = {

    { LANGUAGE, parameterTypeInteger, 1, 0, 0, 0 ,"2"} , /* "0" to simulate it was executed */
    { RUNFIRSTOPERATION, parameterTypeInteger, 1, 0, 0, 0 ,"1"} , /* "0" to simulate it was executed */
    { ANALOGSIGNALSPREAD04MA, parameterTypeFloat, 6, 3, 0, 99 ,"0"},
    { ANALOGSIGNALSPREAD20MA, parameterTypeFloat, 7, 3, 0, 100 ,"100"} ,
    { ZEROVALUEMA, parameterTypeInteger, 6, 0, 0, 999999 ,""} ,
    { TOPFULLMA, parameterTypeInteger, 6, 0, 0, 999999 ,""} ,

    { PROBEZEROPOINT, parameterTypeInteger, 6, 0, 0, 9999990 ,""} ,
    { PROBEFULLPOINT, parameterTypeInteger, 6, 0, 0, 9999990 ,""} ,
    { EDITEDCONFIG, parameterTypeInteger, 2, 0, 0, 9999990 ,"0"} ,
    { EDITEDARCHIVE, parameterTypeInteger, 2, 0, 0, 9999990 ,"0"} ,

    { ACTIVECONFIG, parameterTypeInteger, 2, 0, 0, 9999990 ,"0"} ,
    { SENSORSERIALNUMBER, parameterTypeInteger, SERIALNUMBER_SIZE, 0, 0 ,0,"9876"} ,
    { PROBESERIALNUMBER, parameterTypeInteger, SERIALNUMBER_SIZE, 0, 0 ,0,"12345"} ,

    { SOFTWAREVERSION, parameterTypeString, DEVICENAME_SIZE, 0, 0 ,0,PACKAGE_VERSION} ,
    { HARDWAREVERSION, parameterTypeString, DEVICENAME_SIZE, 0, 0 ,0,PACKAGE_VERSION} ,

    { QRMANUAL, parameterTypeString, 0, 0, 0 ,0,"aquasant-mt.com/exdocs"} ,
    { QRDOCS, parameterTypeString, 0, 0, 0 ,0,"aquasant-mt.com\n Link: /qrdocs"} ,
    { CONTACT, parameterTypeString, 0, 0, 0 ,0,ADDRESS_URL} ,

    { MASIMULATIONVALUE, parameterTypeFloat, 4,1,  4 ,20,"20.0"} ,
    { ACTIVEERROR, parameterTypeString, 0, 0 ,0, 0,"Error 02\nError 05\nError 13\n--Ende--"} ,

    { DEVICENAME, parameterTypeString, DEVICENAME_SIZE, 0, 0 ,0,PACKAGE_VERSION},
    { PROBETYPE, parameterTypeString, PROBENAME_SIZE, 0, 0 ,0,"PROBEXY"},
    { EXPECTSYSPASSWORD, parameterTypeInteger, 4, 0 ,0, 0,"0000"},
    { EXPECTAMTBPASSWORD, parameterTypeInteger, 4, 0 ,0, 0,"4416"},

    { PASSWORDENTRYVALUE, parameterTypeInteger, 4, 0 ,0, 0,"0000"},
    { NEWPASSWORDENTRY, parameterTypeInteger, 4, 0 ,0, 0,"0000"},
    { NEWPASSWORDVERIFY, parameterTypeInteger, 4, 0 ,0, 0,"0000"},

    { TRYTOLOGINUSER, parameterTypeInteger, 4, 0, 0 ,loginUserMax,""},
    { SELECTUSER, parameterTypeInteger, 4, 0, 0 ,loginUserMax,"0"},
    { DISPLAY, parameterTypeInteger, 0, 0 , 0, 0, "1"},
    /* Config area just for first config */
    { NAMEFORNEWCONFIG, parameterTypeString, CONFIGNAME_SIZE, 0, 0 ,0, ""}, /* leave default value empty */
    { NAMEFORNEWMEDIUM, parameterTypeString, MEDIUMNAME_SIZE, 0, 0 ,0,""} , /* leave default value empty */


    { SIGNALFILTER, parameterTypeFloat, 4, 0, 0 ,20,"11.5"} ,
    { CURRENTTAG, parameterTypeTagNumber, TAG_SIZE, 0, 0 ,0, "--------------------"},
    { PROOFDATE, parameterTypeDate, DATE_SIZE, 0 ,0, 0,"01.12.2023"},
    { FIRSTDATE, parameterTypeDate, DATE_SIZE, 0, 0,0, "01.12.2023"},

    { ADDTO20MAVALUE, parameterTypeInteger, 3, 0, 0, 500 ,"50"} ,
    { MEASVALUNITS, parameterTypeInteger, 0, 0, 0, 0,""},   /* MEASVARUNITS is Set in default values */
    { ERROR_HANDLING, parameterTypeInteger, 0, 0, 0, 0,""},   /* ERROR_HANDLING is set in default values */

};
uint16_t sizeofParameterCharacteristics = sizeof(parameterCharacteristics)/ sizeof(parametercharacteristics_t);

const parameterEndNodeActions_t parameterEndNodeActions[] = {
/*  ID;                                 event action to call ;   */
    {EXECUTEDELETE,                  executeEndNodeDeleteConfigurationOrMedium},

    {COPYCONFIG,                     executeEndNodeCopyConfiguration },
    {MEDIUMDELETE,                   executeEndNodeDeleteConfigurationOrMedium },
    {APPLYCONFIG,                    executeEndNodeApplyConfig},
    {SAVEFIRSTCONFIGCONFIRM,         executeEndNodeSaveFirstRun},
    {SAVEABORT,                      executeEndNodeSaveAbort},
    {CONTINUETONEXT,                 executeEndNodeContinueButton },
    {SKIPFIRSTOPERATION,             executeEndNodeSkipFirst },
    {EXECFACTORYRESET,               executeFactoryReset },
    {EXECAMTBRESET,                  executeAMTBReset },
};

uint16_t sizeOfParameterEndNodeActions = sizeof(parameterEndNodeActions)/ sizeof(parameterEndNodeActions_t);


const mapChooseListEnums_t mapChooseListEnums[] = {
/*  chooseListParameter;              chooseListEnum;   */

    {UNITS_NONE,                   unitsNone             },
    {UNIT_RAW,                      unitsRaw            },
    {UNIT_MA,                      unitsmAmps            },
    {UNIT_pF,                      unitsCapacity         },
    {UNIT_MM ,                     unitsMilMeter         },
    {UNIT_CM,                      unitsCetMeter         },
    {UNIT_M,                       unitsMeter            },
    {UNIT_LITER,                   unitsLiter            },
    {UNIT_M3METER,                 unitsm3Meter          },
    {UNIT_MILLILITER,              unitsMiLiter          },
};

uint16_t sizeOfMapChooseListEnums = sizeof(mapChooseListEnums)/ sizeof(mapChooseListEnums_t);

/* Begin of menustructure definitions */
const hmiMenuScreen_t menuDefinitions[] = {
{ 0, MENU_ENTRY_POINT, DEFAULT_SCREEN, 0, 0, defaultScreenMenuNode },
{ 0, DEFAULT_SCREEN, LOGO_SCREEN, 0, 0,  logoScreenNode },

{ 0, DEFAULT_SCREEN, APPLICATION, 0, 0,  applicationShowNode },

{ nr1, DEFAULT_SCREEN, FIRSTOPERATION, 0, 0,listNode },

{ nr1, FIRSTOPERATION, RUNFIRSTOPERATION, 0, 0, listNodeAllChildsAutoOpen },
{ 0, FIRSTOPERATION, SKIPFIRSTOPERATION, 0, 0, runParameterEndNodeAction },

{ 0, FIRSTOPERATION, BASE_SETUP, 0, 0,listNode },

{ numbered, RUNFIRSTOPERATION, LANGUAGE, 0, 0, listNode },
{ 0, LANGUAGE, ENGLISH, SPANISH, 0, singleChooseValuesNode },

{ numbered, RUNFIRSTOPERATION, CHOOSEAPP, 0, 0, listNode },
    { 0, CHOOSEAPP, APPBATCH, APPCONT, 0, singleChooseValuesNode },

{ numbered, RUNFIRSTOPERATION, EXPECTSYSPASSWORD, 0,  0, parameterEditNode },

{ 0, RUNFIRSTOPERATION, EXPECTSYSPASSWORD, 0,  0, parameterShowNode },

{ numbered, RUNFIRSTOPERATION, FIRSTDATE, 0, 0,parameterEditNode },

{ numbered, RUNFIRSTOPERATION, CURRENTTAG,          0, 0, parameterEditNode },

{ numbered, RUNFIRSTOPERATION,   ZEROVALUEMA, 0, 0, parameterShowNode },
{ numbered, RUNFIRSTOPERATION,   ZEROVALUEMA, 0, 0, parameterTakeOverNode },
{ numbered, RUNFIRSTOPERATION,   ZEROVALUEMA, 0, 0, parameterEditNode },


{ numbered, RUNFIRSTOPERATION,TOPFULLMA, 0, 0, parameterShowNode },
{ numbered, RUNFIRSTOPERATION, TOPFULLMA, 0, 0, parameterTakeOverNode },
{ numbered, RUNFIRSTOPERATION,TOPFULLMA, 0, 0, parameterEditNode },

{ numbered, RUNFIRSTOPERATION, ANALOGSIGNALSPREAD04MA, 0, 0,parameterEditNode },
{ numbered, RUNFIRSTOPERATION, ANALOGSIGNALSPREAD20MA, 0, 0,parameterEditNode },

{ numbered, RUNFIRSTOPERATION,MASIMULATIONVALUE, 0, 0, parameterEditNodeWithApply },

{ 0, RUNFIRSTOPERATION, ENDOFRUNFIRST, 0, 0, listNode },
{ 0, ENDOFRUNFIRST, SAVEFIRSTCONFIGCONFIRM, 0, 0, runParameterEndNodeAction },
{ 0, ENDOFRUNFIRST, SAVEABORT, 0, 0, runParameterEndNodeAction },

{ numbered, BASE_SETUP, SELECTUSER, 0, 0, listNode },
{ numbered, SELECTUSER, SYSTEMUSER, 0, 0,listChildAutoOpens },
{ numbered, SELECTUSER, AMTBUSER, 0, 0,listChildAutoOpens },

{ numbered, SYSTEMUSER, LOGINPROCESS, 0, 0,listChildAutoOpens },
{ numbered, AMTBUSER, LOGINPROCESS, 0, 0,listChildAutoOpens },

{ numbered, LOGINPROCESS, LOGIN, 0, 0,listChildAutoOpens },
    { 0, LOGIN, PASSWORDENTRYVALUE, 0, SELECTUSER,passwordEntryNode },
        { 0, PASSWORDENTRYVALUE, PASSWORDVALID, 0, BASE_SETUP,parameterShowNodeMatching },    /* Password matched */
        { 0, PASSWORDENTRYVALUE, PASSWORDINVALID, 0, SELECTUSER,parameterShowNodeNotMatching },   /* Password not matched */

{ 0, LOGINPROCESS, CHANGEPASSWORD, 0, 0,listChildAutoOpens },
{ 0, CHANGEPASSWORD, PASSWORDENTRYVALUE, 0, 0,passwordEntryNode },
    { 0, PASSWORDENTRYVALUE, PASSWORDVALID, 0, NEWPASSWORDENTRY,parameterShowNodeMatching },    /* Password matched */
    { 0, PASSWORDENTRYVALUE, PASSWORDINVALID, 0, SELECTUSER,parameterShowNodeNotMatching },     /* Password not matched */

{ 0, ENTERCHANGEPASSWORD, NEWPASSWORDENTRY, 0, 0,passwordEntryNode },
{ 0, NEWPASSWORDENTRY, PASSWORDVALID, 0, NEWPASSWORDVERIFY,parameterShowNodeMatching },          /* Password matched */
{ 0, NEWPASSWORDENTRY, PASSWORDINVALID, 0, SELECTUSER,parameterShowNodeNotMatching },            /* Password not matched */

{ 0, VERIFYPASSWORD, NEWPASSWORDVERIFY, 0, 0,passwordEntryNode },                                /* Password matched */
    { 0, NEWPASSWORDVERIFY, NEWPASSWORDOK, 0, BASE_SETUP,parameterShowNodeMatching },        /* Password not matched */
    { 0, NEWPASSWORDVERIFY, NEWPASSWORDNOTOK, 0, SELECTUSER,parameterShowNodeNotMatching },

    { isReferenced, BASE_SETUP, LANGUAGE, 0, 0, listNode },
    { 0, LANGUAGE, ENGLISH, SPANISH, 0, singleChooseValuesNode },

    { numbered, BASE_SETUP, SIGNALCONFIG, 0, 0, listNode },

    { numbered, BASE_SETUP, ARCHIVE, 0, 0, listNode },

    { numbered, SIGNALCONFIG, CONFIGURATIONX, 0, 0, listChildAutoOpensArray },
    { numbered, CONFIGURATIONX, CONFIGACTION, 0, 0, listNode },

    { numbered, CONFIGACTION,   APPLYCONFIG, 0, SIGNALCONFIG, runParameterEndNodeAction },
    { numbered, APPLYCONFIG, EDITCONFIG, 0, SIGNALCONFIG, compressedListNode },   /* Shows a compressed list based on the name given as title */

    { numbered, CONFIGACTION,   EDITCONFIG, 0, 0, listNode },
    { numbered, CONFIGACTION,   CONFIGRENAME, 0, 0, listChildAutoOpens },
        { 0, CONFIGRENAME,   NAMEFORNEWCONFIG, 0, 0, parameterEditNode },
    { numbered, CONFIGACTION,   COPYCONFIG, 0, SIGNALCONFIG, runParameterEndNodeAction },
    { numbered, CONFIGACTION,   DELETECONFIG, 0, 0, listChildAutoOpens },

    { 0, DELETECONFIG, EXPECTSYSPASSWORD, 0, 0,passwordEntryNode },
        { 0, EXPECTSYSPASSWORD, EXECUTEDELETE, 0, SIGNALCONFIG,runParameterEndNodeAction },       /* Password matched */
        { 0, EXPECTSYSPASSWORD, PASSWORDINVALID, 0, SIGNALCONFIG,parameterShowNodeNotMatching },  /* Password not matched */

    { isReferenced, EDITCONFIG,   ZEROADJUST, 0, 0, listNodeAllChildsAutoOpen },
    { isReferenced, ZEROADJUST,   ZEROVALUEMA, 0, 0, parameterShowNode },
    { isReferenced, ZEROADJUST,   ZEROVALUEMA, 0, 0, parameterTakeOverNode },
    { isReferenced, ZEROADJUST,   ZEROVALUEMA, 0, 0, parameterEditNode },

    { isReferenced, EDITCONFIG,   TOPADJUST, 0, 0, listNodeAllChildsAutoOpen },
    { isReferenced, TOPADJUST,TOPFULLMA, 0, 0, parameterShowNode },
    { isReferenced, TOPADJUST, TOPFULLMA, 0, 0, parameterTakeOverNode },
    { isReferenced, TOPADJUST,TOPFULLMA, 0, 0, parameterEditNode },

    { isReferenced, EDITCONFIG, ANALOGSIGNALSPREAD04MA, 0, 0, parameterEditNode },
    { isReferenced, EDITCONFIG, ANALOGSIGNALSPREAD20MA, 0, 0, parameterEditNode },
    { isReferenced, EDITCONFIG, SIGNALFILTER, 0, 0, parameterEditNode },

    { numbered, ARCHIVE, ARCHIVEX, 0, 0, listChildAutoOpensArray },
    { numbered, ARCHIVEX, ARCHIVEACTION, 0, 0, listNode },

    { numbered, ARCHIVEACTION,   MEDIUMEDIT, 0, 0, listNode },
        { numbered, MEDIUMEDIT,   TOPADJUST, 0, 0, listNodeAllChildsAutoOpen },
        { numbered, TOPADJUST,TOPFULLMA, 0, 0, parameterShowNode },
        { numbered, TOPADJUST, TOPFULLMA, 0, 0, parameterTakeOverNode },
        { numbered, TOPADJUST,TOPFULLMA, 0, 0, parameterEditNode },
    { numbered, ARCHIVEACTION,   MEDIUMRENAME, 0, 0, listChildAutoOpens },
        { numbered, MEDIUMRENAME,   NAMEFORNEWMEDIUM, 0, 0, parameterEditNode },
    { 0, ARCHIVEACTION,    MEDIUMDELETE, 0, 0, listChildAutoOpens },
        { 0, MEDIUMDELETE, EXPECTSYSPASSWORD, 0, 0,passwordEntryNode },
        { 0, EXPECTSYSPASSWORD, EXECUTEDELETE, 0, ARCHIVE,runParameterEndNodeAction },       /* Password matched */
        { 0, EXPECTSYSPASSWORD, PASSWORDINVALID, 0, ARCHIVE,parameterShowNodeNotMatching },  /* Password not matched */

{ numbered, BASE_SETUP, DEVICECONFIG, 0, 0, listNode },
    { numbered, DEVICECONFIG, DISPLAY, 0, 0, listNode },
    { numbered, DISPLAY, DISPLAYLINE_1, 0, 0, listNode },
    { numbered, DISPLAYLINE_1, UNITS_NONE, UNIT_MILLILITER, 0, singleChooseValuesNode },
    { numbered, DISPLAY, DISPLAYLINE_2, 0, 0, listNode },
    { numbered, DISPLAYLINE_2, UNITS_NONE, UNIT_MILLILITER, 0, singleChooseValuesNode },
    { numbered, DISPLAY, DISPLAYLINE_3, 0, 0, listNode },
    { numbered, DISPLAYLINE_3, UNITS_NONE,  UNIT_MILLILITER, 0, singleChooseValuesNode },

    { isReferenced, DEVICECONFIG, CHOOSEAPP, 0, 0, listNode },
    { 0, CHOOSEAPP, APPBATCH, APPCONT, 0, singleChooseValuesNode },

    { isReferenced, DEVICECONFIG, CURRENTTAG,          0, 0, parameterEditNode },

    { numbered, DEVICECONFIG, MEASVALUNITS, 0, 0, listNode },
    { 0, MEASVALUNITS, UNITS_NONE, UNIT_MILLILITER, 0, multiChooseValuesNode },

    { numbered, DEVICECONFIG,MASIMULATIONVALUE, 0, 0, parameterEditNodeWithApply },

    { numbered, DEVICECONFIG,ERROR_HANDLING, 0, 0, listNode },
    { 0, ERROR_HANDLING, EH_0001, EH_HW_ERR, 0, multiChooseValuesNode },

    { 0, DEVICECONFIG,FACTORYRESET, 0, 0, listChildAutoOpens },
    { 0, FACTORYRESET, EXPECTSYSPASSWORD, 0, 0,passwordEntryNode },
        { 0, EXPECTSYSPASSWORD, EXECFACTORYRESET, 0, FIRSTOPERATION,runParameterEndNodeAction },
        { 0, EXPECTSYSPASSWORD, PASSWORDINVALID, 0, FIRSTOPERATION,parameterShowNodeNotMatching },

    { 0, DEVICECONFIG,AMTBRESET, 0, 0, listChildAutoOpens },
    { 0, AMTBRESET, EXPECTAMTBPASSWORD, 0, 0,passwordEntryNode },
        { 0, EXPECTAMTBPASSWORD, EXECAMTBRESET, 0, FIRSTOPERATION,runParameterEndNodeAction },
        { 0, EXPECTAMTBPASSWORD, PASSWORDINVALID, 0, FIRSTOPERATION,parameterShowNodeNotMatching },

    { numbered, BASE_SETUP, DEVICE_DATA, 0, 0, listNode },
        { numbered, DEVICE_DATA, SENSORDATA, 0, 0, listNode },
        { numbered, DEVICE_DATA, PROBEDATA, 0, 0, listNode },
        { numbered, DEVICE_DATA, PROOFDATE, 0, 0, parameterShowNode },
        { numbered, DEVICE_DATA, QRMANUAL, 0, 0, parameterShowNode },
        { numbered, DEVICE_DATA, QRDOCS, 0, 0, parameterShowNode },
        { numbered, DEVICE_DATA, CONTACT, 0, 0,parameterShowNode },
        { isReferenced, DEVICE_DATA, FIRSTDATE, 0, 0, parameterShowNode },

    { numbered, SENSORDATA, DEVICENAME, 0, SENSORDATA, parameterShowNode },
    { numbered, SENSORDATA, SENSORSERIALNUMBER, 0, 0, parameterShowNode },
    { numbered, SENSORDATA, SOFTWAREVERSION, 0, 0, parameterShowNode },
    { numbered, SENSORDATA, HARDWAREVERSION, 0, 0, parameterShowNode },

    { numbered, PROBEDATA,  PROBETYPE, 0, 0, parameterEditNode },
    { numbered, PROBEDATA,  PROBESERIALNUMBER, 0, 0, parameterEditNode },
    { numbered, PROBEDATA, PROBEZEROPOINT, 0, 0, parameterShowNode },
    { numbered, PROBEDATA, PROBEFULLPOINT, 0, 0, parameterShowNode },


    /* Generic Screen Definitions */

    { 0, DEFAULT_SCREEN, MESSAGESCREEN, 0, 0, messageScreenNode },
    { 0, ANYPARAMETER, ANYPARAMETER, 0, 0,      parameterNodeTemplate },


    { 0, 0, 0, 0, 0, 0, } /* LAST ENTRYMARK, MUST BE AT THE END OF THE LIST, DO NOT Change*/

};



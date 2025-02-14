/**
  ******************************************************************************
  * @file 	AquaApp.h
  * @author 	Schaer Manuel
  * @date 	14 Dez 2017
  * @brief	This file contains the common defines of the AquaApp unit
  ******************************************************************************
  *
  * Copyright (c) 2017 Aquasant Messtechnik AG 
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AQUAHMI_H
#define __AQUAHMI_H
//#include <platform.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <AquaTypes.h>

#define LVGL_PC_SIM 1

#ifndef LVGL_PC_SIM 
    #include "lvgl.h"
#else
    #include <lvgl.h>
#endif

#ifdef LVGL_PC_SIM 
    #define LOGOSCREEN_DELAY 2000
    #define APPLICATIONSCREEN_DELAY 2000

#else
    #define LOGOSCREEN_DELAY 2000
    #define APPLICATIONSCREEN_DELAY 2000
#endif

#define USER_LOGOUT_TIME 60*60*1000
#define SHOWPARAMETERONCEDELAY 200

#define TESTMODULE_ENABLED                 1
#define PACKAGE_VERSION                   "Rev 163"
#define DEBUGFUNCTIONS                     0
#define NUMBER_OF_CONFIGURATIONS           5
#define NUMBER_OF_MEDIUMS                  3
#define NUMBER_OF_NEWCONFIGURATIONS        2


/**
 * Contact text
 */
#define COMPANY       "Aquasant-Messtechik AG\n"
#define HOME_STREET   "Hauptstrasse 22\n"
#define HOME_CITY    "CH-4416 Bubendorf\n"
#define URL          "www.aquasant.com\n"

#define ADDRESS COMPANY HOME_STREET HOME_CITY
#define ADDRESS_URL COMPANY HOME_STREET HOME_CITY URL
#define SMALLSTRINGSIZE  100 /* size of a small local string  */
#define BIGSTRINGSIZE  300 /* size of a bigger local string  */

#define STRING_CONVERSION_BUFFER_SIZE   100    /**< Buffer size of temporary buffer to convert values into a string */


/** @brief Maximal Number of menulevels  */
#define MAXMENUDEPTH 50


/* Relevant sizes for configuration record. Connsider storage size in EP and queue transmission capacities */
#define DEVICENAME_SIZE                    10
#define NAME_SIZE                          10
#define DATE_SIZE                          10
#define PROBENAME_SIZE                     10
#define SERIALNUMBER_SIZE                  20
#define CONFIGNAME_SIZE                    10
#define MEDIUMNAME_SIZE                    10
#define TAG_SIZE                           20

#define NUMBEROFLANGUAGES LAST_LANGUAGE_ENUM-LANGUAGE-1

#ifdef BGM13S32F512GA
    #define LOGCONSOLE(format,a, b,c,d)  // no logging yet in target
#else

#define LOGCONSOLE(format,a, b,c,d)\
    char temporaryLogBuffer[BIGSTRINGSIZE]; \
    sprintf(temporaryLogBuffer,format,a,b,c,d); \
    strcat(temporaryLogBuffer,"\n"); \
    printf(temporaryLogBuffer);\
    ;
#endif

/**
 * @brief Enum to identify menues and parameters uniquely
 *        Note: Don't care of the sorting order, except for chooselist enums, they have to be in the order from lowest to hights
 */
typedef enum{


/* is aligned with HmiMainDispUnits_t */
UNITSDEFINITIONSTART,  // Use the start value when selecting one of the units
    UNITS_NONE,
    UNIT_RAW,  /* TEMPORARY, used in simulator curreently */
    UNIT_MA,
    UNIT_PERCENT,
    UNIT_pF,
    UNIT_MM,
    UNIT_CM,
    UNIT_M,
    UNIT_LITER,
    UNIT_M3METER,
    UNIT_MILLILITER,
UNITSDEFINITIONSEND,

ERROR_HANDLING               ,
    EH_0001,
    EH_0002,
    EH_UNDERFLOW_MEAS            ,
    EH_OVERFLOW_MEAS             ,
    EH_UNDERFLOW_MOD             ,
    EH_OVERFLOW_MOD              ,
    EH_LOW_TEMP                  ,
    EH_HIGH_TEMP                 ,
    EH_PORBE_OPEN                ,
    EH_PROBE_SHORT               ,
    EH_PROBE_OUT_OF_RANGE        ,
    EH_CONFIG_INVALID            ,
    EH_DATA_INVALID              ,
    EH_FW_ERR                    ,
    EH_HW_ERR                    ,


LANGUAGE                    ,
    ENGLISH,
    FRENCH,
    GERMAN,
    ITALIAN,
    SPANISH,
LAST_LANGUAGE_ENUM,

BASE_SETUP,
MEASURMENT                   ,
CONFIGURATION                ,
GUIDE                        ,
PROBE                        ,
TYPE                         ,
PARAMETER                    ,
HF_CABLE                     ,
LENGTH                       ,
COMPENSATION                 ,
MODE                         ,
PROBESETTINGS,
LOWER_ADJ                    ,
UPPER_ADJ                    ,
LOWER_THRES                  ,
UPPER_THRES                  ,
SERVICE                      ,
LOG                          ,
CALCULATE                    ,
RANGE                        ,
SYSTEM                       ,
ACCESS                       ,
LOCK                         ,
UNLOCK                       ,
SET_DEVICE_KEY               ,
DEL_DEVICE_KEY               ,
SET_CONFIG_KEY               ,
DEL_CONFIG_KEY               ,
FACTORY_UNLOCK               ,
FACTORY_LOCK                 ,

OPTIONS                      ,
ADD_OPTION_KEY               ,
ADD_OPTION                   ,
REMOVE_OPTION                ,
DISPLAY                     ,
DISPLAYLINE_1                       ,
DISPLAYLINE_2                       ,
DISPLAYLINE_3                       ,
DEFAULT_SCREEN               ,
MENU_ENTRY_POINT               ,
LOGO_SCREEN               ,
OKTAKEOVERINFO,
SHOWAPPLICATION_SCREEN,
BACKLIGHT                  ,
CONTRAST                     ,
CONNECTIVITY                ,
PULSE_MOD                    ,
PULSE_MOD_EN                 ,
LOWER_PULSE_COUNT            ,
UPPER_PULSE_COUNT            ,
MAX_PULSE_VALUE              ,

LED                          ,
LED_EN                       ,
BRIGHTNESS                   ,
SERIAL                       ,
SERIAL_EN                    ,
TIMEOUT                    ,
SIGNALCONFIG,
ACTIVECONFIG,
EDITEDCONFIG,
EDITEDARCHIVE,
ACTIVEARCHIVE,
ITEMNOTDELETED,
CONFIGNOTDELETED,
/* Keep this together */
SELECTCONFIG,
CONFIGURATIONX ,
CONFIGURATIONn = CONFIGURATIONX+NUMBER_OF_NEWCONFIGURATIONS -1,  /* reserved space */
NAMEFORNEWCONFIG,
CONFIGCOPIED,
CONFIGNOTCOPIED,
CONFIGCOPIEDNAME,
/* End of Keep this together */

/* Keep this together */
ARCHIVE,
ARCHIVEX,
ARCHIVEn= ARCHIVEX + NUMBER_OF_MEDIUMS -1 ,     /* reserved space */
NAMEFORNEWMEDIUM,
NEWMEDIUM,
ARCHIVEACTION,
MEDIUMEDIT,
MEDIUMRENAME,
MEDIUMDELETE,
MEDIUMNAME,
MEDIUMCOPIEDNAME,
/* End of Keep this together */


CONFIGACTIONFIRST,
CONFIGUSER                     ,
MAINTENANCE                  ,
RESTART                      ,
SELF_TEST                    ,
FW_UPGRADE                   ,
WIPE_DEV                     ,
BLANK_DEV                    ,
DEVICE_INFO                  ,
AQUA_QR                      ,
CONTACT                      ,
SETTINGS                     ,
DISABLED                     ,
BACK                         ,
NEXT                         ,
UP                           ,
DOWN                         ,
ENTER                        ,
SELSECT                      ,
MENU                         ,
MENUQUIT                     ,
SYSTEMPW                    ,

TRYTOLOGINUSER,
PASSWORDENTRYVALUE,
EXPECTAMTBPASSWORD,
EXPECTSYSPASSWORD,
ACTUALVALUELABEL,
STOREDVALUELABEL,
FIRSTCONFIGSTORED,
NOTSTOREDVALUELABEL,
SELECTEDVALUE,
DATEENTRY                   ,
TAGNUMBER                    ,
TAGENTRYMASK                ,
CURRENTTAG,
ZEROADJUST                  ,
ZEROADJUSTINFO,
TAKEOVER,
TOPADJUST,
TOPADJUSTINFO,
EDIT20MA,
EDIT0MA,
SHOWPARAMINFO,
EDITPARAMINFO,
TAKEOVERPARAMINFO,
EDITPASSWORDINFO,
CONTINUETONEXT,
ANALOGSIGNALSPREAD          ,
ANALOGSIGNALSPREAD04MA       ,
ANALOGSIGNALSPREAD20MA       ,
ANALOGSIGNALSPREAD04MAABS       ,
ANALOGSIGNALSPREAD20MAABS       ,
MASIMULATION,
MASIMULATIONVALUE,
ACTIVEERROR,
FACTORYRESET,
AMTBRESET,
EXECFACTORYRESET,
EXECAMTBRESET,
CODEUSEDSIZE,
RAMUSEDSIZE,
FIRSTOPERATION,
STARTFIRSTOPERATION,
RUNFIRSTOPERATION,
ENDOFRUNFIRST,
SKIPFIRSTOPERATION,
JUMPTODEFAULTSCREEN,
MEASVALUNITS,
SAVEFIRSTOPERATION,
SAVECONFIG,
DELETECONFIG,
EXECUTEDELETE,
SAVEFIRSTCONFIGCONFIRM,
SAVEABORT,
STOREDINFO,
MISSINGBUTTONACTION,
NODELETEFIRST,
QUIT,
DEVICE_DATA,
SENSORDATA,
PROBEDATA,
DEVICENAME,
GERATESERIENNUMMER ,
SOFTWAREVERSION     ,
HARDWAREVERSION     ,
PROOFDATE   ,
FIRSTDATE,
QRMANUAL    ,
QREXDOKUMENTE   ,
QRDOCS,
RAW_FACTOR,
MTI10 ,
MTI20,
MTI30,
MTI50,
MTI100,
MTI200,
MTI400,
MTI600,
MTI_FULL,
BATCH,
EXT_TEMP,
TSS80,
TSS90,
STM,
HG100,
FRGL,
STL,
BAUDRATE,
DATA_BITS,
STOP_BITS,
PARITY,
CTS_RTS,
ZEROVALUEMA,
TOPFULLMA,
ADDTO20MAVALUE,
SIGNALFILTER,
CHOOSEAPP ,
APPBATCH,
APPBATCHADAPTIVE,
APPCONT,
SELECTUSER,
SYSTEMUSER,
PUBLICUSER,
AMTBUSER,
TOBEDONE,
MEASCONFIG,
EDITCONFIG,
CHOOSECONFIG,
NEWCONFIG,
CONFIGACTION,
APPLYCONFIG,
LISTCONFIGPARAS,

CONFIGRENAME,
COPYCONFIG,
CHOOSEMEASCONFIG,
PROBEFULLPOINT,
PROBESERIALNUMBER,
PROBETYPE,
PROBEZEROPOINT,
SENSORSERIALNUMBER,
DEVICECONFIG    ,
OUTPUT,
FAILSAFESTATE,
LOWSTATE,
HIGHSTATE,
FWUPDATE,
PCCONNECTION,
BAUDRATE192,
BAUDRATE115,
STARTUPDATE,
APPLICATION,
SERIALNUMBER,
SHOWPARAMETERSCREEN,
TAKEOVERSCREEN,

ANYPARAMETER,
MESSAGESCREEN,

LOGINPROCESS,  LOGIN,PASSWORDINVALID,PASSWORDVALID,ENTERCHANGEPASSWORD,VERIFYPASSWORD,
CHANGEPASSWORD,NEWPASSWORDENTRY, NEWPASSWORDVERIFY, NEWPASSWORDOK,NEWPASSWORDNOTOK,


TESTSELECTUSER,
NOSTRING,

LAST_STR                  /**< LAST_STR */
} STR;

/**
 * @brief Enum with accessright possibilities
 */

typedef enum{
    noAccess,
    readOnly,
    readWrite,
} accessright_t;

/**
 * @brief Enum with login values
 */

typedef enum{
    publicUser,
    amtbUser,
    systemUser,
    loginUserMax,
} loginUser_t;

typedef enum{
    backWard,
    forWard,
} direction_t;

typedef enum {
    noNumber  = 0,
    numbered = 1,
    isReferenced = 2,
    nr1 = 4,
} menuNumber_t;



typedef enum ScreenEnumTypedef {
    unitializedScreenType,
    noScreenAssigned,
    defaultScreen, // Displays basic needed values
    messageScreen,
    showApplicationScreen,
    logoScreen,
    parameterShowScreen,        /** Screentype for displaying a parameter                                                      **/
    parameterTakeValueScreen,   /** Screentype for editing a prameter                                                      **/
    parameterEditScreen,        /** Screentype for editing a prameter                                                      **/
    parameterEditScreenWithApply,
    listScreen,
    maxScreenTypes
} screenType_t;

typedef enum MenuEnumTypedef {
    listNode = maxScreenTypes, /* Node is a list with more menus and parameters to follow. StartValue is set to distinguish screentypes from menuypes        **/
    compressedListNode,        /* Shows a compressed list of parameters  like an overview of parameters */
    listChildAutoOpens,        /* Next child below this will open the editor without showing the variable selection in the list */
    listChildAutoOpensArray,   /* Loads an autopopening array */
    listNodeAllChildsAutoOpen, /* All nodes below this will open the editor without showing the variable selection in the list */
    singleChooseValuesNode,    /* A single checkbox can be selected */
    multiChooseValuesNode,     /* Several checkboxes can be selected */
    parameterShowNode,         /** Nodetype with a parameter to display                                            **/
    parameterShowNodeMatching, /** Nodetype with a parameter to display if the parent has matched a condition      **/
    parameterShowNodeNotMatching, /** Nodetype with a parameter to display if the parent has not matched a condition  **/
    parameterTakeOverNode,      /** Nodetype with a parameter to take over from a live value **/
    parameterEditNodeWithApply, /** Nodetype with a parameter to edit and apply              **/

    parameterEditNode,          /* Edit a parameter */
    parameterNodeTemplate,      /** Nodetype to indicate a template for a parameter screen                         **/
    passwordEntryNode,          /* Password editor */
    defaultScreenMenuNode,      /** Nodetype to indicate a menu end point containing a parameter                     **/
    messageScreenNode,          /* Messagescreen to dislay an information */
    runParameterEndNodeAction,  /** Last parameter in tree, nothing to do with it **/
    logoScreenNode,
    applicationShowNode,
    maxMenuNodes
} menuNodeType_t;


typedef struct {
    lv_obj_t *obj;
} nodeObj_t;


typedef struct AquaHMI_Task_Struct {
    void (*timerTask)(STR screenID);
    uint32_t period;

    uint8_t runNumberOfTimes;  /* If running more than 1, the screen is left after the n th call. if value is 0, the callback is always called */
} timerTask_t;


typedef struct {
    screenType_t rootScreenType; /* screen type assigned to this menunode  */
    menuNodeType_t menuNodeType; /* Type of node   */
    uint8_t contentIndex;     /* screen content data */
    lv_obj_t *content;     /* screen content data */
    lv_obj_t *topScreen;     /* screen content data */
    lv_group_t *group;     /* group of buttons pointer */
    uint8_t objFocusIndex; /* holds the id of past selected element in a list */
    int8_t enumValue;      /* enum if applicable from the mapChooseListEnums  */
    timerTask_t dynamicReadCallBack;
    lv_res_t (*initScreen)(lv_obj_t *p);
    uint8_t numOfObj;  /* number of items in screen */
    nodeObj_t *nodeObj;/* screen object pointers */
    void (*eventHandler)(lv_event_t *e);
} screenNodeData_t;


/* runtime menu node data for navigation */
typedef struct {
 void (*nextChildIndexLoadedBy);
    int16_t parentIndex;        /* points to the previous child or parent  */
    int16_t firstChildIndex;    /* points to the first child of a parent     */
    int16_t previousChildIndex; /* points to the previous neighbour child    */
    int16_t nextChildIndex;     /* points to the next neighbour child        */
    int16_t nextNodeInFlow;     /* points to the next node in a process flow */
    int16_t childIndexinParent; /* Childindex in parents screen */

    /* Node pointing to the preceding node at runtime */
} screenNodeNavigation_t;

/**
 * @Struct to describe a menu
 */
typedef struct HmiMenuScreen {
    menuNumber_t menuNumberEntry; /* If not null, this menupoint will contain a menuindex in the headerline */
    STR parentStringId; /* Pointer to the parents title */
    STR menuStringId; /* Pointer to the title of the menu, identifies the menu as well */
    STR lastParameterFromARange; /* Points to the last member of range of strings to load */
    STR nextMenuNodeInFlow;   /* Only use this for flowcontrol, when jumping to a another than parent node is required  */
    menuNodeType_t menuNodeType;
} hmiMenuScreen_t;


typedef struct {
    STR menuId;
    STR parentNodeId;    /* ID of parent screen.  */
    int16_t menuIndex;     /*  Index in menuchain */
    menuNumber_t menuNumberEntry; /* If not null, this menupoint will contain a menuindex in the headerline */
    screenNodeData_t nodeData;
    screenNodeNavigation_t nodeNavigation;
    STR sourceNode;      /* Pointer to the source menuIdentifier to retrieve the title of a show or edit menu */
    lv_timer_t * nodeTimer;
} nodeDescriptor_t;


typedef struct {
    uint8_t mainMenuIndex;          /* contains the menu index */
    uint8_t referencedMenuIndex;    /* contains the referenced menu index */
} menuIndex_t;


typedef enum
{
    parameterTypeString,
    parameterTypeInteger,
    parameterTypeTagNumber,  /* A number stored as string, for example the 20 digit tag */
    parameterTypeFloat,
    parameterTypeDate,
    parameterTypeChooseList,
    endOfParameterTypeList}
parameterType_t;

typedef enum
{
    resultNotCopied,
    resultCopied
}
copyResult_t;

/**
 * @brief Structure to hold language-specific string
 */
typedef struct
{
    STR const parameterId;
    parameterType_t parameterType;
    uint8_t editDigits;
    uint8_t editCommas;
    float loLimit;
    float hiLimit;
    char*  defaultValue;

} parametercharacteristics_t;

/**
 * @brief Structure to hold menu+parameters accessibility after login. Note: If not listed, the menu/parameter have full access rights
 */
typedef struct
{
    STR  parameterOrMenuId;
    accessright_t const publicUserRight;
    accessright_t const systemUserRight;
    accessright_t const amtbUserRight;
}
accessRightsTable_t;

/**
 * @brief Structure to map a chooselist parameter with its according enum value to be passed further on in the firmware
 * Note: There has to be a map entry for every single chooselist value. If one is missing, an assert is fired
 */
typedef struct
{
    STR const chooseListParameter;
    uint8_t const chooseListEnum;
}
mapChooseListEnums_t;


/**
 * @brief Structure to define a button action on a parameterEndNode
 *
 */
typedef struct
{
    STR const chooseListParameter;
    void (*parameterEndNodeAction)(lv_event_t *e);
}
parameterEndNodeActions_t;



/**
 * @brief Structure to hold language-specific string
 */
typedef struct
{
    STR const menuIdentification;  /* Identification of menu */
    char const * const text;       /**<Array of pointers to language-specific string */
} MENUSTRINGDEFINITIONS;



/**********************
 *  externals
 **********************/
extern lv_obj_t* lcdScreen;
extern const lv_img_dsc_t AMEI_Display;
extern const lv_img_dsc_t Logo_Aquasant_100x25;
extern nodeDescriptor_t* currentScreen;
extern char const* getParameterValueAsString(STR parameterID);
extern void executeEndNodeDeleteConfigurationOrMedium(lv_timer_t *e);
extern void executeEndNodeCopyConfiguration(lv_event_t *e);
extern void executeEndNodeDeleteMedium(lv_event_t *e);
extern void executeEndNodeApplyConfig(lv_event_t *e);
extern int32_t getParameterValueAsInt(STR parameterID);
extern void executeEndNodeSaveFirstRun(lv_event_t *e);
extern void executeEndNodeSaveAbort(lv_timer_t *e);
extern void executeEndNodeContinueButton(lv_event_t *e);
extern void executeEndNodeSkipFirst(lv_timer_t *e);
extern void executeFactoryReset(lv_timer_t *e);
extern void executeAMTBReset(lv_timer_t *e);
extern parametercharacteristics_t* getParameterCharacteristics(STR nodeId);
extern uint8_t isNodeInBackTrace(nodeDescriptor_t *node);
extern void sendKeyToScreen(uint32_t key);
extern void switchToFirstMenuScreen();
extern int8_t isLastChild(nodeDescriptor_t *actualNode);
void setDownButtonAddress(void *data);
void setEscButtonAddress(void *data);
void setUsedMemoryAddress(void * uint32Address);
void setEnterButtonAddress(void *data);
 void initAquaHMI();
 void AquaHMI_GUI_init();
UnitState AquaHMI_stateControll(UnitState state);

void switchToDefaultScreen();
extern void AquaHMI_write_data(uint8_t data);
extern lv_res_t switchToNode(nodeDescriptor_t * requestedNode);
extern nodeDescriptor_t * findNextNode(nodeDescriptor_t * node);
extern nodeDescriptor_t* findParent(nodeDescriptor_t *child);
extern  UnitState AquaHMI_Init();
extern void AquaHMI_tick(void);

extern  lv_disp_drv_t disp_drv;


#ifdef __cplusplus
}
#endif

#endif /* __AQUAHMI_H */

/************************ (C) COPYRIGHT Aquasant Messtechnik AG *****END OF FILE****/


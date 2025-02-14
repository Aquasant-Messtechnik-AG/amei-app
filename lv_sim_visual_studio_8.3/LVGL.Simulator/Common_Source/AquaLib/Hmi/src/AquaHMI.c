/**
 ******************************************************************************
 * @file     AquaHMI.c
 * @author     Schaer Manuel, Daniel Ritter
 * @date     14 Dez 2017 , Oktober 2023
 * @brief    This file contains the common implementation of the AquaApp unit
 ******************************************************************************
 *
 * Copyright (c) 2017 Aquasant Messtechnik AG
 * All rights reserved.
 *
 *
 ******************************************************************************/
 /*********************
 *      INCLUDES
 *********************/




#include <AquaHMI.h>
#include <time.h>


//#include <regex.h>  TODO no regex in windows so far

#ifndef LVGL_PC_SIM
#include <AquaDisplay.h>

#include <AquaQR.h>
#endif
#include <AquaMultiLanguages.h>
#include <assert.h>



#ifndef LVGL_PC_SIM
//#include "lvgl.h"
#include "../lv_drivers/display/ST7565.h"
//#else
//#include "../../lvgl/lvgl.h"
#endif
#include "lv_conf.h"

//#include <stdlib.h>


/*********************
 *      DEFINES
 *********************/
/* Timer values are given in ms */

#if PL_HAS_SPI_DISPLAY
    #define RUN_TASK_MS                    1
#endif



/* Constants for parametereditor */
#define EDITLEFTARROW           "<"
#define EDITRIGHTARROW           ">"
#define EDITSTORECOMMAND        "OK"
#define SIZEOFEDITBUTTONSPERLINE  10  // maximal characters per edit parameter line


#define SCREEN_FUNCTION_CALLBACK_PERIOD 100
#define SCREEN_FUNCTION_SLOWCALLBACK_PERIOD 1000   //*
/** @brief Number of characters in menu information string */
#define MENUNUMBERCHARS 50


#define MAXEDITSTRINGSIZE 30 /* max number of edit buttons */

#define MAX_QUEUE_DATAREQUESTS 8
#define RED_LED_PWM 5

#define HMI_NEXTFSMSTATE HMIfsmState[0]
#define HMI_CURFSMSTATE  HMIfsmState[1]
#define HMI_OLDFSMSTATE  HMIfsmState[2]

//static AquaFSMState fsmState[3];

#define oldFSMState fsmState[0]
#define curFSMState fsmState[1]
#define nextFSMState fsmState[2]

#define SCREEN_MAP_ENTRY_MAX 9
#define MENU_CHAIN_SIZE 250  /* TODO check size, needs more than items defined */

#define USE_NODE_IMPLEMENTATION 1

#define HW_BUTTON_COUNT 3


#define TOP_LINE_LEFT  32
#define TOP_LINE_RIGHT  14
#define TOP_MENU_HEIGHT 11
#define SIDE_CHART_LINE_T_WIDTH 9
#define SIDE_CHART_LINE_T_HEIGHT  3

/**********************
 *      TYPEDEFS
 **********************/

extern parametercharacteristics_t parameterCharacteristics[];
extern accessRightsTable_t accessRightsTable[];
extern hmiMenuScreen_t menuDefinitions[];
extern mapChooseListEnums_t mapChooseListEnums[];
extern parameterEndNodeActions_t parameterEndNodeActions[];


extern  uint16_t sizeofParameterCharacteristics;
extern  uint16_t sizeOfMapChooseListEnums;
extern  uint8_t sizeofAccessRightsTable;
extern  uint8_t sizeOfParameterEndNodeActions;


typedef struct {
    lv_obj_t *content;

    lv_obj_t *tVLineLeft;
    lv_obj_t *tVLineRight;
    lv_obj_t *tHLineLeft;

    lv_obj_t *measuredValPercentage;
    lv_obj_t *highArrow;
    lv_obj_t *lowArrow;
    lv_obj_t *probeHighValPercentage;
    lv_obj_t *probeLowValPercentage;

    lv_obj_t *label4mA;
    lv_obj_t *label20mA;
    lv_obj_t *centerBody;

} analogChart_t;


typedef struct {
    uint32_t *tmpPtr;
    uint32_t tmpData[2];
    cfgOrDataHasChangedBits_t bit;
} nodeTempData_t;

typedef enum {
    arrayUninitialized, /* Array is not displayed and invalid  */
    arrayVisibleDefaultName,   /* Array is displayed but contains no configured parameters */
    arrayVisibleRenamed    /* Array is displayed and contains configured parameters */
} parameterArrayAttribute;

typedef struct {
    char configName[STRING_CONVERSION_BUFFER_SIZE];
    parameterArrayAttribute  status;
    int32_t enabledUnits;
    int32_t enabledErrors;
    uint8_t  application;
    uint16_t SIGNALFILTER;
    uint32_t minInputValuex100;
    uint32_t maxInputValuex100;
} temporaryInsimulatorOnlyConfigurationSetting_t;

typedef struct {
    char mediumName[STRING_CONVERSION_BUFFER_SIZE];
    parameterArrayAttribute  status;
    uint16_t POINT1000PERC;
} temporaryInsimulatorOnlyArchiveSetting_t;

typedef struct {
    char deviceName[DEVICENAME_SIZE+1];
    char qrDocs[STRING_CONVERSION_BUFFER_SIZE];
    char qrManual[STRING_CONVERSION_BUFFER_SIZE];
    char contact[STRING_CONVERSION_BUFFER_SIZE];
    char configName[CONFIGNAME_SIZE+1];
    char firstDate[DATE_SIZE+1];
    char proofDate[DATE_SIZE+1];
    char tag[TAG_SIZE+1];
    char probeType[PROBENAME_SIZE+1];
    uint8_t     failSafeEnum;
    uint32_t    serialNumber;
    uint32_t    sensorSerialNumber;
    uint32_t    probeSerialNumber;
    uint32_t    softwareVersion;
    uint32_t    hardwareVersion;
    uint16_t    systemPassword;
    uint16_t    amtbPassword;
    uint16_t    addTo20mAValue;
    uint8_t     activeConfiguration;
    uint8_t     editedConfiguration;
    uint8_t     editedArchive;
    uint8_t     activeArchive;
    uint8_t     saveFirstOperationMenu;
} temporaryInsimulatorOnlyDeviceCfg_t;

typedef struct {
    uint8_t     firstSetUpRunCancelled;
    uint8_t     currentSelectedDisplayLines;
    uint16_t    actualPasswordEntry;
    uint16_t    passwordToMatch;
    float       maSimulationValue;
    loginUser_t loginUser;
    loginUser_t tryToLoginUser;

} temporaryInsimulatorRAMOnlyCfg_t;

/**
 * @brief Structure to hold elements used in the parameter editor
 */
typedef struct
{
    lv_event_t *event;                              /* Holds the original event data              */
    nodeDescriptor_t * nodeFromEvent;               /* Holds the node element to be edited        */
    parametercharacteristics_t *characteristics;    /* Holds the parameter characteristics        */
    lv_obj_t *lvglString;                           /* Points to the lvgl screen object           */
    char* textUnderCursor;                          /* Points to the character under the cursor   */
    char* textUnderNextCursor;                      /* Points to the next character under the cursor   */
   char *parameterCurrentEditString;               /* Points to the lvgl screen object as string */
} parameterEditorStruc_t;


/* Common datanode pointer for all screentypes */
typedef enum {

    screenDefaultEventReciver,
    screenDefaultMenuIndex,
    screenDefaultTopLine,
    screenDefaultTopText,
    endOfCommonObjIndex              /* Last index in common datanode pinter */
} screenCommonObjIndex_t;

/* control fields for the parameter editor */
typedef struct  {
    uint8_t * actualCharSet;
    uint8_t editorGroupJustSkipped; /* remembers if ediitor character group has been skipped */
    char parameterEditStringArray[2*MAXEDITSTRINGSIZE][3];   /* After many trials so far the best solution to change button Text with 3 characters only for each label */
} editorControl_t;


typedef enum {

    screenDefaultNamurSymbol = endOfCommonObjIndex,
    screenDefaultMeasValue0,
    screenDefaultMeasValue1,
    screenDefaultMeasValue2,
    screenDefaultMeasValue3,
    screenDefaultMeasUnit0,
    screenDefaultMeasUnit1,
    screenDefaultMeasUnit2,
    screenDefaultMeasUnit3,
} screenDefaultObjIndex_t;

typedef enum {
    screenParameterActualValue = endOfCommonObjIndex,
    screenParamBodyText,
    screenParameterName,
    screenParameterControlButtons,
    screenParameterTakeOverValue,

    screenParamCurrentEditString,
    screenParamCurrentEditIndexLine,
    screenParamCurrentEditButtons,
    screenLogoIndex, /* logo */

    /* First dynamically loaded field address */
    screenParameterStartOfAnyOtherFields,

    /* last field address, is asserted in the screen init, keep it as low as possible TODO DR automate this value */
    screenParameterMaxIndex = screenParameterStartOfAnyOtherFields + 10
} screenParameterContents_t;


typedef enum {
    screenMessageEventReciver,
    screenMessageSymbol = endOfCommonObjIndex,
    screenMessageId,
    screenMessageLabel,
    screenMessageBtnLabelLeft,
    screenMessageBtnLabelMid,
    screenMessageBtnLabelRight,
    screenMessageMaxIndex
} screenMessageObjIndex_t;

typedef enum {
    escKeyIndex = 0,
    downKeyIndex = 1,
    okKeyIndex = 2,

} keyButtonArray_t;


typedef struct  {
#if defined(STM32L1xx) | defined(STM32L0xx)
    GPIO_TypeDef* port;
#endif
#if BGM13S32F512GA
    GPIO_Port_TypeDef port;
#endif
    uint32_t pin;
    uint32_t id;
    lv_indev_state_t lastStates;
    lv_indev_state_t buttonPCStates;
    lv_indev_state_t states;
} buttonArray_t;

typedef struct  {
    buttonArray_t buttons[HW_BUTTON_COUNT];
    uint16_t keyIsPressedForMilliSeconds;
    uint16_t keyIsReleasedForMilliSeconds;
    lv_obj_t* downButton;
    lv_obj_t* enterButton;
    lv_obj_t* escButton;
} buttons_t;

typedef struct  {
    lv_obj_t* sliderProbeRange;
    lv_obj_t* sliderSpreadRange;
} sliders_t;

typedef enum {
#if DEJAVU
    dejavu,
#endif
#if UNSCII
    unscii,
#endif
#if BAHNSCHRIFT
    bahnschrift,
#endif
#if MONSERRAT
    montserrat,
#endif
    none_font
} font_t;

/**********************
 *  GLOBAL variables
 **********************/

nodeDescriptor_t* currentScreen;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static uint32_t used_size;
static uint32_t used_kb ;

uint32_t  debugShowMem(){
     lv_mem_monitor_t mon;
     lv_mem_monitor(&mon);
      used_size = mon.total_size - mon.free_size;;
      used_kb = used_size / 1024;
      return used_size;
}

/**********************
 *  STATIC VARIABLES
 **********************/
static buttons_t buttonStates;
static sliders_t sliderStates;
static uint8_t configurationInFocus;  /* Contains the current configuration in focus */
static uint8_t configurationActive;  /* Contains the current configuration in focus */
static uint8_t mediumInFocus;         /* Contains the current medium in focus */
static modConfigDataStruct_t sim_modConfig;

static hmiConfigDataStruct_t sim_hmiConfig;

static measConfigDataStruct_t sim_measConfig;

static nodeDescriptor_t *menuChainArray[MENU_CHAIN_SIZE];

// Timing variables
static uint16_t runTask;
static lv_disp_drv_t disp_drv;

//static  lv_disp_buf_t disp_buf;
static lv_disp_draw_buf_t disp_buf;

static lv_color_t buf_1[(64  * 128)/ 8];
static lv_color_t buf_2[(64  * 128)/ 8];


lv_obj_t *lcdScreen;


static nodeDescriptor_t genericNode1;  /* two generic nodes for parameter and message screens                            */
static nodeDescriptor_t genericNode2;  /* they are used alternating while one is in erase phase, the other can be active */
static lv_obj_t* memoryUsedDisplay;

static uint16_t tryToGetData[3];

static char buff_data[SMALLSTRINGSIZE];
static char temporaryBuffer[BIGSTRINGSIZE];

static uint16_t btnPort;


//static PLDynamicData local_dymanicData;

static uint32_t fsm_timeout[5];

static uint32_t absMaxAmp1;
static uint32_t absMinAmp1;
static int16_t lastMenuEntryIndex = 0;

static float a0Amp1;
static float a1Amp1;

static uint8_t screenCleared = 0;

/* Pointer for current active cfg's*/
static uint32_t measCfgCrc[NUMBER_OF_CONFIGURATIONS];
static uint32_t modCfgCrc[NUMBER_OF_CONFIGURATIONS];
static uint32_t hmiCfgCrc[NUMBER_OF_CONFIGURATIONS];
static uint32_t sysDescCrc[NUMBER_OF_CONFIGURATIONS];
static uint32_t probCfgCrc[NUMBER_OF_CONFIGURATIONS];
static void switchToNodeController(nodeDescriptor_t* actualNode, void* source);
void initParameterDefaultValuesAll();
static measConfigDataStruct_t measCfg;
static modConfigDataStruct_t modCfg;
static modErrorConfigDataStruct_t modErr;
static systemDesc_t sysDesc;
static ledCfgDataStruct_t ledCfg;
static probeCfgDataStruct_t probeCfg;

static measDataSet_t measData;

//Tasks
static lv_timer_t *logOutTimer = NULL;
static lv_timer_t *buttonsTimer = NULL;

static editorControl_t editorControl;


//GUI

static lv_group_t *default_group;

//Theme
static lv_theme_t* th;
//Styles
static lv_style_t style_default;
static lv_style_t style_symbol;
static lv_style_t style_symbol_inverted;
static lv_style_t style_symbol_small;
static lv_style_t style_symbol_focused;
static lv_style_t style_list_std;
static lv_style_t style_list_focus;
static lv_style_t style_message_inverted;
static lv_style_t style_default_invisible;
static lv_style_t style_small;
static lv_style_t style_lowerKeyInfo;
static lv_style_t style_headerInfo;
static lv_style_t style_headerInfoInverted;
static lv_style_t style_medium;
static lv_style_t style_mediumCentered;
static lv_style_t style_mediumBold;
static lv_style_t style_btn;
static lv_style_t style_bg;
static lv_style_t style_big;
static lv_style_t style_huge;
static lv_style_t style_mega;
static lv_style_t style_megaNumbers;

static lv_style_t style_bodyDark;

static lv_point_t topLinePoints[2];

static lv_point_t sideChartLinePoints_bottom[4];
static lv_point_t sideChartLinePoints_top[4];

static lv_point_t chartLine1[2];
static lv_point_t chartLine2[2];
static lv_point_t chartLine3[2];


static lv_point_t defaultScreenLine1[2];
static lv_point_t paramScreenLine1[2];
lv_draw_rect_dsc_t canvas_desc;
static analogChart_t analogChartDefaultScreen;

#if PL_HAS_FIELD_IFACE & PL_HAS_PULSE_MOD
//static lv_obj_t * pulsesModulationVal;
#endif

#if PL_IS_HMI_1_0 | PL_IS_AME_D_nBT
static lv_obj_t * tempNTC_field;
static lv_obj_t * measAmp_field;
static lv_obj_t * measProcAmp_field;
#endif

static int16_t actualEditIndexInButtonArray;
/**********************
 *      MACROS
 **********************/

/**********************
 *   STATIC FUNCTIONS
 **********************/
static accessright_t getAccessRightForLoggedinUser(STR nodeId);
static char * getParameterFormatString(STR parameterID);
float_t getParameterValueAsFloat(STR parameterID);

static int16_t * findFirstFreeFieldObjectIndex(nodeDescriptor_t *screenNode,int16_t firstSearchIndex, int16_t lastSearchIndex);
static int32_t getParameterChooseListFromStorage(STR parameterID);
static int8_t AquaHmi_set_activeDataCfg(uint8_t cfg);

static int8_t getNumberOfDisplayedLines();
static int8_t insertSingleCheckSymbolIntoList(lv_obj_t * focusedButton, int8_t defaultStateOnInit);
static int8_t isChooseListNode(nodeDescriptor_t *node);
static int8_t isFirstSetup(nodeDescriptor_t *actualNode);
static int8_t setParameterChooseListInStorage(STR parameterID, int8_t childIndex);
static lv_obj_t * fillMenuListScreen(nodeDescriptor_t *requestedNode, uint8_t focusThisIndex);
static lv_obj_t * findNextVisibleElement(lv_obj_t * list);
static nodeDescriptor_t *  prepareParameterScreenFromNode(nodeDescriptor_t * sourceScreen);
static nodeDescriptor_t *  prepareParameterScreen(nodeDescriptor_t * sourceScreen,screenType_t screenType, STR focusedParameterId, STR parentMenuId);
static void pauseScreenTimer(nodeDescriptor_t * node);
static lv_res_t AquaHMI_recalcPreca1StaticData(lv_obj_t *p);
static lv_res_t initApplicationScreen(lv_obj_t *p);
static lv_res_t initDefaultScreen(lv_obj_t *p);
static lv_res_t initLogoScreen(lv_obj_t *p);
static lv_res_t initMessageScreen(nodeDescriptor_t *screenNode);
static lv_res_t initParameterEditScreen(nodeDescriptor_t *screenNode);
static lv_res_t initParameterEditWithApplyScreen(nodeDescriptor_t* screenNode);
static lv_res_t initParameterScreenCommon(nodeDescriptor_t *screenNode);
static lv_res_t initParameterShowScreen(nodeDescriptor_t *screenNode);
static lv_res_t initParameterTakeOverScreen(nodeDescriptor_t *screenNode);
static lv_res_t initScreenArea(nodeDescriptor_t *node);
static void redraw_screenNode(struct _lv_timer_t * timer);
static lv_res_t reserveStorageForScreenObjects(nodeDescriptor_t *node,int numberOfScreenObjects);
static lv_res_t switchScreenTo(menuNodeType_t nodeType);

static nodeDescriptor_t * getNodeFromEvent(lv_event_t *e);
static char* findMenuIndexString(nodeDescriptor_t *node);
static nodeDescriptor_t* findFirstChildInParent(nodeDescriptor_t *actualNode);
static nodeDescriptor_t* findNextChild(nodeDescriptor_t *currentNode);
static nodeDescriptor_t* findNextChildWithCondition(nodeDescriptor_t *actualNode, menuNodeType_t nodeType);
static nodeDescriptor_t* findNodeWithId(STR nodeID);
static nodeDescriptor_t* findNodeWithIndex(uint16_t menuChainIndex);
static nodeDescriptor_t * getNodeFromKeyEventOrTimer(lv_event_t *e);
static nodeDescriptor_t* findNodeWithType(nodeDescriptor_t* startNode,menuNodeType_t screenType);
static nodeDescriptor_t* getNodeFromTimer(lv_timer_t *timer);
static nodeDescriptor_t* loadMenuChainItem(const hmiMenuScreen_t * menuDefine);


static STR findSTRFromEnumValue(uint8_t enumValue);
static systemDesc_t* AquaHmi_get_sysDescription(void);
static uint32_t eventHandlerEscAndDownKeysAndReturnKeyPressCode(lv_event_t *e);
static uint32_t getEventKey(lv_event_t *e);
static uint8_t * getNumberOfVisibleElements(lv_obj_t * list);
static uint8_t AquaHMI_Backlight_DutyCycle(uint8_t duty);
static uint8_t AquaHmi_get_activeDataCfg(void);
static uint8_t dataRequestIndex;
static uint8_t findMappedEnumValueFromSTR(STR nodeId);
static uint8_t getParameterValueWithDependence(STR dependsOn, uint8_t position);
static uint8_t isAutoOpening(nodeDescriptor_t * node);
static uint8_t isKeyPressedLongerThanMilliSeconds(int16_t milliSeconds);
static uint8_t isSameParentRoot(nodeDescriptor_t *node1,nodeDescriptor_t *node2);
static uint8_t isKeyReleasedLongerThanMilliSeconds(int16_t milliSeconds);
static uint8_t isArrayMember(STR menuId,STR firstArrayId);
static uint8_t isNoOrValidArrayEntry(STR menuId);
static uint8_t isUnitDefinition(STR menuId);
static uint8_t isVisibleDependentOnSetting(STR dependsOn, uint8_t indexInCaseOfChooseList);
static uint8_t setParameterValue(STR parameterID, char* parameterString);
static uint8_t setParameterValueFromInt(STR parameterID, int32_t parameterValue);

static void * getEventForParameterEndNode(STR parameterId);
static void activateScreen(nodeDescriptor_t * newNodeToSet);

static void AquaHMI_Init_Timer(void);

static void AquaHMI_printNamurSymbolsFromNamurState(lv_obj_t *nodeOb, namurBitFieldPos_t namurState);


static void AquaHMI_styles_init(void);
static void updateMenuIndexString(nodeDescriptor_t *node);
static copyResult_t copyConfiguration(nodeDescriptor_t *screenNode);
static void createTimerTask(nodeDescriptor_t *actualNode);
static void deactivateCheckSymbolInList(lv_obj_t * oldfocusedButton);
static void drawLine(lv_obj_t *lineItem, lv_obj_t *content,lv_point_t *chartLine, int x, int y, int x1, int y1);
static void deleteTimer(nodeDescriptor_t * node);
static void eraseNodesObjects(nodeDescriptor_t *node);
static void eraseScreenNodeTasksAndObjects(nodeDescriptor_t *screenNode);
static void eventHandlerApplicationFirstScreenTimeOut(lv_timer_t *timer);
static void eventHandlerChooseScreenKey(lv_event_t *e);
static void eventHandlerCompressedList(lv_event_t *e);
static void eventHandlerDefaultScreenKeyPressed(lv_event_t *e);
static void eventHandlerDefaultScreenNextKey();
static void eventHandlerListKey(lv_event_t *e);
static void eventHandlerListKeyStoreUser(lv_event_t *e);
static void eventHandlerLogoScreenTimeOut(lv_timer_t *timer);
static void eventHandlerMessageScreen(lv_event_t *e);
static void eventHandlerParameterEditNode(lv_event_t *e);
static void eventHandlerParameterEditNodeWithApply(lv_event_t *e);
static void eventHandlerParameterEditorDownKey(parameterEditorStruc_t * editData);
static void eventHandlerParameterEditorEnterKey(parameterEditorStruc_t * editData);
static void eventHandlerParameterEditorEscKey(parameterEditorStruc_t * editData);
static void eventHandlerParameterEditorKey(lv_event_t * e);
static void eventHandlerParameterEndNode(lv_event_t *e);
static void eventHandlerParameterShowNode(lv_event_t *e);
static void eventHandlerParameterShowNodeKey(lv_event_t *e);
static void eventHandlerParameterTakeOver(lv_event_t *e);
static void eventHandlerParameterTakeOverKey(lv_event_t *e);
static void eventHandlerScreenTimeOutToDefaultScreen(lv_timer_t *timer);
static void eventHandlerScreenTimeOutToNextNode(lv_timer_t *timer);
static void eventShowParameterScreen(lv_timer_t *timer);
static void fillEditAndApplyScreen(lv_timer_t *timer);
static void fillParameterInApplicationInfoScreen(lv_timer_t *timer);
static void fillSimpleInfoScreen(lv_timer_t *timer);
static void initAnalogChart(nodeDescriptor_t *screenNode);
static void initButtons(void);
static void initDefaultScreenValueAndUnitPositions(nodeDescriptor_t *screenNode);
static void initParameterEditButtons(parametercharacteristics_t * editParameterCharacteristics,char* parameterString,nodeDescriptor_t * node);
static void initTopScreen(nodeDescriptor_t * node);
static void loadMenuChain(void);
static void loadNavigation();
static void loadProcessFlowPointers(void);
static void requestDynamicData(void *p);
static void requestParameterFromStorageAndFillDynamicFields(lv_timer_t *timer);
static void resetSingleCharacterEditControl();
static void showHeaderInformation(nodeDescriptor_t *node);
static void setDisplayLineVisibility(lv_obj_t * screenItem, uint8_t visible);
static void showMessage(nodeDescriptor_t *actualNode, STR message);
static void showMessageTemporary(nodeDescriptor_t *actualNode, STR messageFromStringTable);
static void initDisplayLineLayout(nodeDescriptor_t *node);
static void startLogOutTimer();
static void updateHeaderInformations(lv_group_t *e);
static void updateHeaderInformationsFromNode(nodeDescriptor_t *node);
static lv_obj_t* memoryUsedDisplay;

static modConfigDataStruct_t sim_modConfig;

static measConfigDataStruct_t sim_measConfig;

static measDataSet_t     sim_measDataSet;

static void modRangeSlider_event_cb(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);

    /*Provide some extra space for the value*/
    if (code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
        lv_event_set_ext_draw_size(e, 50);
    }
    else if (code == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_part_dsc_t* dsc = lv_event_get_draw_part_dsc(e);
        if (dsc->part == LV_PART_INDICATOR) {
            char buf[200];
            double left = (float)lv_slider_get_left_value(obj);
            double value = (float)lv_slider_get_value(obj);

            sprintf(buf, "%.3f%% - %.3f%%", left, value);

            lv_point_t label_size;
            lv_txt_get_size(&label_size, buf, LV_FONT_DEFAULT, 0, 0, LV_COORD_MAX, 0);
            lv_area_t label_area;
            label_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2 - label_size.x / 2;
            label_area.x2 = label_area.x1 + label_size.x;
            label_area.y2 = dsc->draw_area->y1 - 5;
            label_area.y1 = label_area.y2 - label_size.y;

            lv_draw_label_dsc_t label_draw_dsc;
            lv_draw_label_dsc_init(&label_draw_dsc);
            label_draw_dsc.color = lv_color_black();// lv_color_hex3(0x888);
            lv_draw_label(dsc->draw_ctx, &label_draw_dsc, &label_area, buf, NULL);
        }
    }if (code == LV_EVENT_VALUE_CHANGED) {



        sim_modConfig.minInputValue = (float)lv_slider_get_left_value(obj);
        sim_modConfig.maxInputValue = (float)lv_slider_get_value(obj);
        //      if(sim_modConfig.activeType==curSink){
        sim_modConfig.transformFactor = (float)((sim_modConfig.maxModValue - sim_modConfig.minModValue) / ((float)((uint32_t)sim_modConfig.maxInputValue - (uint32_t)sim_modConfig.minInputValue)));
        //      }

    }
}



static const char* namur_btnm_map[] = { LV_SYMBOL_NAMUR_V2_CHECK,LV_SYMBOL_NAMUR_V2_CHECKED,LV_SYMBOL_NAMUR_V2_UNCHECKED,LV_SYMBOL_NAMUR_V2_FAULT,
        LV_SYMBOL_NAMUR_V2_MAINTENENCE,LV_SYMBOL_NAMUR_V2_OUT_OF_RANGE,"" };
lv_group_t* lvgl_sim_group;
lv_style_t  styleButtonSim;

lv_style_t  styleNamurFontSim;
lv_style_t  styleNamurFontSimInv;

static void sysTempValueSlider_event_cb(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);

    /*Provide some extra space for the value*/
    if (code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
        lv_event_set_ext_draw_size(e, 50);
    }
    else if (code == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_part_dsc_t* dsc = lv_event_get_draw_part_dsc(e);
        if (dsc->part == LV_PART_INDICATOR) {
            char buf[16];
            lv_snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(obj));

            lv_point_t label_size;
            lv_txt_get_size(&label_size, buf, LV_FONT_DEFAULT, 0, 0, LV_COORD_MAX, 0);
            lv_area_t label_area;
            label_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2 - label_size.x / 2;
            label_area.x2 = label_area.x1 + label_size.x;
            label_area.y2 = dsc->draw_area->y1 - 5;
            label_area.y1 = label_area.y2 - label_size.y;

            lv_draw_label_dsc_t label_draw_dsc;
            lv_draw_label_dsc_init(&label_draw_dsc);
            label_draw_dsc.color = lv_color_black();// lv_color_hex3(0x888);
            lv_draw_label(dsc->draw_ctx, &label_draw_dsc, &label_area, buf, NULL);
        }

    }
    else if (code == LV_EVENT_VALUE_CHANGED) {
        uint8_t needToUpdate = 0;

        sim_measDataSet.temp_NTC = (uint32_t)lv_slider_get_value(obj);




        if ((int32_t)lv_slider_get_value(obj) > 65) {
            return;
        }
        if ((int32_t)lv_slider_get_value(obj) < -20) {

            return;
        }

        uint8_t needToClear = 0;



    }
}

void measValueSlider_event_cb(lv_event_t* e)
{
}

static void probeRangeSlider_event_cb(lv_event_t* e);

static void modRangeSlider_event_cb(lv_event_t* e);
static void sysTempValueSlider_event_cb(lv_event_t* e);





static void lvgl_initControllPanel(void) {

    lv_obj_t* slider;
    lv_obj_t* label;
    lv_obj_t* content = lv_obj_create(lv_scr_act());
    char smallBuffer[100];

    //  lv_obj_add_style(cont, , selector)
    lv_obj_set_size(content, LV_HOR_RES, 250);
    lv_obj_align_to(content, lv_scr_act(), LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_update_layout(content);

    /* NAMUR btn matrix */

    lv_obj_t* btnm1 = lv_btnmatrix_create(content);
    lv_obj_set_size(btnm1, 290, 30);
    lv_obj_add_style(btnm1, &styleNamurFontSim, 0);
    lv_obj_add_style(btnm1, &styleNamurFontSimInv, LV_EVENT_CLICKED);
    lv_btnmatrix_set_map(btnm1, namur_btnm_map);

    for (uint8_t i = 0; i < 6; i++) {//     for(uint8_t i=0;i<lv_obj_get_child_cnt(btnm1);i++){
        lv_btnmatrix_set_btn_ctrl(btnm1, i, LV_BTNMATRIX_CTRL_CHECKABLE);
    }
    lv_obj_align_to(btnm1, content, LV_ALIGN_TOP_RIGHT, 0, 0);

    char key = LV_KEY_RIGHT;
    lv_btnmatrix_set_selected_btn(btnm1, 1);
    lv_event_send(btnm1, LV_EVENT_PRESSED, &key);



    /*Create a slider in the center of the display*/
    lv_obj_t* sysTempValueGroup = lv_obj_create(content);
    lv_obj_set_size(sysTempValueGroup, 290, 40);
    lv_obj_align_to(sysTempValueGroup, btnm1, LV_ALIGN_OUT_BOTTOM_MID, 0, 3);
    label = lv_label_create(sysTempValueGroup);
    lv_label_set_text(label, "System temperatur");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_t* sliderSysTempValue = lv_slider_create(sysTempValueGroup);
    //    lv_obj_center(ProbeRangeGroup);
    lv_obj_set_height(sliderSysTempValue, 4);
    lv_obj_align(sliderSysTempValue, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_slider_set_mode(sliderSysTempValue, LV_SLIDER_MODE_NORMAL);
    lv_bar_set_range(sliderSysTempValue, -50, 100);
    lv_slider_set_value(sliderSysTempValue, 0, LV_ANIM_OFF);
    //      lv_slider_set_left_value(sliderMeasValue, lv_slider_get_max_value(sliderMeasValue)/100*20, LV_ANIM_OFF);

    lv_obj_add_event_cb(sliderSysTempValue, sysTempValueSlider_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_refresh_ext_draw_size(sliderSysTempValue);


    /*Create a slider in the center of the display*/
    lv_obj_t* memValueGroup = lv_obj_create(content);
    lv_obj_set_size(memValueGroup, 290, 40);
    lv_obj_align_to(memValueGroup, btnm1, LV_ALIGN_OUT_BOTTOM_MID, 0, 3);

    label = lv_label_create(memValueGroup);
    lv_label_set_text(label, "System memory");

    memoryUsedDisplay = lv_label_create(memValueGroup);
    setUsedMemoryAddress(memoryUsedDisplay);

    lv_obj_align(memoryUsedDisplay, LV_ALIGN_TOP_LEFT, 0, 20);


    /*Create a slider in the center of the display*/
    lv_obj_t* ProbeAdjustGroup = lv_obj_create(content);
    lv_obj_set_size(ProbeAdjustGroup, 290, 40);
    lv_obj_align_to(ProbeAdjustGroup, content, LV_ALIGN_TOP_LEFT, 0, 0);
    label = lv_label_create(ProbeAdjustGroup);
    lv_label_set_text(label, "Null/Nassabgleich");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_t* sliderProbeAdjustZeroFull = lv_slider_create(ProbeAdjustGroup);
    //    lv_obj_center(ProbeRangeGroup);
    lv_obj_set_height(sliderProbeAdjustZeroFull, 4);
    lv_obj_align(sliderProbeAdjustZeroFull, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_slider_set_mode(sliderProbeAdjustZeroFull, LV_SLIDER_MODE_RANGE);
    lv_bar_set_range(sliderProbeAdjustZeroFull, 0, 1000000);
    lv_slider_set_value(sliderProbeAdjustZeroFull, sim_measConfig.probeMaxRawValue, LV_ANIM_OFF);
    lv_slider_set_left_value(sliderProbeAdjustZeroFull, sim_measConfig.probeMinRawValue, LV_ANIM_OFF);

    //  lv_obj_add_event_cb(sliderProbeAdjustZeroFull, probeRangeSlider_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_refresh_ext_draw_size(sliderProbeAdjustZeroFull);





    /*Create a slider in the center of the display*/
    lv_obj_t* spreadRangeGroup = lv_obj_create(content);
    lv_obj_set_size(spreadRangeGroup, 290, 40);
    lv_obj_align_to(spreadRangeGroup, ProbeAdjustGroup, LV_ALIGN_OUT_BOTTOM_MID, 0, 3);
    label = lv_label_create(spreadRangeGroup);
    lv_label_set_text(label, "Spreizung 4/20mA");

    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_update_layout(label);

    lv_obj_t* sliderSpreadRange = lv_slider_create(spreadRangeGroup);
    lv_obj_set_height(sliderSpreadRange, 4);
    lv_obj_align(sliderSpreadRange, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_bar_set_range(sliderSpreadRange, 0, 100.00);// sim_measConfig.probeMinRawValue, sim_measConfig.probeMaxRawValue);
    lv_slider_set_mode(sliderSpreadRange, LV_SLIDER_MODE_RANGE);
    lv_slider_set_value(sliderSpreadRange, sim_measConfig.rangeMaxRawValue, LV_ANIM_OFF);
    lv_slider_set_left_value(sliderSpreadRange, sim_measConfig.rangeMinRawValue, LV_ANIM_OFF);

    lv_obj_add_event_cb(sliderSpreadRange, modRangeSlider_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_refresh_ext_draw_size(sliderSpreadRange);

    /*Create a slider in the center of the display*/
    lv_obj_t* measValueGroup = lv_obj_create(content);
    lv_obj_set_size(measValueGroup, 290, 40);
    lv_obj_align_to(measValueGroup, spreadRangeGroup, LV_ALIGN_OUT_BOTTOM_MID, 0, 3);
    label = lv_label_create(measValueGroup);
    lv_label_set_text(label, "Measurement Value");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_t* sliderMeasValue = lv_slider_create(measValueGroup);

    lv_obj_set_height(sliderMeasValue, 4);
    lv_obj_align(sliderMeasValue, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_slider_set_mode(sliderMeasValue, LV_SLIDER_MODE_NORMAL);
    lv_bar_set_range(sliderMeasValue, lv_slider_get_min_value(sliderProbeAdjustZeroFull), lv_slider_get_max_value(sliderProbeAdjustZeroFull));
    lv_slider_set_value(sliderMeasValue, sim_measConfig.rangeMinRawValue, LV_ANIM_OFF);

    lv_obj_add_event_cb(sliderMeasValue, measValueSlider_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_refresh_ext_draw_size(sliderMeasValue);

    // setModSliderAddress(sliderSpreadRange);
}

static void   sim_init_staticData(void) {

    sim_measConfig.probeMaxRawValue = 700000;
    sim_measConfig.probeMinRawValue = 200000;


    sim_measConfig.rangeMaxRawValue = 100;
    sim_measConfig.rangeMinRawValue = 0;

    sim_measConfig.mtiMode = ProbeRange;



    sim_hmiConfig.lang = 2;
    sim_hmiConfig.dispCfg.brightness = 5;
    sim_hmiConfig.dispCfg.contrast = 50;
    sim_hmiConfig.dispCfg.delay_PowerOffBacklight = 0;
    sim_hmiConfig.menuDispCfg.delay_PowerOffDelay = 0;
    sim_hmiConfig.menuDispCfg.delay_backToDefaultscreen = 60;
    sim_hmiConfig.dispCfg.enableFlag = 1;
    sim_hmiConfig.dispCfg.inverseFlag = 1;
    sim_hmiConfig.mainDispCfg.MeasuringUnits[0] = unitsmAmps;
    sim_hmiConfig.mainDispCfg.MeasuringUnits[1] = unitsmAmps;
    sim_hmiConfig.mainDispCfg.MeasuringUnits[2] = unitsCapacity;
    sim_hmiConfig.mainDispCfg.MeasuringUnits[3] = unitsNone;

    sim_hmiConfig.mainDispCfg.chart = chartTrennschicht;
    sim_hmiConfig.mainDispCfg.chartUnit[0] = unitsPercentSond;
    sim_hmiConfig.mainDispCfg.chartUnit[1] = unitsmAmps;


    sim_modConfig.maxInputValue = (uint32_t)sim_measConfig.probeMaxRawValue;
    sim_modConfig.maxModValue = 20000;
    sim_modConfig.minInputValue = (uint32_t)sim_measConfig.probeMinRawValue;
    sim_modConfig.minModValue = 4000;
    sim_modConfig.transformFactor = ((sim_modConfig.maxModValue - sim_modConfig.minModValue) /
        ((float)(sim_modConfig.maxInputValue - sim_modConfig.minInputValue)));

    sim_measDataSet.ampDiffLin = sim_measConfig.rangeMinRawValue;

}

UnitState AquaHMI_Init() {

    UnitState uState = ERR;

    LV_IMG_DECLARE(AMEI_Display);

    /*-----------------------------------------------------------------------------------------------------------------/
     preset variables
     ------------------------------------------------------------------------------------------------------------------*/

    absMinAmp1 = 0xFFFFFFFF;
    absMaxAmp1 = 0;

    sim_init_staticData();
  //  lvgl_initControllPanel();


 
    AquaHMI_styles_init();
    AquaHMI_GUI_init();
    loadMenuChain();
    loadNavigation();
    loadProcessFlowPointers();


    AquaHMI_Init_Timer();

    /*-----------------------------------------------------------------------------------------------------------------/
     Init Display
     ------------------------------------------------------------------------------------------------------------------*/





    if (currentScreen == NULL) {
        initLogoScreen(NULL);
    }
    return uState;

}

int32_t AquaHMI_anim_path_none(const lv_anim_t *a) {
    return a->end_value;
}

static void AquaHMI_styles_init(void) {
    /*-----------------------------------------------------------------------------------------------------------------/
     Init theme and styles
     ------------------------------------------------------------------------------------------------------------------*/
    /*
     * Generate default style (style_default)
     */

    lv_style_init(&style_bg);
    lv_style_set_pad_all(&style_bg, 0);
    lv_style_set_pad_gap(&style_bg, 0);
    lv_style_set_clip_corner(&style_bg, true);
    lv_style_set_border_width(&style_bg, 0);

    lv_style_init(&style_btn);

    lv_style_set_radius(&style_btn, 0);

    lv_style_set_text_font(&style_btn, &DejaVuSansMono_8);

    lv_style_set_bg_color(&style_btn, lv_color_white());
    lv_style_set_text_color(&style_btn, lv_color_black());
   // lv_style_set_border_width(&style_btn, 1);
    lv_style_set_height(&style_btn, 6);
    lv_style_set_width(&style_btn, 10);
    lv_style_set_border_opa(&style_btn, LV_OPA_0);
    lv_style_set_border_color(&style_btn, lv_palette_main(LV_PALETTE_NONE));
    lv_style_set_border_side(&style_btn, LV_BORDER_SIDE_INTERNAL);

    lv_style_init(&style_default);
    lv_style_set_text_color(&style_default, lv_color_black());
    lv_style_set_text_font(&style_default, &DejaVuSansMono_8);
    lv_style_set_anim_time(&style_default, 110);
    lv_style_set_anim_speed(&style_default, 110);
    lv_style_set_radius(&style_default, 0);
    lv_style_set_outline_width(&style_default, 0);
    lv_style_set_pad_all(&style_default, 0);
    lv_style_set_border_width(&style_default, 0);
    lv_style_set_border_color(&style_default, lv_color_white());


#define LAYOUT_DEV_BORDER 0

#if LAYOUT_DEV_BORDER
    lv_style_set_border_color(&style_default, lv_color_black());
    lv_style_set_border_width(&style_default, (lv_coord_t)1);
#endif


    lv_style_init(&style_symbol_small);
    lv_style_set_text_color(&style_symbol_small, lv_color_black());
    lv_style_set_text_font(&style_symbol_small, &font_Symbols_7);
    lv_style_set_anim_time(&style_symbol_small, 0);
    lv_style_set_anim_speed(&style_symbol_small, 0);
    lv_style_set_radius(&style_symbol_small, 0);
    lv_style_set_outline_width(&style_symbol_small, 0);
    lv_style_set_pad_all(&style_symbol_small, 0);

    lv_style_init(&style_symbol);
    lv_style_set_text_color(&style_symbol, lv_color_black());
    lv_style_set_text_font(&style_symbol, &font_Symbols_12);
    lv_style_set_anim_time(&style_symbol, 0);
    lv_style_set_anim_speed(&style_symbol, 0);
    lv_style_set_radius(&style_symbol, 0);
    lv_style_set_outline_width(&style_symbol, 0);
    lv_style_set_pad_all(&style_symbol, 0);
    lv_style_set_border_width(&style_symbol, 0);

    lv_style_init(&style_symbol_focused);
    lv_style_set_text_color(&style_symbol_focused, lv_color_white());
    lv_style_set_text_font(&style_symbol_focused, &font_Symbols_12);
    lv_style_set_anim_time(&style_symbol_focused, 0);
    lv_style_set_anim_speed(&style_symbol_focused, 0);
    lv_style_set_radius(&style_symbol_focused, 0);
    lv_style_set_outline_width(&style_symbol_focused, 0);
    lv_style_set_pad_all(&style_symbol_focused, 0);
    lv_style_set_border_width(&style_symbol_focused, 0);
    lv_style_set_bg_color(&style_list_std, lv_color_black());

    style_symbol_inverted = style_symbol_focused;
    /*
     * Generate default style (style_list_std)
     */

    lv_style_init(&style_list_std);
    lv_style_set_radius(&style_list_std, 0);
    lv_style_set_text_color(&style_list_std, lv_color_black());
    lv_style_set_text_font(&style_list_std, &DejaVuSans_9);
    lv_style_set_anim_time(&style_list_std, 1110);
    lv_style_set_anim_speed(&style_list_std, 0);
    lv_style_set_text_align(&style_list_std, LV_TEXT_ALIGN_LEFT);
    lv_style_set_text_line_space(&style_list_std, 0);
    lv_style_set_border_width(&style_list_std, 0);
    lv_style_set_pad_top(&style_list_std, 0);
    lv_style_set_pad_bottom(&style_list_std, 0);
    lv_style_set_outline_width(&style_list_std, 0);
    lv_style_set_pad_bottom(&style_list_std, 0);
    lv_style_set_border_color(&style_list_std, lv_color_white());
    lv_style_set_outline_color(&style_list_std, lv_color_white());
    lv_style_set_bg_color(&style_list_std, lv_color_white());
    /*
     * Generate default style (style_list_focus)
     */

    lv_style_init(&style_list_focus);

    lv_style_set_radius(&style_list_focus, 0);
    lv_style_set_text_color(&style_list_focus, lv_color_white());
    //   lv_style_set_text_color(&style_list_focus, lv_color_black());
    lv_style_set_text_align(&style_list_focus, LV_TEXT_ALIGN_LEFT);
    lv_style_set_text_font(&style_list_focus, &DejaVuSans_9);
    lv_style_set_border_width(&style_list_focus, 0);
    lv_style_set_anim_time(&style_list_focus, 0);
    lv_style_set_anim_speed(&style_list_focus, 0);
    lv_style_set_pad_top(&style_list_focus, 0);
    lv_style_set_pad_bottom(&style_list_focus, 0);
    //       lv_style_set_opa(&style_list_focus, LV_OPA_MAX);
    lv_style_set_border_color(&style_list_focus, lv_color_black());
    lv_style_set_outline_color(&style_list_focus, lv_color_black());
    lv_style_set_bg_color(&style_list_focus, lv_color_black());
    //       lv_style_set_opa(&style_list_focus, LV_OPA_COVER);

    lv_style_init(&style_message_inverted);

    lv_style_set_radius(&style_message_inverted, 0);
    lv_style_set_text_color(&style_message_inverted, lv_color_white());
    //   lv_style_set_text_color(&style_list_focus, lv_color_black());
    lv_style_set_text_align(&style_message_inverted, LV_TEXT_ALIGN_LEFT);
    lv_style_set_text_font(&style_message_inverted, &DejaVuSansMono_8);
    lv_style_set_border_width(&style_message_inverted, 0);
    lv_style_set_anim_time(&style_message_inverted, 0);
    lv_style_set_anim_speed(&style_message_inverted, 0);
    lv_style_set_pad_top(&style_message_inverted, 0);
    lv_style_set_pad_bottom(&style_message_inverted, 0);
    lv_style_set_border_width(&style_message_inverted, 0);
    //           lv_style_set_bg_(&style_message_inverted, 1);
    //       lv_style_set_opa(&style_list_focus, LV_OPA_MAX);
    lv_style_set_border_color(&style_message_inverted, lv_color_white());
    lv_style_set_outline_color(&style_message_inverted, lv_color_black());
    lv_style_set_bg_color(&style_message_inverted, lv_color_black());

    lv_style_init(&style_bodyDark);
    lv_style_set_radius(&style_bodyDark, 0);
    lv_style_set_text_color(&style_bodyDark, lv_color_white());
    //   lv_style_set_text_color(&style_bodyDark, lv_color_black());
    //           lv_style_set_text_align(&style_bodyDark, LV_TEXT_ALIGN_LEFT);
    //           lv_style_set_text_font(&style_bodyDark, &DejaVuSans_10);
    lv_style_set_border_width(&style_bodyDark, 0);
    lv_style_set_anim_time(&style_bodyDark, 0);
    lv_style_set_anim_speed(&style_bodyDark, 0);
    lv_style_set_pad_top(&style_bodyDark, 0);
    lv_style_set_pad_bottom(&style_bodyDark, 0);
    lv_style_set_border_color(&style_bodyDark, lv_color_black());
    lv_style_set_outline_color(&style_bodyDark, lv_color_black());
    lv_style_set_bg_color(&style_bodyDark, lv_color_black());
    //           lv_style_set_opa(&style_bodyDark, LV_OPA_COVER);

    lv_style_init(&style_lowerKeyInfo);
    lv_style_set_text_color(&style_lowerKeyInfo, lv_color_black());
    lv_style_set_text_font(&style_lowerKeyInfo, &lv_font_unscii_8);
    lv_style_set_text_align(&style_lowerKeyInfo, LV_TEXT_ALIGN_CENTER);
    lv_style_set_border_width(&style_lowerKeyInfo, 0);
    lv_style_set_anim_time(&style_lowerKeyInfo, 0);
    lv_style_set_anim_speed(&style_lowerKeyInfo, 0);
    lv_style_set_pad_top(&style_lowerKeyInfo, 0);
    lv_style_set_pad_bottom(&style_lowerKeyInfo, 0);

    lv_style_init(&style_headerInfo);
    lv_style_set_text_color(&style_headerInfo, lv_color_black());
    lv_style_set_text_font(&style_headerInfo, &DejaVuSansMono_8);
    lv_style_set_text_align(&style_headerInfo, LV_TEXT_ALIGN_LEFT);
    lv_style_set_border_width(&style_headerInfo, 0);

    lv_style_set_anim_time(&style_headerInfo, 0);
    lv_style_set_anim_speed(&style_headerInfo, 0);
    lv_style_set_pad_top(&style_headerInfo, 0);
    lv_style_set_pad_left(&style_headerInfo, 0);
    lv_style_set_pad_right(&style_headerInfo, 0);
    lv_style_set_pad_bottom(&style_headerInfo, 0);
    lv_style_set_outline_width(&style_headerInfo, 0);
    lv_style_set_line_color(&style_headerInfo, lv_color_black());
    lv_style_set_line_width(&style_headerInfo, 1);
    //           lv_obj_get_style_bg_color(&style_headerInfo, lv_color_black());

    lv_style_init(&style_headerInfoInverted);

    lv_style_set_text_font(&style_headerInfoInverted, &DejaVuSansMono_8);
    lv_style_set_text_align(&style_headerInfoInverted, LV_TEXT_ALIGN_LEFT);
    lv_style_set_border_width(&style_headerInfoInverted, 0);

    lv_style_set_anim_time(&style_headerInfoInverted, 0);
    lv_style_set_anim_speed(&style_headerInfoInverted, 0);
    lv_style_set_pad_top(&style_headerInfoInverted, 0);
    lv_style_set_pad_left(&style_headerInfoInverted, 0);
    lv_style_set_pad_right(&style_headerInfoInverted, 0);
    lv_style_set_pad_bottom(&style_headerInfoInverted, 0);
    lv_style_set_outline_width(&style_headerInfoInverted, 0);
    lv_style_set_line_color(&style_headerInfoInverted, lv_color_black());
    lv_style_set_line_width(&style_headerInfoInverted, 1);
    lv_style_set_text_color(&style_headerInfoInverted, lv_color_white());
    lv_style_set_bg_color(&style_headerInfoInverted, lv_color_black());
    /*
     * Generate small  style (style_small)
     */
    lv_style_init(&style_small);
    lv_style_set_text_color(&style_small, lv_color_black());
    lv_style_set_text_font(&style_small, &DejaVuSansMono_6);
    /*
     * Generate medium  style (style_medium)
     */
    style_medium = style_default;
    lv_style_init(&style_mediumCentered);
    lv_style_set_text_align(&style_mediumCentered, LV_TEXT_ALIGN_CENTER);

    lv_style_init(&style_mediumBold);
    lv_style_set_text_font(&style_default, &DejaVuSansMono_8);

    /*
     * Generate big  style (style_big)
     */
    lv_style_init(&style_big);
    lv_style_set_text_color(&style_big, lv_color_black());
    lv_style_set_text_font(&style_big, &DejaVuSans_10);
    lv_style_set_outline_width(&style_big, 0);
    lv_style_set_pad_all(&style_big, 0);


#if LAYOUT_DEV_BORDER
    lv_style_set_border_color(&style_big, lv_color_black());
    lv_style_set_border_width(&style_big, (lv_coord_t)1);
#endif

/*
 * Generate huge  style (style_huge)
 */
    lv_style_init(&style_huge);
    lv_style_set_text_color(&style_huge, lv_color_black());
    lv_style_set_text_font(&style_huge, &DejaVuSans_15);
    lv_style_set_outline_width(&style_huge, 0);
    lv_style_set_pad_all(&style_huge, 0);

#if LAYOUT_DEV_BORDER
    lv_style_set_border_color(&style_huge, lv_color_black());
    lv_style_set_border_width(&style_huge, (lv_coord_t)1);
#endif

    lv_style_init(&style_mega);
    lv_style_set_text_color(&style_mega, lv_color_black());
    lv_style_set_text_font(&style_mega, &DejaVuSans_28);
    lv_style_set_outline_width(&style_mega, 0);
    lv_style_set_pad_all(&style_mega, 0);

    lv_style_init(&style_megaNumbers);
    lv_style_set_text_color(&style_megaNumbers, lv_color_black());
    lv_style_set_text_font(&style_megaNumbers, &font_Symbols_30);
    lv_style_set_outline_width(&style_megaNumbers, 0);
    lv_style_set_pad_all(&style_megaNumbers, 0);

#if LAYOUT_DEV_BORDER
    lv_style_set_border_color(&style_mega, lv_color_black());
    lv_style_set_border_width(&style_mega, (lv_coord_t)1);
#endif

    lv_style_init(&style_default_invisible);
    lv_style_set_opa(&style_default_invisible, LV_OPA_TRANSP);
    lv_style_set_border_width(&style_default_invisible, 0);

    /*
     * Generate window  style (style_win_header)
     */
    topLinePoints[0].x = TOP_LINE_LEFT;
    topLinePoints[0].y = TOP_MENU_HEIGHT;
    topLinePoints[1].x = 128 - TOP_LINE_RIGHT;
    topLinePoints[1].y = TOP_MENU_HEIGHT;

    sideChartLinePoints_top[0].x = 11;
    sideChartLinePoints_top[0].y = 50;

    sideChartLinePoints_top[1].x = 11;
    sideChartLinePoints_top[1].y = 60;

    sideChartLinePoints_bottom[0].x = 0;
    sideChartLinePoints_bottom[0].y = 3;

    sideChartLinePoints_bottom[1].x = 0 + 9;
    sideChartLinePoints_bottom[1].y = 3;

    sideChartLinePoints_bottom[2].x = 0 + 9 / 2;
    sideChartLinePoints_bottom[2].y = 3;

    sideChartLinePoints_bottom[3].x = 0 + 9 / 2;
    sideChartLinePoints_bottom[3].y = 0;
}


nodeDescriptor_t* findParent(nodeDescriptor_t *child) {

    int16_t parentIndex = child->nodeNavigation.parentIndex;
    return findNodeWithIndex(parentIndex);
}

static nodeDescriptor_t* findScreenTemplateWithType(menuNodeType_t nodeType) {

    int16_t index = lastMenuEntryIndex - 1;
    nodeDescriptor_t *node;
    printf(" findScreenTemplateWithType\n");
    do {
        node = menuChainArray[index];
        if (node->nodeData.menuNodeType == nodeType){

            if (genericNode2.menuIndex <= 0) {
                memset(&genericNode2, 0x00, sizeof(nodeDescriptor_t));
                memcpy(&genericNode2,node,sizeof(nodeDescriptor_t));
                node->nodeData.menuNodeType = nodeType;
                return &genericNode2;
            }
            else {
                memset(&genericNode1, 0x00, sizeof(nodeDescriptor_t));
                memcpy(&genericNode1,node,sizeof(nodeDescriptor_t));
                node->nodeData.menuNodeType = nodeType;
                return &genericNode1;
            }

        }
        index--;
    } while (node != NULL);
    assert(0); /* menudefintions has no matching menutemplate defined */
    return NULL;
}

static nodeDescriptor_t* findScreenWithType(screenType_t screenType) {

    int16_t index = 0;
    nodeDescriptor_t *node;

    do {
        node = menuChainArray[index++];
        if (node->nodeData.rootScreenType == screenType)
            return node;
    } while (index < lastMenuEntryIndex);
    return NULL;
}

/* finds the next menuNode in the menuChain starting at the given menuNode. */
static nodeDescriptor_t* findNodeWithType(nodeDescriptor_t* startNode,menuNodeType_t nodeType) {

    int16_t index;
    nodeDescriptor_t *node;

    if (startNode == NULL)
        index = 0;
    else
        index = startNode->menuIndex + 1;

    do {
        node = menuChainArray[index++];
        if (node == NULL)
            return NULL;
        else if (node->nodeData.menuNodeType == nodeType)
            return node;
    } while (index <= lastMenuEntryIndex);
    return NULL;
}

static nodeDescriptor_t* findScreenForNode(screenType_t screenToFind) {
    int16_t index = 0;

    assert(screenToFind < maxScreenTypes);
    while (index < LAST_STR) {
        nodeDescriptor_t *nodeInSearch = menuChainArray[index];
        if ((nodeInSearch!=NULL) && (nodeInSearch->nodeData.rootScreenType == screenToFind))
            return nodeInSearch;
        index++;
    }
    return NULL;
}

static int8_t findChildIndexInParent(nodeDescriptor_t *actualNode) {
    return actualNode->nodeNavigation.childIndexinParent;
}

static nodeDescriptor_t* findNodeWithIndex(uint16_t menuChainIndex) {
    nodeDescriptor_t * nextNode;

    if (menuChainIndex >= lastMenuEntryIndex)
            return NULL;
     nextNode = menuChainArray[menuChainIndex];

    return nextNode;
}

static nodeDescriptor_t* findNodeWithId(STR nodeID) {
    int16_t index = 0;
    nodeDescriptor_t * nextNode;

    do {
        if (index >= lastMenuEntryIndex)
            return NULL;
        nextNode = menuChainArray[index];
        index++;
    } while (nextNode->menuId !=nodeID);

    return nextNode;
}

static nodeDescriptor_t* findNextChildWithCondition(nodeDescriptor_t *actualNode, menuNodeType_t nodeType) {
    nodeDescriptor_t* nextChild;

   nextChild = findNodeWithIndex(actualNode->nodeNavigation.firstChildIndex);
   while (nextChild != NULL) {
       if (nextChild->nodeData.menuNodeType == nodeType) {
           return nextChild;
       }
       else
           nextChild = findNodeWithIndex(nextChild->nodeNavigation.nextChildIndex);
   }

}


static nodeDescriptor_t* findReferencedNode(nodeDescriptor_t *sourceNode) {
    int16_t index = lastMenuEntryIndex-1;
    nodeDescriptor_t *node;

    do {
        node = menuChainArray[index--];
        if ((node->menuId == sourceNode->menuId) && (node->menuNumberEntry == isReferenced))
            return node;
    } while (index >=0);
    return NULL;
}

static nodeDescriptor_t* findNextChild(nodeDescriptor_t *actualChild) {
    if (actualChild->nodeNavigation.nextChildIndex >0)
        return findNodeWithIndex(actualChild->nodeNavigation.nextChildIndex);
    else
        return NULL;
}

static nodeDescriptor_t* findFirstChildInParent(nodeDescriptor_t *actualNode) {
    return  findNodeWithIndex(actualNode->nodeNavigation.firstChildIndex);
}

static nodeDescriptor_t* findFirstMenu() {
    nodeDescriptor_t* firstMenuNode;

    if (!isVisibleDependentOnSetting(RUNFIRSTOPERATION,0)) { // If  visible take the next
        firstMenuNode = findNodeWithId(BASE_SETUP);  // Jump directly into runfirst setup
        setParameterValueFromInt(SELECTUSER,publicUser);  /* Always start menu without login */
    }
    else {
        firstMenuNode = findNodeWithId(FIRSTOPERATION);
        setParameterValueFromInt(SELECTUSER,systemUser);  /* Set rights for Runfirst  */
    }
    return firstMenuNode;
}

static nodeDescriptor_t* findPreviousChild(nodeDescriptor_t *actualNode) {
    int16_t nodeIndex = actualNode->nodeNavigation.previousChildIndex;
    if (nodeIndex == 0)
        return NULL;
    else
        return findNodeWithIndex(nodeIndex);
}

static lv_res_t addTimerTaskToNode(nodeDescriptor_t *screenNode, void (*taskFunktionPtr), uint32_t period, uint8_t runCount) {

    timerTask_t *task = &screenNode->nodeData.dynamicReadCallBack;

        task->period = period;
        task->runNumberOfTimes = -1;//runCount;
        task->timerTask = taskFunktionPtr;
        return LV_RES_OK;

}
/* load configuration or archives into the menuchain */
static nodeDescriptor_t* loadArrayInMenu( uint16_t menuIndex){
    uint8_t iterator = 0;
    const hmiMenuScreen_t * parentDefine  = &menuDefinitions[menuIndex];
    const hmiMenuScreen_t * childDefine = &menuDefinitions[menuIndex+1];

    if (parentDefine->menuStringId == CONFIGURATIONX) {
        while (iterator<NUMBER_OF_NEWCONFIGURATIONS) {
            nodeDescriptor_t* newNode = loadMenuChainItem(parentDefine);
            newNode->menuId = CONFIGURATIONX + iterator;
            newNode->sourceNode = newNode->menuId;

            newNode = loadMenuChainItem(childDefine);

            newNode->parentNodeId = CONFIGURATIONX + iterator;
            newNode->sourceNode = newNode->menuId;

            iterator++;
        }
    }
    else if (parentDefine->menuStringId == ARCHIVEX) {
        while (iterator<NUMBER_OF_MEDIUMS) {
            nodeDescriptor_t* newNode = loadMenuChainItem(parentDefine);
            newNode->menuId = ARCHIVEX + iterator;
            newNode->sourceNode = newNode->menuId;

            newNode = loadMenuChainItem(childDefine);

            newNode->parentNodeId = ARCHIVEX + iterator;
            newNode->sourceNode = newNode->menuId;

            iterator++;
        }
    }
}
//* Load screen definitions.  */
static nodeDescriptor_t* loadMenuChainItem(const hmiMenuScreen_t * menuDefine) {
    nodeDescriptor_t *nodeScreenPtr;
    nodeDescriptor_t *nextNode;

    /* Last line of menuDescription reached ? */
    if ((menuDefine->parentStringId == NULL) && (menuDefine->menuStringId == NULL))
        return NULL;

    nodeScreenPtr = malloc(sizeof(nodeDescriptor_t));
    memset(nodeScreenPtr, 0x00, sizeof(nodeDescriptor_t));

    nodeScreenPtr->menuNumberEntry = menuDefine->menuNumberEntry;
    nodeScreenPtr->nodeNavigation.parentIndex = -1;
    nodeScreenPtr->nodeNavigation.firstChildIndex = -1;
    nodeScreenPtr->nodeData.numOfObj = 0;
    nodeScreenPtr->parentNodeId = menuDefine->parentStringId;
    nodeScreenPtr->menuId = menuDefine->menuStringId;
    nodeScreenPtr->sourceNode = nodeScreenPtr->menuId ;

    if (menuDefine->nextMenuNodeInFlow > 0){
        /* Load first the pointer to the STR table and later the index to the nextFlow node here */
        nodeScreenPtr->nodeNavigation.nextNodeInFlow = menuDefine->nextMenuNodeInFlow;
    }
    // Initializer must assign a screeType, will be asserted at the end of this function
    nodeScreenPtr->nodeData.rootScreenType = unitializedScreenType;
    nodeScreenPtr->nodeData.menuNodeType = menuDefine->menuNodeType;
    switch (menuDefine->menuNodeType) {
    case defaultScreenMenuNode:
        nodeScreenPtr->nodeData.rootScreenType = defaultScreen;
        nodeScreenPtr->nodeData.eventHandler = eventHandlerDefaultScreenKeyPressed;
        nodeScreenPtr->nodeData.initScreen = initDefaultScreen;
        nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;
        addTimerTaskToNode(nodeScreenPtr, requestDynamicData, SCREEN_FUNCTION_CALLBACK_PERIOD, 1);
        break;

    case runParameterEndNodeAction:
        nodeScreenPtr->nodeData.rootScreenType = noScreenAssigned;
        nodeScreenPtr->nodeData.eventHandler = eventHandlerParameterEndNode;
        nodeScreenPtr->nodeData.numOfObj = 0;
        break;

    case listNode:

    case listNodeAllChildsAutoOpen:
    case listChildAutoOpens:
    case listChildAutoOpensArray:

        nodeScreenPtr->nodeData.rootScreenType = listScreen;
        if ((nodeScreenPtr->menuId == SYSTEMUSER) || (nodeScreenPtr->menuId == AMTBUSER))
                nodeScreenPtr->nodeData.eventHandler = eventHandlerListKeyStoreUser;
        else
            nodeScreenPtr->nodeData.eventHandler = eventHandlerListKey;
        nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;
        break;
    case compressedListNode:
        nodeScreenPtr->nodeData.rootScreenType = listScreen;
        nodeScreenPtr->nodeData.eventHandler = eventHandlerCompressedList;
        nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;
        break;
    case multiChooseValuesNode:
    case singleChooseValuesNode:
         nodeScreenPtr->nodeData.rootScreenType = listScreen;
         nodeScreenPtr->nodeData.eventHandler = eventHandlerChooseScreenKey;
         nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;
         break;

   case parameterNodeTemplate:
        nodeScreenPtr->nodeData.rootScreenType = noScreenAssigned;
        nodeScreenPtr->nodeData.initScreen = initParameterShowScreen;
        nodeScreenPtr->nodeData.eventHandler = eventHandlerParameterShowNode;
        nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;
        break;
   case parameterShowNode:

       nodeScreenPtr->nodeData.rootScreenType = parameterShowScreen;
        nodeScreenPtr->nodeData.eventHandler = eventHandlerParameterShowNode;
        nodeScreenPtr->nodeData.initScreen = initParameterShowScreen;
        nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;
        addTimerTaskToNode(nodeScreenPtr, eventShowParameterScreen,SCREEN_FUNCTION_CALLBACK_PERIOD, -1);
        break;
   case parameterShowNodeMatching:
   case parameterShowNodeNotMatching:
   case messageScreenNode:
       nodeScreenPtr->nodeData.rootScreenType = messageScreen;
        nodeScreenPtr->nodeData.eventHandler = eventHandlerMessageScreen;
        nodeScreenPtr->nodeData.initScreen = initMessageScreen;
        nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;

        addTimerTaskToNode(nodeScreenPtr, eventShowParameterScreen,SCREEN_FUNCTION_CALLBACK_PERIOD, -1);
        break;
   case parameterTakeOverNode:
        nodeScreenPtr->nodeData.rootScreenType = parameterTakeValueScreen;
        nodeScreenPtr->nodeData.eventHandler = eventHandlerParameterTakeOver;
        nodeScreenPtr->nodeData.initScreen = initParameterTakeOverScreen;
        nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;
        addTimerTaskToNode(nodeScreenPtr, requestParameterFromStorageAndFillDynamicFields,
                SCREEN_FUNCTION_CALLBACK_PERIOD, -1);
        break;

    case passwordEntryNode:
    case parameterEditNode:
        nodeScreenPtr->nodeData.rootScreenType = parameterEditScreen;
        nodeScreenPtr->nodeData.eventHandler = eventHandlerParameterEditNode ;
        nodeScreenPtr->nodeData.initScreen = initParameterEditScreen;
        nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;
        addTimerTaskToNode(nodeScreenPtr, requestParameterFromStorageAndFillDynamicFields,
                SCREEN_FUNCTION_CALLBACK_PERIOD, -1);
        break;
    case parameterEditNodeWithApply:
        nodeScreenPtr->nodeData.rootScreenType = parameterEditScreen;
        nodeScreenPtr->nodeData.eventHandler = eventHandlerParameterEditNode ;
        nodeScreenPtr->nodeData.initScreen = initParameterEditScreen;
        nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;
        addTimerTaskToNode(nodeScreenPtr, requestParameterFromStorageAndFillDynamicFields,
                SCREEN_FUNCTION_CALLBACK_PERIOD, -1);
        break;
    case applicationShowNode:
         nodeScreenPtr->nodeData.rootScreenType = showApplicationScreen;
         nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;
         nodeScreenPtr->nodeData.initScreen = initApplicationScreen;
         addTimerTaskToNode(nodeScreenPtr, eventHandlerApplicationFirstScreenTimeOut,1, -1);
         break;

    case logoScreenNode:
        nodeScreenPtr->nodeData.rootScreenType = logoScreen;
        nodeScreenPtr->nodeData.numOfObj = screenParameterMaxIndex;
        nodeScreenPtr->nodeData.initScreen = initLogoScreen;
        addTimerTaskToNode(nodeScreenPtr, eventHandlerLogoScreenTimeOut,
                 LOGOSCREEN_DELAY, 1);
        break;

    default:
        assert(nodeScreenPtr->nodeData.numOfObj != 0);
        break;

    }

    menuChainArray[lastMenuEntryIndex] = nodeScreenPtr;

    nodeScreenPtr->menuIndex = lastMenuEntryIndex++;

    assert(nodeScreenPtr->nodeData.rootScreenType != unitializedScreenType);
    return nodeScreenPtr;

}

static void loadDirectChildren(nodeDescriptor_t* parentNode) {

    uint16_t nodeIndex = 0;
    uint16_t parentIndex = 0;
    nodeDescriptor_t * node = NULL;
    nodeDescriptor_t * nextNode = NULL;
    nodeDescriptor_t * previousNode = NULL;
    uint8_t childIndex = 0;

    while (nodeIndex < lastMenuEntryIndex){
        node= menuChainArray[nodeIndex];


        if (node->parentNodeId == parentNode->menuId && parentNode->menuIndex <  node->menuIndex) {
            node->nodeNavigation.parentIndex = parentNode->menuIndex;

            if (previousNode != NULL) {
                node->nodeNavigation.previousChildIndex = previousNode->menuIndex;
                previousNode->nodeNavigation.nextChildIndex = node->menuIndex;
                node->nodeNavigation.nextChildIndexLoadedBy = loadDirectChildren;
            }
            else {
                /* The first child */
                childIndex = 0;
                parentNode->nodeNavigation.firstChildIndex = node->menuIndex;
            }
            node->nodeNavigation.childIndexinParent = childIndex;
            node->nodeData.enumValue = childIndex++;
            previousNode = node;
            nextNode = menuChainArray[nodeIndex+1];
            if ((isChooseListNode(node)) && (!isChooseListNode(nextNode)))
               break;  /* leaving loadlist for a chooselist */

        }
        nodeIndex++;
    }
}


static void loadNavigation() {

    uint8_t uninitializedNode;
    uint16_t nodeIndex = 0;
    uint16_t parentIndex = 0;
    nodeDescriptor_t * node = NULL;
    nodeDescriptor_t * previousNode = NULL;
    nodeDescriptor_t * parentNode;
    nodeDescriptor_t * nextChild;
// Level 1

    parentNode = findNodeWithId(FIRSTOPERATION); /* This is the entry point */
    loadDirectChildren(parentNode);

// Level 2
    nodeIndex = 0;
    while (nodeIndex < lastMenuEntryIndex) {
        node=(nodeDescriptor_t*)menuChainArray[nodeIndex];
        if (node->nodeNavigation.parentIndex > 0) {/* Node is a child */
            loadDirectChildren(node);
        }
        nodeIndex++;
    }

    do {
        uninitializedNode = false;
        nodeIndex = 0;
        while (nodeIndex < lastMenuEntryIndex) {
            node=(nodeDescriptor_t*)menuChainArray[nodeIndex];
            if ((node->nodeNavigation.parentIndex < 0) && (node->nodeNavigation.firstChildIndex < 0)) {/* Node is not loaded yet  */
                loadDirectChildren(node);
                switch (node->nodeData.menuNodeType) {
                case messageScreen:
                      uninitializedNode = true;
                    break;
                default:
                    /* All other cases are not template screens */
                  break;
                }
            }
            nodeIndex++;
        }
    } while (uninitializedNode == true);

    /* Make sure that a nextChild belongs to the same parent. Can be wrong if menus have the same name in different parents */
    nodeIndex = 0;
    while (nodeIndex < lastMenuEntryIndex) {
        node=(nodeDescriptor_t*)menuChainArray[nodeIndex];
        if (node->nodeNavigation.nextChildIndex != 0) {
            nextChild = findNodeWithIndex(node->nodeNavigation.nextChildIndex);
            if (!isSameParentRoot(node,nextChild))
                node->nodeNavigation.nextChildIndex = -1;
        }
        else {
            /* ok */
        }
        nodeIndex++;
    }
}

static void loadProcessFlowPointers(void) {
    nodeDescriptor_t *node;
    nodeDescriptor_t *nextNode;
    int16_t childIndex = 0;
    int menuTableIndex = 0;
    STR numberOfChildren;

    int16_t actualIndex = 0;

    while (actualIndex < lastMenuEntryIndex){
        node=(nodeDescriptor_t*)menuChainArray[actualIndex];
        if (node->nodeNavigation.nextNodeInFlow > 0){
            nextNode = findNodeWithId(node->nodeNavigation.nextNodeInFlow);
            node->nodeNavigation.nextNodeInFlow = nextNode->menuIndex;
        }
        actualIndex++;
    }
}


static void loadMenuChain(void) {
    nodeDescriptor_t *nodeScreenPtr;
    nodeDescriptor_t *parentScreenPtr;
    int16_t childIndex = 0;
    int menuTableIndex = 0;
    STR numberOfChildren;

    int16_t actualIndex = lastMenuEntryIndex;

    //while (actualIndex>0){
    //    nodeScreenPtr=(nodeDescriptor_t*)menuChainArray[actualIndex-1];
    //}
    lastMenuEntryIndex=0;

    nodeScreenPtr = loadMenuChainItem(&menuDefinitions[menuTableIndex]);

    do {
        // Screen init for first entry

        if (nodeScreenPtr == NULL)
            continue;
        else {
            /* end of list reached */
        }
        parentScreenPtr = nodeScreenPtr ;
        /* Special redefinitions, TODO move into a separate table */
//        if (nodeScreenPtr->menuId == MTI10) /* TODO DR do we need that still ?)
//            nodeScreenPtr->menuId = MTI_FULL;
        if (menuDefinitions[menuTableIndex].lastParameterFromARange > 0) {
            numberOfChildren =
                    menuDefinitions[menuTableIndex].lastParameterFromARange
                            - menuDefinitions[menuTableIndex].menuStringId + 1;

           //* Repeated read of subnodes for the given range, for example units or sensortypes and more */
            while (nodeScreenPtr != NULL) {
                nodeScreenPtr->menuId = nodeScreenPtr->menuId+childIndex;
                nodeScreenPtr->nodeNavigation.childIndexinParent = childIndex;

                childIndex++;
                if (childIndex > (int16_t) numberOfChildren - 1)
                    break;
                else
                    nodeScreenPtr = loadMenuChainItem(&menuDefinitions[menuTableIndex]);
            }
        }

        childIndex = 0;
        menuTableIndex++;
        if (menuDefinitions[menuTableIndex].menuNodeType == listChildAutoOpensArray) {
            loadArrayInMenu(menuTableIndex);
            menuTableIndex++;
        }
        else
            nodeScreenPtr = loadMenuChainItem(&menuDefinitions[menuTableIndex]);
    } while (nodeScreenPtr != NULL);

}


/* TODO Move these to EP storage */
static temporaryInsimulatorOnlyArchiveSetting_t temporaryInsimulatorOnlyArchiveSetting[NUMBER_OF_MEDIUMS];
static temporaryInsimulatorOnlyConfigurationSetting_t temporaryInsimulatorOnlyConfigurationSetting[NUMBER_OF_NEWCONFIGURATIONS];
static temporaryInsimulatorOnlyDeviceCfg_t temporaryInsimulatorOnlyDeviceCfg;

/* local volatile settings  */
static temporaryInsimulatorRAMOnlyCfg_t temporaryInsimulatorRAMOnlyCfg;




static uint8_t AquaHmi_get_activeDataCfg(void) {
    //    return localDevBaseStrPtr->plDinamicDataPtr->activatedConfig[0];
}

static int8_t AquaHmi_set_activeDataCfg(uint8_t cfg) {
    //    if(cfg<3){
    //     localDevBaseStrPtr->plDinamicDataPtr->activatedConfig[0]=cfg;
    //     return localDevBaseStrPtr->plDinamicDataPtr->activatedConfig[0];
    //    }
    return -1;
}

static void AquaHMI_FSM_init(void) {



    // TODO testing initial function without real data


}


void setUsedMemoryAddress(void * uint32Address){
    memoryUsedDisplay = (lv_obj_t*) uint32Address;
}


static char * getMeasurmentValueString(HmiMainDispUnits_t displayUnit, uint8_t currentDisplayLine) {

    float tmp_float = 0;
    uint32_t temp_uint32 = 0;


    sprintf(temporaryBuffer, "");
    switch (displayUnit) {

        /* Process data fields unit depended */
        case unitsmAmps:


                   tmp_float = modCfg.modValue / 1000;
 
               sprintf(temporaryBuffer, "%3.2f", tmp_float);

           break;
        case unitsPercentSond:


               if (((measCfg.probeMaxRawValue
                       - measCfg.probeMinRawValue) > 0)) {
                   tmp_float = (100.00
                           / (measCfg.probeMaxRawValue
                                   - measCfg.probeMinRawValue)
                           * (measData.ampDiffLin
                                   - measCfg.probeMinRawValue));
                   if (tmp_float < 0.0) {
                       tmp_float = 0.0;
                   };
                   if (tmp_float > 100.0) {
                       tmp_float = 100.0;
                   };
                   sprintf(temporaryBuffer, "%3.2f", tmp_float);
               
           }
           break;
        case unitsImp:

   
                   temp_uint32 = modCfg.modValue;

               sprintf(temporaryBuffer, "%u", (unsigned int) temp_uint32);
           
           break;
        case unitsPrecentRange:
  
               if ((measCfg.rangeMaxRawValue
                       - measCfg.rangeMinRawValue) > 0) {

                   tmp_float = (100.00
                           / (measCfg.rangeMaxRawValue
                                   - measCfg.rangeMinRawValue)
                           * (measData.ampDiffLin
                                   - measCfg.rangeMinRawValue));
                   if (tmp_float < 0.0) {
                       tmp_float = 0.0;
                   };
                   if (tmp_float > 100.0) {
                       tmp_float = 100.0;
                   };
                   sprintf(temporaryBuffer, "%3.2f", tmp_float);
               }
           
           break;
        case unitsRaw:

               if (measData.ampDiffLin) {
                   temp_uint32 = measData.ampDiffLin;
               } else {
                   temp_uint32 = measData.ampDiff;
               }
               sprintf(temporaryBuffer, "%u", (unsigned int) temp_uint32);
           
           break;
        case unitsRawFactor:

               if (sim_hmiConfig.mainDispCfg.DataFieldsFactors[sim_hmiConfig.mainDispCfg.MeasuringUnits[currentDisplayLine]
                       - unitsRawFactor] == 0) {
                   sim_hmiConfig.mainDispCfg.DataFieldsFactors[sim_hmiConfig.mainDispCfg.MeasuringUnits[currentDisplayLine]
                           - unitsRawFactor] = 1;
               }
               if (measData.ampDiffLin) {
                   temp_uint32 = measData.ampDiffLin;
               } else {
                   temp_uint32 = measData.ampDiff;
               }
               //                 sprintf(buff_data, "%u",(unsigned int)((temp_uint32*hmiCfg.mainDispCfg.DataFieldsFactors[hmiCfg.mainDispCfg.DataFields[currentDisplayLine]-unitsRawFactor]))/(float));
               sprintf(temporaryBuffer, "%u",
                       (unsigned int) (temp_uint32
                               / sim_hmiConfig.mainDispCfg.DataFieldsFactors[sim_hmiConfig.mainDispCfg.MeasuringUnits[currentDisplayLine]
                                       - unitsRawFactor]));
           
           break;
        case unitsRawSondFactor:
       
               if (sim_hmiConfig.mainDispCfg.DataFieldsFactors[sim_hmiConfig.mainDispCfg.MeasuringUnits[currentDisplayLine]
                       - unitsRawFactor] == 0) {
                   sim_hmiConfig.mainDispCfg.DataFieldsFactors[sim_hmiConfig.mainDispCfg.MeasuringUnits[currentDisplayLine]
                           - unitsRawFactor] = 1;
               }
               if (measData.ampDiffLin) {
                   tmp_float = measData.ampDiffLin;
               } else {
                   tmp_float = measData.ampDiff;
               }

               tmp_float =
                       ((int32_t) tmp_float > measCfg.probeMaxRawValue) ?
                               measCfg.probeMaxRawValue : tmp_float;
               tmp_float =
                       ((int32_t) tmp_float < measCfg.probeMinRawValue) ?
                               measCfg.probeMinRawValue : tmp_float;

               tmp_float = (tmp_float - measCfg.probeMinRawValue);
               tmp_float =
                       ( (sim_hmiConfig.mainDispCfg.DataFieldsFactors[sim_hmiConfig.mainDispCfg.MeasuringUnits[currentDisplayLine]
                               - unitsRawFactor])
                               / (float) (measCfg.probeMaxRawValue)
                                       - measCfg.probeMinRawValue)
                               * tmp_float;

               temp_uint32 =
                       (uint32_t) (tmp_float < 0) ?
                               (tmp_float * -1) : tmp_float;
               sprintf(temporaryBuffer, "%u", (unsigned int) temp_uint32);
         
           break;
        case unitsRawSondRangeFactor:

               if  (sim_hmiConfig.mainDispCfg.DataFieldsFactors[sim_hmiConfig.mainDispCfg.MeasuringUnits[currentDisplayLine]
                       - unitsRawFactor] == 0) {
                   sim_hmiConfig.mainDispCfg.DataFieldsFactors[sim_hmiConfig.mainDispCfg.MeasuringUnits[currentDisplayLine]
                           - unitsRawFactor] = 1;
               }
               if (measData.ampDiffLin) {
                   tmp_float = measData.ampDiffLin;
               } else {
                   tmp_float = measData.ampDiff;
               }
               //                 tmp_float=( (sim_hmiConfig.mainDispCfg.DataFieldsFactors[hmiCfg.mainDispCfg.DataFields[i]-unitsRawFactor]*(tmp_float-measCfg.rangeMinRawValue))/(float)(measCfg.rangeMaxRawValue-measCfg.rangeMinRawValue));

               tmp_float =
                       ((int32_t) tmp_float > measCfg.rangeMaxRawValue) ?
                               measCfg.rangeMaxRawValue : tmp_float;
               tmp_float =
                       ((int32_t) tmp_float < measCfg.rangeMinRawValue) ?
                               measCfg.rangeMinRawValue : tmp_float;

               tmp_float = (tmp_float - measCfg.rangeMinRawValue);
               tmp_float =
                       ( (sim_hmiConfig.mainDispCfg.DataFieldsFactors[sim_hmiConfig.mainDispCfg.MeasuringUnits[currentDisplayLine]
                               - unitsRawFactor])
                               / (float) (measCfg.rangeMaxRawValue
                                       - measCfg.rangeMinRawValue))
                               * tmp_float;
               temp_uint32 =
                       (uint32_t) (tmp_float < 0) ?
                               (tmp_float * -1) : tmp_float;

               sprintf(temporaryBuffer, "%u", (unsigned int) temp_uint32);
        
           break;
        case unitsPhase:

               temp_uint32 = measData.phaseDiff;
               sprintf(temporaryBuffer, "%u", (unsigned int) temp_uint32);
    
           break;
        case unitsCapacity:
        
               tmp_float = measData.cap;
               sprintf(temporaryBuffer, "%3.2f", tmp_float);

           break;
        default:
           sprintf(temporaryBuffer, "");
           break;
    }

    return &temporaryBuffer;
}

static void insertValuesInAnalogChart() {
    char buffer[SMALLSTRINGSIZE];

    if (analogChartDefaultScreen.content == NULL)
        return;

    else if (lv_obj_has_flag(analogChartDefaultScreen.content, LV_OBJ_FLAG_HIDDEN))
        lv_obj_clear_flag(analogChartDefaultScreen.content,LV_OBJ_FLAG_HIDDEN);
    if (analogChartDefaultScreen.probeHighValPercentage == NULL)
        return;

    sprintf(buffer,"%s",getMeasurmentValueString(unitsPercentSond,0));
    if (strlen(buffer) > 0) {
        int8_t measuredValuePercent = atoi(buffer);

        int32_t probeTopVal = getParameterValueAsInt(TOPFULLMA);
        float probeHighValPercentage= getParameterValueAsFloat(ANALOGSIGNALSPREAD20MA);
        int32_t probeZeroVal= getParameterValueAsInt(ZEROVALUEMA);
        float probeLowValPercentage = getParameterValueAsFloat(ANALOGSIGNALSPREAD04MA);

        sprintf(buffer,"%.02f%c",probeHighValPercentage,'%');
        lv_label_set_text(analogChartDefaultScreen.probeHighValPercentage, buffer);

        sprintf(buffer,"%.02f%c",probeLowValPercentage,'%');
        lv_label_set_text(analogChartDefaultScreen.probeLowValPercentage, buffer);

         lv_area_t  coords;
         lv_obj_get_coords(analogChartDefaultScreen.centerBody, &coords);
         uint8_t yPos = coords.y1 - coords.y2;
         uint32_t factor = 10*(coords.x2 - coords.x1); // 100% pixel width
        // measuredValuePercent=100;
         int32_t scopedPercentage = measuredValuePercent;
         if (scopedPercentage <probeLowValPercentage)
             scopedPercentage =0;
         else if (scopedPercentage > probeHighValPercentage)
             scopedPercentage =probeHighValPercentage;

          if (probeHighValPercentage-probeLowValPercentage != 0)
              scopedPercentage =  100*(scopedPercentage-probeLowValPercentage)/(probeHighValPercentage-probeLowValPercentage);
          else{
              /* Avoid division by zero */
          }

         uint32_t position =  (scopedPercentage  * factor) /1000;
         if (measuredValuePercent > probeHighValPercentage)
             measuredValuePercent = probeHighValPercentage;
         lv_label_t * label = analogChartDefaultScreen.measuredValPercentage;
         lv_obj_align_to(label, analogChartDefaultScreen.centerBody, LV_ALIGN_TOP_LEFT, position -4 ,-7);

         label = analogChartDefaultScreen.lowArrow;
         if (scopedPercentage  <= 0)
             lv_label_set_text(label, EDITLEFTARROW);
         else
             lv_label_set_text(label, " ");

         label = analogChartDefaultScreen.highArrow;
         if (scopedPercentage  >= 100)
             lv_label_set_text(label, EDITRIGHTARROW);
         else
             lv_label_set_text(label, " ");
    }
 }

static void requestDynamicData(void *p) {

    (void) p;
    uint8_t lineIsVisible;
    char buffer[SMALLSTRINGSIZE];
    int8_t numberOfDisplayedLines;

    nodeDescriptor_t *screenNode = currentScreen;
    if (screenNode->nodeData.rootScreenType != defaultScreen)
        return;

    numberOfDisplayedLines = getNumberOfDisplayedLines();



    if (numberOfDisplayedLines <= 1)
       insertValuesInAnalogChart();
    else {
        /* Nothing to do */
    }

    /* process data fields */
    for (uint8_t currentDisplayLine = 0; currentDisplayLine < MAX_NUMBER_OF_DISPLAYED_MEASVALUES; currentDisplayLine++) {
        if (sim_hmiConfig.mainDispCfg.MeasuringUnits[currentDisplayLine] == unitsNone) {
            continue;
        }
        if (screenNode->nodeData.nodeObj == NULL)
            return;
        if (screenNode->nodeData.nodeObj[screenDefaultMeasValue0 + currentDisplayLine].obj!= NULL) {
            lineIsVisible = currentDisplayLine <= numberOfDisplayedLines;

            if (lineIsVisible)
            {
                strcpy(buffer,getMeasurmentValueString (sim_hmiConfig.mainDispCfg.MeasuringUnits[currentDisplayLine],currentDisplayLine));

//                /* TEMPORARY, to analyse memory use */
//                if (currentDisplayLine == 0) {
//                    debugShowMem();
//                    sprintf(buffer,"%lu",used_size);
//                }

                if (strlen(buffer) > 0 )
                    lv_label_set_text(screenNode->nodeData.nodeObj[screenDefaultMeasValue0 + currentDisplayLine].obj, buffer);

                else {
                    /* no information to display  */
                }
                if (strlen(buffer) > 0 )
                    lv_label_set_text(screenNode->nodeData.nodeObj[screenDefaultMeasValue0 + currentDisplayLine].obj, buffer);

                else {
                    /* no information to display  */
                }
            }

            else {
                /* no information to display  */
            }
        }
        else {
            /* no information to display  */
        }
    }
    return;
    debugShowMem();
    sprintf(buffer,"%d", used_size);
    lv_label_set_text(memoryUsedDisplay, buffer);
}

static int8_t setParameterChooseListInStorage(STR parameterID, int8_t childIndex) {
    uint8_t displayLine;
    uint8_t mappedToEPValue;
    STR mappedToSTR;
    int8_t result = -1;


    switch (parameterID) {

        case APPBATCH:
        //TODO storage data
        break;
         case LANGUAGE:
             sim_hmiConfig.lang =  childIndex;

        break;
        case FAILSAFESTATE:
            if (temporaryInsimulatorOnlyDeviceCfg.failSafeEnum != (mtiMod_t) childIndex) {
                temporaryInsimulatorOnlyDeviceCfg.failSafeEnum = childIndex;
            }
            break;
        case CHOOSEAPP:
            if (temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].application != (mtiMod_t) childIndex) {
                temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].application = childIndex;
            }
            break;
        case MODE:

            sim_measConfig.mtiMode = (mtiMod_t) childIndex;

        break;
        case TYPE:

            probeCfg.probeType = (probeType_t) childIndex;


        break;

        case DISPLAYLINE_1:
        case DISPLAYLINE_2:
        case DISPLAYLINE_3:
            displayLine = parameterID-DISPLAYLINE_1;
            mappedToSTR = childIndex + UNITSDEFINITIONSTART + 1;
            mappedToEPValue = findMappedEnumValueFromSTR(mappedToSTR);
            sim_hmiConfig.mainDispCfg.MeasuringUnits[displayLine]=mappedToEPValue;

            
        break;
        default:
        break;
    }
    return result;
}


/* Get the index of of choose value parameter */
static int32_t getParameterChooseListFromStorage(STR parameterID) {

    int32_t id = -1;
    int32_t tmp_int32;
    uint8_t displayLine;
    uint8_t storedEnum;
    STR mappedToSTR;

    /* Get stored index od a chooselist parameter */
    switch (parameterID) {

        case MEASVALUNITS:
            id = temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].enabledUnits;
            break;
        case ERROR_HANDLING:
            id = temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].enabledErrors;
            break;

        case FAILSAFESTATE:
            id= temporaryInsimulatorOnlyDeviceCfg.failSafeEnum ;
            break;
        case CHOOSEAPP:
            id= temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].application ;
            break;
        case MODE:
            tmp_int32 = (int32_t)sim_measConfig.mtiMode;
            if (tmp_int32 != Undef_MtiMod && tmp_int32 <= MTI_200) {
                id = tmp_int32 - 1;
            }
            break;

        case TYPE:
            tmp_int32 = (int32_t)temporaryInsimulatorOnlyDeviceCfg.probeType;
            if (tmp_int32 > probeType_undef) {
                id = tmp_int32 - 1;
            }
            break;
        case DISPLAYLINE_1:
        case DISPLAYLINE_2:
        case DISPLAYLINE_3:
            displayLine = parameterID-DISPLAYLINE_1;
            storedEnum = sim_hmiConfig.mainDispCfg.MeasuringUnits[displayLine];
            mappedToSTR = findSTRFromEnumValue(storedEnum);
            id = mappedToSTR - UNITSDEFINITIONSTART;
        break;
        default:
            /* nothing to do */
            break;
    }

    return id;
}
static char userName[SMALLSTRINGSIZE];
static char * getLoginUserName(STR parameterID) {

    uint8_t loggedInUser = getParameterValueAsInt(parameterID);
    switch (loggedInUser)
    {
        case publicUser:
            sprintf(userName,"%s",getMenuOrParameterNameFromMenuDefinitions(PUBLICUSER));
            break;
        case amtbUser:
            sprintf(userName,"%s",getMenuOrParameterNameFromMenuDefinitions(AMTBUSER));
            break;
        case systemUser:
            sprintf(userName,"%s",getMenuOrParameterNameFromMenuDefinitions(SYSTEMUSER));
            break;
        default:
            assert(0); /* All cases need to be defined */
    }
    return &userName;
}

static char * getParameterMaxValue(STR parameterID) {
    char* parameterFormatString = getParameterFormatString(parameterID);
    parametercharacteristics_t *parameterCharacteristics = getParameterCharacteristics(parameterID);
    sprintf(buff_data,parameterFormatString,parameterCharacteristics->hiLimit);
    return buff_data;
}
static char * getParameterMinValue(STR parameterID) {
    char* parameterFormatString = getParameterFormatString(parameterID);
    parametercharacteristics_t *parameterCharacteristics = getParameterCharacteristics(parameterID);

   sprintf(buff_data,parameterFormatString,parameterCharacteristics->loLimit);
   return buff_data;
}

float_t getParameterValueAsFloat(STR parameterID) {
    char valueString[SMALLSTRINGSIZE];
    strcpy(valueString,getParameterValueAsString(parameterID));
    float_t result = atof(valueString);
    return result;
   /* TODO atoi handling */
}

int32_t getParameterValueAsInt(STR parameterID) {
    char valueString[SMALLSTRINGSIZE];
    strcpy(valueString,getParameterValueAsString(parameterID));
    int32_t result = atoi(valueString);
    return result;
   /* TODO atoi handling */
}

char const* getParameterValueAsString(STR parameterID) {
    int8_t choosenListIndex;
    lv_mem_monitor_t memoryMonitor;
    modConfigDataStruct_t * modConfig;
    char parameterFormatString[SMALLSTRINGSIZE];

    strcpy(parameterFormatString,getParameterFormatString(parameterID));

    parametercharacteristics_t *parameterCharacteristics = getParameterCharacteristics(
            parameterID);

    switch (parameterID) {
		case RUNFIRSTOPERATION:
			sprintf(buff_data, parameterFormatString,temporaryInsimulatorOnlyDeviceCfg.saveFirstOperationMenu);
			break;
		case MEASVALUNITS:
			sprintf(buff_data, parameterFormatString,temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].enabledUnits);
			break;
		case ERROR_HANDLING:
			sprintf(buff_data, parameterFormatString,temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].enabledErrors);
			break;
		case DISPLAY:
			sprintf(buff_data, parameterFormatString,temporaryInsimulatorRAMOnlyCfg.currentSelectedDisplayLines);
			break;
		case DEVICENAME:
		case SOFTWAREVERSION:
		case HARDWAREVERSION:
		case DEFAULT_SCREEN:
			sprintf(buff_data, parameterFormatString,temporaryInsimulatorOnlyDeviceCfg.deviceName);//AquaHmi_get_sysDescription()->sysIdentification);
			break;
		case ANALOGSIGNALSPREAD20MA:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].maxInputValuex100 *0.01);
			break;
		case ANALOGSIGNALSPREAD04MA:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].minInputValuex100 *0.01);
			break;
		case ZEROVALUEMA:
			sprintf(buff_data, parameterFormatString, sim_measConfig.probeMinRawValue);
			break;
		case TOPFULLMA:
			sprintf(buff_data, parameterFormatString, sim_measConfig.probeMaxRawValue);
			break;
		case EDITEDCONFIG:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.editedConfiguration);
			break;
		case ACTIVECONFIG:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.activeConfiguration);
			break;
		case EDITEDARCHIVE:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.editedArchive);
			break;

		case ADDTO20MAVALUE:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.addTo20mAValue);
			break;
		case MASIMULATIONVALUE:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorRAMOnlyCfg.maSimulationValue );
			break;
		case CODEUSEDSIZE:
			sprintf(buff_data,"To be done, show Codesize");
			 break;
		case LANGUAGE:
			sprintf(buff_data, parameterFormatString, sim_hmiConfig.lang );
			break;
		case EXPECTSYSPASSWORD:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.systemPassword );
			break;

		case EXPECTAMTBPASSWORD:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.amtbPassword );
			break;
		case TRYTOLOGINUSER:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorRAMOnlyCfg.tryToLoginUser );
			break;
		case NEWPASSWORDENTRY:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorRAMOnlyCfg.passwordToMatch );

			 break;
		case SERIALNUMBER:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.serialNumber );
			break;
		case PROBESERIALNUMBER:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.probeSerialNumber );
			break;
		case PROBETYPE:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.probeType );
			break;
		case SENSORSERIALNUMBER:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.sensorSerialNumber );
			break;

		case SELECTUSER:
			sprintf(buff_data, parameterFormatString, (uint16_t)temporaryInsimulatorRAMOnlyCfg.loginUser );
			break;
	// TODO use them in HW
	//        case SOFTWAREVERSION:
	//        sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.softwareVersion );
	//        break;
	//    case HARDWAREVERSION:
	//        sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.hardwareVersion );
	//        break;
		case PROOFDATE:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.proofDate );
			 break;
		case FIRSTDATE:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.firstDate );
			 break;
		case QRMANUAL:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.qrManual );
			break;
		case QRDOCS:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.qrDocs );
			break;
		case CONTACT:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.contact );
			break;

		case NEWPASSWORDVERIFY:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorRAMOnlyCfg.actualPasswordEntry);
			break;
		case PASSWORDENTRYVALUE:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorRAMOnlyCfg.actualPasswordEntry);
			break;
		case CURRENTTAG:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyDeviceCfg.tag);
			break;
		case APPLICATION:
			choosenListIndex = getParameterChooseListFromStorage(CHOOSEAPP);
			sprintf(buff_data, parameterFormatString, getMenuOrParameterNameFromMenuDefinitions(APPBATCH+choosenListIndex));
			 strcat(buff_data,"\nVersion ");
			 strcat(buff_data,PACKAGE_VERSION);

			break;
		case STOREDVALUELABEL:
			sprintf(buff_data, getMenuOrParameterNameFromMenuDefinitions(STOREDVALUELABEL));
			break;
		case NAMEFORNEWCONFIG:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].configName );
			break;
		case NAMEFORNEWMEDIUM:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyArchiveSetting[mediumInFocus].mediumName );
			break;
		case SIGNALFILTER:
			sprintf(buff_data, parameterFormatString, temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].SIGNALFILTER);
		break;
		default:
			sprintf(buff_data, parameterFormatString, "INVALID");
			break;
    }
    return &buff_data;
}

static char * getParameterFormatString(STR parameterID) {
    int8_t choosenListIndex;
    uint8_t digits;
    uint8_t commaDigits;
    parametercharacteristics_t *parameterCharacteristics = getParameterCharacteristics(
            parameterID);
    strcpy(temporaryBuffer,"%s\0");

    if (parameterCharacteristics) {
        commaDigits = parameterCharacteristics->editCommas;
        digits = parameterCharacteristics->editDigits;
        digits = digits ? digits:1; /* digits can be defined as zero if ignored, but if used in format they have to be defined and minimum size 1 */
    }
    else
        return &temporaryBuffer;

    switch (parameterCharacteristics->parameterType) {
        case parameterTypeString:
        case parameterTypeTagNumber:
                strcpy(temporaryBuffer,"%s");
            break;
        case parameterTypeInteger:

               sprintf(temporaryBuffer,"%c0%ii",'%',digits);
            break;

        case parameterTypeFloat:
            sprintf(temporaryBuffer,"%c0%i.0%if",'%',digits,commaDigits);
            break;

        case parameterTypeDate:
                strcpy(temporaryBuffer,"%s");
            break;

        case parameterTypeChooseList:
            break;
         default:
            strcpy(temporaryBuffer,"%s");
            break;
    }

    return &temporaryBuffer;
}

static uint8_t setParameterDefaultValueInStorage(STR parameterID) {
    char* defaultValue = getParameterCharacteristics(parameterID)->defaultValue;
    assert(defaultValue!=NULL);
    return setParameterValue(parameterID,defaultValue);
}

static uint8_t setParameterValueFromInt(STR parameterID, int32_t parameterValue) {
    uint8_t result = true;
    char parameterAsString[SMALLSTRINGSIZE];
    sprintf(parameterAsString,"%i",parameterValue);
    return setParameterValue(parameterID,parameterAsString);
}

static void enableNextConfigurationInArray(uint8_t arrayIndex) {
    uint8_t nextIndex;

    nextIndex = arrayIndex + 1;
    if (nextIndex  < NUMBER_OF_NEWCONFIGURATIONS)
        temporaryInsimulatorOnlyConfigurationSetting[nextIndex].status = arrayVisibleDefaultName;
}


static void enableNextMediumInArray(uint8_t arrayIndex) {
    uint8_t nextIndex;

    nextIndex = arrayIndex + 1;
    if (nextIndex  < NUMBER_OF_MEDIUMS)
        temporaryInsimulatorOnlyArchiveSetting[nextIndex].status = arrayVisibleDefaultName;
}

static uint8_t setParameterValue(STR parameterID, char* parameterString) {
    modConfigDataStruct_t * modConfig;
    uint8_t result = true;
    float valueFloat;
    float valueInt;
    uint32_t  offsetToAdd;
    valueInt=atoi(parameterString);


    switch (parameterID) {

    case DEVICENAME:
         strcpy(temporaryInsimulatorOnlyDeviceCfg.deviceName,parameterString);
        break;
    case RUNFIRSTOPERATION:
        temporaryInsimulatorOnlyDeviceCfg.saveFirstOperationMenu = valueInt;
        break;
    case DISPLAY:
        temporaryInsimulatorRAMOnlyCfg.currentSelectedDisplayLines = valueInt;
        break;
    case MEASVALUNITS:
        temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].enabledUnits = valueInt;
        break;
    case ERROR_HANDLING:
         temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].enabledErrors = valueInt;
         break;
    case LANGUAGE:
        sim_hmiConfig.lang = valueInt;
        break;
    case ANALOGSIGNALSPREAD04MA:
        valueFloat = atof(parameterString);
        temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].minInputValuex100 = valueFloat * 100;
        if (configurationInFocus == configurationActive) {
            sim_modConfig.minInputValue=valueFloat;
            if (sliderStates.sliderSpreadRange != NULL)
                lv_slider_set_left_value(sliderStates.sliderSpreadRange, valueFloat, LV_ANIM_OFF);
        }
        else {
            /* only store in active configuration */
        }
        break;
    case ANALOGSIGNALSPREAD20MA:
        valueFloat = atof(parameterString);
        temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].maxInputValuex100 = valueFloat * 100;
        if (configurationInFocus == configurationActive) {
            sim_modConfig.maxInputValue=valueFloat;
            if (sliderStates.sliderSpreadRange!= NULL)
                lv_slider_set_value(sliderStates.sliderSpreadRange, valueFloat, LV_ANIM_OFF);
        }
        else {
            /* only store in active configuration */
        }
        break;

    case EDITEDCONFIG:
        temporaryInsimulatorOnlyDeviceCfg.editedConfiguration = valueInt;
        configurationInFocus = valueInt;
        break;
    case EDITEDARCHIVE:
        temporaryInsimulatorOnlyDeviceCfg.editedArchive = valueInt;
        mediumInFocus = valueInt;
        break;
    case ACTIVECONFIG:
        temporaryInsimulatorOnlyDeviceCfg.activeConfiguration = valueInt;
        configurationActive = valueInt;
        break;
    case ZEROVALUEMA:
        sim_measConfig.probeMinRawValue=valueInt;
        lv_slider_set_left_value(sliderStates.sliderProbeRange,valueInt, LV_ANIM_OFF);
        break;

    case TOPFULLMA:
        offsetToAdd = getParameterValueAsInt(ADDTO20MAVALUE);
        sim_measConfig.probeMaxRawValue = valueInt + offsetToAdd;
        lv_slider_set_value(sliderStates.sliderProbeRange, (valueInt + offsetToAdd), LV_ANIM_OFF);
        break;
    case ADDTO20MAVALUE:
        temporaryInsimulatorOnlyDeviceCfg.addTo20mAValue = valueInt;

        break;
    case MASIMULATIONVALUE:
        valueInt=atof(parameterString);
        temporaryInsimulatorRAMOnlyCfg.maSimulationValue = valueInt;
        break;

    case EXPECTSYSPASSWORD:
        temporaryInsimulatorOnlyDeviceCfg.systemPassword = valueInt;
        break;

    case EXPECTAMTBPASSWORD:
        temporaryInsimulatorOnlyDeviceCfg.amtbPassword = valueInt;
        break;
    case NEWPASSWORDENTRY:
        temporaryInsimulatorRAMOnlyCfg.passwordToMatch = valueInt;
         break;
    case TRYTOLOGINUSER:
       temporaryInsimulatorRAMOnlyCfg.tryToLoginUser = valueInt;
        break;
    case SELECTUSER:
        temporaryInsimulatorRAMOnlyCfg.loginUser = valueInt;
        startLogOutTimer();
        break;
    case SERIALNUMBER:
        temporaryInsimulatorOnlyDeviceCfg.serialNumber = valueInt;
        break;
    case PROBESERIALNUMBER:
        temporaryInsimulatorOnlyDeviceCfg.probeSerialNumber= valueInt;
        break;
    case SENSORSERIALNUMBER:
        temporaryInsimulatorOnlyDeviceCfg.sensorSerialNumber = valueInt;
        break;
    case SOFTWAREVERSION:
        temporaryInsimulatorOnlyDeviceCfg.softwareVersion = valueInt;
        break;
    case HARDWAREVERSION:
        temporaryInsimulatorOnlyDeviceCfg.hardwareVersion= valueInt;
        break;
    case FIRSTDATE:
        strcpy(temporaryInsimulatorOnlyDeviceCfg.firstDate,parameterString);
         break;
    case PROOFDATE:
        strcpy(temporaryInsimulatorOnlyDeviceCfg.proofDate,parameterString);
         break;
    case QRMANUAL:
        strcpy(temporaryInsimulatorOnlyDeviceCfg.qrManual,parameterString);
        break;
    case QRDOCS:
        strcpy(temporaryInsimulatorOnlyDeviceCfg.qrDocs,parameterString);
        break;
    case CONTACT:
        strcpy(temporaryInsimulatorOnlyDeviceCfg.contact,parameterString);
        break;
    case CURRENTTAG:
        strcpy(temporaryInsimulatorOnlyDeviceCfg.tag,parameterString);
        break;
    case NAMEFORNEWMEDIUM:
        strcpy(temporaryInsimulatorOnlyArchiveSetting[mediumInFocus].mediumName,parameterString);
        temporaryInsimulatorOnlyArchiveSetting[mediumInFocus].status = arrayVisibleRenamed;
        enableNextMediumInArray(configurationInFocus);
        break;
    case NAMEFORNEWCONFIG:
        strcpy(temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].configName,parameterString);
        temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].status = arrayVisibleRenamed;
        enableNextConfigurationInArray(configurationInFocus);
        break;

    default:
        // TODO error handling
        result = false;
        break;
    }

    return result;
}

static uint8_t checkParameterRange(nodeDescriptor_t *node, char* valueString) {

    uint8_t result = true;
    uint32_t value;
    char format[SMALLSTRINGSIZE];
    STR parameterID = node->sourceNode;

    parametercharacteristics_t *parameterCharacteristics = getParameterCharacteristics(parameterID);

    if (parameterCharacteristics->hiLimit == parameterCharacteristics->loLimit)
        return true; /* No range check configured */

    value=atof(valueString);  //TODO errorhandling
    if (value > parameterCharacteristics->hiLimit){
        value =0;
        result = false;
    }
    else if (value <parameterCharacteristics->loLimit){
        /* TODO DR allow float as well */
        value =parameterCharacteristics->loLimit;
        result = false;
    }

    return result;
}

static uint8_t checkPasswordValidity(nodeDescriptor_t *node, char* valueString) {

    uint8_t result = false;
    uint32_t value;
    char format[SMALLSTRINGSIZE];
    STR parameterID = node->sourceNode;

    switch (getParameterValueAsInt(TRYTOLOGINUSER))
    {
      case amtbUser:
          result = 0 == strcmp(valueString, getParameterValueAsString(EXPECTAMTBPASSWORD));
          break;

     default:  /* system user login */
         result = 0 == strcmp(valueString, getParameterValueAsString(EXPECTSYSPASSWORD));

    }

    return result;
}
static void fillSimpleInfoScreenAndContinue(lv_timer_t *timer) {
    nodeDescriptor_t *sourceNode = (nodeDescriptor_t*) timer->user_data;
    fillSimpleInfoScreen(timer);
    deleteTimer(sourceNode);
    addTimerTaskToNode(sourceNode, eventHandlerScreenTimeOutToNextNode,1000, -1);
    activateScreen(sourceNode);
}

static void fillEditAndApplyScreen(lv_timer_t *timer) {
    nodeDescriptor_t *sourceNode = (nodeDescriptor_t*) timer->user_data;
    char buff_data[BIGSTRINGSIZE];
    char fillIntoDisplay[BIGSTRINGSIZE];
    buff_data[0] = 0;

    if (sourceNode->nodeData.nodeObj == NULL)
        return;

    if (sourceNode->nodeData.nodeObj[screenParamBodyText].obj != NULL) {
        sprintf(buff_data,"%s",getMenuOrParameterNameFromMenuDefinitions(sourceNode->sourceNode));

        lv_label_set_text(sourceNode->nodeData.nodeObj[screenParamBodyText].obj,
                buff_data);
    }
    else{
        /* No value field to fill */
    }
    /* Set focus on first edit digit in buttons */
    if (sourceNode->nodeData.nodeObj[screenParamCurrentEditButtons].obj != NULL){
        lv_btnmatrix_set_btn_ctrl(sourceNode->nodeData.nodeObj[screenParamCurrentEditButtons].obj , actualEditIndexInButtonArray+1,
            LV_BTNMATRIX_CTRL_CHECKED);
    }
}
static void fillSimpleInfoScreen(lv_timer_t *timer) {
    nodeDescriptor_t *node = getNodeFromTimer(timer);
    char buff_data[BIGSTRINGSIZE];
    char fillIntoDisplay[BIGSTRINGSIZE];
    buff_data[0] = 0;

pauseScreenTimer(node);
    if (node->nodeData.nodeObj == NULL)
        return;

    if (node->nodeData.nodeObj[screenParamBodyText].obj != NULL) {
        sprintf(buff_data,"%s",getMenuOrParameterNameFromMenuDefinitions(node->sourceNode));

        lv_label_set_text(node->nodeData.nodeObj[screenParamBodyText].obj,
                buff_data);

        if (!lv_obj_has_flag(node->nodeData.nodeObj[screenParamBodyText].obj, LV_OBJ_FLAG_HIDDEN))
            lv_obj_clear_flag(node->nodeData.nodeObj[screenParamBodyText].obj,LV_OBJ_FLAG_HIDDEN);
        else{
            /* Nothing to do */
        }

    }
    else{
        /* No value field to fill */
    }
}

static void fillParameterInApplicationInfoScreen(lv_timer_t *timer) {
    nodeDescriptor_t *node = (nodeDescriptor_t*) timer->user_data;
    pauseScreenTimer(node);
    requestParameterFromStorageAndFillDynamicFields(timer);

    addTimerTaskToNode(node, eventHandlerScreenTimeOutToDefaultScreen,APPLICATIONSCREEN_DELAY, -1);

    createTimerTask(node);
}

static void requestParameterFromStorageAndFillDynamicFields(lv_timer_t *timer) {
    nodeDescriptor_t *sourceNode = (nodeDescriptor_t*) timer->user_data;
    char buff_data[BIGSTRINGSIZE];
    char valueStoreBuffer[BIGSTRINGSIZE];
    char fillIntoDisplay[BIGSTRINGSIZE];
    buff_data[0] = 0;

    if (sourceNode == NULL)
            return;
    else if (sourceNode->nodeData.nodeObj == NULL)
        return;
    else {
        /* normal functioning */
    }

    if (sourceNode->nodeData.nodeObj[screenParameterName].obj != NULL) {

        sprintf(buff_data,"%s",getMenuOrParameterNameFromMenuDefinitions(sourceNode->sourceNode));

        lv_label_set_text(sourceNode->nodeData.nodeObj[screenParameterName].obj,
                buff_data);

        lv_obj_invalidate(
                sourceNode->nodeData.nodeObj[screenParameterName].obj);

    }
    else{
        /* No value field to fill */
    }


    if (sourceNode->nodeData.nodeObj[screenParamBodyText].obj != NULL) {


        switch (sourceNode->nodeData.menuNodeType)
        {
            case passwordEntryNode:
                sprintf(valueStoreBuffer,"%s","         ");
                break;
            default: {
                sprintf(valueStoreBuffer,"%s:\n",getMenuOrParameterNameFromMenuDefinitions(STOREDVALUELABEL));
                strcat(valueStoreBuffer,getParameterValueAsString(sourceNode->sourceNode));
            }
        }

        if (sourceNode->sourceNode != CURRENTTAG)
                lv_label_set_text(sourceNode->nodeData.nodeObj[screenParamBodyText].obj,valueStoreBuffer);
    }


    if (sourceNode->nodeData.nodeObj[screenParameterActualValue].obj != NULL) {

        sprintf(buff_data,getMeasurmentValueString(unitsRaw,0));
        if (strlen(buff_data) > 0) {
            lv_obj_t * editedParameter = sourceNode->nodeData.nodeObj[screenParameterTakeOverValue].obj;
            if (editedParameter != NULL)
                lv_label_set_text(sourceNode->nodeData.nodeObj[screenParameterTakeOverValue].obj,buff_data);
            else{
                /* No label field to update */
            }

            sprintf(fillIntoDisplay,"%s:\n%s",getMenuOrParameterNameFromMenuDefinitions(ACTUALVALUELABEL),buff_data); /* Get first realtime value as configured  */
            lv_label_set_text(
                    sourceNode->nodeData.nodeObj[screenParameterActualValue].obj,fillIntoDisplay);
            lv_label_set_text(
                    sourceNode->nodeData.nodeObj[screenParameterActualValue].obj,fillIntoDisplay);
            lv_obj_invalidate(
                    sourceNode->nodeData.nodeObj[screenParameterActualValue].obj);
        }
    }
    if (sourceNode->nodeData.dynamicReadCallBack.runNumberOfTimes==1)
        lv_timer_pause(timer);
    if (sourceNode->nodeData.nodeObj[screenParamCurrentEditButtons].obj != NULL){
        lv_btnmatrix_set_btn_ctrl(sourceNode->nodeData.nodeObj[screenParamCurrentEditButtons].obj , actualEditIndexInButtonArray+1,
            LV_BTNMATRIX_CTRL_CHECKED);
    }
    else{
        /* No value field to fill */
    }


}

static void requestParameterInformation(nodeDescriptor_t *sourceNode) {
    char buff_data[BIGSTRINGSIZE];
    buff_data[0] = 0;

    if (sourceNode->nodeData.nodeObj == NULL)
        return;

    if (sourceNode->nodeData.nodeObj[screenParameterName].obj != NULL) {
        sprintf(buff_data,"%s",getMenuOrParameterNameFromMenuDefinitions(sourceNode->sourceNode));

        lv_label_set_text(sourceNode->nodeData.nodeObj[screenParameterName].obj,
                buff_data);

        lv_obj_invalidate(
                sourceNode->nodeData.nodeObj[screenParameterName].obj);
    }
    else{
        /* No value field to fill */
    }

    if (sourceNode->sourceNode == ZEROVALUEMA)
        sprintf(buff_data,"%s",getMenuOrParameterNameFromMenuDefinitions(ZEROADJUSTINFO));
    else if (sourceNode->sourceNode == TOPFULLMA)
            sprintf(buff_data,"%s",getMenuOrParameterNameFromMenuDefinitions(TOPADJUSTINFO));
    else
        sprintf(buff_data,"%s",getParameterValueAsString(sourceNode->sourceNode));
    if (sourceNode->nodeData.nodeObj[screenParamBodyText].obj != NULL) {
        lv_label_set_text(
                sourceNode->nodeData.nodeObj[screenParamBodyText].obj,buff_data);
        lv_obj_invalidate(
                sourceNode->nodeData.nodeObj[screenParamBodyText].obj);
    }

}

static void eventShowParameterScreen(lv_timer_t *timer) {
    nodeDescriptor_t *sourceNode = (nodeDescriptor_t*) timer->user_data;
    timer->paused = 1; /* Call only once */
    requestParameterInformation(sourceNode);
}



void sendKeyToScreen(uint32_t key){

    if (currentScreen->menuIndex <0)
        return;
	if (currentScreen->nodeData.nodeObj[screenDefaultEventReciver].obj != NULL)
		lv_event_send(currentScreen->nodeData.nodeObj[screenDefaultEventReciver].obj, LV_EVENT_KEY, &key);
	else  {
		lv_obj_t * focusedObj = lv_group_get_focused(currentScreen->nodeData.group);
		lv_event_send(focusedObj, LV_EVENT_KEY, &key);
	}
}


/* Counting timer 1ms
 * INDEV on target: 30s => 2811 readcycles
 * Without INDEV, target 10000 => 15s
 * Without INDEV, linux 10000 => 9s
 *
 */
static uint32_t readButtonCycles = 0;
void readButtons() {
    /* cycle measure help function, leave as long as we develop */
    int8_t pressedButtonIndex = -1;
    if (readButtonCycles > 10000)
      readButtonCycles = 0;
    readButtonCycles++;

#if LVGL_PC_SIM

        if(buttonStates.downButton->state & LV_STATE_PRESSED) // 2=release, 34=pressed, aber die anderen setzen das auf 0
            buttonStates.buttons[downKeyIndex].states = LV_INDEV_STATE_PR;
        else
            buttonStates.buttons[downKeyIndex].states = LV_INDEV_STATE_REL;

        if(buttonStates.escButton->state & LV_STATE_PRESSED) // 2=release, 34=pressed, aber die anderen setzen das auf 0
            buttonStates.buttons[escKeyIndex].states = LV_INDEV_STATE_PR;
        else
            buttonStates.buttons[escKeyIndex].states = LV_INDEV_STATE_REL;

        if(buttonStates.enterButton->state & LV_STATE_PRESSED) // 2=release, 34=pressed, aber die anderen setzen das auf 0
            buttonStates.buttons[okKeyIndex].states = LV_INDEV_STATE_PR;
        else
            buttonStates.buttons[okKeyIndex].states = LV_INDEV_STATE_REL;

        if (buttonStates.keyIsReleasedForMilliSeconds%1000 == 10) {
            char buffer[100];
            debugShowMem();
            if (memoryUsedDisplay) {
                sprintf(buffer,"%d", used_size);
                lv_label_set_text(memoryUsedDisplay, buffer);
            }
        }
#endif
    /* Check number of changed buttons */
    for (uint8_t buttonIndex = 0; buttonIndex < HW_BUTTON_COUNT; buttonIndex++) {
#if BGM13S32F512GA
        buttonStates.buttons[buttonIndex].states = !(GPIO_PinInGet((GPIO_Port_TypeDef)buttonStates.buttons[buttonIndex].port,buttonStates.buttons[buttonIndex].pin))  ? LV_INDEV_STATE_REL : LV_INDEV_STATE_PR;
#endif
    }
    for (uint8_t buttonIndex = 0; buttonIndex < HW_BUTTON_COUNT; buttonIndex++) {

        if (buttonStates.buttons[buttonIndex].states == LV_INDEV_STATE_PR) {
            buttonStates.keyIsPressedForMilliSeconds += 1;
            buttonStates.keyIsReleasedForMilliSeconds = 0;

            if (buttonStates.keyIsPressedForMilliSeconds%600 == 0) {
                if (currentScreen->nodeData.eventHandler != NULL){
                    uint32_t key = buttonStates.buttons[buttonIndex].id;
                    printf("Key repeat = %i\n",key);
                    /* Repeat the key as an event */
                    sendKeyToScreen(key);
                }
                else {
                    /* Nothing to do */
                }
            }
            else {
                /* Nothing to do */
            }
        }

        if (buttonStates.buttons[buttonIndex].states != buttonStates.buttons[buttonIndex].lastStates){

            pressedButtonIndex = buttonIndex;
            buttonStates.buttons[buttonIndex].lastStates = buttonStates.buttons[buttonIndex].states;
            if (buttonStates.buttons[buttonIndex].states == LV_INDEV_STATE_REL) {
                uint32_t key=(uint32_t) buttonStates.buttons[buttonIndex].id;
                sendKeyToScreen(key);
                buttonStates.keyIsReleasedForMilliSeconds=0;
                break; /* Leave button interpreter loop */
            }
        }
        else {
            /* Nothing to do */
        }
    }
    if (pressedButtonIndex < 0) /* If no button is pressed => reset keypresscounters */
    {
        buttonStates.keyIsReleasedForMilliSeconds += 1;
        if (isKeyReleasedLongerThanMilliSeconds(1)) {
           // buttonStates.keyIsReleasedForMilliSeconds=0;
            buttonStates.keyIsPressedForMilliSeconds = 0;
        }
        else {
            /* No counter reset for a small time for debouncing */
        }
        return;
    }
}
/*
 * Function to manage screen switching
 * para screenType_t  screen
 */

/**
 * @brief     Function that init the device buttons
 */

static void initButtons(void) {

    /* Init buttom_queu */
#if PL_HAS_HMI_BUTTON

#if STM32L1xx
    buttonStates.buttons[0].pin = BUTTON_ENTER_Pin;
    buttonStates.buttons[0].port = BUTTON_ENTER_Port;
    buttonStates.buttons[0].id = LV_KEY_ENTER;
    buttonStates.buttons[1].pin = BUTTON_NEXT_Pin;
    buttonStates.buttons[1].port = BUTTON_NEXT_Port;
    buttonStates.buttons[1].id = LV_KEY_DOWN;
    buttonStates.buttons[2].pin = BUTTON_ESC_Pin;
    buttonStates.buttons[2].port = BUTTON_ESC_Port;
    buttonStates.buttons[2].id = LV_KEY_ESC;
#endif

#if STM32L0XX
    buttonStates.buttons[0].pin = GPIO_BUTTON1_Pin;
    buttonStates.buttons[0].port = GPIO_BUTTON1_GPIO_Port;
    buttonStates.buttons[0].id = LV_GROUP_KEY_NEXT;
    buttonStates.buttons[1].pin = GPIO_BUTTON2_Pin;
    buttonStates.buttons[1].port = GPIO_BUTTON2_GPIO_Port;
    buttonStates.buttons[1].id = LV_GROUP_KEY_ENTER;
    buttonStates.buttons[2].pin = GPIO_BUTTON3_Pin;
    buttonStates.buttons[2].port = GPIO_BUTTON3_GPIO_Port;
    buttonStates.buttons[2].id = LV_GROUP_KEY_ESC;
#endif
#if BGM13S32F512GA

    buttonStates.buttons[0].pin = BUTTON_BACK_Pin;
    buttonStates.buttons[0].port = BUTTON_BACK_Port;
    buttonStates.buttons[0].id = LV_KEY_ESC;

    buttonStates.buttons[1].pin = BUTTON_NEXT_Pin;
    buttonStates.buttons[1].port =BUTTON_NEXT_Port;
    buttonStates.buttons[1].id = LV_KEY_DOWN;

    buttonStates.buttons[2].pin = BUTTON_OK_Pin;
    buttonStates.buttons[2].port = BUTTON_OK_Port;
    buttonStates.buttons[2].id = LV_KEY_ENTER;
#endif

#endif
    btnPort = 0xFFFF;
    for (uint8_t i = 0; i < HW_BUTTON_COUNT; i++) {
        buttonStates.buttons[i].buttonPCStates =LV_INDEV_STATE_REL;
        buttonStates.buttons[i].states = LV_INDEV_STATE_REL;
        buttonStates.buttons[i].lastStates = buttonStates.buttons[i].states;
    }
    buttonStates.keyIsPressedForMilliSeconds = 0;
    buttonStates.keyIsReleasedForMilliSeconds = 0;
    buttonStates.buttons[0].id = LV_KEY_ESC;
    buttonStates.buttons[1].id = LV_KEY_DOWN;
    buttonStates.buttons[2].id = LV_KEY_ENTER;

    buttonsTimer = lv_timer_create((void*) &readButtons, 1, 0);

    default_group = lv_group_create();
    return;
}
static lv_res_t switchScreenTo(menuNodeType_t nodeType) {
    nodeDescriptor_t *screenNode = findNodeWithType(NULL, nodeType);
    if (screenNode != NULL) {
        activateScreen(screenNode);
    }
    return LV_RES_OK;

}

/* Switches unconditionally to the requested node */
lv_res_t switchToNode(nodeDescriptor_t * requestedNode) {
    nodeDescriptor_t * nextNode;
    uint32_t keyPressed;
    int8_t myChildIndex;
    nodeDescriptor_t *leavingNode;
    nodeDescriptor_t * parentNode;

    if (requestedNode == NULL)
        return LV_RES_OK;

    leavingNode = currentScreen;

    switch (requestedNode->nodeData.rootScreenType ){
        case listScreen: { /* next screen is a list of parameters or chooselist elements */

            if (requestedNode->menuIndex == leavingNode->nodeNavigation.parentIndex) {
            /* requested node is the parent, need to know which element to focus */
                myChildIndex = findChildIndexInParent(leavingNode);
            }
            else if (requestedNode->menuIndex != leavingNode->menuIndex) /* parent is a previous menuitem */
                       myChildIndex = -1;

            else {
                /* requested node is a child, focus to first element */
                myChildIndex = -1;
            }

            if (isAutoOpening(requestedNode)){
                /* If the next node autoopens, the chosen index belongs to its setting in storage */
                myChildIndex = -1;
             }

            fillMenuListScreen(requestedNode,myChildIndex);
//            if (isAutoOpening(requestedNode)) {
//                nextNode = findFirstChildInParent(requestedNode);
//            }
//            else
               nextNode = requestedNode;
        }
        break;
        case showApplicationScreen:
           nextNode = prepareParameterScreenFromNode(requestedNode);
           break;
        case parameterShowScreen:
        case parameterTakeValueScreen:
        case parameterEditScreenWithApply:
        case parameterEditScreen: {
           nextNode = prepareParameterScreenFromNode(requestedNode);
           updateMenuIndexString(nextNode);
            }
            break;

        default:{
            if (requestedNode->nodeData.menuNodeType == runParameterEndNodeAction) {
                nextNode=requestedNode;
                void * eventHandler = getEventForParameterEndNode(requestedNode->menuId);
                addTimerTaskToNode(nextNode, eventHandler,
                       SCREEN_FUNCTION_CALLBACK_PERIOD, -1);
                createTimerTask(nextNode);
            }

            else
                switchToDefaultScreen();
        return LV_RES_OK;
        }
    }

    activateScreen(nextNode);
    return LV_RES_OK;
}

static void eraseNodeGroup(nodeDescriptor_t *node) {
    lv_obj_t * focused;
    if(node->nodeData.group!=NULL){
        lv_group_del(node->nodeData.group);
        node->nodeData.group=NULL;
     }
}

static void eraseNodeContent(nodeDescriptor_t *node) {
    if(node->nodeData.content!=NULL){
        lv_obj_remove_style_all(node->nodeData.content);
        lv_obj_clear_flag(node->nodeData.content, LV_OBJ_FLAG_CLICKABLE);

        lv_obj_set_scrollbar_mode(node->nodeData.content, LV_SCROLLBAR_MODE_OFF);

        lv_obj_invalidate(node->nodeData.content);
        lv_obj_del(node->nodeData.content);
        node->nodeData.content=NULL;
    }
    else {
        /* nothing to di */
    }

//    if ((analogChartDefaultScreen.content != NULL) && (node->nodeData.rootScreenType == defaultScreen)) {
//        lv_obj_del(analogChartDefaultScreen.content);
//        analogChartDefaultScreen.content=NULL;
//    }
//    else {
//        /* nothing to di */
//    }

}

static void eraseNodesObjects(nodeDescriptor_t *node) {


    if (node->nodeData.nodeObj != NULL) {
        for (int index=0;index< node->nodeData.numOfObj;index++)  {
            if (node->nodeData.nodeObj[index].obj != NULL) {
   //             lv_obj_add_flag(node->nodeData.nodeObj[index].obj, LV_OBJ_FLAG_HIDDEN); /* hide  button */
               lv_obj_del(node->nodeData.nodeObj[index].obj);
            }
            node->nodeData.nodeObj[index].obj = NULL;
        }
        free(node->nodeData.nodeObj);
        node->nodeData.nodeObj = NULL;
    }
    else{
        /* no objects to delete */
    }
    if (node->nodeData.topScreen != NULL)
        lv_obj_del(node->nodeData.topScreen );
    node->nodeData.topScreen = NULL;

}

static void createTimerTask(nodeDescriptor_t *actualNode) {

    assert(actualNode!=NULL);
    if (actualNode->nodeData.dynamicReadCallBack.timerTask == NULL)
        return;   /* No task defined for this node */

    uint32_t period = actualNode->nodeData.dynamicReadCallBack.period;
    uint8_t numberOfTimes = actualNode->nodeData.dynamicReadCallBack.runNumberOfTimes;

    actualNode->nodeTimer = lv_timer_create((void*) actualNode->nodeData.dynamicReadCallBack.timerTask, period, actualNode);

}

/* Callback for logout timer, will log out the current user and switch to public user */
static void loginTimedOut(){
    setParameterValueFromInt(SELECTUSER,publicUser);
    logOutTimer->paused = true;
}

/* Starts the logout timer */
static void startLogOutTimer() {
    if (logOutTimer!=NULL)
            lv_timer_del(logOutTimer);
    logOutTimer = lv_timer_create((void*) loginTimedOut, USER_LOGOUT_TIME, 0);
}


// erase screen tasks, groups,  in case we have events or an init procedure that created the objects
static void eraseScreenNodeTasksAndObjects(nodeDescriptor_t *screenNode) {

    if (screenNode == NULL)
        assert(0);
    else {
      // Nothing to do
    }

    printf("eraseScreenNodeTasksAndObjects for %i\n",screenNode->menuIndex);

    if (screenNode->nodeTimer != NULL){
       lv_timer_ready(screenNode->nodeTimer);
       lv_timer_del(screenNode->nodeTimer);
        screenNode->nodeTimer = NULL;
    }
    eraseNodesObjects(screenNode);

    eraseNodeGroup(screenNode);

    eraseNodeContent(screenNode);
    if ((screenNode == &genericNode1)||(screenNode == &genericNode2))  {
        screenNode->menuIndex = -1;
    }

    if (screenNode->nodeData.menuNodeType ==  parameterNodeTemplate){
        screenNode->nodeData.eventHandler = NULL;
    }
}



static void deleteTimer(nodeDescriptor_t * node) {
    if (node->nodeTimer != NULL) {
        lv_timer_del(node->nodeTimer);
    }
    node->nodeTimer = NULL;
}

static void pauseScreenTimer(nodeDescriptor_t * node) {
    if (node->nodeTimer != NULL) {
        node->nodeTimer->paused =1;
    }
}

uint8_t isScreenTransitionWithinSameScreen(nodeDescriptor_t * newNodeToSet)
{
    uint8_t sameScreen =
     (newNodeToSet->menuIndex == currentScreen->menuIndex);
    return sameScreen;
}
uint32_t screenCounter = 0;
static void activateScreen(nodeDescriptor_t * newNodeToSet) {
    char buffer[100];
    if (newNodeToSet == NULL)
        return;
    else {
        screenCounter++;
        if (newNodeToSet->nodeData.content!=NULL) {
            lv_obj_add_flag(newNodeToSet->nodeData.content,LV_OBJ_FLAG_HIDDEN);

            lv_obj_invalidate(newNodeToSet->nodeData.content);
            updateHeaderInformationsFromNode(newNodeToSet);
            updateMenuIndexString(newNodeToSet);
            lv_obj_clear_flag(newNodeToSet->nodeData.content, LV_OBJ_FLAG_HIDDEN);
            lv_obj_update_layout(lcdScreen);
        }
        else {
            /* No content area defined */
        }
        if (currentScreen != NULL){
        	if (!isScreenTransitionWithinSameScreen(newNodeToSet))
        	    eraseScreenNodeTasksAndObjects(currentScreen);
        	else {
        		/* screen is erased within default screen if switching the displayed lines */
        	}
        }
        currentScreen = newNodeToSet;
        /* If no special timer task defined for this node force a redraw after 1 timer period */
        if (newNodeToSet->nodeData.dynamicReadCallBack.timerTask != NULL) {
            createTimerTask(newNodeToSet);
        }
    }
}

static void initDeviceConfigurationAndArchiveArrays() {

    nodeDescriptor_t* node = findNodeWithType(NULL, listChildAutoOpensArray);

    while (node != NULL) {
       switch (node->menuId) {
           case CONFIGURATIONX:
               strcpy(temporaryInsimulatorOnlyConfigurationSetting[0].configName,getMenuOrParameterNameFromMenuDefinitions(CONFIGURATIONX));
               for (int8_t index = 1; index < NUMBER_OF_NEWCONFIGURATIONS; index ++) {
                   strcpy(temporaryInsimulatorOnlyConfigurationSetting[index].configName,getMenuOrParameterNameFromMenuDefinitions(NAMEFORNEWCONFIG));
                   temporaryInsimulatorOnlyConfigurationSetting[index].status = arrayUninitialized;
               }
               temporaryInsimulatorOnlyConfigurationSetting[0].status = arrayVisibleRenamed;
               temporaryInsimulatorOnlyConfigurationSetting[1].status = arrayVisibleDefaultName;
               break;
           case ARCHIVEX:
               for (int8_t index = 0; index < NUMBER_OF_MEDIUMS; index ++) {
                   strcpy(temporaryInsimulatorOnlyArchiveSetting[index].mediumName,getMenuOrParameterNameFromMenuDefinitions(NAMEFORNEWMEDIUM));
                   temporaryInsimulatorOnlyArchiveSetting[index].status = arrayUninitialized;
               }
               temporaryInsimulatorOnlyArchiveSetting[0].status = arrayVisibleDefaultName;
               break;
           default:
             break;
       }
       node = findNodeWithType(node, listChildAutoOpensArray);
    }

}

static void initArchives() {

}

void AquaHMI_GUI_init(void) {

    uint16_t menuId;
    initButtons();

    currentScreen = NULL;

    initDeviceConfigurationAndArchiveArrays();
    initArchives();

    initParameterDefaultValuesAll(); /* initializes also arrayElements at index zero */

    uint32_t enabledUnits =  -1;
    sprintf(temporaryBuffer,"%i",enabledUnits);
    setParameterValue(MEASVALUNITS,temporaryBuffer);
    setParameterValue(ERROR_HANDLING,temporaryBuffer);

        lcdScreen = lv_obj_create(lv_scr_act());
#ifdef LVGL_PC_SIM

   lv_obj_add_style(lcdScreen, &style_default, 0);
    lv_obj_set_size(lcdScreen, 128, 64);
    lv_obj_align(lcdScreen, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_scrollbar_mode(lcdScreen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(lcdScreen);
#else
    lcdScreen = lv_scr_act();//lv_obj_create(lv_scr_act());//lv_disp_get_scr_act(NULL));
    // lv_obj_add_style(lcdScreen, &style_default,0);
#endif
}


static lv_obj_t * initContent(nodeDescriptor_t *node) {
  if (node->nodeData.contentIndex == 0)
      node->nodeData.content = lv_list_create(lcdScreen);
  else node->nodeData.content = lv_list_create(lcdScreen);
      node->nodeData.content = lv_list_create(lcdScreen);
}

static void addKeyListener(nodeDescriptor_t *node) {

    if (node->nodeData.numOfObj == 0)
        return;
    if (node->nodeData.nodeObj[screenDefaultEventReciver].obj == NULL) {
        lv_obj_t * obj = lv_btn_create(node->nodeData.content);
        node->nodeData.nodeObj[screenDefaultEventReciver].obj = obj;
        lv_obj_add_style(obj, &style_default_invisible, 0);
        lv_group_add_obj(node->nodeData.group, obj);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN); /* hide  button */
        lv_obj_add_event_cb(obj, node->nodeData.eventHandler,
          LV_EVENT_KEY, (void*) node);

        lv_group_add_obj(node->nodeData.group, obj);
        node->nodeData.nodeObj[screenDefaultEventReciver].obj = obj;
    }
}
static uint8_t contentIndex;     /* screen content data */
static lv_res_t initScreenArea(nodeDescriptor_t *node) {
    lv_res_t result = LV_RES_INV;

    if (node->nodeData.rootScreenType == noScreenAssigned)
        return LV_RES_INV;

    result = reserveStorageForScreenObjects(node,node->nodeData.numOfObj);

    contentIndex = 1- contentIndex;
    node->nodeData.contentIndex = contentIndex;


    if (node->nodeData.content == NULL) {
        switch (node->nodeData.rootScreenType) {
        case messageScreen:

            node->nodeData.content = lv_obj_create(lcdScreen);
            lv_obj_set_size(node->nodeData.content,
           // lv_obj_get_width(lcdScreen) / 14 * 12,
            lv_obj_get_width(lcdScreen),
            lv_obj_get_height(lcdScreen) - TOP_MENU_HEIGHT);
            lv_obj_set_scrollbar_mode(node->nodeData.content, LV_SCROLLBAR_MODE_OFF);
            addKeyListener(node);
            break;
        case listScreen:
            node->nodeData.content = lv_list_create(lcdScreen);
            lv_obj_set_size(node->nodeData.content, lv_obj_get_width(lcdScreen),
            lv_obj_get_height(lcdScreen) - TOP_MENU_HEIGHT+1);
            lv_obj_align(node->nodeData.content, LV_ALIGN_TOP_LEFT, 0, TOP_MENU_HEIGHT+1);
            lv_obj_set_scrollbar_mode(node->nodeData.content, LV_SCROLLBAR_MODE_OFF);
            lv_obj_t * content = node->nodeData.content;
            node->nodeData.group = lv_group_create();
            break;

        case defaultScreen:
        case parameterShowScreen:
        case parameterTakeValueScreen:
        case parameterEditScreen:
        case parameterEditScreenWithApply:
            node->nodeData.content = lv_obj_create(lcdScreen);
            lv_obj_set_size(node->nodeData.content, lv_obj_get_width(lcdScreen),
                    lv_obj_get_height(lcdScreen));

            lv_obj_set_scrollbar_mode(node->nodeData.content, LV_SCROLLBAR_MODE_OFF);
    //        node->nodeData.group = lv_group_create();
            addKeyListener(node);

            break;
        case showApplicationScreen:
        case logoScreen:
            node->nodeData.content = lv_obj_create(lcdScreen);
            lv_obj_set_size(node->nodeData.content, lv_obj_get_width(lcdScreen),
                    lv_obj_get_height(lcdScreen));
            /* disable scrollbar */
            lv_obj_set_scrollbar_mode(node->nodeData.content, LV_SCROLLBAR_MODE_AUTO);
            break;
        default:
            assert(node->nodeData.content!=NULL); /* check switch enumerators, yours included ?  */
        }

       lv_obj_add_style(node->nodeData.content, &style_default, 0);
        /*force layout update */
        lv_obj_update_layout(node->nodeData.content);

    }
    initTopScreen(node);
    return result;
}

static lv_res_t reserveStorageForScreenObjects(nodeDescriptor_t *node, int numberOfScreenObjects) {
    /* check if node objects allredy allocated*/
    printf("enter reserve routine\n");

    if (node->nodeData.nodeObj == NULL && numberOfScreenObjects) {
        printf("memset obj for %i%s\n",node->menuIndex,getMenuOrParameterNameFromMenuDefinitions(node->menuId));

        /* allocate node object memory */
        node->nodeData.nodeObj = malloc(
                sizeof(nodeObj_t) * numberOfScreenObjects);
/* Malloc has no effect on lv memory, also lv_mem_alloc has no influence */
        assert(node->nodeData.nodeObj);
        /* check if allocation was successfully */
        if (node->nodeData.nodeObj != NULL) {
            /* reset content to 0*/
            memset(node->nodeData.nodeObj, 0x00,
                    sizeof(nodeObj_t*) * numberOfScreenObjects);
        } else {
            /* leave if mem allocation failed */
            return LV_RES_INV;
        }
    }
    node->nodeData.numOfObj = numberOfScreenObjects;
    return LV_RES_OK;
}

static void showHeaderInformation(nodeDescriptor_t *node) {
    nodeDescriptor_t *parentNode = findParent(node);
    lv_obj_t* screen;

    assert(node != NULL);

    screen = node->nodeData.topScreen;
    if (node->nodeData.topScreen == NULL)
        screen = node->nodeData.content;
    else{
        screen = node->nodeData.topScreen;
    }
    if (screen == NULL)
        return;

    char buffer[BIGSTRINGSIZE];
    if (&node->nodeData.nodeObj == NULL)
        return;
    /* check and init screen obj if needed */
    if (node->nodeData.nodeObj[screenDefaultMenuIndex].obj == NULL) {
        lv_obj_t * obj = lv_label_create( screen);
       lv_obj_add_style(obj, &style_headerInfo, 0);
        lv_obj_set_height(obj, 12);
      //  lv_obj_set_width(obj, 120);
        lv_obj_align(obj, LV_ALIGN_TOP_LEFT, 1, 0);
        lv_label_set_text(obj,"    ");
        node->nodeData.nodeObj[screenDefaultMenuIndex].obj = obj;
    }

    if (node->nodeData.nodeObj[screenDefaultTopText].obj == NULL) {
        lv_obj_t * obj = lv_label_create( screen);
       lv_obj_add_style(obj, &style_headerInfo, 0);
        lv_obj_set_height(obj, 12);

        lv_obj_align(obj, LV_ALIGN_TOP_MID, 10, 0);

        switch (node->menuId) {
        case DEFAULT_SCREEN:
            lv_obj_align(obj, LV_ALIGN_TOP_MID, -10, 0);
            strcpy(buffer,getParameterValueAsString(DEVICENAME));
            break;
        case ARCHIVEACTION:
                strcpy(buffer,getParameterValueAsString(NAMEFORNEWMEDIUM));
            break;
        case CONFIGACTION:
                strcpy(buffer,getParameterValueAsString(NAMEFORNEWCONFIG));
            break;
        case LOGINPROCESS:
                strcpy(buffer,getMenuOrParameterNameFromMenuDefinitions(parentNode->menuId));
            break;
        default:
            strcpy(buffer,getMenuOrParameterNameFromMenuDefinitions(node->menuId));
        }

       lv_label_set_text(obj,buffer);
       node->nodeData.nodeObj[screenDefaultTopText].obj = obj;
    }

}


/* Returns true if the two nodes are of the same menuTree above */
static uint8_t isSameParentRoot(nodeDescriptor_t *node1,nodeDescriptor_t *node2) {

    nodeDescriptor_t *previousNode1 = node1;
    nodeDescriptor_t *previousNode2 = node2;


    do {
        previousNode1 = findParent(previousNode1);
        previousNode2 = findParent(previousNode2);
        if ((previousNode1 == NULL) || (previousNode2 == NULL))
            return true;
        if ((previousNode1->menuIndex) != (previousNode2->menuIndex))
            return false;
        else {
            /* continue */
        }

    } while (previousNode1 != NULL);
}
/* Returns true if the node has no menu number to be displayed */
static uint8_t isNodeWithMenuIndex(nodeDescriptor_t *node) {
    if (node == NULL)
        return true;
    return node->menuNumberEntry != noNumber;
}

static int8_t findNumberedIndexInParent(nodeDescriptor_t *screenNodeChild) {
    uint8_t result = 1;

    nodeDescriptor_t *parent = findParent(screenNodeChild);
    nodeDescriptor_t *nextChild;

    uint8_t index = screenNodeChild->nodeNavigation.childIndexinParent;

    if (screenNodeChild->menuNumberEntry == nr1)
        return 1;
    else {
        nextChild = findNodeWithIndex(parent->nodeNavigation.firstChildIndex);
        do {

            if (nextChild == NULL)
                break;
            else if (nextChild->menuIndex == screenNodeChild->menuIndex)
                break;
            else if (nextChild->menuNumberEntry != noNumber)
                result++;
            else {
                /* only numbered children are valid */
            }
            nextChild = findNextChild(nextChild);
        } while (nextChild != NULL);


        if (isFirstSetup(screenNodeChild))
            result+=1;
        return result;
    }
}

char menuNumberForDisplay[MAXMENUDEPTH]={0};
//* This function compiles the menu header string to identify the menu number  */
static char* findMenuIndexString(nodeDescriptor_t *node) {

    nodeDescriptor_t *screenNodeParent;
    nodeDescriptor_t *screenNodeChild;
    int8_t menuLevelIndex = 0;
    int8_t startIndex = 0;

    menuIndex_t indexNumbers[MENUNUMBERCHARS];

    if (node == NULL)
        return "\0";
    if (!isNodeWithMenuIndex(node))
        return "\0";


    screenNodeParent=findParent(node);
    if (screenNodeParent == NULL)
        return "\0";

    strcpy(menuNumberForDisplay, "");

    screenNodeChild = node;
     while (screenNodeParent != NULL){
         if (screenNodeChild->nodeNavigation.parentIndex == 0)
             break;
        if (isNodeWithMenuIndex(screenNodeChild)){
            int8_t indexInParent = findNumberedIndexInParent(screenNodeChild);

            indexNumbers[menuLevelIndex].mainMenuIndex = indexInParent;
            menuLevelIndex++;
        }
        screenNodeChild = screenNodeParent;
        screenNodeParent = findParent(screenNodeParent);

    }
    char smallString[MENUNUMBERCHARS]={0};
    for (int8_t buildStringIndex = menuLevelIndex-1; buildStringIndex>=0;buildStringIndex--) {
        if (buildStringIndex==0)
           sprintf(smallString,"%i%c",indexNumbers[buildStringIndex].mainMenuIndex,0);
        else
           sprintf(smallString,"%i.%c",indexNumbers[buildStringIndex].mainMenuIndex,0);
         strcat(menuNumberForDisplay,smallString);
    }
    return &menuNumberForDisplay;
}

static void updateMenuIndexString(nodeDescriptor_t *node) {

    nodeDescriptor_t *referencedNode; /* describes the node which's number has to be shown as well */
    int8_t menuLevelIndex = 0;
    char menuNumber[MENUNUMBERCHARS];
    char referencedMenuNumber[MENUNUMBERCHARS];

    if (node->menuNumberEntry == noNumber)
        return;
    sprintf(menuNumber,"%s",findMenuIndexString(node));
    if (strlen(menuNumber) == 0)
        return;
    referencedNode = findReferencedNode(node);
    strcpy(menuNumberForDisplay,menuNumber);

    if (referencedNode != NULL) {
        if (referencedNode->menuIndex == node->menuIndex)
            referencedNode = NULL;
        else {
            /* not referencing itself */
            strcpy(referencedMenuNumber,findMenuIndexString(referencedNode));
            sprintf(menuNumberForDisplay,"%s(%s)",menuNumber,referencedMenuNumber);
        }
    }
    else {
        /* no referenced entry found */
    }


    if (node->nodeData.nodeObj!=NULL) {
        lv_obj_t * menuIndexTextObject = node->nodeData.nodeObj[screenDefaultMenuIndex].obj;
        if (menuIndexTextObject!= NULL) {
            char* label=lv_label_get_text(menuIndexTextObject);
            lv_label_set_text(node->nodeData.nodeObj[screenDefaultMenuIndex].obj, menuNumberForDisplay);
            lv_obj_invalidate(menuIndexTextObject);
        }
        else{
            /* Nothing to do, no space to place object */
        }
    }
    else{
        /* Nothing to do, no space to place object */
    }
}

//* This function is called whenever the menu scrolls to the next entry in its list  */

static void moveFocusToSelectedListEntry(lv_group_t *group,nodeDescriptor_t *node, uint8_t indexOfFocusedElement) {
    char smallString[MAXMENUDEPTH]={0};
    if (group==NULL)
        return;  /* No list involved */

    lv_obj_t *focused = lv_group_get_focused(group);
    if (focused==NULL)
        return;  /* No list involved */
    lv_obj_t *parentList = lv_obj_get_parent(focused);
    lv_obj_t * menuTitleField = node->nodeData.nodeObj[screenDefaultTopText].obj;
    if (menuTitleField != NULL) {



        if (node->menuId == LOGINPROCESS) {
            strcpy(smallString,getMenuOrParameterNameFromMenuDefinitions(node->parentNodeId));
        }
        else if ((node->menuId == FIRSTOPERATION) || (node->menuId == ENDOFRUNFIRST)|| (node->menuId == SELECTUSER)) {
           strcpy(smallString,getMenuOrParameterNameFromMenuDefinitions(node->menuId));
        }
        else if (true) {
           strcpy(smallString,getMenuOrParameterNameFromMenuDefinitions(node->menuId));
        }
 //       else if (node->menuId != FIRSTOPERATION) {
        else  {

            lv_obj_t *text;;
            text= lv_obj_get_child(focused,0);

            char * label = lv_label_get_text(text);

            if (node->nodeData.rootScreenType == defaultScreen)
                    strcpy(smallString,getParameterValueAsString(DEVICENAME));
            else if (node->nodeData.menuNodeType == compressedListNode)
                strcpy(smallString,getMenuOrParameterNameFromMenuDefinitions(LISTCONFIGPARAS));

            else
                strcpy(smallString,label);
//            strcpy(smallString,getMenuOrParameterNameFromMenuDefinitions(node->menuId));

                lv_label_set_text(menuTitleField,smallString);
        }
    }

    lv_group_focus_freeze(group,false);  /* TODO DR trials with freeze in timer to avoid ugly scrolling effect on target */
    /* update focused object in current node */
    if (node->nodeData.nodeObj != NULL)
    {
        lv_obj_t *focused_last;
        if (indexOfFocusedElement < lv_obj_get_child_cnt(parentList) && indexOfFocusedElement != 0) {
            focused_last = lv_obj_get_child(parentList, indexOfFocusedElement - 1);
        } else {
            focused_last = lv_obj_get_child(parentList,
                    lv_obj_get_child_cnt(parentList) - 1);
        }

        if (focused->user_data != NULL) {
            lv_obj_t* enSymbol=focused->user_data;
            lv_obj_add_state( enSymbol, LV_STATE_FOCUSED);
           // lv_label_set_text(enSymbol, LV_SYMBOL_NAMUR_UNCHECKED);
        }
        /* bring the selected obj to the center and bypass anim*/
        uint8_t dy = 0;
        uint8_t center = (parentList->coords.y2 - parentList->coords.y1) / 2
                + parentList->coords.y1;
        dy = lv_obj_get_height(focused) * indexOfFocusedElement; //*index;//;(focused->coords.y2-focused->coords.y1)/2;

        int8_t visibleElements =getNumberOfVisibleElements(parentList);

        if ((indexOfFocusedElement >= 3) && visibleElements > 3){
            lv_group_focus_freeze(group,false);
                lv_obj_set_scroll_snap_x(node->nodeData.content, LV_SCROLL_SNAP_CENTER);
                lv_obj_set_scroll_snap_y(node->nodeData.content, LV_SCROLL_SNAP_CENTER);
        }
        else if (indexOfFocusedElement ==0){
            lv_group_get_focused(group);
            lv_obj_scroll_to_y(parentList, dy, 0);
            lv_obj_set_scroll_snap_y(node->nodeData.content, LV_SCROLL_SNAP_START);

        }
        else
            lv_obj_set_scroll_snap_y(node->nodeData.content, LV_SCROLL_SNAP_NONE);

        if (focused_last->user_data != NULL) {
            lv_obj_t* enSymbol=focused_last->user_data;
            lv_obj_clear_state( enSymbol, LV_STATE_FOCUSED);
        }
    }

}

//* This function is called whenever the menu scrolls to the next entry in its list  */

static void updateHeaderInformations(lv_group_t *group) {

    int8_t indexOfFocused;

    nodeDescriptor_t *screenNode = currentScreen;
    assert(screenNode != NULL);

    if (screenNode->nodeData.rootScreenType!=listScreen)
        return; /*

    if (screenNode->nodeData.nodeObj == NULL)
        return; /* no screenobject to write headerinformations to */

    if (group==NULL)
        return;  /* No list involved */
    lv_obj_t *focused = lv_group_get_focused(group);
    if (focused==NULL)
        return;  /* No list involved */

    if (screenNode->nodeData.eventHandler==eventHandlerChooseScreenKey) {
        lv_obj_t *parentList = lv_obj_get_parent(focused);
        indexOfFocused = lv_obj_get_index(parentList);
    }
    else
        indexOfFocused = lv_obj_get_index(focused);

    if (screenNode->nodeData.rootScreenType!=defaultScreen) {

      moveFocusToSelectedListEntry(group,screenNode,indexOfFocused);
    }

}


//* This function is called whenever the menu scrolls to the next entry in its list  */

static void updateHeaderInformationsFromNode(nodeDescriptor_t *node) {

    int8_t indexOfFocused;

    assert(node != NULL);

    if (node->nodeData.rootScreenType!=listScreen)
        return;

    lv_group_t *group = node->nodeData.group;
    if (group==NULL)
        return;  /* No list involved */
    lv_obj_t *focused = lv_group_get_focused(group);
    if (focused==NULL)
        return;  /* No list involved */

    if (node->nodeData.eventHandler==eventHandlerChooseScreenKey) {
        lv_obj_t *parentList = lv_obj_get_parent(focused);
        indexOfFocused = lv_obj_get_index(parentList);
    }
    else
        indexOfFocused = lv_obj_get_index(focused);

    if (node->nodeData.rootScreenType!=defaultScreen) {

      moveFocusToSelectedListEntry(group,node,indexOfFocused);
    }

}
/**
 * Stores a chooselist parameter value. In case of a multiChoose value the bit array is updated
 */
static void setChooseListParameterFromNode(nodeDescriptor_t *node, int8_t value) {
    STR parameterID = node->parentNodeId;
    char temporaryBuffer[SMALLSTRINGSIZE] ={"%s\0"};
    strcpy(temporaryBuffer,"%s\0");
    if (node->nodeData.menuNodeType == multiChooseValuesNode) {
        uint32_t bitArrayValue = atoi(getParameterValueAsString(parameterID));
        if (value == 1)
            bitArrayValue += 1<<node->nodeNavigation.childIndexinParent;
        else
            bitArrayValue -= 1<<node->nodeNavigation.childIndexinParent;
        sprintf(temporaryBuffer,"%li",bitArrayValue);
        setParameterValue(parameterID,temporaryBuffer);
    }
    else
      setParameterChooseListInStorage(parameterID,value);
    updateHeaderInformations(node->nodeData.group);

}
/* This function prepares a menuNode based on the screentype provided and returns it */
nodeDescriptor_t *  prepareParameterScreenFromTemplate(menuNodeType_t nodeType, STR focusedParameterId) {

    int8_t indexOfFocused;
    nodeDescriptor_t * parameterNode;
    nodeDescriptor_t * parentNode;

    parameterNode = findScreenTemplateWithType(nodeType);
    assert(parameterNode!=NULL);
    parameterNode->sourceNode = focusedParameterId;
    parameterNode->menuId = focusedParameterId;
    parameterNode->menuNumberEntry = noNumber;
    parameterNode->nodeNavigation.parentIndex = -1;
//    parentNode = findScreenForNode(defaultScreen);
//    parameterNode->parentNodeId = parentNode->menuId;

    if (parameterNode->nodeData.initScreen != NULL)
        parameterNode->nodeData.initScreen(parameterNode);
    else{
        /* No initializer to be called */
    }
    return parameterNode;
}
/* This function prepares a menuNode with distinguished settings */
static nodeDescriptor_t *  prepareParameterScreen(nodeDescriptor_t * sourceScreen,screenType_t screenType, STR focusedParameterId, STR parentMenuId) {

    nodeDescriptor_t * parameterNode;
    nodeDescriptor_t * parentNode;

    assert(sourceScreen->nodeData.rootScreenType == screenType);
    assert(sourceScreen->parentNodeId==parentMenuId);

    parameterNode = findScreenTemplateWithType(parameterNodeTemplate);
    assert(parameterNode!=NULL);

    parameterNode->sourceNode = focusedParameterId;
    parameterNode->menuId = focusedParameterId;
    parameterNode->menuNumberEntry = sourceScreen->menuNumberEntry;
    parameterNode->nodeData.rootScreenType = screenType;
    parameterNode->sourceNode = focusedParameterId;

    parameterNode->nodeData.menuNodeType = sourceScreen->nodeData.menuNodeType;
    parameterNode->nodeNavigation = sourceScreen->nodeNavigation;
    parameterNode->nodeData.eventHandler = sourceScreen->nodeData.eventHandler;
    parameterNode->nodeData.initScreen = sourceScreen->nodeData.initScreen;
    memcpy(&parameterNode->nodeData.dynamicReadCallBack, &sourceScreen->nodeData.dynamicReadCallBack, sizeof(timerTask_t));
    parameterNode->nodeData.group = sourceScreen->nodeData.group;

    parameterNode->menuIndex = sourceScreen->menuIndex;
    parentNode = findParent(sourceScreen);
    parameterNode->parentNodeId = parentMenuId;

    if (parameterNode->nodeData.initScreen != NULL)
       parameterNode->nodeData.initScreen(parameterNode);
    else{
       /* No initializer to be called */
   }

   if ( parameterNode->nodeData.menuNodeType == passwordEntryNode) {
       parameterNode->sourceNode = PASSWORDENTRYVALUE;
       switch (sourceScreen->menuId) {
       case EXPECTSYSPASSWORD:
           setParameterValueFromInt(TRYTOLOGINUSER,systemUser);
           break;
       case EXPECTAMTBPASSWORD:
           setParameterValueFromInt(TRYTOLOGINUSER,amtbUser);
           break;
       case AMTBUSER:
           setParameterValueFromInt(TRYTOLOGINUSER,amtbUser);
           break;
       case SYSTEMUSER:
           setParameterValueFromInt(TRYTOLOGINUSER,systemUser);
           break;
       case PASSWORDENTRYVALUE:
       case NEWPASSWORDVERIFY:
           /* Trytologin user already stored */
           break;
       case NEWPASSWORDENTRY:
           /* Edit new password*/
           break;

       default:
           assert(0); /* All password dexpected values have to be defined here */
       }
    }
   else {
       /* Nothing to do for other parameter types */
   }

    return parameterNode;
}

static nodeDescriptor_t *  prepareParameterScreenFromNode(nodeDescriptor_t * sourceScreen) {

    return prepareParameterScreen(sourceScreen,sourceScreen->nodeData.rootScreenType,sourceScreen->menuId, sourceScreen->parentNodeId);
}

static void eventHandlerParameterScreen(lv_event_t *e,screenType_t screenType) {

    nodeDescriptor_t *screenNode;
    screenNode = getNodeFromEvent(e);
    STR parentMenuId = screenNode->parentNodeId;
    nodeDescriptor_t * parameterScreen = prepareParameterScreen(screenNode,screenType,screenNode->menuId,parentMenuId);
    activateScreen(parameterScreen);
}

static void eventHandlerParameterTakeOver(lv_event_t *e) {
    nodeDescriptor_t *screenNode;

    screenNode = getNodeFromEvent(e);
    if (screenNode->nodeData.content == NULL){
        eventHandlerListKey(e);
        return;
    }

    if (screenNode->nodeData.rootScreenType == parameterTakeValueScreen)
        /* the edit screen is active */
        eventHandlerParameterTakeOverKey(e);
    else {
        /* trigger to activate the edit screen */
        eventHandlerParameterScreen(e, parameterTakeValueScreen);
        updateMenuIndexString(screenNode);
    }
}

static void eventHandlerMessageScreen(lv_event_t *e) {
    nodeDescriptor_t *screenNode;
    screenNode = getNodeFromEvent(e);
    if (screenNode->nodeData.content == NULL){
        eventHandlerListKey(e);
        return;
    }
}

static void eventHandlerParameterCommon(lv_event_t *e, screenType_t screenType, void (*keyHandler)(lv_event_t *e)) {
    nodeDescriptor_t *screenNode;
    screenNode = getNodeFromEvent(e);
    if (screenNode->nodeData.content == NULL){
        eventHandlerListKey(e);
        return;
    }

    if (screenNode->nodeData.rootScreenType == screenType)
        keyHandler(e);
    else {
        /* trigger to activate the assigned screen */
        eventHandlerParameterScreen(e, screenType);
        updateMenuIndexString(screenNode);
    }
}
static void eventHandlerParameterShowNode(lv_event_t *e) {
    eventHandlerParameterCommon(e,parameterShowScreen,eventHandlerParameterShowNodeKey);
}

static void eventHandlerParameterEditNode(lv_event_t *e) {
    eventHandlerParameterCommon(e,parameterEditScreen,eventHandlerParameterEditorKey);
}

static void eventHandlerParameterEditNodeWithApply(lv_event_t *e) {
    eventHandlerParameterCommon(e,parameterEditScreenWithApply,eventHandlerParameterEditorKey);
}

static void eventHandlerScreenTimeOutToNextNode(lv_timer_t *timer) {
    nodeDescriptor_t *node;
    nodeDescriptor_t *nextNode;
    node = getNodeFromTimer(timer);
    pauseScreenTimer(node);
    if (node->nodeNavigation.nextNodeInFlow > 0) { /* The next node can be any node in the menu */
        nextNode = findNodeWithIndex(node->nodeNavigation.nextNodeInFlow);
    }
    switchToNode(nextNode);
}


static void eventHandlerActionButton(lv_event_t *e) {
    uint32_t keyPressed;
    nodeDescriptor_t *actualNode;
    nodeDescriptor_t *nextNode;
    nodeDescriptor_t *parentNode;

    actualNode = getNodeFromEvent(e);    // loading the menu screen
    keyPressed = eventHandlerEscAndDownKeysAndReturnKeyPressCode(e);
    if (keyPressed == LV_KEY_ENTER) {
        switchToNodeController(actualNode,eventHandlerActionButton);
    }
}
static void eventHandlerParameterShowNodeKey(lv_event_t *e) {
    uint32_t keyPressed;
    nodeDescriptor_t *actualNode;
    nodeDescriptor_t *nextNode;
    nodeDescriptor_t *parentNode;

    actualNode = getNodeFromEvent(e);    // loading the menu screen
    if (actualNode->nodeData.menuNodeType == runParameterEndNodeAction){
    /*call the event for the action button defined for this node */
        if (actualNode->nodeData.eventHandler !=NULL){
            actualNode->nodeData.eventHandler(e);
        }
    }
    else {
        keyPressed = eventHandlerEscAndDownKeysAndReturnKeyPressCode(e);
        if (keyPressed == LV_KEY_ENTER) {
            switchToNodeController(actualNode,eventHandlerParameterShowNodeKey);
        }
    }
}

#define CONTINUEBUTTONINDEX 1
#define TAKEOVERBUTTONINDEX 0

static void eventHandlerParameterTakeOverKey(lv_event_t *e) {
    uint32_t keyPressed;
    nodeDescriptor_t *actualNode;
    nodeDescriptor_t *nextNode;
    nodeDescriptor_t *parentNode;

    lv_obj_t *focused ;

    actualNode = getNodeFromEvent(e);
    uint8_t indexOfFocused = 0;
    keyPressed = eventHandlerEscAndDownKeysAndReturnKeyPressCode(e);
    if (keyPressed == LV_KEY_ENTER) {
         focused = lv_group_get_focused(actualNode->nodeData.group);
         indexOfFocused = lv_obj_get_index(focused);

         if (indexOfFocused > TAKEOVERBUTTONINDEX) { /* Index of continue button */
             switchToNodeController(actualNode,eventHandlerParameterTakeOverKey);
        }
        else{
            char* parameterString = lv_label_get_text(actualNode->nodeData.nodeObj[screenParameterTakeOverValue].obj);
            if (parameterString != NULL) {
                if (true == checkParameterRange(actualNode,parameterString))
                {
                    setParameterValue(actualNode->sourceNode,parameterString);
                }
                else{
                    /* TODO popup out of range  message */
                }
            }
            else{
                /* TODO popup out of range  message */
            }
        }
    }
}


static void removeTrailingCharacters(char* stringToRemoveCharacters, char removeThisCharacter) {
  int8_t charPointer = strlen(stringToRemoveCharacters);
  while (charPointer > 0)
  {
      if (stringToRemoveCharacters[charPointer] == removeThisCharacter)
          stringToRemoveCharacters[charPointer] = ' ';
      charPointer--;
  }
}

uint8_t isKeyPressedLBetweenMilliSeconds(int16_t milliSecondsMin, int16_t milliSecondsMax ){
    uint8_t result = buttonStates.keyIsPressedForMilliSeconds <= milliSecondsMax && buttonStates.keyIsPressedForMilliSeconds >= milliSecondsMin;
    return result;
}

uint8_t isKeyPressedLongerThanMilliSeconds(int16_t milliSeconds){
    uint8_t result = buttonStates.keyIsPressedForMilliSeconds > milliSeconds;
    return result;
}

uint8_t isKeyReleasedLongerThanMilliSeconds(int16_t milliSeconds){
    uint8_t result = buttonStates.keyIsReleasedForMilliSeconds > milliSeconds;
    return result;
}
uint8_t isKeyPressedLessThanMilliSeconds(int16_t milliSeconds){
    uint8_t result = buttonStates.keyIsPressedForMilliSeconds <  milliSeconds;
    return result;
}

/* if a character is within the given range true is returned, otherwise false */
uint8_t isInRange(char actualChar,uint8_t * characterRange) {
    if (characterRange[0] == 0)
        return false;
    else
        return ((actualChar >= characterRange[0]) && (actualChar <= characterRange[1]));
}

static void resetSingleCharacterEditControl() {
    editorControl.editorGroupJustSkipped = false;
}
/* Increases the given character to match into one of the condition strings */
static char replaceWithNextAllowedCharacter( nodeDescriptor_t *node, char actualChar,uint8_t * characterRange1,uint8_t* characterRange2,uint8_t* characterRange3, uint8_t* specialCharacters )
{
    uint8_t specialCharIndex;
    uint8_t skipThisGroup =0;

    assert (characterRange1[0]!=0);  /* the first character range has to be defined */

    if ((editorControl.actualCharSet == NULL) && (actualChar == '-'))
        actualChar = characterRange1[0];      /* First character typed */

    if (isKeyPressedLongerThanMilliSeconds(1800)){
        editorControl.editorGroupJustSkipped = false;
        buttonStates.keyIsPressedForMilliSeconds = 0;
        return editorControl.actualCharSet[0];
    }
    else if (isKeyPressedLongerThanMilliSeconds(800)) { /* skip the range */
        if (editorControl.editorGroupJustSkipped == false){
            skipThisGroup = true;
            lv_label_set_text(
            node->nodeData.nodeObj[screenParamBodyText].obj,"\n-->");
        }
        else  {  /* wait with same character some time after skip */
            return editorControl.actualCharSet[0];
        }
    }
    else{
        lv_label_set_text(node->nodeData.nodeObj[screenParamBodyText].obj,"   ");
        /* normal process of key pressed */
    }

    if (skipThisGroup == false) {
        if (isInRange(actualChar, characterRange1)) {
            editorControl.actualCharSet = characterRange1;
        }
        else if (isInRange(actualChar,characterRange2)) {
            editorControl.actualCharSet = characterRange2;
        }
        else if (isInRange(actualChar, characterRange3)) {
            editorControl.actualCharSet=characterRange3;
        }
        else if (editorControl.actualCharSet == specialCharacters) {

            uint8_t asciiChar = actualChar;
            uint8_t loopEnded = false;
            do {
                specialCharIndex = 0;
                while (specialCharIndex <strlen(specialCharacters)) {
                    if (specialCharacters[specialCharIndex] == asciiChar) {
                        editorControl.actualCharSet=specialCharacters;
                        return asciiChar; /* special character was found */
                    }
                    specialCharIndex++;
                }
                asciiChar++;
                loopEnded = asciiChar == specialCharacters[0];
            } while (loopEnded == false);
            skipThisGroup = true;
           // actualCharSet = characterRange1;
        }
        else{
            skipThisGroup = true;
        }
    }
    if(skipThisGroup && editorControl.actualCharSet) {

        uint8_t * actualCharSet = editorControl.actualCharSet;
        if (editorControl.actualCharSet==characterRange1) {
            if (characterRange2[0] != 0) {
                editorControl.actualCharSet = characterRange2;
            }
            else if (specialCharacters[0]!=0)
                editorControl.actualCharSet = specialCharacters;

        }
        else if (editorControl.actualCharSet==characterRange2) {
            if (characterRange3[0] != 0) {
                editorControl.actualCharSet = characterRange3;
            }
            else if (specialCharacters[0]!=0)
                editorControl.actualCharSet = specialCharacters;
        }
        else if (editorControl.actualCharSet==characterRange3) {
            if (specialCharacters[0] != 0) {
                editorControl.actualCharSet = specialCharacters;
            }
            else
                editorControl.actualCharSet = characterRange1;
        }
        else if (editorControl.actualCharSet==specialCharacters) {
            editorControl.actualCharSet = characterRange1;
        }
        if (editorControl.actualCharSet == actualCharSet)
            editorControl.actualCharSet = characterRange1;
        else {
            /* a statusvalid charset was found otherwise default to the first one */
        }

        editorControl.editorGroupJustSkipped = true;
        return editorControl.actualCharSet[0];
    }

    return actualChar;
}


/* This function returns the index to a block of characters in a string, separated by the separator parameter */
static int8_t findEditBlock(char * string, int8_t indexInString, char separator) {
    int8_t editBlock = 0;
    int8_t index = indexInString;
    if (indexInString >= strlen(string))
        return 0;

    while (indexInString < strlen(string)) {
        if (string[indexInString--] == separator){
            editBlock++;
        }
        else {
                /* Nothing to do */
        }
    }
    return editBlock;
}

/* This function prepares the date/time structure based on the given datestring in format dd.mm.yyyy*/
static struct tm prepareTimeValue(char * string) {
    char smallBuffer[100];
    struct tm timeValue;
    memset(&timeValue,0,sizeof(timeValue));
    sprintf(smallBuffer,"%c%c",string[0],string[1]);
    timeValue.tm_mday = atoi(smallBuffer);

    sprintf(smallBuffer,"%c%c",string[3],string[4]);
    timeValue.tm_mon = atoi(smallBuffer);


    sprintf(smallBuffer,"%c%c%c%c",string[6],string[7],string[8],string[9]);
    timeValue.tm_year = atoi(smallBuffer);
    if (timeValue.tm_year>2100)
        timeValue.tm_year =2022;

    return timeValue;
}

static void eventHandlerParameterEditorDateFieldDownKey(parameterEditorStruc_t *editData,char * editedCharacter) {

    struct tm timeValue;
    char *editString = editData->parameterCurrentEditString;
    nodeDescriptor_t *node = editData->nodeFromEvent;
    char *label = editString;

    char characterUnderCursor = replaceWithNextAllowedCharacter(node,(uint8_t) editedCharacter,"09","","","");
    label[actualEditIndexInButtonArray] = characterUnderCursor;  //* Insert new character into editString */

    timeValue = prepareTimeValue(editString);


	if (timeValue.tm_mday > 31)
		timeValue.tm_mday = 1;
	else if (timeValue.tm_mday <1)
		timeValue.tm_mday = 1;
	if (timeValue.tm_mon > 12 )
		timeValue.tm_mon = 1;
	else if (timeValue.tm_mon < 1 ) /* month was 00 */
			timeValue.tm_mon = 10;

	sprintf(editString,"%02i.%02i.%04i",timeValue.tm_mday ,timeValue.tm_mon ,timeValue.tm_year);
    lv_label_set_text(
            node->nodeData.nodeObj[screenParamCurrentEditString].obj,
            editString);
    initParameterEditButtons(editData->characteristics,editString,node);
}


/* This function returns the next node to display, depending on autopening parent */
nodeDescriptor_t * findNextNode(nodeDescriptor_t * node) {
    nodeDescriptor_t * parentContainingList;
    nodeDescriptor_t * nextNode = NULL;

    parentContainingList = findParent(node);
    if (parentContainingList ->nodeData.group == NULL)
        parentContainingList = findNodeWithIndex(node->nodeNavigation.parentIndex);
    else {
        /* Parent is valid */
    }

    if (isAutoOpening(parentContainingList)) {
        nextNode = findNextChild(node);
        if (nextNode == NULL) {
            nextNode = findParent(parentContainingList);
        }
        else
        {
            /* Node found in same parent*/
        }
    }
    else{
        nextNode = findNextChild(node);
    }
    return nextNode;
}

static uint8_t parameterStorageProcess(parameterEditorStruc_t *editData) {

    if (true == checkParameterRange(editData->nodeFromEvent,editData->parameterCurrentEditString))
    {
        if (editData->characteristics->parameterType == parameterTypeTagNumber)
            removeTrailingCharacters(editData->parameterCurrentEditString,'-');
        setParameterValue(editData->nodeFromEvent->sourceNode,editData->parameterCurrentEditString);

        return true;
    }
    else  /* Edited parameter is out of range */
       return false;
}

static uint8_t passwordCheckProcess(parameterEditorStruc_t *editData) {
    char *editString;
    nodeDescriptor_t *node = editData->nodeFromEvent;
    editString = editData->parameterCurrentEditString;
    if (node->menuId == NEWPASSWORDVERIFY) {/* Accept any password as new */
        if (strcmp(getParameterValueAsString(NEWPASSWORDENTRY),editString) == 0) {
            if (getParameterValueAsInt(TRYTOLOGINUSER) == amtbUser)
                setParameterValue(EXPECTAMTBPASSWORD,editData->parameterCurrentEditString);
            else if (getParameterValueAsInt(TRYTOLOGINUSER) == systemUser)
                setParameterValue(EXPECTSYSPASSWORD,editData->parameterCurrentEditString);
            return true;
        }
        else
            return false;

    }
    else if (node->menuId ==NEWPASSWORDENTRY) {/* Accept any password as new */
        setParameterValue(NEWPASSWORDENTRY,editData->parameterCurrentEditString);
        return true;
    }
    else if (true == checkPasswordValidity(editData->nodeFromEvent,editData->parameterCurrentEditString)) {

        if (getParameterValueAsInt(TRYTOLOGINUSER) == amtbUser) //* Set current User
            setParameterValueFromInt(SELECTUSER,amtbUser);
        else  //* Set system User */
            setParameterValueFromInt(SELECTUSER,systemUser);
        return true;
    }
    else { /* Edited password is out of range */
       return false;
    }
}
static void switchToNodeController(nodeDescriptor_t* actualNode, void* source) {

    nodeDescriptor_t* nextNode;
    nodeDescriptor_t* parentNode = -1;
    uint32_t keyPressed;


    if (source == executeEndNodeSkipFirst) {
        nextNode = findNextNode(actualNode);
        switchToNode(nextNode);
        return;
    }

    else if (source == eventHandlerActionButton) {

        nextNode = findNextChild(actualNode);
        if (nextNode == NULL)
            switchToFirstMenuScreen();
        else {
            /* A child was found */
        }
        switchToNode(nextNode);
        return;
    }

    else if (source == eventHandlerParameterTakeOverKey) {
        nextNode = findNextChild(actualNode);
        switchToNode(nextNode);
        return;
    }


    else if ((source == executeEndNodeSkipFirst)
        || (source == eventHandlerParameterShowNodeKey)) {

        parentNode = findParent(actualNode);
        if (parentNode == NULL) {
            switchToDefaultScreen();
            return;  /* TODO action button */
        }
        if (!isAutoOpening(parentNode)) {
            nextNode = findNextNode(parentNode);
            if (nextNode != NULL)
                parentNode = findParent(nextNode);

            switchToNode(parentNode);
        }
        else {
            nextNode = findNextNode(actualNode);
            switchToNode(nextNode);
        }
        return;
    }
    else if ((source == eventHandlerParameterEditorEnterKey) || (source == eventHandlerLogoScreenTimeOut)) {
        if (actualNode->nodeNavigation.nextNodeInFlow > 0)
            nextNode = findNodeWithIndex(actualNode->nodeNavigation.nextNodeInFlow);
        else {
            if (actualNode->nodeNavigation.nextChildIndex > 0) {
                nextNode = findNodeWithIndex(actualNode->nodeNavigation.nextChildIndex);
            }
            else {
                nextNode = actualNode;
                do {
                    nextNode = findNodeWithIndex(nextNode->nodeNavigation.parentIndex);
                } while (isAutoOpening(nextNode));
            }

            parentNode = findNodeWithIndex(actualNode->nodeNavigation.parentIndex);
            if (!isAutoOpening(parentNode))
                nextNode = parentNode;
        }
        switchToNode(nextNode);
        return;
    }

    else if (source == eventHandlerChooseScreenKey) {
        parentNode = findParent(actualNode);
        nextNode = findNextNode(parentNode);
        if (nextNode == NULL) {  /* No next child => go to parent */
            parentNode = findParent(parentNode);
            switchToNode(parentNode);
            return;
        }
        else {
            if (!isAutoOpening(parentNode)) {
                parentNode = findParent(parentNode);
                switchToNode(parentNode);
            }
            else {
                switchToNode(nextNode);
                return;
            }
        }
    }
    else if (source == executeEndNodeContinueButton) {
        //   nextNode = findParent(actualNode);
        switchToNode(actualNode);
        return;
    }
    else if (source == eventHandlerParameterShowNodeKey) {
        parentNode = findParent(parentNode);
        if (!isAutoOpening(parentNode))
            switchToNode(parentNode);
        else
            nextNode = findNextChild(actualNode);
    }

    else if ((source == eventHandlerListKey)) {
        //LV_KEY_ENTER
        if (isAutoOpening(actualNode)) {
            nextNode = findFirstChildInParent(actualNode);
            switchToNode(nextNode);
        }
        else {
            switchToNode(actualNode);
        }
        return;
    }
    else {
        assert(0);
        return;
    }
}

static void eventHandlerParameterEditorEnterKey(parameterEditorStruc_t *editData) {
    nodeDescriptor_t *node = editData->nodeFromEvent;
    nodeDescriptor_t *nextNode;
    uint8_t validParameter;

    resetSingleCharacterEditControl();

    if (strcmp(editData->textUnderCursor,EDITRIGHTARROW) == 0) {
        switchToNodeController(editData->nodeFromEvent,eventHandlerParameterEditorEnterKey);
        return;
    }
    else if (strcmp(editData->textUnderCursor,EDITSTORECOMMAND) == 0) {
        actualEditIndexInButtonArray++;

        if (editData->nodeFromEvent->nodeData.menuNodeType == passwordEntryNode) {
            pauseScreenTimer(node);
            validParameter = passwordCheckProcess(editData);
            nextNode = findFirstChildInParent(node);
            if (!validParameter)
                nextNode = findNextChild(nextNode);
            else{
                /* Nothing to do */
            }
            showMessageTemporary(nextNode, nextNode->menuId);
            return;
               /* Nothing to do *//* There must be two children for password check, one for valid, one for invalid */
        }
        else {
            validParameter = parameterStorageProcess(editData);
         }
        if (validParameter){
            /*  Keep edited value on screen   */
        }
        else {
            char * parameterString = getParameterValueAsString(editData->nodeFromEvent->sourceNode);
            lv_label_set_text(editData->nodeFromEvent->nodeData.nodeObj[screenParamCurrentEditString].obj,parameterString);
            initParameterEditButtons(editData->characteristics,editData->parameterCurrentEditString,editData->nodeFromEvent);
            actualEditIndexInButtonArray=0;
        }
    }
    else { /* Editor cursor not at the end of the string yet */
        actualEditIndexInButtonArray++;
        if ((strcmp(editData->textUnderNextCursor,".") == 0)){
            /* Skip decimal point and newline character */
            actualEditIndexInButtonArray++;
            /* no action on the last field */
        }
    }
}


static void eventHandlerParameterEditorDownKey(parameterEditorStruc_t * editData) {

    nodeDescriptor_t *actualNode = editData->nodeFromEvent;

    char *editString = editData->parameterCurrentEditString;
    char editStringBeforeKeyApply[MAXEDITSTRINGSIZE];
    strcpy(&editStringBeforeKeyApply,editData->parameterCurrentEditString);

    if (editData->textUnderCursor == NULL)
        return;
    if (strcmp(editData->textUnderCursor,EDITRIGHTARROW) == 0) {
        return; /* No action when cursor is on the right end */
    }
    else if (strcmp(editData->textUnderCursor,EDITLEFTARROW) == 0) {
        return; /* No action when cursor is on the left end */
    }

#if DEBUGFUNCTIONS == 1 // Accelerate testing in debugmode
    if (actualEditIndexInButtonArray ==0)
        actualEditIndexInButtonArray = strlen(editData->parameterCurrentEditString)-1;
#endif

    char msgbuf[2];
    msgbuf[0] = editString[actualEditIndexInButtonArray];
    msgbuf[0]++;
    msgbuf[1] = 0;

    if (strcmp(editData->textUnderCursor,EDITSTORECOMMAND) == 0)
        actualEditIndexInButtonArray = 0;  // Goto first digit
    else {
        switch (editData->characteristics->parameterType) {
            case parameterTypeDate:
                eventHandlerParameterEditorDateFieldDownKey(editData, msgbuf[0]);
                return;
                break;
            case parameterTypeTagNumber:
                msgbuf[0]=replaceWithNextAllowedCharacter(actualNode,msgbuf[0],"AZ","09","az","%&-_");
                 break;

            case parameterTypeInteger:
            case parameterTypeFloat:
                msgbuf[0]=replaceWithNextAllowedCharacter(actualNode,msgbuf[0],"09","","","");

                break;
            case parameterTypeString:
                msgbuf[0]=replaceWithNextAllowedCharacter(actualNode,msgbuf[0],"AZ","az","09","");
                 break;
            default:
                    assert(false);
                break;
        }

        editString[actualEditIndexInButtonArray] = msgbuf[0];  //* Insert new character into editString */
        char * newValueAsString =  getParameterMaxValue(actualNode->sourceNode);
        if ((newValueAsString[0] < editString[0]) && (editData->characteristics->parameterType==parameterTypeFloat))
//            if (false == checkParameterRange(actualNode->sourceNode,parameterCurrentEditString))
         { /* Edited parameter (like mA Simulation Value) is out of range TODO DR maybe there is a cleverer solution */
            editString[0]='0';
        }

        lv_label_set_text(actualNode->nodeData.nodeObj[screenParamCurrentEditString].obj,
                editData->parameterCurrentEditString);

        editorControl.parameterEditStringArray[actualEditIndexInButtonArray + 1][0] =
                editString[actualEditIndexInButtonArray];
        editorControl.parameterEditStringArray[actualEditIndexInButtonArray + 1][1] = 0; /* End of string */

        initParameterEditButtons(editData->characteristics,editData->parameterCurrentEditString,actualNode);
    }
}


static void eventHandlerParameterEditorKey(lv_event_t *e) {

    uint32_t keyPressed;
    parameterEditorStruc_t editData;

    editData.event = e;

    editData.nodeFromEvent = getNodeFromEvent(e);
    assert(editData.nodeFromEvent!=NULL);

    editData.characteristics = getParameterCharacteristics(editData.nodeFromEvent->sourceNode);
    assert(editData.characteristics!=NULL);

    editData.lvglString = editData.nodeFromEvent->nodeData.nodeObj[screenParamCurrentEditString].obj;
    if (editData.lvglString !=NULL)
        editData.parameterCurrentEditString = lv_label_get_text(editData.lvglString);

    lv_obj_t *btnm = editData.nodeFromEvent->nodeData.nodeObj[screenParamCurrentEditButtons].obj;
    editData.textUnderCursor = lv_btnmatrix_get_btn_text(btnm, actualEditIndexInButtonArray+1);

    if (editData.textUnderCursor == NULL )
        return;

    keyPressed = getEventKey(e);

    switch (keyPressed) {
        case LV_KEY_ESC:
            editData.textUnderNextCursor = lv_btnmatrix_get_btn_text(btnm, actualEditIndexInButtonArray);
            eventHandlerParameterEditorEscKey(&editData);
            break;
        case LV_KEY_DOWN:
        	eventHandlerParameterEditorDownKey(&editData);
            break;
        case LV_KEY_ENTER:
            editData.textUnderNextCursor = lv_btnmatrix_get_btn_text(btnm, actualEditIndexInButtonArray+2);
            eventHandlerParameterEditorEnterKey(&editData);
            break;
        default:
            /* Unknown key */
        	break;
    }
}

static void eventHandlerParameterEditorEscKey(parameterEditorStruc_t * editData) {

    if (actualEditIndexInButtonArray < 0) {
        eventHandlerEscAndDownKeysAndReturnKeyPressCode(editData->event);
        return;
    }
    resetSingleCharacterEditControl();
    actualEditIndexInButtonArray--;
    if ((strcmp(editData->textUnderNextCursor,".") == 0)){
        /* Skip decimal point and newline character */
        actualEditIndexInButtonArray--;
    }
}

static void initTopScreen(nodeDescriptor_t * node){
    uint8_t widthOfUnitOnOneLineScreen = 30;

    if (node->nodeData.topScreen == NULL) {

        node->nodeData.topScreen  = lv_obj_create(lcdScreen);
        if (node->nodeData.rootScreenType == defaultScreen)
            lv_obj_set_size(node->nodeData.topScreen , lv_obj_get_width(lcdScreen)-widthOfUnitOnOneLineScreen,
                    TOP_MENU_HEIGHT);
        else
            lv_obj_set_size(node->nodeData.topScreen , lv_obj_get_width(lcdScreen),
                    TOP_MENU_HEIGHT);
        lv_obj_add_style(node->nodeData.topScreen , &style_default, 0);
        lv_obj_align(node->nodeData.topScreen , LV_ALIGN_TOP_LEFT, 0, 0);
        lv_obj_set_scrollbar_mode(node->nodeData.topScreen , LV_SCROLLBAR_MODE_OFF);
        lv_obj_update_layout(node->nodeData.topScreen );
    }
}

static lv_obj_t *  insertScreenListItem(nodeDescriptor_t *parentItem,nodeDescriptor_t *listItem){
    lv_obj_t * newButton = NULL;
    int8_t visible = 0;
    char tempString[STRING_CONVERSION_BUFFER_SIZE];
    accessright_t access;
    uint16_t childIndex = 0;
    STR thisChildId;
    void (*eventHandler)(lv_event_t *e);
    lv_obj_t * list = parentItem->nodeData.content;
    nodeDescriptor_t *listItemGeneric;
    if (list == NULL)
      return NULL;

    visible =  isVisibleDependentOnSetting(listItem->menuId,listItem->nodeNavigation.childIndexinParent);
    visible |= listItem->nodeData.menuNodeType == multiChooseValuesNode;
    access = getAccessRightForLoggedinUser(listItem->menuId);
    if (visible && (access!= noAccess)){

        thisChildId = listItem->menuId; //+screenNodeChild->nodeNavigation.childIndexinParent;
        listItemGeneric = listItem;
        eventHandler = listItem->nodeData.eventHandler;

        if (parentItem->nodeData.menuNodeType == compressedListNode)  {
            eventHandler = parentItem->nodeData.eventHandler;
            if (isAutoOpening(listItem)) {
               listItemGeneric = findFirstChildInParent(listItem);

            }
            else {
              /* Nothing to do */
            }
           sprintf(tempString, "%s:\n (%s)", getMenuOrParameterNameFromMenuDefinitions(listItemGeneric->menuId),getParameterValueAsString(listItemGeneric->menuId));
        }
        else if (isArrayMember(thisChildId, CONFIGURATIONX))  /* Array members provide their configured names as label (configurations, mediums) */
            sprintf(tempString, "%s ", temporaryInsimulatorOnlyConfigurationSetting[thisChildId-CONFIGURATIONX].configName);
        else if (isArrayMember(thisChildId, ARCHIVEX))  /* Array members provide their configured names as label (configurations, mediums) */
            sprintf(tempString, "%s ", temporaryInsimulatorOnlyArchiveSetting[thisChildId-ARCHIVEX].mediumName);
        else
            sprintf(tempString, "%s ", getMenuOrParameterNameFromMenuDefinitions(thisChildId));

        /*create a button */

        newButton =  lv_list_add_btn(list, 0,tempString);
       lv_obj_add_style(newButton, &style_list_std, 0);
       lv_obj_add_style(newButton, &style_list_focus, LV_STATE_FOCUSED);
        lv_group_add_obj(parentItem->nodeData.group, newButton);

         /*  if node has an eventhandler add this to the button */
        if (eventHandler != NULL) {
                lv_obj_add_event_cb(newButton,eventHandler,
                       LV_EVENT_KEY, listItem);
        }
    }
    return newButton;
}

static void fillMenuListItemsForMenu(lv_obj_t *list,nodeDescriptor_t *parentNode){
    nodeDescriptor_t *screenNodeChild;
    nodeDescriptor_t *insertedSpecialNode;
    nodeDescriptor_t *nextNode;
    nodeDescriptor_t cloneOfFirstChild;;
    int8_t focusedIndexInVisibleElements ;
    int8_t dependentMarkState = 0;
    uint16_t indexInList = 0;


    if (list == NULL)
        return; /* No list found to fill */

    screenNodeChild = findFirstChildInParent(parentNode);
    if (screenNodeChild == NULL)
        return; /* No children found to fill into list */

    if (screenNodeChild->nodeNavigation.parentIndex != parentNode->menuIndex) {
        screenNodeChild->nodeNavigation.parentIndex = parentNode->menuIndex;
    }
        /* in this case a subnode is contained in several other nodes as a copy. */
        /* This means that the parentIndex may be changed to the actual required menu */
        /* This is an allowed case, but parentIndex should not be changed for other uses */

    /*  Insert temporary node like  the continue button if we have multiple choice menu */
    if (screenNodeChild->nodeData.menuNodeType == multiChooseValuesNode) {

        memcpy(&cloneOfFirstChild,screenNodeChild,sizeof(nodeDescriptor_t));
        insertedSpecialNode = &cloneOfFirstChild;
        insertedSpecialNode  = prepareParameterScreen(insertedSpecialNode,listScreen,CONTINUETONEXT,parentNode->menuId);
        insertedSpecialNode->menuId = CONTINUETONEXT;
        insertedSpecialNode->nodeData.rootScreenType = listScreen;
        insertedSpecialNode->nodeData.eventHandler=getEventForParameterEndNode(CONTINUETONEXT);
        insertScreenListItem(parentNode,insertedSpecialNode);
        indexInList++;
    }
    else {
        /* No continue key to be inserted */
    }

    if (screenNodeChild->nodeData.menuNodeType == singleChooseValuesNode) {
        focusedIndexInVisibleElements=getParameterChooseListFromStorage(parentNode->menuId)-1;
    }
    else {
        focusedIndexInVisibleElements=0;  /* more than one or no item is focused */
    }

    // subsequent menues are loaded with the same parentindex
    while (screenNodeChild != NULL) {
        lv_obj_t * listEntryButton = insertScreenListItem(parentNode,screenNodeChild);
        if (listEntryButton != NULL) {
            if ((screenNodeChild->nodeData.menuNodeType==multiChooseValuesNode)) {
                dependentMarkState = getParameterValueWithDependence(parentNode->menuId, screenNodeChild->nodeData.enumValue);
                insertSingleCheckSymbolIntoList(listEntryButton,dependentMarkState);
            }
            else if ((screenNodeChild->nodeData.menuNodeType==singleChooseValuesNode) && (focusedIndexInVisibleElements== screenNodeChild->nodeNavigation.childIndexinParent)) {
                dependentMarkState = getParameterValueWithDependence(screenNodeChild->menuId,indexInList);
                insertSingleCheckSymbolIntoList(listEntryButton,dependentMarkState);
            }
            else {
                /* No chooselist shown so no preset actual selected value */
            }

            indexInList++;
        }
        nextNode = findNextChild(screenNodeChild);

        if (nextNode == NULL)
            break;
        else {
   //         screenNodeChild->nodeNavigation.nextNodeIndex = nextNode->menuIndex;
            screenNodeChild = nextNode;;
        }
    }
}

static lv_obj_t * findNextVisibleElement(lv_obj_t * list) {
    int8_t index = 0;
    lv_obj_t * listElement;

    do {
        listElement=lv_obj_get_child(list, index++);
        if (listElement !=NULL) {
            if (!lv_obj_has_flag(listElement, LV_OBJ_FLAG_HIDDEN))
                return listElement;
        }
    }while (listElement !=NULL);

}


static uint8_t * getNumberOfVisibleElements(lv_obj_t * list) {
    int8_t index = 0;
    int8_t counter = 0;
    lv_obj_t * listElement;

    do {
        listElement=lv_obj_get_child(list, index++);
        if (listElement==NULL)
            return counter;
        else if (!lv_obj_has_flag(listElement, LV_OBJ_FLAG_HIDDEN))
            counter++;
    }while ( listElement !=NULL);

}


static lv_obj_t * fillMenuListScreen(nodeDescriptor_t *requestedNode, uint8_t focusThisIndex) {
    nodeDescriptor_t * parentNode = NULL;

    assert(requestedNode != NULL);
    /* Erase actual screen */


    lv_res_t initScreenResult = initScreenArea(requestedNode);
    if (initScreenResult != LV_RES_OK)
        return NULL;

    parentNode = findNodeWithIndex(requestedNode->nodeNavigation.parentIndex);
    if ((parentNode != NULL) && (parentNode->nodeData.rootScreenType != defaultScreen)) {
        if (parentNode->nodeData.menuNodeType == listNodeAllChildsAutoOpen) /* listChildAutoOpens is not inherited */
        { /* inherit auto open function in case of a list */
            requestedNode->nodeData.menuNodeType = parentNode->nodeData.menuNodeType;
        }
        else {
            /* Nothing to do */
        }
    }
    else {
        /* Nothing to do */
    }


 //   lv_obj_add_flag(requestedNode->nodeData.content,LV_OBJ_FLAG_HIDDEN);
    requestedNode->sourceNode=requestedNode->menuId;
    showHeaderInformation(requestedNode);
    drawLine(requestedNode->nodeData.nodeObj[screenDefaultTopLine].obj, requestedNode->nodeData.topScreen,
    defaultScreenLine1, 0, 10, 130, 10);
    lv_obj_t * list = requestedNode->nodeData.content;

    fillMenuListItemsForMenu(list,requestedNode);

    lv_obj_t * focusedObj = lv_obj_get_child(list, focusThisIndex);
    if (focusedObj==NULL)
       focusedObj = lv_obj_get_child(list, 0); /* Focus on first element if no child is selected*/
    else if (lv_obj_has_flag(focusedObj, LV_OBJ_FLAG_HIDDEN))
       focusedObj = findNextVisibleElement(list);
    else {
        /* Nothing to do */
    }
    lv_group_focus_obj(focusedObj);

    lv_obj_invalidate(list);
    lv_group_set_focus_cb(requestedNode->nodeData.group, updateHeaderInformations);

}

static uint32_t getEventKey(lv_event_t *e) {
    uint32_t * keyFromEventAdress;
    uint32_t  key;
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_KEY) {
        keyFromEventAdress = e->param;
        key = *keyFromEventAdress;
       return key;
    }
    else
        return 0;
}

static void eventHandlerDefaultScreenNextKey() {
    switchToFirstMenuScreen();
}

/* This function processes the event when the enter key is pressed in the default screen */
static void eventHandlerDefaultScreenKeyPressed(lv_event_t *e) {
    nodeDescriptor_t *screenNode;
    int currentDisplayLines;
    uint32_t keyPressed = getEventKey(e);
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_KEY) {
        if (keyPressed == LV_KEY_DOWN) {
            screenNode = getNodeFromEvent(e);
   //         eraseNodeContent(screenNode);


            currentDisplayLines = atoi(getParameterValueAsString(DISPLAY)) + 1;
            if (currentDisplayLines > MAX_NUMBER_OF_DISPLAYED_MEASVALUES)
                currentDisplayLines = 1;
            setParameterValueFromInt(DISPLAY,currentDisplayLines);
//            initDisplayLineLayout(screenNode,currentDisplayLines);

            switchToDefaultScreen();
        }
        else if (keyPressed == LV_KEY_ENTER) {
            eventHandlerDefaultScreenNextKey();
        }
        else if (keyPressed == LV_KEY_ESC) {
            if (isKeyPressedLongerThanMilliSeconds(3000))
                setParameterValueFromInt(SELECTUSER,publicUser);
        }
        else {
            /* No key to handle here */
        }
    }
}

void executeEndNodeApplyConfig(lv_event_t *e) {
    nodeDescriptor_t *screenNode;
    nodeDescriptor_t *nextNode;
    screenNode = getNodeFromEvent(e);    // loading the menu screen
    uint8_t editedConfig = getParameterValueAsInt(EDITEDCONFIG);
    setParameterValueFromInt(ACTIVECONFIG,editedConfig);

    nextNode = findNodeWithIndex(screenNode->nodeNavigation.firstChildIndex);
    switchToNode(nextNode);
}

void executeEndNodeDeleteConfigurationOrMedium(lv_timer_t *e) {
    nodeDescriptor_t *nextNode;
    nodeDescriptor_t *node;
    nodeDescriptor_t *parentNode;
    uint8_t editedItem;
    uint8_t activeItem;
    STR repositoryAlias;
    STR nameForNewItem;
    uint8_t * validPointer;
    char* namePointer;

    node = getNodeFromTimer(e);
    assert(node->menuId == EXECUTEDELETE);

    parentNode = findNodeWithIndex(node->nodeNavigation.parentIndex);
    repositoryAlias = parentNode->parentNodeId;

    switch (repositoryAlias) {
        case DELETECONFIG:
            editedItem = getParameterValueAsInt(EDITEDCONFIG);
            activeItem = getParameterValueAsInt(ACTIVECONFIG);
            validPointer = &temporaryInsimulatorOnlyConfigurationSetting[editedItem].status;
            namePointer = &temporaryInsimulatorOnlyConfigurationSetting[editedItem].configName;
            nameForNewItem = NAMEFORNEWCONFIG;
            break;
        case MEDIUMDELETE:
            editedItem = getParameterValueAsInt(EDITEDARCHIVE);
            activeItem = -1; /* not relevant for archive */
            validPointer = &temporaryInsimulatorOnlyArchiveSetting[editedItem].status;
            namePointer = &temporaryInsimulatorOnlyArchiveSetting[editedItem].mediumName;
            nameForNewItem = NAMEFORNEWMEDIUM;
            break;
        default:
            break;
    }
    if ((editedItem == 0) && (repositoryAlias == DELETECONFIG)) {  /* Can't delete the first configuration */
        nextNode = findNodeWithIndex(node->nodeNavigation.nextNodeInFlow);
        showMessageTemporary(node, NODELETEFIRST);
        return;
    }
    if (editedItem != activeItem) {
        nextNode = findNodeWithIndex(node->nodeNavigation.nextNodeInFlow);
        showMessageTemporary(node, node->menuId);
        *validPointer = arrayVisibleDefaultName;
        strcpy(namePointer ,getMenuOrParameterNameFromMenuDefinitions(nameForNewItem));
        return;
    }
    else {
        nextNode = findNextChildWithCondition(parentNode, parameterShowNodeNotMatching);
        nextNode = findNodeWithIndex(nextNode->nodeNavigation.nextNodeInFlow);
    }
    if(nextNode == NULL)
        switchToDefaultScreen();
    else
        switchToNode(nextNode);
}

static int8_t getIndexOfEmptyConfiguration() {
    uint8_t index=0; /* skip first configuration */
    do {
        if (temporaryInsimulatorOnlyConfigurationSetting[index].status == arrayVisibleDefaultName)
           return index;
        index++;
    } while (index < NUMBER_OF_NEWCONFIGURATIONS);
    return -1;
}

static int8_t getIndexOfEmptyMedium() {
    uint8_t index=0; /* skip first configuration */
    do {
        if (temporaryInsimulatorOnlyArchiveSetting[index].status == arrayVisibleDefaultName)
           return index;
        index++;
    } while (index < NUMBER_OF_MEDIUMS);
    return -1;
}

static copyResult_t copyConfiguration(nodeDescriptor_t *screenNode) {
    char buffer[SMALLSTRINGSIZE];
    int8_t index;

    index = getIndexOfEmptyConfiguration();

    if ((index >=0) && (index != configurationInFocus)) /* A empty configuration is available, copy the focused selewction into this */
    {
        memcpy(&temporaryInsimulatorOnlyConfigurationSetting[index],&temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus],sizeof(temporaryInsimulatorOnlyConfigurationSetting_t));
        sprintf(buffer,"%s(%01i)",temporaryInsimulatorOnlyConfigurationSetting[configurationInFocus].configName,index);
        strcpy(temporaryInsimulatorOnlyConfigurationSetting[index].configName,buffer);

        if (index < NUMBER_OF_NEWCONFIGURATIONS-1)
            temporaryInsimulatorOnlyConfigurationSetting[index+1].status = arrayVisibleDefaultName;
        else {
            /* No more configuraitons possible */
        }
        return resultCopied;
    }
    else
        return resultNotCopied;
}

static uint8_t copyMedium(nodeDescriptor_t *screenNode) {
    char buffer[SMALLSTRINGSIZE];
    int8_t index=0;

    index=getIndexOfEmptyMedium();

    if ((index >=0) && (index != mediumInFocus)) /* A empty configuration is available, copy the focused selewction into this */
     {
        memcpy(&temporaryInsimulatorOnlyArchiveSetting[index],&temporaryInsimulatorOnlyArchiveSetting[configurationInFocus],sizeof(temporaryInsimulatorOnlyConfigurationSetting_t));
        sprintf(buffer,"%s(%01i)",temporaryInsimulatorOnlyArchiveSetting[configurationInFocus].mediumName,index);
        strcpy(temporaryInsimulatorOnlyArchiveSetting[index].mediumName,buffer);

        if (index < NUMBER_OF_MEDIUMS)
            temporaryInsimulatorOnlyArchiveSetting[index+1].status = arrayVisibleDefaultName;
        else {
            /* No more medium possible */
        }

    }
}

void executeEndNodeCopyConfiguration(lv_event_t *e) {
    char buffer[SMALLSTRINGSIZE];
    nodeDescriptor_t *screenNode;
    screenNode = getNodeFromEvent(e);    // loading the menu screen
    if (copyConfiguration(screenNode) == resultCopied)
        showMessageTemporary(screenNode,CONFIGCOPIED);
    else
        showMessageTemporary(screenNode,CONFIGNOTCOPIED);

}

/* This function processes canceling first run operation  */
void executeEndNodeSkipFirst(lv_timer_t *e) {

    nodeDescriptor_t *actualNode;
    nodeDescriptor_t *nextNode = NULL;

    actualNode = getNodeFromKeyEventOrTimer(e);    // loading the menu screen
    if (actualNode->menuId == 0)
        return;
    assert(actualNode->menuId == SKIPFIRSTOPERATION);

    setParameterValue(RUNFIRSTOPERATION,"0");  /* Only for simulator */

    switchToDefaultScreen();
}

/* This function processes the special list entry to continue to the next menu  */
void executeEndNodeContinueButton(lv_event_t *e) {
    nodeDescriptor_t *nextNode;
    nodeDescriptor_t *node;
    nodeDescriptor_t *parentContainingList;

    uint32_t keyPressed;

    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_KEY) {
        return;
    }

    keyPressed = eventHandlerEscAndDownKeysAndReturnKeyPressCode(e);
    if (keyPressed == LV_KEY_ENTER)
    {
        node = getNodeFromEvent(e);    // loading the menu screen
        assert(node->menuId == CONTINUETONEXT);
        if (isChooseListNode(node))
            nextNode=findParent(node);

            nextNode=findParent(nextNode);
     // maybe with autoopen ?    nextNode=findNextChild(nextNode);
       switchToNode(nextNode);
      //  switchToNodeController(nextNode,executeEndNodeContinueButton);
    }
    else {
        /* All keys processed */
    }
}

void executeEndNodeSaveAbort(lv_timer_t *e) {
    nodeDescriptor_t *screenNode;
    nodeDescriptor_t *nextNode;
     screenNode = getNodeFromTimer(e);

     assert(screenNode->menuId == SAVEABORT);

     setParameterValue(RUNFIRSTOPERATION,"0");

     nextNode = prepareParameterScreenFromTemplate(parameterShowNode,STOREDINFO);
     nextNode->sourceNode = NOTSTOREDVALUELABEL;
     assert(nextNode->nodeData.nodeObj[screenParamBodyText].obj != NULL);
     addTimerTaskToNode(nextNode, requestParameterFromStorageAndFillDynamicFields,
            SCREEN_FUNCTION_CALLBACK_PERIOD, -1);
     activateScreen(nextNode);

}

void executeAMTBReset(lv_timer_t *e) {
    nodeDescriptor_t * actualNode = getNodeFromTimer(e);
    initDeviceConfigurationAndArchiveArrays();
    showMessage(actualNode,AMTBRESET);
}

void executeFactoryReset(lv_timer_t *e) {
    nodeDescriptor_t * actualNode = getNodeFromEvent(e);
    initDeviceConfigurationAndArchiveArrays();
    showMessage(actualNode,FACTORYRESET);
}

void executeEndNodeMissingActionPoint(lv_event_t *e) {
    nodeDescriptor_t * actualNode = getNodeFromEvent(e);
    showMessage(actualNode,NOTSTOREDVALUELABEL);
}

static nodeDescriptor_t * prepareShowMessage(nodeDescriptor_t *actualNode, STR messageFromStringTable) {
    nodeDescriptor_t *nextNode;
    nodeDescriptor_t *parent;
    nextNode = prepareParameterScreenFromTemplate(messageScreenNode, messageFromStringTable);
    nextNode->sourceNode = messageFromStringTable;
    nextNode->nodeNavigation = actualNode->nodeNavigation;
    assert(nextNode->nodeData.nodeObj[screenParamBodyText].obj != NULL);
     return nextNode;
}
static void showMessageTemporary(nodeDescriptor_t *actualNode, STR messageFromStringTable) {
    nodeDescriptor_t *nextNode;
    pauseScreenTimer(actualNode);
    nextNode = prepareShowMessage(actualNode,messageFromStringTable);
    nextNode->nodeData.eventHandler = eventHandlerScreenTimeOutToNextNode;
    nextNode->nodeNavigation.nextNodeInFlow = actualNode->nodeNavigation.nextNodeInFlow;

    addTimerTaskToNode(nextNode, fillSimpleInfoScreenAndContinue,
            SCREEN_FUNCTION_CALLBACK_PERIOD, -1);

        createTimerTask(nextNode);

}

static void showMessage(nodeDescriptor_t *actualNode, STR messageFromStringTable) {
    nodeDescriptor_t *nextNode;
    nextNode = prepareShowMessage(actualNode,messageFromStringTable);
    nextNode->nodeData.eventHandler = eventHandlerActionButton;
    addTimerTaskToNode(nextNode, fillSimpleInfoScreen,
           SCREEN_FUNCTION_CALLBACK_PERIOD, 1);
    activateScreen(nextNode);
}

void executeEndNodeSaveFirstRun(lv_event_t *e) {
    nodeDescriptor_t *actualNode;

    actualNode = getNodeFromEvent(e);
    assert(actualNode->menuId == SAVEFIRSTCONFIGCONFIRM);
    setParameterValue(RUNFIRSTOPERATION,"0");

    showMessageTemporary(actualNode,FIRSTCONFIGSTORED);
}

static void * getEventForParameterEndNode(STR parameterId){
    uint8_t index = 0;
    while (index < sizeOfParameterEndNodeActions) {
        if (parameterEndNodeActions[index].chooseListParameter == parameterId)
            return parameterEndNodeActions[index].parameterEndNodeAction;
        else {
            /* check next defined item */
        }
        index ++;
    }
     /* Definition is missing, inform developer */
    return &executeEndNodeMissingActionPoint;
}

static nodeDescriptor_t * getNodeFromKeyEventOrTimer(lv_event_t *e) {
    nodeDescriptor_t *node;
    if (e->code == LV_EVENT_KEY)
        node = getNodeFromEvent(e);
    else
        node = getNodeFromTimer(e);
    return node;
}



static void eventHandlerParameterEndNode(lv_event_t *e) {
    nodeDescriptor_t *screenNode;
    uint32_t keyPressed;
    void (*eventHandler)(lv_event_t *e);

    screenNode = getNodeFromEvent(e);
    keyPressed = eventHandlerEscAndDownKeysAndReturnKeyPressCode(e);

    if (keyPressed == LV_KEY_ENTER)
    {
        eventHandler = getEventForParameterEndNode(screenNode->menuId);
        if (eventHandler == NULL)
            executeEndNodeMissingActionPoint(e);
        else {
            /* eventHandler was found in Event table For Parameter EndNode */
        }
        eventHandler(e);
    }
}

int8_t isFirstSetup(nodeDescriptor_t *actualNode) {
    nodeDescriptor_t *node;
    node = actualNode;
    while (node != NULL) {
        if (node->menuId == RUNFIRSTOPERATION)
            return true;
        node = findNodeWithIndex(node->nodeNavigation.parentIndex);
    }
    return false;
}

int8_t isCompressedList(nodeDescriptor_t *node) {
    uint8_t result;
    result = node->nodeData.menuNodeType == compressedListNode;
    return result;
}

int8_t isLastChild(nodeDescriptor_t *actualNode) {
    uint8_t result;
    result = actualNode->nodeNavigation.nextChildIndex == 0;
    return result;
}

static int8_t isChooseListNode(nodeDescriptor_t *node) {
  return ((node->nodeData.menuNodeType == singleChooseValuesNode) || (node->nodeData.menuNodeType == multiChooseValuesNode));
}

/* This function processes the event when the enter key is pressed in the parameter screen */
static uint32_t eventHandlerEscAndDownKeysAndReturnKeyPressCode(lv_event_t *e) {

    nodeDescriptor_t *actualNode;
    nodeDescriptor_t *parentContainingList;
    nodeDescriptor_t * nextNode;
    uint32_t keyPressed;
    nodeDescriptor_t * parentNode;

    lv_obj_t *focused ;
    uint8_t indexOfFocused = 0;

    lv_event_code_t code = lv_event_get_code(e);

    if (code != LV_EVENT_KEY)
        return 0;

    actualNode = getNodeFromEvent(e);    // loading the menu screen
    keyPressed = getEventKey(e);
    parentContainingList  = findNodeWithId(actualNode->parentNodeId); /* works except second config apply */
    parentContainingList  = currentScreen;              /* if buttons are in a sequence above instruction does not work TODO */

    if (keyPressed == LV_KEY_DOWN)
    {
        if (parentContainingList->nodeData.group != NULL) {// Focus to next item if it is a list
            if (isKeyPressedLongerThanMilliSeconds(300))
                lv_group_focus_prev(parentContainingList->nodeData.group);
            else
                lv_group_focus_next(parentContainingList->nodeData.group);
        }

        else if (actualNode->nodeData.group != NULL) { // Takeover Screen
                 lv_group_focus_next(actualNode->nodeData.group);
             focused = lv_group_get_focused(actualNode->nodeData.group);
             indexOfFocused = lv_obj_get_index(focused);
            if (indexOfFocused >= 2)
                lv_group_focus_next(actualNode->nodeData.group);
        }

    }
    if (keyPressed == LV_KEY_ESC){
        //ESC
        nextNode = parentContainingList;
        if (isChooseListNode(nextNode))
          assert(0); //  nextNode = findNodeWithIndex(actualNode->nodeNavigation.parentIndex);

        if (nextNode->nodeNavigation.nextNodeInFlow > 0)
            nextNode = findNodeWithIndex(nextNode->nodeNavigation.nextNodeInFlow);
        else {
            if (isFirstSetup(nextNode)) {
                if (nextNode->nodeNavigation.previousChildIndex > 0)
                    nextNode = findNodeWithIndex(nextNode->nodeNavigation.previousChildIndex);
                else {
                    nextNode = findNodeWithIndex(nextNode->nodeNavigation.parentIndex);
                    if (isAutoOpening(nextNode))
                        nextNode = findNodeWithIndex(nextNode->nodeNavigation.parentIndex);
                }
            }
            else {
                nextNode = findNodeWithIndex(nextNode->nodeNavigation.parentIndex);
                if (nextNode == NULL)
                    return keyPressed;
                else if (isAutoOpening(nextNode))
                    nextNode = findNodeWithIndex(nextNode->nodeNavigation.parentIndex);
                /* else nothing to do */
            }

        }

        assert(nextNode != NULL);
        switchToNode(nextNode);
    }
    return keyPressed;
}

/* This function processes the event when the enter key is pressed in the parameter screen */
static void eventHandlerChooseScreenKey(lv_event_t *e) {

    nodeDescriptor_t *screenNode;
    nodeDescriptor_t *parentContainingList;
    uint32_t keyPressed;
    int32_t previousParameterValue;
    keyPressed = eventHandlerEscAndDownKeysAndReturnKeyPressCode(e);

    if (keyPressed == LV_KEY_ENTER)
    {
        screenNode = getNodeFromEvent(e);    // loading the menu screen
        parentContainingList = findParent(screenNode);

        /* Unmark previous chooselist entry and mark the selected */
        previousParameterValue = getParameterChooseListFromStorage(screenNode->parentNodeId);

        lv_obj_t *previousfocused = lv_obj_get_child(parentContainingList->nodeData.content,previousParameterValue);
        if (screenNode->nodeData.menuNodeType == singleChooseValuesNode){
           deactivateCheckSymbolInList(previousfocused);  /* Activation will be on loading new screen */
           lv_obj_t *focused = lv_group_get_focused(parentContainingList->nodeData.group);
           int8_t checkMarkSet = insertSingleCheckSymbolIntoList(focused,1);
           setChooseListParameterFromNode(screenNode,screenNode->nodeData.enumValue);
           switchToNodeController(screenNode,eventHandlerChooseScreenKey);

        }
        else if (screenNode->nodeData.menuNodeType == multiChooseValuesNode){

            lv_obj_t *focused = lv_group_get_focused(parentContainingList->nodeData.group);
            int8_t checkMarkSet = insertSingleCheckSymbolIntoList(focused,1);
            setChooseListParameterFromNode(screenNode,checkMarkSet);

        }
        else{
            /* Nothing to do */
        }

    }
}

/* This function returns true if the string id is a unit definition */
static uint8_t isUnitDefinition(STR menuId) {
    return ((UNITSDEFINITIONSTART < menuId) && (menuId < UNITSDEFINITIONSEND));
}


/* This function returns true if a node opens its children automatically when displayed */
static uint8_t isAutoOpening(nodeDescriptor_t * node) {
    return ((node->nodeData.menuNodeType == listNodeAllChildsAutoOpen) ||
            (node->nodeData.menuNodeType == listChildAutoOpens) ||
            (node->nodeData.menuNodeType == listChildAutoOpensArray));
}


/* This function processes the event when a  key is pressed  */
static void eventHandlerCompressedList(lv_event_t *e) {
    nodeDescriptor_t *actualNode;
    nodeDescriptor_t *parentNode;
    nodeDescriptor_t *nextNode;
    uint32_t keyPressed;

    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_KEY) {
        return;
    }
    keyPressed = getEventKey(e);
    if ((keyPressed == LV_KEY_ENTER) || (keyPressed == LV_KEY_ESC)) {
        actualNode = getNodeFromEvent(e);
        parentNode = findNodeWithIndex(actualNode->nodeNavigation.parentIndex);
        parentNode = findNodeWithIndex(parentNode->nodeNavigation.parentIndex);
        if (parentNode->nodeNavigation.nextNodeInFlow > 0)
            nextNode = findNodeWithIndex(parentNode->nodeNavigation.nextNodeInFlow);
        else
            nextNode = parentNode;
         switchToNode(nextNode);
    }
    else
       eventHandlerEscAndDownKeysAndReturnKeyPressCode(e);
}

/* This function processes the event when the enter key is pressed  */
static void eventHandlerListKey(lv_event_t *e) {
    nodeDescriptor_t *actualNode;
    nodeDescriptor_t *parentNode;
    nodeDescriptor_t *nextNode;
    uint32_t keyPressed;
    uint8_t arraySelector;

    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_KEY) {
        return;
    }
    actualNode = getNodeFromEvent(e);
        keyPressed = eventHandlerEscAndDownKeysAndReturnKeyPressCode(e);

    if (keyPressed == LV_KEY_ENTER) {
        parentNode = findNodeWithIndex(actualNode->nodeNavigation.parentIndex);
        if (isCompressedList(parentNode)) {
            nextNode = findNodeWithIndex(parentNode->nodeNavigation.nextNodeInFlow);
            if (nextNode == NULL)
                assert(0);  /* compressed list must contain a next node in Flow */
            switchToNode(nextNode);
            return;
        }
        else {
            /* Choose archive or selected config */
             arraySelector = actualNode->nodeNavigation.childIndexinParent;
             switch (actualNode->parentNodeId){
             case SIGNALCONFIG:
                     setParameterValueFromInt(EDITEDCONFIG,arraySelector);
                     /* create a new configuration  */
                     if (temporaryInsimulatorOnlyConfigurationSetting[arraySelector].status == arrayVisibleDefaultName) { /* A empty configuration is available, copy the focused selewction into this */
                         copyConfiguration(actualNode);
                         nextNode = findNodeWithId(NAMEFORNEWCONFIG);
                         switchToNode(nextNode);
                         return;
                     }

                 break;
             case ARCHIVE:
                 setParameterValueFromInt(EDITEDARCHIVE,arraySelector);
                 /* create a new medium  */
                 if (temporaryInsimulatorOnlyArchiveSetting[arraySelector].status == arrayVisibleDefaultName) {
                     copyMedium(actualNode);
                     nextNode = findNodeWithId(NAMEFORNEWMEDIUM);
                     switchToNode(nextNode);
                     return;
                 }
                 break;

             default:
                 /* Nothing to do */
               break;
             }
            switchToNodeController(actualNode,eventHandlerListKey);
        }
    }
}

/* This function processes the event when the enter key is pressed on the user selection screen */
static void eventHandlerListKeyStoreUser(lv_event_t *e) {
    nodeDescriptor_t *actualNode;
    actualNode = getNodeFromEvent(e);
    switch (actualNode->menuId) {
        case AMTBUSER:
            setParameterValueFromInt(TRYTOLOGINUSER,amtbUser);
            break;
        case SYSTEMUSER:
            setParameterValueFromInt(TRYTOLOGINUSER,systemUser);
            break;
        default:
          break;
    }
    eventHandlerListKey(e);
}
/* This function processes the event for leaving the show application seccren */
static void eventHandlerApplicationFirstScreenTimeOut(lv_timer_t *timer) {

    nodeDescriptor_t* node = getNodeFromTimer(timer);
    pauseScreenTimer(node);
    requestParameterInformation(node);
    timer->timer_cb = eventHandlerScreenTimeOutToDefaultScreen;
    timer->period = APPLICATIONSCREEN_DELAY;
    lv_timer_resume(timer);

}
/* This function processes the event for leaving the show application seccren */
static void eventHandlerScreenTimeOutToDefaultScreen(lv_timer_t *timer) {
    nodeDescriptor_t *actualNode;
    actualNode = getNodeFromTimer(timer);
    pauseScreenTimer(actualNode);
    switchToFirstMenuScreen();
}


/* This function retrieves the node information from the timer event pointer */
static nodeDescriptor_t*  getNodeFromTimer(lv_timer_t *timer) {
    if (timer->user_data == NULL)
        return NULL;
    else
        return (nodeDescriptor_t*)timer->user_data;
}

static lv_res_t switchToApplicationInfoScreen(lv_timer_t * timer) {
    initApplicationScreen(NULL);
}
/* This function processes the event for leaving the logoscreen */
static void eventHandlerLogoScreenTimeOut(lv_timer_t *timer) {
    timer->paused = 1;
    switchToApplicationInfoScreen(timer);
}

/* This function retrieves the menu node processed by the eventhandler  */
static nodeDescriptor_t * getNodeFromEvent(lv_event_t *e) {
    nodeDescriptor_t *screenNode;
    lv_obj_t *obj;

    if (e != NULL) {
        obj = lv_event_get_target(e);
    }

    if (obj != NULL) {
        if (e->user_data != NULL) {
            screenNode = (nodeDescriptor_t*) e->user_data;
        } else {
            screenNode = (nodeDescriptor_t*) e->param;
        }
    }

    return screenNode;
}


/**
 * @brief Insert or toggle the stored value in the multichooselist
 */


/**
 * @brief Deactivate the stored value in the singlechooselist
 */
static void deactivateCheckSymbolInList(lv_obj_t * oldfocusedButton){
    lv_obj_t* checkMarkSymbol;
    if (oldfocusedButton==NULL)
        return;
    if (oldfocusedButton->user_data!=NULL){
        checkMarkSymbol=oldfocusedButton->user_data;
        lv_obj_del(checkMarkSymbol);
        oldfocusedButton->user_data=NULL;
    }
}


/**
 * @brief Mark the stored value in the singlechooselist
 */
static int8_t insertSingleCheckSymbolIntoList(lv_obj_t * focusedButton, int8_t defaultStateOnInit){
    // Mark the stored values in the list
    int8_t checkMarkSet;
    lv_obj_t* checkMarkSymbol;

    if (focusedButton->user_data==NULL){
        checkMarkSymbol = lv_label_create(focusedButton);
        focusedButton->user_data=checkMarkSymbol;

        lv_obj_align(checkMarkSymbol, LV_TEXT_ALIGN_RIGHT, 0, -20);

       lv_obj_add_style(checkMarkSymbol, &style_symbol,0);
       lv_obj_add_style(checkMarkSymbol, &style_symbol_focused,LV_STATE_FOCUSED);
        if (defaultStateOnInit!=0)
            lv_label_set_text(checkMarkSymbol, LV_SYMBOL_NAMUR_CHECKED);
        else
            lv_label_set_text(checkMarkSymbol, LV_SYMBOL_NAMUR_UNCHECKED);
    }
    else{
        checkMarkSymbol=focusedButton->user_data;
        char* checkMarkText= lv_label_get_text(checkMarkSymbol);
        /* Toggle state of checkmark */
        if (strcmp(checkMarkText,LV_SYMBOL_NAMUR_CHECKED)!=0){
            lv_label_set_text(checkMarkSymbol, LV_SYMBOL_NAMUR_CHECKED);
            checkMarkSet = 1;
        }
        else {
            lv_label_set_text(checkMarkSymbol, LV_SYMBOL_NAMUR_UNCHECKED);
            checkMarkSet = 0;
        }

    }
    lv_group_focus_obj(focusedButton);
    return checkMarkSet;
}

void switchToDefaultScreen() {
//    if (currentScreen->menuId == DEFAULT_SCREEN) {
//         return;
//    }
    initDefaultScreen(NULL);
    switchScreenTo(defaultScreenMenuNode);
}

void switchToFirstMenuScreen() {

    nodeDescriptor_t *screenNode;
    nodeDescriptor_t *defaultNode;

    defaultNode = findNodeWithType(NULL, defaultScreenMenuNode);
    screenNode= findFirstMenu();
    screenNode->nodeNavigation.parentIndex = defaultNode->menuIndex;
    fillMenuListScreen(screenNode , 0);  // First menu is a list

    activateScreen(screenNode);
    return;
}


static lv_res_t initDefaultScreen(lv_obj_t *p) {
    nodeDescriptor_t *node;
    lv_obj_t *content;
    lv_obj_t *obj;

    node = findNodeWithType(NULL, defaultScreenMenuNode);

    /* check lookuptable for data */
    if (node == NULL)
        return LV_RES_INV;

    if (node->menuIndex == currentScreen->menuIndex){
        eraseScreenNodeTasksAndObjects(node);
    }
    lv_res_t initScreenResult = initScreenArea(node);
    if (initScreenResult != LV_RES_OK)
        return initScreenResult;
    content = node->nodeData.content;

    initDefaultScreenValueAndUnitPositions(node);

    showHeaderInformation(node);
    initDisplayLineLayout(node);


// TODO DR Error handling */

}

/* TODO DR remove static lv_point parameter */
static void drawLine(lv_obj_t *lineItem, lv_obj_t *content,
        lv_point_t *chartLine, int x, int y, int x1, int y1) {
    lv_obj_t *obj;

    if ((lineItem == NULL) && (content != NULL)) {
        obj = lv_line_create(content);
       lv_obj_add_style(obj, &style_headerInfo, 0);
        chartLine[0].x = x;
        chartLine[0].y = y;
        chartLine[1].x = x1;
        chartLine[1].y = y1;
        lv_line_set_points(obj, chartLine, 2);
        lv_obj_align_to(obj, content, LV_ALIGN_TOP_LEFT, 0, 0);
        lv_obj_update_layout(obj);
        lineItem = obj;
    }
}

static void initAnalogChart(nodeDescriptor_t *screenNode) {
    lv_obj_t *obj;
    lv_obj_t *label;

    if (screenNode == NULL) {
        return;
    }

    if (screenNode->nodeData.content == NULL) {
        return;
    }

    printf("InitAnalog≤n");
   analogChartDefaultScreen.content = screenNode->nodeData.content ;
   lv_obj_t *content = analogChartDefaultScreen.content;

    /*
      * x=          9         10      y0
      *    --|--<---XXXXXXXXXXX-->---|--
      * x= 1 2  3   4         5  6   7 8         *
      */

     uint8_t const x1 = 6;
     uint8_t const x2 = 11;
     uint8_t const x3 = 15;

     uint8_t const x4 = 25;
     uint8_t const x5 = 100;//95
     uint8_t const x6 = 104;
     uint8_t const x7 = 115;  //109
     uint8_t const x8 = 120; //114
     uint8_t const x9 = 20;
     uint8_t const x10 = 89;
     uint8_t const y0 = 39;   // 0..100% values

     uint8_t const y1 = 50;
     uint8_t const y2 = 56;
     uint8_t const y3 = 60;
     uint8_t const y9 = 52;
     uint8_t const y10 = 63;


    drawLine(analogChartDefaultScreen.tVLineLeft, content, chartLine1, x2, y1, x2, y3);
    drawLine(analogChartDefaultScreen.tVLineRight, content, chartLine2, x7, y1, x7, y3);
    drawLine(analogChartDefaultScreen.tHLineLeft, content, chartLine3, x1, y2, x8, y2);
    //        drawLine(analogChartDefaultScreen.VAnalogValue, content, chartLine4, 35, 49, 35, 58);

    obj = lv_btn_create(content);
    lv_obj_add_style(obj, &style_bodyDark, 0);
    lv_obj_set_size(obj, x5-x4, y10-y9);
    lv_obj_align_to(obj, content, LV_ALIGN_TOP_LEFT, x4, y9);
    analogChartDefaultScreen.centerBody = obj;

    label = lv_label_create(content);
   lv_obj_add_style(label, &style_headerInfoInverted, 0);
    //        lv_obj_set_size(obj, 60, 11);
    lv_obj_align_to(label, analogChartDefaultScreen.centerBody, LV_ALIGN_TOP_LEFT, 0, 1);
    lv_label_set_text(label, "4.0");
    analogChartDefaultScreen.label4mA = obj;


    label = lv_label_create(content);
   lv_obj_add_style(label, &style_headerInfoInverted, 0);
    lv_obj_align_to(label, analogChartDefaultScreen.centerBody, LV_ALIGN_TOP_RIGHT, -0, 1);
    lv_label_set_text(label, "20.0");
    analogChartDefaultScreen.label20mA = label;

    label = lv_label_create(content);
   lv_obj_add_style(label, &style_headerInfo, 0);
    lv_obj_align_to(label, content, LV_ALIGN_TOP_LEFT, x9, y0);
     lv_label_set_text(label, "0%");
     analogChartDefaultScreen.probeLowValPercentage = label;

    label = lv_label_create(content);
   lv_obj_add_style(label, &style_headerInfo, 0);
    lv_obj_align_to(label, content, LV_ALIGN_TOP_LEFT, x10, y0);
    lv_label_set_text(label, "100%");
    analogChartDefaultScreen.probeHighValPercentage = label;

    label = lv_label_create(content);
   lv_obj_add_style(label, &style_headerInfo, 0);
    lv_obj_align_to(label, content, LV_ALIGN_TOP_LEFT, x3, y9-5);
    lv_label_set_text(label, EDITLEFTARROW);
    analogChartDefaultScreen.lowArrow = label;

    //analogChartDefaultScreen.probeHighValPercentage = label;

    label = lv_label_create(content);
    lv_obj_add_style(label, &style_headerInfo, 0);
    lv_obj_align_to(label, content, LV_ALIGN_TOP_LEFT, x6, y9-5);
    lv_label_set_text(label, EDITRIGHTARROW);
    analogChartDefaultScreen.highArrow = label;

    label = lv_label_create(content);
   lv_obj_add_style(label, &style_headerInfo, 0);
    lv_obj_align_to(label, content, LV_ALIGN_TOP_LEFT, x4, y9);
    lv_label_set_text(label, "|");
    analogChartDefaultScreen.measuredValPercentage = label;

}

static int8_t getNumberOfDisplayedLines(){
    int8_t count = 0;
    int8_t currentlyChosenNumberOfDisplayedLines = getParameterValueAsInt(DISPLAY);
    for (uint8_t displayLine = DISPLAYLINE_1; displayLine<=DISPLAYLINE_3;displayLine++) {
        if (getParameterChooseListFromStorage(displayLine)!=unitsNone)
            count++;
    }

    if (count >=currentlyChosenNumberOfDisplayedLines)
        count = currentlyChosenNumberOfDisplayedLines;
    else{
        /* nothing to do */
    }


    return count;
}

static void initDisplayLineLayout(nodeDescriptor_t *node) {
    uint8_t curIndex = 0;
    uint16_t unitRightX = 110;  /* line can be full length as there is not unit field in header */


    lv_style_t *style;
    lv_obj_t *obj_unit;
    lv_obj_t *obj;
    lv_obj_t * content = node->nodeData.content;

    uint8_t numberOfDisplayedLines = getNumberOfDisplayedLines();

    switch (numberOfDisplayedLines) {
        case 1:
            style = &style_big;

            obj_unit = node->nodeData.nodeObj[screenDefaultMeasUnit0].obj;
            if (obj_unit)
            {
                lv_obj_remove_style_all(obj_unit);
                lv_obj_add_style(obj_unit, &style_huge, 0);
                lv_obj_align_to(obj_unit, content, LV_ALIGN_TOP_RIGHT, 0,-1);
                lv_obj_align(obj_unit, LV_TEXT_ALIGN_RIGHT, 0, -2);

                style = &style_mega;
                obj = node->nodeData.nodeObj[screenDefaultMeasValue0].obj;
                lv_obj_remove_style_all(obj);

                lv_obj_add_style(obj, style, 0);
                lv_style_set_text_align(&style_mega, LV_TEXT_ALIGN_RIGHT);
                lv_obj_align(obj, LV_ALIGN_RIGHT_MID, 0, -3);
                lv_obj_set_width(obj, 110);

            }
            break;
        case 2:
            style = &style_huge;
            lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
            obj_unit = node->nodeData.nodeObj[screenDefaultMeasUnit0].obj;
            if (obj_unit)
            {
               lv_obj_remove_style_all(obj_unit);
               lv_obj_add_style(obj_unit, &style_big, 0);
                lv_obj_set_content_width(obj_unit, 20);
                lv_obj_align_to(obj_unit, content, LV_ALIGN_BOTTOM_RIGHT, -5,
                        -(lv_obj_get_height(content)) / (numberOfDisplayedLines + 2)
                                * (numberOfDisplayedLines - curIndex));
                lv_obj_update_layout(obj_unit);
                lv_obj_invalidate( obj_unit);

                obj = node->nodeData.nodeObj[screenDefaultMeasValue0].obj;

                lv_obj_remove_style_all(obj);
                lv_obj_add_style(obj, style, 0);

                lv_obj_align_to(obj, obj_unit, LV_ALIGN_OUT_RIGHT_MID, -75, 0);
                lv_obj_invalidate( obj);

            }
            curIndex++;

            obj_unit = node->nodeData.nodeObj[screenDefaultMeasUnit1].obj;
            if (obj_unit)
            {
                lv_obj_remove_style_all(obj_unit);
                lv_obj_add_style(obj_unit, &style_big, 0);
                lv_obj_set_content_width(obj_unit, 20);
                lv_obj_align_to(obj_unit, content, LV_ALIGN_BOTTOM_RIGHT, -5,
                        -(lv_obj_get_height(content)) / (numberOfDisplayedLines + 2)
                                * (numberOfDisplayedLines - curIndex));
                lv_obj_update_layout(obj_unit);

                obj = node->nodeData.nodeObj[screenDefaultMeasValue1].obj;
                lv_obj_remove_style_all(obj);
                lv_obj_add_style(obj, style, 0);

                lv_obj_align_to(obj, obj_unit, LV_ALIGN_OUT_RIGHT_MID, -75, 0);
            }
            break;
         case 3:
             style = &style_big;
             lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);

              obj_unit = node->nodeData.nodeObj[screenDefaultMeasUnit0].obj;
              if (obj_unit)
              {
                  lv_obj_remove_style_all(obj_unit);

                  lv_obj_add_style(obj_unit, style, 0);
                  lv_obj_set_content_width(obj_unit, 20);
                  lv_obj_align_to(obj_unit, content, LV_ALIGN_BOTTOM_RIGHT, -5,
                          -(lv_obj_get_height(content)) / (numberOfDisplayedLines + 2)
                                  * (numberOfDisplayedLines - curIndex));
                  lv_obj_update_layout(obj_unit);
                  lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);

                  obj = node->nodeData.nodeObj[screenDefaultMeasValue0].obj;
                  lv_obj_remove_style_all(obj);
                  lv_obj_add_style(obj, style, 0);

                  lv_obj_align_to(obj, obj_unit, LV_ALIGN_OUT_LEFT_MID, -30, 0);
              }
              curIndex++;

              obj_unit = node->nodeData.nodeObj[screenDefaultMeasUnit1].obj;
              if (obj_unit)
              {
                  lv_obj_remove_style_all(obj_unit);
                  lv_obj_add_style(obj_unit, style, 0);
                  lv_obj_set_content_width(obj_unit, 20);
                  lv_obj_align_to(obj_unit, content, LV_ALIGN_BOTTOM_RIGHT, -5,
                          -(lv_obj_get_height(content)) / (numberOfDisplayedLines + 2)
                                  * (numberOfDisplayedLines - curIndex));
                  lv_obj_update_layout(obj_unit);


                  obj = node->nodeData.nodeObj[screenDefaultMeasValue1].obj;
                  lv_obj_remove_style_all(obj);
                  lv_obj_add_style(obj, style, 0);

                  lv_obj_align_to(obj, obj_unit, LV_ALIGN_OUT_LEFT_MID, -30, 0);
              }
              curIndex++;

              obj_unit = node->nodeData.nodeObj[screenDefaultMeasUnit2].obj;
              if (obj_unit)
              {
                  lv_obj_remove_style_all(obj_unit);
                  lv_obj_add_style(obj_unit, style, 0);
                  lv_obj_set_content_width(obj_unit, 20);
                  lv_obj_align_to(obj_unit, content, LV_ALIGN_BOTTOM_RIGHT, -5,
                          -(lv_obj_get_height(content)) / (numberOfDisplayedLines + 2)
                                  * (numberOfDisplayedLines - curIndex));
                  lv_obj_update_layout(obj_unit);

                  obj = node->nodeData.nodeObj[screenDefaultMeasValue2].obj;
                  lv_obj_remove_style_all(obj);
                  lv_obj_add_style(obj, style, 0);
                  lv_obj_align_to(obj, obj_unit, LV_ALIGN_OUT_LEFT_MID, -30, 0);
              }
          break;
     default:
        break;
    }
    unitRightX = obj_unit->coords.x2;
    drawLine(node->nodeData.nodeObj[screenDefaultTopLine].obj, content,
            defaultScreenLine1, 0, 14, unitRightX, 14);

}

static void initDefaultScreenValueAndUnitPositions(nodeDescriptor_t *screenNode) {
    uint8_t curIndex = 0;
    char unitString[SMALLSTRINGSIZE];
    lv_style_t *style;
    lv_obj_t *obj_unit;
    lv_obj_t *obj;

   pauseScreenTimer(screenNode);
   printf("initDefaultScreenValueAndUnitPositions\n");
    lv_obj_t * content = screenNode->nodeData.content;
    int8_t numberOfDisplayedLines = getNumberOfDisplayedLines();

    if (numberOfDisplayedLines <=1 )
        initAnalogChart(screenNode);
    else {
        /* No analog chart if more than one displayed line */
    }

    if (numberOfDisplayedLines == 0)
        return;  /* No display lines to support */

    uint8_t unitForThisLine;
    /*count number of datafields */
    for (uint8_t currentDisplayLine = 0; currentDisplayLine < MAX_NUMBER_OF_DISPLAYED_MEASVALUES;currentDisplayLine++) {
    /* check and init screen obj if needed */
        if (screenNode->nodeData.nodeObj[screenDefaultMeasUnit0 + currentDisplayLine].obj == NULL) {
            if (currentDisplayLine < numberOfDisplayedLines) {
                printf("line\n");

                unitForThisLine = getParameterChooseListFromStorage(DISPLAYLINE_1+currentDisplayLine);
                 if (unitForThisLine != UNITS_NONE) {
                     obj = lv_label_create(content);
                     printf("linecreated\n");
                     screenNode->nodeData.nodeObj[screenDefaultMeasUnit0 + currentDisplayLine].obj = obj;
                     strcpy(unitString,getMenuOrParameterNameFromMenuDefinitions(unitForThisLine));
                     lv_label_set_text(screenNode->nodeData.nodeObj[screenDefaultMeasUnit0 + currentDisplayLine].obj, unitString);
                     if (screenNode->nodeData.nodeObj[screenDefaultMeasValue0 + currentDisplayLine].obj == NULL) {
                         obj = lv_label_create(content);
                         lv_label_set_text(obj, " ");
                         screenNode->nodeData.nodeObj[screenDefaultMeasValue0 + currentDisplayLine].obj = obj;
                     }
                     else {
                         /* Nothing to do */
                     }
                 }
                 else {
                     /* Nothing to do */
                 }
            }
            else {
                /* Nothing to do */
            }
        }
        else {
            /* Nothing to do */
        }
    }
}

static void AquaHMI_printNamurSymbolsFromNamurState(lv_obj_t *nodeOb,
        namurBitFieldPos_t namurState) {
    //    char* string[4]={0,0,0,0};
    if (nodeOb == NULL) {
        return;
    }
    switch (namurState) {
    case namurFault:
        //        string=LV_SYMBOL_NAMUR_V2_FAULT;
        lv_label_set_text(nodeOb, LV_SYMBOL_NAMUR_V2_FAULT);
        break;
    case namurOutOfRange:
        //        string=LV_SYMBOL_NAMUR_V2_OUT_OF_RANGE;
        lv_label_set_text(nodeOb, LV_SYMBOL_NAMUR_V2_OUT_OF_RANGE);
        break;
    case namurMaintenence:
        //        string=LV_SYMBOL_NAMUR_V2_MAINTENENCE;
        lv_label_set_text(nodeOb, LV_SYMBOL_NAMUR_V2_MAINTENENCE);
        break;
    case namurCheck:
        //        string=LV_SYMBOL_NAMUR_V2_CHECK;
        lv_label_set_text(nodeOb, LV_SYMBOL_NAMUR_V2_CHECK);
        break;
    case namurChecked:
        //        string=LV_SYMBOL_NAMUR_V2_CHECKED;
        lv_label_set_text(nodeOb, LV_SYMBOL_NAMUR_V2_CHECKED);
        break;
    case namurUnchecked:
        //        string=LV_SYMBOL_NAMUR_V2_UNCHECKED;
        lv_label_set_text(nodeOb, LV_SYMBOL_NAMUR_V2_UNCHECKED);
        break;

    default:

        break;
    }
}


static lv_res_t initParameterTakeOverScreen(nodeDescriptor_t *screenNode) {

    assert(screenNode!=NULL);

    if (initParameterScreenCommon(screenNode)!=LV_RES_OK)
        return LV_RES_INV;

    lv_obj_t *content = screenNode->nodeData.content;
    lv_obj_t * obj;

    lv_obj_align(screenNode->nodeData.nodeObj[screenParamBodyText].obj, LV_ALIGN_TOP_LEFT, 10, TOP_MENU_HEIGHT);
    if (screenNode->nodeData.nodeObj[screenParameterActualValue].obj == NULL) {
        obj = lv_label_create(content);
       lv_obj_add_style(obj, &style_medium, 0);
        lv_label_set_text(obj, "1234");

        lv_obj_align(obj, LV_ALIGN_TOP_LEFT, 10, TOP_MENU_HEIGHT + 20);
        screenNode->nodeData.nodeObj[screenParameterActualValue].obj = obj;
    }

    if (screenNode->nodeData.nodeObj[screenParameterControlButtons].obj == NULL) {
        lv_obj_t * list = lv_list_create(screenNode->nodeData.content);
        screenNode->nodeData.nodeObj[screenParameterControlButtons].obj = list;
        lv_obj_set_size(list, 80,40);

        lv_obj_align(list, LV_ALIGN_TOP_LEFT, 50, 30);
        lv_obj_set_scrollbar_mode(list, LV_SCROLLBAR_MODE_OFF);

        lv_obj_t * takeOverButton =  lv_list_add_btn(list, 0, getMenuOrParameterNameFromMenuDefinitions(OKTAKEOVERINFO));
        lv_obj_t * okButton =  lv_list_add_btn(list, 0, getMenuOrParameterNameFromMenuDefinitions(CONTINUETONEXT));
       lv_obj_add_style(takeOverButton, &style_headerInfo, 0);
       lv_obj_add_style(takeOverButton, &style_headerInfoInverted, LV_STATE_FOCUSED);

       lv_obj_add_style(okButton, &style_headerInfo, 0);
       lv_obj_add_style(okButton, &style_headerInfoInverted, LV_STATE_FOCUSED);


        lv_obj_align_to(takeOverButton,list, LV_ALIGN_TOP_LEFT, 0, 0);
        lv_obj_align_to(okButton, takeOverButton,LV_ALIGN_TOP_LEFT, 40, 0);
        screenNode->nodeData.group = lv_group_create();
        lv_group_add_obj(screenNode->nodeData.group, takeOverButton);
        lv_group_add_obj(screenNode->nodeData.group, okButton);
        lv_obj_add_event_cb(takeOverButton, screenNode->nodeData.eventHandler,
                LV_EVENT_KEY, screenNode);
        lv_obj_add_event_cb(okButton, screenNode->nodeData.eventHandler,
                LV_EVENT_KEY, screenNode);
        lv_group_focus_obj(takeOverButton);
    }

    return LV_RES_OK;
}

static void initParameterEditorButtons(lv_obj_t *btnm){
    int8_t activeValueEditIndex=1;

   // lv_btnmatrix_set_map(btnm, map);
   lv_obj_add_style(btnm, &style_bg, 0);
   lv_obj_add_style(btnm, &style_btn, LV_PART_ITEMS);
     lv_obj_set_size(btnm, 120, 28);

    /*Allow selecting on one number at time*/
    lv_btnmatrix_set_btn_ctrl_all(btnm, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_btnmatrix_clear_btn_ctrl(btnm, 0, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_btnmatrix_clear_btn_ctrl(btnm, 6, LV_BTNMATRIX_CTRL_CHECKABLE);

  //  lv_btnmatrix_set_btn_width(btnm, 0, 2);

    lv_btnmatrix_set_one_checked(btnm, true);
    lv_btnmatrix_set_btn_ctrl(btnm, activeValueEditIndex, LV_BTNMATRIX_CTRL_CHECKED);
    lv_btnmatrix_set_selected_btn(btnm, 4);
    lv_obj_align(btnm, LV_ALIGN_CENTER, 0, 15);

    //    lv_btnmatrix_set_btn_ctrl(btnm, 1, LV_BTNMATRIX_CTRL_CHECKED);
        lv_btnmatrix_set_btn_ctrl(btnm, 1,
                LV_BTNMATRIX_CTRL_CHECKED);
}

static void initParameterEditButtons(parametercharacteristics_t * editParameterCharacteristics,char* parameterString,nodeDescriptor_t *  node){
    uint8_t  digits = editParameterCharacteristics->editDigits;
    uint8_t lengthOfEditParameterContent=digits +2;   // Add two, one for EDITLEFTARROW and one for EDITSTORECOMMAND
    int8_t targetStringIndex = 0;
    assert(lengthOfEditParameterContent < MAXEDITSTRINGSIZE);
    static const char * btnm_map[MAXEDITSTRINGSIZE];
    lv_obj_t * btnm = node->nodeData.nodeObj[screenParamCurrentEditButtons].obj;
    if (btnm == NULL){
        btnm = lv_btnmatrix_create(node->nodeData.content);
        initParameterEditorButtons(btnm);
    }
    lv_btnmatrix_set_map(btnm, btnm_map);
    /* Make the button informations static during the lifetime of the screen */
     node->nodeData.nodeObj[screenParamCurrentEditButtons].obj = btnm;

     int16_t size=sizeof(editorControl.parameterEditStringArray);
     memset(editorControl.parameterEditStringArray,0,sizeof(editorControl.parameterEditStringArray));
     strcpy(editorControl.parameterEditStringArray[0],EDITLEFTARROW);
     targetStringIndex++;
     strcpy(editorControl.parameterEditStringArray[lengthOfEditParameterContent+4],"");


     for (int index=0;index<=digits;index++){
         if (strlen(parameterString) > index){
             editorControl.parameterEditStringArray[targetStringIndex][0]= parameterString[index];
             strcat(editorControl.parameterEditStringArray[targetStringIndex],"\0");
         }
         else
             editorControl.parameterEditStringArray[targetStringIndex][0]= ' ';
         if ((digits > SIZEOFEDITBUTTONSPERLINE) && (index==digits / 2)){ /* linebreak for long strings */
             strcpy(editorControl.parameterEditStringArray[++targetStringIndex],"\n\0");

         }
         targetStringIndex++;
     }
     targetStringIndex--;
     strcpy(editorControl.parameterEditStringArray[targetStringIndex++],EDITSTORECOMMAND);
//     if (node->nodeData.menuNodeType ==  parameterEditNodeWithApply) {
         strcpy(editorControl.parameterEditStringArray[targetStringIndex++],EDITRIGHTARROW);
//     }
//     else
//         strcpy(editorControl.parameterEditStringArray[targetStringIndex],"OK\0");

     /* Necessary storing edit string in a static array, did many tries to figure out */
    for (int index=0;index<=lengthOfEditParameterContent+3;index++){
       ((lv_btnmatrix_t *)btnm)->map_p[index]=&editorControl.parameterEditStringArray[index];

    }
   // ((lv_btnmatrix_t *)btnm)->map_p[lengthOfEditParameterContent+2]="\nOK\0";
}

static int16_t * findFirstFreeFieldObjectIndex(nodeDescriptor_t *screenNode,int16_t firstSearchIndex, int16_t lastSearchIndex){
int16_t searchIndex=firstSearchIndex;
  while (searchIndex!=lastSearchIndex){
      if ((screenNode->nodeData.nodeObj==NULL) || (screenNode->nodeData.nodeObj[searchIndex].obj == NULL))
          return searchIndex;
      searchIndex++;
  }

    return NULL;
}

static lv_res_t initParameterEditWithApplyScreen(nodeDescriptor_t* screenNode) {

    lv_res_t result = initParameterEditScreen(screenNode);

    if (result == LV_RES_OK) {

        lv_obj_align(screenNode->nodeData.nodeObj[screenParamCurrentEditButtons].obj, LV_ALIGN_TOP_LEFT, 10, 20);

        if (screenNode->nodeData.nodeObj[screenParameterControlButtons].obj == NULL) {
             lv_obj_t * list = lv_list_create(lcdScreen);
             screenNode->nodeData.nodeObj[screenParameterControlButtons].obj = list;
             lv_obj_set_size(list, 80,20);
             lv_obj_align(list, LV_ALIGN_TOP_LEFT, 50, 50);
             lv_obj_set_scrollbar_mode(list, LV_SCROLLBAR_MODE_OFF);

             lv_obj_t * okButton =  lv_list_add_btn(list, 0, getMenuOrParameterNameFromMenuDefinitions(CONTINUETONEXT));
            lv_obj_add_style(okButton, &style_headerInfo, 0);
            lv_obj_add_style(okButton, &style_headerInfoInverted, LV_STATE_FOCUSED);

             lv_group_add_obj(screenNode->nodeData.group, okButton);
             lv_obj_add_event_cb(okButton, screenNode->nodeData.eventHandler,
                     LV_EVENT_KEY, screenNode);
          //   lv_group_focus_obj(okButton);
         }

    }
    else {
        /* Initialisation fault */
    }

    return result;;
}



static lv_res_t initParameterEditScreen(nodeDescriptor_t* screenNode) {

    lv_obj_t *content;
    lv_obj_t *obj;

    if (initParameterScreenCommon(screenNode)!=LV_RES_OK)
        return LV_RES_INV;

    assert(screenNode!=NULL);
    content = screenNode->nodeData.content;

    if (screenNode->nodeData.nodeObj[screenParamBodyText].obj !=NULL)
        lv_obj_align(screenNode->nodeData.nodeObj[screenParamBodyText].obj, LV_ALIGN_TOP_LEFT, 10, TOP_MENU_HEIGHT);

    STR currentParameterID = screenNode->sourceNode;
    parametercharacteristics_t *editParameterCharacteristics = getParameterCharacteristics(
            currentParameterID);
    assert(editParameterCharacteristics!=NULL);

    drawLine(screenNode->nodeData.nodeObj[screenParamCurrentEditIndexLine].obj, content,
            paramScreenLine1, 40, 45, 50, 45);

    const char* parameterString = getParameterValueAsString(screenNode->sourceNode);
    if (screenNode->nodeData.menuNodeType != passwordEntryNode)
        checkParameterRange(screenNode,parameterString);
    else
    {
        /* No range check for password entries */
    }
    initParameterEditButtons(editParameterCharacteristics,parameterString,screenNode);


    return LV_RES_OK;
}

static lv_res_t initMessageScreen(nodeDescriptor_t *screenNode) {
    lv_obj_t *content;
    lv_obj_t *obj;

    actualEditIndexInButtonArray = 0;
    lv_res_t initScreenResult = initScreenArea(screenNode);
    if (initScreenResult != LV_RES_OK)
        return initScreenResult;

    content = screenNode->nodeData.content;

    if (screenNode->nodeData.nodeObj[screenParamBodyText].obj == NULL) {

        obj = lv_label_create(content);
       lv_obj_add_style(obj, &style_medium, 0);
        lv_label_set_text(obj, " ");
        lv_obj_align(obj, LV_ALIGN_TOP_LEFT, 10, 11);
        screenNode->nodeData.nodeObj[screenParamBodyText].obj = obj;
    }
    return LV_RES_OK;
}


static lv_res_t initParameterShowScreen(nodeDescriptor_t *screenNode) {
    lv_obj_t *content;
    lv_obj_t *obj;

    lv_res_t initScreenResult = initParameterScreenCommon(screenNode);
    if (initScreenResult != LV_RES_OK)
        return initScreenResult;

    content = screenNode->nodeData.content;

    if (screenNode->nodeData.nodeObj[screenParameterControlButtons].obj == NULL) {
         lv_obj_t * list = lv_list_create(lcdScreen);
         screenNode->nodeData.nodeObj[screenParameterControlButtons].obj = list;
         lv_obj_set_size(list, 80,20);
         lv_obj_align(list, LV_ALIGN_TOP_LEFT, 50, 50);
         lv_obj_set_scrollbar_mode(list, LV_SCROLLBAR_MODE_OFF);

        lv_obj_t * okButton =  lv_list_add_btn(list, 0, getMenuOrParameterNameFromMenuDefinitions(CONTINUETONEXT));
        lv_obj_add_style(okButton, &style_headerInfo, 0);
        lv_obj_add_style(okButton, &style_headerInfoInverted, LV_STATE_FOCUSED);

        lv_group_add_obj(screenNode->nodeData.group, okButton);
        lv_obj_add_event_cb(okButton, screenNode->nodeData.eventHandler,
             LV_EVENT_KEY, screenNode);
        lv_group_focus_obj(okButton);
     }
}

static lv_res_t initParameterScreenCommon(nodeDescriptor_t *screenNode) {

    lv_obj_t *content;
    lv_obj_t *obj;

    actualEditIndexInButtonArray = 0;
    lv_res_t initScreenResult = initScreenArea(screenNode);
    if (initScreenResult != LV_RES_OK)
        return initScreenResult;

    content = screenNode->nodeData.content;

    drawLine(screenNode->nodeData.nodeObj[screenDefaultTopLine].obj, content,
            defaultScreenLine1, 0, 10, 130, 10);

    if (screenNode->nodeData.nodeObj[screenParameterName].obj == NULL) {
        obj = lv_label_create(content);
       lv_obj_add_style(obj, &style_headerInfo, 0);

        lv_label_set_text(obj, "ParamName");
        lv_obj_align(obj, LV_ALIGN_TOP_MID, 20, 0);
        screenNode->nodeData.nodeObj[screenParameterName].obj = obj;
    }

    char* parameterString = getParameterValueAsString(screenNode->sourceNode);
    if (screenNode->nodeData.nodeObj[screenParamCurrentEditString].obj == NULL) {
        obj = lv_label_create(content);
       lv_obj_add_style(obj, &style_default_invisible, 0);
        lv_label_set_text(obj,parameterString);
        lv_obj_align(obj, LV_ALIGN_TOP_LEFT, 40, 34);
        screenNode->nodeData.nodeObj[screenParamCurrentEditString].obj = obj;
    }

    if (screenNode->nodeData.nodeObj[screenParameterTakeOverValue].obj == NULL) {
        obj = lv_label_create(content);
       lv_obj_add_style(obj, &style_default_invisible, 0);
        lv_label_set_text(obj,parameterString);
        lv_obj_align(obj, LV_ALIGN_TOP_LEFT, 40, 34);
        screenNode->nodeData.nodeObj[screenParameterTakeOverValue].obj = obj;
    }

    if (screenNode->nodeData.nodeObj[screenParamBodyText].obj == NULL) {
        obj = lv_label_create(content);
       lv_obj_add_style(obj, &style_medium, 0);
        lv_label_set_text(obj, "   ");
        lv_obj_align(obj, LV_ALIGN_TOP_LEFT, 10, 11);
        screenNode->nodeData.nodeObj[screenParamBodyText].obj = obj;
    }
    showHeaderInformation(screenNode);
    return LV_RES_OK;
}



static lv_res_t initApplicationScreen(lv_obj_t *p) {
    nodeDescriptor_t *screenNode = prepareParameterScreenFromTemplate(parameterShowNode,APPLICATION);
    assert(screenNode->nodeData.nodeObj[screenParamBodyText].obj != NULL);
    lv_obj_add_flag(screenNode->nodeData.nodeObj[screenParameterControlButtons].obj ,LV_OBJ_FLAG_HIDDEN);
    addTimerTaskToNode(screenNode, fillParameterInApplicationInfoScreen,
            SCREEN_FUNCTION_CALLBACK_PERIOD, 1);
    activateScreen(screenNode);
}

static lv_res_t initLogoScreen(lv_obj_t *p) {

    nodeDescriptor_t *screenNode;
    lv_obj_t *content;
    lv_obj_t *obj;

    screenNode = findNodeWithType(NULL, logoScreenNode);

    lv_res_t initScreenResult = initScreenArea(screenNode);
    if (initScreenResult != LV_RES_OK)
        return initScreenResult;

    content = screenNode->nodeData.content;

    /* check and init screen obj if needed */
    if (screenNode->nodeData.nodeObj[screenLogoIndex].obj == NULL) {
        obj = lv_img_create(content);
        screenNode->nodeData.nodeObj[screenLogoIndex].obj = obj;
        lv_img_set_src(obj, &Logo_Aquasant_100x25);
        lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
    }
    activateScreen(screenNode);

    return LV_RES_OK;

}

static uint8_t isVisibleDependentOnSetting(STR menuId, uint8_t indexInCaseOfChooseList){
    uint8_t visible ;
    int32_t dependsOnBitArray ;
    int32_t bitMask;

    switch (menuId){
        case UNITS_NONE:
        case UNIT_MA:
        case UNIT_pF:
        case UNIT_PERCENT:
        case UNIT_MM:
        case UNIT_CM:
        case UNIT_M:
        case UNIT_LITER:
        case UNIT_M3METER:
        case UNIT_MILLILITER:

        case EH_0001:
        case EH_UNDERFLOW_MEAS:
        case EH_OVERFLOW_MEAS:
        case EH_UNDERFLOW_MOD:
        case EH_OVERFLOW_MOD:
        case EH_LOW_TEMP:
        case EH_HIGH_TEMP:
        case EH_PORBE_OPEN:
        case EH_PROBE_SHORT:
        case EH_PROBE_OUT_OF_RANGE:
        case EH_CONFIG_INVALID:
        case EH_DATA_INVALID:
        case EH_FW_ERR:
        case EH_HW_ERR:

            dependsOnBitArray = atoi(getParameterValueAsString(ERROR_HANDLING));
            bitMask = 1<<indexInCaseOfChooseList;
            visible = (dependsOnBitArray & bitMask) >0;
            break;
        case RUNFIRSTOPERATION:
        case SKIPFIRSTOPERATION:
            visible =  getParameterValueAsInt(RUNFIRSTOPERATION)==1;
            break;
        case BASE_SETUP:
            visible =  getParameterValueAsInt(RUNFIRSTOPERATION)==0;
            break;
        default:
            visible = isNoOrValidArrayEntry(menuId);
            break;
    }
    return visible;
}


/* analyses if the given menu is a array element (like config, medium). */
static uint8_t isArrayMember(STR menuId,STR firstArrayId) {
    uint8_t isMember = false;
    uint16_t numberOfEntries;
    parameterArrayAttribute * arrayValidity;
    int16_t indexToArray; /* can be minus but should work like that */

    if ((firstArrayId == CONFIGURATIONX) || NULL) {
        indexToArray = menuId - CONFIGURATIONX;
        numberOfEntries = NUMBER_OF_NEWCONFIGURATIONS;
        if ((indexToArray >= 0) && (indexToArray < numberOfEntries)) {
              isMember = true;
        }
        else {
            /* is not a member */
        }
    }
    else if ((firstArrayId == ARCHIVEX) || NULL) {
        indexToArray = menuId - ARCHIVEX;
        numberOfEntries = NUMBER_OF_MEDIUMS;;

        if ((indexToArray >= 0) && (indexToArray < numberOfEntries)) {
            isMember = true;
        }
        else {
            /* is not a member */
        }
   }
   else {
           /* is not a member */
   }
    return isMember;
}
/* analyses if the given menu is a visible array  element (like config, medium). Non array elements are marked visible */
static uint8_t isNoOrValidArrayEntry(STR menuId) {
    uint8_t visible;
    uint16_t numberOfEntries;
    parameterArrayAttribute * arrayValidity;
    int16_t indexToArray; /* can be minus but should work like that */


    indexToArray = menuId - CONFIGURATIONX;
    numberOfEntries = NUMBER_OF_NEWCONFIGURATIONS;
    if ((indexToArray >= 0) && (indexToArray < numberOfEntries)) {
          visible = arrayUninitialized != temporaryInsimulatorOnlyConfigurationSetting[indexToArray].status;
          return visible;
    }
    else {
        indexToArray = menuId - ARCHIVEX;
        numberOfEntries = NUMBER_OF_MEDIUMS;;

        if ((indexToArray >=0) && (indexToArray < numberOfEntries)) {
                visible = arrayUninitialized != temporaryInsimulatorOnlyArchiveSetting[indexToArray].status;
                return visible;
        }
        else {
            return true;
        }
   }
    return true;
}

static uint8_t getParameterValueWithDependence(STR menuId, uint8_t position){
    uint8_t visible ;
    int32_t dependsOnBitArray ;
    int32_t bitMask;

    switch (menuId){
        case MEASVALUNITS:
        case DISPLAYLINE_1:
        case DISPLAYLINE_2:
        case DISPLAYLINE_3:

            dependsOnBitArray = (uint32_t) atoi(getParameterValueAsString(MEASVALUNITS));
            bitMask = 1<<position;
            visible = (dependsOnBitArray & bitMask) >0;
            break;
        case ERROR_HANDLING:
            dependsOnBitArray = (uint32_t) atoi(getParameterValueAsString(ERROR_HANDLING));
            bitMask = 1<<position;
            visible = (dependsOnBitArray & bitMask) >0;
            break;

        default:
            visible = true;
    }

    return visible;
}


static accessright_t getAccessRightForLoggedinUser(STR nodeId) {

    int8_t activeUser = getParameterValueAsInt(SELECTUSER); /* TODO DR error handling if not string */
    assert(activeUser < loginUserMax);
    int8_t index = 0;
    accessright_t accessRight = readWrite;  /* Generally right, if not limited by menuaccessRightsTable */

    while (index < sizeofAccessRightsTable) {
        if (accessRightsTable[index].parameterOrMenuId == nodeId) {
            switch (activeUser) {
                case amtbUser:
                    accessRight = accessRightsTable[index].amtbUserRight;
                    break;
                case systemUser:
                    accessRight = accessRightsTable[index].systemUserRight;
                    break;
                case publicUser:
                    accessRight = accessRightsTable[index].publicUserRight;
                    break;
                default:
                    accessRight = readWrite;
                    break;
             }
            return accessRight;
        }
        index++;
    }

    return accessRight;
}


/* Storage of enum items for example units from a chooselist   */
/* childIndex = STR - Unitsdefinitionstart + 1  => mapped value in storage for EP */
static STR findSTRFromEnumValue(uint8_t enumValue) {
    uint16_t index = 0;
    while (index < sizeOfMapChooseListEnums) {
        if (mapChooseListEnums[index].chooseListEnum== enumValue) {
            return mapChooseListEnums[index].chooseListParameter;
        }
        index++;
    }

#if BGM13S32F512GA
    return 0;     /* use 0 when an entry in the mapping table is missing, TODO DR decide final behaviour  " */
#else
    assert(0);  /* "An entry in the mapping table is required " */
#endif
    return 0;
}
static uint8_t findMappedEnumValueFromSTR(STR nodeId) {
    uint16_t index = 0;
    while (index < sizeOfMapChooseListEnums) {
        if (mapChooseListEnums[index].chooseListParameter == nodeId) {
            return mapChooseListEnums[index].chooseListEnum;
        }
        index++;
    }
#if BGM13S32F512GA
    return 0;     /* use 0 when an entry in the mapping table is missing, TODO DR decide final behaviour  " */
#else
    return 0;
    assert(0);  /* "An entry in the mapping table is required " */
#endif
}

void initParameterDefaultValuesAll() {

    uint16_t index = 0;
    while (index < sizeofParameterCharacteristics) {
        parametercharacteristics_t *parameterDescription =
                &parameterCharacteristics[index++];
        if (strlen(parameterDescription->defaultValue) > 0)

            switch(parameterDescription->parameterId){
            case SERIALNUMBER:
            case PASSWORDENTRYVALUE:
            case PROBETYPE:
            case ANALOGSIGNALSPREAD04MA:
            case ANALOGSIGNALSPREAD20MA:
            case EXPECTAMTBPASSWORD:
            case EXPECTSYSPASSWORD:
            case MASIMULATIONVALUE:
            case SELECTUSER:
            case SENSORSERIALNUMBER:
            case PROBESERIALNUMBER:
            case SOFTWAREVERSION:
            case HARDWAREVERSION:
            case FIRSTDATE:
            case PROOFDATE:
            case QRMANUAL:
            case QRDOCS:
            case CONTACT:
            case CURRENTTAG:
            case NAMEFORNEWCONFIG:
            case MEDIUMNAME:
            case DEVICENAME:
            case DISPLAY:
            case ADDTO20MAVALUE:
            case RUNFIRSTOPERATION:
            case ACTIVEERROR:
            case NEWPASSWORDENTRY:
            case NEWPASSWORDVERIFY:
            case ACTIVECONFIG:
            case EDITEDARCHIVE:
            case EDITEDCONFIG:
            case SIGNALFILTER:
            case LANGUAGE:
            case NAMEFORNEWMEDIUM:
                setParameterDefaultValueInStorage(parameterDescription->parameterId);
            break;
            default:
                assert(0); /* A parameter default value is defined but not executed */
            }
     }
    return;
}

parametercharacteristics_t* getParameterCharacteristics(STR nodeId) {

    uint16_t index = 0;
    while (index < sizeofParameterCharacteristics) {
        parametercharacteristics_t *parameterDescription =
                &parameterCharacteristics[index++];
        if (parameterDescription->parameterId == nodeId)
            return parameterDescription;
    }
    return NULL;
}

#ifdef LVGL_PC_SIM

void setModSliderAddress(void *sliderAddress){
    sliderStates.sliderSpreadRange = sliderAddress;
}

void setProbeRangeSliderAddress(void *sliderAddress){
    sliderStates.sliderProbeRange = sliderAddress;
}

void setDownButtonAddress(void *buttonddress){
    buttonStates.downButton = (lv_obj_t*) buttonddress;
}

void setEscButtonAddress(void *buttonddress){
    buttonStates.escButton = (lv_obj_t*) buttonddress;
}

void setEnterButtonAddress(void *buttonddress){
    buttonStates.enterButton = (lv_obj_t*) buttonddress;
}



#endif
static void AquaHMI_Init_Timer(void) {

    //setup count down variable

#if STM32L0XX
    runTask = RUN_TASK_MS;
    LL_TIM_InitTypeDef TIM_InitStruct;
    /* Enable the timer peripheral clock */

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);

    /* Configure the NVIC to handle TIM2 update interrupt */
    NVIC_SetPriority(TIM7_IRQn, 7);
    NVIC_EnableIRQ(TIM7_IRQn);

    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV2;
    /* Set the auto-reload value to have an initial update event frequency of 1000 Hz */
    TIM_InitStruct.Autoreload = __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM7), 1000);

    LL_TIM_Init(TIM7, &TIM_InitStruct);

    LL_TIM_SetClockSource(TIM7, LL_TIM_CLOCKSOURCE_INTERNAL);

    LL_TIM_ClearFlag_UPDATE(TIM7);

    /* Enable the update interrupt */
    LL_TIM_EnableIT_UPDATE(TIM7);
#endif

#if defined(STM32L1xx)
    LL_TIM_InitTypeDef TIM_InitStruct;
    /* Enable the timer peripheral clock */

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

    /* Configure the NVIC to handle TIM3 update interrupt */
    NVIC_SetPriority(TIM3_IRQn, 6);
    NVIC_EnableIRQ(TIM3_IRQn);

    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    /* Set the auto-reload value to have an initial update event frequency of 1000 Hz */
    TIM_InitStruct.Autoreload = __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM3), 1000);

    LL_TIM_Init(TIM3, &TIM_InitStruct);

    LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_INTERNAL);

    LL_TIM_ClearFlag_UPDATE(TIM3);

    /* Enable the update interrupt */
    LL_TIM_EnableIT_UPDATE(TIM3);
#endif

#if BGM13S32F512GA
    runTask = RUN_TASK_MS;

#endif
}


static void AquaHMI_Init_DisplayPWM(void) {

#if STM32L0XX
    LL_TIM_InitTypeDef TIM_InitStruct;
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM21);

    TIM_InitStruct.Prescaler = 0;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM21), 20000);     //0;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV4;

    LL_TIM_Init(TIM21, &TIM_InitStruct);

    LL_TIM_SetClockSource(TIM21, LL_TIM_CLOCKSOURCE_INTERNAL);

    LL_TIM_OC_EnablePreload(TIM21, LL_TIM_CHANNEL_CH1);

    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = (LL_TIM_GetAutoReload(TIM21) / 2);     //0;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    LL_TIM_OC_Init(TIM21, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

    LL_TIM_OC_DisableFast(TIM21, LL_TIM_CHANNEL_CH1);

    LL_TIM_SetTriggerOutput(TIM21, LL_TIM_TRGO_RESET);

    LL_TIM_DisableMasterSlaveMode(TIM21);

    /**TIM21 GPIO Configuration
     PD0     ------> TIM21_CH1
     */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);

    GPIO_InitStruct.Pin = TIM21_CH1_PWM_LCD_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(TIM21_CH1_PWM_LCD_GPIO_Port, &GPIO_InitStruct);

    /**********************************/
    /* Start output signal generation */
    /**********************************/
    /* Enable output channel 1 */
    LL_TIM_CC_EnableChannel(TIM21, LL_TIM_CHANNEL_CH1);
#ifdef LVGL_PC_SIM


#endif
    /* Enable counter */
    LL_TIM_EnableCounter(TIM21);

    /* Force update generation */
    LL_TIM_GenerateEvent_UPDATE(TIM21);
#endif

#if defined(STM32L1xx)
    LL_TIM_InitTypeDef TIM_InitStruct;
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;
    LL_GPIO_InitTypeDef GPIO_InitStruct;



    /* Configure the NVIC to handle TIM2 update interrupt */
    NVIC_SetPriority(TIM2_IRQn, 0);
    NVIC_EnableIRQ(TIM2_IRQn);

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

    /***************************/
    /* Time base configuration */
    /***************************/
    /* Set counter mode */
    /* Reset value is LL_TIM_COUNTERMODE_UP */
    //LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);

    /* Set the pre-scaler value to have TIM2 counter clock equal to 1 kHz */
    LL_TIM_SetPrescaler(TIM2, __LL_TIM_CALC_PSC(SystemCoreClock, 1000));

    /* Enable TIM2_ARR register preload. Writing to or reading from the         */
    /* auto-reload register accesses the preload register. The content of the   */
    /* preload register are transferred into the shadow register at each update */
    /* event (UEV).                                                             */
    LL_TIM_EnableARRPreload(TIM2);

    /* Set the auto-reload value to have a counter frequency of 100 Hz */
    LL_TIM_SetAutoReload(TIM2, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM2), 100));

    /*********************************/
    /* Output waveform configuration */
    /*********************************/
    /* Set output mode */
    /* Reset value is LL_TIM_OCMODE_FROZEN */
    LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH4, LL_TIM_OCMODE_PWM1);

    /* Set output channel polarity */
    /* Reset value is LL_TIM_OCPOLARITY_HIGH */
    LL_TIM_OC_SetPolarity(TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_LOW);

    /* Set compare value to half of the counter period (50% duty cycle ) */
    LL_TIM_OC_SetCompareCH1(TIM2, localHMIHandleStructPtr->pwm.green);
    LL_TIM_OC_SetCompareCH2(TIM2, localHMIHandleStructPtr->pwm.blue);
    LL_TIM_OC_SetCompareCH3(TIM2, localHMIHandleStructPtr->pwm.red);
    LL_TIM_OC_SetCompareCH4(TIM2, localHMIHandleStructPtr->pwm.backlight);

    /* Enable TIM2_CCR1 register preload. Read/Write operations access the      */
    /* preload register. TIM2_CCR1 preload value is loaded in the active        */
    /* at each update event.                                                    */
    LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH1);
    LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH2);
    //LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH3);
    // LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH4);

    /**************************/
    /* TIM2 interrupts set-up */
    /**************************/
    /* Enable the capture/compare interrupt for channel 1*/
    // LL_TIM_EnableIT_CC1(TIM2);


    /**********************************/
    /* Start output signal generation */
    /**********************************/


    /* Enable output channel 1 */
    LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH2);
    LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH3);
    LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH4);

    /* Enable counter */
    LL_TIM_EnableCounter(TIM2);

    /* Force update generation */
    LL_TIM_GenerateEvent_UPDATE(TIM2);
#endif

#if BGM13S32F512GA
    //    CMU_Select_TypeDef  clk_source = CMU_ClockSelectGet(cmuClock_TIMER1);

    uint32_t frq = CMU_ClockFreqGet(cmuClock_TIMER1);
    (void) frq;
    // Configure TIMER1 Compare/Capture for output compare
    // Use PWM mode, which sets output on overflow and clears on compare events
    TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;
    timerCCInit.mode = timerCCModePWM;
    TIMER_InitCC(TIMER1, 0, &timerCCInit);
    TIMER_InitCC(TIMER1, 1, &timerCCInit);
    TIMER_InitCC(TIMER1, 2, &timerCCInit);
    TIMER_InitCC(TIMER1, 3, &timerCCInit);

    // Route TIMER1 CC0 to location 4 and enable CC0 route pin

    TIMER1->ROUTELOC0 |= ( TIMER_ROUTELOC0_CC0LOC_LOC29 |TIMER_ROUTELOC0_CC1LOC_LOC29|TIMER_ROUTELOC0_CC2LOC_LOC29|TIMER_ROUTELOC0_CC3LOC_LOC25);
    TIMER1->ROUTEPEN |= ( TIMER_ROUTEPEN_CC0PEN | TIMER_ROUTEPEN_CC1PEN | TIMER_ROUTEPEN_CC2PEN | TIMER_ROUTEPEN_CC3PEN);


    // Set top value to overflow at the desired PWM_FREQ frequency
    TIMER_TopSet(TIMER1, CMU_ClockFreqGet(cmuClock_TIMER1) / 10000);

    // Set compare value for initial duty cycle
    TIMER_CompareSet(TIMER1, 0, (TIMER_TopGet(TIMER1) * localHMIHandleStructPtr->pwm.green) / 100);
    TIMER_CompareSet(TIMER1, 1, (TIMER_TopGet(TIMER1) * localHMIHandleStructPtr->pwm.blue) / 100);
    TIMER_CompareSet(TIMER1, 2, (TIMER_TopGet(TIMER1) * localHMIHandleStructPtr->pwm.red) / 100);
    TIMER_CompareSet(TIMER1, 3, (TIMER_TopGet(TIMER1) * (100-localHMIHandleStructPtr->pwm.backlight)) / 100);

    // Initialize the timer
    TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
    TIMER_Init(TIMER1, &timerInit);

    // Enable TIMER1 compare event interrupts to update the duty cycle
    TIMER_IntEnable(TIMER1, TIMER_IEN_CC0|TIMER_IEN_CC1|TIMER_IEN_CC2|TIMER_IEN_CC3);
    NVIC_EnableIRQ(TIMER1_IRQn);
#endif
}

#if BGM13S32F512GA
/**************************************************************************//**
 * @brief
 *    Interrupt handler for TIMER1 that changes the duty cycle
 *
 * @note
 *    This handler doesn't actually dynamically change the duty cycle. Instead,
 *    it acts as a template for doing so. Simply change the dutyCyclePercent
 *    global variable here to dynamically change the duty cycle.
 *****************************************************************************/
//void LED_PWM_IRQ_Handler(void)
void TIMER1_IRQHandler(void)
{
    // Acknowledge the interrupt
    uint32_t flags = TIMER_IntGet(TIMER1);
    TIMER_IntClear(TIMER1, flags);

    // Update CCVB to alter duty cycle starting next period
    // Set compare value for initial duty cycle
    if(localHMIHandleStructPtr->pwm.doRefresh){
        TIMER_CompareSet(TIMER1, 0, (TIMER_TopGet(TIMER1) * localHMIHandleStructPtr->pwm.green) / 100);
        TIMER_CompareSet(TIMER1, 1, (TIMER_TopGet(TIMER1) * localHMIHandleStructPtr->pwm.blue) / 100);
        TIMER_CompareSet(TIMER1, 2, (TIMER_TopGet(TIMER1) * localHMIHandleStructPtr->pwm.red) / 100);
        if(!localHMIHandleStructPtr->pwm.backlight){
            GPIO_PinModeSet(BACKLIGHT_Port,BACKLIGHT_Pin, gpioModeDisabled, 1);
        }else{
            GPIO_PinModeSet(BACKLIGHT_Port,BACKLIGHT_Pin, gpioModePushPull, 1);
            TIMER_CompareSet(TIMER1, 3, (TIMER_TopGet(TIMER1) * (100-localHMIHandleStructPtr->pwm.backlight)) / 100);
        }

        localHMIHandleStructPtr->pwm.doRefresh=0;
        NVIC_DisableIRQ(TIMER1_IRQn);
    }
}
#endif /* BGM13S32F512GA */

/**
 * @brief  Changes the duty cycle of the PWM signal.
 *         D = (T/P)*100
 *           where T is the pulse duration and P is the PWM signal period
 * @param  D Duty cycle
 * @retval None
 */


void AquaHMI_tick(void) {


    lv_timer_handler();


}

/************************ (C) COPYRIGHT Aquasant Messtechnik AG *****END OF FILE****/


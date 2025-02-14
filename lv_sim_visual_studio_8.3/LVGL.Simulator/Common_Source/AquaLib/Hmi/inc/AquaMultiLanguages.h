/*
 * AquaHMIText.h
 *
 *  Created on: 21.01.2019
 *      Author: Sch�rMa
 */

#ifndef AQUALIB_INC_AQUAMULTILANGUAGES_H_
#define AQUALIB_INC_AQUAMULTILANGUAGES_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>

#include <stdint.h>
#include "AquaHMI.h"
/**
 * @brief Enum to indicate available languages
 * @note "LAST_LANGUAGE" is terminator
 */

#define NUMBEROFLANGUAGES LAST_LANGUAGE_ENUM-LANGUAGE-1

typedef struct
{
	uint16_t const menuId;
#ifndef BGM13S32F512GA
    char*  name;                  /**< Parameter Name only on simulator for creationof scv file */
  #endif
	char const * const text[NUMBEROFLANGUAGES];	/**<Array of pointers to language-specific string */
} menuStringEntry_t;

/**
 * @brief Structure to hold  string (not language-specific
 */
typedef struct
{
	uint8_t const len;						/**<Maximum length */
	char const * const text[1];				/**<Array of pointers to uni-language string */
} UNI_STRING;

void setLanguageLocally(uint8_t selectedLanguage);
char  * getMenuOrParameterNameFromMenuDefinitions(STR stringId);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AQUALIB_INC_AQUAMULTILANGUAGES_H_ */

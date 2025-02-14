/*
 * AquaMultiLanguages.c
 *
 *  Created on: 1.7.2023
 *  Author: Daniel Ritter
 */
 /*********************
 *      INCLUDES
 *********************/

#include "../inc/AquaMultiLanguages.h"
#include "../inc/AquaHMI.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *  STATIC VARIABLES
 **********************/

static volatile uint8_t localLang;

/* Macro to create csv file definitions */
#ifndef BGM13S32F512GA
  #define ID(x) x ,#x
#else
  #define ID(x) x
#endif

static char smallBuffer[SMALLSTRINGSIZE];

static const menuStringEntry_t strings[] =
{
/* 
   {   ID,                             ENGLISH,                     FRENCH,                                      GERMAN,                          ITALIAN ,                                SPANISH,                                                   }},  */
    {    ID(MEASURMENT)                 ,{  "Messkonfiguration ",             "Mesure ",                                "Messung ",                     "Misura ",                              "Medida "                                                                 }},
    {    ID(BASE_SETUP)                 ,{  "Grundeinstellungen ",           "Configuration ",                           "Grundeinstellungen ",               "Configurazione ",                      "Configuración "                                                            }},
    {    ID(GUIDE                )      ,{  "Guided Config. ",          "Configuration guide ",                    "Geführte Konfig.",             "Configurazione guidata ",              "Configuración guiada "                                                     }},
    {    ID(PROBE                )      ,{  "Probe ",                   "Sonde ",                                   "Sonde ",                       "Sonda ",                               "Sonda "                                                                    }},
    {    ID(PROBESETTINGS        )      ,{  "Probe/Mode ",              "",                                         "Berechne",                     "",                                     ""                                                                          }},
    {    ID(TYPE                 )      ,{  "Type ",                    "Type ",                                    "Typ ",                         "Tipo ",                                "Tipo "                                                                      }},
    {    ID(PARAMETER            )      ,{  "Parameter ",               "Paramêtre ",                               "Parameter ",                   "Parametro ",                           "Parámetro "                                                                 }},
    {    ID(HF_CABLE             )      ,{  "HF-Cable ",                "Câble hf ",                                "HF-Kabel ",                    "Cavo HF ",                             "HF cable "                                                                  }},
    {    ID(LENGTH               )      ,{  "Length ",                  "Longueur ",                                "Lânge ",                       "Lunghezza ",                           "Longitud "                                                                  }},
    {    ID(COMPENSATION         )      ,{  "Compensation ",            "Componsation ",                            "Kompensation ",                "Compensazione ",                       "Compensaciân "                                                              }},
    {    ID(MODE                 )      ,{  "Mode ",                    "Mode ",                                    "Modus ",                       "Modo ",                                "Modo "                                                                      }},
    {    ID(LOWER_ADJ            )      ,{  "Lower point ",             "Valeur vide ",                             "Leer Messwert ",               "Valore vuoto ",                        "Medida vacia "                                                              }},
    {    ID(UPPER_ADJ            )      ,{  "Upper point ",             "Valeur pleine ",                           "Voll Messwert ",               "Valore pieno ",                        "Medida completa "                                                           }},
    {    ID(LOWER_THRES          )      ,{  "Lower threshold ",         "Distance de mesure en dessous ",           "Messabstand unten ",           "Distanza di misurazione sotto",        "Medicion abajo "                                                            }},
    {    ID(UPPER_THRES          )      ,{  "Upper threshold ",         "Distance de mesure ci-dessus ",            "Messabstand oben ",            "Distanza di misurazione sopra",        "Medicion arriba "                                                           }},
    {    ID(SERVICE              )      ,{  "Service ",                 "Service ",                                 "Service ",                     "Servizio",                             "Servicio "                                                                  }},
    {    ID(LOG                  )      ,{  "Log ",                     "File de enregistrement",                   "Log ",                         "File di registro ",                    "File de registro"                                                          }},
    {    ID(CALCULATE            )      ,{  "Calculate",                "",                                         "Berechne",                     "",                                     ""                                                                          }},
    {    ID(RANGE                )      ,{  "range",                    "",                                         "Bereich",                      "",                                     ""                                                                          }},
    {    ID(SYSTEM               )      ,{  "System ",                  "Système ",                                 "System ",                      "Sistema ",                             "Sistema "                                                                   }},
    {    ID(ACCESS               )      ,{  "Access ",                  "Accâs ",                                   "Zugang ",                      "Accesso",                              "Acceso "                                                                    }},
    {    ID(LOCK                 )      ,{  "Lock ",                    "Bloquer ",                                 "Sperren ",                     "Bloccare ",                            "Bloquear "                                                                  }},
    {    ID(UNLOCK               )      ,{  "Unlock ",                  "Dâbloquer ",                               "Entsperren  ",                 "Sbloccare ",                           "Desbloquear "                                                               }},
    {    ID(SET_DEVICE_KEY       )      ,{  "Set device key ",          "Mettre clé de dispositif ",                "Geräte Schlüssel setzen ",     "Mettere chiave dispositivo ",          "Poner llave dispositivo "                                                  }},
    {    ID(DEL_DEVICE_KEY       )      ,{  "Del. device key ",         "Effacer clé de dispositif ",               "Geräte Schlüssel léschen ",    "Cancellare chiave dispositivo ",       "Borrar llave dispositivo "                                                 }},
    {    ID(SET_CONFIG_KEY       )      ,{  "Set config. key ",         "Mettre clé de configuration ",             "Konfig. Schlüssel setzen ",    "Mettere chiave di configurazione ",    "Poner llave configuratión "                                                }},
    {    ID(DEL_CONFIG_KEY       )      ,{  "Del. config. key ",        "Effacer clé de configuration",             "Konfig. Schlüssel löschen ",   "Cancellare chiave di configurazione ", "Borrar llave configuratión "                                               }},
    {    ID(FACTORY_UNLOCK       )      ,{  "Service unlock ",          "Débloquer service",                        "Service entsperren ",          "Sbloccare servizio ",                  "Desbloquear servicio "                                                     }},
    {    ID(FACTORY_LOCK         )      ,{  "Service lock ",            "Bloquer service ",                         "Service sperren ",             "Bloccare servizio ",                   "Bloquear servicio "                                                        }},
    {    ID(LANGUAGE             )      ,{  "Language ",                "Langue",                                   "Sprache ",                     "Lingua ",                              "Idioma "                                                                   }},
    {    ID(OPTIONS              )      ,{  "Options ",                 "Option ",                                  "Optionen ",                    "Opzioni ",                             "Opciònes "                                                                     }},
    {    ID(ADD_OPTION_KEY       )      ,{  "Add option key ",          "Métre clé option ",                        "OptionsSchlüssel eingeben ",   "Mettere chiave opzioni ",              "Entrar llave opciòn "                                                      }},
    {    ID(ADD_OPTION           )      ,{  "Add option ",              "Métre option ",                            "Option hinzufégen",            "Aggiungere opzioni ",                  "Aéadir opciòn "                                                            }},
    {    ID(REMOVE_OPTION        )      ,{  "Remove option ",           "Supprimer l'option  ",                     "Option entfernen",             "Togliere opzioni ",                    "Eliminar opciòn "                                                          }},
    {    ID(DISPLAY              )      ,{  "Display ",                 "Écran ",                                  "Messwert Anzeigen ",                     "Schermo ",                             "Visualizaciòn "                                                            }},
    {    ID(DEFAULT_SCREEN       )      ,{  "Maindisplay  ",           "Affichage principal ",                     "Hauptanzeige ",               "Visualizz. principale ",                "Pantalla principal "                                                             }},
    {    ID(BACKLIGHT            )      ,{  "Back light ",              "Éclairage ",                               "Beleuchtung ",                 "Illuminazione ",                       "Iluminaciòn "                                                          }},
    {    ID(CONTRAST             )      ,{  "Contrast ",                "Contraste ",                               "Kontrast ",                    "Contrasto ",                           "Contraste "                                                            }},
    {    ID(CONNECTIVITY         )      ,{  "Connectivity ",            "Connectivité ",                            "Konnektivitét ",               "Connetivté",                           "Conectividad "                                                             }},
    {    ID(PULSE_MOD            )      ,{  "Pulse modulation ",        "Modulation d'impulsion",                   "Puls-Modulation ",             "Modulazione d'impulso ",               "Modulacién de impulsos "                                                           }},
    {    ID(PULSE_MOD_EN         )      ,{  "Enable ",                  "Activer ",                                 "Aktivieren ",                  "Attivare ",                            "Activar "                                                          }},
    {    ID(LOWER_PULSE_COUNT    )      ,{  "Lower pulse value ",       "Valeur de modulation inférieure ",         "Unterer mod. Wert ",           "Valore dell'impulso inferiore ",       "Menor valor de pulso "                                                             }},
    {    ID(UPPER_PULSE_COUNT    )      ,{  "Upper pulse value ",       "Valeur de modulation supérieure ",         "Oberer mod. Wert ",            "Valore dell'impulso superiore",        "Major valor de pulso "                                                             }},
    {    ID(MAX_PULSE_VALUE      )      ,{  "Max pulse value ",         "Valeur de modulation maximale ",           "Max. mod. Wert ",              "Valore dell'impulso massiomo",         "Méximo valor de pulso "                                                            }},
    {    ID(LED                  )      ,{  "Signal led ",              "Signal led ",                              "Signal Led ",                  "Segnale led ",                         "Seéal led "                                                            }},
    {    ID(LED_EN               )      ,{  "Enable ",                  "Activer ",                                 "Aktivieren ",                  "Attivare ",                            "Activar "                                                          }},
    {    ID(BRIGHTNESS           )      ,{  "Brightness ",              "Luminosité ",                              "Helligkeit ",                  "Luminosité ",                          "Luminosidad "                                                          }},
    {    ID(SERIAL               )      ,{  "Serial ",                  "En série ",                                "Seriell",                      "Seriale ",                             "De serie "                                                             }},
    {    ID(SERIAL_EN            )      ,{  "Enable ",                  "Activer ",                                 "Aktivieren ",                  "Attivare ",                            "Activar "                                                          }},
    {    ID(TIMEOUT              )      ,{  "Timeout ",                 "Timeout",                                  "Timeout",                      "Timeout",                              "Timeout"                                                           }},
    {    ID(DISPLAYLINE_1        )      ,{  "Line 1",                   "Ligne 1",                                   "Zeile 1",                       "Linea 1",                               "Línea 1"                                                            }},
    {    ID(DISPLAYLINE_2        )      ,{  "Line 2",                   "Ligne 2",                                   "Zeile 2",                       "Linea 2",                               "Línea 2"                                                            }},
    {    ID(DISPLAYLINE_3        )      ,{  "Line 3",                   "Ligne 3",                                   "Zeile 3",                       "Linea 3",                               "Línea 3"                                                            }},
    {    ID(SIGNALCONFIG         )      ,{  "Signaleinstellungen",           "",                                   "",                       "",                               ""                                                            }},
    {    ID(SELECTCONFIG         )      ,{  "Konfiguration wählen",          "", "", "", "" }},
    {    ID(CONFIGNOTDELETED         )      ,{"Konfiguration aktiv, \nlöschen nicht \nmöglich",          "", "", "", "" }},
    {    ID(EXECUTEDELETE         )      ,{"Konfiguration gelöscht",          "", "", "", "" }},
    {    ID(ARCHIVEX         )      ,{  "NeuCHECK ",          "", "", "", "" }},
    {    ID(NAMEFORNEWMEDIUM         )      ,{  "Neu ",          "", "", "", "" }},

    {    ID(CONFIGURATIONX         )      ,{  "1.Inbetriebnahme",          "", "", "", "" }},
    {    ID(CONFIGUSER           )      ,{  "UserConfig",          "", "", "", "" }},
    {    ID(MAINTENANCE          )      ,{  "Maintenance ",             "Entretien ",                               "Wartung ",                     "Manutenzione ",                        "Mantenimiento "                                                            }},
    {    ID(RESTART              )      ,{  "Restart ",                 "Redémarrage ",                             "Neustart ",                    "Ripristino ",                          "Reiniciar "                                                            }},
    {    ID(SELF_TEST            )      ,{  "Self test ",               "Test de controle ",                        "Selbsttest ",                  "Test di controllo ",                   "Autocomprobacién "                                                             }},
    {    ID(FACTORYRESET         )      ,{  "Factory Reset ",           "Réinitialiser ",                           "Werksreset ",                "Risettare ",                           "Regreso "                                                          }},
    {    ID(PROBESERIALNUMBER            )      ,{  "Serienummer"                "",                                         "",                       "",                               ""                                                            }},
    {    ID(PROBETYPE            )      ,{  "Sondentyp"                "",                                         "",                       "",                               ""                                                            }},
    {    ID(PROBEZEROPOINT            )      ,{  "0-Punkt"                "",                                         "",                       "",                               ""                                                            }},
    {    ID(PROBEFULLPOINT            )      ,{  "Produktmesswert 100%"                "",                                         "",                       "",                               ""                                                            }},
    {    ID(AMTBRESET            )      ,{  "AMTB Reset "                "",                                         "",                       "",                               ""                                                            }},
    {    ID(SENSORSERIALNUMBER            )      ,{  "Serienummer"                "",                                         "",                       "",                               ""                                                            }},

    {    ID(FW_UPGRADE           )      ,{  "Firmware upgrade ",        "Mise ü niveau du firmware ",               "FW aktualisierung ",           "Attualizzare firmware ",               "Actualizaciün firmware "                                                           }},
    {    ID(WIPE_DEV             )      ,{  "Wipe device ",             "Réinitialiser l'appareil ",                "Gerät reinitialisieren ",      "Reinizializzare  ",      "Inicializar  "                                                          }},
    {    ID(BLANK_DEV            )      ,{  "",                         "",                                         "",                             "",                                     ""                                                          }},
    {    ID(DEVICE_INFO          )      ,{  "Device info",              "Informations ",             "Geräte Info",                  "Informazione",                         "Informacion "                                                           }},
    {    ID(AQUA_QR              )      ,{  "AQUA-QR ",                 "AQUA-QR ",                                 "AQUA-QR ",                     "AQUA-QR ",                             "AQUA-QR "                                                  }},
    {    ID(CONTACT              )      ,{  "Contact ",                 "Contacte ",                                 "Kontakt ",                     "Contatto ",                            "Contacto "                                                         }},
    {    ID(SETTINGS             )      ,{  "Settings ",                "Settings",                                "Einstellungen ",                "Impostazioni ",                       "Ajustes"                                                                     }},
    {    ID(DISABLED             )      ,{  "Disabled",                 "Désactivé",                           "Disattivato",                  "Desactivado",                    "Disabled"                                                                  }},
    {    ID(BACK                 )      ,{  "Back ",                    "Retour ",                             "Zurück ",                      "Ritorno ",                       "Regreso "                                                                 }},
    {    ID(NEXT                 )  ,{  "Next ",                        "Suivant ",                            "Weiter ",                      "Next ",                          "Next "                                                                 }},
    {    ID(UP                   )      ,{  "Up ",                       "Êlevé ",                                  "Hoch ",                        "Alto ",                          "Alta "                                                                   }},
    {    ID(DOWN                 )      ,{  "Down ",                    "Bas ",                                "Hinunter",                      "Giù ",                            "Abajo "                                                                 }},
    {    ID(ENTER                )      ,{  "OK ",                   "OK ",                             "Ok ",                     "Ok ",                        "Ok "                                                                    }},
    {    ID(SELSECT              ) ,{  "OK ",                  "OK ",                                 "Ok ",                     "Ok ",                       "Ok  "                                                                   }},
    {    ID(MENU                 )  ,{  "Menu ",                    "Menu ",                                   "Menu ",                        "Menú ",                            "Menu "                                                                 }},
    {    ID(QUIT                 )  ,  {  "Quit ",                    "Sortie ",                                 "Uscire ",                      "Salida ",                          "Quit "                                                                 }},
    {    ID(SYSTEMPW)            , { "Freigabe Passwort", "", "", "", "" }},

    {    ID(FIRSTDATE           ), { "Inbetriebnahmedatum", "", "", "", "" }},
    {    ID(CURRENTTAG          ) ,  { "Tag-Nummer", "", "", "", "" }},
    {    ID(ZEROADJUST          ) ,  { "0% Punkt", "", "", "", "" }},
    {    ID(ZEROADJUSTINFO      ) ,  { "Für Stab / Rohrsonden\nleer/sauber\n 4mA / 0% Punkt", "", "", "", "" }},
    {    ID(ZEROVALUEMA         ) ,   { "0% Punkt", "", "", "", "" }},
    {    ID(TOPADJUST           ) , { "100% Punkt", "", "", "", "" }},
    {    ID(TOPADJUSTINFO       ) ,  { "Füllen wässrige Phase\nMessspanne\n 20mA / 100% Punkt", "", "", "", "" }},
    {    ID(TOPFULLMA           ) , { "20 mA/100%", "", "", "", "" }},
    {    ID(ADDTO20MAVALUE) , { " + 20mA Wert", "", "", "", "50" }},
    {    ID(EDITPASSWORDINFO    ),         { "eingeben.", "", "", "", "" }},
    {    ID(MASIMULATION     )  ,   { "mA Signal Simulation", "", "", "", "" }},
    {    ID(MASIMULATIONVALUE   ) ,    { "mA Simulation", "", "", "", "" }},
    {    ID(ANALOGSIGNALSPREAD   ),   { "Spreizung 4mA/20mA", "", "", "", "" }},
    {    ID(ANALOGSIGNALSPREAD04MA ),  { "Spreizung 4mA", "", "", "", "" }},
    {    ID(ANALOGSIGNALSPREAD20MA ), { "Spreizung 20 mA", "", "", "", "" }},
    {    ID(CHOOSEAPP        ),      { "Applikation",  "","","",""           }},
    {    ID(FIRSTOPERATION    )  ,   { "Erstinbetriebnahme ?", "","","",""           }},
    {    ID(EDIT0MA      ),         { "0mA Signal ",  "","","",""           }},
    {    ID(EDIT20MA      ),        { "20mA Signal",  "","","",""           }},
    {    ID(RUNFIRSTOPERATION     ) ,        { "Ja",  "","","",""           }},
    {    ID(SKIPFIRSTOPERATION      ),        { "Nein",  "","","",""           }},
    {    ID(DELETECONFIG )     ,        { "Löschen",  "","","",""           }},
    {    ID(LISTCONFIGPARAS)     ,        { "Zusammenfassung",  "","","",""           }},

    {    ID(NODELETEFIRST )     ,        { "Löschen nicht möglich",  "","","",""           }},
    {    ID(SAVEFIRSTCONFIGCONFIRM )     ,        { "Konfiguration Speichern",  "","","",""           }},
    {    ID(SAVEABORT    )  ,        { "Nicht speichern",  "","","",""           }},
    {    ID(STOREDINFO    )  ,        { "Speicherung ",  "","","",""           }},
    {    ID(MISSINGBUTTONACTION    )  ,        { "Missing Action!",  "","","",""           }},
    {    ID(ENDOFRUNFIRST )     ,        { "Erstinbetriebnahme ",  "","","",""           }},
    {    ID(MEASVALUNITS  )    ,        { "Einheiten",  "","","",""           }},

    {    ID(SELECTUSER ) ,             { "Benutzer Auswahl",  "","","",""           }},
    {    ID(SYSTEMUSER ) ,             { "Systembenutzer",  "","","",""           }},
    {    ID(AMTBUSER  ),              { "AMTB",  "","","",""           }},
    {    ID(PUBLICUSER  ),             { "Nicht eingeloggt",  "","","",""           }},

    {    ID(LOGIN ),      { "Login",  "","","",""           }},
    {    ID(LOGINPROCESS ),      { "Login",  "","","",""           }},

    {    ID(PASSWORDINVALID ),      { "Passwort ungültig",  "","","",""           }},
    {    ID(PASSWORDVALID ),      { "Passwort gültig",  "","","",""           }},
    {    ID(CHANGEPASSWORD ),      { "Passwort ändern",  "","","",""           }},
    {    ID(NEWPASSWORDENTRY ),      { "Neues Password ",  "","","",""           }},
    {    ID(NEWPASSWORDVERIFY ),      { "Neues Password verifizieren",  "","","",""           }},
    {    ID(NEWPASSWORDOK ),      { "Neues Password OK",  "","","",""           }},
    {    ID(NEWPASSWORDNOTOK ),      { "Neues Passwort falsch",  "","","",""           }},

    {    ID(SENSORDATA ),      { "Sensordaten",  "","","",""           }},
    {    ID(PROBEDATA ),      { "Sondendaten",  "","","",""           }},
    {    ID(PASSWORDENTRYVALUE ),      { "Passwort Eingabe",  "","","",""           }},
    {    ID(EXPECTAMTBPASSWORD ),      { "AMTB Passwort",  "","","",""           }},
    {    ID(EXPECTSYSPASSWORD ),      { "Freigabe Passwort",  "","","",""           }},

    {    ID(ACTUALVALUELABEL ),      { "Aktuell",  "","","",""           }},
    {    ID(FIRSTCONFIGSTORED ),      { "Erstkonfiguration\nGespeichert",  "","","",""           }},
    {    ID(STOREDVALUELABEL ),      { "Gespeichert",  "","","",""           }},
    {    ID(NOTSTOREDVALUELABEL ),      { "Abgebrochen",  "","","",""           }},
    {    ID(SELECTEDVALUE ) ,             { "Aktuelle",  "","","",""           }},
    {    ID(LOGO_SCREEN ) ,             { "",  "","","",""           }},
    {    ID(OKTAKEOVERINFO ) ,             { "OK = Übernahme",  "","","",""           }},


    {    ID(ACTIVEERROR ) ,             { "Fehler aktiv",  "","","",""           }},

    {    ID(CONTINUETONEXT ) ,             { "OK = Weiter",  "","","",""           }},

    {  ID(ENGLISH) ,   {"English"   ,"","","",""            }},
    {  ID(FRENCH) ,   {"Français"   ,"","","",""            }},
    {  ID(GERMAN ),   {"Deutsch"   ,"","","",""            }},
    {  ID(ITALIAN ),   {"Italiano"   ,"","","",""            }},
    {  ID(SPANISH ),   {"Español"   ,"","","",""            }},
    {  ID(MTI10   ) ,{"MTI 10 "         ,"","","",""           }},
    {  ID(MTI20   ) ,   {"MTI 20 "          ,"","","",""           }},
    {  ID(MTI30   ) ,   {"MTI 30 "          ,"","","",""           }},
    {  ID(MTI50   ) ,   {"MTI 50 "          ,"","","",""           }},
    {  ID(MTI100  ) ,   {"MTI 100 "         ,"","","",""           }},
    {  ID(MTI200  ) ,   {"MTI 200 "         ,"","","",""           }},
    {  ID(MTI400  ) ,   {"MTI 400 "         ,"","","",""           }},
    {  ID(MTI600  ) ,   {"MTI 800 "         ,"","","",""           }},
    {  ID(MTI_FULL) ,   {"MTI FULL "        ,"","","",""           }},
    {  ID(BATCH   ) ,   {"BATCH "           ,"","","",""           }},
    {  ID(EXT_TEMP) ,   {"EXT. TEMP "       ,"","","",""           }},
    {  ID(NOSTRING) ,   {""                 ,"","","",""           }},
    {  ID(TSS80   ) ,   {"TSS80 "           ,"","","",""           }},
    {  ID(TSS90   ) ,   {"TSS90 "           ,"","","",""           }},
    {  ID(STM  ),   {"STM "                 ,"","","",""            }},
    {  ID(HG100   ) ,   {"HG100 "           ,"","","",""                }},
    {  ID(FRGL ),   {"FRGL "                ,"","","",""            }},
    {  ID(STL  ),   {"STL "                 ,"","","",""            }},
    {  ID(BAUDRATE ),   {"BAUDRATE "        ,"","","",""            }},
    {  ID(DATA_BITS  )  ,   {"DATA BITS "   ,"","","",""            }},
    {  ID(STOP_BITS  )  ,   {"STOP BITS "   ,"","","",""            }},
    {  ID(PARITY  ) ,   {"PARITY "          ,"","","",""            }},
    {  ID(CTS_RTS ) ,   {"CTS/RTS "         ,"","","",""            }},
    {  ID(UNITS_NONE),{"None"               ,"","","",""            }},
    {  ID(UNIT_MA  ),   {"mA"              ,"","","",""            }},
    {  ID(UNIT_PERCENT  ),   {"%"              ,"","","",""        }},
    {  ID(UNIT_RAW  ),   {"raw"               ,"","","",""            }},
    {  ID(UNIT_pF  ),   {"pF"               ,"","","",""            }},
    {  ID(UNIT_MM  ),   {"mm"               ,"","","",""            }},
    {  ID(UNIT_CM  ),   {"cm"               ,"","","",""            }},
    {  ID(UNIT_M   ),   {"m"                ,"","","",""            }},
    {  ID(UNIT_LITER   ),   {"l"            ,"","","",""            }},
    {  ID(UNIT_M3METER  ),   {"m3"   ,"","","",""            }},
    {  ID(UNIT_MILLILITER  ),   {"ml"   ,"","","",""            }},


    {  ID(APPBATCH ),   {"Batch"            ,"","Batch","",""               }},
    {  ID(APPBATCHADAPTIVE ),   {"Batch-Adaptiv"    ,"","Batch-Adaptiv","",""           }},
    {  ID(APPCONT  ),   {"Kontinuierlich"       ,"","Kontinuierlich","",""              }},
    {  ID(DEVICE_DATA),   {"Gerätedaten"          ,"","","",""                }},
    {  ID(DEVICENAME   ),   {"Gerätebezeichnung"          ,"","","",""                }},
    {  ID(APPLICATION  ),   {"Applikation"          ,"","","",""                }},
    {  ID(SOFTWAREVERSION  ),   {"Software Version"          ,"","","",""                }},
    {  ID(HARDWAREVERSION  ),   {"Hardware Version"          ,"","","",""                }},
    {  ID(PROOFDATE    ),   {"Prüfdatum"            ,"","","",""                }},
    {  ID(QRMANUAL     ),   {"QR-Manual"            ,"","","",""                }},
    {  ID(QRDOCS   ),   {"QR-Ex Dokumente"          ,"","","",""                }},
    {  ID(MEASCONFIG   ),   {"Messkonfiguration"            ,"","","",""                }},
    {  ID(CHOOSEMEASCONFIG),    {"Aktivieren"            ,"","","",""                }},
    {  ID(EDITCONFIG),    {"Bearbeiten"            ,"","","",""                }},
    {  ID(NEWCONFIG),    {"Neu"            ,"","","",""                }},
    {  ID(CONFIGACTION),    {"Bearbeiten"            ,"","","",""                }},
    {  ID(APPLYCONFIG),    {"Verwenden"            ,"","","",""                }},
    {  ID(CONFIGRENAME),    {"Umbenennen"            ,"","","",""                }},
    {  ID(COPYCONFIG),    {"Kopieren"            ,"","","",""                }},
    {  ID(NAMEFORNEWCONFIG),    {"Neu"            ,"","","",""                }},
    {  ID(CONFIGCOPIEDNAME),    {"Neue Kopie"            ,"","","",""                }},
    {  ID(CONFIGCOPIED),    {"Kopieren erfolgreich"            ,"","","",""                }},
    {  ID(CONFIGNOTCOPIED),    {"Kopieren nicht\n möglich"            ,"","","",""                }},

    {  ID(ARCHIVE    ),   {"Archiv"            ,"","","",""                }},
    {  ID(MEDIUMNAME    ),   {"Mediumname"            ,"","","",""                }},
    {  ID(MEDIUMCOPIEDNAME),    {"Neue Kopie"            ,"","","",""                }},
    {  ID(   MEDIUMDELETE           ),    {"Löschen"            ,"","","",""                }},
    {  ID(   MEDIUMEDIT          ),    {"Bearbeiten"            ,"","","",""                }},
    {  ID(   MEDIUMRENAME          ),    {"Umbenennen"            ,"","","",""                }},

    {  ID(   ITEMNOTDELETED          ),    {"Nicht gelöscht"            ,"","","",""                }},
    {  ID(SIGNALFILTER     ),   {"Signalfilter"         ,"","","",""                }},
    {  ID(DEVICECONFIG     ),   {"Gerätekonfiguration"          ,"","","",""}},
    {  ID(OUTPUT),    {"Ausgang" ,"","","",""                }},
    {  ID(FAILSAFESTATE), {"Fehlerzustand"          ,"","","",""                }},
    {  ID(LOWSTATE),    {"3.6mA" ,"","","",""                }},
    {  ID(HIGHSTATE),    {"22.5mA"          ,"","","",""                }},
    {  ID(FWUPDATE),    {"Firmware update"          ,"","","",""                }},
    {  ID(PCCONNECTION),    {"PCVerbindung-Baudrate"            ,"","","",""                }},
    {  ID(BAUDRATE192), {"19200"            ,"","","",""                }},
    {  ID(BAUDRATE115), {"115200"           ,"","","",""                }},
    {  ID(CODEUSEDSIZE), {"Codesize"           ,"","","",""                }},
    {  ID(RAMUSEDSIZE), {"Ram Size"           ,"","","",""                }},
    {  ID(STARTUPDATE), {"Update starten"           ,"","","",""                }},

    {    ID(ERROR_HANDLING       )      ,{  "Error Handling ",          "Traitement d'erreur ",                     "Fehler Behandlung ",           "Trattamento di errore ",               "Tratamiento de error"                                                          }},
    {  ID(EH_0001), {"0001 Kein Sensor"      "","","",""                }},
    {  ID(EH_0002), {"0002 Wartung fällig"      "","","",""                }},
    {    ID(EH_OVERFLOW_MEAS     )      ,{  "0101 Meas.overflow ",      "","","",""                }},
    {    ID(EH_UNDERFLOW_MEAS    )      ,{  "0102 Meas.underflow ",      "","","",""                }},
    {    ID(EH_UNDERFLOW_MOD     )      ,{  "0102 Mod. underflow ",      "","","",""                }},
    {    ID(EH_OVERFLOW_MOD      )      ,{  "0103 Mod. overflow ",            "","","",""                }},
    {    ID(EH_LOW_TEMP          )      ,{  "0201 Temp. too low ",        "","","",""                }},
    {    ID(EH_HIGH_TEMP         )      ,{  "0202 Temp. too high ",       "","","",""                }},
    {    ID(EH_PORBE_OPEN        )      ,{  "0203 Probe open ",               "","","",""                }},
    {    ID(EH_PROBE_SHORT       )      ,{  "0204 Probe short ",              "","","",""                }},
    {    ID(EH_PROBE_OUT_OF_RANGE)        ,{  "0205 Out Of Range",     "","","",""                }},
    {    ID(EH_CONFIG_INVALID    )      ,{  "0206 Invalid config. ",          "","","",""                }},
    {    ID(EH_DATA_INVALID      )      ,{  "0206 Invalid data ",             "","","",""                }},
    {    ID(EH_FW_ERR            )      ,{  "0206 Firmware error ",           "","","",""                }},
    {    ID(EH_HW_ERR            )      ,{  "0206 Hardware error ",           "","","",""                }},


};

static uint32_t sizeOfStringEntries = (uint32_t)(sizeof(strings)/sizeof(menuStringEntry_t));

static const UNI_STRING error_string[(1)]={{ 0  , {"error "     }},};

/**********************
 *  STATIC PROTOTYPES
 **********************/
/**
 * @brief Find the index in the menudefinition table to a given menu
 * @param lang language to set
 */
static uint16_t findStringIndex(uint16_t stringId){
    uint16_t index=0;
    uint16_t sizeOfStringEntries = sizeof(strings)/sizeof(menuStringEntry_t);
    if (stringId<LAST_STR){
        while (index<sizeof(strings)/sizeof(menuStringEntry_t)){
            if (strings[index].menuId==stringId)
              return index;
            index++;
        }
    }
    else
        return LAST_STR;
}


/**
 * @brief This function returns a pointer to the requested string id / selected language
 * @param stringId string id
 * @return pointer to the string
 */
char  * getMenuOrParameterNameFromMenuDefinitions(STR stringId){
    uint16_t stringIndex= findStringIndex(stringId);
    uint8_t stringDefinitionFound = 0;
    char * buffer = &smallBuffer;

    uint8_t localLanguage;

    localLanguage = getParameterValueAsInt(LANGUAGE);
    if ((stringIndex >= sizeOfStringEntries) || (localLanguage >= NUMBEROFLANGUAGES)){
        sprintf(buffer,"String ID #%i",(uint16_t) stringId);
    }
    else if (strings[stringIndex].text != NULL) {
        if (strlen(strings[stringIndex].text[localLanguage])==0)
            buffer = strings[stringIndex].text[0];
        else
            buffer = strings[stringIndex].text[localLanguage];
    }
    else {
        buffer = 0;
        sprintf(buffer,"String ID #%i",(uint16_t) stringId);
    }
    return buffer;
}

static char* generateTranlationFile = "stringsToTranslate.csv";

void writeLanguageStringsAsCsvFile()
{
#ifndef BGM13S32F512GA
#endif
}


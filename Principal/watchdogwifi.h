/*========================================================================*/
/* NOM DU FICHIER  : watchdogwifi.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/12/2010                                           */
/* Libelle         : Principal: gestion de la surveillance wifi			  */
/* Projet          : WRM100                                               */
/* Indice          : BE065                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE047 01/12/2010 CM
// - CREATION
//BE065.0 14/03/2012 (CM)
// - Correction bug inactivité Quelque soit le mode de sécurité
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _WATCHDOGWIFI
#define _WATCHDOGWIFI_EXT
#else
#define _WATCHDOGWIFI_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Watchdog_Wifi
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 01/12/2010 -
// Description	: Surveillance Wifi
//=====================================================================================
void Watchdog_Wifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//d: BE065.0 27/03/2012 (CM) - Correction bug inactivité station
//=====================================================================================
// Fonction		: Watchdog_ActivityWifi
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 01/12/2010 -
// Description	: Signal activité Wifi à l'AP
//=====================================================================================
void Watchdog_ActivityWifi(S_STRUCT_CONFIGURATION *loc_ps_config);
//f: BE065.0 27/03/2012 (CM) - Correction bug inactivité station

//=====================================================================================
// Fonction		: InitModule_WatchdogWifi
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/12/2010 -
// Description	: Initialisation du module de watchdogwifi
//=====================================================================================
void InitModule_WatchdogWifi(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/



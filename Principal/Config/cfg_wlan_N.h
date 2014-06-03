/*========================================================================*/
/* NOM DU FICHIER  : cfg_wlan_N.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 15/09/2010                                           */
/* Libelle         : Principal: Configuration du Wifi (N)				  */
/* Projet          : WRM100                                               */
/* Indice          : BE059                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 15/09/2010 CM
// - CREATION
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
// - Integration des paramètres handoff
//BE047 29/11/2010 CM
// - Correction configuration du paramètre bmiss (handoff)
//	uniquement prise en compte suite à un "ifconfig ath0 up"
//BE049 08/12/2010 CM
// - Correction configuration du paramètre bmiss (handoff)
//	annule correction faite dans BE047
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_WLAN_N
#define _CFG_WLAN_N_EXT
#else
#define _CFG_WLAN_N_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/


/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: WlanN_Install_Wifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Installe la configuration du wifi (basic)
//=====================================================================================
void WlanN_Install_Wifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: WlanN_Install_Handoff
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 12/10/2010 -
// Description	: Installe la configuration du handoff
//=====================================================================================
void WlanN_Install_Handoff(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: WlanN_Install_AdvWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Installe la configuration du advwifi (avancé et antennes)
//=====================================================================================
void WlanN_Install_AdvWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: WlanN_Install_FrequenceWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Installe la configuration du wifi (fréquence)
//=====================================================================================
void WlanN_Install_FrequenceWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: WlanN_Get_ListFrequency
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/10/2010 -
// Description	: Récupère la liste des fréquences réglementaires
//=====================================================================================
void WlanN_Get_ListFrequency(void);

//=====================================================================================
// Fonction		: WlanN_Install_ModeRSSI
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 17/02/2011 -
// Description	: Installe la configuration du mode RSSI
//=====================================================================================
void WlanN_Install_ModeRSSI(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_Wlan_N
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Initialisation du module de cfg_wlan_N
//=====================================================================================
void InitModule_Cfg_Wlan_N(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

const s8sod *ISO3166_COUNTRY_CODE[NB_MAX_COUNTRY_ID];
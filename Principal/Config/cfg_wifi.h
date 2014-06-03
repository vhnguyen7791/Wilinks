/*========================================================================*/
/* NOM DU FICHIER  : cfg_wifi.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 12/11/2009                                           */
/* Libelle         : Principal: Configuration du Wifi					  */
/* Projet          : WRM100                                               */
/* Indice          : BE032                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE021 24/03/2010 CM
// - Correction BUG liaison bridge-bridge
//BE032 16/06/2010 CM
// - Correction commande iwconfig 'txpower' (Wifi) repasse au maximum sur A/M ou sur down/up interface Wifi
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_WIFI
#define _CFG_WIFI_EXT
#else
#define _CFG_WIFI_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_SecuriteWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration de la sécurité wifi
//=====================================================================================
void Install_SecuriteWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_SecuriteWifi
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Désinstalle la configuration de la sécurité wifi
//=====================================================================================
void Uninstall_SecuriteWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_WdsWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 25/03/2010 -
// Description	: Installe la configuration du wifi (wds) 
//=====================================================================================
void Install_WdsWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_FrequenceWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du wifi (fréquence)
//=====================================================================================
void Install_FrequenceWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_TxPowerWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 16/06/2010 -
// Description	: Installe la configuration du wifi (puissance)
//=====================================================================================
void Install_TxPowerWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_Wifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du wifi (basic, avancé et antennes)
//=====================================================================================
void Install_Wifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_Wifi
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Désinstalle la configuration du wifi
//=====================================================================================
void Uninstall_Wifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_AdvWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du advwifi (avancé et antennes)
//=====================================================================================
void Install_AdvWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_Wifi
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/11/2009 -
// Description	: Initialisation du module de cfg_wifi
//=====================================================================================
void InitModule_Cfg_Wifi(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


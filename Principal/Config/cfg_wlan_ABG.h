/*========================================================================*/
/* NOM DU FICHIER  : cfg_wlan_ABG.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 15/09/2010                                           */
/* Libelle         : Principal: Configuration du Wifi (ABG)				  */
/* Projet          : WRM100                                               */
/* Indice          : BE056                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 15/09/2010 CM
// - CREATION
//BE056 18/01/2011 CM
// - Ajout limitation de la bande de fréquence aux canaux ETSI non DFS pour WRM100-ABG
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_WLAN_ABG
#define _CFG_WLAN_ABG_EXT
#else
#define _CFG_WLAN_ABG_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: WlanABG_Install_Wifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du wifi (basic)
//=====================================================================================
void WlanABG_Install_Wifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: WlanABG_Install_AdvWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du advwifi (avancé et antennes)
//=====================================================================================
void WlanABG_Install_AdvWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: WlanABG_Install_FrequenceWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du wifi (fréquence)
//=====================================================================================
void WlanABG_Install_FrequenceWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: WlanABG_Get_ListFrequency
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 18/01/2011 -
// Description	: Récupère la liste des fréquences réglementaires
//=====================================================================================
void WlanABG_Get_ListFrequency(void);

//=====================================================================================
// Fonction		: InitModule_Cfg_Wlan_ABG
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Initialisation du module de cfg_wlan_ABG
//=====================================================================================
void InitModule_Cfg_Wlan_ABG(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


/*========================================================================*/
/* NOM DU FICHIER  : wifi_ABG_tools.h		                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 14/09/2010                                           */
/* Libelle         : Module commun à plusieurs process (gérant Wifi ABG)  */
/* Projet          : WRM100		                                          */
/* Indice          : BE040                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 14/09/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _WIFI_N_TOOLS
#define _WIFI_N_TOOLS_EXT
#else
#define _WIFI_N_TOOLS_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8WlanN_GetWifiUserInfo
// Entrees		: <loc_s32_sockfd> : open file descriptor
//				: <loc_pt_userinfo_value< : pointeur sur structure userinfo
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 23/09/2010 -
// Description	: get rssi of last packet (better beacon?)
//=====================================================================================
u8sod u8WlanN_GetWifiUserInfo(s32sod loc_s32_sockfd, struct ieee80211req_get_userinfo *loc_pt_userinfo_value);

//=====================================================================================
// Fonction		: u8WlanN_GetWifiUserInfo_Ioctl
//				: <loc_pt_userinfo_value< : pointeur sur structure userinfo
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 23/09/2010 -
// Description	: Extraction du paramètre d'exploitation "userinfo" du driver Wifi
//=====================================================================================
u8sod u8WlanN_GetWifiUserInfo_Ioctl(struct ieee80211req_get_userinfo *loc_pt_userinfo_value);

//=====================================================================================
// Fonction		: InitModule_Wifi_N_Tools
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/09/2010 -
// Description	: Initialisation du module de wifi_N_tools
//=====================================================================================
void InitModule_Wifi_N_Tools(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


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

#ifdef _WIFI_ABG_TOOLS
#define _WIFI_ABG_TOOLS_EXT
#else
#define _WIFI_ABG_TOOLS_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8WlanABG_SetWifiTypePreambule
// Entrees		: <loc_u8_valeur> : valeur du preambule (WF_TYPE_PREAMBULE_SHORT ou WF_TYPE_PREAMBULE_LONG)
// Sortie		: <loc_u8_resultat>: TRUE,si set réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: Configure le preamble
//=====================================================================================
u8sod u8WlanABG_SetWifiTypePreambule(u8sod loc_u8_valeur);

//=====================================================================================
// Fonction		: u8WlanABG_GetWifiFilterRSSI
// Entrees		: <loc_s32_sockfd> : open file descriptor
//				: <loc_ps32_rssi_value< : pointeur sur valeur info RSSI
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: Extraction info RSSI filtrée du driver wifi
//=====================================================================================
u8sod u8WlanABG_GetWifiFilterRSSI(s32sod loc_s32_sockfd, s32sod *loc_ps32_rssi_value);

//=====================================================================================
// Fonction		: u8WlanABG_GetWifiRawRSSI
// Entrees		: <loc_s32_sockfd> : open file descriptor
//				: <loc_ps32_rssi_value< : pointeur sur valeur info RSSI
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: get rssi of last packet (better beacon?)
//=====================================================================================
u8sod u8WlanABG_GetWifiRawRSSI(s32sod loc_s32_sockfd, s32sod *loc_ps32_rssi_value);

//=====================================================================================
// Fonction		: u8WlanABG_GetWifiRSSIFilter_Ioctl
// Entrees		: <loc_ps32_rssi_value< : pointeur sur valeur info RSSI
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: Extraction du paramètre d'exploitation RSSI "Filtré" du driver Wifi
//=====================================================================================
u8sod u8WlanABG_GetWifiRSSIFilter_Ioctl(s32sod *loc_ps32_rssi_value);

//=====================================================================================
// Fonction		: u8WlanABG_GetWifiRSSIRaw_Ioctl
// Entrees		: <loc_ps32_rssi_value< : pointeur sur valeur info RSSI
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: Extraction du paramètre d'exploitation RSSI "brute" du driver Wifi
//=====================================================================================
u8sod u8WlanABG_GetWifiRSSIRaw_Ioctl(s32sod *loc_ps32_rssi_value);

//=====================================================================================
// Fonction		: InitModule_Wifi_ABG_Tools
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 14/09/2010 -
// Description	: Initialisation du module de wifi_ABG_tools
//=====================================================================================
void InitModule_Wifi_ABG_Tools(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


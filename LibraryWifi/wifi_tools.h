/*========================================================================*/
/* NOM DU FICHIER  : wifi_tools.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009                                           */
/* Libelle         : Module commun à plusieurs process (gérant le Wifi)   */
/* Projet          : WRM100		                                          */
/* Indice          : BE058                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
//BE040 13/09/2010 CM
// - Nouveaux projets WRM100
//BE047 29/11/2010 CM
// - Gestion mode dégradé - connection à AP impossible en permanence suite à configuration wifi 
//BE051 13/12/2010 CM
// - Ajout exploitation SSID (utile si dual ssid activé)
//BE058 21/01/2011 CM
// - Modification gestion exploitation wifi
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _WIFI_TOOLS
#define _WIFI_TOOLS_EXT
#else
#define _WIFI_TOOLS_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8GetWifiBSSID_Ioctl
// Entrees		: <loc_ps_exp_station<: pointeur sur l'exploitation de la station
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: Extraction info BSSID
//=====================================================================================
u8sod u8GetWifiBSSID_Ioctl(S_STRUCT_EXP_STATION *loc_ps_exp_station);

//=====================================================================================
// Fonction		: u8GetWifiESSID_Ioctl
// Entrees		: <loc_ps_exp_station<: pointeur sur l'exploitation de la station
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 13/12/2010 -
// Description	: Extraction info nom du SSID
//=====================================================================================
u8sod u8GetWifiESSID_Ioctl(S_STRUCT_EXP_STATION *loc_ps_exp_station);

//=====================================================================================
// Fonction		: s32Ether_cmp
// Entrees		: <loc_pt_eth1<: adresse ethernet 1
//				: <loc_pt_eth2<: adresse ethernet 2
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Compare two ethernet addresses
//=====================================================================================
s32sod s32Ether_cmp(struct ether_addr* loc_pt_eth1, struct ether_addr* loc_pt_eth2);

//=====================================================================================
// Fonction		: InitModule_Wifi_Tools
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de wifi_tools
//=====================================================================================
void InitModule_Wifi_Tools(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


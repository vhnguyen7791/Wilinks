/*========================================================================*/
/* NOM DU FICHIER  : mac_tools.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/10/2009                                           */
/* Libelle         : Module commun à plusieurs process (gérant adr MAC)   */
/* Projet          : WRM100		                                          */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _MAC_TOOLS
#define _MAC_TOOLS_EXT
#else
#define _MAC_TOOLS_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8GetMacAddress
// Entrees		: <loc_ps8_nom_interface< : nom de l'interface
//				: >loc_pu8_adr_mac< : adresse MAC retournée (si TRUE)
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 26/10/2009 -
// Description	: Extraction adresse MAC de l'interface
//=====================================================================================
u8sod u8GetMacAddress(s8sod *loc_ps8_nom_interface, u8sod *loc_pu8_adr_mac);

//=====================================================================================
// Fonction		: InitModule_Mac_Tools
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de mac_tools
//=====================================================================================
void InitModule_Mac_Tools(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


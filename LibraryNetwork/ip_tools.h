/*========================================================================*/
/* NOM DU FICHIER  : ip_tools.h		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/01/2010                                           */
/* Libelle         : Module commun à plusieurs process (gérant adr IP)    */
/* Projet          : WRM100		                                          */
/* Indice          : BE003                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE003 07/01/10 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _IP_TOOLS
#define _IP_TOOLS_EXT
#else
#define _IP_TOOLS_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8GetIPAddress
// Entrees		: <loc_ps8_nom_interface< : nom de l'interface
//				: >loc_ps8_adr_ip< : adresse IP retournée (si TRUE)
//				: >loc_ps8_mask_ip< : masque IP retourné (si TRUE)
// Sortie		: <loc_u8_resultat>: TRUE, si get réussi, sinon FALSE
// Auteur		: CM - 07/01/2010 -
// Description	: Extraction adresse IP / Mask de l'interface
//=====================================================================================
u8sod u8GetIPAddress(s8sod *loc_ps8_nom_interface, s8sod *loc_ps8_adr_ip, s8sod *loc_ps8_mask_ip);

//=====================================================================================
// Fonction		: InitModule_Ip_Tools
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 07/01/2010 -
// Description	: Initialisation du module de ip_tools
//=====================================================================================
void InitModule_Ip_Tools(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


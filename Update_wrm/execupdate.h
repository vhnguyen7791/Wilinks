/*========================================================================*/
/* NOM DU FICHIER  : execupdate.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 18/12/2009                                           */
/* Libelle         : UPDATE: Processus de mise à jour logicielle		  */
/* Projet          : WRM100	                                              */
/* Indice          : BE010                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE002 18/12/09 CM
// - CREATION
//BE010 03/02/2010 CM
// - Modification processus update (independance avec principal)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXECUPDATE
#define _EXECUPDATE_EXT
#else
#define _EXECUPDATE_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: InitModule_ExecUpdate
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 18/12/2009 -
// Description	: Initialisation du module de ExecUpdate
//=====================================================================================
void InitModule_ExecUpdate(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

_EXECUPDATE_EXT	u8sod	u8_modeboot_encours;

_EXECUPDATE_EXT	s8sod ps8_update__version_be_uboot[TAILLE_MAX_MSG_VERSION_UBOOT +1];	//version BE Uboot 

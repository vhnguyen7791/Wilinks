/*========================================================================*/
/* NOM DU FICHIER  : execupdate.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 18/12/2009                                           */
/* Libelle         : UPDATE: Processus de mise � jour logicielle		  */
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

#ifndef EXECUPDATE_H
#define EXECUPDATE_H
/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXECUPDATE
#define _EXECUPDATE_EXT
#else
#define _EXECUPDATE_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

typedef enum E_LISTE_MODES_BOOT
{
	E_MODE_BOOT_AUCUN = 0,
	E_MODE_BOOT_APP1,
	E_MODE_BOOT_APP2,
	NB_MAX_MODES_BOOT 
} T_E_LISTE_MODES_BOOT; 

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

_EXECUPDATE_EXT	T_E_LISTE_MODES_BOOT e_modeboot_encours;

_EXECUPDATE_EXT	s8sod ps8_update__version_be_uboot[TAILLE_MAX_MSG_VERSION_UBOOT +1];	//version BE Uboot 
#endif

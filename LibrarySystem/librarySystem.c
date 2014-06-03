/*========================================================================*/
/* NOM DU FICHIER  : librarySystem.c		                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/07/2010                                           */
/* Libelle         : Base de données: initialisation de la librarie system*/
/* Projet          : WRM100                                               */
/* Indice          : BE035                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE035 01/07/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

//REMARQUE IMPORTANTE: POUR AFFICHER LE DEBUG DE LA LIBRAIRIE SYSTEM
//Il faut activer la configuration via la fonction SetConfig_LibrarySystem

/*_____II - DEFINE SBIT __________________________________________________*/
#define _LIBRARYSYSTEM

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: FunctionPrintfVide
//Entrée	 : <loc_ps8_fmtp< : message du texte dans debug
// Sortie		: void
// Auteur		: CM - 07/07/2010 -
// Description	: Fonction de la printf video
//=====================================================================================
void FunctionPrintfVide(s8sod *loc_ps8_fmtp, ...)
{
}/*FunctionPrintfVide*/

//=====================================================================================
// Fonction		: SetConfig_LibrarySystem
// Entrees		: <loc_pf_functionPrintf>	: fonction de debug
// Sortie		: rien
// Auteur		: CM - 01/07/2010 -
// Description	: Configure la library system
//=====================================================================================
void SetConfig_LibrarySystem(void *loc_pf_functionPrintf)
{
	pf_functionPrintf = loc_pf_functionPrintf; //MAJ
}/*SetConfig_LibrarySystem*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_LibrarySystem
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/07/2010 -
// Description	: Initialisation du module de librarySystem
//=====================================================================================
void InitModule_LibrarySystem(void)
{
	InitModule_CmdSystem(); //INIT
	InitModule_InfoSystem(); //INIT
	InitModule_Date(); //INIT
	InitModule_ResetFile(); //INIT

	pf_functionPrintf = &FunctionPrintfVide;	//INIT
	
}/*InitModule_LibrarySystem*/


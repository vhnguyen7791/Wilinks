/*========================================================================*/
/* NOM DU FICHIER  : libraryNetwork.c		                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/01/2010                                           */
/* Libelle         : Base de données: initialisation de la librarie Network*/
/* Projet          : WRM100                                               */
/* Indice          : BE003                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE003 07/01/10 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _LIBRARYNETWORK

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_LibraryNetwork
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 07/01/2010 -
// Description	: Initialisation du module de libraryNetwork
//=====================================================================================
void InitModule_LibraryNetwork(void)
{
	InitModule_Mac_Tools(); //INIT
	InitModule_Ip_Tools(); //INIT
}/*InitModule_LibraryNetwork*/


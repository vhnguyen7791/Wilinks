/*========================================================================*/
/* NOM DU FICHIER  : libraryWifi.c			                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 14/09/2010                                           */
/* Libelle         : LibraryWifi: initialisation de la librarie Wifi	  */
/* Projet          : WRM100                                               */
/* Indice          : BE040                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 14/09/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _LIBRARYWIFI

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_LibraryWifi
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 14/09/2010 -
// Description	: Initialisation du module de libraryWifi
//=====================================================================================
void InitModule_LibraryWifi(void)
{
	InitModule_Wifi_Tools(); //INIT
#ifdef _WRM100_ABG_SELECT
	InitModule_Wifi_ABG_Tools(); //INIT
#endif
#ifdef _WRM100_N_SELECT
	InitModule_Wifi_N_Tools(); //INIT
#endif
}/*InitModule_LibraryWifi*/


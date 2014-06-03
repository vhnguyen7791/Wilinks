/*========================================================================*/
/* NOM DU FICHIER  : resetfile.c 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/01/2010                                           */
/* Libelle         : Base de données: gestion ordre reset CPU			  */
/* Projet          : WRM100                                               */
/* Indice          : BE007                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE007 26/01/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _RESETFILE

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: OrdreResetUc
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/10/2009 -
// Description	: Ordre de Reset du uC
//=====================================================================================
void OrdreResetUc(void)
{
	FILE		*loc_p_handle;

	//On crée le fichier reset.now
	if(NULL != (loc_p_handle = fopen( FICHIER_RESET_NOW, "w" )))
	{
		fclose (loc_p_handle);
	}

}/*OrdreResetUc*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_ResetFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/01/2010 -
// Description	: Initialisation du module de resetfile
//=====================================================================================
void InitModule_ResetFile(void)
{

}/*InitModule_ResetFile*/


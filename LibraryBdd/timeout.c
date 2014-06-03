/*========================================================================*/
/*  NOM DU FICHIER : timeout.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 05/11/2009                                           */
/* Libelle         : Base de données: gestion des timeout				  */
/* Projet          : WRM100                                               */
/* Indice	       : BE000												  */
/*========================================================================*/
/*  Historique	      :													  */
/*	Version		Date	Auteur		Commentaires						  */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère la base de données timeoutr

/*_____II - DEFINE SBIT __________________________________________________*/

#define _TIMEOUT	1


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: StartTimeOut
// Entrees		: <loc_ps_date<
// Sortie		: void
// Auteur		: CM - 05/11/2009 -
// Description	: Démarre l'incrementation du timeout
//=====================================================================================
void StartTimeOut(S_STRUCT_TIME_OUT *loc_pt_timeout)
{
	loc_pt_timeout->u16_cpt_timeout	= 0;	//RAZ
	loc_pt_timeout->u8_flag	= TRUE;	

}/*StartTimeOut*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitStructTimeOut
// Entrees		: <loc_ps_date<
// Sortie		: void
// Auteur		: CM - 05/11/2009 -
// Description	: Initialisation la structure timeout
//=====================================================================================
void InitStructTimeOut(S_STRUCT_TIME_OUT *loc_pt_timeout)
{
	loc_pt_timeout->u16_cpt_timeout	= 0;	//INIT
	loc_pt_timeout->u8_flag	= FALSE;	//INIT

}/*InitStructTimeOut*/

//=====================================================================================
// Fonction		: InitModule_Timeout
// Entrees		: rien
// Sortie		: void
// Auteur		: CM - 05/11/2009 -
// Description	: Initialisation du module de Date
//=====================================================================================
void InitModule_Timeout(void)
{

}/*InitModule_Timeout*/


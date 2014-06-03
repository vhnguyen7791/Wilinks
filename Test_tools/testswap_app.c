/*========================================================================*/
/* NOM DU FICHIER  : testswap_app.c	  	                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 21/12/2009                                           */
/* Libelle         : Test le swap sur l'autre application				  */
/* Projet          : WRM100		                                          */
/* Indice          : BE010                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE002 21/12/09 CM
// - CREATION
//BE010 03/02/2010 CM
// - Modification processus update (independance avec principal)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _TESTSWAP_APP

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: TestSwap_App
// Entrees		: <loc_u8_mode_app>: app � activer
// Sortie		: rien
// Auteur		: CM - 21/12/2009 -
// Description	: Teste le basculement sur l'autre application
//=====================================================================================
void TestSwap_App(u8sod loc_u8_mode_app)
{
	s32sod	loc_s32_sem;
	S_STRUC_EXP_GENERAL loc_s_exp_general;
	
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on l�ve le sem
	if(FALSE == u8FillExploitGeneralFile(&loc_s_exp_general))
	{
		printf("TestSwap_App: Probleme lecture exploit general\n");
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
	
	switch(loc_u8_mode_app)
	{
		case MODE_BOOT_APP1:
			u8MiseAJourInfoSystem(MODE_BOOT_APP1, loc_s_exp_general.ps8_version_be_uboot);
			break;
		case MODE_BOOT_APP2:
			u8MiseAJourInfoSystem(MODE_BOOT_APP2, loc_s_exp_general.ps8_version_be_uboot);
			break;
		default:
			break;
	}
	
	
}/*TestSwap_App*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_TestSwap_App
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 21/12/2009 -
// Description	: Initialisation du module de testswap_app
//=====================================================================================
void InitModule_TestSwap_App(void)
{
}/*InitModule_TestSwap_App*/


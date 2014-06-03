/*========================================================================*/
/* NOM DU FICHIER  : gestreboot.c 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Principal: gestion du reboot de l'équipement		  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _GESTREBOOT

#define TIME_OUT_RESET_NOW	1

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static u8sod u8_cpt_reset_now;

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: ExecuteGestionReboot
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Gestion du reboot de l'équipement
//=====================================================================================
void ExecuteGestionReboot(void)
{
	FILE		*loc_p_handle;

	//On test si le fichier est présent
	if(NULL != (loc_p_handle = fopen( FICHIER_RESET_NOW, "r" )))
	{
		//fermeture du fichier
		fclose (loc_p_handle);

		u8_cpt_reset_now ++;
		if(u8_cpt_reset_now > TIME_OUT_RESET_NOW)//CONDITION: time out expiré
		{
			//Suppression du fichier reset.now
			CmdSystem_Generique("rm %s",FICHIER_RESET_NOW);

			//Une petite pause
			sleep(1);

			//on reboot la carte
			CmdSystem_Generique("reboot &");
			sleep(5);
		}
	}
	else
	{
		u8_cpt_reset_now = 0;//RAZ
	}
	

}/*ExecuteGestionReboot*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_GestReboot
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de gestreboot
//=====================================================================================
void InitModule_GestReboot(void)
{
	u8_cpt_reset_now = 0;	//INIT	
}/*InitModule_GestReboot*/


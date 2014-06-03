/*========================================================================*/
/* NOM DU FICHIER  : evt_debug.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/03/2010                                           */
/* Libelle         : Monitor: Calcul des évènements debug				  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 11/03/2010 CM
// - CREATION
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _EVT_DEBUG

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: CalculEvents_Debug
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 04/03/2010 -
// Description	: Calcul les évènements de debug
//=====================================================================================
void CalculEvents_Debug(void)
{
	static u8sod loc_u8_swap_evt177;
	static u8sod loc_u8_cpt_swap_evt179;
	static u8sod loc_u8_swap_evt179;
	u16sod	loc_u16_i;
	u8sod	loc_u8_etat;

	//Gestion EVT177
	if(TRUE == loc_u8_swap_evt177)
	{
		loc_u8_swap_evt177 = FALSE;	//RAZ
	}
	else
	{
		loc_u8_swap_evt177 = TRUE;	//RAZ
	}

	for(loc_u16_i=1;loc_u16_i<=5;loc_u16_i++)
	{
		if(TRUE == loc_u8_swap_evt177)
		{
			if(0 == (loc_u16_i % 2))
			{
				loc_u8_etat = ETAT_EVT_DEBUT;
			}
			else
			{
				loc_u8_etat = ETAT_EVT_FIN;
			}
		}
		else
		{
			if(0 == (loc_u16_i % 2))
			{
				loc_u8_etat = ETAT_EVT_FIN;
			}
			else
			{
				loc_u8_etat = ETAT_EVT_DEBUT;
			}
		}
		RegisterEvent(EVT177_RESERVE, (u32sod)loc_u16_i, 0, 0, NULL, 0, loc_u8_etat);
	}

	//Calcul EVT178
	RegisterEvent(EVT178_RESERVE, (u32sod)1818, 0, 0, NULL, 0, ETAT_EVT_DEBUT);

	//Calcul EVT179
	loc_u8_cpt_swap_evt179++;
	if(loc_u8_cpt_swap_evt179 >= 5)
	{
		loc_u8_cpt_swap_evt179 = 0; //RAZ
		if(TRUE == loc_u8_swap_evt179)
		{
			loc_u8_swap_evt179 = FALSE;
		}
		else
		{
			loc_u8_swap_evt179 = TRUE;
		}
	}

	if(TRUE == loc_u8_swap_evt179)
	{
		RegisterEvent(EVT179_RESERVE, 0, 0, 0, NULL, 0, ETAT_EVT_DEBUT);
	}
	else
	{
		RegisterEvent(EVT179_RESERVE, 0, 0, 0, NULL, 0, ETAT_EVT_FIN);
	}
	
	

}/*CalculEvents_Debug*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Evt_Debug
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010 -
// Description	: Initialisation du module evt_debug
//=====================================================================================
void InitModule_Evt_Debug(void)
{
	
}/*InitModule_Evt_Debug*/

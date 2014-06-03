/*========================================================================*/
/* NOM DU FICHIER  : ad7814.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 06/07/2010                                           */
/* Libelle         : Base de données: controle du capteur de temperature  */
/* Projet          : WRM100                                               */
/* Indice          : BE037                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE037 06/07/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _TEMPERATURE

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

#define FICHIER__SYS_AD_TEMP PATH_DIR_PROC "sys/wrm100/ad_temp"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: s32GetTemperature
// Entrees		: rien
// Sortie		: <loc_s32_valeur> : valeur de la température
// Auteur		: CM - 06/07/2010 -
// Description	: Mesure de la temperature
//=====================================================================================
s32sod s32GetTemperature(void)
{
	s32sod loc_s32_valeur;
	u32sod	loc_u32_temp;
	FILE	*loc_p_handle;
	s8sod	loc_ps8_chaine10[10+1];//au max on a besoin de 4+1 caracteres

	loc_p_handle = NULL;	//INIT
	loc_s32_valeur = VALEUR_TEMPERATURE_INCONNUE;	//INIT
	strcpy(loc_ps8_chaine10, "");	//INIT
	loc_u32_temp = 0;	//INIT

	if(NULL != (loc_p_handle = fopen( FICHIER__SYS_AD_TEMP, "rt" )))
	{
		//Lecture de la ligne
		if (NULL != fgets(loc_ps8_chaine10,5,loc_p_handle))
		{
			loc_u32_temp = atoi(loc_ps8_chaine10);
			//transformation du resultat en degre
			loc_u32_temp >>=2; // on divise par 4
			if (loc_u32_temp > 127)
			{//temp négative
				loc_s32_valeur = loc_u32_temp - 256;
			}
			else
			{//temp positive
				loc_s32_valeur = loc_u32_temp;
			}
		}
		//fermeture du fichier
		fclose (loc_p_handle);
	}
	
	return loc_s32_valeur;
}/*s32GetTemperature*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Ad7814
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 06/07/2010 -
// Description	: Initialisation du module de ad7814
//=====================================================================================
void InitModule_Ad7814(void)
{
	
}/*InitModule_Ad7814*/


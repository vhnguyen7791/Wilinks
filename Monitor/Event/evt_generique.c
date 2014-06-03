/*========================================================================*/
/* NOM DU FICHIER  : evt_generique.c                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : Monitor: Calcul des évènements génériques			  */
/* Projet          : WRM100                                               */
/* Indice          : BE016                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION
//BE016 11/03/2010 CM
// - Ajout calcul evt EquipmentOn
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _EVT_GENERIQUE

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

// variable utilisées pour la gestion de l'évt "Signe de vie"
static struct timeval s_timevalsignevie;
static struct timeval s_timevalnow;

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Calcul_Evt_EquipmentOn
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 11/03/2010 -
// Description	: Gestion de l'evènement de EquipementOn
//=====================================================================================
void Calcul_Evt_EquipmentOn(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	//Revue_caf - 07/04/10 - Info : le paramètre d'entrée ne sert à rien	
	RegisterEvent(EVT175_INF_EQUIPEMENT_ON, 0, 0, 0, NULL, 0, ETAT_EVT_INFO); //INIT
}/*Calcul_Evt_EquipmentOn*/

//=====================================================================================
// Fonction		: Calcul_Evt_SigneVie
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 01/03/2010 -
// Description	: Gestion de l'evènement de signe de vie
//=====================================================================================
void Calcul_Evt_SigneVie(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	if(TRUE == loc_ps_config->s_snmp.s_trap_signevie.u8_activation)
	{
		gettimeofday(&s_timevalnow, (struct timezone *) NULL);
		if (s_timevalnow.tv_sec >= s_timevalsignevie.tv_sec)
		{
			//RAZ
			s_timevalsignevie.tv_usec = s_timevalnow.tv_usec;	//RAZ
			s_timevalsignevie.tv_sec = s_timevalnow.tv_sec + loc_ps_config->s_snmp.s_trap_signevie.u16_cycle*60; //RAZ
			
			RegisterEvent(EVT176_INF_SIGNE_DE_VIE, 0, 0, 0, NULL, 0, ETAT_EVT_INFO); //INIT
		}
	}
}/*Calcul_Evt_SigneVie*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Evt_Generique
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/03/2010 -
// Description	: Initialisation du module evt_generique
//=====================================================================================
void InitModule_Evt_Generique(void)
{
	gettimeofday(&s_timevalnow, (struct timezone *) NULL); //INIT
	s_timevalsignevie.tv_usec = 0; //INIT
	s_timevalsignevie.tv_sec = 0; //INIT
	
}/*InitModule_Evt_Generique*/

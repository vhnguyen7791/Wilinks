/*========================================================================*/
/*  NOM DU FICHIER : date.c												  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : Base de données: gestion de la date / heure		  */
/* Projet          : WRM100                                               */
/* Indice	       : BE046												  */
/*========================================================================*/
/*  Historique	      :													  */
//BE000 24/09/09 CM
// - CREATION
//BE013 26/02/2010 CM
// - Ajout fonction affichage de la date complète 
//BE035 30/06/2010 CM
// - Ajout gestion de l'heure courante
//BE046 17/11/2010 CM
// - Correction force horodatage identique à tous les évènements dans la seconde
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère la base de données date / heure

/*_____II - DEFINE SBIT __________________________________________________*/

#define _DATE	1

//Gestion de la date (sélectionner l'un des 2 défine)
//#define DATE_VIA_FPGA
#define DATE_VIA_LINUX

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static u8sod	u8_moddate__mode_dateheure;
static S_STRUCT_DATE s_moddate__date_manuelle;

/*_____V - PROCEDURES ____________________________________________________*/

//============================================================================
// Fonction		: ps8GetChDate
// Entrees		: <loc_ps_date< : pointeur sur date
// Sortie		: <loc_ps8_chaine< : chaine à afficher
// Auteur		: CM - 02/03/2010 -
// Description	: renvoie la chaîne à afficher de la date complète
//============================================================================
s8sod* ps8GetChDate(S_STRUCT_DATE *loc_ps_date)
{
	static s8sod loc_ps8_chaine[UI_TAILLE_MAX_MESSAGE];

	loc_ps8_chaine[0] = 0;	//INIT

	if (MODE_DATE_HEURE_24H == u8_moddate__mode_dateheure)	//CONDITION: format Heure=12H
	{
		sprintf( loc_ps8_chaine,  "%02d/%02d/%04d %02d:%02d:%02d",
				 loc_ps_date->u8_jour,
				 loc_ps_date->u8_mois,
				 loc_ps_date->u16_annee,
				 loc_ps_date->u8_heure,
				 loc_ps_date->u8_minute,
				 loc_ps_date->u8_seconde);
	}
	else
	{
		//	[COMMENTER POUR PLUS DE CLARTE!!] [AUDIT DU CODE] [2008/09/04] [MS]
		sprintf( loc_ps8_chaine,  "%02d/%02d/%04d %02d:%02d:%02d %s",
				 loc_ps_date->u8_jour,
				 loc_ps_date->u8_mois,
				 loc_ps_date->u16_annee,
				 ( (loc_ps_date->u8_heure<12) ? ( (0==loc_ps_date->u8_heure) ? 12 : loc_ps_date->u8_heure ) : ( (12==loc_ps_date->u8_heure) ? 12 : (loc_ps_date->u8_heure-12))),
				 loc_ps_date->u8_minute,
				 loc_ps_date->u8_seconde,
				 ( (loc_ps_date->u8_heure<12) ? "AM" : "PM" )
			   );
	}

	return (&loc_ps8_chaine[0]);
}/*ps8GetChDate*/

// -------------------------------------------------------------
// Fonction    : ChFormatDate
// Entrees     : <loc_s_date>
//				 <loc_ps8_chaine<	: chaine retournée
// Sortie	   : rien
// Auteur      : CM - 20/04/2004
// Description : Procedure qui retourne en chaine de caractère
//				au format date xx/xx/xx
// Historique  : 
// -------------------------------------------------------------
void ChFormatDate(s8sod *loc_ps8_chaine, S_STRUCT_DATE	loc_s_date)
{
	loc_ps8_chaine[0] = 0;
	
	sprintf( loc_ps8_chaine,     "%02d/%02d/%04d", loc_s_date.u8_jour,loc_s_date.u8_mois,loc_s_date.u16_annee);
	
}/*ChFormatDate*/

// -------------------------------------------------------------
// Fonction    : ChFormatHeure
// Entrees     : <loc_s_date>
//				 <loc_ps8_chaine<	: chaine retournée
// Sortie	   : void
// Auteur      : CM - 20/04/2004
// Description : Procedure qui retourne en chaine de caractère
//				au format Heure hh:mm:ss (AM/PM en option)
// Historique  : 
// -------------------------------------------------------------
void ChFormatHeure(s8sod *loc_ps8_chaine, S_STRUCT_DATE	loc_s_date)
{
	loc_ps8_chaine[0] = 0;
	
	if (MODE_DATE_HEURE_24H == u8_moddate__mode_dateheure)	//CONDITION: format Heure=12H
	{
		sprintf( loc_ps8_chaine,     "%02d:%02d:%02d",loc_s_date.u8_heure,loc_s_date.u8_minute, loc_s_date.u8_seconde);
	}
	else
	{
//	[COMMENTER POUR PLUS DE CLARTE!!] [AUDIT DU CODE] [2008/09/04] [MS]
		sprintf( loc_ps8_chaine,  "%02d:%02d:%02d %s",
				 ( (loc_s_date.u8_heure<12) ? ( (0==loc_s_date.u8_heure) ? 12 : loc_s_date.u8_heure ) : ( (12==loc_s_date.u8_heure) ? 12 : (loc_s_date.u8_heure-12))),
				 loc_s_date.u8_minute,
				 loc_s_date.u8_seconde,
				 ( (loc_s_date.u8_heure<12) ? "AM" : "PM" )
			   );
	}

}/*ChFormatHeure*/

//=====================================================================================
// Fonction		: SetDateAvantCoupureSecteur
// Entrees		: <loc_ps_date<
// Sortie		: void
// Auteur		: CM - 10/10/2007 -
// Description	: Fixe date avant coupure secteur
//=====================================================================================
void SetDateAvantCoupureSecteur(S_STRUCT_DATE	*loc_ps_date)
{
#ifdef DATE_VIA_LINUX
	time_t	loc_s_time_t;
	struct tm	loc_s_tm;

	time(&loc_s_time_t);
	loc_s_tm = *localtime((const time_t *)(&loc_s_time_t));
#endif

	loc_ps_date->u16_annee	= (u16sod)(loc_s_tm.tm_year + 1900);
	loc_ps_date->u8_mois	= (u8sod)(loc_s_tm.tm_mon+1);
	loc_ps_date->u8_jour	= (u8sod)loc_s_tm.tm_mday;
	loc_ps_date->u8_heure	= (u8sod)loc_s_tm.tm_hour;
	loc_ps_date->u8_minute	= (u8sod)loc_s_tm.tm_min;
	loc_ps_date->u8_seconde	= (u8sod)loc_s_tm.tm_sec;

}/*SetDateAvantCoupureSecteur*/

//=====================================================================================
// Fonction		: SetDate
// Entrees		: <loc_ps_date< : date retournée
//				: <loc_u8_methode> : methode pour fixer date (METHODE_SETDATE_SYSTEM ou METHODE_SETDATE_MANUEL)
// Sortie		: void
// Auteur		: CM - 27/07/2007 -
// Description	: Fixe date (via l'heure systeme ou avec date sauvée manuellement)
//=====================================================================================
void SetDate(S_STRUCT_DATE	*loc_ps_date, u8sod loc_u8_methode)
{
	time_t	loc_s_time_t;
	struct tm	loc_s_tm;
	
	switch(loc_u8_methode)
	{
		case METHODE_SETDATE_MANUEL:
			*loc_ps_date = s_moddate__date_manuelle; 
			break;
		case METHODE_SETDATE_SYSTEM:
		default:
			time(&loc_s_time_t);
			loc_s_tm = *localtime((const time_t *)(&loc_s_time_t));
			*loc_ps_date = sConvertTimeToDate(loc_s_time_t);
			break;
	}


}/*SetDate*/

//=====================================================================================
// Fonction		: sConvertTimeToDate
// Entrees		: <loc_ps_date<
// Sortie		: void
// Auteur		: CM - 27/07/2007 -
// Description	: Convertit time en date
//=====================================================================================
S_STRUCT_DATE sConvertTimeToDate(time_t	loc_s_time_t)
{
	S_STRUCT_DATE loc_s_date;
	struct tm	loc_s_tm;

	loc_s_tm = *localtime((const time_t *)(&loc_s_time_t));

	loc_s_date.u16_annee	= (u16sod)(loc_s_tm.tm_year + 1900);
	loc_s_date.u8_mois	= (u8sod)(loc_s_tm.tm_mon+1);
	loc_s_date.u8_jour	= (u8sod)loc_s_tm.tm_mday;
	loc_s_date.u8_heure	= (u8sod)loc_s_tm.tm_hour;
	loc_s_date.u8_minute	= (u8sod)loc_s_tm.tm_min;
	loc_s_date.u8_seconde	= (u8sod)loc_s_tm.tm_sec;

	return loc_s_date;
}/*sConvertTimeToDate*/

//=====================================================================================
// Fonction		: u8TestDate_Valide
// Entrees		: <loc_ps_date< : date à tester
// Sortie		: <loc_u8_resultat>: TRUE si valide, sinon FALSE
// Auteur		: CM - 22/09/2008 -
// Description	: Test si la date est valide
//=====================================================================================
u8sod u8TestDate_Valide(S_STRUCT_DATE	*loc_ps_date)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	//Test de la date
	if(loc_ps_date->u8_mois > 12)
	{
		loc_u8_resultat = FALSE;
	}
	if(loc_ps_date->u8_jour > 31)
	{
		loc_u8_resultat = FALSE;
	}
	if(loc_ps_date->u8_heure > 23)
	{
		loc_u8_resultat = FALSE;
	}
	if(loc_ps_date->u8_minute > 59)
	{
		loc_u8_resultat = FALSE;
	}
	if(loc_ps_date->u8_seconde > 59)
	{
		loc_u8_resultat = FALSE;
	}

	if(FALSE == loc_u8_resultat)
	{
		printf("u8TestDate_Valide: KO %d/%d/%d %d:%d:%d\n",
			   loc_ps_date->u16_annee,
			   loc_ps_date->u8_mois,
			   loc_ps_date->u8_jour,
			   loc_ps_date->u8_heure,
			   loc_ps_date->u8_minute,
			   loc_ps_date->u8_seconde);
	}
	
	return loc_u8_resultat;
}/*u8TestDate_Valide*/

//=====================================================================================
// Fonction		: SetConfig_SetDateManuelle
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 18/11/2010 -
// Description	: Configure la date manuelle dans ce module
//=====================================================================================
void SetConfig_SetDateManuelle(void)
{
	SetDate(&s_moddate__date_manuelle, METHODE_SETDATE_SYSTEM);
}/*SetConfig_SetDateManuelle*/

//=====================================================================================
// Fonction		: SetConfig_ModuleDate
// Entrees		: <loc_u8_mode_date_heure>	: paramètre de config mode date/heure
// Sortie		: rien
// Auteur		: CM - 01/10/2009 -
// Description	: Configure le mode date/heure dans ce module
//=====================================================================================
void SetConfig_ModuleDate(u8sod loc_u8_mode_date_heure)
{
	u8_moddate__mode_dateheure = loc_u8_mode_date_heure; //MAJ
}/*SetConfig_ModuleDate*/

//=====================================================================================
// Fonction		: InitStructDate
// Entrees		: <loc_ps_date<
// Sortie		: void
// Auteur		: CM - 02/04/2004 -
// Description	: Initialisation la structure date
//=====================================================================================
void InitStructDate(S_STRUCT_DATE	*loc_ps_date)
{
	loc_ps_date->u16_annee	= 0;	//INIT
	loc_ps_date->u8_mois	= 0;	//INIT
	loc_ps_date->u8_jour	= 0;	//INIT
	loc_ps_date->u8_heure	= 0;	//INIT
	loc_ps_date->u8_minute	= 0;	//INIT
	loc_ps_date->u8_seconde	= 0;	//INIT

}/*InitStructDate*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Date
// Entrees		: rien
// Sortie		: void
// Auteur		: CM - 02/04/2004 -
// Description	: Initialisation du module de Date
//=====================================================================================
void InitModule_Date(void)
{
	u8_moddate__mode_dateheure = MODE_DATE_HEURE_24H;//INIT
	InitStructDate(&s_moddate__date_manuelle); //INIT

}/*InitModule_Date*/


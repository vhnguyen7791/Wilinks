/*========================================================================*/
/* NOM DU FICHIER  : date.h												  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007                                           */
/* Libelle         : Base de données: gestion de la date / heure		  */
/* Projet          : WRM100                                               */
/* Indice	       : BE035												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE013 26/02/2010 CM
// - Ajout fonction affichage de la date complète 
//BE035 30/06/2010 CM
// - Ajout gestion de l'heure courante
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _DATE
#define _DATE_EXT
#else
#define _DATE_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//============================================================================
// Fonction		: ps8GetChDate
// Entrees		: <loc_ps_date< : pointeur sur date
// Sortie		: <loc_ps8_chaine< : chaine à afficher
// Auteur		: CM - 02/03/2010 -
// Description	: renvoie la chaîne à afficher de la date complète
//============================================================================
s8sod* ps8GetChDate(S_STRUCT_DATE *loc_ps_date);

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
void ChFormatDate(s8sod *loc_ps8_chaine, S_STRUCT_DATE	loc_s_date);

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
void ChFormatHeure(s8sod *loc_ps8_chaine, S_STRUCT_DATE	loc_s_date);

//=====================================================================================
// Fonction		: SetDateAvantCoupureSecteur
// Entrees		: <loc_ps_date<
// Sortie		: void
// Auteur		: CM - 10/10/2007 -
// Description	: Fixe date avant coupure secteur
//=====================================================================================
void SetDateAvantCoupureSecteur(S_STRUCT_DATE	*loc_ps_date);

//=====================================================================================
// Fonction		: SetDate
// Entrees		: <loc_ps_date< : date retournée
//				: <loc_u8_methode> : methode pour fixer date (METHODE_SETDATE_SYSTEM ou METHODE_SETDATE_MANUEL)
// Sortie		: void
// Auteur		: CM - 27/07/2007 -
// Description	: Fixe date (via l'heure systeme ou avec date sauvée manuellement)
//=====================================================================================
void SetDate(S_STRUCT_DATE	*loc_ps_date, u8sod loc_u8_methode);

//=====================================================================================
// Fonction		: sConvertTimeToDate
// Entrees		: <loc_ps_date<
// Sortie		: void
// Auteur		: CM - 27/07/2007 -
// Description	: Convertit time en date
//=====================================================================================
S_STRUCT_DATE sConvertTimeToDate(time_t	loc_s_time_t);

//=====================================================================================
// Fonction		: u8TestDate_Valide
// Entrees		: <loc_ps_date< : date à tester
// Sortie		: <loc_u8_resultat>: TRUE si valide, sinon FALSE
// Auteur		: CM - 22/09/2008 -
// Description	: Test si la date est valide
//=====================================================================================
u8sod u8TestDate_Valide(S_STRUCT_DATE	*loc_ps_date);

//=====================================================================================
// Fonction		: SetConfig_SetDateManuelle
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 18/11/2010 -
// Description	: Configure la date manuelle dans ce module
//=====================================================================================
void SetConfig_SetDateManuelle(void);

//=====================================================================================
// Fonction		: SetConfig_ModuleDate
// Entrees		: <loc_u8_mode_date_heure>	: paramètre de config mode date/heure
// Sortie		: rien
// Auteur		: CM - 01/10/2009 -
// Description	: Configure le mode date/heure dans ce module
//=====================================================================================
void SetConfig_ModuleDate(u8sod loc_u8_mode_date_heure);

//=====================================================================================
// Fonction		: InitStructDate
// Entrees		: <loc_ps_date<
// Sortie		: void
// Auteur		: CM - 02/04/2004 -
// Description	: Initialisation la structure date
//=====================================================================================
void InitStructDate(S_STRUCT_DATE	*loc_ps_date);

//=====================================================================================
// Fonction		: InitModule_Date
// Entrees		: rien
// Sortie		: void
// Auteur		: CM - 02/04/2004 -
// Description	: Initialisation du module de Date
//=====================================================================================
void InitModule_Date(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

#ifdef _DATE
const S_STRUCT_DATE S_DATE_DEFAUT =
{
	ANNEE_PAR_DEFAUT,	//u16_annee
	MOIS_PAR_DEFAUT,	//u8_mois
	JOUR_PAR_DEFAUT,	//u8_jour
	HEURE_PAR_DEFAUT,	//u8_heure
	MINUTE_PAR_DEFAUT,	//u8_minute
	SECONDE_PAR_DEFAUT,	//u8_seconde
};
#else
extern const S_STRUCT_DATE S_DATE_DEFAUT;
#endif


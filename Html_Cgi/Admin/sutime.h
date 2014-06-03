/*========================================================================*/
/* NOM DU FICHIER  : sutime.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: page HTML mise à l'heure					  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE037 06/07/2010 CM
// - Modification page HTML Admin - Mise à l'heure
//		-> surveillance etat NTP
//BE060 16/03/2011
// - Ajout configuration date/heure au démarrage de l'équipement
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUTIME
#define _SUTIME_EXT
#else
#define _SUTIME_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUtime_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 08/07/2010
// Description	: Page rafraichissement page Admin Mise à l'heure
//				"URL=VExploitGeneral_Dyn
//=====================================================================================
void SUtime_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: SUtime
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: Page de Mise à l'heure
//=====================================================================================
void SUtime(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: CreateHtmlListOptionYear
// Entrees		: <loc_u16_cfg_year>: config année
// Sortie		: rien
// Description	: Création html des options de la boite "année"
//=====================================================================================
void CreateHtmlListOptionYear(u16sod loc_u16_cfg_year);

//=====================================================================================
// Fonction		: CreateHtmlListOptionMonth
// Entrees		: <loc_u16_cfg_month>: config mois
// Sortie		: rien
// Description	: Création html des options de la boite "mois"
//=====================================================================================
void CreateHtmlListOptionMonth(u16sod loc_u16_cfg_month);

//=====================================================================================
// Fonction		: CreateHtmlListOptionDay
// Entrees		: <loc_u16_cfg_year>: config année
//				: <loc_u8_cfg_month>: config mois
//				: <loc_u8_cfg_day>: config jour
// Sortie		: rien
// Description	: Création html des options de la boite "jour"
//=====================================================================================
void CreateHtmlListOptionDay(u16sod loc_u16_cfg_year, u8sod loc_u8_cfg_month, u8sod loc_u8_cfg_day);

//=====================================================================================
// Fonction	: Day_Javascript
// Entrees	: rien
// Sortie	: rien
// Description	: Quand on change de "month", on aligne "day" à 28,29,30 ou 31 jours
//=====================================================================================
void Day_Javascript(void);

//=====================================================================================
// Fonction	: Hour_Javascript
// Entrees	: rien
// Sortie	: rien
// Description	: Quand on change le format -> répercussion sur heure
//=====================================================================================
void Hour_Javascript(void);

//=====================================================================================
// Fonction		: InitModule_SUTime
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de sutime
//=====================================================================================
void InitModule_SUTime(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

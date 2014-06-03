/*========================================================================*/
/* NOM DU FICHIER  : susystemlog.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 28/01/2008                                           */
/* Libelle         : HTML CGI: page HTML d'adminsitration - System Log	  */
/* Projet          : WRM100		                                          */
/* Indice          : BE008                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE008 28/01/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUSYSTEMLOG
#define _SUSYSTEMLOG_EXT
#else
#define _SUSYSTEMLOG_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUAdmSystemLog
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 28/01/2010
// Description	: Page HTML Administration: System Log
//=====================================================================================
void SUAdmSystemLog(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SuSystemLog
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de susystemlog
//=====================================================================================
void InitModule_SuSystemLog(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

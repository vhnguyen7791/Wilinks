/*========================================================================*/
/* NOM DU FICHIER  : valarme.h		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/03/2010                                           */
/* Libelle         : HTML CGI: page HTML exploitation alarmes			  */
/* Projet          : WRM100                                               */
/* Indice          : BE016                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE016 11/03/2010 CM
//	- CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VALARME
#define _VALARME_EXT
#else
#define _VALARME_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: VAlarme_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 26/07/2007
// Description	: Page rafraichissement page Alarme
//				"URL=VAlarme&param=<index_page_alarm>"
//=====================================================================================
void VAlarme_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: VAlarme
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 26/07/2007
// Description	: Page HTML Exploitation: Alarme
//				"URL=VAlarme&param=<index_page_alarm>"
//=====================================================================================
void VAlarme(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_VAlarme
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/07/2007
// Description	: Initialisation du module de VAlarme
//=====================================================================================
void InitModule_VAlarme(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

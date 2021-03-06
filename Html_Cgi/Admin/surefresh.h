/*========================================================================*/
/* NOM DU FICHIER  : surefresh.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 23/08/2007                                           */
/* Libelle         : HTML CGI: page HTML de config refresh HTML			  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUREFRESH
#define _SUREFRESH_EXT
#else
#define _SUREFRESH_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUAdmRefresh
// Entrees		: <loc_p_varlist< : liste des param�tres URL
//				  <loc_s32_form_method> : m�thode du formulaire
// Sortie		: Rien
// Auteur		: CM - 23/08/07
// Description	: Page HTML Administration: REfresh
//=====================================================================================
void SUAdmRefresh(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SURefresh
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SURefresh
//=====================================================================================
void InitModule_SURefresh(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

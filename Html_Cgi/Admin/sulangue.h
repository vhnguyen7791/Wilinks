/*========================================================================*/
/* NOM DU FICHIER  : sulangue.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 03/07/2007                                           */
/* Libelle         : HTML CGI: page HTML adminsitration - Langue		  */
/* Projet          : WRM100		                                          */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SULANGUE
#define _SULANGUE_EXT
#else
#define _SULANGUE_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUAdmLangue
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 03/07/07
// Description	: Page HTML Administration: Langue
//=====================================================================================
void SUAdmLangue(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SULangue
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SULangue
//=====================================================================================
void InitModule_SULangue(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

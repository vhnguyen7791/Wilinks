/*========================================================================*/
/* NOM DU FICHIER  : suconfigHandoff.h									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 15/09/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - Handoff		  */
/* Projet          : WRM100                                               */
/* Indice          : BE040                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 15/09/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUCONFIGHANDOFF
#define _SUCONFIGHANDOFF_EXT
#else
#define _SUCONFIGHANDOFF_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUConfigHandoff
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 15/09/2010
// Description	: Page HTML Configuration: Handoff
//				"URL=SUConfigHandoff"
//=====================================================================================
void SUConfigHandoff(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUConfigHandoff
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/09/2010
// Description	: Initialisation du module de SUConfigHandoff
//=====================================================================================
void InitModule_SUConfigHandoff(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

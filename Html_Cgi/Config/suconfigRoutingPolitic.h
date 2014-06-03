/*========================================================================*/
/* NOM DU FICHIER  : suconfigRoutingPolitic.h							  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 15/04/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - Routing /Politic */
/* Projet          : WRM100                                               */
/* Indice          : BE025                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE025 15/04/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUCONFIGROUTINGPOLITIC
#define _SUCONFIGROUTINGPOLITIC_EXT
#else
#define _SUCONFIGROUTINGPOLITIC_EXT	extern
#endif

enum LISTE_DES_PARAM_SUCONFIGROUTINGPOLITIC
{
	PARAM_SUCONFIGROUTINGPOLITIC_NULL = 0,
	PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MIN,
	PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MAX = (PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MIN + NB_MAX_POLICY_ROUTING),
	NB_MAX_PARAM_SUCONFIGROUTINGPOLITIC
};

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUConfigRoutingPolitic
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 15/04/2010
// Description	: Page HTML Configuration: IP Routing 
//				"URL=SUConfigRoutingPolitic"
//=====================================================================================
void SUConfigRoutingPolitic(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUConfigRoutingPolitic
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigRoutingPolitic
//=====================================================================================
void InitModule_SUConfigRoutingPolitic(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

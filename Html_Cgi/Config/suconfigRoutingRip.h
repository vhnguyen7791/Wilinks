/*========================================================================*/
/* NOM DU FICHIER  : suconfigRoutingRip.h								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 20/04/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - Routing / RIP	  */
/* Projet          : WRM100                                               */
/* Indice          : BE025                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE025 20/04/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUCONFIGROUTINGRIP
#define _SUCONFIGROUTINGRIP_EXT
#else
#define _SUCONFIGROUTINGRIP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUConfigRoutingRip
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 20/04/2010
// Description	: Page HTML Configuration: IP Routing  / RIP
//				"URL=SUConfigRoutingRip"
//=====================================================================================
void SUConfigRoutingRip(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUConfigRoutingRip
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigRoutingRip
//=====================================================================================
void InitModule_SUConfigRoutingRip(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

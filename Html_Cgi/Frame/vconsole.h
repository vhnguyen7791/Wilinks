/*========================================================================*/
/* NOM DU FICHIER  : vconsole.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: pages HTML console						  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère le Vconsole.htm


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VCONSOLE
#define _VCONSOLE_EXT
#else
#define _VCONSOLE_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: VConsole_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 02/08/2007
// Description	: Page rafraichissement console HTML
//				"URL=VConsole_Dyn
//=====================================================================================
void VConsole_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: VConsole
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 14/06/2007
// Description	: page HTML de console
//=====================================================================================
void VConsole(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_VConsole
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 14/06/2007 -
// Description	: Initialisation du module VConsole
//=====================================================================================
void InitModule_VConsole(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/*_______VII - INITIALISATIONS NON PROGRAMMEES ___________________________*/


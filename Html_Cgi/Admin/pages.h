/*========================================================================*/
/* NOM DU FICHIER  : pages.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: page HTML password						  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère les passwords

/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _PAGES
#define _PAGES_EXT
#else
#define _PAGES_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

// -------------------------------------------------------------
// Fonction    : enter_pwd
// Entrees     :
// Sortie      : rien
// Description : page de saisie du mot de passe
// -------------------------------------------------------------
void enter_pwd(s8sod **loc_p_varlist, s32sod form_method);

//=====================================================================================
// Fonction		: InitModule_Pages
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de pages
//=====================================================================================
void InitModule_Pages(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


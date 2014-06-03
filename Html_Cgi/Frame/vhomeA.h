/*========================================================================*/
/* NOM DU FICHIER  : vhomeA.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: pages HTML homeA							  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VHOMEA
#define _VHOMEA_EXT
#else
#define _VHOMEA_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: JavaScript_HomeA
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/03/2004 -
// Description	: code de javascript de la page HomeA
//=====================================================================================
void JavaScript_HomeA(void);

//=====================================================================================
// Fonction		: HomeA_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 29/05/2008
// Description	: Page rafraichissement page HomeA
//				"URL=HomeA_Dyn
//=====================================================================================
void HomeA_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: HomeA
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: cadre supérieure du site HTML
//=====================================================================================
void HomeA(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_VHomeA
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/08/2004 -
// Description	: Initialisation du module homea
//=====================================================================================
void InitModule_VHomeA(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


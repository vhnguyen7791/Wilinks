/*========================================================================*/
/* NOM DU FICHIER  : suadmidentif.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: pages HTML Administration - Identification */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUADMIDENTIF
#define _SUADMIDENTIF_EXT
#else
#define _SUADMIDENTIF_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUAdmIdentification
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: rien
// Auteur		: 
// Description	: Page HTML Administration: Identification
//=====================================================================================
void SUAdmIdentification(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUAdmIdentif
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de suadmidentif
//=====================================================================================
void InitModule_SUAdmIdentif(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

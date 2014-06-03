/*========================================================================*/
/* NOM DU FICHIER  : suadmcontrol.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: pages HTML Administration - Control		  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUADMCONTROL
#define _SUADMCONTROL_EXT
#else
#define _SUADMCONTROL_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUAdmControle
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: rien
// Auteur		: 
// Description	: Page HTML Administration: Controle
//=====================================================================================
void SUAdmControle(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUAdmControl
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de suadmcontrol
//=====================================================================================
void InitModule_SUAdmControl(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

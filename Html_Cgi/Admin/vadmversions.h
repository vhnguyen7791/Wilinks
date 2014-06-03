/*========================================================================*/
/* NOM DU FICHIER  : vadmversions.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: pages HTML administration - Versions		  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VADMVERSIONS
#define _VADMVERSIONS_EXT
#else
#define _VADMVERSIONS_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: VAdmVersionsLogicielles
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: rien
// Auteur		: 
// Description	: Page HTML: Administration: Versions Logicielles
//=====================================================================================
void VAdmVersionsLogicielles(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_VAdmVersions
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de vadmversions
//=====================================================================================
void InitModule_VAdmVersions(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/*========================================================================*/
/* NOM DU FICHIER  : vcfginprogress.h									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 02/12/2010                                           */
/* Libelle         : HTML CGI: pages HTML pour afficher "config en cours" */
/* Projet          : WRM100                                               */
/* Indice          : BE047                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE047 02/12/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VCFGINPROGRESS
#define _VCFGINPROGRESS_EXT
#else
#define _VCFGINPROGRESS_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: VCfgInProgress_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 02/12/2010
// Description	: Page rafraichissement page 
//				"URL=VCfgInProgress_Dyn
//=====================================================================================
void VCfgInProgress_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//============================================================================
// Fonction		: PreparePageCfgInProgress
// Entrees		: <loc_ps8_adresse_url<: une chaine de cractere contenant l'adresse de la page demandee
// Sortie		: rien
// Auteur		: CM - 03/12/2010
// Description	: on sauve  la page à accéder et on charge la page HTML CfgInProgress
//============================================================================
void PreparePageCfgInProgress (s8sod *loc_ps8_adresse_url);

//=====================================================================================
// Fonction		: VCfgInProgress
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 02/12/2010 -
// Description	: page HTML d'avertissement
//=====================================================================================
void VCfgInProgress(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_VcfgInProgress
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/12/2010 -
// Description	: Initialisation du module Vcfginprogress
//=====================================================================================
void InitModule_VcfgInProgress(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


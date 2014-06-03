/*========================================================================*/
/* NOM DU FICHIER  : suconfigNat.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 10/02/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - NAT			  */
/* Projet          : WRM100                                               */
/* Indice          : BE010                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE010 10/02/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUCONFIGNAT
#define _SUCONFIGNAT_EXT
#else
#define _SUCONFIGNAT_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUConfigNat_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 16/02/2010
// Description	: Page Dynamique Configuration NAT
//				"URL=SUConfigNat_Dyn
//=====================================================================================
void SUConfigNat_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: HtmlPrint_TableRulesFilterActive
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/02/2010
// Description	: Code HTML de la liste des règles FILTER actives
//=====================================================================================
void HtmlPrint_TableRulesFilterActive(void);

//=====================================================================================
// Fonction		: HtmlPrint_TableRulesNatActive
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/02/2010
// Description	: Code HTML de la liste des règles NAT actives
//=====================================================================================
void HtmlPrint_TableRulesNatActive(void);

//=====================================================================================
// Fonction		: SUConfigNat
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 10/02/2010
// Description	: Page HTML Configuration: NAT
//				"URL=SUConfigNat"
//=====================================================================================
void SUConfigNat(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUConfigNat
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/02/2010
// Description	: Initialisation du module de SUConfigNat
//=====================================================================================
void InitModule_SUConfigNat(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

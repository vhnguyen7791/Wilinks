/*========================================================================*/
/* NOM DU FICHIER  : suconfigRoutingGene.h								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 15/04/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - Routing / General*/
/* Projet          : WRM100                                               */
/* Indice          : BE025                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE025 15/04/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUCONFIGROUTINGGENE
#define _SUCONFIGROUTINGGENE_EXT
#else
#define _SUCONFIGROUTINGGENE_EXT	extern
#endif

enum LISTE_PAGES_HTML_SUCONFIGROUTING
{
	PAGE_HTML_SUCONFIGROUTING__GENE = 0,
	PAGE_HTML_SUCONFIGROUTING__STATIC,
	PAGE_HTML_SUCONFIGROUTING__POLITIC,
	PAGE_HTML_SUCONFIGROUTING__RIP,
	NB_MAX_PAGES_HTML_SUCONFIGROUTING
};

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUConfigRoutingGene
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 15/04/2010
// Description	: Page HTML Configuration: IP Routing 
//				"URL=SUConfigRoutingGene"
//=====================================================================================
void SUConfigRoutingGene(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: HtmlPrint_TableRulesMangleActive
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 18/04/2010
// Description	: Code HTML de la liste des règles MANGLE actives
//=====================================================================================
void HtmlPrint_TableRulesMangleActive(void);

//=====================================================================================
// Fonction		: HtmlPrint_IpRuleInfo
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/04/2010
// Description	: Code HTML de la liste des règles Ip
//=====================================================================================
void HtmlPrint_IpRuleInfo(void);

//=====================================================================================
// Fonction		: HtmlPrint_IpRoutePolicyInfo
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/04/2010
// Description	: Code HTML de la liste des routes Ip politiques
//=====================================================================================
void HtmlPrint_IpRoutePolicyInfo(void);

//=====================================================================================
// Fonction		: HtmlPrint_OngletRouting
// Entrees		: <loc_u8_idx_html> : index page HTML active
// Sortie		: rien
// Auteur		: CM - 15/04/2010
// Description	: Code HTML des onglets des pages HTML de routing
//=====================================================================================
void HtmlPrint_OngletRouting(u8sod loc_u8_idx_html);

//=====================================================================================
// Fonction		: HtmlPrint_TableRoutageActive
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/04/2010
// Description	: Code HTML de la table de routage active
//=====================================================================================
void HtmlPrint_TableRoutageActive(void);

//=====================================================================================
// Fonction		: InitModule_SUConfigRoutingGene
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigRoutingGene
//=====================================================================================
void InitModule_SUConfigRoutingGene(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

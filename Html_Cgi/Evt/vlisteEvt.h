/*========================================================================*/
/* NOM DU FICHIER  : vlisteEvt.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/02/2010											  */
/* Libelle         : HTML CGI: page HTML Evenements - liste				  */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 26/02/2010 CM
//	- CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VLISTEEVT
#define _VLISTEEVT_EXT
#else
#define _VLISTEEVT_EXT	extern
#endif

enum LISTE_NUM_PAGES_HTML_VLISTEEVT
{
	PAGE_VLISTEVT_NUM_1	=0,
	PAGE_VLISTEVT_NUM_2,
	NB_MAX_PAGES_HTML_VLISTEEVT
};

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: VListeEvt
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 29/06/2007
// Description	: Page HTML Liste des évènements
//				"URL=VListeEvt&param=<num_page_html>&hidden1=<numForm>"
//					<num_page_html> : numéro page HTML
//					<numForm> : suite action boutons
//=====================================================================================
void VListeEvt(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_VListeEvt
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de VListeEvt
//=====================================================================================
void InitModule_VListeEvt(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

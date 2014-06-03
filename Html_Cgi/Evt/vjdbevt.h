/*========================================================================*/
/* NOM DU FICHIER  : vjdbevt.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/02/2010											  */
/* Libelle         : HTML CGI: page HTML Evenements - Journal de bord	  */
/* Projet          : WRM100                                               */
/* Indice          : BE029												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 26/02/2010 CM
//	- CREATION
//BE029 10/05/2010 CM
// - Correction plantage page HTML Journal de bord (lors de plusieurs actualisations de la plage)
//	=> conséquences sémaphore SEMAPHORE_BDD_JDB bloqué, et jdb bloqué...
//	il semble que le le processus plante lors du html_tag (printf) raison ????
//	solution: on copie tout le jdb dans la RAM pour l'afficher
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VJDBEVT
#define _VJDBEVT_EXT
#else
#define _VJDBEVT_EXT	extern
#endif

enum LISTE_PAGES_HTML_JDB
{
	PAGE_HTML_JDB_CONFIG = 0,
	PAGE_HTML_JDB_1,			//1 seule page
	NB_MAX_PAGES_HTML_JDB
};

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: VJDBEvenement_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 11/03/2010
// Description	: Page rafraichissement page configuration VJDBEvenement
//				"URL=VJDBEvenement_Dyn&param=<numpage>
//					<numpage> : numéro de la page
//=====================================================================================
void VJDBEvenement_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: VJDBEvenement
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 11/03/2010
// Description	: Page HTML Configuration: JDB des évènements
//				"URL=VJDBEvenement&param=<numpage>&hidden1=<numForm>"
//					<numpage> : numéro de la page
//					<numForm> : suite action boutons
//=====================================================================================
void VJDBEvenement(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: HtmlJdb_Configuration
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: partie config jdb
//=====================================================================================
void HtmlJdb_Configuration(void);

//=====================================================================================
// Fonction		: HtmlJdb_PageDetail
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: partie page jdb détaillé
//=====================================================================================
void HtmlJdb_PageDetail(void);

//=====================================================================================
// Fonction		: HtmlAffiche_JdbPart
// Entrees		: <loc_u16_nb_evt_lus> : nombre d'évènements lus du fichier jdbpart
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: Affichage de tous les évènements du fichier jdbpart
//=====================================================================================
void HtmlAffiche_JdbPart(u16sod loc_u16_nb_evt_lus);

//=====================================================================================
// Fonction		: HtmlAffiche_EvtJdb
// Entrees		: <loc_ps_evt<	: element qui doit etre affiché
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: Affichage d'un évènement du journal de bord
//=====================================================================================
void HtmlAffiche_EvtJdb(S_STRUCT_JDBEVT *loc_ps_evt);

//=====================================================================================
// Fonction		: u8AjouteEvtFifoHtmlJdb
// Entrees		: <loc_ps_evt<	: element qui doit etre ajouté
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 11/03/2010 -
// Description	: Ajoute element jdb dans la fifo html
//=====================================================================================
u8sod u8AjouteEvtFifoHtmlJdb(S_STRUCT_JDBEVT *loc_ps_evt);

//=====================================================================================
// Fonction		: LectureCompleteJDB
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/05/2010
// Description	: lecture complète du journal de bord  (de l'évènement du plus récent au plus ancien)
//=====================================================================================
void LectureCompleteJDB(void);

//=====================================================================================
// Fonction		: CopyPartToCompletJdb
// Entrees		: <loc_u16_nb_evt_lus> : nombre d'évènements lus du fichier jdbpart
// Sortie		: rien
// Auteur		: CM - 11/05/2010
// Description	: Lecture de tous les évènements du fichier jdbpart et on copie dans jdb complet
//=====================================================================================
void CopyPartToCompletJdb(u16sod loc_u16_nb_evt_lus);

//=====================================================================================
// Fonction		: InitCompletHtmlJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/05/2010
// Description	: Initialisation du jdb complet utilisée pour construire la page HTML
//=====================================================================================
void InitCompletHtmlJdb(void);

//=====================================================================================
// Fonction		: InitFifoHtmlJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: Initialisation de la fifo utilisée pour construire la page HTML
//=====================================================================================
void InitFifoHtmlJdb(void);

//=====================================================================================
// Fonction		: InitModule_VJdbEvt
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de vjdbevt
//=====================================================================================
void InitModule_VJdbEvt(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

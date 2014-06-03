/*========================================================================*/
/* NOM DU FICHIER  : bdd_html.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: Base de données commune des pages HTML	  */
/* Projet          : WRM100                                               */
/* Indice          : BE042                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE008 28/01/2010 CM
// - Gestion fichier configuration debug.ini
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _BDD_HTML
#define _BDD_HTML_EXT
#else
#define _BDD_HTML_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//============================================================================
// Fonction		: u8TestStartHtml
// Entrees		: rien
// Sortie		: <loc_u8_resultat> : indique si test démarrage
// Auteur		: CM - 04/11/2009 -
// Description	: renvoie la page d'avertissement si bdd inacessible
//					a appeler au demarrage de chaque page HTML (frameC)
//============================================================================
u8sod u8TestStartHtml(void);

//============================================================================
// Fonction		: u16GetTpsRefreshHtml
// Entrees		: 
// Sortie		: <loc_u16_tps_refresh_html> : temps de rafraichissement
// Auteur		: CM - 23/08/2007 -
// Description	: renvoie le tps de rafraichissement des pages HTML actuellement configuree
//============================================================================
u16sod u16GetTpsRefreshHtml(void);

//=====================================================================================
// Fonction		: InitModule_Bdd_Html
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/06/2007 -
// Description	: Initialisation du module Bdd_html
//=====================================================================================
void InitModule_Bdd_Html(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


//Photo de la base de données de l'équipement (pour utiliser dans les
//pages HTML)

_BDD_HTML_EXT S_STRUCT_CONFIGURATION s_html_cfg_eqpmt;
_BDD_HTML_EXT S_STRUCT_EXPLOITATION s_html_exploit;
_BDD_HTML_EXT S_STRUCT_HTTP_GLOBAL s_html_global;
_BDD_HTML_EXT S_STRUCT_DEBUG_GLOBAL s_html_debug_global;
_BDD_HTML_EXT S_STRUCT_EXPLOIT_EVENTS s_html_exp_events;

_BDD_HTML_EXT S_STRUCT_EVENTSYSTEM	*pt_html_eventsystem;

_BDD_HTML_EXT S_STRUCT_LIST_FREQ s_html_list_freq;

//Gestion CIP
_BDD_HTML_EXT S_STRUCT_CIP_SNMPD s_cip_snmpd_from_html;
_BDD_HTML_EXT S_STRUCT_CIP_JDB s_cip_jdb_from_html;

//Gestion du journal de bord
_BDD_HTML_EXT	S_STRUCT_STATUTJDB s_statutjdb_from_html;


//Pour gérer langue du site web
_BDD_HTML_EXT u8sod	 u8_html_langue;

//Pour gérer probleme accès à la base de données
_BDD_HTML_EXT u8sod u8_html_base_donnees_inaccessible;

//Variables utilisées dans les pages HTML
_BDD_HTML_EXT s8sod	 ps8_pageHtmlRetour[100];
_BDD_HTML_EXT s8sod	 ps8_pageHtmlEnCours[100];

//Pour utiliser dans les pages HTML si nécessaire
_BDD_HTML_EXT s8sod	 ps8_html_string[1000];



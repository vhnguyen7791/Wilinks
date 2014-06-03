/*========================================================================*/
/* NOM DU FICHIER  : Html_define.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: define utilisés par le process			  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define ACTIVATION_PRESENCE_SYNOPTIQUE	0	//0: pas de synoptique, 1: présence synoptique

#define ACTIVATION_CONSOLE_HTML	0	//0: console désactivée, 1: console activée

#define HOMEA_LOGO_SODIEL_PLUS_CLIENT 1	//0: sans logo client, 1 : avec logo client

#define ACTIVATION_MISE_A_L_HEURE_HTTP	1	//0: mise à l'heure par HTTP désactivée	, 1: MAH HTTP activée

#define IMAGE_SUR_PAGE_ACCUEIL	0		//0: pas d'image sur la page d'accueil, 1 : image sur la page d'accueil

#define AFFICHAGE_INFORMATIONS_SUPPLEMENTAIRES_HOMEA	1	//0: pas d'informations générales affichées dans homeA, 1: informations générales affichées dans homeA

#define AFFICHAGE_HTML_VERSIONS_LOGICIELLES_ONLY	1	//1: uniquement, 0: avec divers (options,...)


#define html_tag printf

#define HTML_CARACTERE_PLUS_MOINS "&#177;"

#define CHECKBOX_VALUE_CHECKED	"1"

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


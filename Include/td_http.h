/*========================================================================*/
/* NOM DU FICHIER  : td_http.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 04/07/2007                                           */
/* Libelle         : Base de données: type def serveur HTTP				  */
/* Projet          : WRM100                                               */
/* Indice	       : BE047												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

//Variable : S_STRUCT_HTTP_GLOBAL
//Champs : ps8_nom_page_html_enter_pwd
#define TAILLE_MAX_NOM_PAGE_HTML	200

//Variable : S_STRUCT_CLIENT_CONNECTE
//Champs : s_client[].s32_AccessLevel
#define		LOW_LEVEL_ACCESS	0
#define		MIDDLE_LEVEL_ACCESS	1
#define		HIGH_LEVEL_ACCESS	2

//Nom des utilisateurs
#define NOM_USER_ROOT	"root"
#define NOM_USER_HIGH	"userhigh"
#define NOM_USER_MIDDLE	"usermiddle"
#define NOM_USER_LOW	"userlow"

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

// Caractéristiques d'un client connecté 
typedef struct
{
	u8sod	u8_flag_connecte;	//Indique si le client est connecté
	s8sod	ps8_addrIP[MAX_LG_FORMAT_ADRESSE_IP+1];		// Adresse Ip du client
	s32sod	s32_AccessLevel;	// Droit d'accès
	time_t	u32_time;			// heure de connexion

}S_STRUCT_CLIENT_CONNECTE;

//*****************************************
/* structure HTTP de l'équipement		  */
//*****************************************
typedef struct 
{
	s8sod	ps8_nom_page_html_enter_pwd[TAILLE_MAX_NOM_PAGE_HTML+1];	//Nom de la page à accéder avant de saisir le mot de passe nécessaire
	S_STRUCT_CLIENT_CONNECTE s_client[NB_CLIENT_IP_MAX];

	u8sod	u8_connexion_prioritaire_http; //Signale une connexion en root (mot de passe goLum)
	s8sod	ps8_url_cfginprogress[TAILLE_MAX_NOM_PAGE_HTML+1];	//url à accèder après la configuration
	
}S_STRUCT_HTTP_GLOBAL;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/



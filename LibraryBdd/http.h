/*========================================================================*/
/* NOM DU FICHIER  : http.h												  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 04/07/2007                                           */
/* Libelle         : Base de données: serveur HTTP						  */
/* Projet          : WRM100                                               */
/* Indice	       : BE000												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _HTTP
#define _HTTP_EXT
#else
#define _HTTP_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8FillHttpFile
// Entrees		: <loc_ps_http< : pointeur sur la base de données HTTP
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture du fichier
//=====================================================================================
u8sod u8FillHttpFile(S_STRUCT_HTTP_GLOBAL *loc_ps_http);

//=====================================================================================
// Fonction		: u8EditHttpFile
// Entrees		: <loc_ps_http< : pointeur sur la base de données HTTP
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture  du fichier
//=====================================================================================
u8sod u8EditHttpFile(S_STRUCT_HTTP_GLOBAL *loc_ps_http);

//=====================================================================================
// Fonction		: InitClientIp
// Entrees		: <loc_ps_client< : pointeur du client
// Sortie		: rien
// Auteur		: CM - 04/07/2007 -
// Description	: Initialisation du module de Http de l'équipement
//=====================================================================================
void InitClientIp(S_STRUCT_CLIENT_CONNECTE	*loc_ps_client);

//=====================================================================================
// Fonction		: InitBDD_Http
// Entrees		: <loc_ps_http< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 04/07/2007 -
// Description	: Initialisation de la base de données de http
//=====================================================================================
void InitBDD_Http(S_STRUCT_HTTP_GLOBAL *loc_ps_http);

//=====================================================================================
// Fonction		: InitModule_Http
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 04/07/2007 -
// Description	: Initialisation du module de Http de l'équipement
//=====================================================================================
void InitModule_Http(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

#ifdef _HTTP
#else
//Contenu du fichier http.ini
_HTTP_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_HTTP_INI[];
//Définition du fichier http.ini
_HTTP_EXT	T_STRUCT_DEFINITION_FILE_FS		T_DEF_FILE_HTTP_INI;
#endif

/*========================================================================*/
/* NOM DU FICHIER  : cfg_http.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 28/01/2010                                           */
/* Libelle         : Principal: Configuration du serveur HTTP			  */
/* Projet          : WRM100                                               */
/* Indice          : BE009                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE009 01/02/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_HTTP
#define _CFG_HTTP_EXT
#else
#define _CFG_HTTP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_Http
// Entrees		: <loc_ps_exploit<: exploitation (RAM) pour ce processus
//				: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Installe http
//=====================================================================================
void Install_Http(S_STRUCT_EXPLOITATION *loc_ps_exploit, S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_Http
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Désinstalle  http
//=====================================================================================
void Uninstall_Http(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8CreationFichierIndexHtml
// Entrees		: <loc_u8_type_equipement> : type d'équipement
//				  <loc_u8_langue> : langue
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 10/10/2007 -
// Description	: Edition du fichier index.html pour le serveur boa
//=====================================================================================
u8sod u8CreationFichierIndexHtml(u8sod loc_u8_type_equipement, u8sod loc_u8_langue);

//=====================================================================================
// Fonction		: InitModule_Cfg_Http
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Initialisation du module de cfg_http
//=====================================================================================
void InitModule_Cfg_Http(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


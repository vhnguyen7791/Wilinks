/*========================================================================*/
/* NOM DU FICHIER  : cfg_ntp.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/02/2010                                           */
/* Libelle         : Principal: Configuration du CLIENT NTP				  */
/* Projet          : WRM100                                               */
/* Indice          : BE009                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE009 01/02/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_NTP
#define _CFG_NTP_EXT
#else
#define _CFG_NTP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_ClientNtp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 01/02/2010 -
// Description	: Installe client NTP
//=====================================================================================
void Install_ClientNtp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_ClientNtp
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 01/02/2010 -
// Description	: Désinstalle  client NTP
//=====================================================================================
void Uninstall_ClientNtp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: RequestNtp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Requete Ntp
//=====================================================================================
void RequestNtp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: GestionClientNTP
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Gestion client NTP
//=====================================================================================
void GestionClientNTP(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8CreationFichierCfgNtp
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 01/02/2010 -
// Description	: Edition du fichier ntp.conf pour le processus ntpd
//=====================================================================================
u8sod u8CreationFichierCfgNtp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_Ntp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/02/2010 -
// Description	: Initialisation du module de cfg_ntp
//=====================================================================================
void InitModule_Cfg_Ntp(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


/*========================================================================*/
/* NOM DU FICHIER  : cfg_dhcp.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 15/01/2010                                           */
/* Libelle         : Principal: Configuration du serveur / relai DHCP	  */
/* Projet          : WRM100                                               */
/* Indice          : BE005                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE005 15/01/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_DHCP
#define _CFG_DHCP_EXT
#else
#define _CFG_DHCP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_FctDHCP
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Installe la configuration de la fonction DHCP
//=====================================================================================
void Install_FctDHCP(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_FctDHCP
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Désinstalle la configuration de la fonction DHCP
//=====================================================================================
void Uninstall_FctDHCP(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_DHCP_serveur
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Installe la configuration du serveur DHCP
//=====================================================================================
void Install_DHCP_serveur(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_DHCP_serveur
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Désinstalle la configuration du serveur DHCP
//=====================================================================================
void Uninstall_DHCP_serveur(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_DHCP_relay
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Installe la configuration du relai DHCP
//=====================================================================================
void Install_DHCP_relay(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_DHCP_relay
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Désinstalle la configuration du relay DHCP
//=====================================================================================
void Uninstall_DHCP_relay(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8CreationFichierCfgUdhcpd
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 15/01/2010 -
// Description	: Edition du fichier udhcpd.conf pour le processus udhcpd (busybox)
//=====================================================================================
u8sod u8CreationFichierCfgUdhcpd(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_Dhcp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Initialisation du module de cfg_dhcp
//=====================================================================================
void InitModule_Cfg_Dhcp(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


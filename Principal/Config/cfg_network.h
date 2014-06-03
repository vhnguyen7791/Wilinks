/*========================================================================*/
/* NOM DU FICHIER  : cfg_network.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 12/11/2009                                           */
/* Libelle         : Principal: Configuration du réseau					  */
/* Projet          : WRM100                                               */
/* Indice          : BE047                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Intégration configuration hostname
// - Intégration configuration par DHCP client
//BE007 25/01/2010 CM
// - Correction bug hostapd lors de modification paramètres réseau (en particulier ath0 down)
// - Modification gestion routage statique
//BE010 03/02/2010 CM
// - Ajout information statut IP des interfaces
//		valeur: static, DHCP in progress, success DHCP, failure DHCP
//BE014 08/03/2010 CM
// - Modification gestion de l'exploitation
//	=> toute l'exploitation est calculée dans le processus 'monitor'.
//BE020 23/03/2010 CM
// - Ajout gestion VLAN
//BE025 15/04/2010 CM
// - Modification gestion reconfiguration (quand interface down)
// - Modification gestion routage par le processus bird
//	et non plus via des commandes de type "route"
// - Correction bug passerelle perdue (quand interface down) (cas avec cmd route)
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_NETWORK
#define _CFG_NETWORK_EXT
#else
#define _CFG_NETWORK_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: CmdIfconfig_Down
// Entrees		: <loc_ps8_nom_interface> : nom de l'interface à mettre DOWN
// Sortie		: rien
// Auteur		: CM - 25/01/2010 -
// Description	: Mise DOWN de l'interface
//=====================================================================================
void CmdIfconfig_Down(s8sod *loc_ps8_nom_interface);

//=====================================================================================
// Fonction		: CmdIfconfig_Up
// Entrees		: <loc_ps8_nom_interface> : nom de l'interface à mettre UP
//				: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 25/01/2010 -
// Description	: Mise UP de l'interface
//=====================================================================================
void CmdIfconfig_Up(s8sod *loc_ps8_nom_interface, S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CmdIfconfigEthernetAliasTempo_Down
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/12/2010 -
// Description	: Mise DOWN de l'interface temporaire (alias)
//=====================================================================================
void CmdIfconfigEthernetAliasTempo_Down(void);

//=====================================================================================
// Fonction		: CmdIfconfigEthernetAliasTempo_Up
// Entrees		: <loc_u32_adresse_ip> : adresse IP
//				: <loc_u32_mask> : masque de sous-reseau
// Sortie		: rien
// Auteur		: CM - 02/12/2010 -
// Description	: Mise UP de l'interface temporaire (alias)
//=====================================================================================
void CmdIfconfigEthernetAliasTempo_Up(u32sod loc_u32_adresse_ip, u32sod loc_u32_mask);



//=====================================================================================
// Fonction		: Install_Hostname
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 06/01/2010 -
// Description	: Installe la configuration du hostname
//=====================================================================================
void Install_Hostname(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_BridgeVlan
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 23/03/2010 -
// Description	: Installe la configuration VLAN (bridge)
//=====================================================================================
void Install_BridgeVlan(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_BridgeVlan
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 23/03/2010 -
// Description	: Désinstalle la configuration VLAN (bridge)
//=====================================================================================
void Uninstall_BridgeVlan(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_NetworkBridge
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du réseau bridge
//=====================================================================================
void Install_NetworkBridge(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_NetworkBridge
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Désinstalle la configuration du réseau bridge
//=====================================================================================
void Uninstall_NetworkBridge(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_NetworkRouter
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du réseau router
//=====================================================================================
void Install_NetworkRouter(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_NetworkRouter
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Désinstalle la configuration du réseau router
//=====================================================================================
void Uninstall_NetworkRouter(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: ExecReconfiguration_Routage
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 25/01/2010 -
// Description	: Reconfigurer la table de routage statique
//=====================================================================================
void ExecReconfiguration_Routage(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: RazStatutIP_Interfaces
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/02/2010 -
// Description	: Remise à zéro du statut des interfaces
//=====================================================================================
void RazStatutIP_Interfaces(void);

//=====================================================================================
// Fonction		: InitModule_Cfg_Network
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/11/2009 -
// Description	: Initialisation du module de cfg_network
//=====================================================================================
void InitModule_Cfg_Network(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

//Statut de l'adresse IP de l'interface bridge
_CFG_NETWORK_EXT u8sod u8_bridge_autostatut_ip;
//Statut de l'adresse IP de l'interface WLAN
_CFG_NETWORK_EXT u8sod u8_wlan_autostatut_ip;

//Flag démarrage installation du DHCP client
_CFG_NETWORK_EXT u8sod u8_start_installDHCPClient;

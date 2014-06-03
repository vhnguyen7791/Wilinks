/*========================================================================*/
/* NOM DU FICHIER  : cfg_multicast.h									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/03/2010                                           */
/* Libelle         : Principal: Configuration du Multicast				  */
/* Projet          : WRM100                                               */
/* Indice          : BE025                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE022 30/03/2010 CM
// - CREATION
//BE025 15/04/2010 CM
// - Modification gestion reconfiguration (quand interface down)
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_MULTICAST
#define _CFG_MULTICAST_EXT
#else
#define _CFG_MULTICAST_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: ExecReconfiguration_Multicast
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 31/03/2010 -
// Description	: Reconfigurer multicast
//=====================================================================================
void ExecReconfiguration_Multicast(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_RouteForMulticast
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				  <loc_u8_interface>: sur l'interface sélectionnée
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Installe la route pour multicast
//=====================================================================================
void Install_RouteForMulticast(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_interface);

//=====================================================================================
// Fonction		: Uninstall_RouteForMulticast
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
//				  <loc_u8_interface>: sur l'interface sélectionnée
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Désinstalle la route associée au multicast
//=====================================================================================
void Uninstall_RouteForMulticast(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_interface);

//=====================================================================================
// Fonction		: Install_MulticastBridge
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Installe la configuration du multicast IP (bridge)
//=====================================================================================
void Install_MulticastBridge(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_MulticastBridge
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Désinstalle la configuration du multicast IP (bridge)
//=====================================================================================
void Uninstall_MulticastBridge(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_MulticastRouter
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Installe la configuration du multicast IP (router)
//=====================================================================================
void Install_MulticastRouter(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_MulticastRouter
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Désinstalle la configuration du multicast IP (router)
//=====================================================================================
void Uninstall_MulticastRouter(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8CreationFichierCfgIgmpProxy
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Edition du fichier igmpproxy.conf pour le processus igmpproxy
//=====================================================================================
u8sod u8CreationFichierCfgIgmpProxy(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_Multicast
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Initialisation du module de cfg_multicast
//=====================================================================================
void InitModule_Cfg_Multicast(void);





/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


/*========================================================================*/
/* NOM DU FICHIER  : apply_cfg.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/04/2009                                           */
/* Libelle         : Principal: Application de la configuration			  */
/* Projet          : WRM100                                               */
/* Indice          : BE026                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE014 08/03/2010 CM
// - Modification gestion de l'exploitation
//	=> toute l'exploitation est calculée dans le processus 'monitor'.
//BE025 15/04/2010 CM
// - Modification gestion reconfiguration (quand interface down)
// - Correction bug passerelle perdue (quand interface down) (cas avec cmd route)
//BE026 26/04/2010 CM
// - Correction gestion passerelle via bird (qd station / router en client DHCP)
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _APPLY_CFG
#define _APPLY_CFG_EXT
#else
#define _APPLY_CFG_EXT	extern
#endif

//Liste des ordres de reconfiguration
enum LISTE_ORDRES_RECONFIG
{
	ORDRE_RECONFIG__ROUTAGE_POLICY = 0,
	ORDRE_RECONFIG__ROUTAGE_MULTICAST,
	ORDRE_RECONFIG__WPA_SUPPLICANT,
	ORDRE_RECONFIG__HOSTAPD,
	NB_MAX_ORDRE_RECONFIG
};

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_General
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe générale
//=====================================================================================
void Install_General(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: ImposeConfigSiEvolution
// Entrees		: <loc_ps_new_config< : nouvelle configuration
//				: <loc_ps_old_config< : ancienne configuration
//				: <loc_pt_newcfg< : tableau signalant une nouvelle configuration
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Sur changement de certains paramètres, on impose la configuration
//=====================================================================================
void ImposeConfigSiEvolution(S_STRUCT_CONFIGURATION *loc_ps_new_config, S_STRUCT_CONFIGURATION *loc_ps_old_config, T_STRUCT_OF_FILE_NEWCFG_INI *loc_pt_newcfg);

//=====================================================================================
// Fonction		: ExecuteApplyConfig
// Entrees		: <loc_ps_new_config< : nouvelle configuration
//				: <loc_ps_old_config< : ancienne configuration
//				: <loc_u32_reconfig_total> : ordre de reconfiguration
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Applique la nouvelle configuration
//=====================================================================================
void ExecuteApplyConfig(S_STRUCT_CONFIGURATION *loc_ps_new_config, S_STRUCT_CONFIGURATION *loc_ps_old_config, u32sod loc_u32_reconfig_total);

//=====================================================================================
// Fonction		: ExecuteGestionInstall
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 07/01/2009 -
// Description	: Gestion des installlations réalisées sur les services
//					appelée en tache de fond
//=====================================================================================
void ExecuteGestionInstall(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: ControlAccessPoint_ON_OFF
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 21/01/2011 -
// Description	: controle AP en fonction etat ethernet
//=====================================================================================
void ControlAccessPoint_ON_OFF(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: GestionInstall_DHCPClient
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 06/01/2010 -
// Description	: Gestion de l'installation du DHCP client (modes dégradés: exemple repli IP, si DHCP echoue)
//=====================================================================================
void GestionInstall_DHCPClient(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u32GetGatewayByDefault
// Entrees		: rien
// Sortie		: <loc_u32_gateway>
// Auteur		: CM - 26/04/2010 -
// Description	: Récupère valeur de l'adresse par défaut (si ça n'existe pas, retourne adresse nulle)
//=====================================================================================
u32sod u32GetGatewayByDefault(void);

//=====================================================================================
// Fonction		: ClearOrdreReconfiguration
// Entrees		: <loc_u8_idx_ordre> : index de l'ordre de reconfiguration
// Sortie		: rien
// Auteur		: CM - 21/04/2010 -
// Description	: RAZ ordre de reconfig
//=====================================================================================
void ClearOrdreReconfiguration(u8sod loc_u8_idx_ordre);

//=====================================================================================
// Fonction		: SetOrdreReconfiguration
// Entrees		: <loc_u8_idx_ordre> : index de l'ordre de reconfiguration
// Sortie		: rien
// Auteur		: CM - 21/04/2010 -
// Description	: Ordre de reconfigurer
//=====================================================================================
void SetOrdreReconfiguration(u8sod loc_u8_idx_ordre);

//=====================================================================================
// Fonction		: u8TestOrdreReconfiguration
// Entrees		: <loc_u8_idx_ordre> : index de l'ordre de reconfiguration
// Sortie		: <loc_u8_resultat> : etat de l'ordre de reconfiguration
// Auteur		: CM - 21/04/2010 -
// Description	: Retourne état de l'ordre de reconfiguration
//=====================================================================================
u8sod u8TestOrdreReconfiguration(u8sod loc_u8_idx_ordre);

//=====================================================================================
// Fonction		: InitModule_Apply_Cfg
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de apply_cfg
//=====================================================================================
void InitModule_Apply_Cfg(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

_APPLY_CFG_EXT u8sod pu8_ordre_reconfig[NB_MAX_ORDRE_RECONFIG];

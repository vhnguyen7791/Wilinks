/*========================================================================*/
/* NOM DU FICHIER  : cfg_bird.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 20/04/2010                                           */
/* Libelle         : Principal: Configuration de bird					  */
/* Projet          : WRM100                                               */
/* Indice          : BE026                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE025 20/04/2010 CM
// - CREATION
//BE026 26/04/2010 CM
// - Correction gestion passerelle via bird (qd station / router en client DHCP)
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_BIRD
#define _CFG_BIRD_EXT
#else
#define _CFG_BIRD_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_Bird
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_u32_wlan_adr_ip> : adresse IP de l'accès WLAN
//				: <loc_u32_wlan_mask> : Masque sous-réseau de l'accès WLAN
//				: <loc_u32_wlan_gateway> : Passerelle de l'accès WLAN
// Sortie		: rien
// Auteur		: CM - 20/04/2010 -
// Description	: Installe bird
//=====================================================================================
void Install_Bird(S_STRUCT_CONFIGURATION *loc_ps_config, u32sod loc_u32_wlan_adr_ip, u32sod loc_u32_wlan_mask, u32sod loc_u32_wlan_gateway);

//=====================================================================================
// Fonction		: Uninstall_Bird
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 20/04/2010 -
// Description	: Désinstalle bird
//=====================================================================================
void Uninstall_Bird(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8CreationFichierCfgBird
// Entrees		: <loc_ps_config< : config de l'équipement
//				: <loc_u32_wlan_adr_ip> : adresse IP de l'accès WLAN
//				: <loc_u32_wlan_mask> : Masque sous-réseau de l'accès WLAN
//				: <loc_u32_wlan_gateway> : Passerelle de l'accès WLAN
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 20/04/2010 -
// Description	: Edition du fichier bird.conf pour le processus bird
//=====================================================================================
u8sod u8CreationFichierCfgBird(S_STRUCT_CONFIGURATION *loc_ps_config, u32sod loc_u32_wlan_adr_ip, u32sod loc_u32_wlan_mask, u32sod loc_u32_wlan_gateway);

//=====================================================================================
// Fonction		: InitModule_Cfg_Bird
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 20/04/2010 -
// Description	: Initialisation du module de cfg_bird
//=====================================================================================
void InitModule_Cfg_Bird(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


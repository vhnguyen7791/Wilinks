/*========================================================================*/
/* NOM DU FICHIER  : cfg_hostapd.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/11/2009                                           */
/* Libelle         : Principal: Configuration du HOSTAPD				  */
/* Projet          : WRM100                                               */
/* Indice          : BE025                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/11/09 CM
// - CREATION
//BE007 25/01/2010 CM
// - Correction bug hostapd lors de modification paramètres réseau (en particulier ath0 down)
//BE025 15/04/2010 CM
// - Modification gestion reconfiguration (quand interface down)
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_HOSTAPD
#define _CFG_HOSTAPD_EXT
#else
#define _CFG_HOSTAPD_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: ExecReconfiguration_HostApd
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 25/01/2010 -
// Description	: Reconfigurer le processus hostapd (si présent)
//=====================================================================================
void ExecReconfiguration_HostApd(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_Hostapd
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Installe hostapd
//=====================================================================================
void Install_Hostapd(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_Hostapd
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Désinstalle hostapd
//=====================================================================================
void Uninstall_Hostapd(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8CreationFichierCfgHostapd
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 24/11/2009 -
// Description	: Edition du fichier hostapd.conf pour le processus hostapd
//=====================================================================================
u8sod u8CreationFichierCfgHostapd(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_Hostapd
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Initialisation du module de cfg_hostapd
//=====================================================================================
void InitModule_Cfg_Hostapd(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


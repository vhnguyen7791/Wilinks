/*========================================================================*/
/* NOM DU FICHIER  : cfg_wpa_supplicant.h								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/11/2009                                           */
/* Libelle         : Principal: Configuration du WPA_SUPPLICANT			  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/11/2009 CM
// - CREATION
//BE021 24/03/2010 CM
// - Correction BUG liaison bridge-bridge
//BE025 15/04/2010 CM
// - Modification gestion reconfiguration (quand interface down)
//BE060 16/03/2011
// - Ajout fonction qui liste les fichiers dans répertoire
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_WPA_SUPPLICANT
#define _CFG_WPA_SUPPLICANT_EXT
#else
#define _CFG_WPA_SUPPLICANT_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: ExecReconfiguration_WpaSupplicant
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 26/03/2010 -
// Description	: Reconfigurer le processus wpa_supplicant (si présent)
//=====================================================================================
void ExecReconfiguration_WpaSupplicant(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_WpaSupplicant
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Installe wpa_supplicant
//=====================================================================================
void Install_WpaSupplicant(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_WpaSupplicant
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Désinstalle wpa_supplicant
//=====================================================================================
void Uninstall_WpaSupplicant(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8CreationFichierCfgWpaSupplicant
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 24/11/2009 -
// Description	: Edition du fichier wpa_supplicant.conf pour le processus wpa_supplicant
//=====================================================================================
u8sod u8CreationFichierCfgWpaSupplicant(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CopyCertificats_FlashToEtc
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 23/03/2011 -
// Description	: copie tous les fichiers stockés dans la flash sous ETC
//=====================================================================================
void CopyCertificats_FlashToEtc(void);

//=====================================================================================
// Fonction		: GestionCertificats_InVar
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: rien
// Auteur		: CM - 23/03/2011 -
// Description	: gère les certificats postés par SFTP par l'utilisateur (STATION)
//=====================================================================================
void GestionCertificats_InVar(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_Wpa_Supplicant
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Initialisation du module de cfg_wpa_supplicant
//=====================================================================================
void InitModule_Cfg_Wpa_Supplicant(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


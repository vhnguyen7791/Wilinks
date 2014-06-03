/*========================================================================*/
/* NOM DU FICHIER  : cfg_time.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/12/2010                                           */
/* Libelle         : Principal: Configuration du date/heure via network	  */
/* Projet          : WRM100                                               */
/* Indice          : BE050                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE050 09/12/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_TIME
#define _CFG_TIME_EXT
#else
#define _CFG_TIME_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_Time
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Installe time
//=====================================================================================
void Install_Time(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_Time
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Désinstalle time
//=====================================================================================
void Uninstall_Time(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_ZoneTime
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Installe time zone (fuseau horaire)
//=====================================================================================
void Install_ZoneTime(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_ZoneTime
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Désinstalle time zone (fuseau horaire)
//=====================================================================================
void Uninstall_ZoneTime(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: GestionConfigTime
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Gestion config time
//=====================================================================================
void GestionConfigTime(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_Time
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Initialisation du module de cfg_time
//=====================================================================================
void InitModule_Cfg_Time(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

_CFG_TIME_EXT u8sod u8_info_restart_time;

/*========================================================================*/
/* NOM DU FICHIER  : cfg_syslog.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 28/01/2010                                           */
/* Libelle         : Principal: Configuration du SYSTEM LOG				  */
/* Projet          : WRM100                                               */
/* Indice          : BE008                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE008 28/01/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_SYSLOG
#define _CFG_SYSLOG_EXT
#else
#define _CFG_SYSLOG_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_Systemlog
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Installe systemlog
//=====================================================================================
void Install_Systemlog(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_Systemlog
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Désinstalle  systemlog
//=====================================================================================
void Uninstall_Systemlog(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_Syslog
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Initialisation du module de cfg_syslog
//=====================================================================================
void InitModule_Cfg_Syslog(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


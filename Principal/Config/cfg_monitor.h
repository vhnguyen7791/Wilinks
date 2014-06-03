/*========================================================================*/
/* NOM DU FICHIER  : cfg_monitor.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 02/03/2010                                           */
/* Libelle         : Principal: Configuration du processus monitor		  */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 02/03/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_MONITOR
#define _CFG_MONITOR_EXT
#else
#define _CFG_MONITOR_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_Monitor
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Installe monitor
//=====================================================================================
void Install_Monitor(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_Monitor
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Désinstalle du processus monitor
//=====================================================================================
void Uninstall_Monitor(void);

//=====================================================================================
// Fonction		: InitModule_Cfg_Monitor
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Initialisation du module de cfg_monitor
//=====================================================================================
void InitModule_Cfg_Monitor(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


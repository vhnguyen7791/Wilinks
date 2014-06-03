/*========================================================================*/
/* NOM DU FICHIER  : cfg_jdb.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 10/03/2010                                           */
/* Libelle         : Principal: Configuration du journal de bord		  */
/* Projet          : WRM100                                               */
/* Indice          : BE015                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 10/03/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_JDB
#define _CFG_JDB_EXT
#else
#define _CFG_JDB_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_Jdb
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 10/03/2010 -
// Description	: Installe jdb
//=====================================================================================
void Install_Jdb(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_Jdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/03/2010 -
// Description	: Désinstalle du processus jdb
//=====================================================================================
void Uninstall_Jdb(void);

//=====================================================================================
// Fonction		: InitModule_Cfg_Jdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/03/2010 -
// Description	: Initialisation du module de cfg_jdb
//=====================================================================================
void InitModule_Cfg_Jdb(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


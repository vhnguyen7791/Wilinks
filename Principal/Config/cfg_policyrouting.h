/*========================================================================*/
/* NOM DU FICHIER  : cfg_policyrouting.h								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 19/04/2010                                           */
/* Libelle         : Principal: Configuration de la politique de routage  */
/* Projet          : WRM100                                               */
/* Indice          : BE025                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE025 19/04/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_POLICYROUTING
#define _CFG_POLICYROUTING_EXT
#else
#define _CFG_POLICYROUTING_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_IptablesMangleForPolicyRouting
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 16/04/2010 -
// Description	: Installe iptables mangle pour le routage politique
//=====================================================================================
void Install_IptablesMangleForPolicyRouting(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Install_RulesForPolicyRouting
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 16/04/2010 -
// Description	: Installe les routes politiques
//=====================================================================================
void Install_RulesForPolicyRouting(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_PolicyRouting
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 16/04/2010 -
// Description	: Désinstalle les routes politiques
//=====================================================================================
void Uninstall_PolicyRouting(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_PolicyRouting
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/04/2010 -
// Description	: Initialisation du module de cfg_policyrouting
//=====================================================================================
void InitModule_Cfg_PolicyRouting(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

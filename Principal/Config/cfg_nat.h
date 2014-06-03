/*========================================================================*/
/* NOM DU FICHIER  : cfg_nat.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/02/2010                                           */
/* Libelle         : Principal: Configuration du NAT					  */
/* Projet          : WRM100                                               */
/* Indice          : BE010                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE010 11/02/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_NAT
#define _CFG_NAT_EXT
#else
#define _CFG_NAT_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_Nat
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_u32_adr_ip_public_default> : adresse IP publique par défaut
//				: <loc_u32_mask_ip_public_default> : adresse IP publique par défaut
// Sortie		: rien
// Auteur		: CM - 11/02/2010 -
// Description	: Installe NAT
//=====================================================================================
void Install_Nat(S_STRUCT_CONFIGURATION *loc_ps_config, u32sod loc_u32_adr_ip_public_default, u32sod loc_u32_mask_ip_public_default);

//=====================================================================================
// Fonction		: Uninstall_Nat
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 11/02/2010 -
// Description	: Désinstalle  NAT
//=====================================================================================
void Uninstall_Nat(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_Nat
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/02/2010 -
// Description	: Initialisation du module de cfg_nat
//=====================================================================================
void InitModule_Cfg_Nat(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


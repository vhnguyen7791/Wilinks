/*========================================================================*/
/* NOM DU FICHIER  : cfg_sntp.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/12/2010                                           */
/* Libelle         : Principal: Configuration du CLIENT SNTP			  */
/* Projet          : WRM100                                               */
/* Indice          : BE050                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE050 09/12/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_SNTP
#define _CFG_SNTP_EXT
#else
#define _CFG_SNTP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_ClientSntp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Installe client SNTP
//=====================================================================================
void Install_ClientSntp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_ClientSntp
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Désinstalle  client SNTP
//=====================================================================================
void Uninstall_ClientSntp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: RequestSntp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Requete Sntp
//=====================================================================================
void RequestSntp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: GestionClientSntp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Gestion client SNTP
//=====================================================================================
void GestionClientSntp(S_STRUCT_CONFIGURATION *loc_ps_config);
   
//=====================================================================================
// Fonction		: InitModule_Cfg_Sntp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Initialisation du module de cfg_sntp
//=====================================================================================
void InitModule_Cfg_Sntp(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


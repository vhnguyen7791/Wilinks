/*========================================================================*/
/* NOM DU FICHIER  : gestconfig.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/04/2009                                           */
/* Libelle         : Principal: gestion de la configuration				  */
/* Projet          : WRM100                                               */
/* Indice          : BE042                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Int�gration configuration par DHCP client
//BE042 07/10/2010 CM
// - Ajout possibilit� de reconfigurer entierement l'�quipement
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _GESTCONFIG
#define _GESTCONFIG_EXT
#else
#define _GESTCONFIG_EXT	extern
#endif

#define ORDRE_RECONFIG_TOTALE_DESACTIVEE  0x00000000
#define ORDRE_RECONFIG_TOTALE_ACTIVEE	  0xECA8531B

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: ExecuteStartConfig
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Execute les �tapes suivantes (lors du d�marrage):
//				-> v�rification des fichiers de configuration (pr�sents dans la m�moire non volatile)
//					(checksum + conformit�)
//				-> extraction de la configuration
//				-> V�rification coh�rence de la configuration
//=====================================================================================
void ExecuteStartConfig(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: ExecuteGestionConfig
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Execute les �tapes suivantes (en r�gime �tabli):
//				-> v�rification evolution de la configuration
//				-> application de la configuration aux services n�cessaires
//				-> copie dans FLASH
//					appel�e en tache de fond
//=====================================================================================
void ExecuteGestionConfig(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Ordre_ReconfigurationTotale
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/10/2010 -
// Description	: Ordre de tout reconfigurer
//=====================================================================================
void Ordre_ReconfigurationTotale(void);

//=====================================================================================
// Fonction		: InitModule_GestConfig
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de gestconfig
//=====================================================================================
void InitModule_GestConfig(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/



/*========================================================================*/
/* NOM DU FICHIER  : evt_system.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 06/07/2010                                           */
/* Libelle         : Monitor: Calcul des évènements system				  */
/* Projet          : WRM100                                               */
/* Indice          : BE037                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE037 06/07/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EVT_SYSTEM
#define _EVT_SYSTEM_EXT
#else
#define _EVT_SYSTEM_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: CalculEvents_System
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_ps_exploit<: exploitation (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 06/07/2010 -
// Description	: Gestion des évènements system
//=====================================================================================
void CalculEvents_System(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EXPLOITATION *loc_ps_exploit);

//=====================================================================================
// Fonction		: CalculEvent_PbConfig
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_ps_exploit<: exploitation (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 06/07/2010 -
// Description	: Gestion de l'évènement probleme configuration
//=====================================================================================
void CalculEvent_PbConfig(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EXPLOITATION *loc_ps_exploit);

//=====================================================================================
// Fonction		: InitModule_Evt_System
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 06/07/2010 -
// Description	: Initialisation du module evt_system
//=====================================================================================
void InitModule_Evt_System(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/*_______VII - INITIALISATIONS NON PROGRAMMEES _____________________________*/


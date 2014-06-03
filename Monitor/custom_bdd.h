/*========================================================================*/
/* NOM DU FICHIER  : custom_bdd.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : Monitor: Personnalise la base de données			  */
/* Projet          : WRM100                                               */
/* Indice          : BE037                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _CUSTOM_BDD
#define _CUSTOM_BDD_EXT
#else
#define _CUSTOM_BDD_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: CustomBdd_EnFonctionAllOptionsHard
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: Personnalise la base de données en fonction de toutes
// les options hards
//=====================================================================================
void CustomBdd_EnFonctionAllOptionsHard(void);

//=====================================================================================
// Fonction		: CustomBdd_EnFonctionConfig
// Entrees		: <loc_ps_config<: pointeur sur configuration equipement
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: Personnalise la base de données en fonction de la configuration
//=====================================================================================
void CustomBdd_EnFonctionConfig(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CustomBddEvents_EnFonctionConfig
// Entrees		: <loc_ps_config<: pointeur sur configuration equipement
//				: <loc_pt_eventsystem< : pointeur sur systeme evt
// Sortie		: rien
// Auteur		: CM - 08/07/2010 -
// Description	: Personnalise la base de données des évènements en fonction de la configuration
//=====================================================================================
void CustomBddEvents_EnFonctionConfig(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EVENTSYSTEM *loc_pt_eventsystem);

//=====================================================================================
// Fonction		: InitModule_CustomBdd
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: Initialisation du module custom_Bdd
//=====================================================================================
void InitModule_CustomBdd(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/*_______VII - INITIALISATIONS NON PROGRAMMEES _____________________________*/

